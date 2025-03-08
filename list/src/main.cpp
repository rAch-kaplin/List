#include "list.h"
#include "logger.h"

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
    ListPrint(lst);
    ListFree(lst);

    //system("dot -Tpng dump.dot -o dump.png");
    LoggerDeinit();
}
