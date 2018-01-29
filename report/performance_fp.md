
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
[jsoncons](https://github.com/danielaparker/jsoncons)|15.104|24.657|1060|
[nlohmann](https://github.com/nlohmann/json)|19.04|30.691|1571|
[cjson](https://github.com/DaveGamble/cJSON)|15.498|44.98|5897|
[json11](https://github.com/dropbox/json11)|18.099|31.774|5356|
[rapidjson](https://github.com/miloyip/rapidjson)|4.164|5.46|1651|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|45.279|47.751|5468|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|228.342|61.796|2113|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|2.837|41.39|1750|No serialization function, using sample pretty-print code

