#ifndef _LOG_H_
#define _LOG_H_

#include "filesystem"
#include "unistd.h"
#include "stdarg.h"

#include "Define.h"

class Log
{
public:
    static Log * Instance()
    {
        static Log m_log;
        return & m_log;
    }

    void WriteLog(const char * format, ...)
    {
        char buf[LOGBUFSIZE];
        va_list list;
        va_start(list, format);
        vsnprintf(buf, LOGBUFSIZE, format, list);
        va_end(list);

        FILE * fp = fopen(m_path.c_str(), "a");
        fwrite(buf, 1, sizeof(buf), fp);
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
    }

private:
    std::string m_path;
};

#define LOG(format, ...) Log::Instance()->WriteLog(format, ##__VA_ARGS__);

#endif