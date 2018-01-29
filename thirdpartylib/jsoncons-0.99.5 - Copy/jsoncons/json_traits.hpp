// Copyright 2013 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSON_TRAITS_HPP
#define JSONCONS_JSON_TRAITS_HPP

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#endif

#include <jsoncons/serialization_options.hpp>
#include <jsoncons/parse_error_handler.hpp>
#include <string>
#include <vector>

namespace jsoncons {

template <class CharT>
struct json_traits
{
    template <class T,class Allocator>
    using base_container_type = std::vector<T,Allocator>;

    typedef typename std::char_traits<CharT> char_traits_type;

    static const bool preserve_order = false;

    typedef basic_default_parse_error_handler<CharT> parse_error_handler_type;
};

template <class CharT>
struct o_json_traits 
{
    template <class T,class Allocator>
    using base_container_type = std::vector<T,Allocator>;

    typedef typename std::char_traits<CharT> char_traits_type;

    static const bool preserve_order = true;

    typedef basic_default_parse_error_handler<CharT> parse_error_handler_type;
};

}

#endif
