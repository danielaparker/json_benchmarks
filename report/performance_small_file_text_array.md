
## Read and Write Time Comparison


Input filename|Size (bytes)|Content
---|---|---
data/input/small_file/small_file_text_array.json|3930|Text,integers

Environment|Windows, Intel
---|---
Computer|Lenovo Thinkpad X Extreme with 8 cores, 16 hardware threads, 32 GB memory, 2 TB solid state drive
Operating system|Windows 2011
Compiler|Visual Studio 2022
Language|C++ 2017

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|1.4.1
[nlohmann](https://github.com/nlohmann/json)|3.12.0
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.6
[yyjson](https://github.com/ibireme/yyjson)|0.12.0

Library|Time to read (milliseconds)|Time to write (milliseconds)|Physical memory footprint of json value (bytes)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|46|17|49|
[nlohmann](https://github.com/nlohmann/json)|73|32|16|
[rapidjson](https://github.com/miloyip/rapidjson)|28|12|84|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|108|95|55|
[yyjson](https://github.com/ibireme/yyjson)|6|71|1|

