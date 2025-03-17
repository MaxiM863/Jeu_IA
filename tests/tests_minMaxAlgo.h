#include "MinMaxAlgo.h"

class tests_minMaxAlgo{

public:

    bool run() 
    {
        bool result = true;

        if(!test_Utility_1()) result = false;
        if(!test_Utility_2()) result = false;
        if(!test_Utility_3()) result = false;
        if(!test_Utility_4()) result = false;
        if(!test_Utility_5()) result = false;
        if(!test_Utility_6()) result = false;
        if(!test_Utility_7()) result = false;
        if(!test_Utility_8()) result = false;

        if(!test_Algo_1()) result = false;
        if(!test_Algo_2()) result = false;
        //if(!test_Algo_3()) result = false;

        return result;
    }

private:

    bool test_Utility_1()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        if(algo.testUtility(node, played) != 0L) res = false;
        
        return res;
    }

    bool test_Utility_2()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        played.push_back(Position(0, 0));
        
        long test = algo.testUtility(node, played);

        if(test != 4L) res = false;
        
        return res;
    }

    bool test_Utility_3()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        played.push_back(Position(0, 0));
        played.push_back(Position(0, 5));
        played.push_back(Position(5, 0));
        played.push_back(Position(5, 5));
        
        long test = algo.testUtility(node, played);

        if(test != 16L) res = false;
        
        return res;
    }

    bool test_Utility_4()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        played.push_back(Position(0, 0));
        played.push_back(Position(0, 1));
        played.push_back(Position(1, 0));
        played.push_back(Position(1, 1));

        // 5*25 + 2*3 + 1
        
        long test = algo.testUtility(node, played);

        if(test != 160L) res = false;
        
        return res;
    }

    bool test_Utility_5()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        played.push_back(Position(0, 0));
        played.push_back(Position(0, 1));
        played.push_back(Position(0, 2));

        // 625*1 + 25*1 + 3*1 + 1
        
        long test = algo.testUtility(node, played);

        if(test != 660L) res = false;
        
        return res;
    }

    bool test_Utility_6()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        played.push_back(Position(1, 1));
        played.push_back(Position(2, 2));
        played.push_back(Position(3, 3));
        played.push_back(Position(4, 4));

        // 15625*1 + 625*1 + 25*1 + 3*2 + 3
        
        long test = algo.testUtility(node, played);

        if(test != 16288L) res = false;
        
        return res;
    }

    bool test_Utility_7()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = nullptr;

        std::vector<Position> played;

        played.push_back(Position(1, 1));
        played.push_back(Position(2, 2));
        played.push_back(Position(3, 3));
        played.push_back(Position(4, 4));
        played.push_back(Position(5, 5));

        // 390625*1 + 15625*1 + 625*1 + 25*1 + 4*2 + 3
        
        long test = algo.testUtility(node, played);

        if(test != 406916L) res = false;
        
        return res;
    }

    bool test_Utility_8()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        TreeNode* node = new TreeNode(nullptr, 36, Position(5, 5));

        std::vector<Position> played;

        played.push_back(Position(1, 1));
        played.push_back(Position(2, 2));
        played.push_back(Position(3, 3));

        node->parent = new TreeNode(new TreeNode(new TreeNode(nullptr, 36, Position(-1, -1)), 
            36, Position(4, 4)), 36, Position(4, 2));

        // 390625*1 + 15625*1 + 625*1 + 25*1 + 4*2 + 3
        
        long test = algo.testUtility(node, played);

        if(test != 406916L) res = false;

        delete(node->parent->parent);
        delete(node->parent);
        delete(node);
        
        return res;
    }

    bool test_Algo_1()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        Tree* tree = new Tree(6);

        std::vector<Position> played;

        played.push_back(Position(1, 1));
        played.push_back(Position(2, 2));

        std::vector<Position> playedPly;

        playedPly.push_back(Position(0, 0));
        playedPly.push_back(Position(4, 4));
        
        tree->addLevel(2, played, playedPly);

        Position posOptimal = algo.minMaxRun(tree, played, playedPly);        

        if(posOptimal.xPos != 3 || posOptimal.yPos != 3) res = false;
        
        return res;
    }

    bool test_Algo_2()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        Tree tree(6);

        std::vector<Position> played;

        played.push_back(Position(1, 1));
        played.push_back(Position(0, 3));

        std::vector<Position> playedPly;

        playedPly.push_back(Position(2, 2));
        playedPly.push_back(Position(4, 4));
        
        tree.addLevel(2, played, playedPly);

        Position posOptimal = algo.minMaxRun(&tree, played, playedPly);        

        if(posOptimal.xPos != 3 || posOptimal.yPos != 3) res = false;
        
        return res;
    }

    bool test_Algo_3()
    {
        MinMaxAlgo algo;

        bool res = true;
        
        Tree tree(6);

        std::vector<Position> played;

        played.push_back(Position(0, 0));
        played.push_back(Position(0, 1));
        played.push_back(Position(2, 0));
        played.push_back(Position(3, 0));
        played.push_back(Position(1, 3));
        played.push_back(Position(2, 4));
        played.push_back(Position(5, 5));

        std::vector<Position> playedPly;

        playedPly.push_back(Position(0, 3));
        playedPly.push_back(Position(1, 1));
        playedPly.push_back(Position(2, 2));
        playedPly.push_back(Position(3, 3));
        playedPly.push_back(Position(2, 1));
        playedPly.push_back(Position(1, 2));
        playedPly.push_back(Position(3, 5));
        
        tree.addLevel(4, played, playedPly);

        Position posOptimal = algo.minMaxRun(&tree, played, played);        

        if(posOptimal.xPos != 3 || posOptimal.yPos != 3) res = false;
        
        return res;
    }
};