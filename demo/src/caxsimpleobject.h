#ifndef CPLSIMPLEOBJECT_H
#define CPLSIMPLEOBJECT_H

class caxSimpleObject : public caxObject {

public:
    /** create instance */
    static caxSimpleObject * New();

public:
    /** show me.*/
    virtual void ShowMe() = 0;

protected:    
    //constructor
    caxSimpleObject() {}

    //destructor.
    virtual ~caxSimpleObject() {}
};

//-------------------------------------------------------------------------
inline caxSimpleObject * caxSimpleObject::New() {
    caxSimpleObject* pObj = NULL;
    cpl_createObject("caxSimpleObject", (void**)&pObj,  1);
    return pObj;
}

#endif //CPLSIMPLEOBJECT_H
