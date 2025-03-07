#ifndef TREENODE
#define TREENODE

#include<vector>

struct Position
{
    Position(int x, int y) { xPos = x; yPos = y; }
    int xPos;
    int yPos;
};

struct TreeNode
{
    TreeNode* parent;
    std::vector<TreeNode*> childs;

    Position positionBoard;

    int valeurChild;
};

#endif