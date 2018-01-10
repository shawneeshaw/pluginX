#ifndef CAXSERVICE_H
#define CAXSERVICE_H

class caxService: public IService, public caxObject {
public:
    /** initialize service */
    virtual void InitializeService() {}

    /** unload service */
    virtual void UnloadService() {}	

protected:
    // constructor.
    caxService() {}

    // destructor.
    virtual ~caxService() {}
};

#endif //CAXSERVICE_H
