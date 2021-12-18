#ifndef TREE_H
#define TREE_H
#include "Stack.h"
#include <QList>
//---------------------node class
template<typename T>
class Node
{
    T value ;
    Node * parent ;
    Node * left ;
    Node * right ;
public:
    Node (T value , Node * p = nullptr , Node * l = nullptr , Node * r = nullptr )
    {
        this->value = value ;
        this->parent = p ;
        this->left = l ;
        this->right = r ;
    }
    inline Node * getParent() const
    {
        return parent;
    }
    inline void setParent(Node *newParent)
    {
        parent = newParent;
    }
    inline const T &getValue() const
    {
        return value;
    }
    inline void setValue(const T &newValue)
    {
        value = newValue;
    }
    inline Node *getRight() const
    {
        return right;
    }
    inline void setRight(Node *newRight)
    {
        right = newRight;
    }
    inline Node *getLeft() const
    {
        return left;
    }
    inline void setLeft(Node *newLeft)
    {
        left = newLeft;
    }
};
//-----------------------end of node class
//--------------------tree class
template<typename T>
class Binary_Tree
{
    int size ;
    Node<T> * root ;
public:
    Binary_Tree ()
    {
        this->size = 0 ;
        this->root = nullptr ;
    }
    bool isempty ()
    {
        return size== 0 ;
    }
    Node<T> * createnode (T v , Node<T> * p = nullptr , Node<T> * l = nullptr , Node<T> * r = nullptr) const
    {
        Node<T> * tmp = new Node<T> (v , p , l , r) ;
        if (l != nullptr)
            l->setParent(tmp) ;
        if (r != nullptr)
            r->setParent(tmp) ;
        return tmp;
    }
    void add_root (T v)
    {
        if (!isempty())
        {
            throw "tree is not empty !!!" ;
            return;
        }
        this->root = createnode(v) ;
        size++ ;
    }
    int getsize ()const
    {
        return size;
    }
    Node<T> * getroot () const
    {
        return this->root;
    }
    bool isroot (Node<T> * r)
    {
        return this->root == r ;
    }
    bool isexternal (Node<T> * leaf)
    {
        return numchildren(leaf) == 0 ;
    }
    bool isinternal (Node<T> * p)
    {
        return numchildren(p) > 0 ;
    }
    int numchildren (Node<T> * p)
    {
        int count = 0 ;
        if (p->getLeft() != nullptr )
            count++;
        if (p->getRight() != nullptr )
            count++;
        return count;
    }
    Node<T> * parent (Node<T> * p)
    {
        return p->getParent();
    }
    Node<T> * left (Node<T> * p)
    {
        return p->getLeft();
    }
    Node<T> * right (Node<T> * p)
    {
        return p->getRight();
    }
    Node<T> * sibiling (Node<T> * p)
    {
        Node<T> * tmp = p->getParent() ;
        if (tmp == nullptr)
            return nullptr;
        return tmp->getLeft()==p ? tmp->getRight() : p ;
    }
    QList<Node<T> *> children (Node<T> * p)
    {
        QList<Node<T> *> tmp ;
        if (p->getLeft()!= nullptr)
            tmp.push_back(p->getLeft()) ;
        if (p->getRight() != nullptr)
            tmp.push_back(p->getRight()) ;
        return tmp ;
    }
    void add_left (Node<T> * p , T v)
    {
        if (p->getLeft() != nullptr)
        {
            throw "node already has left child" ;
            return;
        }
        p->setLeft(createnode(v , p )) ;
        size ++ ;
    }
    void add_right (Node<T> * p , T v)
    {
        if (p->getRight() != nullptr)
        {
            throw "node already has right child" ;
            return;
        }
        p->setRight(createnode(v , p )) ;
        size ++ ;
    }
    void set (Node<T> * p , T v)
    {
        p->setValue(v) ;
    }
    void attach (Node<T> * p , Binary_Tree t1 , Binary_Tree t2)
    {
        if (isinternal(p))
        {
            throw "node must be leaf" ;
            return;
        }
        this->size += t1.size + t2.size ;
        if (!t1.isempty())
        {
            t1.root.setparent (p) ;
            p->setLeft(t1.root) ;
            t1.~Binary_Tree<T>() ;
        }
        if (!t2.isempty())
        {
            t2.root.setparent (p) ;
            p->setRight(t2.root) ;
            t2.~Binary_Tree<T>() ;
        }
    }
    void remove (Node<T> * p)
    {
        if (numchildren(p) == 2)
        {
            throw " node has 2 child cant remove node" ;
            return;
        }
        Node<T> * child = p->getLeft()==nullptr ? p->getRight() : p->getLeft() ;
        Node<T> * parent = p->getParent() ;
        if (child != nullptr)
            child->setParent(parent) ;
        if (root == p)
            root = child ;
        else
        {
            if (p == parent->getLeft())
                parent->setLeft(child) ;
            else
                parent->setRight(child) ;
        }
        size -- ;
        delete p ;
        p = nullptr ;
    }
    ~Binary_Tree()
    {

    }
    void set_root (Node<T> * p)
    {
        if (!isempty())
        {
            throw "tree has root " ;
            return;
        }
        this->root = p ;
    }
    int max (int a , int b)
    {
        if (a>b)
            return a;
        else
            return b;
    }
    bool isopr (QString input)
    {
        if (input == "+")
            return true;
        if (input == "-")
            return true;
        if (input == "/")
            return true;
        if (input == "*")
            return true;
        if (input == "^")
            return true;
        return false;
    }
    void fillfrompostfix(QList<QString> postfix)
    {
        Stack<Node<QString> * > stk ;
        for (int i=0 ; i<postfix.size() ;i++)
             if (isopr(postfix.at(i)))
             {
                 Node<QString> * a = stk.pop() ;
                 Node<QString> * b = stk.pop() ;
                 stk.push(this->createnode(postfix.at(i) , nullptr , b , a)) ;
             }
            else
             {
                 stk.push( this->createnode(postfix.at(i))) ;
             }
        this->set_root(stk.pop()) ;
        this->size = postfix.size() ;
    }/*
    QString print2DUtil(Node<T> *root, int space)
    {
        QString output ;
        // Base case
        if (root == nullptr)
            return NULL;

        // Increase distance between levels
        space += 10;

        // Process right child first
        print2DUtil(root->getRight(), space);

        // Print current node after space
        // count
        //cout<<endl;
        output += "\n" ;
        for (int i = 10; i < space; i++)
            output += " " ;
        output += root->getValue() + "\n" ;

        // Process left child
        print2DUtil(root->getLeft(), space);
        return output;
    }

    // Wrapper over print2DUtil()
    QString print2D()
    {
        // Pass initial space count as 0
        return  print2DUtil(this->root, 0);
    }*/
    int height (Node<T> * p )
    {
        int h = 0 ;
        for (Node<T> * t : children(p))
            h = max (h , 1 + height(t)) ;
        return h;
    }
};
#endif // TREE_H
