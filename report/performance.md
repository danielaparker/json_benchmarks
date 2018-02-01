
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
[jsoncons](https://github.com/danielaparker/jsoncons)|9.776|3.097|2056|
[nlohmann](https://github.com/nlohmann/json)|19.315|14.755|2218|
[cjson](https://github.com/DaveGamble/cJSON)|19.448|66.928|10746|
[json11](https://github.com/dropbox/json11)|24.431|15.572|8887|
[rapidjson](https://github.com/miloyip/rapidjson)|6.794|2.691|2165|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|56.637|20.988|12175|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|299.341|55.741|5271|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|6.937|81.948|2669|No serialization function, using sample pretty-print code

