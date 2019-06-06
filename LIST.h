//
//  LIST.h
//  Lab 2
//
//  Created by Lily Tang on 4/29/19.
//  Copyright © 2019 Lily Tang. All rights reserved.
//

#ifndef LIST_h
#define LIST_h

#include "NODE.h"
#include <cassert>
template <class ItemType>
class SingleList {
private:
    // head ptr to first node
    Node<ItemType>* headPtr;
    // count of items; returns ptr to given entry node or nullptr
protected:
    int itemCount;
   
public:
    // Constructor
    SingleList();
    // Copy Constructor
    SingleList(const SingleList<ItemType>& list);
    // Virtual Destructor
    virtual ~SingleList();
    // getsize
    int getCurrentSize() const;
    // isEmpty
    bool isEmpty() const;
    // addNode
    bool addNode(const ItemType& newItem);
    bool insertNode(const ItemType& newItem, const int x);
    // deleteNode
    bool deleteNode(const ItemType& anEntry);
    // clear
	void clear();
    // contain
    bool contains(const ItemType& anItem) const;
    int getFrequencyOf(const ItemType& anItem) const;
    // traverses the linked chain to locate an entry (parameter)
    // Returns either a pointer to the node containing a given entry or
    // the null pointer if the entry is not in the bag.
    Node<ItemType>* getPointerTo(const ItemType& target) const;
	void displayList() const;
	Node<ItemType>* getNodeAt(int position) const;
	bool remove(int position);
	ItemType getEntry(int position) const; //throw(PrecondViolatedExcep)
};

template<class ItemType>
ItemType SingleList<ItemType>::getEntry(int position) const //throw(PrecondViolatedExcep)
{
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* NodePtr = getNodeAt(position);
		return NodePtr->getItem();
	}
	//else
	//{
	//	string message = "getEntry() called with an empty list or ";
	//	message = message + " invalid position.";
	//	throw(PrecondViolatedExcep(message));
	//}
}


// Returns either a pointer to the node containing a given entry
// or the null pointer if the entry is not in the bag.
// to be used in the bool contains function
template<class ItemType>
Node<ItemType>* SingleList<ItemType>::getPointerTo(const ItemType& target) const {
    bool found = false;
    Node<ItemType>* curPtr = headPtr;
    while (!found && (curPtr != nullptr)) {
        if (target == curPtr->getItem())
            found = true;
        else
            curPtr = curPtr->getNext();
    } // end while
    return curPtr;
} // end getPointerTo
                    
template<class ItemType>
int SingleList<ItemType>::getCurrentSize() const {
    return itemCount;
} // end getCurrentSize
       
  /** Sees whether this stack is empty.
  @return True if the stack is empty, or false if not. */
template<class ItemType>
bool SingleList<ItemType>::isEmpty() const {
	if (itemCount == 0)
		return true;
	else
		return false;
} // end isEmpty
            
template <class ItemType>
SingleList<ItemType>::SingleList() : headPtr(nullptr), itemCount(0) {
} // end default constructor

template <class ItemType>
SingleList<ItemType>::SingleList(const SingleList<ItemType>& list){
    itemCount = list->itemCount;
    Node<ItemType>* origChainPtr = list->headPtr;
    if (origChainPtr == nullptr)
        headPtr = nullptr; // Original bag is empty; so is copy
    else
    {
        // Copy first node
        headPtr = new Node<ItemType>();
        headPtr->setItem(origChainPtr->getItem());
        // Copy remaining nodes
        Node<ItemType>* newChainPtr = headPtr;
        while (origChainPtr != nullptr)
            // Last-node pointer
        {
            origChainPtr = origChainPtr ->getNext(); // Advance pointer
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();
            // Create a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext(); } // end while
        newChainPtr->setNext(nullptr); // Flag end of new chain // end if
    }
} // end copy constructor

  /** Adds a new item to end of single list
  @post If the operation was successful, newItem is added to end of list
  @param newItem The object to be added as a new item.
  @return True if successful or false if not. */
template<class ItemType>
bool SingleList<ItemType>::addNode(const ItemType& newItem) {
    // Add to beginning of chain: new node references rest of chain;
    // (headPtr is nullptr if chain is empty)
    Node<ItemType>* newNodePtr = new Node<ItemType>();
    newNodePtr->setItem(newItem);
    newNodePtr->setNext(nullptr); // New node points to chain
    if (headPtr != nullptr) {
        // Append the new node to the list
        // Need to find out the pointer to the last node
        Node<ItemType>* curPtr = headPtr;
        while (curPtr->getNext() != nullptr){
            curPtr = curPtr->getNext();
        }
        // Now curPtr is pointing to the last node
		//make the last node now the second last node
		curPtr->setNext(newNodePtr);
    }
    else {
        // Add the node to the empty list
        headPtr = newNodePtr;
    }

    itemCount++;
    return true;
} // end addNode

  /** Adds a new item after a certain item's location
  @post If the operation was successful, newItem is added to end item
  @param newItem The object to be added as a new item, item will determine the location where newItem will be placed
  @return True if successful or false if not. */
template<class ItemType>
bool SingleList<ItemType>::insertNode(const ItemType& newItem, const int x) {
	int count = 0;
	Node<ItemType>* newNodePtr = new Node<ItemType>();
	newNodePtr->setItem(newItem);

	if (headPtr != nullptr) {
		// Append the new node to the list
		// Need to find out the pointer to the last node
		if (x< 1 || x> itemCount + 1) {
			cout << "Invalid postion!" << endl;
			return false;
		}
		else {
			Node<ItemType>* curPtr = headPtr;
			while (curPtr->getNext() != nullptr) {
				curPtr = curPtr->getNext();
				count++;
				if (count == (x - 1)) {
					Node<ItemType>* temp = new Node<ItemType>();
					temp = curPtr->getNext();
					curPtr->setNext(newNodePtr);

					temp = newNodePtr->getNext();
				}
			}
			return true;
		}
	
	}
	else
		return false;
}

/** removes an item in list
@post If the operation was successful, anEntry is removed from list
@param anEntry The object to be removed from list.
@return True if successful or false if not. */
template<class ItemType>
bool SingleList<ItemType>::deleteNode(const ItemType& anEntry) {
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
    if (canRemoveItem){
        // Copy data from first node to located node
        entryNodePtr->setItem(headPtr->getItem());
        // Delete first node
        Node<ItemType>* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();
        // Return node to the system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        itemCount--;
    } // end if
    return canRemoveItem;
} // end deleteNode
        
  /** removes all items in list
  @post If the operation was successful, all items are removed from list
  @param none.
  @return nothing */
template<class ItemType>
void SingleList<ItemType>::clear(){
    Node<ItemType>* nodeToDeletePtr;
    while (headPtr != nullptr) {
        nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();
        
        // Return node to the system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
    } // end while
    
    // headPtr is nullptr
    nodeToDeletePtr = nullptr; 
	itemCount = 0;
}// end clear

 /** checks if list contains an item
 @param none.
 @return True if item exists */
template<class ItemType>
bool SingleList<ItemType>::contains(const ItemType& anEntry) const {
    return (getPointerTo(anEntry) != nullptr);
} // end contains
    
/* counts how many times an item appears in a list
@param anEntry is the item to count 
@return int frequency, which is number of times anEntry is found in list*/
template<class ItemType>
int SingleList<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
    int frequency = 0;
    int counter = 0;
    Node<ItemType>* curPtr = headPtr;
    while ((curPtr != nullptr) && (counter < itemCount)) {
        if (anEntry == curPtr->getItem()) {
            frequency++;
        } // end if
        counter ++;
        curPtr = curPtr->getNext();
    } // end while
    return frequency;
} // end getFrequencyOf



template<class ItemType> SingleList<ItemType>::~SingleList() {
   clear();
} // end destructor

template<class ItemType> 
void SingleList<ItemType>::displayList() const {
	Node<ItemType>* cur = headPtr;
	while (cur != nullptr) {
		ItemType print = cur->getItem();
		cout << print << endl;
		cur = cur->getNext();
	}
}

	template<class ItemType>
	Node<ItemType>* SingleList<ItemType>::getNodeAt(int position) const
	{
		assert((position >= 1) && (position <= itemCount));

		Node<ItemType>* curPtr = headPtr;
		for (int skip = 1; skip < position; skip++)
			curPtr = curPtr->getNext();

		return curPtr;
	}

	template<class ItemType>
	bool SingleList<ItemType>::remove(int position)
	{
		bool ableToRemove = (position >= 1) && (position <= itemCount);
		if (ableToRemove)
		{
			Node<ItemType>* curPtr = nullptr;
			if (position == 1)
			{
				curPtr = headPtr;
				headPtr = headPtr->getNext();
			}
			else
			{
				Node<ItemType>* prevPtr = getNodeAt(position - 1);

				curPtr = prevPtr->getNext();

				prevPtr->setNext(curPtr->getNext());
			}
			curPtr->setNext(nullptr);
			delete curPtr;
			curPtr = nullptr;
			itemCount--;
		}
		return ableToRemove;
	}


#endif /* LIST_h */
