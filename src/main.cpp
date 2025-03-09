#include "GraphiqueSDL.h"
#include "tests_minMaxAlgo.h"


int main(int argc, char *argv[]){

    if(argc > 1)
    {
        tests_minMaxAlgo tests;

        bool res = tests.run();

        if(res == true) return 0;

        return 1;
    }

    if(!GraphiqueSDL::initialize(6, 6))
    {
        return 1;
    }

    bool jeuActif = true;

    MinMaxAlgo algo;

    std::vector<Position> botPos;
    std::vector<Position> plyPos;

    bool plyHasPlayed = true;

    while(jeuActif)
    {

        if(plyHasPlayed)
        {
            plyHasPlayed = false;

            Tree tree(6);

            tree.addLevel(botPos, plyPos);
            tree.addLevel(botPos, plyPos);
            tree.addLevel(botPos, plyPos);
            tree.addLevel(botPos, plyPos);

            Position pos = algo.minMaxRun(&tree, botPos, plyPos);
            
            botPos.push_back(pos);

            Position clickedPos(-1, -1);

            GraphiqueSDL::afficherUnFrame(clickedPos);

            GraphiqueSDL::putBotData(pos);
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
            }
        }        
    }

    return 0;
}