#include "GraphiqueSDL.h"
#include "tests_minMaxAlgo.h"

int main(int argc, char *argv[]){

    if(argc > 1)
    {
        tests_minMaxAlgo tests;

        bool res = tests.run();

        return res;
    }

    if(!GraphiqueSDL::initialize(6, 6))
    {
        return 1;
    }

    bool jeuActif = true;

    while(jeuActif)
    {
        jeuActif = GraphiqueSDL::afficherUnFrame();
    }

    return 0;
}