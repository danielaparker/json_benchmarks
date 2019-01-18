
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
[jsoncons](https://github.com/danielaparker/jsoncons)|0.117.0
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.9
[nlohmann](https://github.com/nlohmann/json)|3.4.0
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|11.54|3.675|2057|Uses girsu3 for printing floating-point numbers, expect faster serializing. Uses flat sorted map for objects, expect smaller memory footprint.
[cjson](https://github.com/DaveGamble/cJSON)|50.275|114.67|7513|Inefficient storage (items do not share the same space). Nice use of sprintf and sscanf to support locale-independent round-trip.
[nlohmann](https://github.com/nlohmann/json)|25.698|13.116|2215|Uses girsu2 for printing floating-point numbers, expect faster serializing. Uses std::map for objects.
[json11](https://github.com/dropbox/json11)|24.814|19.646|9126|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|7.707|2.59|2164|Uses custom floating point parsing and girsu3 for printing floating-point numbers, expect faster parsing and serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|83.328|23.021|10435|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|390.754|51.166|5266|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|8.218|95.829|2956|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

