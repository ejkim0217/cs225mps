// Iterator code, initially from C++ reference:
// http://www.cplusplus.com/reference/std/iterator/iterator/
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
    ListNode* p;

  public:
    ListIterator() : p(NULL) { }
    ListIterator(ListNode* x) : p(x) { }

    // Pre-Increment
    ListIterator& operator++()
    {
        // @TODO: graded in MP3.1
        p = p->next;
        return *this;
    }

    // Post-Increment
    ListIterator operator++(int)
    {
        ListNode* r = p;
        p = p->next;
        return ListIterator(r);
    }

    // Pre-Decrement
    ListIterator& operator--()
    {
        p = p->prev;
        return *this;
    }

    // Post-Decrement
    ListIterator operator--(int)
    {
        // @TODO: graded in MP3.1
        ListNode *r = p;
        p = p->prev;
        return ListIterator(r);
    }

    bool operator==(const ListIterator& rhs)
    {
        return p == rhs.p;
    }
    bool operator!=(const ListIterator& rhs)
    {
        // @TODO: graded in MP3.1
        return p != rhs.p;
    }

    const T& operator*()
    {
        return p->data;
    }
    const T* operator->()
    {
        return &(p->data);
    }
};
class RevIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
    ListNode* p;

  public:
    RevIterator() : p(NULL) { }
    RevIterator(ListNode* x) : p(x) { }
    RevIterator& operator++()
    {
        p = p->prev;
        return *this;
    } // Pre-Increment
    RevIterator operator++(int)
    {
        ListNode* r = p;
        p = p->prev;
        return RevIterator(r);
    } // Post-Increment

    RevIterator& operator--()
    {
        p = p->next;
        return *this;
    } // Pre-Decrement
    RevIterator operator--(int)
    {
        ListNode* r = p;
        p = p->next;
        return RevIterator(r);
    } // Post-Decrement

    bool operator==(const RevIterator& rhs)
    {
        return p == rhs.p;
    }
    bool operator!=(const RevIterator& rhs)
    {
        return p != rhs.p;
    }

    const T& operator*()
    {
        return p->data;
    }
    const T* operator->()
    {
        return &(p->data);
    }
};
typedef ListIterator iterator;
typedef ListIterator const_iterator;
typedef RevIterator reverse_iterator;
typedef RevIterator const_reverse_iterator;

const_iterator         begin()  const { return ListIterator(head_); }
const_iterator         end()    const { return ListIterator(NULL); }
const_reverse_iterator rbegin() const { return RevIterator(tail_); }
const_reverse_iterator rend()   const { return RevIterator(NULL); }

// Iterator constructor
template <class Iter>
List(const Iter& start, const Iter& end);
