
## Read and Write Time Comparison


Input filename|Size (bytes)|Content
---|---|---
data/input/small_file/small_file_text.json|6571|Text,integers

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

Library|Time to read (milliseconds)|Time to write (milliseconds)|Memory footprint of json value (bytes)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|92|25|180|
[cjson](https://github.com/DaveGamble/cJSON)|51|22|9|
[nlohmann](https://github.com/nlohmann/json)|103|35|1|
[json11](https://github.com/dropbox/json11)|101|44|22|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|30|18|106|
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|137|96|50|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|351|144|23|Boost spirit parsing is slow

