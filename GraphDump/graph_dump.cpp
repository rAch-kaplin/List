#include "list.h"
#include "color.h"

int ListDumpDot (List *lst)
{
    static int dump_counter = 0;
    const size_t PNG_NAME_SIZE = 30;
    const size_t SIZE_BUFFER_DUMP = 8192;
    char buffer_dump[SIZE_BUFFER_DUMP];
    int buffer_len = 0;

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
                           "digraph G {\n\t"
                           "rankdir = LR;\n\t"
                           "bgcolor=\"#4A5949\"\n");

    Node *current = lst->head;
    int index = 0;

    while  (current != nullptr)
    {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
                       "\tnode%03d [shape=Mrecord; style=filled; color=\"#769074\"; label = <\n"
                       "\t\t         <table BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"#769074\" COLOR=\"black\">\n"
                       "\t\t\t           <tr><td align='center' colspan='2'> ip: %03d </td></tr>\n"
                       "\t\t\t           <tr><td PORT='prev' align='center' colspan='2'> value: %03d </td></tr>\n"
                       "\t\t\t           <tr><td PORT='prev' align='center'> prev: %3d </td>\n"
                       "\t\t\t               <td PORT='next' align='center'> next: %3d </td></tr>\n"
                       "\t\t         </table> >];\n",
                       index, index, current->value,
                       (current->prev ? index - 1 : -1),
                       (current->next ? index + 1 : -1));

        current = current->next;
        index++;
    }

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len, "\n\n");

    current = lst->head;
    index = 0;
    while (current != nullptr && current->next != nullptr)
    {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
                               "\tnode%03d -> node%03d [style=bold; weight=1000; color=chocolate1; ];\n",
                               index, index + 1);
        index++;
        current = current->next;
    }
    int last_index = index;
    printf(COLOR_RED "%d\n" COLOR_RESET, last_index);

    current = lst->tail;
    index = lst->size - 1;
    while (current != nullptr && current->prev != nullptr)
    {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
                               "\tnode%03d -> node%03d [weight=0; color=purple; constraint=false; ];\n",
                               index, index - 1);
        index--;
        current = current->prev;
    }

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len, "\n");

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
                       "\tsubgraph cluster_head_tail {\n"
                       "\t\tcolor=transparent;\n"
                       "\t\tlabel = \"\";\n");

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - buffer_len,
                           "\thead [shape=hexagon; style=filled; color=\"#ffac05\"; label=\"Head\"];\n"
                           "\ttail [shape=hexagon; style=filled; color=\"#ffac05\"; label=\"Tail\"];\n\t}\n");

    // buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
    //                     "\t{ rank=same; head; node000; }\n"
    //                     "\t{ rank=same; tail; node%03d; }\n", last_index);


    if (lst->head != nullptr)
    {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
                               "\thead -> node000 [style=dashed; color=\"#ffac05\"];\n");
    }

    if (lst->tail != nullptr)
    {
        buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len,
                               "\ttail -> node%03d [style=dashed; color=\"#ffac05\"];\n", last_index);
    }

    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len, "\n");


    buffer_len += snprintf(buffer_dump + buffer_len, SIZE_BUFFER_DUMP - (size_t)buffer_len, "}\n");


    FILE *dump_file = fopen("GraphDump/dump.dot", "w+");
    if (!dump_file)
    {
        fprintf(stderr, "dump.dot don't open\n");
        return -1;
    }

    fprintf(dump_file, "%s", buffer_dump);
    fclose(dump_file);


    system("dot -Tpng GraphDump/dump.dot -o dump.png");

    char png_filename[PNG_NAME_SIZE];
    snprintf(png_filename, PNG_NAME_SIZE, "GraphDump/img/dump_%d.png", dump_counter++);

    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng GraphDump/dump.dot -o %s", png_filename);
    system(command);

    return 0;
}
