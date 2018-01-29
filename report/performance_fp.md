
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/input/persons_fp.json|1207.9|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|master20180126
[nlohmann](https://github.com/nlohmann/json)|2.0.7
[cJSON](https://github.com/DaveGamble/cJSON)|master 20180125

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|36.323|49.891|1701|
[nlohmann](https://github.com/nlohmann/json)|49.952|30.858|186|
[cjson](https://github.com/DaveGamble/cJSON)|69.822|105.128|11238|
[json11](https://github.com/dropbox/json11)|68.701|68.608|9625|
[rapidjson](https://github.com/miloyip/rapidjson)|29.322|13.698|3807|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|148.824|117.22|12542|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|623.045|126.12|6280|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|14.727|88.317|3314|No serialization function, using sample pretty-print code

