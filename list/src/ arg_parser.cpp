#include "arg_parser.h"
#include "logger.h"

void parse_args(int argc, char *argv[])
{
    static Arg args = {{"-f", "--file", NULL, false},
                       {"-m", "--mode", DEFAULT_MODE, false}};

    const size_t ArgSize = sizeof(args) / sizeof(arg[0]);

    for (int i = 1; i < argc; i++)
    {
        for (size_t j = 0; j < ArgSize; j++)
        {
            if (args[j].short_version != NULL && strcmp(argv[i], args[j].short_version) == 0)
            {
                args[j].state = true;
                if (i + 1 < argc)
                {
                    args[j].value = argv[i + 1];
                    i++;
                }
                break;
            }
            if (args[j].long_version != NULL && strcmp(argv[i], args[j].long_version) == 0)
            {
                args[j].state = true;
                if (i + 1 < argc)
                {
                    args[j].value = argv[i + 1];
                    i++;
                }
                break;
            }
        }
    }
}
