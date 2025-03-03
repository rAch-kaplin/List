#include "list.h"
#include "logger.h"

ServiceLines* GetServiceLines()
{
    static ServiceLines serv_lines = {};
    return &serv_lines;
}

List *ListInit()
{
    List *lst = (List*)calloc(1, sizeof(List));

    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "Could't allocate memory\n");
        return nullptr;
    }

    lst->head = nullptr;
    lst->tail = nullptr;
    lst->size = 0;

    return lst;
}

void ListFree(List *lst)
{
    if (lst != nullptr)
    {
        Node *current = lst->head;
        while (current != nullptr)
        {
            Node *next_node = current->next;
            free(current);
            current = next_node;
        }
    }
    free(lst);
}

ListErrors ListInsertFirst(List *lst, elem_t value)
{
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "List struct nullptr\n");
        return LIST_STRUCT_NULLPTR;
    }

    Node *new_node = (Node*)calloc(1, sizeof(Node));
    if (new_node == nullptr)
    {
        LOG(LOGL_ERROR, "Node allocation error\n");
        return ERROR_NODE_ALLOCATION;
    }

    new_node->value = value;
    new_node->prev = nullptr;

    if (lst->head == nullptr)
    {
        new_node->next = nullptr;
        lst->head = new_node;
        lst->tail = new_node;
    }
    else
    {
        new_node->next = lst->head;
        lst->head->prev = new_node;
        lst->head = new_node;
    }

    lst->size++;
    return OK;
}


ListErrors ListInsertLast(List *lst, elem_t value)
{
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "List struct nullptr\n");
        return LIST_STRUCT_NULLPTR;
    }

    Node *new_node = (Node*)calloc(1, sizeof(Node));
    if (new_node == nullptr)
    {
        LOG(LOGL_ERROR, "Node allocation error\n");
        return ERROR_NODE_ALLOCATION;
    }

    new_node->value = value;
    new_node->next = nullptr;

    if (lst->tail == nullptr)
    {
        new_node->prev = nullptr;
        lst->tail = new_node;
        lst->head = new_node;
    }
    else
    {
        new_node->prev = lst->tail;
        lst->tail->next = new_node;
        lst->tail = new_node;
    }

    lst->size++;
    return OK;
}

void ListPrint(List *lst)
{
    Node* current_node = lst->head;
    while (current_node != nullptr)
    {
        printf("\t[%p]: %d, current_pos->next = %p, current_pos->prev = %p\n",
                current_node, current_node->value, current_node->next, current_node->prev);

        current_node = current_node->next;
    }
    printf("\t---------------------------------------\n");
}

Node* ListGetFirst(List* lst)
{
    return lst ? lst->head : nullptr;
}

Node* ListGetLast(List* lst)
{
    return lst ? lst->tail : nullptr;
}

Node* ListGetNext(Node* current)
{
    return current ? current->next : nullptr;
}

Node* ListGetPrev(Node* current)
{
    return current ? current->prev : nullptr;
}


Node* ListFind(List *lst, elem_t value)
{
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "List struct nullptr\n");
        return nullptr;
    }

    Node *current = lst->head;
    while (current)
    {
        if (current->value == value)
        {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

ListErrors ListRemove(List *lst, Node *remove_node)
{
    if (lst == nullptr || remove_node == nullptr)
    {
        LOG(LOGL_ERROR, "List struct nullptr\n");
        return LIST_STRUCT_NULLPTR;
    }

    if (remove_node->prev != nullptr)
    {
        remove_node->prev->next = remove_node->next;
    }
    else if (remove_node == lst->head)
    {
        lst->head = remove_node->next;
    }

    if (remove_node->next != nullptr)
    {
        remove_node->next->prev = remove_node->prev;
    }
    else if (remove_node == lst->tail)
    {
        lst->tail = remove_node->prev;
    }

    free(remove_node);
    lst->size--;
    return OK;
}
