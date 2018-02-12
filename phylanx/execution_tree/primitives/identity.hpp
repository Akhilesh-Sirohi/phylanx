//   Copyright (c) 2017 Shahrzad Shirzad
//
//   Distributed under the Boost Software License, Version 1.0. (See accompanying
//   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_PRIMITIVES_IDENTITY_JAN_08_2018_0243PM)
#define PHYLANX_PRIMITIVES_IDENTITY_JAN_08_2018_0243PM

#include <phylanx/config.hpp>
#include <phylanx/ast/node.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/ir/node_data.hpp>

#include <hpx/include/components.hpp>

#include <vector>

namespace phylanx { namespace execution_tree { namespace primitives
{
    class identity
      : public base_primitive
      , public hpx::components::component_base<identity>
    {
    public:
        static match_pattern_type const match_data;

        identity() = default;

        PHYLANX_EXPORT identity(
            std::vector<primitive_argument_type>&& operands);

        PHYLANX_EXPORT hpx::future<primitive_argument_type> eval(
            std::vector<primitive_argument_type> const& args) const override;
    };
}}}

#endif