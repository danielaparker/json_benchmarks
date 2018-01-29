#include <chrono>
#include "jsoncons/json_serializer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

void make_big_file(const char *filename, size_t count, size_t numIntegers, size_t numDoubles, uint64_t flags)
{
    std::ofstream os(filename, std::ofstream::binary | std::ios_base::out| std::ios_base::trunc);
    if (os.bad() || !os.is_open())
    {
        throw jsoncons::json_exception_1<std::exception>("Cannot open file %s", std::string(filename));
    }

    jsoncons::serialization_options options;
    options.escape_all_non_ascii(true);
    jsoncons::json_serializer handler(os, options, false);

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

    handler.begin_json();
    handler.begin_array();
    for (size_t i = 0; i < count; i+=2)
    {
        handler.begin_object();
        handler.name("person");
        handler.begin_object();
        handler.name("first_name");
        handler.value("John");
        handler.name("last_name"   );
        handler.value("Doe");
        handler.name("birthdate");
        handler.value("1998-05-13");
        handler.name("sex");
        handler.value("m");
        handler.name("salary");
        handler.value(70000);
        handler.name("married");
        handler.value(false);
        handler.name("interests");
        handler.begin_array();
        handler.value("Reading");
        handler.value("Mountain biking");
        handler.value("Hacking");
        handler.end_array();
        handler.name("favorites");
        handler.begin_object();
        handler.name("color");
        handler.value("blue");
        handler.name("sport");
        handler.value("soccer");
        handler.name("food");
        handler.value("spaghetti");
        handler.name("big_text");
        handler.value(big_text);
        handler.name("integer_values");
        handler.begin_array();
        for (auto x : integer_values)
        {
            handler.integer_value(x);
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
        handler.value("jane");
        handler.name("last_name"   );
        handler.value("doe");
        handler.name("birthdate");
        handler.value("1998-05-13");
        handler.name("sex");
        handler.value("f");
        handler.name("salary");
        handler.value(80000);
        handler.name("married");
        handler.value(true);
        handler.name("pets");
        handler.value(jsoncons::null_type());
        handler.name("interests");
        handler.begin_array();
        handler.value("Skiing");
        handler.value("Hiking");
        handler.value("Camoing");
        handler.end_array();
        handler.name("favorites");
        handler.begin_object();
        handler.name("color");
        handler.value("Red");
        handler.name("sport");
        handler.value("skiing");
        handler.name("food");
        handler.value("risotto");
        handler.end_object();

        handler.end_object();
        handler.end_object();
    }
    handler.end_array();
    handler.end_json();
    auto end = high_resolution_clock::now();
    auto time_to_write = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Big file took " << (time_to_write/1000.0) << " seconds to write.\n";
}

