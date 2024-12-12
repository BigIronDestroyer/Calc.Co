#include <iostream>
#include <string>
#include<sstream>
#include "../include/calculations.hpp"
#include "../include/tree.hpp"

namespace tree
{

    BinaryTree::Node *BinaryTree::createNode(std::string value)
    {
        // create a new node
        return new BinaryTree::Node(value);
    }

    BinaryTree::Node *BinaryTree::insertNode(BinaryTree::Node *root, BinaryTree::Node *&left, BinaryTree::Node *&right)
    {
        // add the left and right if they are not nullptr
        if (left != nullptr)
        {
            root->left = left;
        }

        if (right != nullptr)
        {
            root->right = right;
        }

        return root;
    };

    std::string BinaryTree::printNode(BinaryTree::Node *cur_node)
    {
        if(cur_node != nullptr){
           return cur_node->value; 
        }
        
        return "";
    }

    // recursivly print the tree inorder
    void BinaryTree::_rec_printTree(BinaryTree::Node *cur_node)
    {

        // visit left node
        if (cur_node->left != nullptr)
        {
            BinaryTree::_rec_printTree(cur_node->left);
        }

        // print node
        std::cout<< BinaryTree::printNode(cur_node);

        // visit left node
        if (cur_node->right != nullptr)
        {
            BinaryTree::_rec_printTree(cur_node->right);
        }
    }

    // print the tree inorder
    void BinaryTree::printTree(BinaryTree::Node *root)
    {
        if (root == nullptr)
        {
            std::printf("Empty equation");
            
        } else{
            BinaryTree::_rec_printTree(root);
            std::cout<<std::endl;
        }
    }

    // recursivly print the tree inorder
    long double BinaryTree::_rec_evaluateTree(BinaryTree::Node *cur_node)
    {
        // base case
        //if the cyrent node is a leaf node
        if (!cur_node->left && !cur_node->right)
        {
            return std::stod(cur_node->value); // Convert string value to double
        }
        
        long double left = 0, right = 0;

        // visit left node
        if (cur_node->left)
        {   
            left = BinaryTree::_rec_evaluateTree(cur_node->left);
        }

        // visit right node
        if (cur_node->right )
        {
            right = BinaryTree::_rec_evaluateTree(cur_node->right);
        }
        
        return calculate::solve(cur_node->value, left, right);

    }

    // calculate equations stored in tree
    long double BinaryTree::evaluateTree(BinaryTree::Node *root)
    {
        if (!root)
        {
            throw std::runtime_error("Error: Cannot evaluate an empty tree");
        }
        return _rec_evaluateTree(root);
    }


}