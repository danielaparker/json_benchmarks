
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons.json|540.82|Text,integers

Environment|Windows, Intel
---|---
Computer|Lenovo Thinkpad X Extreme with 8 cores, 16 hardware threads, 32 GB memory, 2 TB solid state drive
Operating system|Windows 2011
Compiler|Visual Studio 2022 Version 17.14.16
Optimization|/O2,/Ot
Language|/std:c++23preview

Library|Version|Type to read into/write from
---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|1.4.3|jsoncons::json
[nlohmann](https://github.com/nlohmann/json)|3.12.0|nlohmann::json
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0|rapidjson::Document
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.6|Json::Value
[yyjson](https://github.com/ibireme/yyjson)|0.12.0|yyjson_doc
[glaze](https://github.com/stephenberry/glaze)|5.7.1|glz::json_t
[reflect-cpp](https://github.com/getml/reflect-cpp)|0.21.0|rfl::Generic

Library|Time to read (s)|Time to write (s)|Physical memory footprint of json value (MB)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|3.637|0.773|343|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|13.848|5.867|410|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|3.306|0.874|332|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|25.04|9.737|1985|Uses std::map for both arrays and objects, expect larger memory footprint.
[yyjson](https://github.com/ibireme/yyjson)|1.016|0.301|871|
[glaze](https://github.com/stephenberry/glaze)|9.297|1.232|1200|
[reflect-cpp](https://github.com/getml/reflect-cpp)|10.91|3.49|1234|

