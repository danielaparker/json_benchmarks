// Copyright 2016 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://sourceforge.net/projects/jsoncons/files/ for latest version
// See https://sourceforge.net/p/jsoncons/wiki/Home/ for documentation.

#ifndef JSON_BENCHMARKS_MEASURER_HPP
#define JSON_BENCHMARKS_MEASURER_HPP

namespace json_benchmarks {

class memory_measurer
{
public:
    static size_t get_process_memory();
};

}

#endif

