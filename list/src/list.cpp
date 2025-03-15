#include "list.h"
#include "logger.h"

List *ListInit()
{
    List *lst = (List*)calloc(1, sizeof(List));

    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "Could't allocate memory\n");
        return lst;
    }

    lst->head = nullptr;
    lst->tail = nullptr;
    lst->size = 0;

    LOG(LOGL_DEBUG, "ListInit: \n");

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

    GetListData(lst);
    LOG(LOGL_DEBUG, "ListInsertFirst:");

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

ListErrors ListInsert(List *lst, elem_t value, size_t position)
{
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "List struct nullptr\n");
        return LIST_STRUCT_NULLPTR;
    }

    if (position > (size_t)lst->size)
    {
        LOG(LOGL_ERROR, "Invalid position: %zu\n", position);
        return INVALID_POSITION;
    }

    if (position == 0)
    {
        return ListInsertFirst(lst, value);
    }

    if (position == (size_t)lst->size)
    {
        return ListInsertLast(lst, value);
    }

    Node *new_node = (Node*)calloc(1, sizeof(Node));
    if (new_node == nullptr)
    {
        LOG(LOGL_ERROR, "Node allocation error\n");
        return ERROR_NODE_ALLOCATION;
    }

    new_node->value = value;

    Node *current = lst->head;
    for (size_t i = 0; i < position - 1; i++)
    {
        current = current->next;
    }

    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
    current->next = new_node;

    lst->size++;

    return OK;
}

void ListPrint(List *lst)
{
    Node* current_node = lst->head;
    while (current_node != nullptr)
    {
        printf("\t[%p]: %03d, current_pos->next = %p, current_pos->prev = %p\n",
                current_node, current_node->value, current_node->next, current_node->prev);

        current_node = current_node->next;
    }
    printf("\t------------------------------------------------------------\n");
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
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "List struct nullptr\n");
        return LIST_STRUCT_NULLPTR;
    }
    else if (remove_node == nullptr)
    {
        LOG(LOGL_ERROR, "remove_node nullptr\n");
        return NODE_NULLPTR;
    }

    if (lst->head == lst->tail)
    {
        RemoveSingleNode(lst, remove_node);
    }

    else if (lst->head == remove_node)
    {
        RemoveBegin(lst, remove_node);
    }

    else if (lst->tail == remove_node)
    {
        RemoveEnd(lst, remove_node);
    }

    else
    {
        RemoveNode(lst, remove_node);
    }

    lst->size--;
    remove_node->value = POISON;
    free(remove_node);

    return OK;
}

void RemoveSingleNode(List *lst, Node *remove_node)
{
    assert(lst && remove_node);

    lst->head = nullptr;
    lst->tail = nullptr;
}

void RemoveEnd(List *lst, Node *remove_node)
{
    assert(lst && remove_node);

    lst->tail = lst->tail->prev;
    if (lst->tail != nullptr)
    {
        lst->tail->next = nullptr;
    }
}

void RemoveBegin(List *lst, Node *remove_node)
{
    assert(lst && remove_node);

    lst->head = lst->head->next;
    if (lst->head != nullptr)
    {
        lst->head->prev = nullptr;
    }
}

void RemoveNode(List *lst, Node *remove_node)
{
    assert(lst && remove_node);

    remove_node->prev->next = remove_node->next;
    remove_node->next->prev = remove_node->prev;
}

ListErrors ListReverse(List *lst)
{
    if (lst == nullptr)
    {
        LOG(LOGL_ERROR, "List struct nullptr\n");
        return LIST_STRUCT_NULLPTR;
    }
    else if (lst->head == nullptr)
    {
        LOG(LOGL_ERROR, "List is empty\n");
        return LIST_EMPTY;
    }

    Node *current = lst->head;
    Node *temp = nullptr;

    while (current != nullptr)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    temp = lst->head;
    lst->head = lst->tail;
    lst->tail = temp;

    return OK;
}

bool ListHasCycle(List *lst)
{
    assert(!lst);

    Node *slow_fwd = lst->head;
    Node *fast_fwd = lst->head;

    Node *slow_bwd = lst->tail;
    Node *fast_bwd = lst->tail;

    while (fast_fwd->next || fast_bwd->prev)
    {
        if (fast_fwd && fast_fwd->next)
        {
            slow_fwd = slow_fwd->next;
            fast_fwd = fast_fwd->next->next;
        }

        if (fast_bwd && fast_bwd->prev)
        {
            slow_bwd = slow_bwd->prev;
            fast_bwd = fast_bwd->prev->prev;
        }
    }

    if (slow_fwd == fast_fwd || slow_bwd == fast_bwd)
    {
            return true;
    }

    return false;
}


