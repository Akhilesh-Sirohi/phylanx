// Copyright (c) 2017-2018 Hartmut Kaiser
// Copyright (c) 2019 Bita Hasheminezhad
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_COMMON_TRANSPOSE_OPERATION_JUN_26_2019_0410PM)
#define PHYLANX_COMMON_TRANSPOSE_OPERATION_JUN_26_2019_0410PM

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/ir/node_data.hpp>
#include <phylanx/plugins/common/export_definitions.hpp>

#include <cstdint>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace phylanx { namespace common
{
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose0d1d(
        execution_tree::primitive_argument_type&& arg);

    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose2d(
        ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose2d(
        ir::node_data<T>&& arg, ir::node_data<std::int64_t>&& axes);

    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose2d(
        execution_tree::primitive_argument_type&& arg,
        std::string const& name, std::string const& codename);
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose2d(
        execution_tree::primitive_argument_type&& arg,
        ir::node_data<std::int64_t>&& axes, std::string const& name,
        std::string const& codename);

    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose3d_axes102(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose3d_axes021(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose3d_axes120(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose3d_axes201(ir::node_data<T>&& arg);

    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose3d(
        ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose3d(
        ir::node_data<T>&& arg, ir::node_data<std::int64_t>&& axes);

    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose3d(
        execution_tree::primitive_argument_type&& arg,
        std::string const& name, std::string const& codename);
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose3d(
        execution_tree::primitive_argument_type&& arg,
        ir::node_data<std::int64_t>&& axes, std::string const& name,
        std::string const& codename);

    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes0132(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes0213(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes0231(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes0312(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes0321(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes1023(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes1032(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes1203(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes1230(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes1302(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes1320(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes2013(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes2031(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes2103(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes2130(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes2301(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes2310(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes3012(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes3021(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes3102(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes3120(ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type
    transpose4d_axes3201(ir::node_data<T>&& arg);

    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose4d(
        ir::node_data<T>&& arg);
    template <typename T>
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose4d(
        ir::node_data<T>&& arg, ir::node_data<std::int64_t>&& axes);

    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose4d(
        execution_tree::primitive_argument_type&& arg,
        std::string const& name, std::string const& codename);
    PHYLANX_COMMON_EXPORT execution_tree::primitive_argument_type transpose4d(
        execution_tree::primitive_argument_type&& arg,
        ir::node_data<std::int64_t>&& axes, std::string const& name,
        std::string const& codename);
}}

#endif
