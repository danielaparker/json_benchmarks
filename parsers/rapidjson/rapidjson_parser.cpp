#include <fstream>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"

using namespace rapidjson;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }
    try
    {
        Document doc;
        FILE* fp = fopen(argv[1], "rb"); // non-Windows use "r"
        std::vector<char> readBuffer;
        readBuffer.resize(65536);
        FileReadStream is(fp, readBuffer.data(), readBuffer.size());
        ParseResult ok = doc.ParseStream(is);
        if (!ok)
        {
            return 1;
        }
        return 0;
    }
    catch (const std::exception&)
    {
        return 1;
    }
}
