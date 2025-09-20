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
        virtual const std::string& get_notes() const = 0;
        virtual measurements measure_small(const std::string& input, std::string& output) = 0;
        virtual measurements measure_big(const char *input_filename, const char* output_filename) = 0;
        virtual std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) = 0;
    };

    class cjson_benchmark : public benchmark
    {
    public:
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        const std::string& get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class jsoncons_benchmark : public benchmark
    {
    public:
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        const std::string& get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class jsoncpp_benchmark : public benchmark
    {
    public:
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        const std::string& get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class nlohmann_benchmark : public benchmark
    {
    public:
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        const std::string& get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class rapidjson_benchmark : public benchmark
    {
    public:
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        const std::string& get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class taojson_benchmark : public benchmark
    {
    public:
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        const std::string& get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };
}

#endif

