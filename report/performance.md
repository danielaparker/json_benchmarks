
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons.json|540.82|Text,integers

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

Library|Time to read (s)|Time to write (s)|Physical memory footprint of json value (MB)|Notes
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|10.487|2.121|343|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|25.477|9.274|410|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|6.089|1.712|332|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|44.919|19.29|1985|Uses std::map for both arrays and objects, expect larger memory footprint.
[yyjson](https://github.com/ibireme/yyjson)|0|0.69|871|

