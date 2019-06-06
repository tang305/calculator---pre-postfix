#ifndef NODE_h
#define NODE_h

using namespace std;

template<class ItemType>
class Node {
private:
    ItemType item; // A data item
    Node<ItemType>* next; // Pointer to next node
public:
    Node();
    Node(const ItemType& anItem);
    Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
    void setItem(const ItemType& anItem);
    void setNext(Node<ItemType>* nextNodePtr);
    ItemType getItem() const ;
    Node<ItemType>* getNext() const ;
}; // end Node

template<class ItemType>
Node<ItemType>::Node() : next(nullptr) {
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr) {
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
item(anItem), next(nextNodePtr) {
} // end constructor

/*sets the item of the node
@post If the operation was succesful the item of the node will store the value of anItem
@param anItem is the value to be stored in item
*/
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
    item = anItem;
} // end setItem

  /*sets next to a pointer
  @post If the operation was succesful the next of the node will point to the address of nextNodePtr 
  @param nextNodePtr is the value to be stored in next
  */
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr) {
    next = nextNodePtr;
} // end setNext

  /*returns item
  @post If the operation was succesful, item is returned
  @param none
  */
template<class ItemType>
ItemType Node<ItemType>::getItem() const {
    return item;
} // end getItem

  /*returns next item of node
  @post If the operation was succesful, next is returned
  @param none
  */
template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {
    return next;
}

#endif
