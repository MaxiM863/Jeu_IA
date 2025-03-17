#include "TreeNode.h"

#define MAX_NODES 1000000

class Tree {

    public:

        Tree(int boardSize) { top = new TreeNode(nullptr, boardSize*boardSize, Position(-1, -1)); this->boardSize = boardSize; }

        TreeNode* getTopTree() { return top; }

        void addLevel(int difficulty, std::vector<Position> bot, std::vector<Position> ply)
        {
            
            recursiveAddNode(top, 0, bot, ply, difficulty);
        }

        int getTreeDepth() 
        { 
            
            int count = 0;

            recursiveLeaf(top, count);
            
            return count;
        }

    private:

        void recursiveLeaf(TreeNode* actual, int& count)
        {       
            
            if(actual->childsCount > 0)
            {

                count++;
                recursiveLeaf(actual->childs[0], count);                
            }
        }

        void recursiveAddNode(TreeNode* actual, int level, std::vector<Position> bot, std::vector<Position> ply, int difficulty)
        {

            std::vector<Position> plyPlayed = ply;
            std::vector<Position> botPlayed = bot;

            if(actual->childsCount == 0)
            {

                TreeNode* tmpActual = actual;

                while(tmpActual->parent != nullptr)
                {
                    if(level % 2 == 0)
                    {
                        plyPlayed.push_back(tmpActual->positionBoard);
                    }
                    else
                    {
                        botPlayed.push_back(tmpActual->positionBoard);
                    }

                    tmpActual = tmpActual->parent;
                }

                for(int i = 0; i < boardSize; i++)
                {
                    for(int j = 0; j < boardSize; j++)
                    {
                        bool testExist = false;

                        for(int k = 0; k < botPlayed.size(); k++)
                        {
                            if(botPlayed.at(k).xPos == i && botPlayed.at(k).yPos == j)
                            {
                                testExist = true;
                                break;
                            }
                        }

                        if(!testExist)
                        {
                            for(int k = 0; k < plyPlayed.size(); k++)
                            {
                                if(plyPlayed.at(k).xPos == i && plyPlayed.at(k).yPos == j)
                                {
                                    testExist = true;
                                    break;
                                }
                            }
                        }

                        if(!testExist)
                        {
                        
                            actual->childs[actual->childsCount++] = (new TreeNode(actual, boardSize * boardSize - plyPlayed.size() - botPlayed.size(), Position(i, j)));
                        }
                    }
                }
            }
            
            if(level < difficulty)
            {
                for(int i = 0; i < actual->childsCount; i++)
                {
                    recursiveAddNode(actual->childs[i], level + 1, bot, ply, difficulty);
                }
            }
        }

    private:

        TreeNode* top;
        int boardSize;
};