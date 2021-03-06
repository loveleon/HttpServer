#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED

#include <string>
#include <fstream>

namespace CommonFunction
{
    using std::string;

    int StringToInt(const string &str);
    string IntToString(int n);
    string CurrentTime();
    size_t FileLength(std::ifstream &file);
    string FileName(const string &path);
    string FileType(const string &filename);
}

#endif // COMMONFUNCTION_H_INCLUDED
