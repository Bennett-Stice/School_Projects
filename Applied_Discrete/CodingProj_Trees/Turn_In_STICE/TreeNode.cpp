#include "TreeNode.hpp"

using namespace std;

bool
TreeNode::isLeaf() const
{
    if ( !_left && !_right)
        return true;
    else
        return false;
}

int
TreeNode::depth() const
{
    int hopCount=0;

    TreeNode *curr=(TreeNode *) this;
    while(curr!=nullptr)
    {
        curr=curr->parent();
        hopCount++;
    }

    return hopCount;
}

std::ostream&
TreeNode::print(std::ostream &toStream) const
{
    toStream << _data  << " (" << depth() << ")";
    return toStream;
}

std::ostream& operator<<(std::ostream &os, const TreeNode &tn)
{
    return tn.print(os);
}

