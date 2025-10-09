
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|794.72|Text,doubles

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

Library|Time to read (s)|Time to write (s)|Physical memory footprint of json value (MB)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|8.843|3.965|423|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|17.61|8.179|494|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|3.719|3.291|457|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|58.977|32.827|2466|Uses std::map for both arrays and objects, expect larger memory footprint.
[yyjson](https://github.com/ibireme/yyjson)|1.727|1.374|1205|
[glaze](https://github.com/stephenberry/glaze)|12.215|1.837|1261|
[reflect-cpp](https://github.com/getml/reflect-cpp)|16.521|5.053|1034|

