#include "teamlist.h"
#include <stdlib.h>

typedef struct node {
    Team *team;
    struct node *prev;
    struct node *next;
} Node;

struct teamlist {
    Node *first;
    Node *last;
    int count;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL) {
        return NULL;
    }

    tl->first = NULL;
    tl->last = NULL;
    tl->count = 0;
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }

    node->team = t;
    node->next = NULL;
    node->prev = tl->last;

    if (tl->last != NULL) {
        tl->last->next = node;
    } else {
        tl->first = node;
    }

    tl->last = node;
    tl->count++;
}

int tl_size(TeamList *tl) {
    return tl->count;
}

Team *tl_get(TeamList *tl, int i) {
    Node *curr;

    if (i < tl->count / 2) {
        curr = tl->first;
        for (int idx = 0; idx < i; idx++) {
            curr = curr->next;
        }
    } else {
        curr = tl->last;
        for (int idx = tl->count - 1; idx > i; idx--) {
            curr = curr->prev;
        }
    }

    return curr->team;
}

void tl_free(TeamList *tl) {
    if (tl != NULL) {
        Node *curr = tl->first;
        while (curr != NULL) {
            Node *next = curr->next;
            team_free(curr->team);
            free(curr);
            curr = next;
        }
        free(tl);
    }
}