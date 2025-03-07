#include "../src/MinMaxAlgo.h"

class tests_minMaxAlgo{

public:

    static bool run() 
    {
        bool result = true;

        if(!tests_minMaxAlgo::test_Utility_1()) result = false;
        

        return result;
    }

private:

    static bool test_Utility_1()
    {

        return true;
    }

};