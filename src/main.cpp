#include "GraphiqueSDL.h"
#include "tests_minMaxAlgo.h"

#define BOARDSIZE 8

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

    bool plyHasPlayed = true;

    int difficulty = 1;

    bool selection = true;

    while(selection)
    {
        
    }

    while(jeuActif)
    {

        if(plyHasPlayed)
        {
            plyHasPlayed = false;

            Tree tree(BOARDSIZE);

            for(int i = 0; i <= dificulty; i++)
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

    return 0;
}