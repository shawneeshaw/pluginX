#ifndef DTKPLUGINTREEPATHINTERFACE_H
#define DTKPLUGINTREEPATHINTERFACE_H

class IPluginTreePath : public IPluginTreeNode {
public:
    /** allocate. */
    virtual int Allocate(int sz, int ext) = 0;

    /** insert node */
    virtual int InsertNextItem(IPluginTreeNode* node) = 0;
    
    /** remove node */
    virtual int RemoveItem(IPluginTreeNode* node) = 0;
    
    /** remove all node */
    virtual int RemoveAllItems() = 0;

    /** get number of node. */
    virtual int GetNumberOfItems() = 0;
    
    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestItems() = 0;

    /** get specific position plugin */
    virtual IPluginTreeNode* GetItem(int subID) = 0;

    /** get specific plugin by name*/
    virtual IPluginTreeNode* GetItem(char* subID) = 0;

    /** get specific plugin by codon*/
    virtual IPluginTreeNode* GetItem(IPluginCodon* subID) = 0;
};

#endif //DTKPLUGINTREEPATHINTERFACE_H
