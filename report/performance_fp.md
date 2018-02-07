
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
[jsoncons](https://github.com/danielaparker/jsoncons)|15.011|25.643|1057|
[cjson](https://github.com/DaveGamble/cJSON)|16.961|46.993|5713|
[nlohmann](https://github.com/nlohmann/json)|21.253|31.605|1230|
[json11](https://github.com/dropbox/json11)|18.813|33.992|4807|
[rapidjson](https://github.com/miloyip/rapidjson)|3.729|5.694|1092|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|46.899|50.288|6163|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|227.238|65.434|2591|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|2.605|42.327|1634|No serialization function, using sample pretty-print code

