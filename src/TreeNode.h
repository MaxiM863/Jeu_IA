#ifndef TREENODE
#define TREENODE

#include<vector>

struct Position
{
    Position(){}
    Position(int x, int y) { xPos = x; yPos = y; }

    int xPos;
    int yPos;
};

struct TreeNode
{
    TreeNode(){}
    TreeNode(TreeNode* _parent, int nbrChilds, Position position)
    {
        parent = _parent;
        childs = new TreeNode*[nbrChilds];
        positionBoard = position;
        valeurChild = 0;
    }

    TreeNode* parent;
    TreeNode** childs;

    int childsCount = 0;

    Position positionBoard;

    int valeurChild;
};

#endif