
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
[jsoncons](https://github.com/danielaparker/jsoncons)|8.428|3.592|423|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|15.431|7.295|494|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|3.396|3.061|457|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|51.57|28.559|2466|Uses std::map for both arrays and objects, expect larger memory footprint.
[glaze](https://github.com/stephenberry/glaze)|4.772|1.73|1085|
[Boost.JSON](https://www.boost.org/doc/libs/latest/libs/json/doc/html/index.html)|3.264|2.571|622|
[yyjson](https://github.com/ibireme/yyjson)|1.629|1.487|1205|
[reflect-cpp](https://github.com/getml/reflect-cpp)|18.866|4.751|1033|Uses yyjson for serializing and deserializing JSON.

