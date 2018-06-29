
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|595.4|Text,doubles

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
[jsoncons](https://github.com/danielaparker/jsoncons)|19.735|27.339|1047|
[cjson](https://github.com/DaveGamble/cJSON)|31.939|53.661|5709|
[nlohmann](https://github.com/nlohmann/json)|27.204|37.009|1191|
[json11](https://github.com/dropbox/json11)|25.632|39.622|4783|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|5.94|6.822|1048|Uses custom floating point conversion
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|55.632|60.134|5168|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|274.093|68.811|2628|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|3.86|51.734|1634|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

