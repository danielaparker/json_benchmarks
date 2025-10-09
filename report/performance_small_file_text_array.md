
## Read and Write Time Comparison


Input filename|Size (bytes)|Content
---|---|---
data/input/small_file/small_file_text_array.json|3930|Text,integers

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

Library|Time to read (milliseconds)|Time to write (milliseconds)|Physical memory footprint of json value (bytes)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|58|21|3144|
[nlohmann](https://github.com/nlohmann/json)|95|43|2803|
[rapidjson](https://github.com/miloyip/rapidjson)|36|15|8460|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|139|114|1282|
[yyjson](https://github.com/ibireme/yyjson)|7|3|7|
[glaze](https://github.com/stephenberry/glaze)|75|7|6676|
[reflect-cpp](https://github.com/getml/reflect-cpp)|195|33|20323|

