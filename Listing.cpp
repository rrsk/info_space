#include <windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <vector>
#include <iostream>

using namespace std;



typedef std::wstring String;
typedef std::vector<String> StringVector;
typedef unsigned long long uint64_t;

bool IsBrowsePath(string path)
{
    return (path == _T(".") || path == _T(".."));
}

uint64_t CalculateDirSize(string &path, vector<String> *errVect = NULL,uint64_t size = 0)
{
    WIN32_FIND_DATA data;
    HANDLE sh = NULL;
    string s_path= path + "/*";
    sh = ::FindFirstFile(s_path.c_str(), &data);

    /*if (sh == INVALID_HANDLE_VALUE )
    {
        //if we want, store all happened error
        if (errVect != NULL)
            errVect->push_back(path);
        return size;
    }*/

    do
    {
        // skip current and parent
        if (!IsBrowsePath(data.cFileName))
        {
            // if found object is ...
            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {// directory, then search it recursievly
                  string n_path=path + "/" + data.cFileName;
                  //cout<<"working"<<endl;
                size = CalculateDirSize(n_path,NULL,size);
                }
            else
                {// otherwise get object size and add it to directory size
                //cout<<"inElse"<<endl;
                size += (uint64_t) (data.nFileSizeHigh * (MAXDWORD ) + data.nFileSizeLow);
                }
        }

    } while (FindNextFile(sh, &data)); // do

    FindClose(sh);

    return size;
}


vector<string> get_all_files_names_within_folder(string folder)
{
    uint64_t size=0;
    vector<string> names;
    string search_path = folder + "/*";
    WIN32_FIND_DATA fd;
    LARGE_INTEGER filesize;
    long long int sum =0;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);

    if(hFind == INVALID_HANDLE_VALUE)
            {
                cout<<" Invalid Path";
            }
    if(hFind != INVALID_HANDLE_VALUE) {
        do {

            if (!IsBrowsePath(fd.cFileName))
            {// read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                names.push_back(fd.cFileName);
                filesize.LowPart = fd.nFileSizeLow;
                filesize.HighPart = fd.nFileSizeHigh;
                string path_2=folder +"/"+fd.cFileName;
                cout<<fd.cFileName<<" <DIR> " <<CalculateDirSize(path_2)/1000<<" KB"<< endl;
            }
            else{
                 filesize.LowPart = fd.nFileSizeLow;
                 filesize.HighPart = fd.nFileSizeHigh;
                 printf("  %s   %ld bytes\n", fd.cFileName, filesize.QuadPart);
            }
        }


        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);

        cout<<"Folder Size: "<<CalculateDirSize(folder)/1000000<<" MB";
    }
    return names;
}

int main()
{
    string f;
    cout<<"Enter your folder location(eg. C:Documents/<Folder_name> ): \n";
    cin>>f;
    cout<<"\n\n FILE/Folder  SIZE \n";
    get_all_files_names_within_folder(f);
    return 0;
}
