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

long MinMaxAlgo::runAlgo(TreeNode* node, int depth, bool isMaximizing, long alpha, long beta)
{
    
    if(isTerminal(node) || depth == 0)
    {
        return MinMaxAlgo::utilityFunction(node);
    }
        
    if(isMaximizing)
    {
        long max_eval = LONG_MIN;

        for(int i = 0; i < node->childs.size(); i++)
        {
            long eval = MinMaxAlgo::runAlgo(node->childs.at(i), false, depth - 1, alpha, beta);

            max_eval = std::max(max_eval, eval);

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
            long eval = MinMaxAlgo::runAlgo(node->childs.at(i), true, depth - 1, alpha, beta);

            min_eval = std::min(min_eval, eval);

            beta = std::min(beta, eval);
            
            if(beta <= alpha)
            {
                break;
            }                
        }

        return min_eval;
    }
}

long MinMaxAlgo::utilityFunction(TreeNode* node)
{


}

bool MinMaxAlgo::isTerminal(TreeNode* node)
{


}