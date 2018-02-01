
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
[jsoncons](https://github.com/danielaparker/jsoncons)|master20180126
[nlohmann](https://github.com/nlohmann/json)|3.0.1
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.1
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|15.631|24.693|1056|
[nlohmann](https://github.com/nlohmann/json)|19.172|31.059|1236|
[cjson](https://github.com/DaveGamble/cJSON)|15.539|45.32|5713|
[json11](https://github.com/dropbox/json11)|18.34|32.205|4812|
[rapidjson](https://github.com/miloyip/rapidjson)|3.281|5.284|1099|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|43.431|48.246|6164|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|213.737|62.868|2703|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|2.484|42.004|1634|No serialization function, using sample pretty-print code

