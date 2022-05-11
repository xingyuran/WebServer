#ifndef _LOG_H_
#define _LOG_H_

#include "filesystem"
#include "unistd.h"

class Log
{
public:
    Log * Instance()
    {
        static Log m_log;
        return &m_log;
    }

    void AddLog(const char * str)
    {
        FILE * fp = fopen(m_path.c_str(), "a");
        fwrite(str, 1, sizeof(str), fp);
        fclose(fp);
    }

private:
    Log()
    {
        char * path = NULL;
        getcwd(path, 0);
        m_path = path;
        m_path += "/Server.log";
        free(path);
    }
    ~Log()
    {
    };

private:
    std::string m_path;
};

#define LOG(...) 

#endif