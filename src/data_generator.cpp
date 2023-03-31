#include <chrono>
#include <sstream>
#include "jsoncons/json_encoder.hpp"
#include <fstream>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

void make_big_file(const char *filename, size_t count, size_t numIntegers, size_t numDoubles, uint64_t flags)
{
    std::fstream os(filename, std::fstream::binary | std::fstream::out| std::fstream::trunc);
    if (os.bad() || !os.is_open())
    {
        std::ostringstream os;
        os << "Cannot open file " << filename;
        throw std::runtime_error(os.str().c_str());
    }

    jsoncons::json_options options;
    options.escape_all_non_ascii(true);
    jsoncons::json_stream_encoder handler(os, options);

    auto start = high_resolution_clock::now();

    std::string big_text;
    for (size_t i = 0; i < 5000; ++i)
    {
        big_text.assign("All cats like mice.");
        big_text.assign("\"\\uD800\\uDC00\"");
    }
    std::vector<double> double_values;
    for (size_t i = 0; i < numDoubles; ++i)
    {
        double_values.push_back((double)i + (double)i/(double)numDoubles);
    }
    std::vector<uint64_t> integer_values;
    for (size_t i = 0; i < numIntegers; ++i)
    {
        integer_values.push_back(i);
    }

    handler.begin_array();
    for (size_t i = 0; i < count; i+=2)
    {
        handler.begin_object();
        handler.key("person");
        handler.begin_object();
        handler.key("first_name");
        handler.string_value("John");
        handler.key("last_name"   );
        handler.string_value("Doe");
        handler.key("birthdate");
        handler.string_value("1998-05-13");
        handler.key("sex");
        handler.string_value("m");
        handler.key("salary");
        handler.uint64_value(70000);
        handler.key("married");
        handler.bool_value(false);
        handler.key("interests");
        handler.begin_array();
        handler.string_value("Reading");
        handler.string_value("Mountain biking");
        handler.string_value("Hacking");
        handler.end_array();
        handler.key("favorites");
        handler.begin_object();
        handler.key("color");
        handler.string_value("blue");
        handler.key("sport");
        handler.string_value("soccer");
        handler.key("food");
        handler.string_value("spaghetti");
        handler.key("big_text");
        handler.string_value(big_text);
        handler.key("integer_values");
        handler.begin_array();
        for (auto x : integer_values)
        {
            handler.int64_value(x);
        }
        handler.end_array();
        handler.key("double_values");
        handler.begin_array();
        for (auto x : double_values)
        {
            handler.double_value(x);
        }
        handler.end_array();
        handler.end_object();

        handler.end_object();
        handler.end_object();
    }
    for (size_t i = 0; i < count; i+=2)
    {
        handler.begin_object();
        handler.key("person");
        handler.begin_object();
        handler.key("first_name");
        handler.string_value("jane");
        handler.key("last_name"   );
        handler.string_value("doe");
        handler.key("birthdate");
        handler.string_value("1998-05-13");
        handler.key("sex");
        handler.string_value("f");
        handler.key("salary");
        handler.uint64_value(80000);
        handler.key("married");
        handler.bool_value(true);
        handler.key("pets");
        handler.null_value();
        handler.key("interests");
        handler.begin_array();
        handler.string_value("Skiing");
        handler.string_value("Hiking");
        handler.string_value("Camoing");
        handler.end_array();
        handler.key("favorites");
        handler.begin_object();
        handler.key("color");
        handler.string_value("Red");
        handler.key("sport");
        handler.string_value("skiing");
        handler.key("food");
        handler.string_value("risotto");
        handler.end_object();

        handler.end_object();
        handler.end_object();
    }
    handler.end_array();
    handler.flush();
    auto end = high_resolution_clock::now();
    auto time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Big file took " << (time_to_write/1000.0) << " seconds to write.\n";
}

