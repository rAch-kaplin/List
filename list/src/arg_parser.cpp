#include "arg_parser.h"
#include "logger.h"

void ParseArgs(int argc, char *argv[], Arg args[], size_t ArgSize)
{
    for (int i = 1; i < argc; i++)
    {
        for (size_t j = 0; j < ArgSize; j++)
        {
            if ((args[j].short_version && strcmp(argv[i], args[j].short_version) == 0) ||
                (args[j].long_version  && strcmp(argv[i], args[j].long_version) == 0))
            {
                args[j].state = true;

                if (i + 1 < argc && argv[i + 1][0] != '-')
                {
                    if (!args[j].arg)
                    {
                        args[j].arg = argv[i + 1];
                    }
                    i++;
                }
                break;
            }
        }
    }
}
