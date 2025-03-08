#include "list.h"

// background 4A5949
// 769074

int ListDumpDot (List *lst);


int ListDumpDot (List *lst)
{
    const size_t SIZE_BUFFER_DUMP = 1024;
    char buffer_dump[SIZE_BUFFER_DUMP];
    size_t buffer_len = 0;

    FILE *dump_file = fopen("GraphDump/dump.dot", "wt");
    if (!dump_file)
    {
        fprintf(stderr, "dump.dot don't open\n");
        return -1;
    }

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - buffer_len,
                           "digraph G {\n\t"
                           "rankdir = LR;\n\t"
                           "bgcolor=\"#4A5949\"\n");

    Node *current = lst->head;
    int index = 0;
    while (current != NULL) {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - buffer_len,
                               "\tnode%03d [shape=Mrecord; style=filled; color=\"#769074\"; "
                               "label = \" { ip: %03d} | {value: %3d} | {next: %3d} | {prev: %3d} \" ];\n",
                               index, index, current->value, (current->next ? index + 1 : -1),
                               (current->prev ? index - 1 : -1));
        current = current->next;
        index++;
    }

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - buffer_len, "\n");

    current = lst->head;
    index = 0;
    while (current != NULL && current->next != NULL) {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - buffer_len,
                               "\tnode%03d -> node%03d [style=bold; weight=1000; color=chocolate1; ];\n",
                               index, index + 1);
        index++;
        current = current->next;
    }

    current = lst->tail;
    index = lst->size - 1;
    while (current != NULL && current->prev != NULL) {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - buffer_len,
                               "\tnode%03d -> node%03d [weight=0; color=purple; constraint=false; ];\n",
                               index, index - 1);
        index--;
        current = current->prev;
    }

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - buffer_len, "}\n");


    fprintf(dump_file, "%s", buffer_dump);

    fclose(dump_file);
    system("dot -Tpng dump.dot -o dump.png");

    return 0;
}
