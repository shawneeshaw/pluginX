#ifndef CPLSERVICESAYHELLO_H
#define CPLSERVICESAYHELLO_H

class caxServiceStringSayHello : public caxService {

public:
    /** create instance */
    static caxServiceStringSayHello * New();

public:
    /** parse string */
    virtual const char* Parse(const char* buff);

protected:    
    //constructor
    caxServiceStringSayHello() {}

    //destructor.
    virtual ~caxServiceStringSayHello() {}
};

#endif //CPLSERVICESTRINGPARSERIMP_H
