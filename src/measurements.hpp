// Copyright 2016 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://sourceforge.net/projects/jsoncons/files/ for latest version
// See https://sourceforge.net/p/jsoncons/wiki/Home/ for documentation.

#ifndef JSON_BENCHMARKS_MEASUREMENTS_HPP
#define JSON_BENCHMARKS_MEASUREMENTS_HPP

#include <chrono>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace json_benchmark {

    namespace fs = std::filesystem;

    template <class F>
    void json_file_finder(const char* dir_name, F f)
    {
        fs::path p{ dir_name };

        if (exists(p) && is_directory(p))
        {
            fs::directory_iterator end_iter;
            for (fs::directory_iterator dir_itr(p);
                dir_itr != end_iter;
                ++dir_itr)
            {
                if (fs::is_regular_file(dir_itr->status()))
                {
                    if (dir_itr->path().extension() == ".json")
                    {
                        f(dir_itr->path());
                    }
                }
            }
        }
    }

    struct measurements
    {
        std::string library_name;
        size_t memory_used{0};
        size_t time_to_read{0};
        size_t time_to_write{0};
    };

    enum class result_code
    {
        expected_result,
        expected_success_parsing_failed,
        expected_failure_parsing_succeeded,
        result_undefined_parsing_succeeded,
        result_undefined_parsing_failed,
        process_stopped
    };

    struct result_code_info
    {
        result_code code;
        std::string description;
        std::string color;
    };

    enum class expected_result : uint8_t
    {
        expect_success = 0,
        expect_failure = 1,
        result_undefined = 2
    };

    struct test_suite_file
    {
        fs::path path;
        expected_result type; 
        std::string text;
    };

    struct test_suite_result
    {
        result_code result;

        test_suite_result(result_code result) :
            result(result)
        {
        }
    };

    inline
    size_t count_results(const std::vector<test_suite_result>& results, 
                         result_code outcome)
    {
        size_t count = 0;
        for (auto result : results)
        {
            if (result.result == outcome)
            {
                ++count;
            }
        }
        return count;
    }

} // namespace json_benchmark

#endif

