#include "list.h"
#include "logger.h"

// вставка в середину
// free() передавать через указатель
// Renove...() общще вынести из функций
// snap vscode, yay mb
// html table

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

    for (int i = 0; i < 10; i++)
    {
        if (i == 6)
        {
        ListInsertFirst(lst, 999);
        continue;
        }
        ListInsertLast(lst, i * 10);
    }

    ListPrint(lst);
    ListDumpDot(lst);
    ListFree(lst);

    system("dot -Tpng GraphDump/dump.dot -o dump.png");
    LoggerDeinit();
}
