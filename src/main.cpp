#include "GraphiqueSDL.h"
#include "../tests/tests_minMaxAlgo.h"

int main(int argc, char *argv[]){

    if(argc > 1)
    {

        bool res = tests_minMaxAlgo::run();

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