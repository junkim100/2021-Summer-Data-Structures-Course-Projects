/* 
This is the Templated Linked List implementation from class.  You will use this to implement the stack described in Stack.cpp
DO NOT MODIFY THIS HEADER FILE. You will not submit this file.
*/

#ifndef __TEMPLATE_LINKEDLIST_HPP
#define __TEMPLATE_LINKEDLIST_HPP

template <class T>
class Node
{
private:
  T data;
  Node<T>* nextPtr;
  Node<T>* prevPtr;
public:
  Node(T x) { data = x; prevPtr = nextPtr = nullptr; }
  T& value() { return data; }
  T value() const { return data; }
  Node<T>* next() { return nextPtr; }
  const Node<T>* next() const { return nextPtr; }
  Node<T>* prev() { return prevPtr; }
  const Node<T>* prev() const { return prevPtr; }
  void setNext(Node<T>* n) { nextPtr = n; }
  void setPrev(Node<T>* p) { prevPtr = p; }
  bool hasPrev() const { return prevPtr != nullptr; }
  bool hasNext() const { return nextPtr != nullptr; }
};

template <class T>
class LinkedList
{
private:
  Node<T>* head;
  Node<T>* tail;
  int size;
public:
  LinkedList() { head = tail = nullptr; size = 0; }
  bool empty() const { return size == 0; }
  int getSize() const { return size; }
  Node<T>* getHead() { return head; }
  const Node<T>* getHead() const { return head; }
  Node<T>* getTail() { return tail; }
  const Node<T>* getTail() const { return tail; }
  Node<T>* getNode(int pos);
  const Node<T>* getNode(int pos) const;
  void insert(T data, Node<T>* before);
  void remove(Node<T>* victim);
  void insert(T data, int pos)
    { if (pos == size) insert(data, tail);
      else insert(data, getNode(pos)->prev()); }
  void remove(int pos)
    { remove(getNode(pos)); }
  ~LinkedList();
  LinkedList(const LinkedList<T>&);
  const LinkedList<T>& operator=(const LinkedList<T>&);
};


template <class T>
Node<T>* LinkedList<T>::getNode(int n)
{ 
  Node<T>* ret = head;
  for (int i = 0; i < n && ret; i++)
    ret = ret->next();
  return ret;
}

template <class T>
const Node<T>* LinkedList<T>::getNode(int n) const
{
  const Node<T>* ret = head;
  for (int i = 0; i < n && ret; i++)
    ret = ret->next();
  return ret;
}

//Add a node with value x at position pos
//pos may be between 0 and size, inclusive
template <class T>
void LinkedList<T>::insert(T value, Node<T>* before)
{
  Node<T>* after;
  if (before != nullptr)
    after = before->next();
  else
    after = head;
  Node<T>* ins = new Node<T>(value);
  ins->setPrev(before);
  ins->setNext(after);

  if (before != nullptr) //At beginning
    before->setNext(ins); //inserting in middle or at end
  else
    head = ins; //at beginning or adding to empty list

  if (before != tail) //or:  after != nullptr
    after->setPrev(ins); //inserting in middle or at beginning
  else
    tail = ins; //at end or adding to empty list
  size++;
}

//Remove the given node from this list
//Note:  will fail if passed a Node* from another list
template <class T>
void LinkedList<T>::remove(Node<T>* victim)
{
  //Sanity check
  if (victim == nullptr)
    return;
  
  if (victim->prev() != nullptr)
    victim->prev()->setNext(victim->next());
  else //removing head
    head = head->next();
  
  if (victim->next() != nullptr)
    victim->next()->setPrev(victim->prev());
  else //removing tail
    tail = tail->prev();

  delete victim;
  size--;
}

//Destroys the linked list
template <class T>
LinkedList<T>::~LinkedList()
{
  Node<T>* temp;
  while (head != nullptr)
  {
    temp = head;
    head = head->next();
    delete temp;
  }
}

//Constructs a copy of the argument
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& copy)
{
  head = nullptr;
  size = copy.size;

  const Node<T>* temp;
  Node<T>* node;
  temp = copy.head;
  while (temp != nullptr)
  {
    node = new Node<T>(temp->value());
    if (head == nullptr)
      head = node;
    else
    {
      tail->setNext(node);
      node->setPrev(tail);
    }
    tail = node;
    temp = temp->next();
  }
}

//Makes this list into a copy of the RHS
template <class T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& copy)
{
  //Copy assignment:  delete existing, then make a copy
  //Could be made more efficient by changing values and either
  // extending or shortening existing list, but much harder to implement!

  if (&copy == this)
    return copy;
  
  Node<T>* node;
  const Node<T>* temp;
  while (head != nullptr)
  {
    node = head;
    head = head->next();
    delete node;
  }
  head = tail = nullptr;
  size = copy.size;

  temp = copy.head;
  while (temp != nullptr)
  {
    node = new Node<T>(temp->value());
    if (head == nullptr)
      head = node;
    else
    {
      tail->setNext(node);
      node->setPrev(tail);
    }
    tail = node;
    temp = temp->next();
  }
  return copy;
}

#endif 