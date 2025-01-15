#ifndef _BINARY_TREE_HPP_
#define _BINARY_TREE_HPP_

#include <iostream>

#include "TreeNode.hpp"

class BinaryTree
{
private:
    TreeNode *_root;
public:
    BinaryTree() : _root(nullptr) {}

    const TreeNode* root() const {return _root;}
    TreeNode* &root() {return _root;}

    TreeNode* find(const std::string &findMe) const;

    void insert(const std::string &newValue);
    void remove(const std::string &toDel);

    std::ostream& print(std::ostream &toStream) const;
};

std::ostream& operator<<(std::ostream &os, const BinaryTree &bt);
#endif
