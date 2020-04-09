#include "jsoncons/json.hpp"
#include "jsoncons/json_reader.hpp"
#include <chrono>
#include <fstream>
#include <locale>
#include <codecvt>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include "json_benchmarks.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmarks;
using namespace jsoncons;

namespace json_benchmarks {

const std::string library_name = "[jsoncons](https://github.com/danielaparker/jsoncons)";

measurements jsoncons_benchmarks::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_process_memory();
        {
            jsoncons::json root;
            {
                auto start = high_resolution_clock::now();
                try
                {
                    root = jsoncons::json::parse(input.data(),input.length());
                    auto end = high_resolution_clock::now();
                    time_to_read = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
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
                root.dump(output);
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            }
        }
    }
    size_t final_memory_used = memory_measurer::get_process_memory();
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = end_memory_used > start_memory_used ? end_memory_used - start_memory_used : 0;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    results.remarks = "Uses girsu3 for printing floating-point numbers, expect faster serializing. Uses flat sorted map for objects, expect smaller memory footprint.";
    return results;
}

measurements jsoncons_benchmarks::measure_big(const char *input_filename, const char* output_filename)
{
    std::cout << "jsoncons output_filename: " << output_filename << "\n";
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_process_memory();
        {
            jsoncons::json root;
            {
                auto start = high_resolution_clock::now();
                try
                {
                    std::ifstream is(input_filename);
                    root = jsoncons::json::parse(is);
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
                std::ofstream os;
                os.open(output_filename, std::ios_base::out | std::ios_base::binary);
                auto start = high_resolution_clock::now();
                root.dump(os);
                auto end = high_resolution_clock::now();
                time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
        }
    }
    size_t final_memory_used = memory_measurer::get_process_memory();
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> jsoncons_benchmarks::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        strict_json_parsing err_handler;
        if (file.type == expected_result::expect_success)
        {
            if (file.path.filename().string().find("utf16") != std::string::npos)
            {
                try
                {
                    std::wifstream fin(file.path.string().c_str(), std::ios::binary);
                    // apply BOM-sensitive UTF-16 facet
                    fin.imbue(std::locale(fin.getloc(),
                                          new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
                    wjson document;
                    fin >> document;
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
            else
            {
                try
                {
                    std::istringstream is(file.text);
                    json val = json::parse(is,err_handler);
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
        }
        else if (file.type == expected_result::expect_failure)
        {
            try
            {
                std::istringstream is(file.text);
                json val = json::parse(is,err_handler);
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
                std::istringstream is(file.text);
                json val = json::parse(is,err_handler);
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
