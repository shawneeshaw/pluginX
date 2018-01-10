#ifndef CAXSIMPLESERVICE_H
#define CAXSIMPLESERVICE_H

class caxShape : public caxService { 
public:
    /** create instance */
    static caxShape * New();

public:
    /** draw something */
    virtual void DrawSomething() = 0;

protected:    
    //constructor
    caxShape() {}

    //destructor.
    virtual ~caxShape() {}
};

//-------------------------------------------------------------------------
inline caxShape * caxShape::New() {
    caxShape* pObj = NULL;
    cpl_createObject("07559FD3-E558-44ad-A2D3-7658BB8DADEC", (void**)&pObj, 1);
    return pObj;
}

#endif //CAXSIMPLESERVICE_H
