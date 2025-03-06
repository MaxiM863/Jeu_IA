#include "TreeNode.h"

class Tree {

    public:

        TreeNode* getTopTree() { return top; }

        int getTreeDepth() 
        { 
            
            int count = 0;

            recursiveLeaf(top, count);
            
            return count;
        }

    private:

        void recursiveLeaf(TreeNode* actual, int& count)
        {       
            
            if(actual->childs.size() > 0)
            {

                count++;
                recursiveLeaf(actual->childs.at(0), count);                
            }
        }

    private:

        TreeNode* top;
};