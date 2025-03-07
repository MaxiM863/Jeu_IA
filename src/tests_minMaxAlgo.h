#include "MinMaxAlgo.h"

class tests_minMaxAlgo{

public:

    bool run() 
    {
        bool result = true;

        if(!test_Utility_1()) result = false;
        

        return result;
    }

private:

    bool test_Utility_1()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        if(algo.testUtility(node, played) != 0) res = false;
        
        return res;
    }

};