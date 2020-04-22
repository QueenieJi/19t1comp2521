int checkvalue(BSTree t){
    if (t == NULL) return 1;
    if (left(t) != NULL && data(t) < data(left(t))) return 0;
    if (right(t) != NULL && data(t) < data(right(t))) return 0;
    return checkvalue(left(t)) && checkvalue(right(t));
}

int checkStructure (BSTree t) {
    int noNodes = countNodes(t);
    return structurehelper(t,1,noNodes)
}

int structurehelper(BSTree t, int currIndex, int numNodes) {
    if (t == NULL) return 1;
    if (currIndex > numNodes) return 0;
    return structurehelper(t->left, currIndex*2, numNodes) && structurehelper(t->right, currIndex * 2 + 1, numNodes);
}
int countNodes(BSTree t) {
    if (t == NULL) return 0;
    return countNodes(t->left) + countNodes(t->right) + 1;
}

int isHeap(BSTree t) {
    //if(t == NULL) return 0;
    int isHeap = checkvalue(t) && checkStructure(t);
    if (!isHeap) return 0;
    return 1;
}