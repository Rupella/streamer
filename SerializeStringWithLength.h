#ifndef SERIALIZESTRINGWITHLENGTH_H
#define SERIALIZESTRINGWITHLENGTH_H

#include "DriverStream.hpp"
#include <string>
template <class Type = unsigned long>
class SerializeStringWithLength
{
protected:
    template< typename S>
    void serialize( DriverStream<S>& stream, const std::string& strToInject ) const {
        Type len = strToInject.length();
        stream << len;

        for ( int idx = 0 ; idx < strToInject.length() ; idx++ ) 
        {
           stream << strToInject[idx];
        }
    }

    template< typename S>
    std::string deserialize(DriverStream<S>& stream) const {
       Type length = 0;
       stream >> length;
       std::string strToReturn;

       char c = 0;
       do {
          stream >> c;
          strToReturn.push_back(c);
       } while (--length > 0);

       return strToReturn;
    }
};

#endif /* SERIALIZESTRINGWITHLENGTH_H */