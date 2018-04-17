//Simon Owens
//Binary tree project
//MP6


#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Binary_Tree {
public:
  Binary_Tree();
  Binary_Tree(const Binary_Tree& source);
  ~Binary_Tree();

  Binary_Tree<T>& operator=(Binary_Tree source);

  void swap(Binary_Tree<T>& b1, Binary_Tree<T>& b2);
  
  void insert(const T& item);
  int size() const;
  int height() const;
  bool find(const T& item) const;
  std::string to_string() const;
  
private:

  struct BTNode {
    T data;
    int priority;
    BTNode* parent;
    BTNode* left;
    BTNode* right;
    BTNode(const T& d = T(),
      	  BTNode* p = 0,
	  BTNode* l = 0,
	  BTNode* r = 0) : data(d),  parent(p), left(l), right(r) {}
  };

  void node_add(BTNode* subtree, BTNode* new_node);
  bool node_find(BTNode* subtree, const T& item) const;
  int node_size(BTNode* subtree) const;
  int node_height(BTNode* subtree) const;
  void node_string(BTNode* subtree, std::ostream & out) const;
  void node_kill(BTNode* subtree);
 
  void SetRight(BTNode* parentN, BTNode* child);
  void SetLeft(BTNode* parentN, BTNode* child); 
  void rotate_right(BTNode* n); 
  void rotate_left(BTNode* n);

  BTNode* node_copy(BTNode* subtree);
  BTNode* root;

};

template <typename T>
Binary_Tree<T>::Binary_Tree() {
  root = 0;    // empty tree
}

template <typename T>
Binary_Tree<T>::Binary_Tree(const Binary_Tree& source) {
  root = node_copy(source.root);
}

template <typename T>
Binary_Tree<T>::~Binary_Tree() {
  node_kill(root);
}

template <typename T>
Binary_Tree<T> &
Binary_Tree<T>::operator=(Binary_Tree source) {
  swap(*this, source);
}

template <typename T>
bool
Binary_Tree<T>::find(const T& item) const {
  return node_find(root, item);

}


template <typename T>
int
Binary_Tree<T>::size() const {
  return node_size(root);
}

template <typename T>
int
Binary_Tree<T>::height() const {
  return node_height(root);
}

template <typename T>
std::string
Binary_Tree<T>::to_string() const {
  std::ostringstream ss;

  node_string(root, ss);
  return ss.str();
}

template <typename T>
void
Binary_Tree<T>::insert(const T& item) {
  BTNode* new_node = new BTNode(item);
  //create the new priority
  new_node->priority=rand();
  if (root == 0) 
    {
      root = new_node;
      
    }
  else 
    {
      //insert a node into the tree, works its way down
     node_add(root, new_node);
     //loop through this until priority is correct or new_node == root
    while((new_node != root)&&(new_node->priority > new_node->parent->priority))
       {
	 //rotation depends on whether you are right or left child
	 if(new_node->parent->left == new_node)
	   rotate_right(new_node);
	 else
	   rotate_left(new_node);
       }
    }
}
//Function:  Setright
// this sets a child pointer as a parent pointers right
template <typename T>
void 
Binary_Tree<T>::SetRight(BTNode* parentN, BTNode* child) {
  
  parentN->right = child;
  //make sure that you aren't given a blank child
  if(child != 0) 
     child->parent = parentN;
 
}

//Function: setleft
// this sets a child pointer as a parent pointers left
template <typename T>
void 
Binary_Tree<T>::SetLeft(BTNode* parentN, BTNode* child) {
  
  parentN->left = child;
  // make sure you arent given a blank child
  if(child != 0) 
     child->parent = parentN;
  
}

//Function: rotate right
// this rotates the given function right.. keeps track of all pointers
template <typename T>
void 
Binary_Tree<T>::rotate_right(BTNode* n)
{
  //make a temporary variable to keep track of the orgininal pointer
  BTNode *temp=n->parent;
  
  //if grandparent isn't headpointer
  if(temp->parent!=0)
    {
      if(temp->parent->right==temp)
	SetRight(temp->parent, n);
      else
	SetLeft(temp->parent,n);
      
    }
  //the node you are rotating is way down 
  else
    {
      root=n;
      n->parent=0;
    }
  //regardless of the case you need to finish up by making
  // the finalizing what you are rotating
  SetLeft(temp,n->right);
  SetRight(n,temp);
}
//Function: rotate left
// this rotates the given node to the left.. keeps track of all pointers
template <typename T>
void 
Binary_Tree<T>::rotate_left(BTNode* n)
{
  //make a temporary variable to keep track of the parent
  BTNode *temp =n->parent;

  //if grandparent isnt null 
  if(temp->parent!=0){
    if(temp->parent->right==temp)
      SetRight(temp->parent, n);
    else
      SetLeft(temp->parent,n);

  }
  //the node you are rotating is far down the tree
  else
    {
      root=n;
      n->parent=0;
    }
  //regardless of the case you need to finish up by making
  // the finalizing what you are rotating
  SetRight(temp,n->left);
  SetLeft(n,temp);
}

/////////////////////////////////////////////////////////
//   Private helper functions below here               //
/////////////////////////////////////////////////////////


template <typename T>
void
Binary_Tree<T>::node_add(BTNode* subtree, BTNode* new_node) {
  if (new_node->data < subtree->data ||
      (new_node->data == subtree->data && rand() % 2 == 0) ) {   // to the left
    if (subtree->left == 0) {              // and there's room
      //replaced with set functions
      SetLeft(subtree, new_node);
      
    } else {// someone else's problem
      node_add(subtree->left, new_node);
    }
  } else { // to the right
    if (subtree->right == 0) {// and there's room
      //replaced with set function 
      SetRight(subtree, new_node);
    } else {
      node_add(subtree->right, new_node);
    }
  } 
}

template <typename T>
bool
Binary_Tree<T>::node_find(BTNode* subtree, const T& item) const {
  
  if (subtree == 0) {
    return false;
  }
  if (subtree->data == item) {
    return true;
  }
  if (item < subtree->data)
    return node_find(subtree->left, item);
  else
    return node_find(subtree->right, item);
}

template <typename T>
int
Binary_Tree<T>::node_size(BTNode* subtree) const {
  if (subtree == 0)
    return 0;
  else
    return 1 + node_size(subtree->left) + node_size(subtree->right);
}

template <typename T>
int
Binary_Tree<T>::node_height(BTNode* subtree) const {
  if (subtree == 0)
    return 0;
  else {
    int lh = node_height(subtree->left);
    int rh = node_height(subtree->right);
    
    int max = (lh > rh) ? lh : rh;

    return 1+max;
  }
}

template <typename T>
void
Binary_Tree<T>::node_string(BTNode* subtree, std::ostream & out) const {
  if (subtree == 0)
    return;
  node_string(subtree->left, out);
  out << subtree->data << std::endl;
  node_string(subtree->right, out);
}

template <typename T>
void
Binary_Tree<T>::node_kill(BTNode* subtree) {
  if (subtree == 0)
    return;
  node_kill(subtree->left);
  node_kill(subtree->right);
  delete subtree;
}

template <typename T>
typename Binary_Tree<T>::BTNode*
Binary_Tree<T>::node_copy(BTNode* subtree) {
  if (subtree == 0)
    return 0;

  return new BTNode(subtree->data,
 node_copy(subtree->left),
 node_copy(subtree->right));
}

template <typename T>
void swap(Binary_Tree<T>& b1, Binary_Tree<T>& b2) {
  std::swap(b1.root, b2.root);
}









// Iterative version with a while loop
// 
// template <typename t>
// void
// Binary_Tree::node_add(BTNode* subtree, BTNode* new_node) {
//   BTNode* current = subtree;
//   while (true) {
//     if (new_node->data <= current->data) {   // to the left
//       if (current->left == 0) {              // and there's room
// current->left = new_node;
// break;
//       } else { 
// current = current->left;
//       }
//     } else {                                 // to the right
//       if (current->right == 0) {             // and there's room
// current->right = new_node;
// break;
//       } else {
// current = current->right;
//       }
//     }
//   }
// }

#endif
