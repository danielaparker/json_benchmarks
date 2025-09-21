#include <assert.h>
#include <fstream>
#include <chrono>
#include "jsoncons/config/version.hpp"
#include "nlohmann/json.hpp"
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include "benchmark.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmark;
using namespace nlohmann;

namespace json_benchmark {

std::string nlohmann_benchmark::get_version() const {return JSONCONS_VERSION_CONCAT(NLOHMANN_JSON_VERSION_MAJOR,NLOHMANN_JSON_VERSION_MINOR,NLOHMANN_JSON_VERSION_PATCH);}
std::string nlohmann_benchmark::get_name() const {return "nlohmann";}
std::string nlohmann_benchmark::get_url() const {return "https://github.com/nlohmann/json";}

measurements nlohmann_benchmark::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
    nlohmann::json root;
    {
        auto start = high_resolution_clock::now();
        try
        {
            root = nlohmann::json::parse(input);
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
        output = root.dump();
        auto end = high_resolution_clock::now();
        time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    
    measurements results;
    results.notes = R"abc(Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.)abc";
    results.memory_used = (end_memory_used - start_memory_used);
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

measurements nlohmann_benchmark::measure_big(const char *input_filename, const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
    nlohmann::json root;
    {
        auto start = high_resolution_clock::now();
        try
        {
            std::ifstream is(input_filename);
            root = nlohmann::json::parse(is);
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
        os << root;
        auto end = high_resolution_clock::now();
        time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    
    measurements results;
    results.notes = R"abc(Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.)abc";
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> nlohmann_benchmark::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        std::string command = "x64\\Release\\nlohmann_parser.exe ";
        command = command + file.path.string();
        int result = std::system(command.c_str());
        if (file.type == expected_result::expect_success)
        {
            if (result == 0)
            {
                results.emplace_back(result_code::expected_result);
            }
            else if (result == 1)
            {
                results.emplace_back(result_code::expected_success_parsing_failed);
            }
            else
            {
                results.emplace_back(result_code::process_stopped);
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            if (result == 0)
            {
                results.emplace_back(result_code::expected_failure_parsing_succeeded);
            }
            else if (result == 1)
            {
                results.emplace_back(result_code::expected_result);
            }
            else
            {
                results.emplace_back(result_code::process_stopped);
            }
        }
        else if (file.type == expected_result::result_undefined)
        {
            if (result == 0)
            {
                results.emplace_back(result_code::result_undefined_parsing_succeeded);
            }
            else if (result == 1)
            {
                results.emplace_back(result_code::result_undefined_parsing_failed);
            }
            else
            {
                results.emplace_back(result_code::process_stopped);
            }
        }
    }
    
    return results;
}
}
