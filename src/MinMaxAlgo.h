#include "Tree.h"

class MinMaxAlgo {

public:

    MinMaxAlgo();
    MinMaxAlgo(Tree* treeData);
    ~MinMaxAlgo();
    MinMaxAlgo(MinMaxAlgo& copy);

public:

    long runAlgo(TreeNode* node, int depth, bool isMaximizing, long alpha, long beta);
    void SetDataTree(Tree* treeData);

private:

    long utilityFunction(TreeNode* node);
    bool isTerminal(TreeNode* node);

private:

    Tree* tree;
};