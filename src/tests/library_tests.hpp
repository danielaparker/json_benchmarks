#ifndef JSON_BENCHMARKS_LIBRARY_TESTS_HPP
#define JSON_BENCHMARKS_LIBRARY_TESTS_HPP

#include "measurements.hpp"
#include <vector>
#include <memory>

namespace json_benchmarks {

    class library_measures
    {
    public:
        virtual ~library_measures() = default;
        virtual measurements measure_small(const std::string& input, std::string& output) = 0;
        virtual measurements measure_big(const char *input_filename, const char* output_filename) = 0;
        virtual std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) = 0;
    };

    struct library_info
    {
        std::string name;
        std::string url;
        std::string version;
        std::string notes;
        std::shared_ptr<library_measures> measures;

        library_info() = default;

        library_info(const library_info&) = default;

        library_info(const std::string& name,
                     const std::string& url,
                     const std::string& version,
                     const std::string& notes,
                     std::shared_ptr<library_measures> measures)
            : name(name), url(url), version(version), notes(notes), measures(measures)
        {
        }
    };

    class cjson_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class gason_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class json11_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class json_spirit_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class jsoncons_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class jsoncpp_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class nlohmann_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };

    class rapidjson_benchmarks : public library_measures
    {
    public:
        measurements measure_small(const std::string& input, std::string& output) override;
        measurements measure_big(const char *input_filename, const char* output_filename) override;
        std::vector<test_suite_result> run_test_suite(std::vector<test_suite_file>& pathnames) override;
    };
}

#endif

