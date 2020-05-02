 // Brian Pereira Alegria
// brpereir
// PA2
// List.c

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// private NodeObj type
typedef struct NodeObj {
        int item;
        struct NodeObj *next;
        struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj {
        Node head;
        Node tail;
        Node cursor;
        int numItems;
} ListObj;

typedef ListObj *List;

// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int item) {
        Node N = malloc(sizeof(NodeObj));
        N->item = item;
        N->next = NULL;
        N->prev = NULL;
        return N;
}
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN) {
        if (pN != NULL && *pN != NULL) {
                free(*pN);
                *pN = NULL;
        }
}
// Returns reference to new empty List object.
List newList(void) {
        List L;
 L = malloc(sizeof(ListObj));
        L->head = NULL;
        L->tail = NULL;
        L->cursor = NULL;
        L->numItems = 0;
        return L;
}
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL) {
        if (pL != NULL && *pL != NULL) {
                if (length(*pL) > 0)
                        clear(*pL);
                free(*pL);
                *pL = NULL;
        }
}
// Returns the number of elements in this List.
int length(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call numItems() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                int size = 0;
                Node N = L->head;
                if (N == NULL) {
                        return size;
                } else {
                        while (N != NULL) {
                                N = N->next;
                                size++;
                        }
                        return size;
                }
        }
}
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call front() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        Node N = L->head;
        Node C = L->cursor;
        int index = 0;
        if (C == NULL) {
                return -1;
        }
        while (N != NULL) {
                if (N->item == C->item) {
                        return index;
                }
                N = N->next;
                index++;
        }
        return -1;

}

        // Returns front element. Pre: length()>0


int front(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call front() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) <= 0) {
                fprintf(stderr,
                                "List Error: cannot call front() on empty List\n");
                exit(EXIT_FAILURE);
        } else {
                return L->head->item;
        }
}
// Returns back element. Pre: length()>0
int back(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call front() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) <= 0) {
                fprintf(stderr,
                                "List Error: cannot call front() on empty List\n");
                exit(EXIT_FAILURE);
        } else {
                return L->tail->item;
        }
}
// Returns cursor element. Pre: length()>0, index()>=0
int get(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call get() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) < 0) {
                fprintf(stderr,
                                "List Error: cannot call get() on empty List\n");
                exit(EXIT_FAILURE);
        }

        if (index(L) < 0) {
                fprintf(stderr,
                                "List Error: cannot call get() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                return L->cursor->item;
        }
}
// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B) {
        if (A == NULL || B == NULL) {
                fprintf(stderr,
                                "List Error: cannot call equals() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
            Node N = NULL, M = NULL;
        int eq;
        N = A->head;
        M = B->head;
        eq = (length(A) == length(B));
        while (eq && N != NULL && M != NULL) {
                eq = (N->item == M->item);
                N = N->next;
                M = M->next;
        }
        return eq;
}
// Resets this List to its original empty state.
void clear(List L) {
        Node N = L->head;
        while (N != NULL) {
                Node T = N;
                N = N->next;
                freeNode(&T);
        }
        L->head = NULL;
        L->tail = NULL;
        L->cursor = NULL;
        L->numItems = 0;
}
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call front() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                if (length(L) != 0)
                        L->cursor = L->head;
        }
}
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call moveBack() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                if (length(L) != 0)
                        L->cursor = L->tail;
        }
}
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call movePrev() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
            int k = index(L);
                if (k <= length(L) - 1 && k != 0) {
                        L->cursor = L->cursor->prev;
                }
                if (k == 0) {
                        L->cursor = NULL;
                }
                if (k == -1) {
                        return;
                }
        }
}
// If cursor is defined and not at back, moves cursor one step toward 
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call moveNext() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                int k = index(L);

                if (k <= length(L) - 1 && k >= 0) {
                        L->cursor = L->cursor->next;
                }
                if (k == length(L) - 1) {
                        L->cursor = NULL;
                }
                if (k == -1) {
                        return;
                }
        }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call prepend() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                Node N = newNode(data);
                Node H = L->head;
                if (length(L) != 0) {
                        N->next = H;
                        H->prev = N;
                        L->head = H->prev;
                } else {
                        L->head = N;
                        L->tail = N;
                        return;
                }
        }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call append() with NULL List reference\n");
                exit(EXIT_FAILURE);
           
           } else {
                Node N = newNode(data);
                Node H = L->head;
                if (length(L) != 0) {
                        N->next = H;
                        H->prev = N;
                        L->head = H->prev;
                } else {
                        L->head = N;
                        L->tail = N;
                        return;
                }
        }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call append() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                Node N = newNode(data);
                Node T = L->tail;
                if (length(L) != 0) {
                        N->prev = T;
                        T->next = N;
                        L->tail = T->next;
                } else {
                        L->head = N;
                        L->tail = N;
                        return;
                }
        }
}
// Insert new element before cursor.
//  Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
        Node N;
        int k = index(L);

        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call insertBefore() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) <= 0) {
                fprintf(stderr,
                                "List Error: cannot call insertBefore() on empty List\n");
                exit(EXIT_FAILURE);
        }

        if (k < 0) {
                fprintf(stderr,
                                "List Error: cannot call insertBefore() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                if (k != 0) {
                        N = newNode(data);
                        N->next = L->cursor;
                        N->prev = L->cursor->prev;
          L->cursor->prev->next = N;
                        L->cursor->prev = N;

                } else {
                        prepend(L, data);
                        return;
                }
        }
}
// Inserts new element after cursor.
//  Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
        Node N;
        int k = index(L);
        int n = length(L);

        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call insertAfter() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) <= 0) {
                fprintf(stderr,
                                "List Error: cannot call insertAfter() on empty List\n");
                exit(EXIT_FAILURE);
        }

        if (k < 0) {
                fprintf(stderr,
                                "List Error: cannot call insertAfter() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                if (k != n - 1) {
                        N = newNode(data);
                        N->next = L->cursor->next;
                        L->cursor->next = N;
                        N->prev = L->cursor;
                        L->cursor->next->prev = N;
                } else {
                        append(L, data);
                        return;
                }

        }
}
// Deletes the front element. Pre: length()>0
void deleteFront(List L) {
        Node H;
        int n = length(L);
        int k = index(L);

        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call insertAfter() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) <= 0) {
                fprintf(stderr,
                                "List Error: cannot call insertAfter() on empty List\n");
                exit(EXIT_FAILURE);
        } else {
    if (n != 1) {
                        H = L->head;
                        L->head = L->head->next;
                        L->head->prev = NULL;
                        freeNode(&H);
                } else {
                        H = L->head;
                        L->head = NULL;
                        L->tail = NULL;
                        freeNode(&H);
                        return;
                }
        }
}
// Deletes the back element. Pre: length()>0
void deleteBack(List L){
        Node H;
        int k = index(L);
        int n = length(L);

        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call deleteBack() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (n < 0) {
                fprintf(stderr,
                                "List Error: cannot call deleteBack() on empty List\n");
                exit(EXIT_FAILURE);
        } else {
                if (k == n - 1) {
                        L->cursor = NULL;
                }
                if (n != 1) {
                        H = L->tail;
                        L->tail = L->tail->prev;
                        L->tail->next = NULL;
                        freeNode(&H);
                } else {
                        H = L->tail;
                        L->head = NULL;
                        L->tail = NULL;
                        freeNode(&H);
                        return;
                }
        }
}
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: cannot call delete() with NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) <= 0) {
                fprintf(stderr,
                                "List Error: cannot call delete() on empty List\n");
                exit(EXIT_FAILURE);
        }
        if (index(L) < 0) {
                fprintf(stderr,
                                "List Error: cannot call delete() with NULL List reference\n");
                exit(EXIT_FAILURE);
        } else {
                Node C = L->cursor;
                if (C == L->head) {
                        deleteFront(L);
                        return;
                }
                if (C == L->tail) {
                        deleteBack(L);
                        return;
                }
                if (C != NULL) {
                        L->cursor->prev->next = L->cursor->next;
                        L->cursor->next->prev = L->cursor->prev;

                        L->cursor = NULL;
                }
                freeNode(&C);
        }
}

// Prints data elements in L to stdout.
void printList(FILE *out, List L) {
        Node N = NULL;
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: calling printList() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        N = L->head;
        while (N != NULL) {
                fprintf(out, "%d ", N->item);
                N = N->next;
        }
}
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
        if (L == NULL) {
                fprintf(stderr,
                                "List Error: calling printList() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        List A = newList();
        Node N = L->head;

        while (N != NULL) {
                append(A, N->item);
                N = N->next;
        }
        return A;
}
