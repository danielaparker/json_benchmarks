
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons.json|897.95|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|master-52fc6f7
[nlohmann](https://github.com/nlohmann/json)|3.6.1
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.12
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.0
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|9.55|3.545|2057|
[nlohmann](https://github.com/nlohmann/json)|21.555|13.081|2217|Uses girsu2 for printing floating-point numbers, expect faster serializing. Uses std::map for objects.
[cjson](https://github.com/DaveGamble/cJSON)|23.396|77.12|11033|Inefficient storage (items do not share the same space). Nice use of sprintf and sscanf to support locale-independent round-trip.
[json11](https://github.com/dropbox/json11)|22.272|18.43|9135|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|8.389|2.564|2163|Uses custom floating point parsing and girsu3 for printing floating-point numbers, expect faster parsing and serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|65.759|18.204|12176|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|350.012|52.1|5204|Boost spirit parsing is slow

