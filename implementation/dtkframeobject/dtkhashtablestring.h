#ifndef DTKHASHTABLESTRING_H
#define DTKHASHTABLESTRING_H

/** implementation dependend declarations */
typedef int StringIdHashIndexType;

typedef struct {
    char id[64];
}StringIdKeyType;

/** user data stored in hash table */
typedef struct {
    char* stuff;
    StringIdKeyType inkey;
}
StringIdRecType;

/** implementation independent declarations */
typedef enum {
    STRID_STATUS_OK, STRID_STATUS_MEM_EXHAUSTED, STRID_STATUS_KEY_NOT_FOUND
}
StringIdStatusEnum;

typedef struct StringIdNodeTag {
    struct StringIdNodeTag * next; // next node
    StringIdKeyType key; // key
    StringIdRecType rec; // user data
}
StringIdNodeType;

typedef StringIdNodeType * StringIdNodeTypeP;

class dtkHashTableStringOneKey {

public:
    /** hash function */
    StringIdHashIndexType StringIdHashFunction(StringIdKeyType key) ;

    /** insert */
    StringIdStatusEnum StringIdInsert(StringIdKeyType key, StringIdRecType * rec);

    /** delete */
    StringIdStatusEnum StringIdDelete(StringIdKeyType key) ;

    /** find */
    StringIdStatusEnum StringIdFind(StringIdKeyType key, StringIdRecType * rec);

    /** initial */
    StringIdStatusEnum StringIdHashInit(int TableSize = 0);

    /** cleanup */
    StringIdStatusEnum StringIdHashClean();

    //constructor
    dtkHashTableStringOneKey(int tablesize = 1000) {
        this->StringIdHashTable = NULL;
        this->StringIdHashTableSize = tablesize;
        StringIdHashInit(tablesize);
    }

    //destructor
    virtual ~dtkHashTableStringOneKey() {
        StringIdHashClean();
    }

protected:

    //variables
    StringIdNodeType * * StringIdHashTable;
    int StringIdHashTableSize;
};

inline int compStrIdKeyType(StringIdKeyType key1, StringIdKeyType key2) { 
    if (strcmp(key1.id, key2.id) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

inline StringIdHashIndexType dtkHashTableStringOneKey::StringIdHashFunction(StringIdKeyType key) {
    StringIdHashIndexType h = 0;
    char* str = key.id;
    while (*str) { 
		int tmp = (*str); 
		if (tmp < 0) {tmp = -tmp; } 
		h += tmp;
		*str++;
	}
    return h % StringIdHashTableSize;    
}

inline StringIdStatusEnum dtkHashTableStringOneKey::StringIdInsert(StringIdKeyType key, StringIdRecType * rec) {
    StringIdNodeType * p, * p0;
    StringIdHashIndexType bucket;

    bucket = StringIdHashFunction(key);
    p =  new StringIdNodeType;
    if (p == NULL) {
        return STRID_STATUS_MEM_EXHAUSTED;
    }
    p0 = StringIdHashTable[bucket];
    StringIdHashTable[bucket] = p;
    p->next = p0;
    strcpy(p->key.id, key.id);
    p->rec.stuff = rec->stuff;
    strcpy(p->rec.inkey.id, rec->inkey.id);
    return STRID_STATUS_OK;
}

inline StringIdStatusEnum dtkHashTableStringOneKey::StringIdDelete(StringIdKeyType key) {
    StringIdNodeType * p0, * p;
    StringIdHashIndexType bucket;

    p0 = 0;
    bucket = StringIdHashFunction(key);
    p = StringIdHashTable[bucket];
    while (p && !compStrIdKeyType(p->rec.inkey, key)) {
        p0 = p;
        p = p->next;
    }

    if (!p) {
        return STRID_STATUS_KEY_NOT_FOUND;
    }

    if (p0) {
        p0->next = p->next;
    }
    else {
        StringIdHashTable[bucket] = p->next;
    }

    delete (p);
    return STRID_STATUS_OK;
}

inline StringIdStatusEnum dtkHashTableStringOneKey::StringIdFind(StringIdKeyType key, StringIdRecType * rec) {
    StringIdNodeType * p;

    p = StringIdHashTable[StringIdHashFunction(key)];
    while (p && !compStrIdKeyType(p->rec.inkey, key)) {
        p = p->next;
    }
    if (!p) {
        return STRID_STATUS_KEY_NOT_FOUND;
    }
    * rec = p->rec;
    return STRID_STATUS_OK;
}

inline StringIdStatusEnum dtkHashTableStringOneKey::StringIdHashInit(int TableSize) {
    //@@preconditions
    assert(TableSize > 0);
    //@@end precondtions

    int i;

    if (TableSize > 0) {
        StringIdHashTableSize = TableSize;
    }
    StringIdHashTable = new StringIdNodeTypeP[StringIdHashTableSize];
    if (StringIdHashTable == NULL) {
        return STRID_STATUS_MEM_EXHAUSTED;
    }

    for (i = 0; i < StringIdHashTableSize; i++) {
        StringIdHashTable[i] = NULL;
    }

    return STRID_STATUS_OK;
}

inline StringIdStatusEnum dtkHashTableStringOneKey::StringIdHashClean() {
    StringIdNodeType * p0, * p;
    int i = 0;
    for (i = 0; i < StringIdHashTableSize; i++) {
        p = StringIdHashTable[i];
        while (p) {
            p0 = p;
            p = p->next;
            if (p0) {
                if (p0->rec.stuff) {
                    delete[] p0->rec.stuff;
                }
                delete (p0);
                p0 = NULL;
            }
        }
    }
    if (StringIdHashTable) {
        delete[] StringIdHashTable;
    }
    StringIdHashTable = NULL;

    return STRID_STATUS_OK;
}

#endif //DTKHASHTABLESTRING_H
