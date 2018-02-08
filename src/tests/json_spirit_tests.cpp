#include "json_spirit/json_spirit_reader_template.h"
#include "json_spirit/json_spirit_writer_template.h"
#include <chrono>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include <fstream>
#include "library_tests.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace json_spirit;

#ifndef JSON_SPIRIT_VALUE_ENABLED
#define JSON_SPIRIT_VALUE_ENABLED
#endif

namespace json_benchmarks {

const std::string library_name = "[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)";

measurements json_spirit_benchmarks::measure(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_process_memory();

        Value root;
        {
            {
                auto start = high_resolution_clock::now();
                try
                {
                    read_string(input, root);
                    auto end = high_resolution_clock::now();
                    time_to_read = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                }
                catch (const std::exception & e)
                {
                    std::cout << e.what() << std::endl;
                    exit(1);
                }
            }
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            auto start = high_resolution_clock::now();
            std::ostringstream os;
            write_stream(root,os);
            output = os.str();
            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
    }
    size_t final_memory_used = memory_measurer::get_process_memory();

    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used);
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    results.remarks = "Boost spirit parsing is slow";
    return results;
}

measurements json_spirit_benchmarks::measure(const char *input_filename,const char *output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_process_memory();

        Value root;
        {
            {
                auto start = high_resolution_clock::now();
                try
                {
                    std::ifstream is(input_filename);
                    read_stream(is, root);
                    auto end = high_resolution_clock::now();
                    time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                }
                catch (const std::exception & e)
                {
                    std::cout << e.what() << std::endl;
                    exit(1);
                }
            }
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            std::ofstream os;
            os.open(output_filename, std::ios_base::out | std::ios_base::binary);
            auto start = high_resolution_clock::now();
            write_stream(root,os);
            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }
    size_t final_memory_used = memory_measurer::get_process_memory();

    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    results.remarks = "Boost spirit parsing is slow";
    return results;
}

std::vector<test_suite_result> json_spirit_benchmarks::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        std::string command = "build\\vs2015\\x64\\Release\\json_spirit_parser.exe ";
        command = command + file.path.string();
        int result = std::system(command.c_str());

        if (file.type == expected_result::expect_success)
        {
            if (result == 0)
            {
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
            else if (result == 1)
            {
                results.push_back(
                    test_suite_result{result_code::expected_success_parsing_failed}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::process_stopped}
                );
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            if (result == 0)
            {
                results.push_back(
                    test_suite_result{result_code::expected_failure_parsing_succeeded}
                );
            }
            else if (result == 1)
            {
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::process_stopped}
                );
            }
        }
        else if (file.type == expected_result::result_undefined)
        {
            if (result == 0)
            {
                results.push_back(
                    test_suite_result{result_code::result_undefined_parsing_succeeded}
                );
            }
            else if (result == 1)
            {
                results.push_back(
                    test_suite_result{result_code::result_undefined_parsing_failed}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::process_stopped}
                );
            }
        }
    }

    return results;
}

}
