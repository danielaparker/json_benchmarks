#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <cstdio>
#include <chrono>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include "library_tests.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

using namespace json_benchmarks;
using namespace rapidjson;

namespace json_benchmarks {

const std::string library_name = "[rapidjson](https://github.com/miloyip/rapidjson)";

measurements rapidjson_benchmarks::measure(const std::string& input, std::string& output)
{
    size_t start_memory_used = 0;
    size_t end_memory_used = 0;
    size_t time_to_read = 0;
    size_t time_to_write = 0;

    start_memory_used =  memory_measurer::get_process_memory();
    {
        Document d;
        try
        {
            auto start = high_resolution_clock::now();
            d.Parse(input.c_str());
            auto end = high_resolution_clock::now();
            time_to_read = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            exit(1);
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            try
            {
                auto start = high_resolution_clock::now();
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                d.Accept(writer);
                output = buffer.GetString();
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    size_t final_memory_used = memory_measurer::get_process_memory();
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used);
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

measurements rapidjson_benchmarks::measure(const char *input_filename, const char* output_filename)
{
    size_t start_memory_used = 0;
    size_t end_memory_used = 0;
    size_t time_to_read = 0;
    size_t time_to_write = 0;

    start_memory_used =  memory_measurer::get_process_memory();
    {
        Document d;
        try
        {
            auto start = high_resolution_clock::now();
            FILE* fp = fopen(input_filename, "rb"); // non-Windows use "r"
            std::vector<char> readBuffer; 
            readBuffer.resize(65536);
            FileReadStream is(fp, readBuffer.data(), readBuffer.size());
            d.ParseStream(is);
            auto end = high_resolution_clock::now();
            time_to_read = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            fclose(fp);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            exit(1);
        }
        end_memory_used =  memory_measurer::get_process_memory();
        {
            try
            {
                FILE* fp = fopen(output_filename, "wb"); // non-Windows use "w"
                assert(fp != nullptr);

                std::vector<char> writeBuffer;
                writeBuffer.resize(65536);
                FileWriteStream os(fp, &writeBuffer[0], writeBuffer.size());

                Writer<FileWriteStream> writer(os);
                auto start = high_resolution_clock::now();
                d.Accept(writer);
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                fclose(fp);        
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    size_t final_memory_used = memory_measurer::get_process_memory();
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    results.remarks = "Uses custom floating point parsing and girsu3 for printing floating-point numbers, expect faster parsing and serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.";
    return results;
}

void print(FILE* fp, const Value& val)
{
    char buffer[1000];
    FileWriteStream fws(fp, buffer, sizeof(buffer));
    Writer<FileWriteStream> writer(fws);
    val.Accept(writer);
    fws.Flush();
}

std::vector<test_suite_result> rapidjson_benchmarks::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        Document d;
        std::string command = "x64\\Release\\rapidjson_parser.exe ";
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
