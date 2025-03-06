#include "GraphiqueSDL.h"

int main(){

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