
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|794.72|Text,doubles

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
[rapidjson](https://github.com/miloyip/rapidjson)|RAPIDJSON_VERSION_MAJOR.RAPIDJSON_VERSION_MINOR.RAPIDJSON_VERSION_PATCH
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.6
[taojson](https://github.com/taocpp/json)|TAO_JSON_VERSION_MAJOR.TAO_JSON_VERSION_MINOR.TAO_JSON_VERSION_PATCH

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|8.372|3.679|423|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|15.702|7.437|494|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|3.385|3|457|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|55.078|27.504|2466|Uses std::map for both arrays and objects, expect larger memory footprint.
[taojson](https://github.com/taocpp/json)|17.43|5.837|1060|Uses modified [google/double conversion](https://github.com/google/double-conversion) routines for parsing doubles. Uses modified [jeaiii/itoa](https://github.com/jeaiii/itoa) routines for outputting integers. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.

