
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|797.1|Text,doubles

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
[jsoncons](https://github.com/danielaparker/jsoncons)|18.597|26.966|1047|
[cjson](https://github.com/DaveGamble/cJSON)|30.473|51.606|4958|
[nlohmann](https://github.com/nlohmann/json)|29.98|14.382|1190|
[json11](https://github.com/dropbox/json11)|26.025|38.399|4985|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|6.319|5.72|1046|Uses custom floating point conversion
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|58.6|58.137|6162|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|334.598|62.316|203|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|4.353|49.254|1836|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

