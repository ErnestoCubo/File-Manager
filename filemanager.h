#ifndef FILEMANAGER_H
#define FILEMANAGER_Hop

#include "utils.h"

using namespace std;

class FileManager
{
    string dirPath;
    map<string, string* > files;
public:
    FileManager(string path);
    vector<string*>* listFiles();
    void readFile(char* fileName, char* &data, unsigned long int & dataLength);
    void writeFile(char* fileName, char* data, unsigned long int dataLength);
    void freeListedFiles(vector<string*>* fileList);
};

#endif // FILEMANAGER_H
