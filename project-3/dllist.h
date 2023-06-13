#ifndef S23_CS20A_LlST_H
#define S23_CS20A_LlST_H

#include<iostream>
#include<assert.h>
// Linked DLList object that maintains both front and rear pointers
// and the size of the list.  Note that you have to keep the front,
// rear and size consistent with the intended state of the DLList 
// otherwise very bad things happen. 
template<typename Type>
class DLList {
public:

	DLList();

	DLList(const DLList<Type>& other);

	DLList<Type>& operator=(const DLList<Type>& other);

	~DLList();

	void	print() const;
	bool	empty() const;

	void	insert_front(const Type &value);
	void	insert_rear(const Type &value);
	void	insert(int idx, const Type &value);

	// Note that the user must front ensure the list is not empty
	// prior to calling these functions. 
	Type	peek_front() const;
	Type	peek_rear() const;
	Type	peek(int idx) const;

	int		count() const;
	int		count_value(const Type &value) const;

	int		find(const Type &value) const;

	bool	remove_front();
	bool	remove_rear();
	bool	remove_index(int idx);
	int		remove_value(const Type &value);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our DLList.
	// Will be implemented along with list
	// member functions
	class DLNode;

	// We'll have both front and rear points for 
	// Fast insertion/deletion from both ends.
	DLNode*	front;
	DLNode*	rear;

	// Keep track of number of nodes in the list
	int		size;
};


/* DLList Implementation
//
//  Since DLList is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* DLNode definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Type>
class DLList<Type>::DLNode {
public:
	DLNode() :nxt(nullptr), prv(nullptr) {}
	DLNode(Type v, DLNode* p, DLNode* n) : val(v), nxt(n), prv(p) {}

	DLNode * next() const { return nxt; }
	void next(DLNode *n) { nxt = n; }

	DLNode * prev() const { return prv; }
	void prev(DLNode *p) { prv = p; }

	Type value() const { return val; }
	void value(const Type &v) { val = v; }

private:
	Type  val;
	DLNode * nxt;
	DLNode * prv;
};



/* DLList default constructor
//		Set front and rear pointer to point to nothing, size is zero
//		Already implemented, nothing to do.
*/
template<typename Type>
DLList<Type>::DLList() :front(nullptr), rear(nullptr), size(0) {
	/*    COMPLETE    */
}


/* Copy constructor
*/
template<typename Type>
DLList<Type>::DLList(const DLList<Type>& other) {

  // If other is null point return nullptr
  if (other.front == nullptr) {
    front = nullptr;
    rear = nullptr;
    size = 0;
    return;
  }

  // Otherwise, set current value to front value
  DLNode* current = new DLNode();
  current->value(other.front->value());
  DLNode* otherNode = new DLNode();
  otherNode = other.front->next();

  front = current;

  // Loop through linked list 
  while(otherNode != nullptr) {
    DLNode* temp = new DLNode();
    temp->value(otherNode->value());

    current->next(temp);
    current->next()->prev(current);

    current = current->next();
    otherNode = otherNode->next();
  }

  rear = current;
  size = other.size;

}
/* Overloaded assignment operator
*/
template<typename Type>
DLList<Type>& DLList<Type>::operator=(const DLList<Type>& other) {

  if (this == &other) {
    return *this;
  }

  DLNode* Node = front;
  while (Node != nullptr) {
    DLNode* next = Node->next();
    delete Node;
    Node = next;
  }

  front = nullptr;
  rear = nullptr;
  size = 0;

  DLNode* current = other.front;

  while(current != nullptr) {

    DLNode* newNode = new DLNode();
    newNode->value(current->value());

    if (rear == nullptr) {
      front = newNode;
    } else {
      rear->next(newNode);
      newNode->prev(rear);
    }

    rear = newNode;
    size++;
    current = current->next();

  }

  if (rear != nullptr) {
    rear->next(nullptr);
  }

  return *this;
}


/* DLList destructor
*/
template<typename Type>
DLList<Type>::~DLList() {
    DLNode* current = front;
    
    // Loop through linked list, delete a each node at a time
    while (current != nullptr) {
      DLNode* next = current->next();
      delete current;
      current = next;
    }
}

/* DLList print
*/
template<typename Type>
void DLList<Type>::print() const {

    DLNode* temp = front;

    // If nullptr nothing to print
    if(temp == nullptr) return;

    // Loop through linked list and print current 
    while(temp != nullptr) {
        std::cout << temp->value();
        if (temp != rear) {
            std::cout << " ";
        }
        temp = temp->next();
    }

}

/* DLList empty
*/
template<typename Type>
bool DLList<Type>::empty() const {
    // Return True if size equal 0
    return size == 0;
}


/* DLList insert_front
*/
template<typename Type>
void DLList<Type>::insert_front(const Type &value) {

    // instantiate new node
    DLNode* newNode = new DLNode();
    newNode->value(value);
    newNode->next(nullptr);
    newNode->prev(nullptr);


    // if front == nullptr set new node to both front and rear
    if (front == nullptr) {
      front = newNode;
      rear = newNode;
    } else {
       // Set new node next to current front
      newNode->next(front);
      // Set current front prev to new node
      front->prev(newNode);
      // set new node to front
      front = newNode;
    }

    size++;
}

/* DLList insert_rear
*/
template<typename Type>
void DLList<Type>::insert_rear(const Type &value) {

    // instantiate new node
    DLNode* newNode = new DLNode();
    newNode->value(value);
    newNode->next(nullptr);
    newNode->prev(nullptr);

    // if rear == nullptr set new node to both front and rear
    if (rear == nullptr) {
      front = newNode;
      rear = newNode;
    } else {
      // Set new node to current rear
      newNode->prev(rear);
      // Set new node to rear
      rear = newNode;
    }

    size++;
}

/* DLList insert
*/
template<typename Type>
void DLList<Type>::insert(int idx, const Type &value) {

  // if index less or equal to 0, insert into front
  if (idx <= 0) {
    insert_front(value);
    return;
  }

  // if index greater or equal to current size, insert into rear
  if (idx >= size) {
    insert_rear(value);
    return;
  }

  DLNode* current = front;
  DLNode* nextNode = front->next();

  // Insert node into index, and set next for each node leading up to index
  for (int i = 0; i < idx - 1; i++) {
    current = current->next();
    nextNode = nextNode->next();
  }

  DLNode* newNode = new DLNode();
  newNode->value(value);

  newNode->next(current->next());
  newNode->prev(current);
  current->next(newNode);
  nextNode->prev(newNode);

  size++;

}

/*  DLList peek_front
*/
template<typename Type>
Type DLList<Type>::peek_front() const {

    // Get front value
	assert(front != nullptr);
    return front->value();
}

/* DLList peek_rear
*/
template<typename Type>
Type DLList<Type>::peek_rear() const {

    // get rear value
	assert(rear != nullptr);
    return rear->value();
}

/* DLList peek
*/
template<typename Type>
Type DLList<Type>::peek(int idx) const {

	assert(idx >= 0 && idx < size);

    DLNode* dlnode = front;

    // Loop to index
    for (int i = 0; i < idx; i++) {
        dlnode = dlnode->next();
    }

    // Show value of index
    return dlnode->value();

}

/* DLList count
*/
template<typename Type>
int DLList<Type>::count() const {
    // return size
    return size;
}

/* DLList count_value
*/
template<typename Type>
int DLList<Type>::count_value(const Type &value) const {

	int retval = 0;

    // Loop through list counting all equal to value
    for (DLNode* dlnode = front; dlnode != nullptr; dlnode = dlnode->next()) {
      if (dlnode->value() == value) {
        retval++;
      }
    }

	return retval;

}
/* DLList find
*/
template<typename Type>
int DLList<Type>::find(const Type &value) const {

  if (front == nullptr) {
    return -1;
  }

  DLNode* current = front;
  int index = 0;
  // Loop through and return at first occurrence of value
  while (current != nullptr) {
    if (current->value() == value) {
      return index;
    }

    index++;
    current = current->next();
  }

  return -1;
}

/* DLList remove_front
*/
template<typename Type>
bool DLList<Type>::remove_front() {

  if (front == nullptr) {
    return false;
  }

  DLNode* frontNode = front;

  // If only 1 node set both rear and front to nullptr
  if (front == rear) {
    front = rear = nullptr;
  } else {
  // Otherwise, set next to front 
    front = front->next();
    front->prev(nullptr);
  }

  // Delete Front
  delete frontNode;

  // Reduce Size by 1
  size--;

  return true;

}
/* DLList remove_rear
*/
template<typename Type>
bool DLList<Type>::remove_rear() {

  if (front == nullptr) {
    return false;
  }

  DLNode* rearNode = rear;
  // If only 1 node set both rear and front to nullptr
  if (front == rear) {
    front = rear = nullptr;
  } else {
    // Otherwise, set prev to rear
    rear = rearNode->prev();
    rear->next(nullptr);
  }

  // Delete rear
  delete rearNode;

  //reduce size
  size--;

  return true;

}

/* DLList remove_index
*/
template<typename Type>
bool DLList<Type>::remove_index(int idx) {

  if (idx < 0 || idx >= size) {
    return false;
  }

  if (idx == 0) {
    remove_front();
    return true;
  }

  if (idx == size - 1) {
    remove_rear();
    return true;
  }

  DLNode* currentNode = front; // first
                               //
  // Get node at index
  for (int i = 1; i == idx; i++) {
    currentNode = currentNode->next(); //second
  }

  // Set Nodes around index to accomodate for removal
  if (currentNode->prev() != nullptr) {
      currentNode->prev()->next(currentNode->next());
  }

  if (currentNode->next() != nullptr) {
      currentNode->next()->prev(currentNode->prev());
  }

  // Reduce Size
  size--;

  // Delete Node
  delete currentNode;

  return true;

}

/* DLList remove_index on value
*/
template<typename Type>
int DLList<Type>::remove_value(const Type &value) {

  if (front == nullptr) {
    return -1;
  }

  DLNode* current = front;
  int index = 0;

  // Loop thorugh whole list, and delete when node value is equal to input value
  while (current != nullptr) {
    if (current->value() == value) {

      // Set Nodes around value to accomodate to removal
      if (current->prev() != nullptr) {
          current->prev()->next(current->next());
      }

      if (current->next() != nullptr) {
          current->next()->prev(current->prev());
      }


      if (current == front) {
        front = current->next();
      }

      if (current == rear) {
        rear = current->prev();
      }

      size--;

      delete current;

      return index;
    }

    index++;
    current = current->next();
  }

  return -1;
}

#endif







































































































// _X_XMXMXI
