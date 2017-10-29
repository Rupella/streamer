#include <string>
#include <iostream>
#include <iomanip>

#include "DriverStream.hpp"
#include "SerializeStringWithLength.h"
#include "SerializeStringWithZero.h"
typedef DriverStream<SerializeStringWithLength<unsigned long> > CDriverStreamWithLength;
typedef DriverStream<SerializeStringWithZero > CDriverStreamWithZero;

int main(int argc, char *argv[])
{

    char state = 1;
    std::string version = "1.53";
    unsigned short nb_scenario = 24561;
    unsigned long play_time = 465132154;
    CDriverStreamWithLength stream;

    stream << state << version << nb_scenario << play_time;

    for (unsigned int index = 0; index < stream.size(); ++index)
    {
       unsigned char c = stream.at(index);
       std::cout << std::setw(2) << std::setfill('0') << std::hex << (unsigned short)c << " ";
    }
    std::cout << std::endl;

    return 0;
}
