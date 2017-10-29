#pragma once

#include "DriverStream.hpp"

class CrcSmsp
{
protected:
	template< typename S>
	unsigned long crc( const DriverStream<S>& stream ) const {

		//const QByteArray& data = stream.getData();
		unsigned long crc = 0xffff;
		//for ( int index = 0 ; index < data.length() ; ++index ) {
		//	quint8 car = data.at( index );
		//	int i;
		//	unsigned int c;
		//	c = car & 0xff;
		//	for ( i = 0 ; i < 8 ; i++ ) {
		//		if ( ( c ^ crc ) & 0x0001 ) {
		//			crc >>= 1;
		//			crc ^= 0x8408;
		//		} 
		//		else {
		//			crc >>= 1;
		//		}
		//		c >>= 1;
		//	} 
		//}
		crc ^= 0xffff;
		return crc;
	}
};
