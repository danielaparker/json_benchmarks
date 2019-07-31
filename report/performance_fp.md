
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|697.35|Text,doubles

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
[jsoncons](https://github.com/danielaparker/jsoncons)|15.08|8.183|1057|
[nlohmann](https://github.com/nlohmann/json)|24.131|16.613|1235|Uses girsu2 for printing floating-point numbers, expect faster serializing. Uses std::map for objects.
[cjson](https://github.com/DaveGamble/cJSON)|22.787|67.138|5814|Inefficient storage (items do not share the same space). Nice use of sprintf and sscanf to support locale-independent round-trip.
[json11](https://github.com/dropbox/json11)|20.793|44.952|4913|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|4.122|6.049|1102|Uses custom floating point parsing and girsu3 for printing floating-point numbers, expect faster parsing and serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|54.242|62.607|5760|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|252.395|61.37|2647|Boost spirit parsing is slow

