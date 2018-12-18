
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
[jsoncons](https://github.com/danielaparker/jsoncons)|0.114.0
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.9
[nlohmann](https://github.com/nlohmann/json)|3.4.0
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|11.627|3.658|2057|
[cjson](https://github.com/DaveGamble/cJSON)|28.423|100.23|11032|
[nlohmann](https://github.com/nlohmann/json)|25.846|13.175|2215|
[json11](https://github.com/dropbox/json11)|27.556|20.375|9165|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|8.633|2.684|2167|Uses custom floating point conversion
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|80.079|24.227|10516|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|392.527|50.098|5304|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|8.085|94.587|2956|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

