#include "MinMaxAlgo.h"

MinMaxAlgo::MinMaxAlgo(Tree* treeData)
{
    MinMaxAlgo::SetDataTree(treeData);
}

MinMaxAlgo::MinMaxAlgo()
{

}

MinMaxAlgo::MinMaxAlgo(MinMaxAlgo& copy)
{

}

MinMaxAlgo::~MinMaxAlgo()
{

}

Position MinMaxAlgo::minMaxRun(Tree* tree, std::vector<Position> botPlayed, std::vector<Position> plyPlayed)
{
    TreeNode* tmpNode = tree->getTopTree();

    runAlgo(tmpNode, tree->getTreeDepth(), true, LONG_MIN, LONG_MAX, botPlayed, plyPlayed);

    return tmpNode->positionBoard;
}

long MinMaxAlgo::runAlgo(TreeNode* node, int depth, bool isMaximizing, long alpha, long beta, std::vector<Position> botPlayed, std::vector<Position> plyPlayed)
{
    
    if(isTerminal(node, botPlayed, plyPlayed) || depth == 0)
    {
        return MinMaxAlgo::utilityFunction(node, botPlayed, plyPlayed);
    }
        
    if(isMaximizing)
    {
        long max_eval = LONG_MIN;

        for(int i = 0; i < node->childs.size(); i++)
        {
            long eval = MinMaxAlgo::runAlgo(node->childs.at(i), false, depth - 1, alpha, beta, botPlayed, plyPlayed);

            if(max_eval < eval) 
            {
                max_eval = eval;
                node->valeurChild = i;
            }         

            alpha = std::max(alpha, eval);
            
            if(beta <= alpha)
            {
                break;
            }                
        }

        return max_eval;
    }
    else
    {
        long min_eval = LONG_MAX;

        for(int i = 0; i < node->childs.size(); i++)
        {
            long eval = MinMaxAlgo::runAlgo(node->childs.at(i), true, depth - 1, alpha, beta, botPlayed, plyPlayed);

            if(min_eval > eval) 
            {
                min_eval = eval;
                node->valeurChild = i;
            }  

            beta = std::min(beta, eval);
            
            if(beta <= alpha)
            {
                break;
            }                
        }

        return min_eval;
    }
}

long MinMaxAlgo::utilityFunction(TreeNode* node, std::vector<Position> botPlayed, std::vector<Position> plyPlayed)
{


}

bool MinMaxAlgo::isTerminal(TreeNode* node, std::vector<Position> botPlayed, std::vector<Position> plyPlayed)
{


}