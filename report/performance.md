
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons.json|897.95|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2019

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|0.150.0
[nlohmann](https://github.com/nlohmann/json)|3.7.3
[cJSON](https://github.com/DaveGamble/cJSON)|2019-11-30
[json11](https://github.com/dropbox/json11)|2017-06-20-2
[rapidjson](https://github.com/miloyip/rapidjson)|2020-02-08
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.2
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.1.0-1

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|8.832|3.398|2057|
[nlohmann](https://github.com/nlohmann/json)|21.323|12.634|2218|Uses girsu2 for printing floating-point numbers, expect faster serializing. Uses std::map for objects.
[cjson](https://github.com/DaveGamble/cJSON)|29.248|79.435|11032|Inefficient storage (items do not share the same space). Nice use of sprintf and sscanf to support locale-independent round-trip.
[json11](https://github.com/dropbox/json11)|28.702|15.838|9167|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|8.916|2.108|2165|Uses custom floating point parsing and girsu3 for printing floating-point numbers, expect faster parsing and serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|62.43|28.066|12175|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|364.381|51.884|5277|Boost spirit parsing is slow

