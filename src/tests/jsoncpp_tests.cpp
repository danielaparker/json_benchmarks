#include <fstream>
#include <chrono>
#include <iostream>
#include "json/json.h"
#include <sstream>
#include <boost/filesystem.hpp>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace Json;

namespace json_benchmarks {

const std::string library_name = "[jsoncpp](https://github.com/open-source-parsers/jsoncpp)";

measurements measure_jsoncpp(const char *input_filename,
                               const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::virtual_memory_currently_used_by_current_process();

        Value root;
        {
            try
            {
                auto start = high_resolution_clock::now();
                std::ifstream is(input_filename);
                is >> root;
                //Reader reader;
                //if (!reader.parse(input_filename, root))
                //{
                //    std::cerr << "jsoncpp failed." << std::endl;
                //}
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
            char writeBuffer[65536];
            std::ofstream os; //(output_filename/*,std::ofstream::binary*/);
            os.rdbuf()->pubsetbuf(writeBuffer, sizeof(writeBuffer));
            os.open(output_filename, std::ios_base::out | std::ios_base::binary);
            auto start = high_resolution_clock::now();
            //os << root;

            StyledWriter styledWriter;
            //std::ofstream writer(filename, std::ifstream::binary);
            os << styledWriter.write(root);

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

std::vector<test_suite_result> JsonTestSuite_jsoncpp(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        if (file.type == expected_result::expect_success)
        {
            try
            {
                Value val;
                std::istringstream is(file.text);
                is >> val;
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
            catch (const std::exception&)
            {
                results.push_back(
                    test_suite_result{result_code::expected_success_parsing_failed}
                );
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            try
            {
                Value val;
                std::istringstream is(file.text);
                is >> val;
                results.push_back(
                    test_suite_result{result_code::expected_failure_parsing_succeeded}
                );
            }
            catch (const std::exception&)
            {
                results.push_back(
                    test_suite_result{result_code::expected_result}
                );
            }
        }
        else if (file.type == expected_result::result_undefined)
        {
            try
            {
                Value val;
                std::istringstream is(file.text);
                is >> val;
                results.push_back(
                    test_suite_result{result_code::result_undefined_parsing_succeeded}
                );
            }
            catch (const std::exception&)
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



