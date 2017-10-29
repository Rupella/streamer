#ifndef SERIALIZESTRINGWITHZERO_H
#define SERIALIZESTRINGWITHZERO_H

#include "DriverStream.hpp"
#include <string>

class SerializeStringWithZero
{
protected:
    template< typename S>
    void serialize( DriverStream<S>& stream, const std::string& strToInject ) const {

        for ( int idx = 0 ; idx < strToInject.length() ; idx++ ) 
        {
           stream << strToInject[idx];
        }
        stream << '\0';
    }

    template< typename S>
    std::string deserialize(DriverStream<S>& stream) const {

       std::string strToReturn;
       std::vector<char>& array = stream.getData();
       char c = 0;
       do {
          stream >> c;
          strToReturn.push_back(c);
       } while (c != 0);

       return strToReturn;
    }
};

#endif /* SERIALIZESTRINGWITHZERO_H */