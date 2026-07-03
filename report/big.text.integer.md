
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/big.text.integer.json|540.82|Text,integers

Environment|Windows, Intel
---|---
Computer|Lenovo Thinkpad X Extreme with 8 cores, 16 hardware threads, 32 GB memory, 2 TB solid state drive
Operating system|Windows 2011
Compiler|Visual Studio 2022 Version 17.14.16
Optimization|/O2,/Ot
Language|/std:c++23preview

Library|Version|Type to read into/write from
---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|1.8.1|jsoncons::json
[nlohmann](https://github.com/nlohmann/json)|3.12.0|nlohmann::json
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0|rapidjson::Document
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.6|Json::Value
[glaze](https://github.com/stephenberry/glaze)|7.4.0|glz::generic
[Boost.JSON](https://www.boost.org/doc/libs/latest/libs/json/doc/html/index.html)|1_90|boost::json::value
[yyjson](https://github.com/ibireme/yyjson)|0.12.0|yyjson_doc
[reflect-cpp](https://github.com/getml/reflect-cpp)|0.24.0|rfl::Generic

Library|Time to read (s)|Time to write (s)|Physical memory footprint of json value (MB)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|3.918|0.744|343|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|8.177|2.885|409|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|2.254|0.656|332|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|13.556|7.641|1985|Uses std::map for both arrays and objects, expect larger memory footprint.
[glaze](https://github.com/stephenberry/glaze)|3.462|1.262|880|
[Boost.JSON](https://www.boost.org/doc/libs/latest/libs/json/doc/html/index.html)|2.269|0.585|502|
[yyjson](https://github.com/ibireme/yyjson)|1.007|0.279|871|
[reflect-cpp](https://github.com/getml/reflect-cpp)|11.702|3.147|837|Uses yyjson for serializing and deserializing JSON.

