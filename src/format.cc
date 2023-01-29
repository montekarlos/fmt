// Formatting library for C++
//
// Copyright (c) 2012 - 2016, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

// See https://github.com/fmtlib/fmt/issues/1617 for more context on using
// libfmt on bare metal

// Be defining FMT_STATIC_THOUSANDS_SEPARATOR we avoid #including <locale>.
// Including results in large increase of memory usages (~150kB RAM, ~kB ROM)
// and we just don't need the locale aware separator on an embedded micro
#define FMT_STATIC_THOUSANDS_SEPARATOR '.'

// Disable support for formatting/parsing long doubles but maintain support
// for floats and doubles for now. Reduces ROM usage
#define FMT_USE_FLOAT 1
#define FMT_USE_DOUBLE 1
#define FMT_USE_LONG_DOUBLE 0

// Disable exceptions. Reduces ROM usage
#define FMT_THROW panic

#include "fmt/format-inl.h"

FMT_BEGIN_NAMESPACE
namespace detail {

template FMT_API auto dragonbox::to_decimal(float x) noexcept
    -> dragonbox::decimal_fp<float>;
template FMT_API auto dragonbox::to_decimal(double x) noexcept
    -> dragonbox::decimal_fp<double>;

#ifndef FMT_STATIC_THOUSANDS_SEPARATOR
template FMT_API locale_ref::locale_ref(const std::locale& loc);
template FMT_API auto locale_ref::get<std::locale>() const -> std::locale;
#endif

// Explicit instantiations for char.

template FMT_API auto thousands_sep_impl(locale_ref)
    -> thousands_sep_result<char>;
template FMT_API auto decimal_point_impl(locale_ref) -> char;

template FMT_API void buffer<char>::append(const char*, const char*);

}  // namespace detail
FMT_END_NAMESPACE
