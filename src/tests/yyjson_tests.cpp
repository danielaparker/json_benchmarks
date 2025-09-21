#include "yyjson.h"
#include <chrono>
#include <fstream>
#include <locale>
#include <codecvt>
#include "measurements.hpp"
#include "memory_measurer.hpp"
#include "benchmark.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

namespace json_benchmark {

std::string yyjson_benchmark::get_version() const {return YYJSON_VERSION_STRING;}
std::string yyjson_benchmark::get_name() const {return "yyjson"; }
std::string yyjson_benchmark::get_url() const {return "https://github.com/ibireme/yyjson";}

measurements yyjson_benchmark::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used = 0;
    size_t end_memory_used = 0;
    size_t time_to_read = 0;
    size_t time_to_write = 0;

    {
        start_memory_used =  memory_measurer::get_physical_memory_use();
        {
            yyjson_doc *doc;
            {
                auto start = high_resolution_clock::now();
                doc = yyjson_read(input.data(), input.length(), 0);
                if (!doc)
                {
                    std::cout << "yyjson parse failed" << std::endl;
                    exit(1);
                }
                auto end = high_resolution_clock::now();
                time_to_read = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            }
            
            end_memory_used =  memory_measurer::get_physical_memory_use();
            {
                auto start = high_resolution_clock::now();
                yyjson_write_flag flg = 0;
                yyjson_write_err err;
                std::cout << "write yyjson " << output.c_str() << "\n";
                std::size_t len{0};
                char* ptr = yyjson_write(doc, flg, &len);
                if (err.code) {
                    printf("write error (%u): %s\n", err.code, err.msg);
                }
                output = std::string(ptr, len);
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            }
            if (doc)
            {
                yyjson_doc_free(doc);
            }
        }
    }
    size_t final_memory_used = memory_measurer::get_physical_memory_use();
    
    measurements results;
    results.notes = "";
    results.memory_used = end_memory_used > start_memory_used ? end_memory_used - start_memory_used : 0;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

measurements yyjson_benchmark::measure_big(const char *input_filename, const char* output_filename)
{
    std::cout << "yyjson output_filename: " << output_filename << "\n";
    size_t start_memory_used = 0;
    size_t end_memory_used = 0;
    size_t time_to_read = 0;
    size_t time_to_write = 0;

    {
        start_memory_used =  memory_measurer::get_physical_memory_use();
        {
            yyjson_doc *doc;
            {
                auto start = high_resolution_clock::now();
                doc = yyjson_read_file(input_filename, 0, nullptr, nullptr);
                if (!doc)
                {
                    std::cout << "yyjson parse failed" << std::endl;
                    exit(1);
                }
            }
            end_memory_used =  memory_measurer::get_physical_memory_use();
            {
                auto start = high_resolution_clock::now();
                yyjson_write_flag flg = 0;
                yyjson_write_err err;
                yyjson_write_file(output_filename, doc, flg, NULL, &err);
                if (err.code) {
                    printf("write error (%u): %s\n", err.code, err.msg);
                }
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
            if (doc)
            {
                yyjson_doc_free(doc);
            }
        }
    }
    size_t final_memory_used = memory_measurer::get_physical_memory_use();
    
    measurements results;
    results.notes = "";
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> yyjson_benchmark::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        if (file.type == expected_result::expect_success)
        {
            if (file.path.filename().string().find("utf16") != std::string::npos)
            {
                results.emplace_back(result_code::expected_success_parsing_failed);
            }
            else
            {
                auto* doc = yyjson_read(file.text.data(), file.text.length(), 0);
                if (doc)
                {
                    results.emplace_back(result_code::expected_result);
                }
                else
                {
                    results.emplace_back(result_code::expected_success_parsing_failed);
                }
                if (doc)
                {
                    yyjson_doc_free(doc);
                }
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            auto* doc = yyjson_read(file.text.data(), file.text.length(), 0);
            if (doc)
            {
                results.emplace_back(result_code::expected_failure_parsing_succeeded);
            }
            else
            {
                results.emplace_back(result_code::expected_result);
            }
            if (doc)
            {
                yyjson_doc_free(doc);
            }
        }
        else if (file.type == expected_result::result_undefined)
        {
            auto* doc = yyjson_read(file.text.data(), file.text.length(), 0);
            if (doc)
            {
                results.emplace_back(result_code::result_undefined_parsing_succeeded);
            }
            else
            {
                results.emplace_back(result_code::result_undefined_parsing_failed);
            }
            if (doc)
            {
                yyjson_doc_free(doc);
            }
        }
    }

    return results;
}

}
