#include "list.h"
#include "logger.h"
#include "color.h"

int main(int argc, char *argv[])
{
    printf(COLOR_GREEN "Start main\n" COLOR_RESET);
    
    LoggerInit(LOGL_DEBUG, "logger/logfile.log", DEFAULT_MODE);

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

    ListPrint(lst);
    ListDumpDot(lst);

    ListReverse(lst);
    ListDumpDot(lst);

    ListFree(lst);

    LoggerDeinit();

    printf(COLOR_GREEN "End of main\n" COLOR_RESET);
}
