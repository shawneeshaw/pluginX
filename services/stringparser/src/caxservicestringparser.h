#ifndef CPLSERVICESTRINGPARSER_H
#define CPLSERVICESTRINGPARSER_H

class caxServiceStringParser : public caxService { 
public:
    /** create instance */
    static caxServiceStringParser * New();

public:
    /** parse string */
    virtual const char* Parse(const char* buff) = 0;

protected:    
    //constructor
    caxServiceStringParser() {}

    //destructor.
    virtual ~caxServiceStringParser() {}
};

//-------------------------------------------------------------------------
inline caxServiceStringParser * caxServiceStringParser::New() {
    caxServiceStringParser* pObj = NULL;
    cpl_createObject("3C561AE4-0912-43bb-8CF0-AFB88E7927BD", (void**)&pObj,  1);
    return pObj;
}

#endif //CPLSERVICESTRINGPARSER_H
