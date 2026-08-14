
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/big.text.floating_point.json|794.72|Text,doubles

Environment|Windows, Intel
---|---
Computer|Lenovo Thinkpad X Extreme with 8 cores, 16 hardware threads, 32 GB memory, 2 TB solid state drive
Operating system|Windows 2011
Compiler|Visual Studio 2022 Version 17.14.16
Optimization|/O2,/Ot
Language|/std:c++23preview

Library|Version|Type to read into/write from
---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|JSONCONS_VERSION_MAJOR.JSONCONS_VERSION_MINOR.JSONCONS_VERSION_PATCH|jsoncons::json
[nlohmann](https://github.com/nlohmann/json)|3.12.0|nlohmann::json
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0|rapidjson::Document
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.6|Json::Value
[glaze](https://github.com/stephenberry/glaze)|7.4.0|glz::generic
[Boost.JSON](https://www.boost.org/doc/libs/latest/libs/json/doc/html/index.html)|1_90|boost::json::value
[yyjson](https://github.com/ibireme/yyjson)|0.12.0|yyjson_doc
[reflect-cpp](https://github.com/getml/reflect-cpp)|0.24.0|rfl::Generic

Library|Time to read (s)|Time to write (s)|Physical memory footprint of json value (MB)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|8.879|3.879|423|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|15.997|7.165|494|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|3.443|3.061|457|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|52.944|30.007|2466|Uses std::map for both arrays and objects, expect larger memory footprint.
[glaze](https://github.com/stephenberry/glaze)|5.266|1.825|1087|
[Boost.JSON](https://www.boost.org/doc/libs/latest/libs/json/doc/html/index.html)|3.579|2.722|621|
[yyjson](https://github.com/ibireme/yyjson)|1.672|1.497|1205|
[reflect-cpp](https://github.com/getml/reflect-cpp)|19.924|5.482|1032|Uses yyjson for serializing and deserializing JSON.

