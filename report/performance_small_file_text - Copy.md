
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
[jsoncons](https://github.com/danielaparker/jsoncons)|master20180126
[cJSON](https://github.com/DaveGamble/cJSON)|1.7.1

Library|Time to read (milliseconds)|Time to write (milliseconds)|Memory footprint of json value (bytes)|Remarks
---|---|---|---|---
