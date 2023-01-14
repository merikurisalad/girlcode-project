/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    n1 = 0;  // left
    n2 = -1; // right
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    data.push_back(newItem);
    n2 += 1;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T leftMostItem = peekL();
    n1 += 1; // increase left index

    if ((n2-n1+1) <= n1) {
        vector<T> newDeque;
        for (int i = n1; i <= n2 ; i++){
            newDeque.push_back(data[i]);
        }

        // reset data
        data.resize(0);
        n1 = 0;
        n2 = -1;

        // add items back to data
        for (unsigned long i=0; i < newDeque.size(); i++){
            pushR(newDeque[i]);
        }
    }
    return leftMostItem;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T rightMostItem = peekR();
    data.pop_back();
    n2 -= 1; // decrease right index

    if ((n2-n1+1) <= n1) {
        vector<T> newDeque;
        for (int i = n1; i <= n2 ; i++){
            newDeque.push_back(data[i]);
        }

        // reset data
        data.resize(0);
        n1 = 0;
        n2 = -1;

        // add items back to data
        for (unsigned long i=0; i < newDeque.size(); i++){
            pushR(newDeque[i]);
        }
    }
    return rightMostItem;

}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data[n1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data[n2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return data.empty();
}
