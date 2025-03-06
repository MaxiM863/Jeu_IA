#include<vector>

struct Position
{
    int xPos;
    int yPos;
};

struct TreeNode
{
    TreeNode* parent;
    std::vector<TreeNode> childs;

    Position positionBoard;
};