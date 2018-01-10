#ifndef CAXOBJECTBASE_H
#define CAXOBJECTBASE_H

class caxObjectBase {
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
    caxObjectBase() { this->ReferenceCount = 1; }

    // destructor.
    virtual ~caxObjectBase() { assert(this->ReferenceCount == 0); }

private:
    // reference count.
    unsigned long ReferenceCount;
};

//-----------------------------------------------------------------------------
inline void caxObjectBase::Delete() {
    delete this;
}

//-----------------------------------------------------------------------------
inline unsigned long caxObjectBase::GetReference() {
    return this->ReferenceCount;
}

//-----------------------------------------------------------------------------
inline unsigned long caxObjectBase::AddReference() {
    this->ReferenceCount++;
    return this->ReferenceCount;
}

//-----------------------------------------------------------------------------
inline unsigned long caxObjectBase::Release() {
    this->ReferenceCount--;
    if (this->ReferenceCount == 0) {
        delete this;
        return 0;
    }
    return this->ReferenceCount;
}

#endif //CAXOBJECTBASE_H
