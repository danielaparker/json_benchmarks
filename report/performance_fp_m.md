
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|697.35|Text,doubles

Environment|Windows, Intel
---|---
Computer|Lenovo Thinkpad X Extreme with 8 cores, 16 hardware threads, 32 GB memory, 2 TB solid state drive
Operating system|Windows 2011
Compiler|Visual Studio 2022
Language|C++ 2017

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|0.170.0
[nlohmann](https://github.com/nlohmann/json)|3.11.2
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.15
[rapidjson](https://github.com/miloyip/rapidjson)|2020-02-08
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.5
[taojson](https://github.com/taocpp/json)|2020-09-14

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|18.801|12.311|1057|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|24.371|19.619|1234|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[cJSON](https://github.com/DaveGamble/cJSON)|24.515|69.299|5813|Inefficient storage (items do not share the same space), expect larger memory footprint. Uses sprintf and sscanf to support locale-independent round-trip.
[rapidjson](https://github.com/miloyip/rapidjson)|4.986|7.48|1132|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|128.057|77.492|6163|Uses std::map for both arrays and objects, expect larger memory footprint.
[taojson](https://github.com/taocpp/json)|36.483|14.202|2646|Uses modified [google/double conversion](https://github.com/google/double-conversion) routines for parsing doubles. Uses modified [jeaiii/itoa](https://github.com/jeaiii/itoa) routines for outputting integers. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.

