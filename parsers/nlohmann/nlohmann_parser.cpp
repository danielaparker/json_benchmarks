#include <fstream>
#include "nlohmann/json.hpp"
using namespace nlohmann;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }
    try
    {
        nlohmann::json val;
        std::ifstream is(argv[1]);
        is >> val;
        return 0;
    }
    catch (const std::exception&)
    {
        return 1;
    }
}
