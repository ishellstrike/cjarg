#ifndef FIELSYSTEM
#define FIELSYSTEM
#include "logger.h"
#include <vector>
#include "jhelper.inl"

#ifdef _WIN32
    #include <windows.h>

    void getFiles(const std::string &dir, std::vector<std::string> &files)
    {
        files.clear();
        WIN32_FIND_DATA f;


        std::wstring s = L"./" + string_to_wstring(dir) + L"*";
        HANDLE h = FindFirstFile(s.c_str(), &f);
        if(h != INVALID_HANDLE_VALUE)
        {
            do
            {
                std::string fn = wstring_to_string(f.cFileName);
                if(fn == "." || fn == "..")
                    continue;

                files.push_back(fn);
            } while(FindNextFile(h, &f));
        }
        else
            LOG(error) << "Error opening directory";
    }

#endif
#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>

    void getFiles(const std::string &dir, std::vector<std::string> &files)
    {
        files.clear();
        DIR *dir = opendir("."+dir);
        if(dir)
        {
            struct dirent *ent;
            while((ent = readdir(dir)) != nullptr)
                files.push_back(ent->d_name);
        }
        else
            LOG(error) << "Error opening directory";
    }
#endif

#endif // FIELSYSTEM

