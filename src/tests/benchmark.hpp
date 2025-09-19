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
        virtual std::string get_notes() const = 0;
        virtual measurements measure_small(const std::string& input, std::string& output) = 0;
        virtual measurements measure_big(const char *input_filename, const char* output_filename) = 0;
        virtual std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) = 0;
        virtual const std::string& remarks() const = 0;
    };

    struct json_implementation
    {
        std::string name;
        std::string url;
        std::string version;
        std::string notes;
        std::shared_ptr<benchmark> measures;

        json_implementation() = default;

        json_implementation(const json_implementation&) = default;

        json_implementation(const std::string& name,
                           const std::string& url,
                           const std::string& version,
                           const std::string& notes,
                           std::shared_ptr<benchmark> measures)
            : name(name), url(url), version(version), notes(notes), measures(measures)
        {
        }
    };

    class cjson_benchmark : public benchmark
    {
    public:
        static std::string version();
        static std::string name();
        static std::string url();
        static std::string notes();

        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        std::string get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
        const std::string& remarks() const override;
    };

    class jsoncons_benchmark : public benchmark
    {
    public:
        static std::string version();
        static std::string name();
        static std::string url();
        static std::string notes();
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        std::string get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
        const std::string& remarks() const override;
    };

    class jsoncpp_benchmark : public benchmark
    {
    public:
        static std::string version();
        static std::string name();
        static std::string url();
        static std::string notes();
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        std::string get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
        const std::string& remarks() const override;
    };

    class nlohmann_benchmark : public benchmark
    {
    public:
        static std::string version();
        static std::string name();
        static std::string url();
        static std::string notes();
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        std::string get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
        const std::string& remarks() const override;
    };

    class rapidjson_benchmark : public benchmark
    {
    public:
        static std::string version();
        static std::string name();
        static std::string url();
        static std::string notes();
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        std::string get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
        const std::string& remarks() const override;
    };

    class taojson_benchmark : public benchmark
    {
    public:
        static std::string version();
        static std::string name();
        static std::string url();
        static std::string notes();
        std::string get_version() const override;
        std::string get_name() const override;
        std::string get_url() const override;
        std::string get_notes() const override;
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
        const std::string& remarks() const override;
    };
}

#endif

