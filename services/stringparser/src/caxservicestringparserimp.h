#ifndef CPLSERVICESTRINGPARSERIMP_H
#define CPLSERVICESTRINGPARSERIMP_H

class caxServiceStringParserImp : public caxServiceStringParser {

public:
    /** create instance */
    static caxServiceStringParserImp * New();

public:
    /** parse string */
    virtual const char* Parse(const char* buff);

protected:    
    //constructor
    caxServiceStringParserImp() {}

    //destructor.
    virtual ~caxServiceStringParserImp() {}
};

#endif //CPLSERVICESTRINGPARSERIMP_H
