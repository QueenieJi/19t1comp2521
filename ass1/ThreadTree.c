// Implement by Queenie Ji (z5191512)
// ThreadTree.c ... implementation of Tree-of-Mail-Threads ADT
// Written by John Shepherd, Feb 2019

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "MMList.h"
#include "MMTree.h"
#include "MailMessage.h"
#include "ThreadTree.h"

// Representation of ThreadTree's

typedef struct ThreadTreeNode *Link;

typedef struct ThreadTreeNode {
    MailMessage mesg;
    Link next, replies;
} ThreadTreeNode;

typedef struct ThreadTreeRep {
    Link messages;
} ThreadTreeRep;

// Auxiliary data structures and functions

// Add any new data structures and functions here ...

static void doDropThreadTree (Link t);
static void doShowThreadTree (Link t, int level);
static Link newTTNode(MailMessage m);
// END auxiliary data structures and functions

// create a new empty ThreadTree
ThreadTree newThreadTree (void)
{
    ThreadTreeRep *new = malloc (sizeof *new);
    if (new == NULL) err (EX_OSERR, "couldn't allocate ThreadTree");
    *new = (ThreadTreeRep) { };
    return new;
}

void dropThreadTree (ThreadTree tt)
{
    assert (tt != NULL);
    doDropThreadTree (tt->messages);
}

// free up memory associated with list
static void doDropThreadTree (Link t)
{
    if (t == NULL)
        return;

    for (Link curr = t, next; curr != NULL; curr = next) {
        next = curr->next;
        doDropThreadTree (curr->replies);
        // don't drop curr->mesg, in case referenced elsehwere
        free (curr);
    }
}

void showThreadTree (ThreadTree tt)
{
    assert (tt != NULL);
    doShowThreadTree (tt->messages, 0);
}

// display thread tree as hiearchical list
static void doShowThreadTree (Link t, int level)
{
    if (t == NULL)
        return;
    for (Link curr = t; curr != NULL; curr = curr->next) {
        showMailMessage (curr->mesg, level);
        doShowThreadTree (curr->replies, level + 1);
    }
}

// Create a new ThreadTreeNode
static Link newTTNode (MailMessage m) {
    Link new = malloc(sizeof(ThreadTreeNode));
    assert(new != NULL);
    new->mesg = m;
    new->next = NULL;
    new->replies = NULL;
    return new;
}

// Find the correct node by recursion
static Link findNode (Link t, MailMessage newMessage)
{
    if (t == NULL) return NULL;
    if (strcmp(MailMessageRepliesTo(newMessage), MailMessageID(t->mesg)) == 0) {
        return t;
    }
    // If a reply, find the correct message from replies
    Link node1 = findNode (t->replies, newMessage);
    if (node1) return node1;
    // If not a reply, find the correct message on the next 
    Link node2 = findNode (t->next, newMessage);
    if (node2) return node2;
    return NULL;
}
// insert mail message into ThreadTree
// if a reply, insert in appropriate replies list
// whichever list inserted, must be in timestamp-order
ThreadTree ThreadTreeBuild (MMList mesgs, MMTree msgids)
{
    assert(mesgs != NULL);
    assert(msgids != NULL);
    // Build an empty tree
    ThreadTree new = newThreadTree();
    MMListStart(mesgs);
    MailMessage new_message = MMListNext(mesgs);
    new->messages = newTTNode(new_message);
    
    while (!MMListEnd (mesgs)) {
        new_message = MMListNext(mesgs);
        // find the correct place in next
        if (MailMessageRepliesTo(new_message) == NULL) {
            Link cur = new->messages;
            while (cur != NULL && cur->next != NULL) cur = cur->next;
            cur->next = newTTNode(new_message);
        } else {
            Link node = findNode(new->messages, new_message);
            if (node->replies == NULL) {
                node->replies = newTTNode(new_message);
            } else {
                // find the correct place in reply
                Link cur = node->replies;
                while (cur != NULL && cur->next != NULL) cur = cur->next;
                cur->next = newTTNode(new_message);
            }
        }
    }
    return new;
}
