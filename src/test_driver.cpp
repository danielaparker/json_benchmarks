#include "tests/library_tests.hpp"
#include <iostream>
#include <fstream>
#include "measurements.hpp"
#include <string>
#include "json_parsing_report_generator.hpp"
#include "data_generator.hpp"
#include "jsoncons/json.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace json_benchmarks;

void benchmarks_small_file(std::vector<library_info>& info)
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
           << "|" << "Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD" << std::endl;
        os << "Operating system"
           << "|" << "Windows 2010" << std::endl;
        os << "Compiler"
           << "|" << "Visual Studio 2015" << std::endl;

        os << std::endl;

        os << "Library|Version" << std::endl;
        os << "---|---" << std::endl;
        for (const auto& val : info)
        {
            os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
        }
        os << std::endl;

        os << "Library|Time to read (milliseconds)|Time to write (milliseconds)|Memory footprint of json value (bytes)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        std::vector<measurements> v(info.size());

        size_t number_times = 50000;
        for (size_t i = 0; i < number_times; ++i)
        {
            for (size_t j = 0; j < info.size(); ++j)
            {
                auto results = info[j].measures->measure_small(input,output);
                v[j].time_to_read += results.time_to_read;
                v[j].time_to_write += results.time_to_write;
                v[j].memory_used += results.memory_used;
            }
            output.clear();
        }
        for (const auto& results : v)
        {
            os << results.library_name
               << "|" << results.time_to_read/(number_times)
               << "|" << results.time_to_write/(number_times)
               << "|" << results.memory_used/number_times
               << "|" << results.remarks
               << std::endl; 
        }
        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void benchmarks_int(std::vector<library_info>& info)
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

        for (const auto& val : info)
        {
            os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
        }
        os << std::endl;

        os << "Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        for (auto& item : info)
        {
            std::string output_path = "data/output/persons_" + item.name + ".json";
            auto results = item.measures->measure_big("data/output/persons.json",output_path.c_str());
            os << results.library_name
               << "|" << (results.time_to_read/1000.0) 
               << "|" << (results.time_to_write/1000.0) 
               << "|" << (results.memory_used)
               << "|" << results.remarks
               << std::endl; 
        }

        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void benchmarks_fp(std::vector<library_info>& info)
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
        for (const auto& val : info)
        {
            os << "[" << val.name << "](" << val.url << ")" << "|" << val.version << std::endl;
        }
        os << std::endl;

        os << "Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks" << std::endl;
        os << "---|---|---|---|---" << std::endl;

        for (auto& item : info)
        {
            std::string output_path = "data/output_fp/persons_" + item.name + ".json";
            auto results = item.measures->measure_big("data/output/persons_fp.json",output_path.c_str());
            os << results.library_name
               << "|" << (results.time_to_read/1000.0) 
               << "|" << (results.time_to_write/1000.0) 
               << "|" << (results.memory_used)
               << "|" << results.remarks
               << std::endl; 
        }

        os << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void insert_JSONTestSuite(const std::vector<library_info>& info,
                          json_parsing_report_generator& generator)
{
    try
    {
        std::vector<result_code_info> result_code_infos;
        result_code_infos.push_back(result_code_info{result_code::expected_result,"Expected result","#d19b73"});
        result_code_infos.push_back(result_code_info{result_code::expected_success_parsing_failed,"Expected success, parsing failed","#69005e"});
        result_code_infos.push_back(result_code_info{result_code::expected_failure_parsing_succeeded,"Expected failure, parsing succeeded","#001a75"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_succeeded,"Result undefined, parsing succeeded","#f7a8ff"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_failed,"Result undefined, parsing failed","#050f07"});
        result_code_infos.push_back(result_code_info{result_code::process_stopped,"Process stopped","#e00053"});

        std::vector<test_suite_file> pathnames;

        json_file_finder
        (
            "data/input/JSONTestSuite",
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
        for (auto& item : info)
        {
            results.push_back(item.measures->run_test_suite(pathnames));
        }

        generator.insert_results(pathnames,results);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void insert_JSON_checker(const std::vector<library_info>& info,
                         json_parsing_report_generator& generator)
{
    try
    {
        std::vector<result_code_info> result_code_infos;
        result_code_infos.push_back(result_code_info{result_code::expected_result,"Expected result","#008000"});
        result_code_infos.push_back(result_code_info{result_code::expected_success_parsing_failed,"Expected success, parsing failed","#d19b73"});
        result_code_infos.push_back(result_code_info{result_code::expected_failure_parsing_succeeded,"Expected failure, parsing succeeded","#001a75"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_succeeded,"Result undefined, parsing succeeded","#f7a8ff"});
        result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_failed,"Result undefined, parsing failed","#050f07"});
        result_code_infos.push_back(result_code_info{result_code::process_stopped,"Process stopped","#e00053"});

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
        for (auto& item : info)
        {
            results.push_back(item.measures->run_test_suite(pathnames));
        }

        generator.insert_results(pathnames,results);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    std::vector<library_info> info; 

    info.emplace_back("jsoncons",
                      "https://github.com/danielaparker/jsoncons",
                      "0.150.0", 
                      "With strict_json_parsing, uses wjson if utf16" ,
                      std::make_shared<jsoncons_benchmarks>());
    info.emplace_back("nlohmann",
                      "https://github.com/nlohmann/json",
                      "3.7.3", 
                      "",
                      std::make_shared<nlohmann_benchmarks>());
    info.emplace_back("cJSON",
                      "https://github.com/DaveGamble/cJSON",
                      "2019-11-30", 
                      "",
                      std::make_shared<cjson_benchmarks>());
    info.emplace_back("json11",
                      "https://github.com/dropbox/json11",
                      "2017-06-20-2", 
                      "",
                      std::make_shared<json11_benchmarks>());
    info.emplace_back("rapidjson",
                      "https://github.com/miloyip/rapidjson",
                      "2020-02-08", 
                      "Uses custom (non standard lib) floating point conversion",
                      std::make_shared<rapidjson_benchmarks>());
    info.emplace_back("jsoncpp",
                      "https://github.com/open-source-parsers/jsoncpp",
                      "1.9.2", 
                      "Uses map for both arrays and objects",
                      std::make_shared<jsoncpp_benchmarks>());
    info.emplace_back("json_spirit",
                      "http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented",
                      "4.1.0-1", 
                      "",
                      std::make_shared<json_spirit_benchmarks>());

    benchmarks_int(info);
    //benchmarks_fp(info);
    //benchmarks_small_file(info);

    /*std::vector<result_code_info> result_code_infos;
    result_code_infos.push_back(result_code_info{result_code::expected_result,"Expected result","#008000"});
    result_code_infos.push_back(result_code_info{result_code::expected_success_parsing_failed,"Expected success, parsing failed","#d19b73"});
    result_code_infos.push_back(result_code_info{result_code::expected_failure_parsing_succeeded,"Expected failure, parsing succeeded","#001a75"});
    result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_succeeded,"Result undefined, parsing succeeded","#f7a8ff"});
    result_code_infos.push_back(result_code_info{result_code::result_undefined_parsing_failed,"Result undefined, parsing failed","#050f07"});
    result_code_infos.push_back(result_code_info{result_code::process_stopped,"Process stopped","#e00053"});

    std::ofstream fs("docs/index.html");
    json_parsing_report_generator generator("Parser Comparisons", result_code_infos, info, fs);
    generator.insert_generator("JSON Test Suite",insert_JSONTestSuite);
    generator.insert_generator("JSON Checker",insert_JSON_checker);
    generator.generate();*/
}

