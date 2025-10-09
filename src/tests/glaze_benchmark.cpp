#include "jsoncons/config/version.hpp"
#include <glaze/glaze.hpp>
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

std::string glaze_benchmark::get_version() const {return JSONCONS_VERSION_CONCAT(NLOHMANN_JSON_VERSION_MAJOR, NLOHMANN_JSON_VERSION_MINOR, NLOHMANN_JSON_VERSION_PATCH);
}
std::string glaze_benchmark::get_name() const {return "glaze";}
std::string glaze_benchmark::get_url() const {return "https://github.com/stephenberry/glaze";}

measurements glaze_benchmark::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
    glz::json_t root;
    {
        auto start = high_resolution_clock::now();
        try
        {
            auto err = glz::read_json(root, input);
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
        auto result = glz::write_json(root, output);
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

measurements glaze_benchmark::measure_big(const char *input_filename, const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
    glz::json_t root;
    {
        auto start = high_resolution_clock::now();
        try
        {
            std::ifstream file(input_filename, std::ios::binary | std::ios::ate);
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);
            std::string buffer(size, 0);
            if (file.read(buffer.data(), size))
            {
                /* worked! */
            }
            auto err = glz::read_json(root, buffer);
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
        std::string output;
        auto err = glz::write_json(root, output);
        os.write(output.data(), output.size());
        auto end = high_resolution_clock::now();
        time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    
    measurements results;
    results.notes = R"abc()abc";
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> glaze_benchmark::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        if (file.type == expected_result::expect_success)
        {
            try
            {
                glz::json_t val;
                auto err = glz::read_json(val, file.text);
                if (err)
                {
                    results.emplace_back(result_code::expected_success_parsing_failed);
                }
                else
                {
                    results.emplace_back(result_code::expected_result);
                }
            }
            catch (const std::exception&)
            {
                results.emplace_back(result_code::expected_success_parsing_failed);
            }
        }
        else if (file.type == expected_result::expect_failure)
        {
            try
            {
                glz::json_t val;
                auto err = glz::read_json(val, file.text);
                if (err)
                {
                    results.emplace_back(result_code::expected_result);
                }
                else
                {
                    results.emplace_back(result_code::expected_failure_parsing_succeeded);
                }
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
                glz::json_t val;
                auto err = glz::read_json(val, file.text);
                if (err)
                {
                    results.emplace_back(result_code::result_undefined_parsing_failed);
                }
                else
                {
                    results.emplace_back(result_code::result_undefined_parsing_succeeded);
                }
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
