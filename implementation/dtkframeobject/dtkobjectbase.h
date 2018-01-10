#ifndef DTKOBJECTBASE_H
#define DTKOBJECTBASE_H

class dtkObjectBase {
public:
    /** delete object directly, dangerously. */
    virtual void Delete();

    /** increase reference count. */
    virtual unsigned long AddReference();

    /** decrease reference count, if reference count == 0, then destroy this object. */
    virtual unsigned long Release();

    /** get the current reference count. */
    virtual unsigned long GetReference();

protected:
    // constructor.
    dtkObjectBase() { this->ReferenceCount = 1; }

    // destructor.
    virtual ~dtkObjectBase() { assert(this->ReferenceCount == 0); }

private:
    // reference count.
    unsigned long ReferenceCount;
};

//-----------------------------------------------------------------------------
inline void dtkObjectBase::Delete() {
    delete this;
}

//-----------------------------------------------------------------------------
inline unsigned long dtkObjectBase::GetReference() {
    return this->ReferenceCount;
}

//-----------------------------------------------------------------------------
inline unsigned long dtkObjectBase::AddReference() {
    this->ReferenceCount++;
    return this->ReferenceCount;
}

//-----------------------------------------------------------------------------
inline unsigned long dtkObjectBase::Release() {
    this->ReferenceCount--;
    if (this->ReferenceCount == 0) {
        delete this;
        return 0;
    }
    return this->ReferenceCount;
}

#endif //DTKOBJECTBASE_H
