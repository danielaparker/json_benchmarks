
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
[jsoncons](https://github.com/danielaparker/jsoncons)|master20180206
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.1
[nlohmann](https://github.com/nlohmann/json)|3.0.1
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|10.708|3.184|2057|
[cjson](https://github.com/DaveGamble/cJSON)|24.596|78.878|10745|
[nlohmann](https://github.com/nlohmann/json)|21.001|14.384|2214|
[json11](https://github.com/dropbox/json11)|20.903|16.555|8852|
[rapidjson](https://github.com/miloyip/rapidjson)|6.378|2.479|2168|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|60.048|19.946|12176|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|317.484|58.406|5340|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|6.687|82.5|2669|No serialization function, using sample pretty-print code

