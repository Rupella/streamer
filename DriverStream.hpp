#ifndef DRIVERSTREAM_HPP
#define DRIVERSTREAM_HPP
#include <vector>
#include <string>

template< typename StringSerializer>
class DriverStream : private StringSerializer
{
    typedef typename DriverStream< StringSerializer > Stream;
    using StringSerializer::serialize;
    using StringSerializer::deserialize;

    /************************************************************************/
    /* Ctor/Dtor                                                            */
    /************************************************************************/
public:
    DriverStream();
    ~DriverStream() {}

    /************************************************************************/
    /* Extraction methods                                                   */
    /************************************************************************/
public:
    Stream& operator>>( char & t )           { t = unmarshallint8();   return *this; } 
    Stream& operator>>( unsigned char & t )  { t = unmarshalluint8();  return *this; } 
    Stream& operator>>( short & t )          { t = unmarshallint16();  return *this; } 
    Stream& operator>>( unsigned short & t ) { t = unmarshalluint16(); return *this; } 
    Stream& operator>>( long & t )           { t = unmarshallint32();  return *this; } 
    Stream& operator>>( unsigned long & t )  { t = unmarshalluint32(); return *this; } 
    Stream& operator>>( std::string& t  )    { t = unmarshallstring(); return *this; }

    /************************************************************************/
    /* Injection methods                                                    */
    /************************************************************************/
public:
    Stream& operator<<( const char & t )            { marshall( t ); return *this; }
    Stream& operator<<( const unsigned char & t )   { marshall( t ); return *this; }
    Stream& operator<<( const short & t )           { marshall( t ); return *this; }
    Stream& operator<<( const unsigned short & t )  { marshall( t ); return *this; }
    Stream& operator<<( const long & t )            { marshall( t ); return *this; }
    Stream& operator<<( const unsigned long & t )   { marshall( t ); return *this; }
    Stream& operator<<( const std::string& t  )     { marshall( t ); return *this; }

    /************************************************************************/
    /* Utilities                                                            */
    /************************************************************************/
public:
    const std::vector<char>& getData() const                { return m_array;           }
    std::vector<char>&       getData()                      { return m_array; }
    unsigned long       size   () const                     { return m_array.size();    }
    bool                empty  () const                     { return m_array.isEmpty(); }
    void                append ( const std::vector<char>& array_ ) { m_array.append( array_ ); }
    void                clear  ()                           { m_array.clear();          }
    char                at( int pos )                       { return get( pos ); }
    const char          at( int pos ) const                 { return get( pos ); }
    unsigned long       crc() const;

    /************************************************************************/
    /* Iteration behavior                                                   */
    /************************************************************************/
protected:
    /**
     * Inner class that describes a const_iterator and 'regular' iterator at the same time, depending
     * on the bool template parameter (default: true - a const_iterator)
     */
    template<bool is_const_iterator = true>
    class const_noconst_iterator : public std::iterator<std::bidirectional_iterator_tag, char> {
        /**
         * For const_iterator:   define ContainerType to be a   const DriverStream*
         * For regular iterator: define ContainerType to be a   DriverStream*
         * For const_iterator:   define ValueType     to be a   const char&
         * For regular iterator: define ValueType     to be a   char&
         */
        typedef typename std::conditional<is_const_iterator, const DriverStream*, DriverStream*>::type ContainerType;
        typedef typename std::conditional<is_const_iterator, const char, char>::type ValueType;

    public:
        /**
         * Regular constructor: set up the iterator.
         */
        const_noconst_iterator( ContainerType pointer_to_datastructure, int pos )
            : m_datastructure( pointer_to_datastructure )
            , m_pos( pos ) 
        {}

        /**
         * Copy constructor. Allows for implicit conversion from a regular iterator to a const_iterator
         */
        const_noconst_iterator( const const_noconst_iterator<false>& other )
            : m_datastructure( other.m_datastructure ) 
            , m_pos( other.m_pos ) 
        {}

        /**
         * Equals comparison operator
         */
        bool operator== (const const_noconst_iterator& other) const { return m_pos == other.m_pos; }

        /**
         * Not-equals comparison operator
         * @see operator==(const const_noconst_iterator&) const
         */
        bool operator!= (const const_noconst_iterator& other) const { return !(*this == other); }

        /**
         * Dereference operator
         * @return the value of the element this iterator is currently pointing at
         */
        ValueType operator*() { return m_datastructure->get( m_pos ); }

        /**
         * Prefix decrement operator (e.g., --it)
         */
        const_noconst_iterator &operator--() { --m_pos; return *this; }

        /**
         * Postfix decrement operator (e.g., it--)
         */
        const_noconst_iterator operator--(int){
            const const_noconst_iterator old(*this);
            --(*this);
            return old;
        }

        /**
         * Prefix increment operator (e.g., ++it)
         */
        const_noconst_iterator &operator++() { ++m_pos; return *this; }

        /**
         * Postfix increment operator (e.g., it++)
         */
        const_noconst_iterator operator++(int){
            const const_noconst_iterator old(*this);
            ++(*this);
            return old;
        }

        /**
         * Make const_noconst_iterator<true> a friend class of const_noconst_iterator<false> so
         * the copy constructor can access the private member variables.
         */
        friend class const_noconst_iterator<true>;

    private:
        ContainerType m_datastructure;
        int           m_pos;

    }; // end of nested class const_noconst_iterator

public:
    /**
     * Shorthand for a regular iterator (non-const) and a constant iterator (const_iterator)
     */
    typedef const_noconst_iterator<false> iterator;
    typedef const_noconst_iterator<true> const_iterator;

    /**
     * Helpers to obtain a regular iterator (non-const) and a constant iterator (const_iterator)
     * Iterator is available both for usual iteration and for range-for iterations
     * e.g., for ( auto a : stream ) { ... }
     * consider using syntax : for ( const auto& a : stream ) { ... } to be sure to use const iterator
     */
    iterator        begin()       { return iterator      ( this, 0 ); }
    const_iterator  begin() const { return const_iterator( this, 0 ); }
    iterator        end  ()       { return iterator      ( this, m_array.size() ); }   
    const_iterator  end  () const { return const_iterator( this, m_array.size() ); }

    /************************************************************************/
    /* Private marshaling operations                                        */
    /************************************************************************/
private:
    void    marshall( const char&   );
    void    marshall( const unsigned char&  );
    void    marshall( const short&  );
    void    marshall( const unsigned short& );
    void    marshall( const long&  );
    void    marshall( const unsigned long& );
    void    marshall( const std::string& );

    /************************************************************************/
    /* Private un-marshaling operations                                     */
    /************************************************************************/
private:
    char   unmarshallint8();
    unsigned char  unmarshalluint8();
    short  unmarshallint16();
    unsigned short unmarshalluint16();
    long  unmarshallint32();
    unsigned long unmarshalluint32();
    std::string unmarshallstring();

    /************************************************************************/
    /* Unauthorized operations                                              */
    /************************************************************************/
private:
#if ( _MSC_VER >= 1800 )
    void    marshall(const long long&) = delete;
    void    marshall(const double&) = delete;
    long long  unmarshall( long long ) = delete;
    double   unmarshall( double ) = delete;
#else
    void    marshall(const long long&);
    void    marshall(const double&);
    long long  unmarshall( long long );
    double   unmarshall( double );
#endif

    /************************************************************************/
    /* Internal tool methods                                                */
    /************************************************************************/
private:

    /**
     * @brief swaps data in array in order to be convenient with endian-ness
     * @warning this function modifies the specified array
     * 
     * @param array : data to be swapped
     * @param size : size of array
     */
    void swap( char * array, int size );
    
    /**
     * @brief does the system is little endian or not
     * 
     * @return   bool
     */
    bool littleEndian();

    /**
     * get
     * @brief 
     * 
     * @param int pos
     * @return   const char
     */
    const char get( int pos ) const { return m_array[pos]; }
    char       get( int pos )       { return m_array[pos]; }

    /************************************************************************/
    /* Properties                                                           */
    /************************************************************************/
private:
    //! 
    bool        m_bSwapBytes;

    //! 
    std::vector<char>    m_array;

};

#include "DriverStream.inl"

#endif