/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
DriverStream< StringSerializer >::DriverStream()
    : m_bSwapBytes(true)
{
    // config param ?
    bool myByteOrder = true;
    //m_bSwapBytes = littleEndian() == myByteOrder ? false : true;
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::marshall( const char & c ) {
    m_array.push_back( c );
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::marshall( const unsigned char & c ) {
    m_array.push_back( c );
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::marshall( const short & c ) {

    char array[2];
    array[0] =  ( c & 0x00ff );
    array[1] = (( c & 0xff00 ) >> 8 );
    swap( array, 2 );

    m_array.push_back( array[0] );
    m_array.push_back( array[1] );

}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::marshall( const unsigned short & c ) {
    char array[2];
    array[0] =  ( c & 0x00ff );
    array[1] = (( c & 0xff00 ) >> 8 );
    swap( array, 2 );

    m_array.push_back( array[0] );
    m_array.push_back( array[1] );

}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::marshall( const long&  i ) {

    char array[4];
    array[0] = ( i & 0x000000ff );
    array[1] = (( i & 0x0000ff00 ) >> 8 );
    array[2] = (( i & 0x00ff0000 ) >> 16 );
    array[3] = (( i & 0xff000000 ) >> 24 );
    swap( array, 4 );

    m_array.push_back( array[0] );
    m_array.push_back( array[1] );
    m_array.push_back( array[2] );
    m_array.push_back( array[3] );

}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::marshall( const unsigned long&  i ) {

    char array[4];
    array[0] = ( i & 0x000000ff );
    array[1] = (( i & 0x0000ff00 ) >> 8 );
    array[2] = (( i & 0x00ff0000 ) >> 16 );
    array[3] = (( i & 0xff000000 ) >> 24 );
    swap( array, 4 );

    m_array.push_back( array[0] );
    m_array.push_back( array[1] );
    m_array.push_back( array[2] );
    m_array.push_back( array[3] );

}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::marshall( const std::string&  strToInject ) {

    serialize( *this, strToInject );
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
char DriverStream< StringSerializer >::unmarshallint8() {
    char c = m_array[0];
    m_array.erase(m_array.begin(), m_array.begin() + 1);
    return c;
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
unsigned char DriverStream< StringSerializer >::unmarshalluint8() {
    unsigned char c = m_array[0];
    m_array.erase(m_array.begin(), m_array.begin() + 1);
    return c;
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
short DriverStream< StringSerializer >::unmarshallint16() {

    char array[2];
    array[0] = m_array[0];
    array[1] = m_array[1];
    m_array.erase(m_array.begin(), m_array.begin() + 2);
    swap( array, 2 );

    return (short)  ( ((((short) array[0])      ) & 0x00ff)
                    | ((((short) array[1]) << 8 ) & 0xff00) );

}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
unsigned short DriverStream< StringSerializer >::unmarshalluint16() {

    char array[2];
    array[0] = m_array[0];
    array[1] = m_array[1];
    m_array.erase(m_array.begin(), m_array.begin() + 2);
    swap( array, 2 );

    return (unsigned short)  ( ((((unsigned short) array[0])      ) & 0x00ff)
                             | ((((unsigned short) array[1]) << 8 ) & 0xff00) );

}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
long DriverStream< StringSerializer >::unmarshallint32() {

    char array[4];
    array[0] = m_array[0];
    array[1] = m_array[1];
    array[2] = m_array[2];
    array[3] = m_array[3];
    m_array.erase(m_array.begin(), m_array.begin() + 4);
    swap( array, 4 );

    return (long)  ( ((((long) array[0])      ) & 0x000000ff)
                   | ((((long) array[1]) << 8 ) & 0x0000ff00)
                   | ((((long) array[2]) << 16) & 0x00ff0000)
                   | ((((long) array[3]) << 24) & 0xff000000) );
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
unsigned long DriverStream< StringSerializer >::unmarshalluint32() {

    char array[4];
    array[0] = m_array[0];
    array[1] = m_array[1];
    array[2] = m_array[2];
    array[3] = m_array[3];
    m_array.erase(m_array.begin(), m_array.begin() + 4);
    swap( array, 4 );

    return (unsigned long)  ( ((((long) array[0])      ) & 0x000000ff)
                            | ((((long) array[1]) << 8 ) & 0x0000ff00)
                            | ((((long) array[2]) << 16) & 0x00ff0000)
                            | ((((long) array[3]) << 24) & 0xff000000) );
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
std::string DriverStream< StringSerializer >::unmarshallstring() {

    return deserialize( *this );
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
bool DriverStream< StringSerializer >::littleEndian() {
    static int num = 1;
    if(*(char *)&num == 1) return true; 
    return false;
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
void DriverStream< StringSerializer >::swap( char * array, int size ) {
    if ( m_bSwapBytes ) {
        std::reverse(array, array + size);
    }
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
template<typename StringSerializer >
unsigned long	DriverStream< StringSerializer >::crc() const {
  //return CrcCalc::crc(*this);
  return 0;
}