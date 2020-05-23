/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Adds the parameter object to the top of the Stack. That is, the element
 * should go at the beginning of the list.
 *
 * @param newItem The object to be added to the Stack.
 */
template<class T>
void Stack<T>::push(T newItem) {
    myStack.pushR(newItem);
}

/**
 * Removes the object on top of the Stack, and returns it. That is, remove
 * the element at the beginning of the list. You may assume this function
 * is only called when the Stack is not empty.
 *
 * @return The element that used to be at the top of the Stack.
 */
template<class T>
T Stack<T>::pop() {
    return myStack.popR();
}

/**
 * Adds an element to the ordering structure.
 */
template<class T>
void Stack<T>::add(T theItem) {
    push(theItem);
}

/**
 * Removes an element from the ordering structure.
 */
template<class T>
T Stack<T>::remove() {
    return pop();
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 *
 * @return The value of the element at the top of the Stack.
 */
template<class T>
T Stack<T>::peek() {
    return myStack.peekR();
}

/**
 * Determines if the Stack is empty.
 * 
 * @return Whether or not the stack is empty (bool).
 */
template<class T>
bool Stack<T>::isEmpty() const {
    return myStack.isEmpty();
}