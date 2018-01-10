#ifndef DTKCREATOR_H
#define DTKCREATOR_H

class dtkImplementationProxyCollection;
class dtkCreator : public dtkObject {
public:
    /** create function */
    static dtkCreator * New();

public:
    /** create object */
    int CreateObject(REFDGUID clsId, void** ppv);

    /** create object */
    int CreateObject(const char* classId, void** ppv, int overrided = 1);
 
    /** insert implementation proxy */
    int InsertImplementationProxy(dtkImplementationProxy& proxy);

    /** remove implementation proxy */
    int RemoveImplementationProxy(dtkImplementationProxy& proxy);

public:
    /** add class override info */
    int InsertClassOverrideInfo(const char* classId, const char* newClassId);

    /** remove class override info */
    int RemoveClassOverrideInfo(const char* classId);

    /** find override info */
    int QueryClassOverrideInfo(const char* classId, const char*& newClassId);

protected:    
    // constructor 
    dtkCreator();

    // destructor 
    virtual ~dtkCreator();

    //protected variables.
    dtkHashTableStringOneKey* pClassOverrideInfo;
    dtkImplementationProxyCollection* ImplementionProxyCollection;   
};

#endif //DTKCREATOR_H
