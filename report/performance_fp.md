
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|697.35|Text,doubles

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
[jsoncons](https://github.com/danielaparker/jsoncons)|17.881|7.862|1047|Uses girsu3 for printing floating-point numbers.
[cjson](https://github.com/DaveGamble/cJSON)|28.657|51.213|4855|Expect larger size because of inefficient storage.
[nlohmann](https://github.com/nlohmann/json)|28.95|13.678|1189|Uses girsu2 for printing floating-point numbers.
[json11](https://github.com/dropbox/json11)|23.892|40.378|4887|Uses pimpl idiom, implementation uses virtual inheritance
[rapidjson](https://github.com/miloyip/rapidjson)|6.379|7.25|1048|Uses custom floating point parsing, girsu3 for printing floating-point numbers.
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|59.065|60.588|6162|Uses std::map for both arrays and objects
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|295.107|60.147|3499|Boost spirit parsing is slow
[gason](https://github.com/vivkin/gason)|3.722|51.139|1736|Uses naive floating point conversion, fast but inaccurate. No serialization function, using sample pretty-print code

