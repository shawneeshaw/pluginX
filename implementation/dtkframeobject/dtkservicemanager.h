#ifndef DTKSERVICEMANAGER_H
#define DTKSERVICEMANAGER_H

class dtkService;
class dtkServiceCollection;
class dtkServiceManager: public dtkObject {
public:
    /** create function */
    static dtkServiceManager * New();

public:
    /** initializes all service*/
    void InitializeAllServices();

    /** unload all services. */
    void UnloadAllServices();

    /** add service */
    void AddService(const char* key, dtkService* service, int priority = 0);
    
    /** remove service */
    void RemoveService(dtkService* service);

    /** get service */
    void GetService(const char* key, dtkService*& service);

protected:    
    // constructor 
    dtkServiceManager();

    // destructor 
    virtual ~dtkServiceManager();

    dtkServiceCollection* collection;
};

#endif //DTKSERVICEMANAGER_H
