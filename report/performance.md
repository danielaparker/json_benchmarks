
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons.json|897.95|Text,integers

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2015

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|master e72c822
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.9
[nlohmann](https://github.com/nlohmann/json)|3.4.0
[json11](https://github.com/dropbox/json11)|master 20161125
[rapidjson](https://github.com/miloyip/rapidjson)|1.1.0
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.7.7
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.08
[gason](https://github.com/vivkin/gason)|master 20161107

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|12.16|4.16|2057|
[cjson](https://github.com/DaveGamble/cJSON)|38.172|109.112|8011|
[nlohmann](https://github.com/nlohmann/json)|26.441|16.689|2215|
[json11](https://github.com/dropbox/json11)|23.526|19.917|9140|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|7.968|2.574|2168|Uses custom floating point conversion
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|76.325|23.453|11057|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|412.734|51.203|5213|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|7.752|94.203|2956|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

