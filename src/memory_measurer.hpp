// Copyright 2016 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://sourceforge.net/projects/jsoncons/files/ for latest version
// See https://sourceforge.net/p/jsoncons/wiki/Home/ for documentation.

#ifndef JSON_BENCHMARKS_MEASURER_HPP
#define JSON_BENCHMARKS_MEASURER_HPP

#include <chrono>
#include "windows.h"
#include "psapi.h"
#undef max

namespace json_benchmarks {

class memory_measurer
{
public:
    static size_t total_virtual_memory()
    {
        MEMORYSTATUSEX mem_info;
        mem_info.dwLength = sizeof(mem_info);
        GlobalMemoryStatusEx(&mem_info);
        return mem_info.ullTotalPageFile;
    }
    static size_t virtual_memory_currently_used()
    {
        MEMORYSTATUSEX mem_info;
        mem_info.dwLength = sizeof(mem_info);
        GlobalMemoryStatusEx(&mem_info);
        return mem_info.ullTotalPageFile - mem_info.ullAvailPageFile;
    }
    static size_t virtual_memory_currently_used_by_current_process()
    {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        pmc.cb = sizeof(pmc); 
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        return pmc.PrivateUsage;    
    }
};

}

#endif

