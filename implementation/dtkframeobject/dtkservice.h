#ifndef DTKSERVICE_H
#define DTKSERVICE_H

class dtkService: public IService, public dtkObject {
public:
    /** initialize service */
    virtual void InitializeService() {}

    /** unload service */
    virtual void UnloadService() {}	

protected:
    // constructor.
    dtkService() {}

    // destructor.
    virtual ~dtkService() {}
};

#endif //DTKSERVICE_H
