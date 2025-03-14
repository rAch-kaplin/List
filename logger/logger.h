#ifndef _HLOGGER
#define _HLOGGER

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

const size_t SIZE_BUFFER = 8192;

enum LogLevel
{
    LOGL_DEBUG = 100,
    LOGL_INFO  = 200,
    LOGL_ERROR = 300
};

enum OutputMode
{
    COLOR_MODE = 10,
    DEFAULT_MODE = 1
};

//typedef struct Logger Logger;

typedef struct Logger {
    LogLevel levelLogger;
    FILE *logFile;
    OutputMode color_mode;
} Logger;

Logger* GetLogger();
int CheckOutputMode(const char *log_file_name);
bool shouldLog(LogLevel levelMsg);
int LoggerInit(LogLevel levelLogger, const char *log_file_name, OutputMode color_mode);
void LoggerDeinit();
const char* ColorLogMsg(const enum LogLevel levelMsg);
void RemoveAnsiCodes(char *str);
void log(LogLevel levelMsg, const char *file, size_t line, const char *func,  const char *fmt, ...);

#define LOG(levelMsg, fmt, ...)                   \
    do {                                          \
        LOG_BEGIN(levelMsg, fmt, ##__VA_ARGS__);  \
        LOG_MSG(fmt);                             \
        LOG_END();                                \
    } while(0)

#define LOG_BEGIN(levelMsg, fmt, ...)                                         \
    do {                                                                      \
        if (shouldLog(levelMsg))                                              \
        {                                                                     \
            log(levelMsg, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__);  \
        }                                                                     \
    } while(0)

#define LOG_MSG(fmt, ...)                                                           \
    do {                                                                            \
        fprintf(GetLogger()->logFile, "\n%s", GetServiceLines()->list_data);        \
    } while(0)

#define LOG_END()                                                                       \
    do {                                                                                \
        memset(GetServiceLines()->list_data, 0, sizeof(GetServiceLines()->list_data));  \
        fflush(GetLogger()->logFile);                                                   \
    } while(0)

#endif //_HLOGGER
