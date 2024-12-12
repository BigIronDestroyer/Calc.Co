#ifndef TREE_HPP
#define TREE_HPP

#include <string>

namespace tree
{
    class BinaryTree
    {
    public:
        struct Node
        {
            std::string value = "";
            // pointers are used to create nodes dynamicly
            Node *left;
            Node *right;
            
            //constructor
            Node(const std::string &v) : value(v), left(nullptr), right(nullptr) {}
        };

        Node *insertNode(BinaryTree::Node *root, BinaryTree::Node *&left, BinaryTree::Node *&right);
        Node *createNode(std::string v);
        Node *createNumberNode(std::string o, double v);
        Node *createOperatorNode(std::string o, double v);
        long double evaluateTree(BinaryTree::Node *tree);
        

    private:
        Node *root;
        long double _rec_evaluateTree(BinaryTree::Node *cur_node);
        std::string printNode(BinaryTree::Node* root);
        void _rec_printTree(BinaryTree::Node *root);
        void printTree(BinaryTree::Node *tree);
    };
}
#endif