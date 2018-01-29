
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/input/persons.json|610.65|Text,integers

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
[jsoncons](https://github.com/danielaparker/jsoncons)|10.153|3.039|2067|
[nlohmann](https://github.com/nlohmann/json)|19.057|13.924|2292|
[cjson](https://github.com/DaveGamble/cJSON)|24.399|71.392|11111|
[json11](https://github.com/dropbox/json11)|24.871|16.143|9297|
[rapidjson](https://github.com/miloyip/rapidjson)|8.638|2.491|3739|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|77.573|42.039|12551|
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|382.213|60.362|5188|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|9.102|86.714|2949|No serialization function, using sample pretty-print code

