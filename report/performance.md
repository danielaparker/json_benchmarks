
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons.json|610.65|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|master20180629
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.1
[nlohmann](https://github.com/nlohmann/json)|3.0.1
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|16.134|3.959|2057|
[cjson](https://github.com/DaveGamble/cJSON)|22.87|77.175|10746|
[nlohmann](https://github.com/nlohmann/json)|23.219|15.032|2214|
[json11](https://github.com/dropbox/json11)|29.891|20.701|8884|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|7.818|2.617|2168|Uses custom floating point conversion
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|71.305|23.772|12175|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|345.424|56.723|5289|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|7.629|98.387|2669|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

