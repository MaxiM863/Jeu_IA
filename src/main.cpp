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

    Tree tree(6);

    std::vector<Position> botPos;
    std::vector<Position> plyPos;

    bool plyHasPlayed = false;

    while(jeuActif)
    {

        if(plyHasPlayed)
        {
            plyHasPlayed = false;
            
            Position pos = algo.minMaxRun(&tree, botPos, plyPos);
            
            botPos.push_back(pos);
        }
        else
        {
            Position clickedPos(-1, -1);

            jeuActif = GraphiqueSDL::afficherUnFrame(clickedPos);

            if(clickedPos.xPos != -1)
            {
                plyHasPlayed = true;
            }
        }        
    }

    return 0;
}