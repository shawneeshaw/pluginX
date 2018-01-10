#ifndef DTKHASHTABLEOBJECT_H
#define DTKHASHTABLEOBJECT_H

/** implementation dependend declarations */
typedef int ObjectIdHashIndexType;

typedef struct {
    char id[64];
}ObjectIdKeyType;

/** user data stored in hash table */
typedef struct {
    dtkObject* stuff;
    ObjectIdKeyType inkey;
}
ObjectIdRecType;

/** implementation independent declarations */
typedef enum {
    OBJID_STATUS_OK, OBJID_STATUS_MEM_EXHAUSTED, OBJID_STATUS_KEY_NOT_FOUND
}
ObjectIdStatusEnum;

typedef struct ObjectIdNodeTag {
    struct ObjectIdNodeTag * next; // next node
    ObjectIdKeyType key; // key
    ObjectIdRecType rec; // user data
}
ObjectIdNodeType;

typedef ObjectIdNodeType * ObjectIdNodeTypeP;

class dtkObjectHashTableStringOneKey {

public:
    /** hash function */
    ObjectIdHashIndexType ObjectIdHashFunction(ObjectIdKeyType key) ;

    /** insert */
    ObjectIdStatusEnum ObjectIdInsert(ObjectIdKeyType key, ObjectIdRecType * rec);

    /** delete */
    ObjectIdStatusEnum ObjectIdDelete(ObjectIdKeyType key) ;

    /** find */
    ObjectIdStatusEnum ObjectIdFind(ObjectIdKeyType key, ObjectIdRecType * rec);

    /** initial */
    ObjectIdStatusEnum ObjectIdHashInit(int TableSize = 0);

    /** cleanup */
    ObjectIdStatusEnum ObjectIdHashClean();

    //constructor
    dtkObjectHashTableStringOneKey(int tablesize = 1000) {
        this->ObjectIdHashTable = NULL;
        this->ObjectIdHashTableSize = tablesize;
        ObjectIdHashInit(tablesize);
    }

    //destructor
    virtual ~dtkObjectHashTableStringOneKey() {
        ObjectIdHashClean();
    }

protected:

    //variables
    ObjectIdNodeType * * ObjectIdHashTable;
    int ObjectIdHashTableSize;
};

inline int compStrIdKeyType(ObjectIdKeyType key1, ObjectIdKeyType key2) { 
    if (strcmp(key1.id, key2.id) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

inline ObjectIdHashIndexType dtkObjectHashTableStringOneKey::ObjectIdHashFunction(ObjectIdKeyType key) {
    ObjectIdHashIndexType h = 0;
    char* str = key.id;
    while (*str) { 
		int tmp = (*str); 
		if (tmp < 0) {tmp = -tmp; } 
		h += tmp;
		*str++;
	}
    return h % ObjectIdHashTableSize;    
}

inline ObjectIdStatusEnum dtkObjectHashTableStringOneKey::ObjectIdInsert(ObjectIdKeyType key, ObjectIdRecType * rec) {
    ObjectIdNodeType * p, * p0;
    ObjectIdHashIndexType bucket;

    bucket = ObjectIdHashFunction(key);
    p =  new ObjectIdNodeType;
    if (p == NULL) {
        return OBJID_STATUS_MEM_EXHAUSTED;
    }
    p0 = ObjectIdHashTable[bucket];
    ObjectIdHashTable[bucket] = p;
    p->next = p0;
    strcpy(p->key.id, key.id);
    p->rec.stuff = rec->stuff;
    strcpy(p->rec.inkey.id, rec->inkey.id);
    return OBJID_STATUS_OK;
}

inline ObjectIdStatusEnum dtkObjectHashTableStringOneKey::ObjectIdDelete(ObjectIdKeyType key) {
    ObjectIdNodeType * p0, * p;
    ObjectIdHashIndexType bucket;

    p0 = 0;
    bucket = ObjectIdHashFunction(key);
    p = ObjectIdHashTable[bucket];
    while (p && !compStrIdKeyType(p->rec.inkey, key)) {
        p0 = p;
        p = p->next;
    }

    if (!p) {
        return OBJID_STATUS_KEY_NOT_FOUND;
    }

    if (p0) {
        p0->next = p->next;
    }
    else {
        ObjectIdHashTable[bucket] = p->next;
    }

    delete (p);
    return OBJID_STATUS_OK;
}

inline ObjectIdStatusEnum dtkObjectHashTableStringOneKey::ObjectIdFind(ObjectIdKeyType key, ObjectIdRecType * rec) {
    ObjectIdNodeType * p;

    p = ObjectIdHashTable[ObjectIdHashFunction(key)];
    while (p && !compStrIdKeyType(p->rec.inkey, key)) {
        p = p->next;
    }
    if (!p) {
        return OBJID_STATUS_KEY_NOT_FOUND;
    }
    * rec = p->rec;
    return OBJID_STATUS_OK;
}

inline ObjectIdStatusEnum dtkObjectHashTableStringOneKey::ObjectIdHashInit(int TableSize) {
    //@@preconditions
    assert(TableSize > 0);
    //@@end precondtions

    int i;

    if (TableSize > 0) {
        ObjectIdHashTableSize = TableSize;
    }
    ObjectIdHashTable = new ObjectIdNodeTypeP[ObjectIdHashTableSize];
    if (ObjectIdHashTable == NULL) {
        return OBJID_STATUS_MEM_EXHAUSTED;
    }

    for (i = 0; i < ObjectIdHashTableSize; i++) {
        ObjectIdHashTable[i] = NULL;
    }

    return OBJID_STATUS_OK;
}

inline ObjectIdStatusEnum dtkObjectHashTableStringOneKey::ObjectIdHashClean() {
    ObjectIdNodeType * p0, * p;
    int i = 0;
    for (i = 0; i < ObjectIdHashTableSize; i++) {
        p = ObjectIdHashTable[i];
        while (p) {
            p0 = p;
            p = p->next;
            if (p0) {
                if (p0->rec.stuff) {
                    p0->rec.stuff->Delete();
                }
                delete (p0);
                p0 = NULL;
            }
        }
    }
    if (ObjectIdHashTable) {
        delete[] ObjectIdHashTable;
    }
    ObjectIdHashTable = NULL;

    return OBJID_STATUS_OK;
}

#endif //DTKHASHTABLEOBJECT_H
