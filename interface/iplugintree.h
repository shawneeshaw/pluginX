#ifndef DTKPLUGINTREEINTERFACE_H
#define DTKPLUGINTREEINTERFACE_H

class IPluginTree {
public:
    /** get node in specific path */
    virtual IPluginTreePath* GetTreePath(const char* path) = 0;
};

#endif //DTKPLUGINTREEINTERFACE_H
