#include <fstream>
#include <chrono>
#include <iostream>
#include <tao/json.hpp>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }
    try
    {        
        std::fstream is(argv[1]);
        try
        {
            tao::json::value val = tao::json::from_stream(is, argv[1]);
            return 0;
        }
        catch (...)
        {
            return 1;
        }
    }
    catch (...)
    {
        return 1;
    }
}
