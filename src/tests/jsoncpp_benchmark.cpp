#include <fstream>
#include <chrono>
#include <iostream>
#include "json/json.h"
#include <sstream>
#include "../measurements.hpp"
#include "../memory_measurer.hpp"
#include "benchmark.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace json_benchmark;
using namespace Json;

namespace json_benchmark {

const std::string library_name = "[jsoncpp](https://github.com/open-source-parsers/jsoncpp)";

std::string jsoncpp_benchmark::version()
{
    return JSONCPP_VERSION_STRING;
}

std::string jsoncpp_benchmark::name()
{
    return "jsoncpp";
}

std::string jsoncpp_benchmark::url()
{
    return "https://github.com/open-source-parsers/jsoncpp";
}

std::string jsoncpp_benchmark::notes()
{
    return "Uses map for both arrays and objects";
}

std::string jsoncpp_benchmark::get_version() const {return jsoncpp_benchmark::version();}
std::string jsoncpp_benchmark::get_name() const {return jsoncpp_benchmark::name();}
std::string jsoncpp_benchmark::get_url() const {return jsoncpp_benchmark::url();}
std::string jsoncpp_benchmark::get_notes() const {return jsoncpp_benchmark::notes();}

measurements jsoncpp_benchmark::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_physical_memory_use();

        Value root;
        {
            try
            {
                auto start = high_resolution_clock::now();
                Reader reader;
                if (!reader.parse(input, root))
                {
                    std::cerr << "jsoncpp failed." << std::endl;
                }
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
            std::stringstream os;
            auto start = high_resolution_clock::now();


            Json::StreamWriterBuilder builder;
            builder.settings_["indentation"] = "";
            std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
            writer->write(root, &os);

            output = os.str();

            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
    }
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used);
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

measurements jsoncpp_benchmark::measure_big(const char *input_filename, const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    {
        start_memory_used =  memory_measurer::get_physical_memory_use();

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
        end_memory_used =  memory_measurer::get_physical_memory_use();
        {
            std::ofstream os;
            os.open(output_filename, std::ios_base::out | std::ios_base::binary);
            auto start = high_resolution_clock::now();

            Json::StreamWriterBuilder builder;
            builder.settings_["indentation"] = "";
            std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
            writer->write(root, &os);

            auto end = high_resolution_clock::now();
            time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }
    
    measurements results;
    results.library_name = library_name;
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

const std::string& jsoncpp_benchmark::remarks() const 
{
    static const std::string s = R"abc(Uses std::map for both arrays and objects, expect larger memory footprint.)abc";

    return s;
}

std::vector<test_suite_result> jsoncpp_benchmark::run_test_suite(std::vector<test_suite_file>& pathnames)
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
                results.emplace_back(result_code::expected_result);
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
                Value val;
                std::istringstream is(file.text);
                is >> val;
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
                Value val;
                std::istringstream is(file.text);
                is >> val;
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



