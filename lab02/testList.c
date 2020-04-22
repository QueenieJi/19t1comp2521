// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

static void empty_list(void);
static void one_element(void);
static void more_elements(void);
int main (void)
{
	DLList myList = getDLList (stdin);
	putDLList (stdout, myList);
	assert (validDLList (myList));
    empty_list();
    one_element();
    more_elements();
	// TODO: more tests needed here

	freeDLList (myList);
	return EXIT_SUCCESS;
}
static void empty_list(void) {
    printf("Check empty_list...\n");
    DLList L = newDLList();
    printf("Insert an item before current item. New item becomes current item.\n");
    DLListBefore(L, "a new line");
    assert(validDLList(L) == 1);
    putDLList (stdout, L);
    printf("Delete current item.\n");
    DLListDelete(L);
    assert(validDLList(L) == 1);
    
    printf("Insert an item after current item. New item becomes current item.\n");
    DLListAfter(L, "a");
    
    putDLList (stdout, L);
    printf("empty_list test pass!\n");
    
    freeDLList(L);
}

static void one_element(void) {
    printf("Check one_element_list...\n");
    DLList L = newDLList();
    DLListBefore(L, "the only element");
    assert(validDLList(L) == 1);
    printf("Insert an item before current item. New item becomes current item.\n");
    DLListBefore(L, "new first line");
    assert(validDLList(L) == 1);
    putDLList (stdout, L);
    printf("Delete current item.\n");
    DLListDelete(L);
    putDLList(stdout, L);
    assert(validDLList(L) == 1);
    printf("Insert an item after current item. New item becomes current item.\n");
    DLListAfter(L, "the second line");
    putDLList(stdout, L);
    assert(validDLList(L) == 1);
    printf("Delete current item until nothing left.\n");
    DLListDelete(L);
    assert(validDLList(L) == 1);
    putDLList(stdout, L);
    DLListDelete(L);
    assert(validDLList(L) == 1);
    freeDLList(L);
    printf("One_element_list test passed!\n");
}
static void more_elements(void) {
    printf("Check more_elements_list...\n");
    DLList L = newDLList();
    DLListBefore(L, "one element");
    DLListAfter(L, "two elements");
    assert(validDLList(L) == 1);
    printf("Insert two items before current item. New item becomes current item.\n");
    DLListBefore(L, "new second line");
    DLListBefore(L, "new third line");
    assert(validDLList(L) == 1);
    putDLList (stdout, L);
    printf("Delete current item.\n");
    DLListDelete(L);
    putDLList(stdout, L);
    assert(validDLList(L) == 1);
    printf("Insert an item after current item. New item becomes current item.\n");
    DLListAfter(L, "something");
    assert(validDLList(L) == 1);
    putDLList(stdout, L);
    freeDLList(L);
    printf("more_elements_list test passed!\n");

}
