#ifndef DTKSYSTEMTOOLS_H
#define DTKSYSTEMTOOLS_H

class dtkSystemTools {
public:
    /** Sleep */
    static void Sleep(unsigned long elasped);

    /** Convert windows-style arguments given as a command-line string into more traditional argc/argv arguments. Note that argv[0] will be assigned the executable name using the ::GetModuleFileName function. */
    static void ConvertWindowsCommandLineToUnixArguments(const char * cmd_line, int * argc, char * * * argv);

    /** Convert window styler path to unix */
    static void ConvertWindowsPathToUnix(char* path);

    /** Split string by seperator char */
    static bool Split(const char * str, char**& buffer, int& num, char separator);

    /** Make a new directory */
    static void CreateDirectory(const char* str);

    /** Is directory exist */
    static bool IsDirectoryExist(const char * name);

    /** get parent directory */
    static char* GetParentDirectory(const char *name);

    /** append path */
    static char* AppendPath(char* path1, char* path2);

    /** regular express match */
    static bool RegExpressMatch(const char* src, const char* pattern); 

public:
    static char CONST_SEPDIRCHAR;
};

#endif //DTKSYSTEMTOOLS_H
