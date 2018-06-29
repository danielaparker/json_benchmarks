#include "measurements.hpp"
#include "tests/library_tests.hpp"
#include <vector>
#include <boost/filesystem.hpp>

namespace json_benchmarks {

    std::vector<library_info> library_tests::get_library_info() 
    {
        std::vector<library_info> info;

        info.push_back(library_info{"jsoncons","https://github.com/danielaparker/jsoncons","master20180629", "With strict_parse_error_handler, uses wjson if utf16" });
        info.push_back(library_info{"cJSON","https://github.com/DaveGamble/cJSON","1.7.1", ""});
        info.push_back(library_info{"nlohmann","https://github.com/nlohmann/json","3.0.1", ""});
        info.push_back(library_info{"json11","https://github.com/dropbox/json11","master 20161125", ""});
        info.push_back(library_info{"rapidjson","https://github.com/miloyip/rapidjson","1.1.0", "Uses custom (non standard lib) floating point conversion"});
        info.push_back(library_info{"jsoncpp","https://github.com/open-source-parsers/jsoncpp","1.7.7", "Uses map for both arrays and objects"});
        info.push_back(library_info{"json_spirit","http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented","4.08", ""});
        info.push_back(library_info{"gason","https://github.com/vivkin/gason","master 20161107", "Uses naive floating point conversion, fast but inaccurate"});

        return info;
    }

    std::vector<measurements> library_tests::measure(const std::string& input, std::string& output)
    {
        std::vector<measurements> tests;

        tests.push_back(jsoncons_benchmarks::measure(input, output));
        tests.push_back(cjson_benchmarks::measure(input, output));
        tests.push_back(nlohmann_benchmarks::measure(input, output));
        tests.push_back(json11_benchmarks::measure(input, output));
        tests.push_back(rapidjson_benchmarks::measure(input, output));
        tests.push_back(jsoncpp_benchmarks::measure(input, output));
        tests.push_back(json_spirit_benchmarks::measure(input, output));
        tests.push_back(gason_benchmarks::measure(input, output));

        return tests;
    }

    std::vector<measurements> library_tests::measure(const char *input_filename, const char* output_dir)
    {
        boost::filesystem::path base(output_dir);

        std::vector<measurements> tests;

        tests.push_back(jsoncons_benchmarks::measure(input_filename, 
                                         (base / "persons-jsoncons.json").string().c_str()));

        tests.push_back(cjson_benchmarks::measure(input_filename, 
                                      (base / "persons-cjson.json").string().c_str()));

        tests.push_back(nlohmann_benchmarks::measure(input_filename, 
                                         (base / "persons-nlohmann.json").string().c_str()));


        tests.push_back(json11_benchmarks::measure(input_filename, (base / "persons-json11.json").string().c_str()));

        tests.push_back(rapidjson_benchmarks::measure(input_filename, (base / "persons-rapidjson.json").string().c_str()));

        tests.push_back(jsoncpp_benchmarks::measure(input_filename, (base / "persons-jsoncpp.json").string().c_str()));

        tests.push_back(json_spirit_benchmarks::measure(input_filename, (base / "persons-json_spirit.json").string().c_str()));

        tests.push_back(gason_benchmarks::measure(input_filename, (base / "persons-gason.json").string().c_str()));

        return tests;
    }

    std::vector<std::vector<test_suite_result>> library_tests::run_test_suite(std::vector<test_suite_file>& pathnames) const
    {
        std::vector<std::vector<test_suite_result>> results;

        results.push_back(jsoncons_benchmarks::run_test_suite(pathnames));

        results.push_back(cjson_benchmarks::run_test_suite(pathnames));

        results.push_back(nlohmann_benchmarks::run_test_suite(pathnames));

        results.push_back(json11_benchmarks::run_test_suite(pathnames));
 
        results.push_back(rapidjson_benchmarks::run_test_suite(pathnames));

        results.push_back(jsoncpp_benchmarks::run_test_suite(pathnames));

        results.push_back(json_spirit_benchmarks::run_test_suite(pathnames));

        results.push_back(gason_benchmarks::run_test_suite(pathnames));

        return results;
    }


}

