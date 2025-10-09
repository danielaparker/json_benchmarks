
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

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|1.4.3
[nlohmann](https://github.com/nlohmann/json)|3.12.0
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.6
[yyjson](https://github.com/ibireme/yyjson)|0.12.0
[glaze](https://github.com/stephenberry/glaze)|5.7.1
[reflect-cpp](https://github.com/getml/reflect-cpp)|0.21.0

Library|Time to read (milliseconds)|Time to write (milliseconds)|Physical memory footprint of json value (bytes)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|49|18|2710|
[nlohmann](https://github.com/nlohmann/json)|76|37|185|
[rapidjson](https://github.com/miloyip/rapidjson)|32|14|8151|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|117|100|1059|
[yyjson](https://github.com/ibireme/yyjson)|6|3|606|
[glaze](https://github.com/stephenberry/glaze)|66|5|11786|
[reflect-cpp](https://github.com/getml/reflect-cpp)|168|28|24576|

