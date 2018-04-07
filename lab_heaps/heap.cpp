
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx +1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
      return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    size_t v_size = _elems.size();
    return ((v_size -1) >= 2*currentIdx && v_size > 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t left = 2 * currentIdx;
    size_t right = 2 * currentIdx +1;

    if(_elems.size()-1 < 2 * currentIdx +1)
      return left;
    if(higherPriority(_elems[left], _elems[right]))
      return left;
    else
      return right;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    size_t child = maxPriorityChild(currentIdx);
    if(child > _elems.size() -1)
      return;

    if (higherPriority(_elems[child], _elems[currentIdx]))
    {
      std::swap(_elems[child], _elems[currentIdx]);
      heapifyDown(child);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    // typename std::vector<T>::iterator it;
    // it = _elems.begin();
    // it = _elems.insert(it, -1);
    _elems.push_back(T());
    for(unsigned i = 0; i < elems.size(); i++){
      _elems.push_back(elems[i]);
    }
    for(unsigned i = parent(_elems.size()-1); i > 0; i--){
      heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T value = _elems[1];
    // Set to the size of the last element
    size_t last = _elems.size() -1;
    _elems[1] = _elems[last];
    // Delete last element
    _elems.erase(_elems.begin()+last);
    //Reconstruct tree
    heapifyDown(1);
    return value;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    size_t addition = _elems.size()-1;
    heapifyUp(addition);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() <= 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
