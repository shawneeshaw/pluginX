#ifndef DTKSTRING_H
#define DTKSTRING_H

class dtkString {
public:
    /** Default constructor: sets to empty string ("") */
    dtkString();

    /** Allocates the string to be of length \b len. Does not set the buffer to any initial value */
    dtkString( unsigned int len );

    /** String copy constructor */
    dtkString( const char *s );

    /** Copy constructor */
    dtkString( const dtkString& s );

    /** Default destructor */
    ~dtkString();

    /** copy operator */
    dtkString& operator =( const char *s );

    /** copy operator */
    dtkString& operator =( dtkString s );

    /** concatenate assignment operator */
    dtkString& operator +=( const char *s );

    /** concatenate assignment operator */
    dtkString& operator +=( const dtkString& s );

    /** return the indicated substring of this string */
    dtkString substr( int pos, int len ) const;

public:
    /** a c-style nul terminated pointer to the string */
    char* operator() ();

    /** a c-style nul terminated pointer to the string */
    const char* c_str() const;

    /** array operator */
    char& operator [](int i);

    /** array operator */
    char  operator [](int i) const;

    /** alias for the = operator */
    void copy( const dtkString& s );

    /** alias for the = operator */
    void copy( const char *s );

    /** convert this string to uppercase */
    void upcase();

    /** convert this string to lowercase */
    void downcase();

    /** character c to the end of the string */
    void push_back( char c );

    /** copy the substring of s to this string */
    void copy( const dtkString& s, unsigned int start, unsigned int len ) ;

    /** copy the substring of s to this string */
    void copy( const char *s, unsigned int start, unsigned int len );

    /** how long the string is */
    int size() const;

    /** return the first index of character c in this string, or -1 if c is not in this string */
    int find( char c ) const;

    /** return the first index of character c in this string, or -1 if c is not in this string */
    int find( char c, int pos) const;

    /** return the last index of character c in this string, or -1 if c is not in this string */
    int rfind( char c ) const;

    /** return 0 if this string is equal to s, -1 if this string is lexigraphically less than \b s, 1 if this string is lexigraphically greater than s (uses c-std function strcmp ) */
    int compare( const dtkString &s ) const;

    /** same as compare(), except ignores the case of the string */
    int casecompare( const dtkString &s ) const;

    /** less-than operator */
    bool operator <( const dtkString& s ) const;

    /** greater-than operator */
    bool operator >( const dtkString& s ) const;

    /** equality operator */
    bool operator ==( const dtkString& s ) const;

    /** inequality operator */
    bool operator !=( const dtkString& s ) const;

private:
    char *str;
};

#endif //DTKSTRING_H


