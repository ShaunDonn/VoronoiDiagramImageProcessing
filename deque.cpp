/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

/* No argument constructor */
template<class T>
Deque<T>::Deque() {
    n1 = 0;
    n2 = -1;
}


/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template<class T>
void Deque<T>::pushR(T newItem) {
    n2++;
    data.push_back(newItem);
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template<class T>
T Deque<T>::popL() {
    T popped = data[n1];
    n1++;
    
    // resize if we can fit data in 0 to n1-1
    if (n1 > (n2 - n1)) {
        int i = n1;
        int j = 0;
        vector<T> newData;
        while (i <= (int) n2) {
            newData.push_back(data[i]);
            i++;
            j++;
        }
        n1 = 0;
        n2 = j - 1;
        data.clear();
        for(unsigned long i = 0; i < newData.size();i++){
            data.push_back(newData[i]);
        }
    }
    return popped;
}


/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template<class T>
T Deque<T>::popR() {
    T popped = data[n2];
    data.pop_back();
    n2--;
    // resize if we can fit data in 1 to n1
    if (((n1 > (n2 - n1)) && (n1 <= n2)) || ((n1 == n2) && (n1>0))) {
        int i = n1;
        int j = 0;
        vector<T> newData;
        while (i <= (int) n2) {
            newData.push_back(data[i]);
            i++;
            j++;
        }
        n1 = 0;
        n2 = j - 1;
        data.clear();
        for(unsigned long i = 0; i < newData.size();i++){
            data.push_back(newData[i]);
        }
    }
    return popped;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template<class T>
T Deque<T>::peekL() {
    return data[n1];
}


/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template<class T>
T Deque<T>::peekR() {
    return data[n2];
}


/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template<class T>
bool Deque<T>::isEmpty() const {
    return data.size() == 0;
}