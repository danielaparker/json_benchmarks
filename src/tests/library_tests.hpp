#ifndef JSON_BENCHMARKS_LIBRARY_TESTS_HPP
#define JSON_BENCHMARKS_LIBRARY_TESTS_HPP

#include "measurements.hpp"
#include <vector>

namespace json_benchmarks {

    class library_tests
    {
    public:
        static std::vector<library_info> get_library_info();

        std::vector<measurements> measure(const std::string& input, std::string& output);

        std::vector<measurements> measure(const char *input_filename, const char *output_dir);

        std::vector<std::vector<test_suite_result>> run_test_suite(std::vector<test_suite_file>& pathnames) const;
    };
}

#endif

