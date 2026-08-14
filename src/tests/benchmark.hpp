#ifndef JSON_BENCHMARK_HPP
#define JSON_BENCHMARK_HPP

#include "measurements.hpp"
#include <vector>
#include <memory>

namespace json_benchmark {

class benchmark
{
public:
    virtual ~benchmark() = default;
    virtual std::string get_version() const = 0;
    virtual std::string get_name() const = 0;
    virtual std::string get_url() const = 0;
    virtual std::string get_type() const = 0;
    virtual measurements measure_small(const std::string& input, std::string& output) = 0;
    virtual measurements measure_big(const char *input_filename, const char* output_filename) = 0;
    virtual std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) = 0;
};

std::shared_ptr<benchmark> make_jsoncons_benchmark();
std::shared_ptr<benchmark> make_nlohmann_benchmark();
std::shared_ptr<benchmark> make_rapidjson_benchmark();
std::shared_ptr<benchmark> make_jsoncpp_benchmark();
std::shared_ptr<benchmark> make_glaze_benchmark();
std::shared_ptr<benchmark> make_boost_json_benchmark();
std::shared_ptr<benchmark> make_yyjson_benchmark();
std::shared_ptr<benchmark> make_reflectcpp_benchmark();

} // namespace json_benchmark


#endif

