#ifndef _TREE_NODE_HPP_
#define _TREE_NODE_HPP_

#include <iostream>
#include <string>

class TreeNode
{
private:
    std::string _data;
    TreeNode *_left;
    TreeNode *_right;
    TreeNode *_parent;
public:
    TreeNode() : _data(), _left(nullptr), _right(nullptr), _parent(nullptr) {}
    TreeNode(const std::string &initVal)
        : _data(initVal), _left(nullptr), _right(nullptr), _parent(nullptr) {}

    // accessors
    const std::string& value() const {return _data;}
    TreeNode* left() const {return _left;}
    TreeNode* right() const {return _right;}
    TreeNode* parent() const {return _parent;}

    // modifiers
    std::string& value() {return _data;}
    TreeNode* &left() {return _left;}
    TreeNode* &right() {return _right;}
    TreeNode* &parent() {return _parent;}

    bool isLeaf() const;
    int depth() const;

    std::ostream& print(std::ostream &toStream) const;
};

std::ostream& operator<<(std::ostream &os, const TreeNode &tn);

#endif


