//
//  STACK.h
//  Lab 2
//
//  Created by Lily Tang on 4/29/19.
//  Copyright © 2019 Lily Tang. All rights reserved.
//

#ifndef STACK_h
#define STACK_h

#include "LIST.h"

template<class ItemType>
class Stack : protected SingleList <ItemType> {
public:
  //  Node<ItemType>* top;
    // constructor
	Stack() : SingleList<ItemType>() {};
    // destructor
    ~Stack(){
       
    }
    /** Sees whether this stack is empty.
     @return True if the stack is empty, or false if not. */
    bool isStackEmpty() const {
		return this->isEmpty();
    }
    /** Adds a new entry to the top of this stack.
     @post If the operation was successful, newEntry is at the top of the stack.
     @param newEntry The object to be added as a new entry. */
    void push(const ItemType& newEntry) {
		addNode(newEntry);
    }
    /** Removes the top of this stack.
     @post If the operation was successful, the top of the stack
     has been removed. */
    bool pop(){
        
		return this->remove(this->getCurrentSize());
    }
	/**	@throw Precond if the stack is empty.
	@post returns the item front if the stack is not empty.
	@return item of top if successful
	@param none **/
	//template <class ItemType>
	ItemType peak() const {
			return this->getEntry(this->getCurrentSize());
		
	}

	
    
}; // end Stack



#endif /* STACK_h */
