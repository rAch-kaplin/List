#include "list.h"
#include "logger.h"

// вставка в середину
// free() передавать через указатель
// Remove...() общще вынести из функций


int main(int argc, char *argv[])
{
    LoggerInit(LOGL_DEBUG, "logger/logfile.log", DEFAULT_MODE);

    List *lst = ListInit();
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "lst nullptr\n");
        return -1;
    }

    ListInsertFirst(lst, 10);

    for (int i = 0; i < 6; i++)
    {
        if (i == 2)
        {
        ListInsertFirst(lst, 999);
        continue;
        }
        ListInsertLast(lst, i * 10);
    }

    ListRemove(lst, ListFind(lst, 30));

    ListPrint(lst);
    ListDumpDot(lst);
    ListFree(lst);

    LoggerDeinit();
}
