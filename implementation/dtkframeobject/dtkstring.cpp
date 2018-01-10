#include "dtkframeobjectincludes.h"

//-------------------------------------------------------------------------
static char *strnew(const char *val) {
    if ( val == NULL ) return(NULL);
    char *s = (char*)malloc(strlen(val)+1);
    strcpy(s, val);
    return(s);
}

//-------------------------------------------------------------------------
// class dtkString
//-------------------------------------------------------------------------
//
dtkString::dtkString() {
    this->str = strnew("");
}

//-------------------------------------------------------------------------
dtkString::dtkString( unsigned int len ) {
    if (len > 0) {
        this->str = (char*)malloc( len );
    }
    else {
        this->str = strnew("");
    }    
}

//-------------------------------------------------------------------------
dtkString::dtkString( const char *s ) {
    this->str = strnew("");
   *this = s;
}

//-------------------------------------------------------------------------
dtkString::dtkString( const dtkString & s ) {
    this->str = strnew("");
   *this = s.str;
}

//-------------------------------------------------------------------------
dtkString::~dtkString() {
    if (this->str != NULL) {
        free(this->str);
        this->str = NULL;
    }    
}

//-------------------------------------------------------------------------
void dtkString::copy(const char * s, unsigned int start, unsigned int len ) {
    if (s == 0) return;
    if (len == 0) return;
    if (start+len > strlen(s) ) return;
    if (this->str) free(this->str);
    this->str = (char*)malloc( len+1 );
    strncpy(this->str, s+start, len );
    this->str[len] = '\0';
}

//-------------------------------------------------------------------------
int dtkString::compare(const dtkString &s) const {
    return strcmp(this->str, s.str );
}

//-------------------------------------------------------------------------
int dtkString::casecompare(const dtkString &s) const {
    dtkString s1(str), s2(s);
    s1.upcase();
    s2.upcase();
    return strcmp( s1.str, s2.str );
}

//-------------------------------------------------------------------------
void dtkString::upcase() {
    unsigned int l = strlen(this->str);
    for(unsigned int i = 0; i < l; i++ ) {
        str[i] = (char)toupper((int)str[i]);
    }    
}

//-------------------------------------------------------------------------
void dtkString::downcase() {
    unsigned int l = strlen(this->str);
    for(unsigned int i = 0; i < l; i++ ) {
        this->str[i] = (char)tolower((int)this->str[i]);
    }    
}

//-------------------------------------------------------------------------
int dtkString :: find(char c) const {
    const char *i = strchr(str, c);
    if( !i ) {
        return -1;
    }    
    else {
        return i-str;
    }    
}

//-------------------------------------------------------------------------
int dtkString::find(char c, int pos) const {
    if (pos > this->size()) {
        return -1;
    }
    const char *i = strchr(&str[pos], c);
    if( !i ) {
        return -1;
    }    
    else {
        return i-str;
    }    
}

//-------------------------------------------------------------------------
int dtkString::rfind(char c) const {
    const char *i = strrchr(str, c);
    if ( !i ) {
        return -1;
    }    
    else {
        return i-str;
    }    
}

//-------------------------------------------------------------------------
dtkString dtkString::substr(int pos, int len) const {
    if ((pos+len) <= 0 || (pos+len) > size()) {
        return dtkString("");
    }    
    else {
        char *buf = (char*)malloc(len+1);
        strncpy( buf, str+pos, len );
        buf[len] = '\0';
        dtkString s = buf;
        free( buf );
        return s;
    }
}

//-------------------------------------------------------------------------
dtkString& dtkString::operator =(const char *s) { 
    char* tmp;
    if (s == 0) {
        tmp = strnew("");
    }    
    else {
        tmp = strnew(s);
    }    
    if (this->str != NULL) {
        free(this->str);
    }    
    this->str = tmp;
    return *this;
}

//-------------------------------------------------------------------------
dtkString& dtkString::operator += (const char *s) {
    if (s == 0) {
        s = "";
    }    
    char *old = strnew(this->str);
    int lold = strlen(old), ls = strlen(s);
    free(this->str);
    this->str = (char*)malloc( lold + ls + 1 );
    memcpy(this->str, old, lold );
    memcpy(this->str+lold, s, ls );
    this->str[lold+ls] = '\0';
    free(old);
    return *this;
}

//-------------------------------------------------------------------------
char* dtkString::operator() () { 
    return str; 
}

//-------------------------------------------------------------------------
const char* dtkString::c_str() const { 
    return str; 
}

//-------------------------------------------------------------------------
char& dtkString::operator [](int i) { 
    return str[i]; 
}

//-------------------------------------------------------------------------
char  dtkString::operator [](int i) const { 
    return str[i]; 
}

//-------------------------------------------------------------------------
void dtkString::copy(const dtkString& s) { 
    *this = s; 
}

//-------------------------------------------------------------------------
void dtkString::copy(const char *s) { 
    *this = s; 
}

//-------------------------------------------------------------------------
void dtkString::push_back(char c) { 
     char s[2] = { c, '\0' }; 
    *this += s; 
}

//-------------------------------------------------------------------------
void dtkString::copy(const dtkString& s, unsigned int start, unsigned int len) { 
    copy( s.c_str(), start, len ); 
}

//-------------------------------------------------------------------------
int dtkString::size() const { 
    return strlen(str); 
}

//-------------------------------------------------------------------------
bool dtkString::operator < (const dtkString& s) const { 
    return (strcmp(str, s.str) < 0); 
}

//-------------------------------------------------------------------------
bool dtkString::operator > (const dtkString& s) const {
    return (strcmp(str, s.str) > 0); 
}

//-------------------------------------------------------------------------
bool dtkString::operator == (const dtkString& s) const { 
    return (strcmp(str, s.str) == 0); 
}

//-------------------------------------------------------------------------
bool dtkString::operator != (const dtkString& s) const { 
    return (strcmp(str, s.str) != 0); 
}

//-------------------------------------------------------------------------
dtkString& dtkString::operator += (const dtkString& s) { 
    *this += s.str; return *this; 
}

//-------------------------------------------------------------------------
dtkString& dtkString::operator = (dtkString s) {
     return (*this = s.str); 
}
