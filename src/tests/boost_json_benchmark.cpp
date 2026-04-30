#include <boost/json.hpp>
#include <boost/version.hpp>
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

namespace json_benchmark {

std::string boost_json_benchmark::get_version() const {return BOOST_LIB_VERSION;}
std::string boost_json_benchmark::get_name() const {return "Boost.JSON";}
std::string boost_json_benchmark::get_url() const {return "https://www.boost.org/doc/libs/latest/libs/json/doc/html/index.html";}
std::string boost_json_benchmark::get_type() const {return "boost::json::value";}

measurements boost_json_benchmark::measure_small(const std::string& input, std::string& output)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
    boost::json::value jv;
    {
        auto start = high_resolution_clock::now();
        try
        {
            jv = boost::json::parse(input);
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
        boost::json::serializer sr;
        output = serialize(jv);
        auto end = high_resolution_clock::now();
        time_to_write = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }   
    
    measurements results;
    results.notes = "";
    results.memory_used = end_memory_used > start_memory_used ? end_memory_used - start_memory_used : 0;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

measurements boost_json_benchmark::measure_big(const char *input_filename, const char* output_filename)
{
    size_t start_memory_used;
    size_t end_memory_used;
    size_t time_to_read;
    size_t time_to_write;

    start_memory_used =  memory_measurer::get_physical_memory_use();
    boost::json::value jv;
    {
        auto start = high_resolution_clock::now();
        try
        {
            std::ifstream is(input_filename);
            jv = boost::json::parse(is);
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
        boost::json::serializer sr;
        sr.reset(&jv);
        while(!sr.done())
        {
            char buf[10000];
            os << sr.read( buf );
        }        
        auto end = high_resolution_clock::now();
        time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    
    measurements results;
    results.notes = "";
    results.memory_used = (end_memory_used - start_memory_used)/1000000;
    results.time_to_read = time_to_read;
    results.time_to_write = time_to_write;
    return results;
}

std::vector<test_suite_result> boost_json_benchmark::run_test_suite(std::vector<test_suite_file>& pathnames)
{
    std::vector<test_suite_result> results;
    for (auto& file : pathnames)
    {
        if (file.type == expected_result::expect_success)
        {
            try
            {
                std::istringstream is(file.text);
                boost::json::value jv = boost::json::parse(is);
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
                std::istringstream is(file.text);
                boost::json::value jv = boost::json::parse(is);
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
                boost::json::value jv = boost::json::parse(is);
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
