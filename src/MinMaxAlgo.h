#include "Tree.h"

class MinMaxAlgo {

public:

    MinMaxAlgo();
    MinMaxAlgo(Tree* treeData);
    ~MinMaxAlgo();
    MinMaxAlgo(MinMaxAlgo& copy);

public:

    Position minMaxRun(Tree* tree, std::vector<Position> botPlayed, std::vector<Position> plyPlayed);

    void SetDataTree(Tree* treeData);

private:

    long runAlgo(TreeNode* node, int depth, bool isMaximizing, long alpha, long beta, std::vector<Position> botPlayed, std::vector<Position> plyPlayed);
    
    long utilityFunction(TreeNode* node, std::vector<Position> botPlayed, std::vector<Position> plyPlayed);
    bool isTerminal(TreeNode* node, std::vector<Position> botPlayed, std::vector<Position> plyPlayed);

private:

    Tree* tree;
};