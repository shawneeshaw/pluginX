#ifndef DTKSERVICEINTERFACE_H
#define DTKSERVICEINTERFACE_H

class IService {
public:
    /** initialize service */
    virtual void InitializeService() = 0;

    /** unload service */
    virtual void UnloadService() = 0;
};

#endif //DTKSERVICEINTERFACE_H
