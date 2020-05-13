
## Read and Write Time Comparison


Input filename|Size (MB)|Content
---|---|---
data/output/persons_fp.json|697.35|Text,doubles

Environment|Windows, Intel
---|---
Computer|Dell Mobile Precision 2015, Intel Xeon E3-1535M v5, 32GB memory, 1TB SSD
Operating system|Windows 2010
Compiler|Visual Studio 2019

Library|Version
---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|0.151.0
[nlohmann](https://github.com/nlohmann/json)|3.7.3
[cJSON](https://github.com/DaveGamble/cJSON)|2019-11-30
[json11](https://github.com/dropbox/json11)|2017-06-20-2
[rapidjson](https://github.com/miloyip/rapidjson)|2020-02-08
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|1.9.2
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|4.1.0-1
[taojson](https://github.com/taocpp/json)|2019-07-11

Library|Time to read (s)|Time to write (s)|Memory footprint of json value (MB)|Remarks
---|---|---|---|---
[jsoncons](https://github.com/danielaparker/jsoncons)|16.39|8.161|1057|
Uses sorted `std::vector` of key/value pairs for objects, expect smaller memory footprint.
Uses slightly modified [grisu3_59_56 implementation by Florian Loitsch](https://florian.loitsch.com/publications) 
plus fallback for printing doubles, expect faster serializing.
    
[nlohmann](https://github.com/nlohmann/json)|19.987|14.841|1236|
Uses `std::map` for objects.
Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
    
[cJSON](https://github.com/DaveGamble/cJSON)|19.606|51.287|5813|
Inefficient storage (items do not share the same space), expect larger memory footprint. 
Uses sprintf and sscanf to support locale-independent round-trip.
    
[json11](https://github.com/dropbox/json11)|19.097|34.488|4918|
Uses pimpl idiom, implementation uses virtual inheritance, expect larger memory footprint.
    
[rapidjson](https://github.com/miloyip/rapidjson)|4.155|5.401|1098|
Uses custom floating point parsing, expect faster parsing. 
Uses girsu3 for printing doubles, expect faster serializing. 
Uses custom allocation and flat map for objects, expect smaller memory footprint.
    
[jsoncpp](https://github.com/open-source-parsers/jsoncpp)|84.761|47.614|6164|
Uses std::map for both arrays and objects, expect larger memory footprint.
    
[json_spirit](http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented)|263.005|60.941|2603|
Uses Boost spirit parsing, expect slower parsing.
    
[taojson](https://github.com/taocpp/json)|24.671|10.341|2712|
Uses modified [google/double conversion](https://github.com/google/double-conversion) routines for parsing doubles.
Uses modified [jeaiii/itoa](https://github.com/jeaiii/itoa) routines for outputting integers.
Uses slightly modified [Grisu2 implementation by Florian Loitsch](https://florian.loitsch.com/publications) for printing doubles, expect faster serializing.
    

