#ifndef STACK_H
#define STACK_H
#include <iostream>
template <typename Q>
class node
{
public:
    Q value ;
    node * next ;
    node (Q v , node * n)
    {
        this->value = v ;
        this->next = n ;
    }
};
//--------------------------------------
template<typename  T>
class linked_list
{

    node<T> *head ;
    node<T> *tail ;
    int size ;
public:
    linked_list()
    {
        this->head = nullptr ;
        this->tail = nullptr ;
        this->size = 0 ;
    }
    void add_between (node<T> * prev , T v , node<T> *next)
    {
        node<T> * tt = new node<T> (v , next) ;
        prev->next = tt ;
        size ++ ;
    }
    void add_first (T v )
    {
        node<T> * tmp  = new  node<T> (v , this->head) ;
        if ( this->head == nullptr )
        {
            this->head = tmp ;
            this->tail = tmp ;
            this->size ++ ;
            return;
        }
        this->head = tmp ;
        this->size ++ ;
    }
    void add_last (T v )
    {
        if ( this->tail == nullptr )
        {
            this->add_first(v) ;
            return;
        }
        node<T> * tmp = new  node<T> (v , nullptr ) ;
        this->tail->next = tmp ;
        this->tail = tmp ;
        this->size ++ ;
    }
    int getsize ()
    {
        return this->size;
    }
    bool isempty ()
    {
        return (size==0);
    }
    T first_eleman ()
    {
        if (head == nullptr)
            return 0 ;
        return head->value ;
    }
    T last_eleman ()
    {
        if (head == nullptr)
            return NULL;
        return tail->value ;
    }
    T remove_first ()
    {
        if ( this->head == nullptr )
            return  0 ;
        T a = head->value ;
        node<T> * tmp = this->head ;
        this->head = this->head->next ;
        this->size -- ;
        delete  tmp ;
        tmp = nullptr ;
        if ( size == 0 )
        {
            this->tail = nullptr ;
            return a ;
        }
        return  a ;
    }
    T remove_last ()
    {
        if (this->tail == nullptr )
            return NULL ;
        T a = tail->value ;
        node<T> * tmp = this->tail ;
        this->size -- ;
        delete tmp ;
        tmp = head ;
        for (int i=0 ; i<this->size  ; i++)
            tmp = tmp->next ;
        this->tail = tmp ;
        if ( size == 0  )
        {
            this->tail == nullptr ;
            this->head = nullptr ;
            return a ;
        }
        this->tail->next = nullptr ;
        return a ;
    }
    T remove (node<T> * tmp )
    {
        if (isempty())
            return NULL;
        if (this->size == 1)
        {
            T data = tmp->value ;
            delete tmp ;
            head =nullptr ;
            tail = nullptr ;
            size -- ;
            return data ;
        }
        if (head == tmp)
        {
            head = tmp->next ;
            size -- ;
            T data = tmp->value ;
            delete  tmp ;
            return data;
        }
        node<T> *tt = head ;
        while (tt)
        {
            if (tt->next == tmp)
            {
                tt->next = tmp->next ;
                size-- ;
                T data = tmp->value ;
                delete tmp ;
                return data ;
            }
            tt = tt->next ;
        }
        return NULL ;
    }
    node<T> *getHead() const
    {
        return head;
    }
    void setHead(node<T> *newHead)
    {
        head = newHead ;
    }
    node<T> *getTail() const
    {
        return tail;
    }
    void setTail(node<T> *newTail)
    {
        tail = newTail ;
    }
    T at (int i)
    {
        if (i >= this->size && i < 0)
            return NULL;
        node<T> * tmp ;
        tmp = this->head ;
        for (int j=0 ; j<i ; j++)
            tmp = tmp->next ;
        return tmp->value;
    }
    int indexOf(T data)
    {
        node<T> * tmp = this->head ;
        for ( int i=0 ; i< this->size; i++ , tmp = tmp->next)
        {
            if (tmp->value == data )
                return i;
        }
        return -1;
    }
    ~linked_list()
    {
        if ( this->head != nullptr && this->tail != nullptr )
        {
            while ( this->head )
            {
                node<T> * tp = this->head ;
                this->head = tp->next ;
                delete  tp ;
                tp = nullptr ;
            }
            this->size = 0 ;
            this->head = nullptr ;
            this->head = nullptr ;
        }
    }
};
//----------------------------------------
template<typename  T>
class Stack : private linked_list<T>
{
public:
    Stack ()
    {

    }
    int getsize ()
    {
        return this->getsize();
    }
    bool isemptys ()
    {
        return this->isempty();
    }
    void push (T eleman)
    {
        this->add_first(eleman) ;
    }
    T top ()
    {
        return this->first_eleman();
    }
    T pop ()
    {
        return this->remove_first();
    }
    void operator = (  Stack<T> & a)
    {
        node<T> * tmp = a.getHead() ;
        while (tmp != nullptr )
        {
            this->push(tmp->value) ;
            tmp = tmp->next ;
        }
    }
};
#endif // STACK_H
