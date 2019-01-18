
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
[jsoncons](https://github.com/danielaparker/jsoncons)|17.935|7.843|1046|Uses girsu3 for printing floating-point numbers, expect faster serializing. Uses flat sorted map for objects, expect smaller memory footprint.
[cjson](https://github.com/DaveGamble/cJSON)|32.002|51.534|4857|Inefficient storage (items do not share the same space). Nice use of sprintf and sscanf to support locale-independent round-trip.
[nlohmann](https://github.com/nlohmann/json)|27.756|14.448|1188|Uses girsu2 for printing floating-point numbers, expect faster serializing. Uses std::map for objects.
[json11](https://github.com/dropbox/json11)|31.513|37.781|4884|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|5.888|5.643|1047|Uses custom floating point parsing and girsu3 for printing floating-point numbers, expect faster parsing and serializing. Uses custom allocation and flat map for objects, expect smaller memory footprint.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|56.694|59.691|6162|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|297.711|62.381|4222|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|4.003|48.635|1736|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

