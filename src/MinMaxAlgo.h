#include "Tree.h"

#define MAXHITS 4

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
    
    long utilityFunction(TreeNode* node, std::vector<Position> Played);
    bool isTerminal(TreeNode* node, std::vector<Position> botPlayed);

    void recursiveDirection(long& points, Position pos, Position direction, std::vector<Position> botPlayed);

    long calculatePoints(int hits);

private:

    Tree* tree;
};