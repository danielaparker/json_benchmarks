#include <fstream>
#include <chrono>
#include <iostream>
#include "json11.hpp"
#include <sstream>
#include <stdio.h>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include "library_tests.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace json11;

namespace json_benchmarks {

const std::string library_name = "[json11](https://github.com/dropbox/json11)";

measurements json11_benchmarks::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;
    std::string buffer;

    {
        start_memory_used =  memory_measurer::get_process_memory();

        Json val;
        {
            std::string err;
            auto start = high_resolution_clock::now();
            val = Json::parse(input,err);
            if (err.length() > 0)
            {
                std::cout << err << std::endl;
                exit(1);
            }

            auto end = high_resolution_clock::now();
            time_to_read = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            auto start = high_resolution_clock::now();

            val.dump(output);

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
    results.remarks = "Uses pimpl idiom, implementation uses virtual inheritance, expect larger memory footprint.";
    return results;
}

measurements json11_benchmarks::measure_big(const char *input_filename, const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;
    std::string buffer;

    {
        start_memory_used =  memory_measurer::get_process_memory();

        Json val;
        {
            std::string err;
            auto start = high_resolution_clock::now();
            FILE *fp = fopen(input_filename, "r");
            if (!fp) {
                perror(input_filename);
                exit(EXIT_FAILURE);
            }
            fseek(fp, 0, SEEK_END);
            size_t size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            buffer.resize(size);
            fread(&buffer[0], 1, size, fp);
            fclose(fp);
            val = Json::parse(buffer,err);
            if (err.length() > 0)
            {
                std::cout << err << std::endl;
                exit(1);
            }

            auto end = high_resolution_clock::now();
            time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            auto start = high_resolution_clock::now();

            std::string s;
            val.dump(s);
            std::ofstream os;
            os.open(output_filename, std::ios_base::out | std::ios_base::binary);
            os << s;

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
    results.remarks = "Uses pimpl idiom, implementation uses virtual inheritance";
    return results;
}

std::vector<test_suite_result> json11_benchmarks::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        if (file.type == expected_result::expect_success)
        {
            std::string err;
            Json val = Json::parse(file.text,err);
            
            if (err.length() == 0)
            {
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::expected_success_parsing_failed}
                );
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            std::string err;
            Json val = Json::parse(file.text,err);
            if (err.length() == 0)
            {
                results.push_back(
                    test_suite_result{result_code::expected_failure_parsing_succeeded}
                );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
        }
        else if (file.type == expected_result::result_undefined)
        {
            std::string err;
            Json val = Json::parse(file.text,err);
            if (err.length() == 0)
            {
                    results.push_back(
                        test_suite_result{result_code::result_undefined_parsing_succeeded}
                    );
            }
            else
            {
                results.push_back(
                    test_suite_result{result_code::result_undefined_parsing_failed}
                );
            }
        }
    }

    return results;
}
}



