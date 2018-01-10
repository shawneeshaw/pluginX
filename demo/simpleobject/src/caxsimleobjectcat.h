#ifndef CPLSIMPLEOBJECTCAT_H
#define CPLSIMPLEOBJECTCAT_H

//-------------------------------------------------------------------------
// class caxSimpleObjectCat
//-------------------------------------------------------------------------
//
class caxSimpleObjectCat : public caxSimpleObject {
public:
    /** create instance */
    static caxSimpleObjectCat * New();

public:
    /** show me.*/
    virtual void ShowMe();

protected:    
    //constructor
    caxSimpleObjectCat() {}

    //destructor.
    virtual ~caxSimpleObjectCat() {}
};


#endif //CPLSIMPLEOBJECTCAT_H
