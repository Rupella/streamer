#pragma once

#include "DriverStream.hpp"

class CrcTx8000
{
protected:
	template< typename S, typename D>
	unsigned long crc( const DriverStream<S>& stream ) const {

		unsigned long i;
		unsigned char t0=0;
		unsigned char t1=0;
		//const QByteArray& data = stream.getData();
		//for ( int index = 0 ; index < data.length() ; ++index ) {
		//	qint8 car = data.at( index );
		//	t0 += car;
		//	t1 += t0;
		//}
		return (-(t0+t1)<<8)+t1;
	}
};

