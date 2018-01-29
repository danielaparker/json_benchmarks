#include <fstream>gason
#include <chrono>
#include <iostream>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include "cjson/cJSON.h"
#include "measurements.hpp"
#include "memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

namespace json_benchmarks {

const std::string library_name = "[cjson](https://github.com/DaveGamble/cJSON)";

measurements measure_cjson(const char *input_filename,
                           const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();

        cJSON* root = nullptr;
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
                root = cJSON_Parse(buffer.c_str());
                auto end = high_resolution_clock::now();
                time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                exit(1);
            }
        }
        end_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();
        {
            auto start = high_resolution_clock::now();
            //FILE *fp = fopen(output_filename, "w");
            //if (!fp) {
            //    perror(output_filename);
            //    exit(EXIT_FAILURE);
            //}
            char* s = cJSON_Print(root);
            std::ofstream os; //(output_filename/*,std::ofstream::binary*/);
                              //os.rdbuf()->pubsetbuf(writeBuffer, sizeof(writeBuffer));
            os.open(output_filename, std::ios_base::out | std::ios_base::binary);
            os.write(s,std::strlen(s));
            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
        free(root);
    }
    size_t final_memory_used = memory_measurer::virtual_memory_currently_used_by_current_process();
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    results.remarks = "";
    return results;
}

std::vector<test_suite_result> JsonTestSuite_cjson(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        std::string text(file.text);
        if (file.type == expected_result::expect_success)
        {
            cJSON* j = cJSON_Parse(text.c_str());
            if (j != nullptr) 
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
            cJSON* j = cJSON_Parse(text.c_str());
            if (j != nullptr) 
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
            cJSON* j = cJSON_Parse(text.c_str());
            if (j != nullptr) 
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



