#include "dtkframeobjectincludes.h"

#ifdef _WIN32
#include <windows.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <direct.h>
#else
#include <sys/time.h>
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>
#endif

#include <sys/types.h>
#include <time.h>
//#include <pcre.h>

// The microsoft compiler defines this as a macro, so undefine it here
#undef GetCurrentTime

#ifdef WIN32
char dtkSystemTools::CONST_SEPDIRCHAR = '\\';
#else
char dtkSystemTools::CONST_SEPDIRCHAR = '/';
#endif

//-----------------------------------------------------------------------------
// class dtkSystemTools
//-----------------------------------------------------------------------------
//
void dtkSystemTools::ConvertWindowsCommandLineToUnixArguments(const char * cmd_line, int * argc, char * * * argv) {
    if (!cmd_line || !argc || !argv) {
        return;
    }

    (* argc) = 1;
    size_t cmd_line_len = strlen(cmd_line);
    size_t i;
    for (i = 0; i < cmd_line_len; i++) {
        while (isspace(cmd_line[i]) && i < cmd_line_len) {
            i++;
        }
        if (i < cmd_line_len) {
            if (cmd_line[i] == '\"') {
                i++;
                while (cmd_line[i] != '\"' && i < cmd_line_len) {
                    i++;
                }
                (* argc) ++;
            }
            else {
                while (!isspace(cmd_line[i]) && i < cmd_line_len) {
                    i++;
                }
                (* argc) ++;
            }
        }
    }

    (* argv) = new char * [(* argc) + 1];
    (* argv) [(* argc)] = NULL;
    (* argv) [0] = new char[1024];
#ifdef _WIN32
    ::GetModuleFileName(0, (* argv) [0], 1024);
#else
    (* argv) [0] [0] = '\0';
#endif
    int  j;
    for (j = 1; j < (* argc); j++) {
        (* argv) [j] = new char[cmd_line_len + 10];
    }

    size_t pos;
    int argc_idx = 1;

    for (i = 0; i < cmd_line_len; i++) {
        while (isspace(cmd_line[i]) && i < cmd_line_len) {
            i++;
        }
        if (i < cmd_line_len) {
            if (cmd_line[i] == '\"') {
                i++;
                pos = i;
                while (cmd_line[i] != '\"' && i < cmd_line_len) {
                    i++;
                }
                memcpy((* argv) [argc_idx], & cmd_line[pos], i - pos);
                (* argv) [argc_idx] [i - pos] = '\0';
                argc_idx++;
            }
            else {
                pos = i;
                while (!isspace(cmd_line[i]) && i < cmd_line_len) {
                    i++;
                }
                memcpy((* argv) [argc_idx], & cmd_line[pos], i - pos);
                (* argv) [argc_idx] [i - pos] = '\0';
                argc_idx++;
            }
        }
    }
}

//-----------------------------------------------------------------------------
void dtkSystemTools::ConvertWindowsPathToUnix(char* path) {
    if (NULL == path)
        return;

    int i = 0 ;
    while (path[i] != 0){
        if ('\\' == path[i]) path[i] = '/' ;
        i++ ;
    }
    return;
}

//----------------------------------------------------------------------------
bool dtkSystemTools::Split(const char * str, char**& buffer, int& num, char separator) {
    //@@preconditions
    assert(buffer == NULL);
    //@@end preconditions

    dtkString data = dtkString(str);

    int count = 0;
    {
        int lpos = 0;
        while (lpos < data.size()) {
            int rpos = data.find(separator, lpos);
            if (rpos == -1) {
                count++;
                break;
            }
            else {
                count++;
            }
            lpos = rpos + 1;
        }
    }

    buffer = new char* [count];
    {
        count = 0;
        int lpos = 0;
        while (lpos < data.size()) {
            int rpos = data.find(separator, lpos);
            if (rpos == -1) {
                dtkString tmpStr = data.substr(lpos, data.size()-lpos);
                int len = data.size()-lpos;
                buffer[count] = new char[len+1];
                strncpy(buffer[count], &str[lpos], len);
                buffer[count][len] = '\0';
                count++;
                break;
            }
            else {                
                dtkString tmpStr = data.substr(lpos, rpos-lpos);
                int len = rpos-lpos;
                buffer[count] = new char[len+1];
                strncpy(buffer[count], &str[lpos], len);
                buffer[count][len] = '\0';
                count++;
            }
            lpos = rpos + 1;
        }
    }
    num = count;
    return true;
}

//-----------------------------------------------------------------------------
static unsigned long GetCurrentTime() {
    double currentTimeInSeconds;

#ifdef _WIN32
    timeb CurrentTime;
    static double scale = 1.0 / 1000.0;
    ::ftime(& CurrentTime);
    currentTimeInSeconds = CurrentTime.time + scale * CurrentTime.millitm;
#else
    static timeval CurrentTimeA;
    static double scale = 1.0 / 1000000.0;
    gettimeofday(& (CurrentTimeA), NULL);
    currentTimeInSeconds = CurrentTimeA.tv_sec + scale * CurrentTimeA.tv_usec;
#endif
    return (unsigned long)(1000.0*currentTimeInSeconds);
}

//-----------------------------------------------------------------------------
void dtkSystemTools::Sleep(unsigned long elasped) {
    unsigned long initTime = GetCurrentTime();
    for (;;) {
        unsigned long currentTime = GetCurrentTime();
        if ((currentTime-initTime) > elasped) {
            break;
        }
    }
}

//-----------------------------------------------------------------------------
void dtkSystemTools::CreateDirectory(const char* str) {
#ifdef WIN32
   _mkdir(str);
#else
   _mkdir(str);
#endif
}

//-----------------------------------------------------------------------------
bool dtkSystemTools::IsDirectoryExist(const char * name) {
    struct stat fs;
    if (stat(name, & fs) == 0) {
#ifdef WIN32
        return ((fs.st_mode & _S_IFDIR) != 0);
#else
        return S_ISDIR(fs.st_mode);
#endif
    }
    else {
        return false;
    }
}

//-----------------------------------------------------------------------------
char* dtkSystemTools::AppendPath(char* path1, char* path2) {
    static char szpath[2048];
    int len = strlen(path1);
    if (path1[len-1] == dtkSystemTools::CONST_SEPDIRCHAR) {
        sprintf(szpath, "%s%s", path1, path2);
    }
    else {
        sprintf(szpath, "%s%c%s", path1, dtkSystemTools::CONST_SEPDIRCHAR, path2);
    }
    return szpath;
}

//-----------------------------------------------------------------------------
char* dtkSystemTools::GetParentDirectory(const char *path1) {
    static char szpath[2048];
    int cc = strlen(path1)-1;
    if (path1[cc] == dtkSystemTools::CONST_SEPDIRCHAR) {
        cc--;
    }
    for ( ; cc > 0; cc--) {
        if (path1[cc] == dtkSystemTools::CONST_SEPDIRCHAR) {
            break;
        }
    }    
    if (cc > 0) {
        char * updir = new char[cc+1];
        memcpy(updir, path1, cc);
        updir[cc] = '\0';
        sprintf(szpath, "%s", updir);
        delete[] updir;
        return szpath;
    }
    return NULL;
}


#define OVECCOUNT   30    
//-----------------------------------------------------------------------------
bool dtkSystemTools::RegExpressMatch(const char* src, const char* pattern) {   
/*
    const char * error = NULL; int erroffset;
    pcre* re = pcre_compile(pattern, PCRE_CASELESS, &error, &erroffset, NULL);
    if (re == NULL) {
        return FALSE;
    }
    
    int ovector[OVECCOUNT];
    int rc = pcre_exec(re, NULL, src, strlen(src), 0, 0, ovector, OVECCOUNT);
    if (rc < 0) {
        return FALSE;
    }        
    pcre_free(re);
*/
    return TRUE;
}
