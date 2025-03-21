#include "list.h"
#include "logger.h"
#include "color.h"
#include "arg_parser.h"

void CheckArgs(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    printf(COLOR_GREEN "Start main\n" COLOR_RESET);

    Arg args[] = {  { "-f",       "--file", NULL, false},
                    {"-mc",  "--ModeColor", NULL, false}};

    const size_t ArgSize = sizeof(args) / sizeof(args[0]);
    ParseArgs(argc, argv, args, ArgSize);
    CheckArgs(argc, argv);
    printf("%d\n", args[1].state);
    LoggerInit(LOGL_DEBUG, "logger/logfile.log", GetLogger()->color_mode);

    List *lst = ListInit();
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "lst nullptr\n");
        return -1;
    }

    ListInsertFirst(lst, 100);

    for (int i = 0; i < 6; i++)
    {
        if (i == 2)
        {
        ListInsertFirst(lst, 999);
        continue;
        }
        ListInsertLast(lst, i * 10);
    }

    ListInsert(lst, 89, 6);

    ListDumpDot(lst);

    ListReverse(lst);
    ListDumpDot(lst);

    ListFree(lst);

    LoggerDeinit();

    printf(COLOR_GREEN "End of main\n" COLOR_RESET);
}

void CheckArgs(int argc, char *argv[])
{
    GetLogger()->color_mode = DEFAULT_MODE;

    const char* color_mode = NULL;

    for (int i = 1; i < argc; i++)
    {

        if ((strcmp(argv[i], "--mode") == 0 || strcmp(argv[i], "-m") == 0) && i + 1 < argc)
        {
            color_mode = argv[i + 1];
            if (strcmp(color_mode, "COLOR_MODE") == 0)
            {
                GetLogger()->color_mode = COLOR_MODE;
            }
            i++;
        }
    }
}
