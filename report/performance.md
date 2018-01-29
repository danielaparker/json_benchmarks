
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
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented))|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|10.053|3.494|2067|
[nlohmann](https://github.com/nlohmann/json)|18.12|13.733|2292|
[cjson](https://github.com/DaveGamble/cJSON)|19.499|66.15|11111|
[json11](https://github.com/dropbox/json11)|27.418|14.67|9305|
[rapidjson](https://github.com/miloyip/rapidjson)|8.462|2.592|3747|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|66.301|20.487|12427|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|333.143|54.467|4988|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|7.68|79.401|2987|No serialization function, using sample pretty-print code

