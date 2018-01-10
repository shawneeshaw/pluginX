#ifndef DTKDIRECTORY_H
#define DTKDIRECTORY_H

class dtkDirectory : public dtkObject {
public:
    /** create instance */
    static dtkDirectory *New();
    
    /** open the specified directory and load the names of the files */
    int Open(const char* dir);

    /** return the number of files in the current directory. */
    int GetNumberOfFiles() { return this->NumberOfFiles; }
        
    /** return the file at the given index, the indexing is 0 based */
    const char* GetFile(int index);

    /** is path. */
    static int FileIsDirectory(const char* name);

    /** get the current working directory. */
    static const char* GetCurrentWorkingDirectory(char* buf, unsigned int len);

protected:
    // constructor.
    dtkDirectory();

    // destructor.
    virtual ~dtkDirectory() ;
  
    // clean variables. 
    void CleanUpFilesAndPath();

private:
    char* Path;   
    char** Files; 
    int NumberOfFiles;    
};

#endif //DTKSCRIPTDIRECTORY_H

