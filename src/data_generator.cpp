#include <chrono>
#include <sstream>
#include "jsoncons/json_encoder.hpp"
#include <fstream>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

void make_big_file(const char *filename, size_t count, size_t numIntegers, size_t numDoubles, uint64_t flags)
{
    std::ofstream os(filename, std::ofstream::binary | std::ios_base::out| std::ios_base::trunc);
    if (os.bad() || !os.is_open())
    {
        std::ostringstream os;
        os << "Cannot open file %s" << filename;
        throw std::runtime_error(os.str().c_str());
    }

    jsoncons::json_options options;
    options.escape_all_non_ascii(true);
    jsoncons::json_encoder handler(os, options);

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
        handler.name("person");
        handler.begin_object();
        handler.name("first_name");
        handler.string_value("John");
        handler.name("last_name"   );
        handler.string_value("Doe");
        handler.name("birthdate");
        handler.string_value("1998-05-13");
        handler.name("sex");
        handler.string_value("m");
        handler.name("salary");
        handler.uinteger_value(70000);
        handler.name("married");
        handler.bool_value(false);
        handler.name("interests");
        handler.begin_array();
        handler.string_value("Reading");
        handler.string_value("Mountain biking");
        handler.string_value("Hacking");
        handler.end_array();
        handler.name("favorites");
        handler.begin_object();
        handler.name("color");
        handler.string_value("blue");
        handler.name("sport");
        handler.string_value("soccer");
        handler.name("food");
        handler.string_value("spaghetti");
        handler.name("big_text");
        handler.string_value(big_text);
        handler.name("integer_values");
        handler.begin_array();
        for (auto x : integer_values)
        {
            handler.int64_value(x);
        }
        handler.end_array();
        handler.name("double_values");
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
        handler.name("person");
        handler.begin_object();
        handler.name("first_name");
        handler.string_value("jane");
        handler.name("last_name"   );
        handler.string_value("doe");
        handler.name("birthdate");
        handler.string_value("1998-05-13");
        handler.name("sex");
        handler.string_value("f");
        handler.name("salary");
        handler.uinteger_value(80000);
        handler.name("married");
        handler.bool_value(true);
        handler.name("pets");
        handler.null_value();
        handler.name("interests");
        handler.begin_array();
        handler.string_value("Skiing");
        handler.string_value("Hiking");
        handler.string_value("Camoing");
        handler.end_array();
        handler.name("favorites");
        handler.begin_object();
        handler.name("color");
        handler.string_value("Red");
        handler.name("sport");
        handler.string_value("skiing");
        handler.name("food");
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

