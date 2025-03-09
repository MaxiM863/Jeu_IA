#include "GraphiqueSDL.h"
#include "tests_minMaxAlgo.h"
#include <time.h>
#include <random>

#define BOARDSIZE 4
#define DIFFICULTY 6

int main(int argc, char *argv[]){

    if(argc > 1)
    {
        tests_minMaxAlgo tests;

        bool res = tests.run();

        if(res == true) return 0;

        return 1;
    }

    if(!GraphiqueSDL::initialize(BOARDSIZE, BOARDSIZE))
    {
        return 1;
    }

    bool jeuActif = true;

    MinMaxAlgo algo;

    std::vector<Position> botPos;
    std::vector<Position> plyPos;

    bool plyHasPlayed = false;

    srand((unsigned)time(0));

    Position pos = Position(rand()%BOARDSIZE, rand()%BOARDSIZE);
    
    botPos.push_back(pos);

    Position clickedPos(-1, -1);

    GraphiqueSDL::afficherUnFrame(clickedPos);

    GraphiqueSDL::putBotData(pos);

    if(algo.isFinished(botPos))
    {

        jeuActif = false;
        GraphiqueSDL::afficherFin(true);
    }

    while(jeuActif)
    {

        if(plyHasPlayed)
        {
            plyHasPlayed = false;

            Tree tree(BOARDSIZE);

            for(int i = 0; i <= DIFFICULTY; i++)
            {
                tree.addLevel(botPos, plyPos);
            }

            Position pos = algo.minMaxRun(&tree, botPos, plyPos);
            
            botPos.push_back(pos);

            Position clickedPos(-1, -1);

            GraphiqueSDL::afficherUnFrame(clickedPos);

            GraphiqueSDL::putBotData(pos);

            if(algo.isFinished(botPos))
            {

                jeuActif = false;
                GraphiqueSDL::afficherFin(true);
            }
        }
        else
        {
            Position clickedPos(-1, -1);

            jeuActif = GraphiqueSDL::afficherUnFrame(clickedPos);

            if(clickedPos.xPos != -1)
            {
                bool testPresent = false;

                for(int i = 0; i < botPos.size(); i++)
                {
                    if(botPos.at(i).xPos == clickedPos.xPos && botPos.at(i).yPos == clickedPos.yPos)
                    {
                        testPresent = true;
                        break;
                    }
                }

                for(int i = 0; i < plyPos.size(); i++)
                {
                    if(plyPos.at(i).xPos == clickedPos.xPos && plyPos.at(i).yPos == clickedPos.yPos)
                    {
                        testPresent = true;
                        break;
                    }
                }

                if(!testPresent)
                {
                    plyHasPlayed = true;

                    plyPos.push_back(clickedPos);

                    GraphiqueSDL::putPlayerData(clickedPos);

                    if(algo.isFinished(plyPos)) 
                    {
                        jeuActif = false;
                        GraphiqueSDL::afficherFin(false);
                    }
                }                
            }
        }    
        
        if(botPos.size() + plyPos.size() == BOARDSIZE*BOARDSIZE) jeuActif = false;
    }

    return 0;
}