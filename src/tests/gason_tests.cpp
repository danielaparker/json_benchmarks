#include <fstream>
#include <chrono>
#include <iostream>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <boost/filesystem.hpp>
#include "gason.h"
#include "measurements.hpp"
#include "memory_measurer.hpp"
#include "library_tests.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

void dumpValue(JsonValue o, int indent = 0);

namespace json_benchmarks {

const std::string library_name = "[gason](https://github.com/vivkin/gason)";

measurements gason_benchmarks::measure(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_process_memory();

        JsonValue root;
        JsonAllocator allocator;
        std::string buffer(input.data(),input.length());
        {
            try
            {
                auto start = high_resolution_clock::now();
                char *endptr;
                int result = jsonParse(&buffer[0], &endptr, &root, allocator);
                auto end = high_resolution_clock::now();
                time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                exit(1);
            }
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            auto start = high_resolution_clock::now();
            std::ostringstream os;
            
            std::string s;
            s.resize(input.size()*4);
            freopen("/dev/null","w", stdout);
            setvbuf(stdout, &s[0],_IOFBF,s.size());

            dumpValue(root);
            output = os.str();
            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }
    size_t final_memory_used = memory_measurer::get_process_memory();
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used);
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    results.remarks = "Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code";
    return results;
}

measurements gason_benchmarks::measure(const char *input_filename,const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_process_memory();

        JsonValue root;
        JsonAllocator allocator;
        std::string buffer;
        {
            try
            {
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
                char *endptr;
                int result = jsonParse(&buffer[0], &endptr, &root, allocator);
                auto end = high_resolution_clock::now();
                time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                exit(1);
            }
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            auto start = high_resolution_clock::now();
            freopen(output_filename, "w", stdout);
            dumpValue(root);
            fclose(stdout);
            freopen("CONOUT$", "w", stdout);
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
    results.remarks = "Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code";
    return results;
}

std::vector<test_suite_result> gason_benchmarks::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        std::string text(file.text);
        JsonValue root;
        JsonAllocator allocator;
        if (file.type == expected_result::expect_success)
        {
            char *endptr;
            int status = jsonParse(&(text[0]), &endptr, &root, allocator);
            if (status == JSON_OK) 
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
            char *endptr;
            int status = jsonParse(&(text[0]), &endptr, &root, allocator);
            if (status == JSON_OK) 
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
            char *endptr;
            int status = jsonParse(&(text[0]), &endptr, &root, allocator);
            if (status == JSON_OK) 
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



