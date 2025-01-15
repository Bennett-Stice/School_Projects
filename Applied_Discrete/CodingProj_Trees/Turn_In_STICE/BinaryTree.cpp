#include "BinaryTree.hpp"
using namespace std;

TreeNode*
BinaryTree::find(const std::string &findMe) const
{
    TreeNode *curr = _root;

    while( curr!= nullptr)
    {
        if (findMe < curr->value() )
        {
            curr = curr->left();
        }
        else if (findMe > curr->value() )
        {
            curr = curr->right();
        }
        else // must be ==
        {
            return curr;
        }
    }

    return nullptr;
}

// intoSubTree -- the subtree we want to insert intoSubTree
// newVal -- the new value we want to insert into the subtree
//
//  returns the updated subtree
TreeNode* insertHelper(TreeNode *intoSubTree, const string &newVal)
{
    if (intoSubTree == nullptr) // if (!intoSubTree)
    {
        TreeNode *newRoot = new TreeNode(newVal);
        return newRoot;
    }

    // if we get here, we have at least one node in the subtree!
    if (newVal < intoSubTree->value() )
    {
        TreeNode *newRoot=insertHelper(intoSubTree->left() , newVal);
        intoSubTree->left() = newRoot;
        newRoot->parent() = intoSubTree;
        return intoSubTree;
    }
    else if (newVal > intoSubTree->value() )
    {
        TreeNode *newRoot=insertHelper(intoSubTree->right() , newVal);
        intoSubTree->right() = newRoot;
        newRoot->parent() = intoSubTree;
        return intoSubTree;
    }
    else // not <, not >, so must be ==
    {
        return intoSubTree;
    }
}
void
BinaryTree::insert(const std::string &newValue)
{
    _root = insertHelper(_root, newValue );
}

void
BinaryTree::remove(const std::string &stringToDel)
{
    TreeNode *toDel = find(stringToDel);
    if (!toDel)
    {
        cerr << "Sorry, \"" << stringToDel << "\" is not in tree!"
            << endl;
        return;
    }
    // case 1: no children ...
    if (toDel->isLeaf())
    {
        // special case
        if (toDel == _root)
        {
            _root=nullptr;
            return;
        }
        TreeNode *parent = toDel->parent();

        if (parent->left() == toDel)
            parent->left() = nullptr;
        else // must be on the right
            parent ->right() = nullptr;

        // following is not strictly necessary ...
        //    .. but lets "clean up" toDel
        toDel->parent() = nullptr;
        delete toDel;  // depending on application, don't do this
        return;
    }
    // case 2: one children
    else if ( ( toDel->right() && !toDel->left() ) ||
              ( toDel->left() && !toDel->right() )
            )
    {
        if (toDel==_root)
        {
            if (toDel->left())
                _root=toDel->left();
            else
                _root=toDel->right();

            _root->parent() = nullptr;
            return;
        }

        TreeNode *subTree;
        if (toDel->left())
            subTree=toDel->left();
        else
            subTree=toDel->right();

        TreeNode *parent = toDel->parent();
        if (parent->left() == toDel)
            parent->left() = subTree;
        else
            parent->right() = subTree;

        subTree->parent() = parent;

        // following is not strictly necessary ...
        //    .. but lets "clean up" toDel
        toDel->left() = toDel->right() = nullptr;
        toDel->parent() = nullptr;
        delete toDel;  // depending on application, don't do this
    }
    // case 3: two children
    else
    {
        // hop once to the right
        TreeNode *curr = toDel->right();
        // go as far left as you can ...
        while (curr->left() )
            curr=curr->left();

        string valToSave = curr->value();
        remove(valToSave);
        toDel->value() = valToSave;
        return;
    }

}

void inOrder(TreeNode *curr, ostream &someStream)
{
        if (!curr)
            return;

        inOrder(curr->right(), someStream);

        for (int i=1; i< curr->depth(); i++)
            someStream << "    ";
        someStream << *curr << endl;


        inOrder(curr->left(), someStream);
}

std::ostream&
BinaryTree::print(std::ostream &toStream) const
{
    inOrder(_root, toStream);
    return toStream;
}


std::ostream& operator<<(std::ostream &os, const BinaryTree &bt)
{
    return bt.print(os);
}
