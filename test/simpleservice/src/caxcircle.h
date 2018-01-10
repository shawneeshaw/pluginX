#ifndef CAXCIRCLE_H
#define CAXCIRCLE_H

class caxCircle : public caxShape {
public:
    /** create instance */
    static caxCircle * New();

public:
    /** draw something */
    virtual void DrawSomething();

protected:    
    //constructor
    caxCircle() {}

    //destructor.
    virtual ~caxCircle() {}
};

#endif //CAXCIRCLE_H
