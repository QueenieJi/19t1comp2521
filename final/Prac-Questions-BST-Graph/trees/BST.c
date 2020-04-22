#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BST.h"


/* --------------- README --------------
 * A quick note before you begin these questions,
 * it's very strongly recommended that you work these out on pen and paper
 * before actually coding, figure out what edge cases there are, and just
 * work through some of those logically on paper.
 * These questions (tree questions) in particular are typical interview questions.
 * If you're into role playing (or not), try and practice speaking out your thoughts
 * the whole time as you're doing these questions on paper/coding. This is what
 * the interviewer wants to see, your thinking process. It'll also help you maintain
 * focus and pick up errors which you would otherwise miss.
 *
 * https://en.wikipedia.org/wiki/Rubber_duck_debugging is pretty legit
 *
 * glhf
 */


// Tree struct you have to play with
struct tree {
  Tree right, left;
  int val;
};

/* 
 * Easy Questions 
 */
// Check if a value is in the tree
// Should return 1 if it finds it, otherwise 0
int findValue(Tree t, int v) {
  if (t == NULL) return 0;
  if (t->val == v) return 1;
  return findValue(t->left, v) || findValue(t->right, v);
}

// Check to see if the given tree is actually a BST
// The rule is that from some arbitrary root, the left child's value must be
// smaller than the root, and the right child bigger
// return 0 if it isn't a BST, 1 if it is

//BST help functions
int BSThelp(Tree t, int lo, int hi) {
  if (t == NULL) return 1;
  if (t->val <= lo || t->val >= hi) return 0;
  return BSThelp(t->left, lo, t->val) && BSThelp(t->right, t->val, hi);
}
int isBST(Tree t) {
  if(BSThelp(t, -131613492, 131613492)) return 1;
  return 0;
}

/*
 * check if AVL
 * A tutorial question added by Queenie
 * 
 *
 */
//Help function for the AVL tree and it will check whether the tree is balanced. Return height if it is return -1 otherwise.
int isBalanced(Tree t) {
  if (t == NULL) return 0;
  if (t->left == NULL && t->right == NULL) return 0;
  int hl,hr;
  hl = isBalanced(t->left);
  hr = isBalanced(t->right);
  if (hl - hr > 1 || hr - hl > 1) return -1;
  if (hr == -1 || hl == -1) return -1;
  if (hl > hr) return hl + 1;
  if (hr > hl) return hr + 1;
}
int isAVL(Tree t) {
 return (isBalanced(t) > 0) && isBST(t);
}
*/

/*
 * Medium Questions
 */
/*
 * Given a pointer to a node in the tree, return its in order successor node in the tree, that is the node in the tree whose value is the smallest value larger than the value of the given node. If no successor node exists return NULL.
 */
Tree min(Tree t){
  if (t->left == NULL) return t;
  return min(t->left);

}

Tree succ(Tree t, int target) {
  Tree res = NULL;
  if (target < t->val) {
    res = succ(t->left, target);
    if (res == NULL) res = t;
  } else if (target > t->val) {
    res = succ(t->right, target);
  }
  return res;
}

Tree successor(Tree t, Tree target) {
  if (target->right) return min(target->right);
  return succ(t, target->val);

}

/* 
   You are given a Tree (t), and two pointers.
   k is a pointer to the 'kth' smallest value you should go to
    E.g. for *k == 0, it should return the smallest value
         for *k == 4, it should return the 5th smallest value
   v is a pointer to an int pointer, the function should finish by pointing to the value
    E.g. You found the kth smallest value, there should be some code which says
         *v = &(t->val)
    Initially, v is set to point to NULL
  
    You can assume the tree is a BST with at least one element and no duplicates 
    and that 0 <= k < n where n is the number of nodes in the tree
*/
void getKthSmallest(Tree t, int* k, int** v) {
  if (t == NULL || *v != NULL) return;
  getKthSmallest(t->left, k, v);
  if (*k  <= 0 && *v == NULL) {
    *v = &(t->val);
  }
  *k = *k - 1;
  getKthSmallest(t->right, k, v);
  
}

/* Find the lowest common ancestor between the noes with values v1 and v2.
   You are guaranteed that both these values exist in your BST and they are
   different
   The lowest common ancestor is defined as the first node which each of
   v1 and v2 share, as they go up the tree. I.e. the root of the whole tree is
   the highest common ancestor. For the following tree:
           
            4
          /   \
         2     7
        / \   /
       1   3 6
      /
     0 
   If v1 == 3, and v2 == 7, then their lowest common ancestor is 4
   If v1 == 3, and v2 == 0, then their lowest common ancestor is 2
*/
Tree lowestCommonAnc(Tree t, int v1, int v2) {
  if (t == NULL) return NULL;
  if (t->val < v1 && t->val < v2) return lowestCommonAnc(t->right, v1, v2);
  else if (t->val > v1 && t->val > v2) return lowestCommonAnc(t->left, v1, v2);
  else return t;
}


/*

   You can ignore these methods below, unless you want examples of using the tree

*/
Tree createTree() {
  return NULL;
}

void destroyTree(Tree t) {
  if (t == NULL) return;
  destroyTree(t->right);
  destroyTree(t->left);
  free(t);
}

int  getValue(Tree t) {
  return t->val;
}

Tree find(Tree t, int v) {
  if (t->val == v) return t;
  if (t->val < v) {
    return find(t->right, v);
  } else if (t->val > v) {
    return find(t->left, v);
  } else {
    return NULL;
  }
}

Tree insert(Tree t, int v) {
  if (t == NULL) {
    t = malloc(sizeof(struct tree));
    t->val = v;
    t->right = NULL;
    t->left = NULL;
  } else {
    if (t->val < v) {
      t->right = insert(t->right, v);
    } else if (t->val > v) {
      t->left = insert(t->left, v);
    }
  }
  return t;
}

Tree randInsert(Tree t, int v) {
  if (t == NULL) {
    t = malloc(sizeof(struct tree));
    t->val = v;
    t->right = NULL;
    t->left = NULL;
  } else {
    if (rand() % 2) {
      t->right = randInsert(t->right, v);
    } else {
      t->left = randInsert(t->left, v);
    }
  }
  return t;
}

int getRootVal(Tree t) {
  assert(t != NULL);
  return t->val;
}

Tree buildTree(Tree t, int* vals, int n, Tree (*insertF)(Tree, int)) {
  int i = 0;
  for (i = 0; i < n; ++i) {
    t = insertF(t, vals[i]);
  }
  return t;
}

Tree newNode(int val) {
  Tree n = malloc(sizeof(struct tree)); 
  n->val = val;
  n->left = NULL;
  n->right = NULL;
  return n;
}

Tree buildInvalidTree(int c) {
  Tree t = newNode(10); 
  switch (c) {
    case(0) :
      t->left = newNode(5);
      break;
    case(1) :
      t->right = newNode(5);
      break;
    case(2) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      break;
    case(3) :
      t->left = newNode(5);
      t->left->right = newNode(15);
      break;
    case(4) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      break;
    case(5) :
      t->left = newNode(5);
      t->left->right = newNode(15);
      break;
    case(6) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      t->left->right->left = newNode(6);
      break;
    case(7) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      t->left->right->left = newNode(6);
      t->left->right->left->right = newNode(16);
      break;
  } 
  return t;
}

