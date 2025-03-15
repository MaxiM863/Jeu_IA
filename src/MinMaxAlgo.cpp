#include<stdint.h>

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

    runAlgo(tmpNode, tree->getTreeDepth(), true, INT32_MIN, INT32_MAX, botPlayed, plyPlayed);

    return tmpNode->childs.at(tmpNode->valeurChild)->positionBoard;
}

void MinMaxAlgo::SetDataTree(Tree *treeData)
{
}

long MinMaxAlgo::testUtility(TreeNode *node, std::vector<Position> played)
{
    return MinMaxAlgo::utilityFunction(node, played, true, true);
}

bool MinMaxAlgo::isFinished(std::vector<Position> Played)
{
    bool result = false;

    if(MinMaxAlgo::isTerminal(MinMaxAlgo::utilityFunction(nullptr, Played, true, true))) result = true; 
    
    return result;
}

void MinMaxAlgo::func(long* p, int i, int t, TreeNode* node, int depth, bool isMaximizing, long alpha, long beta, std::vector<Position> botPlayed, std::vector<Position> plyPlayed) {
    
    long superMinEval = INT32_MAX;
    
    for(int j = i; j < (i+1)*(node->childs.size()/t); j++)
    {
        long min_eval = INT32_MAX;

        if(j < node->childs.size())
        {            
            for(int i = 0; i < node->childs.at(j)->childs.size(); i++)
            {
                long eval = MinMaxAlgo::runAlgo(node->childs.at(j)->childs.at(i), depth - 1, true, alpha, beta, botPlayed, plyPlayed);

                if(min_eval > eval) 
                {
                    min_eval = eval;
                    node->childs.at(j)->valeurChild = i;
                }  

                beta = std::min(beta, eval);
                
                if(beta <= alpha)
                {
                    break;
                }                
            }
        }

        if(superMinEval > min_eval)
        {
            superMinEval = min_eval;
            node->valeurChild = node->childs.at(j)->valeurChild;
        }
    }

    //mtx.lock();
    p[i] = superMinEval;
    //mtx.unlock();

    return;    
}

long MinMaxAlgo::runAlgo(TreeNode* node, int depth, bool isMaximizing, long alpha, long beta, std::vector<Position> botPlayed, std::vector<Position> plyPlayed)
{
    if(node->parent != nullptr)
    {
        long botPoints;
        long plyPoints;

        if(!isMaximizing)
        {
            botPoints = MinMaxAlgo::utilityFunction(node, botPlayed, !isMaximizing, true);
            plyPoints = MinMaxAlgo::utilityFunction(nullptr, plyPlayed, !isMaximizing, false);
            
            if(isTerminal(botPoints) || depth == 0)
            {
                return botPoints - plyPoints;
            }
        }
        else
        {
            botPoints = MinMaxAlgo::utilityFunction(nullptr, botPlayed, !isMaximizing, true);
            plyPoints = MinMaxAlgo::utilityFunction(node, plyPlayed, !isMaximizing, false);
            
            if(isTerminal(plyPoints) || depth == 0)
            {
                return botPoints - plyPoints;
            }
        }       
    }
        
    if(isMaximizing)
    {
        long max_eval = INT32_MIN;


        for(int i = 0; i < node->childs.size(); i++)
        {
            long eval;

            if(node->parent == nullptr)
            {
                std::thread* t = new std::thread[MAXTHREADS];

                long* p = new long[MAXTHREADS];

                for(int i = 0; i < MAXTHREADS; i++)
                {
                    t[i] = std::thread(&MinMaxAlgo::func, this, std::ref(p), i, MAXTHREADS, std::ref(node), depth - 1, false, alpha, beta, botPlayed, plyPlayed);
                }
                
                for(int i = 0; i < MAXTHREADS; i++)
                {
                    t[i].join();
                    long tmpT = p[i];
                    if(tmpT > max_eval) max_eval = tmpT;
                }

                delete[] t;
                
                return max_eval;
            }
            else
            {
                eval = MinMaxAlgo::runAlgo(node->childs.at(i), depth - 1, false, alpha, beta, botPlayed, plyPlayed);
            }
            

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
        long min_eval = INT32_MAX;

        for(int i = 0; i < node->childs.size(); i++)
        {
            long eval = MinMaxAlgo::runAlgo(node->childs.at(i), depth - 1, true, alpha, beta, botPlayed, plyPlayed);

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

long MinMaxAlgo::utilityFunction(TreeNode* node, std::vector<Position> Played, bool isMaximizing, bool isBot)
{

    long points = 0L;
    long hits = 0;

    if(node != nullptr)
    {
        while(node->parent != nullptr)
        {
        
            if(isMaximizing && isBot)
            {
                Played.push_back(node->positionBoard);
            }
            
            if(!isMaximizing && !isBot)
            {
                Played.push_back(node->positionBoard);
            }
            
            isMaximizing = !isMaximizing;
            node = node->parent;
        }
    }

    for(int i = 0; i < Played.size(); i++)
    {
        recursiveDirection(++hits, Played.at(i), Position(1, 0), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(++hits, Played.at(i), Position(0, 1), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(++hits, Played.at(i), Position(1, 1), Played);
        points += calculatePoints(hits);
        hits = 0;
        recursiveDirection(++hits, Played.at(i), Position(1, -1), Played);
        points += calculatePoints(hits);
        hits = 0;
    }

    return points;
}

bool MinMaxAlgo::isTerminal(long botPoints)
{
    bool test = true;

    if(MAXHITS == 4)
    {
        if(botPoints < 16284L) test = false;
    }
    else if(MAXHITS == 5)
    {
        if(botPoints < 406911L) test = false;
    }

    return test;
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
    else if(hits == 2) points += 25L;
    else if(hits == 3) points += 625L;
    else if(hits == 4) points += 15625L;
    else if(hits == 5) points += 390625L;
    else if(hits == 6) points += 9765625L;

    return points;
}
