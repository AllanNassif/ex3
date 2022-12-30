

#ifndef QUEUE_H
#define QUEUE_H

#include <new>
#include <cassert>


template <class T>
class Queue {

public:

    /*
     * C'tor for Queue class.
     *
     * @return
     * A new instance of Queue.
     * @exception
     * std::bad_alloc exception might be thorwn.
    */
    Queue();

    /*
     * D'tor for Queue class.
     * 
    */
    ~Queue();

    /*
     * Copy constructor for Queue class.
     * 
     * @param queue - the object used to initialize a new instance of Queue.
     * @exception
     * std::bad_alloc exception might be thorwn,
     * as well as, a random exception might be thrown.
    */
    Queue(const Queue& queue);

    /*
     * operator= - assignemnt operator.
     * 
     * @param otherQueue - the object used for assignemnt.
     * @exception
     * std::bad_alloc exception might be thorwn,
     * as well as, a random exception might be thrown.
    */
    Queue& operator=(const Queue& otherQueue);

    
    /*
     * pushBack - Inserts a new member at the end of the queue.
     *
     * @param argumentToAdd - new memeber to add at the end of the queue.
     * @exception
     * std::bad_alloc exception might be thorwn,
     * as well as, a random exception might be thrown.
    */
    void pushBack(const T& argumentToAdd);

    /*
     * front - first element in the queue.
     * 
     * @return
     * Returns first element in the Queue if Queue is not empty
     * @exception
     * Throws an exception if Queue is empty - EmptyQueue exception
     * 
    */
    T& front();

   /*
     * front - first element in the queue (for const Queue).
     * 
     * @return
     * Returns first element in the Queue if Queue is not empty
     * @exception
     * Throws an exception if Queue is empty - EmptyQueue exception
    */
    const T& front() const;

    /*
     * popFront - Removes the first element in the queue.
     * 
     * 
     * @exception
     * EmptyQueue exception, in case the Queue is empty
     * or std::bad_alloc exception might be thorwn,
     * as well as, a random exception might be thrown.
    */
    void popFront();

    /*
     * size - the number of elements in Queue.
     * 
     * @return
     * Returns the number of elements in Queue.
    */
    int size() const;

    /*
     * Iterator - Iterator for queue
    */
    class Iterator;

    /*
     * ConstIterator - Iterator for const queue
    */
    class ConstIterator;

    /*
     * begin - begin iterator
     * 
     * @return
     * Returns Iterator to the beginning of queue.
     * 
    */
    Iterator begin();

    /*
     * end - end iterator
     * 
     * @return
     * Returns Iterator to the end of queue.
     * 
    */
    Iterator end();

    /*
     * begin - begin iterator 
     * 
     * @return
     * Returns ConstIterator to the beginning of queue.
     * 
    */
    ConstIterator begin() const;

    /*
     * end - end iterator
     * 
     * @return
     * Returns ConstIterator to the end of queue.
     * 
    */
    ConstIterator end() const;

    /*
     * EmptyQueue - Exception for invalid operations on empty queue
    */
    class EmptyQueue {};
    

private:
    T* m_data;
    int m_dataSize;
    int m_currentIndex;

    /* The factor by which to expand the array when needed */
    static const int EXPAND_RATE = 2;
    
    /* The initial data size of Queue */
    static const int INITIAL_SIZE = 10;

    /* first index of array */
    static const int FIRST_INDEX = 0;
   
    
    /*
     * expand - expands the array by EXPAND_RATE factor
     * @exception
     * std::bad_alloc exception might be thorwn,
     * as well as, a random exception might be thrown.
    */
    void expand();

    /*
     * compress - compress the array to the current size of data.
     * @exception
     * std::bad_alloc exception might be thorwn,
     * as well as, a random exception might be thrown.
    */
    void compress();


    /*
     * copyData - copy data from source queue into destination data
     * 
     * @param destinationData - destination to paste the data from source queue.
     * @param destinationDataSize - size of the destination data.
     * @param sourceQueue - queue that the data will be copied from.
     * @exception
     * A random exception might be thrown.
    */
    static void copyData(T* const destinationData, int destinationDataSize, const Queue<T>& sourceQueue);

    /*
     * updateData - update the data of queue
     *
     * @param newData - the new data to be applied to the current queue data 
     * 
    */
    void updateData(T* newData);

    /*
     * checkEmptyQueue - Checks if the queue is empty .
     * 
     * @exception
     * Throws EmptyQueue exception if the queue is empty
    */
    void checkEmptyQueue() const;
};


/* --------------------------------------- Public Functions of Queue Class ---------------------------------------*/

template <class T>
Queue<T>::Queue() : m_data(new T[INITIAL_SIZE]) , m_dataSize(INITIAL_SIZE) , m_currentIndex(FIRST_INDEX) {}

template <class T>
Queue<T>::~Queue(){
    delete[] m_data;
}

template <class T>
Queue<T>::Queue(const Queue& queue) : m_data(new T[queue.m_dataSize]), m_dataSize(queue.m_dataSize)
 , m_currentIndex(queue.m_currentIndex){
    try{
        copyData(m_data,m_dataSize,queue);
    } catch(...){
        delete[] m_data;
        throw;
    }
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue& otherQueue){
    if(this == &otherQueue){
        return *this;
    }

    T* tempData = new T[otherQueue.m_dataSize];
    try{
        copyData(tempData,otherQueue.m_dataSize,otherQueue);
    } catch(...) {
        delete[] tempData;
        throw;
    }
    updateData(tempData);
    m_dataSize = otherQueue.m_dataSize;
    m_currentIndex = otherQueue.m_currentIndex;
    return *this;

}

template <class T>
void Queue<T>::pushBack(const T& argumentToAdd){
    if(m_currentIndex == m_dataSize){
        this->expand();
    }
    m_data[m_currentIndex++]= argumentToAdd;
}

template <class T>
T& Queue<T>::front(){
    checkEmptyQueue();
    return m_data[FIRST_INDEX];
}

template <class T>
const T& Queue<T>::front() const {
    checkEmptyQueue();
    return m_data[FIRST_INDEX];
}

template <class T>
void Queue<T>::popFront() {
    checkEmptyQueue();
    compress();

}

template <class T>
int Queue<T>::size() const{
    return m_currentIndex;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin(){
    return Iterator(this, FIRST_INDEX);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() {
    return Iterator(this,m_currentIndex);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const{
    return ConstIterator(this,FIRST_INDEX);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const{
    return ConstIterator(this,m_currentIndex);
}


/* ------------------------------------ End of Public Functions of Queue Class ------------------------------------*/

/* ------------------------------------ ------------------------------------- ------------------------------------*/

/* --------------------------------------- Private Functions of Queue Class ---------------------------------------*/

template <class T>
void Queue<T>::expand(){

    T* tempData = new T[EXPAND_RATE*m_dataSize];
    try{
        copyData(tempData,EXPAND_RATE*m_dataSize,*this);
    } catch(...){
        delete[] tempData;
        throw;
    }
    updateData(tempData);
    m_dataSize= EXPAND_RATE*m_dataSize;
}

template <class T>
void Queue<T>::compress() {

    T* tempData = new T[m_currentIndex];
    try{
        copyData(tempData,m_currentIndex,*this);
        for (int i=0 ; i < m_currentIndex - 1; i++){
            tempData[i] = tempData[i+1];
        }
    } catch(...) {
        delete[] tempData;
        throw;
    }
    updateData(tempData);
    m_dataSize = m_currentIndex;
    m_currentIndex--;
}

template <class T>
void Queue<T>::copyData(T* const destinationData, int destinationDataSize, const Queue<T>& sourceQueue){

    for(int i = 0 ; i < sourceQueue.m_dataSize && i < destinationDataSize ; i++){
        destinationData[i] = sourceQueue.m_data[i];
    }

}

template <class T>
void Queue<T>::updateData(T* newData) {
    delete[] m_data;
    m_data = newData;
}

template <class T>
void Queue<T>::checkEmptyQueue() const{

    if(m_currentIndex == FIRST_INDEX){
        throw EmptyQueue();
    }
}

/* ------------------------------------ End of Private Functions of Queue Class ------------------------------------*/

/* ------------------------------------ ------------------------------------- ------------------------------------*/

/* --------------------------------------- Additional Functions of Interface ---------------------------------------*/


/*
 * filter - Filters queue accordingly to the condition that is given
 * 
 * @param queue - The queue which will be filtered.
 * @param condition - The condition used to filter the queue.
 * @return
 * Returns filtered queue.
 * @exception
 * std::bad_alloc exception might be thorwn,
 * as well as, a random exception might be thrown.
 * 
*/
template <class T,class Condition>
Queue<T> filter(const Queue<T>& queue,const Condition& condition){
    Queue<T> resultQueue;
    for(const T& data : queue){
        if(condition(data)){
            resultQueue.pushBack(data);
        }
    }
    return resultQueue;
}

/*
 * transform - Transforms the queue accordingly to the transform operation given.
 * 
 * @param queue - The queue which will have a transform.
 * @param transform - The operation that will be used to transform the queue.
 * 
 * 
*/
template <class T, class Transform>
void transform(Queue<T>& queue, const Transform& transform){
    
    for(T& data : queue){
        transform(data);
    }

}

/* ----------------------------------- End of Additional Functions of Interface -----------------------------------*/

/* ------------------------------------ ------------------------------------- ------------------------------------*/

/* ----------------------------------------------- Iterator Class -----------------------------------------------*/

template <class T>
class Queue<T>::Iterator{

public:

    /*
     * Here we are explicitly telling the compiler to use the default methods.
    */
    ~Iterator() = default;
    Iterator& operator=(const Iterator& iterator) = default;
    Iterator(const Iterator& otherIterator) = default;

    /*
     * operator* 
     * 
     * @return
     * Returns the data the Iterator is pointing to
     * @exception
     * Throws InvalidOperation exception if Iterator points to end queue.
    */
    T& operator*() const;


    /*
     * operator!=
     * 
     * @param otherIterator - Other Iterator for comprasion
     * @return
     * Returns true if the Iterators are different , else returns false
    */
    bool operator!=(const Iterator& otherIterator) const;

    /*
     * operator++ - prefix operator ++
     * 
     * @return
     * Returns Iterator by reference that points to the next value in the queue
     * @exception
     * Throws InvalidOperation exception if Iterator points to end queue.
    */
    Iterator& operator++();

    /*
     * operator++ - postfix operator ++
     * 
     * @return
     * Returns Iterator that points to the next value in the queue
     * @exception
     * Throws InvalidOperation exception if Iterator points to end queue.
    */
    Iterator operator++(int);

    
    /*
     * InvalidOperation - Exception for invalid operations on Iterator that points to the end of queue
    */
    class InvalidOperation {};
    
private:

    const Queue<T>* m_queue;
    int m_index;

    /*
     * C'tor for Iterator class.
     *
     * @return
     * A new instance of Iterator.
    */
    Iterator(const Queue<T>* queue, int index);
    friend class Queue;

    /*
     * checkInvalidOperation - checks if invalid operation will be made on end queue.
     * 
     * @exception
     * Throws InvalidOperation exception if invalid operation will be made on end queue.
    */
    void checkInvalidOperation() const;


};

/* ------------------------------------- Public Functions of Iterator Class -------------------------------------*/


template <class T>
T& Queue<T>::Iterator::operator*() const {
    checkInvalidOperation();
    return m_queue->m_data[m_index];
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
    checkInvalidOperation();
    ++m_index;
    return *this;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int){

    checkInvalidOperation();
    Iterator result = *this;
    ++(*this);
    return result;

}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& otherIterator) const {
    assert(this->m_queue == otherIterator.m_queue);
    return m_index != otherIterator.m_index;
}

/* ---------------------------------- End of Public Functions of Iterator Class ----------------------------------*/

/* ------------------------------------ ------------------------------------ ------------------------------------ */

/* ------------------------------------- Private Functions of Iterator Class -------------------------------------*/

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue,int index) : m_queue(queue), m_index(index){}

template <class T>
void Queue<T>::Iterator::checkInvalidOperation() const{
    if(m_queue->size() == m_index){
        throw InvalidOperation();
    }
}

/* ---------------------------------- End of Private Functions of Iterator Class ----------------------------------*/

/* ------------------------------------ ------------------------------------ ------------------------------------ */

/* --------------------------------------------- End of Iterator Class ---------------------------------------------*/

/* ------------------------------------ ------------------------------------- ------------------------------------*/

/* --------------------------------------------- ConstIterator Class ---------------------------------------------*/


template <class T>
class Queue<T>::ConstIterator{

public:

    /*
     * Here we are explicitly telling the compiler to use the default methods.
    */
    ~ConstIterator() = default; 
    ConstIterator(const ConstIterator& otherIterator) = default;
    ConstIterator& operator=(const ConstIterator& Iterator) = default;

    /*
     * operator* 
     * 
     * @return
     * Returns the data the ConstIterator is pointing to
     * @exception
     * Throws InvalidOperation exception if Iterator points to end queue.
    */
    const T& operator*() const;

    /*
     * operator!=
     * 
     * @param otherIterator - Other Iterator for comprasion
     * @return
     * Returns true if the Iterators are different , else returns false
    */
    bool operator!=(const ConstIterator& otherIterator) const;

    /*
     * operator++ - prefix operator ++
     * 
     * @return
     * Returns ConstIterator by reference that points to the next value in the queue
     * @exception
     * Throws InvalidOperation exception if Iterator points to end queue.
    */
    ConstIterator& operator++();

    /*
     * operator++ - postfix operator ++
     * 
     * @return
     * Returns ConstIterator that points to the next value in the queue
     * @exception
     * Throws InvalidOperation exception if Iterator points to end queue.
    */
    ConstIterator operator++(int);

    /**
     * InvalidOperation - Exception for invalid operations on Iterator that points to the end of queue
    */
    class InvalidOperation {};

private:
    const Queue<T>* m_queue;
    int m_index;

    /*
     * C'tor for ConstIterator class.
     *
     * @return
     * A new instance of ConstIterator.
    */
    ConstIterator(const Queue<T>* queue, int index);
    friend class Queue;

     /*
     * checkInvalidOperation - checks if invalid operation will be made on end queue.
     * 
     * @exception
     * Throws InvalidOperation exception if invalid operation will be made on end queue.
    */
    void checkInvalidOperation() const;

};



/* -------------------------------------- Public Functions of Iterator Class --------------------------------------*/

template <class T>
const T& Queue<T>::ConstIterator::operator*() const{

    checkInvalidOperation();
    return m_queue->m_data[m_index];
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& otherIterator) const{
    assert(this->m_queue == otherIterator.m_queue);
    return m_index != otherIterator.m_index;
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++() {

    checkInvalidOperation();
    ++m_index;
    return *this;

}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int){

    checkInvalidOperation();
    ConstIterator result = *this;
    ++(*this);
    return result;

}

/* -------------------------------- End of Public Functions of ConstIterator Class --------------------------------*/

/* ------------------------------------ ------------------------------------ ------------------------------------ */

/* ----------------------------------- Private Functions of ConstIterator Class -----------------------------------*/


template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index) : m_queue(queue) , m_index(index) {}

template <class T>
void Queue<T>::ConstIterator::checkInvalidOperation() const{
    if(m_queue->size() == m_index){
        throw InvalidOperation();
    }
}

/* -------------------------------- End of Private Functions of ConstIterator Class --------------------------------*/

/* ------------------------------------ ------------------------------------ ------------------------------------ */

/* ------------------------------------------- End of ConstIterator Class -------------------------------------------*/

#endif //Queue_H