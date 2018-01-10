#ifndef DTKTIMESTAMP_H
#define DTKTIMESTAMP_H

/** Timpstamp, which is used to record modification and/or execution time. */
class dtkTimeStamp {

public:
    /** create instance */
    static dtkTimeStamp * New();

    /** delete itself. */
    void Delete() { delete this; };

    /** increase modification time */
    void Modified();

    /** return this object's modified time. */
    unsigned long int GetMTime() { return this->ModifiedTime; };

    /** support comparisons of time stamp objects directly. */
    int operator > (dtkTimeStamp & ts) { return (this->ModifiedTime > ts.ModifiedTime); };
    int operator < (dtkTimeStamp & ts) { return (this->ModifiedTime < ts.ModifiedTime); };

    /** allow for typecasting to unsigned long. */
    operator unsigned long() { return this->ModifiedTime; };

public:
    //constructor.
    dtkTimeStamp() { this->ModifiedTime = 0; };

private:
    unsigned long ModifiedTime;
};

#endif //DTKTIMESTAMP_H
