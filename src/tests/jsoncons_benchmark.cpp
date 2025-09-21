#include "jsoncons/json.hpp"
#include "jsoncons/json_reader.hpp"
#include <chrono>
#include <fstream>
#include <locale>
#include <codecvt>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include "benchmark.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmark;
using namespace jsoncons;

namespace json_benchmark {

std::string jsoncons_benchmark::get_version() const {return JSONCONS_VERSION;}
std::string jsoncons_benchmark::get_name() const {return "jsoncons";}
std::string jsoncons_benchmark::get_url() const {return "https://github.com/danielaparker/jsoncons";}

measurements jsoncons_benchmark::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
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
    end_memory_used =  memory_measurer::get_physical_memory_use();
    {
        auto start = high_resolution_clock::now();
        root.dump(output);
        auto end = high_resolution_clock::now();
        time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }   
    
    measurements results;
    results.notes = R"abc(Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.)abc";
    results.memory_used = end_memory_used > start_memory_used ? end_memory_used - start_memory_used : 0;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

measurements jsoncons_benchmark::measure_big(const char *input_filename, const char* output_filename)
{
    std::cout << "jsoncons output_filename: " << output_filename << "\n";
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
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
    end_memory_used =  memory_measurer::get_physical_memory_use();
    {
        std::ofstream os;
        os.open(output_filename, std::ios_base::out | std::ios_base::binary);
        auto start = high_resolution_clock::now();
        root.dump(os);
        auto end = high_resolution_clock::now();
        time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    
    measurements results;
    results.notes = R"abc(Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.)abc";
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> jsoncons_benchmark::run_test_suite(std::vector<test_suite_file>& pathnames)
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
                    results.emplace_back(result_code::expected_result);
                }
                catch (const std::exception&)
                {
                    results.emplace_back(result_code::expected_success_parsing_failed);
                }
            }
            else
            {
                try
                {
                    std::istringstream is(file.text);
                    json val = json::parse(is,err_handler);
                    results.emplace_back(result_code::expected_result);
                }
                catch (const std::exception&)
                {
                    results.emplace_back(result_code::expected_success_parsing_failed);
                }
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            try
            {
                std::istringstream is(file.text);
                json val = json::parse(is,err_handler);
                results.emplace_back(result_code::expected_failure_parsing_succeeded);
            }
            catch (const std::exception&)
            {
                results.emplace_back(result_code::expected_result);
            }
        }
        else if (file.type == expected_result::result_undefined)
        {
            try
            {
                std::istringstream is(file.text);
                json val = json::parse(is,err_handler);
                results.emplace_back(result_code::result_undefined_parsing_succeeded);
            }
            catch (const std::exception&)
            {
                results.emplace_back(result_code::result_undefined_parsing_failed);
            }
        }
    }

    return results;
}

}
