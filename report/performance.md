
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

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|7.67|1.54|343|Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) plus fallback for printing doubles, expect faster serializing.
[nlohmann](https://github.com/nlohmann/json)|16.771|5.686|410|Uses `std::map` for objects. Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
[rapidjson](https://github.com/miloyip/rapidjson)|4.299|1.24|332|Uses custom floating point parsing, expect faster parsing. Uses girsu3 for printing doubles, expect faster serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
