#include <fstream>
#include <chrono>
#include <iostream>
#include "json11/json11.hpp"
#include <sstream>
#include <boost/filesystem.hpp>
#include <stdio.h>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace json11;

namespace json_benchmarks {

const std::string library_name = "[json11](https://github.com/dropbox/json11)";

measurements measure_json11(const char *input_filename,
                            const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;
    std::string buffer;

    {
        start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();

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
        end_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();
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
    size_t final_memory_used = memory_measurer::virtual_memory_currently_used_by_current_process();
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> JsonTestSuite_json11(std::vector<test_suite_file>& pathnames)
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



