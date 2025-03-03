#include "list.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    LoggerInit(LOGL_DEBUG, "logfile.log", DEFAULT_MODE);

    List *lst = ListInit();
    ListInsertFirst(lst, 10);
    ListPrint(lst);
    ListFree(lst);

    LoggerDeinit();
}
