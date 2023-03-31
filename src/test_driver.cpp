#include "tests/json_benchmarks.hpp"
#include <iostream>
#include <fstream>
#include "measurements.hpp"
#include <string>
#include "json_parsing_test_reporter.hpp"
#include "data_generator.hpp"
#include "jsoncons/json.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace json_benchmarks;

void benchmarks_small_file(std::vector<json_implementation>& implementations)
{
    try
    {
        const char *filename = "data/input/small_file/small_file_text_array.json";

        size_t file_size;
        {
            std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
            file_size = in.tellg(); 
        }
        std::string input;
        input.resize(file_size);
        std::string output;
        {
            std::ifstream in(filename, std::ifstream::binary);
            in.read(&input[0], file_size);
            //input[file_size] = 0;
            //jsoncons::json j = jsoncons::json::parse(in);
            //j.dump(input);
            //std::cout << input << std::endl;
        }
        //std::cout << input << std::endl;
        output.reserve(input.size()*2);

        std::ofstream os("report/performance_small_file_text_array.md");
        os << std::endl;
        os << "## Read and Write Time Comparison" << std::endl << std::endl;
        os << std::endl;
        os << "Input filename|Size (bytes)|Content" << std::endl;
        os << "---|---|---" << std::endl;
        os << filename << "|" << file_size << "|" << "Text,integers" << std::endl;
        os << std::endl;
        os << "Environment"
           << "|" << "Windows, Intel" << std::endl;
        os << "---|---" << std::endl;
        os << "Computer"
           << "|" << "Lenovo Thinkpad X Extreme with 8 cores, 16 hardware threads, 32 GB memory, 2 TB solid state drive" << std::endl;
        os << "Operating system"
           << "|" << "Windows 2011" << std::endl;
        os << "Compiler"
           << "|" << "Visual Studio 2022" << std::endl;

        os << std::endl;

        os << "Library|Version" << std::endl;
        os << "---|---" << std::endl;
        for (const auto& val : implementations)
        {
            os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
        }
        os << std::endl;

        os << "Library|Time to read (milliseconds)|Time to write (milliseconds)|Memory footprint of json value (bytes)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        std::vector<measurements> v(implementations.size());

        size_t number_times = 50000;
        for (size_t i = 0; i < number_times; ++i)
        {
            for (size_t j = 0; j < implementations.size(); ++j)
            {
                auto results = implementations[j].measures->measure_small(input,output);
                v[j].time_to_read += results.time_to_read;
                v[j].time_to_write += results.time_to_write;
                v[j].memory_used += results.memory_used;
            }
            output.clear();
        }
        for (size_t j = 0; j < implementations.size(); ++j)
        {
            os << v[j].library_name
               << "|" << v[j].time_to_read/(number_times)
               << "|" << v[j].time_to_write/(number_times)
               << "|" << v[j].memory_used/number_times
               << "|" << implementations[j].measures->remarks()
               << std::endl; 
        }
        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void benchmarks_int(std::vector<json_implementation>& implementations)
{
    try
    {
        const char *filename = "data/output/persons.json";
        make_big_file(filename, 50000, 5000, 0, 0);

        size_t file_size;
        {
                std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
                file_size = in.tellg(); 
        }

        std::ofstream os("report/performance.md");
        os << std::endl;
        os << "## Read and Write Time Comparison" << std::endl << std::endl;
        os << std::endl;
        os << "Input filename|Size (MB)|Content" << std::endl;
        os << "---|---|---" << std::endl;
        os << filename << "|" << (file_size/1000000.0) << "|" << "Text,integers" << std::endl;
        os << std::endl;
        os << "Environment"
           << "|" << "Windows, Intel" << std::endl;
        os << "---|---" << std::endl;
        os << "Computer"
           << "|" << "Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD" << std::endl;
        os << "Operating system"
           << "|" << "Windows 2010" << std::endl;
        os << "Compiler"
           << "|" << "Visual Studio 2019" << std::endl;

        os << std::endl;

        os << "Library|Version" << std::endl;
        os << "---|---" << std::endl;

        for (const auto& val : implementations)
        {
            os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
        }
        os << std::endl;

        os << "Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        for (size_t j = 0; j < implementations.size(); ++j)
        {
            auto& impl = implementations[j];
            std::string output_path = "data/output/persons_" + impl.name + ".json";
            auto results = impl.measures->measure_big("data/output/persons.json",output_path.c_str());
            os << "[" << impl.name << "](" << impl.url << ")"
               << "|" << (results.time_to_read/1000.0) 
               << "|" << (results.time_to_write/1000.0) 
               << "|" << (results.memory_used)
               << "|" << impl.measures->remarks()
               << std::endl; 
        }

        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void benchmarks_fp(std::vector<json_implementation>& implementations)
{
    try
    {
        const char *filename = "data/output/persons_fp.json";
        make_big_file(filename, 50000, 0, 2500, 0);

        size_t file_size;
        {
                std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
                file_size = in.tellg(); 
        }
 
        std::ofstream os("report/performance_fp.md");
        os << std::endl;
        os << "## Read and Write Time Comparison" << std::endl << std::endl;
        os << std::endl;
        os << "Input filename|Size (MB)|Content" << std::endl;
        os << "---|---|---" << std::endl;
        os << filename << "|" << (file_size/1000000.0) << "|" << "Text,doubles" << std::endl;
        os << std::endl;
        os << "Environment"
           << "|" << "Windows, Intel" << std::endl;
        os << "---|---" << std::endl;
        os << "Computer"
           << "|" << "Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD" << std::endl;
        os << "Operating system"
           << "|" << "Windows 2010" << std::endl;
        os << "Compiler"
           << "|" << "Visual Studio 2019" << std::endl;

        os << std::endl;

        os << "Library|Version" << std::endl;
        os << "---|---" << std::endl;
        for (const auto& val : implementations)
        {
            os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
        }
        os << std::endl;

        os << "Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        for (size_t j = 0; j < implementations.size(); ++j)
        {
            auto& impl = implementations[j];
            std::string output_path = "data/output_fp/persons_" + impl.name + ".json";
            auto results = impl.measures->measure_big("data/output/persons_fp.json",output_path.c_str());
            os << "[" << impl.name << "](" << impl.url << ")"
               << "|" << (results.time_to_read/1000.0) 
               << "|" << (results.time_to_write/1000.0) 
               << "|" << (results.memory_used)
               << "|" << impl.measures->remarks()
               << std::endl; 
        }

        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void json_test_suite_parsing_tests(const std::vector<json_implementation>& implementations,
                                  json_parsing_test_visitor& visitor)
{
    try
    {
        std::vector<test_suite_file> pathnames;

        json_file_finder
        (
            "data/input/JSONTestSuite/test_parsing",
            [&](const fs::path& path) 
            {
                std::string buffer;
                {
                    std::ifstream fs(path.string(), std::ios::in|std::ios::binary|std::ios::ate);
                    if (fs.is_open())
                    {
                        size_t size = fs.tellg();
                        buffer.resize(size);
                        fs.seekg (0, std::ios::beg);
                        fs.read (&buffer[0], size);
                    }
                }
                char type = path.filename().string().c_str()[0];
                switch (type)
                {
                case 'y':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_success,buffer});
                    break;
                case 'n':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_failure,buffer});
                    break;
                case 'i':
                    pathnames.push_back(test_suite_file{path,expected_result::result_undefined,buffer});
                    break;
                }
            }
        );

        std::stable_sort(pathnames.begin(),pathnames.end(),
                         [](const test_suite_file& a, const test_suite_file& b) -> bool
        {
            return a.type < b.type; 
        }
        );

        std::vector<std::vector<test_suite_result>> results;
        for (auto& impl : implementations)
        {
            results.emplace_back(impl.measures->run_test_suite(pathnames));
        }

        visitor.visit(pathnames,results);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void json_checker_parsing_tests(const std::vector<json_implementation>& implementations,
                                json_parsing_test_visitor& visitor)
{
    try
    {
        std::vector<test_suite_file> pathnames;

        json_file_finder
        (
            "data/input/JSON_checker",
            [&](const fs::path& path) 
            {
                std::string buffer;
                {
                    std::ifstream fs(path.string(), std::ios::in|std::ios::binary|std::ios::ate);
                    if (fs.is_open())
                    {
                        size_t size = fs.tellg();
                        buffer.resize(size);
                        fs.seekg (0, std::ios::beg);
                        fs.read (&buffer[0], size);
                    }
                }
                char type = path.filename().string().c_str()[0];
                switch (type)
                {
                case 'p':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_success,buffer});
                    break;
                case 'f':
                    pathnames.push_back(test_suite_file{path,expected_result::expect_failure,buffer});
                    break;
                case 'i':
                    pathnames.push_back(test_suite_file{path,expected_result::result_undefined,buffer});
                    break;
                }
            }
        );

        std::stable_sort(pathnames.begin(),pathnames.end(),
                         [](const test_suite_file& a, const test_suite_file& b)
        {
            return a.type < b.type; 
        }
        );

        std::vector<std::vector<test_suite_result>> results;
        for (auto& impl : implementations)
        {
            results.emplace_back(impl.measures->run_test_suite(pathnames));
        }

        visitor.visit(pathnames,results);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    std::vector<json_implementation> implementations; 

    implementations.emplace_back("jsoncons",
                                 "https://github.com/danielaparker/jsoncons",
                                 "0.170.0", 
                                 "With strict_json_parsing, uses wjson if utf16" ,
                                  std::make_shared<jsoncons_benchmarks>());
    implementations.emplace_back("nlohmann",
                                 "https://github.com/nlohmann/json",
                                 "3.11.2", 
                                 "",
                                 std::make_shared<nlohmann_benchmarks>());
    implementations.emplace_back("cJSON",
                                 "https://github.com/DaveGamble/cJSON",
                                 "1.7.15", 
                                 "",
                                 std::make_shared<cjson_benchmarks>());
    implementations.emplace_back("json11",
                                 "https://github.com/dropbox/json11",
                                 "2017-06-20-2", 
                                 "",
                                 std::make_shared<json11_benchmarks>());
    implementations.emplace_back("rapidjson",
                                 "https://github.com/miloyip/rapidjson",
                                 "2020-02-08", 
                                 "Uses custom (non standard lib) floating point conversion",
                                 std::make_shared<rapidjson_benchmarks>());
    implementations.emplace_back("jsoncpp",
                                 "https://github.com/open-source-parsers/jsoncpp",
                                 "1.9.5", 
                                 "Uses map for both arrays and objects",
                                 std::make_shared<jsoncpp_benchmarks>());
    implementations.emplace_back("json_spirit",
                                 "http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented",
                                 "4.1.0-1", 
                                 "",
                                 std::make_shared<json_spirit_benchmarks>());
    implementations.emplace_back("taojson",
                                 "https://github.com/taocpp/json",
                                 "2020-09-14", 
                                 "",
                                 std::make_shared<taojson_benchmarks>());

    benchmarks_int(implementations);
    //benchmarks_fp(implementations);
    //benchmarks_small_file(implementations);

    /*std::vector<result_code_info> result_code_infos;
    result_code_infos.push_back(result_code_info{result_code::expected_result,"Expected result","#008000"});
    result_code_infos.push_back(result_code_info{result_code::expected_success_parsing_failed,"Expected success, parsing failed","#d19b73"});
    result_code_infos.push_back(result_code_info{result_code::expected_failure_parsing_succeeded,"Expected failure, parsing succeeded","#001a75"});
    result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_succeeded,"Result undefined, parsing succeeded","#f7a8ff"});
    result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_failed,"Result undefined, parsing failed","#050f07"});
    result_code_infos.push_back(result_code_info{result_code::process_stopped,"Process stopped","#e00053"});

    std::ofstream fs("docs/index.html");
    json_parsing_test_reporter reporter("Parser Comparisons", implementations, result_code_infos, fs);
    reporter.register_test("JSON Test Suite",json_test_suite_parsing_tests);
    reporter.register_test("JSON Checker",json_checker_parsing_tests);
    reporter.run_tests();*/
}

