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
    
    if(isTerminal(node, botPlayed) || depth == 0)
    {
        return MinMaxAlgo::utilityFunction(node, botPlayed) - MinMaxAlgo::utilityFunction(nullptr, plyPlayed);
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

long MinMaxAlgo::utilityFunction(TreeNode* node, std::vector<Position> Played)
{

    long points = 0L;
    long hits = 0;

    if(node != nullptr)
    {
        while(node->parent != nullptr)
        {
        
            Played.push_back(node->positionBoard);
            node = node->parent;
        }
    }

    for(int i = 0; i < Played.size(); i++)
    {
        recursiveDirection(hits, Played.at(i), Position(1, 0), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(points, Played.at(i), Position(-1, 0), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(points, Played.at(i), Position(0, 1), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(points, Played.at(i), Position(0, -1), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(points, Played.at(i), Position(1, 1), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(points, Played.at(i), Position(-1, 1), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(points, Played.at(i), Position(1, -1), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(points, Played.at(i), Position(-1, -1), Played);
        points += calculatePoints(hits);
    }

    return points;
}

bool MinMaxAlgo::isTerminal(TreeNode* node, std::vector<Position> botPlayed)
{


}

void MinMaxAlgo::recursiveDirection(long &points, Position pos, Position direction, std::vector<Position> played)
{
    Position newPos = Position(pos.xPos + direction.xPos, pos.yPos + direction.yPos);

    for(int i = 0; i < played.size(); i++)
    {
        if(played.at(i).xPos == newPos.xPos && played.at(i).yPos == newPos.yPos)
        {
            points++;
            recursiveDirection(points, newPos, direction, played);
        }
    }
}

long MinMaxAlgo::calculatePoints(int hits)
{
    long points = 0L;

    if(hits == 0)      points += 0L;
    else if(hits == 1) points += 1L;
    else if(hits == 2) points += 10L;
    else if(hits == 3) points += 100L;
    else if(hits == 4) points += 1000L;
    else if(hits == 5) points += 10000L;
    else if(hits == 6) points += 100000L;

    return points;
}
