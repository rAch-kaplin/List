#ifndef _HARGPARSER
#define _HARGPARSER

typedef struct
{
    const char *short_version;
    const char *long_version;
    const char *arg;
    bool state;
} Arg;

void ParseArgs(int argc, char *argv[], Arg args[]);

#endif //_HARGPARSER
