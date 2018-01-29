
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|595.4|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|master20180126
[nlohmann](https://github.com/nlohmann/json)|3.0.1
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.1
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented))|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|16.505|24.256|309|
[nlohmann](https://github.com/nlohmann/json)|26.152|30.162|0|
[cjson](https://github.com/DaveGamble/cJSON)|30.806|43.142|5641|
[json11](https://github.com/dropbox/json11)|29.638|31.187|5155|
[rapidjson](https://github.com/miloyip/rapidjson)|14.567|5.202|1683|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|60.838|47.272|5331|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|345.284|62.109|3464|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|5.631|41.655|1472|No serialization function, using sample pretty-print code

