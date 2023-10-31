#include "slist.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
Class Library File
*/

// Constructor
LinkedList::LinkedList() { head = new Node(); }

// Destructor
LinkedList::~LinkedList() {
  clear();
  delete head;
}

// add(value)				//Adds a new value to the end of this
// list.
int LinkedList::add(Node *node) {
  int s = size();

  if (s == 0) {
    printf("size is 0\n");
    head->nextNode = node;
  } else {
    get(s - 1)->nextNode = node;
  }

  node->nextNode = nullptr;
  if (s==0) printf("finished add\n");
  return s+1;
}

// clear()					//Removes all elements from this
// list.
void LinkedList::clear() {
  head = nullptr;
  clearFrom(head->nextNode);
}

void LinkedList::clearFrom(Node *node) {
  if (node->nextNode == nullptr)
    return;

  clearFrom(node->nextNode);
  delete node;
}

// equals(list)				//Returns true if the two lists contain
// the same elements in the same order.
bool LinkedList::equals(LinkedList other) {
  if (other.size() != size())
    return false;

  for (int i = 0; i < size(); i++) {
    if (get(i)->data->code != other.get(i)->data->code) {
      return false;
    }
  }
  return true;
}

// get(index)				//Returns the element at the specified
// index in this list.
Node *LinkedList::get(int index) {
  Node *next = head->nextNode;
  //cout << "index: " << index << endl;
  // printf("head is null: %i\n", head == nullptr);
  // printf("head next node is null: %i\n", head->nextNode == nullptr);
  for (int i = 0; i < index; i++) {
    // printf("looping through get\n");
    if (next == nullptr) {
      //printf("empty node\n");
      return nullptr;
    }

    next = next->nextNode;
  }
  //cout << "node: " << (next == nullptr) << endl;
  //cout << "code: " << (next->data == nullptr) << endl;
  return next;
}

// insert(index, value)		//Inserts the element into this list before the
// specified index.
void LinkedList::insert(int index, Node *node) {
  if (index < 0)
    return;
  if (index == 0) {
    node->nextNode = head->nextNode;
    head = node;
  }
  if (index > size()) {
    Node *old = get(size() - 1);
    old->nextNode = node;
    node->previousNode = old;
  }

  Node *before = get(index);
  node->nextNode = before->nextNode;
  before->nextNode = node;
  node->previousNode = before;
  node->nextNode->previousNode = node;
}

// exchg(index1, index2)		//Switches the payload data of specified
// indexex.
void LinkedList::exchg(int index1, int index2) {
  Node *node1 = get(index1);
  Node *node2 = get(index2);
  Data *temp = node1->data;
  node1->data = node2->data;
  node2->data = node1->data;
}

// swap(index1,index2)		//Swaps node located at index1 with node at
// index2
void LinkedList::swap(int index1, int index2) {
  Node *node1 = get(index1);
  Node *node2 = get(index2);
  Node *temp = node1;
  node1 = node2;
  node2 = temp;
}

// isEmpty()				//Returns true if this list contains no
// elements.
bool LinkedList::isEmpty() { return size() == 0; }

// remove(index)			//Removes the element at the specified
// index from this list.
void LinkedList::remove(int index) {
  Node *removed = get(index);
  removed->previousNode->nextNode = removed->nextNode;
}

// set(index, value)		//Replaces the element at the specified index in
// this list with a new value.
void LinkedList::set(int index, Node *node) {
  Node *old = get(index);
  old = node;
}

// size()					//Returns the number of elements
// in this list.
int LinkedList::size() {
  int count = -1;
  Node *current = head;
  while (current != nullptr) {
    count++;
    current = current->nextNode;
  }
  return count;
}

Data::Data() {
  code = nullptr;
  longitude = NAN;
  latitude = NAN;
}

Data::Data(char *c, double longitude, double latitude) {
  code = c;
  this->longitude = longitude;
  this->latitude = latitude;
}

Data::~Data() {
  if (code != nullptr)
    delete code;
}

Node::Node() {
  data = new Data();
  nextNode = nullptr;
  previousNode = nullptr;
}

Node::Node(Data* d) {
  data = d;
  nextNode = nullptr;
  previousNode = nullptr;
}

Node::Node(Data* d, Node *nextnode) {
  data = d;
  nextNode = nextnode;
  previousNode = nullptr;
}

Node::Node(Data* d, Node *nextnode, Node *previousnode) {
  data = d;
  nextNode = nextnode;
  previousNode = previousnode;
}

Node::~Node() {
  if (data != nullptr)
    delete data;

  if (nextNode != nullptr)
    delete nextNode;

  if (previousNode != nullptr)
    delete previousNode;
}