#ifndef CPLSERVICEDATATPLENGINE_H
#define CPLSERVICEDATATPLENGINE_H

class caxServiceDataTPLEngine : public caxService { 
public:
    /** create instance */
    static caxServiceDataTPLEngine * New();

protected:    
    //constructor
    caxServiceDataTPLEngine() {}

    //destructor.
    virtual ~caxServiceDataTPLEngine() {}
};

//-------------------------------------------------------------------------
inline caxServiceDataTPLEngine * caxServiceDataTPLEngine::New() {
    caxServiceDataTPLEngine* pObj = NULL;
    cpl_createObject("285525E9-8410-43fa-BB7F-9F3A07AB9E67", (void**)&pObj,  1);
    return pObj;
}

#endif //CPLSERVICEDATATPLENGINE_H
