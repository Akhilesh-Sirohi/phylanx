//   Copyright (c) 2017 Hartmut Kaiser
//
//   Distributed under the Boost Software License, Version 1.0. (See accompanying
//   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_AST_MATCH_HPP)
#define PHYLANX_AST_MATCH_HPP

#include <phylanx/config.hpp>
#include <phylanx/ast/node.hpp>
#include <phylanx/util/variant.hpp>

#include <hpx/util/detail/pack.hpp>
#include <hpx/util/invoke.hpp>
#include <hpx/util/tuple.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace phylanx { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Ast1, typename Ast2, typename F, typename ... Ts>
    bool match(Ast1 const&, Ast2 const&, F && f, Ts const&... ts)
    {
        return false;       // by default things don't match
    }

    template <typename Ast1, typename Ast2, typename F, typename... Ts>
    bool match(phylanx::util::recursive_wrapper<Ast1> const& ast1,
        Ast2 const& ast2, F&& f, Ts const&... ts)
    {
        return match (ast1.get(), ast2, std::forward<F>(f), ts...);
    }
    template <typename Ast1, typename Ast2, typename F, typename... Ts>
    bool match(Ast1 const& ast1,
        phylanx::util::recursive_wrapper<Ast2> const& ast2, F&& f,
        Ts const&... ts)
    {
        return match (ast1, ast2.get(), std::forward<F>(f), ts...);
    }
    template <typename Ast1, typename Ast2, typename F, typename... Ts>
    bool match(phylanx::util::recursive_wrapper<Ast1> const& ast1,
        phylanx::util::recursive_wrapper<Ast2> const& ast2, F&& f,
        Ts const&... ts)
    {
        return match (ast1.get(), ast2.get(), std::forward<F>(f), ts...);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(optoken const&, optoken const&, F&&, Ts const&...);

    template <typename F, typename... Ts>
    bool match(identifier const&, identifier const&, F&&, Ts const&...);

    template <typename F, typename... Ts>
    bool match(primary_expr const&, identifier const&, F&&, Ts const&...);
    template <typename F, typename... Ts>
    bool match(primary_expr const&, primary_expr const&, F&&, Ts const&...);

    template <typename F, typename... Ts>
    bool match(operand const&, identifier const&, F&&, Ts const&...);
    template <typename F, typename... Ts>
    bool match(operand const&, operand const&, F&&, Ts const&...);

    template <typename F, typename... Ts>
    bool match(unary_expr const&, identifier const&, F&&, Ts const&...);
    template <typename F, typename... Ts>
    bool match(unary_expr const&, unary_expr const&, F&&, Ts const&...);

    template <typename F, typename... Ts>
    bool match(operation const&, identifier const&, F&&, Ts const&...);
    template <typename F, typename... Ts>
    bool match(operation const&, operation const&, F&&, Ts const&...);

    template <typename F, typename... Ts>
    bool match(expression const&, identifier const&, F&&, Ts const&...);
    template <typename F, typename... Ts>
    bool match(expression const&, expression const&, F&&, Ts const&...);

    template <typename F, typename... Ts>
    bool match(function_call const&, identifier const&, F&&, Ts const&...);
    template <typename F, typename... Ts>
    bool match(function_call const&, function_call const&, F&&, Ts const&...);

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename F, typename... Ts>
        struct match_visitor
        {
//             match_visitor(F const& f, hpx::util::tuple<Ts const&...> const& t)
//               : f_(f), t_(t)
//             {}
            match_visitor(F && f, hpx::util::tuple<Ts const&...> const& t)
              : f_(static_cast<F&&>(f)), t_(t)
            {}

            F && f_;
            hpx::util::tuple<Ts const&...> const& t_;

            template <typename Ast1, typename Ast2, std::size_t... Is>
            inline bool call(Ast1 const& ast1, Ast2 const& ast2,
                hpx::util::detail::pack_c<std::size_t, Is...>) const
            {
                return match(ast1, ast2, f_, hpx::util::get<Is>(t_)...);
            }

            template <typename Ast1, typename Ast2>
            bool operator()(Ast1 const& ast1, Ast2 const& ast2) const
            {
                return call(ast1, ast2,
                    typename hpx::util::detail::make_index_pack<
                            sizeof...(Ts)
                         >::type());
            }
        };

        template <typename F, typename... Ts>
        match_visitor<F, Ts...>
        make_match_visitor(F && f, Ts const&... ts)
        {
            return match_visitor<F, Ts...>(
                std::forward<F>(f), hpx::util::forward_as_tuple(ts...));
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(optoken const& t1, optoken const& t2, F&& f, Ts const&... ts)
    {
        return t1 == t2;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(
        identifier const& id1, identifier const& id2, F&& f, Ts const&... ts)
    {
        // handle placeholder
        if (is_placeholder(id2) || is_placeholder(id1) || id1 == id2)
        {
            return hpx::util::invoke(std::forward<F>(f), id1, id2, ts...);
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(
        primary_expr const& pe1, primary_expr const& pe2, F&& f, Ts const&... ts)
    {
        return visit(
            detail::make_match_visitor(std::forward<F>(f), ts...), pe1, pe2);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(operand const& op, identifier const& id, F&& f, Ts const&... ts)
    {
        // handle placeholder
        if (is_placeholder(id))
        {
            return hpx::util::invoke(std::forward<F>(f), op, id, ts...);
        }
        return false;
    }

    template <typename F, typename... Ts>
    bool match(operand const& op1, operand const& op2, F&& f, Ts const&... ts)
    {
        return visit(
            detail::make_match_visitor(std::forward<F>(f), ts...), op1, op2);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(
        unary_expr const& pe1, unary_expr const& pe2, F&& f, Ts const&... ts)
    {
        if (!match(pe1.operator_, pe2.operator_, std::forward<F>(f), ts...))
            return false;       // operator does not match

        return match(pe1.operand_, pe2.operand_, std::forward<F>(f), ts...);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(
        operation const& op1, operation const& op2, F&& f, Ts const&... ts)
    {
        if (!match(op1.operator_, op2.operator_, std::forward<F>(f), ts...))
            return false;       // operator does not match

        return match(op1.operand_, op2.operand_, std::forward<F>(f), ts...);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(
        expression const& expr, identifier const& id, F&& f, Ts const&... ts)
    {
        // handle placeholder
        if (is_placeholder(id))
        {
            return hpx::util::invoke(std::forward<F>(f), expr, id, ts...);
        }
        return false;
    }

    namespace detail
    {
        // Find full subexpression with a given (or higher) precedence
        template <typename Ast>
        expression extract_subexpression(
            Ast const& ast, int prec,
            std::list<operation>::const_iterator& it,
            std::list<operation>::const_iterator end)
        {
            expression result(it->operand_);
            while (++it != end && precedence_of(it->operator_) > prec)
            {
                result.append(*it);
            }
            return result;
        }

        expression extract_subexpression(
            expression const& expr, int prec,
            std::list<operation>::const_iterator& it,
            std::list<operation>::const_iterator end)
        {
            ++it;
            return expr;
        }

        expression extract_subexpression(
            primary_expr const& pe, int prec,
            std::list<operation>::const_iterator& it,
            std::list<operation>::const_iterator end)
        {
            // primary expression refers to an expression itself
            if (pe.index() == 4)
            {
                return extract_subexpression(util::get<4>(pe.get()).get(),
                    prec, it, end);
            }

            expression result(it->operand_);
            while (++it != end && precedence_of(it->operator_) > prec)
            {
                result.append(*it);
            }
            return result;
        }

        expression extract_subexpression(
            operand const& op, int prec,
            std::list<operation>::const_iterator& it,
            std::list<operation>::const_iterator end)
        {
            // operand may refer to primary expression
            if (op.index() == 1)
            {
                return extract_subexpression(util::get<1>(op.get()).get(),
                    prec, it, end);
            }

            expression result(it->operand_);
            while (++it != end && precedence_of(it->operator_) > prec)
            {
                result.append(*it);
            }
            return result;
        }

        // The Shunting-yard algorithm
        template <typename F, typename ... Ts>
        bool match_expression(
            int min_precedence,
            std::list<operation>::const_iterator& it1,
            std::list<operation>::const_iterator end1,
            std::list<operation>::const_iterator& it2,
            std::list<operation>::const_iterator end2,
            F && f, Ts const&... ts)
        {
            while (it1 != end1 && it2 != end2 &&
                precedence_of(it1->operator_) >= min_precedence)
            {
                operation const& curr1 = *it1;
                operation const& curr2 = *it2;

                int prec = precedence_of(curr1.operator_);

                if (is_placeholder(*it1))
                {
                    if (!hpx::util::invoke(std::forward<F>(f), curr1,
                            extract_subexpression(
                                it2->operand_, prec, it2, end2),
                            ts...))
                    {
                        return false;
                    }
                    ++it1;
                    continue;
                }
                else if (is_placeholder(*it2))
                {
                    if (!hpx::util::invoke(std::forward<F>(f),
                            extract_subexpression(
                                it1->operand_, prec, it1, end1),
                            curr2, ts...))
                    {
                        return false;
                    }
                    ++it2;
                    continue;
                }

                if (!match(curr1.operand_, curr2.operand_, std::forward<F>(f),
                        ts...))
                {
                    return false;
                }

                ++it1;
                ++it2;

                while (it1 != end1 && it2 != end2 &&
                    precedence_of(it1->operator_) > prec)
                {
                    if (!match_expression(precedence_of(it1->operator_), it1,
                            end1, it2, end2, std::forward<F>(f), ts...))
                    {
                        return false;
                    }
                }

                if (!match(curr1.operator_, curr2.operator_, std::forward<F>(f),
                        ts...))
                {
                    return false;
                }
            }

            // bail out if the list lengths don't match
            if (it1 == end1)
            {
                return it2 == end2;
            }
            else if (it2 == end2)
            {
                return false;
            }

            return true;
        }
    }

    template <typename F, typename... Ts>
    bool match(expression const& expr1, expression const& expr2, F&& f,
        Ts const&... ts)
    {
        // check whether first operand matches
        if (!match(expr1.first, expr2.first, std::forward<F>(f), ts...))
            return false;

        // if one is empty, the other one should be empty as well
        if (expr1.rest.empty() || expr2.rest.empty())
            return expr1.rest.size() == expr2.rest.size();

        auto begin1 = expr1.rest.begin();
        auto begin2 = expr2.rest.begin();

        return detail::match_expression(0, begin1, expr1.rest.end(), begin2,
            expr2.rest.end(), std::forward<F>(f), ts...);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename F, typename... Ts>
    bool match(function_call const& fc, identifier const& id, F&& f,
        Ts const&... ts)
    {
        // handle placeholder
        if (is_placeholder(id))
        {
            return hpx::util::invoke(std::forward<F>(f), fc, id, ts...);
        }
        return false;
    }

    template <typename F, typename... Ts>
    bool match(function_call const& fc1, function_call const& fc2, F&& f,
        Ts const&... ts)
    {
        if (fc1.args.size() != fc2.args.size())
            return false;       // different number of operands

        if (!match(fc1.function_name, fc2.function_name,
                std::forward<F>(f), ts...))
        {
            return false;       // function name does not match
        }

        auto end1 = fc1.args.end();
        for (auto it1 = fc1.args.begin(), it2 = fc2.args.begin();
             it1 != end1; ++it1, ++it2)
        {
            if (!match(*it1, *it2, std::forward<F>(f), ts...))
                return false;   // one of the remaining operands does not match
        }

        return true;
    }
}}

#endif
