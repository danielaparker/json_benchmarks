
## Read and Write Time Comparison


Input filename|Size (bytes)|Content
---|---|---
data/input/small_file/small.text.array.json|3930|Text,integers

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

Library|Time to read (milliseconds)|Time to write (milliseconds)|Physical memory footprint of json value (bytes)|Notes
---|---|---|---|---
