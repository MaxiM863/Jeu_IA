#include "oneapi/tbb/task_arena.h"

#include "Tree.h"

#define MAXHITS 4

class MinMaxAlgo {

public:

    MinMaxAlgo();
    MinMaxAlgo(Tree* treeData);
    ~MinMaxAlgo();
    MinMaxAlgo(MinMaxAlgo& copy);

public:

    Position minMaxRun(Tree* tree, std::vector<Position> botPlayed, std::vector<Position> plyPlayed);

    void SetDataTree(Tree* treeData);

    long testUtility(TreeNode* node, std::vector<Position> played);

    bool isFinished(std::vector<Position> Played);

private:

    long runAlgo(TreeNode* node, int depth, bool isMaximizing, long alpha, long beta, std::vector<Position> botPlayed, std::vector<Position> plyPlayed);    
    long utilityFunction(TreeNode* node, std::vector<Position> Played, bool isMaximizing, bool isBot);
    bool isTerminal(long botPoints);

    void recursiveDirection(long& points, Position pos, Position direction, std::vector<Position> botPlayed);

    long calculatePoints(int hits);

private:

    Tree* tree;
};

class tbb_parallel_task {
    public:
        static void set_values(TreeNode* node, int depth, bool isMaximizing, long alpha, long beta, std::vector<Position> botPlayed, std::vector<Position> plyPlayed) {
            _node = node;
            _depth = depth;
            _isMaximizing = isMaximizing;
            _alpha = alpha;
            _beta = beta;
            _botPlayed = botPlayed;
            _plyPlayed = plyPlayed;

            return;
        }
    
        void operator()(const oneapi::tbb::blocked_range<std::size_t>& r) const {
            int begin = (int)r.begin(); //! capture lower range number for this chunk
            int end = (int)r.end(); //! capture upper range number for this chunk
            UpdateState(m_source, m_dest, begin, end);
        }
    
        tbb_parallel_task() {}
    
    private:
        static TreeNode* _node;
        static int _depth;
        static bool _isMaximizing;
        static long _alpha;
        static long _beta;
        static std::vector<Position> _botPlayed;
        static std::vector<Position> _plyPlayed;
    };
