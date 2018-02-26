/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    if(root == NULL){
      return;
    }
    Node *realroot = root;
    Node *temp = root->left;

    root->left = root->right;   //I flippedity flip here
    root->right = temp;

    root = root->right;   //Going down the previously left subtree
    mirror();

    root = realroot;    //Going down the right subtree
    root = root->left;
    mirror();

    root = realroot;    //Set root back to original value
    return;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{    // your code here
  typename InorderTraversal<T>::InorderTraversal temp(root);
  typename InorderTraversal<T>::InorderTraversal temp2(root);
  typename TreeTraversal<T>::Iterator it2  = temp2.begin();
  for (typename TreeTraversal<T>::Iterator it = temp.begin(); it != temp.end(); ++it) {
    ++it2;
    Node* itNode = *it;
    Node* it2Node = *it2;
    if(it2Node == NULL)
      break;
    if(it2Node->elem < itNode->elem)
      {return false;}
  }
  return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedHelper(root);
}

//isOrderedRecursive helper
template <typename T>
bool BinaryTree<T>::isOrderedHelper(Node *subroot)const {
  if(subroot->right == NULL && subroot->left == NULL)   //leaf node
    return true;
  if(subroot->right == NULL){                         //Left child only
    if(subroot->left->elem > subroot->elem)
      return false;
    return isOrderedHelper(subroot->left);
  }
  else if(subroot->left == NULL){                     //right child only
    if(subroot->right->elem < subroot->elem)
      return false;
    return isOrderedHelper(subroot->right);
  }
  else{                                               //Full children for node
    if(subroot->left->elem > subroot->elem)
      return false;
    bool left = isOrderedHelper(subroot->left);
    if(subroot->right->elem < subroot->elem)
      return false;
    bool right = isOrderedHelper(subroot->right);
    return (left && right);
  }

}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
    vector<T> path;
    printPathsHelper(paths, path, root);
}
template <typename T>
void BinaryTree<T>::printPathsHelper(vector<vector<T>> &paths, vector<T> path, Node *subroot) const{
  if(subroot == NULL)
    return;
  if(subroot->left == NULL && subroot->right == NULL){
    path.push_back(subroot->elem);
    paths.push_back(path);
    return;
  }
  path.push_back(subroot->elem);
  printPathsHelper(paths, path, subroot->left);
  printPathsHelper(paths, path, subroot->right);

}
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumDistancesHelper(root, 0);
}

template <typename T>
int BinaryTree<T>::sumDistancesHelper(Node* subroot, int height) const{
  if(subroot == NULL)
    return 0;
  else
    return height + sumDistancesHelper(subroot->left, height+1) + sumDistancesHelper(subroot->right, height+1);
}
