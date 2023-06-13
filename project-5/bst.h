#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include<functional>
#include<iostream>
#include<assert.h>
#include"bstnode.h"

template<typename Item>
class BinarySearchTree {

public:
	// Public Interface Functions: All of these are implemented
	BinarySearchTree();
	~BinarySearchTree();

	void	printInorder();
	void	printPostorder();
	void	printPreorder();
	void	insert(Item item);

	void	remove(Item item);

	Item	min() const;
	Item	max() const;
	int		height() const;
	bool	search(Item item) const;

	bool	empty() const;

	void	printTree() const;

private:

	// Member variable root
	Node<Item>* root;

	//Auxillary recursive bst functions
	//public interface functions call these
	//You will implement these functions.

	// Tree traversal, second parameter is a "function" with 
	// return type void and parameter Node*, i.e: 
	//					void process(Node* )
	void inorder(Node<Item>* node, std::function<void(Node<Item>*)> proc);
	void preorder(Node<Item>* node, std::function<void(Node<Item>*)> proc);
	void postorder(Node<Item>* node, std::function<void(Node<Item>*)> proc);

	Node<Item>* min(Node<Item> *node) const;
	Node<Item>* max(Node<Item> *node) const;
	int   height(Node<Item>* node) const;

	Node<Item>* insert(Node<Item> *node, Item item);
	bool  search(Node<Item> *node, Item item) const;

	Node<Item>* remove(Node<Item> *node, Item item);

	void  printTree(Node<Item> *node, int space) const;
};


//----------------------------------------------------------
//-------------- Binary Search Tree Function Implementations 
// 
//  Public Interface functions
// 		Completley Implemented, nothing to do.  These functions 
//      call the recursive helper functions you will implement
//		below.

// Constructor
template<typename Item>
BinarySearchTree<Item>::BinarySearchTree() :root(nullptr) {}

// Destructor
template<typename Item>
BinarySearchTree<Item>::~BinarySearchTree() {

	//Use the post order traversal to delete the nodes.
	//lambda function to delete a node n: 
	//				[](Node* n) {delete n; } 
	postorder(root, [](Node<Item>* n) {delete n; });
}
template<typename Item>
void BinarySearchTree<Item>::printInorder() {

	//Use inorder traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item() << std::endl; }"
	inorder(root, [](Node<Item>* n) {std::cout << n->item() << " "; });

	std::cout << std::endl;
}
template<typename Item>
void BinarySearchTree<Item>::printPreorder() {

	//Use pre order traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item() << std::endl; }"
	preorder(root, [](Node<Item>* n) {std::cout << n->item() << " "; });
	std::cout << std::endl;
}
template<typename Item>
void BinarySearchTree<Item>::printPostorder() {

	//Use post order traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item() << std::endl; }"
	postorder(root, [](Node<Item>* n) {std::cout << n->item() << " "; });
	std::cout << std::endl;
}
template<typename Item>
void BinarySearchTree<Item>::insert(Item item) {
	root = insert(root, item);
}
template<typename Item>
void BinarySearchTree<Item>::remove(Item item) {
	root = remove(root, item);
}
template<typename Item>
Item	BinarySearchTree<Item>::min() const {

	assert(root != nullptr);

	Node<Item>* node = min(root);
	return node->item();
}
template<typename Item>
Item	BinarySearchTree<Item>::max() const {

	assert(root != nullptr);

	Node<Item>* node = max(root);
	return node->item();
}
template<typename Item>
int	BinarySearchTree<Item>::height() const {

	return height(root);
}
template<typename Item>
bool BinarySearchTree<Item>::search(Item item) const {
	return search(root, item);
}
template<typename Item>
bool BinarySearchTree<Item>::empty() const {
	return (root == nullptr);
}
template<typename Item>
void BinarySearchTree<Item>::printTree() const {
	printTree(root, 0);
}

//----------------------------------------------------------
//
// Private Recursive Functions: You Implement These.
//

// Inorder Traversal: Implemented so you can see how passing a function into 
// another function works, other traversals remain for you to implement.  the second
// parameter, proc, is a function and we see that its return type is void and it 
// has a Node* as a parameter.  Any function of that form passed into inorder will be
// called as seen below.  
// If we assume that we use the printing lambda defined above you can imagine that proc 
// is defined as:
//		void proc(Node<Item> * n){std::cout << n->item() << " "; }
template<typename Item>
void BinarySearchTree<Item>::inorder(Node<Item>* node, std::function<void(Node<Item>*)> proc) {

    // Left, Middle , Right


	if (node != nullptr){
        inorder(node->left(), proc);
        proc(node);
        inorder(node->right(), proc);
    }

}

template<typename Item>
void BinarySearchTree<Item>::postorder(Node<Item>* node, std::function<void(Node<Item>*)> proc) {

    // Left, Right , Middle
    
	if (node != nullptr){
        postorder(node->left(), proc);
        postorder(node->right(), proc);
        proc(node);
    }

}
template<typename Item>
void BinarySearchTree<Item>::preorder(Node<Item>* node, std::function<void(Node<Item>*)> proc) {

    // Middle, Left, Right 

	if (node != nullptr){
        proc(node);
        preorder(node->left(), proc);
        preorder(node->right(), proc);
    }

}

// BinarySearchTree::insert recursively inserts into the BST according 
// to the rules of the BST.  
template<typename Item>
Node<Item>* BinarySearchTree<Item>::insert(Node<Item>* node, Item item) {

  // BaseCase: If node is equal to nullptr create new node
  if (node == nullptr) {
    return new Node<Item>(item, nullptr, nullptr);
  }

  // If item is less than value of node insert into left sub-tree recursively.
  if (item < node->item()) {
    node->left(insert(node->left(), item));
  }

  // If item is greater than value of node insert into right sub-tree recursively.
  else if (item > node->item()) {
    node->right(insert(node->right(), item));
  }

  return node;
}

// BinarySearchTree<Item>::search recursively searches the tree for item.
template<typename Item>
bool BinarySearchTree<Item>::search(Node<Item>* node, Item item) const {

  // BaseCase: If node is equal to nullptr item is not in tree
  if (node == nullptr) {
    return false;
  }

  // If item value is the same as specific Node value, the item is in the tree
  if (item == node->item()) {
    return true;
  }

  // If item is less than value of node search into left sub-tree recursively.
  if (item < node->item()) {
    return search(node->left(), item);
  }

  // If item is greater than value of node search into left sub-tree recursively.
  return search(node->right(), item);
}

// BinarySearchTree<Item>::height
// Height of a binary tree is the height of the largest subtree + 1
// An empty tree has height 0;
template<typename Item>
int	BinarySearchTree<Item>::height(Node<Item>* node) const {

 // BaseCase: If the node is nullptr, the height is 0.
  if (node == nullptr) {
    return 0;
  }

  // recursively get heights of left and right subtrees 
  int leftHeight = height(node->left());
  int rightHeight = height(node->right());

  // Determine and return the bigger height (Between Left and Right Subtrees) and add 1 for the base node
  return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// BinarySearchTree<Item>::min recursively obtain the node with the minimum item
template<typename Item>
Node<Item>* BinarySearchTree<Item>::min(Node<Item>* node) const {

 // BaseCase: If the node is nullptr, there is no minimum as the tree is empty
  if (node == nullptr) {
    return nullptr;
  }

  // BaseCase: Reached bottom of left subtree and hence the current node is the minimum
  if (node->left() == nullptr) {
    return node;
  }

  // Continue searching the left most substree to find minimum recursively
  return min(node->left());
}

// BinarySearchTree<Item>::max recursively obtain the node with the minimum item
template<typename Item>
Node<Item>* BinarySearchTree<Item>::max(Node<Item>* node) const {

  
 // BaseCase: If the node is nullptr, there is no maximum as the tree is empty
  if (node == nullptr) {
    return nullptr;
  }

  // BaseCase: Reached bottom of right subtree and hence the current node is the maximum
  if (node->right() == nullptr) {
    return node;
  }

  // Continue searching the right most substree to find maximum recursively
  return max(node->right());
}

// BinarySearchTree<Item>::printTree
// Prints the BST in a tree format rotated -90 degrees.  Uses space to 
// signify the space between levels of the tree. Uses the inorder 
// traversal but traverses right first, rather than left. Cannot use
// any of the other travel functions because of this.
//
// parameter space determines the number of spaces needed for each level.
// Example binary shows 5 spaces between levels. 
//
// i.e. traverse right 
//		print appropriate number of spaces 
//		print item 
//		traverse left
//
// It never makes sense to use loops to facilitate increasing recursive depth
// But that doesn't mean you should not use loops for other purposes that are
// not related to the actuall recursion.  
template<typename Item>
void BinarySearchTree<Item>::printTree(Node<Item>* node, int space) const {

    // Determine Spacing as specific in the spec
    int numberOfSpaces = 5;

    // BaseCase: If nullptr nothing to print
    if(node == nullptr){
        return;
    }

    // Increment the spacing right based on the level
    space += numberOfSpaces;

    // Get to further most right node to start printing 
    printTree(node->right(), space);

    std::cout << std::endl;
    for (int i = numberOfSpaces; i < space; i++) {
        // Print Number of Spaces equivalent to level
        std::cout << " ";
    }
    // Print Current Value
    std::cout << node->item() << std::endl;

    // Get to further most left node to start printing 
    printTree(node->left(), space);
}


//BinarySearchTree<Item>::remove
//
// Make sure you're comfortable with the iterative solution seen in the lecture slides
// before thinking about how to do it recursively.
//
// Recursively removes a node in the binary tree.  The recursive algorithm will 
// be different than the iterative algorithm.  The iterative algorithm conisted
// of first finding the node using two pointers so that we know how to rearrange
// the children of the deleted node. In recursion we are passing in the sub trees
// each recursive step, so by definition we already have a handle on each subtrees'
// parents (it is the node that is passed into the previous recursive step).
// After we search the node to remove (if it is in the tree) everything else is the same, we  
// handle the three cases: leaf, one child (which consist of two cases: left vs right),
// and two children.  With iterative algorithm there were subcases regardling if the 
// node was root or not, with recursion we get that for free.  
//
// In the iterative algorithm discussed in class, in dealing with a node with two children
// We swapped items from one of the nodes in either subtree.  For the recursive algorithm
// We just want to write the subtree node's item into the node to be deleted, not actually 
// swap. This way subtree remains a valid bst, so we can recurse on that subtree and 
// recursively call _deleteNode on that item (not the original) to remove that node.  
// 
// It takes a bit to wrap your head around this, use the 6 steps, draw lots of pictures.
// 
template<typename Item>
Node<Item>* BinarySearchTree<Item>::remove(Node<Item>* node, Item item) {


    // BaseCase: If nullptr nothing to remove
    if (node == nullptr) {
        return node;
    }

    // If item is less than current node item remove it recursively from left subtree 
    if (item < node->item()) {

        node->left(remove(node->left(), item));

    // If item is greater than current node item remove it recursively from right subtree 
    }  else if (item > node->item()) {

        node->right(remove(node->right(), item));

    }else{

        // If current node has no children
        if (node->left() == nullptr && node->right() == nullptr) {
            return nullptr;
        }
            
        // Check if current node has only 1 child either left or right
        Node<Item>* temp;

        if (node->left() == nullptr) {
          temp = new Node<Item>(item, nullptr, nullptr);
          temp = node->right();

          free(node);

          return temp;
        }

        // Check if current node has only 1 child either left or right
        if (node->right() == nullptr) {
          temp = new Node<Item>(item, nullptr, nullptr);
          temp = node->left();

          free(node);

          return temp;
        }

        // If current node has two children

        // Determine minimum value of right node
        Node<Item>* tempTwo = min(node->right());

        // Swap the current node value for the minimum node value
        node->item(tempTwo->item());

        // Remove minimum node on right subtree
        node->right(remove(node->right(), tempTwo->item()));

    } 

    return node;

}



// MMXM


#endif//BINARYSEARCHTREE_H_MMX
