//
// Created by yiner on 12/11/2017.
//

#ifndef DS_ALGORITHM_PRACTICE_QUEUE_H
#define DS_ALGORITHM_PRACTICE_QUEUE_H

#include <cassert>

//Linked Queue
//长度不固定，不存在满不满的问题
template<class Type>
class QueueNode;

template<class Type>
class Queue {
private:
    QueueNode<Type> *rear, *front;
public:
    Queue() : rear(nullptr), front(nullptr) {};

    ~Queue();

    void EnQueue(const Type &item);

    Type DeQueue();

    Type GetFront();

    void MakeEmpty();  //same as function ~Queue()
    int IsEmpty() const { return front == nullptr; }

};

template<class Type>
class QueueNode {
    friend class Queue<Type>;

private:
    Type data;  //Data element
    QueueNode<Type> *link;  //pointer to next item
    QueueNode(Type d = 0, QueueNode *l = nullptr) : data(d), link(l) {}
};


//(2)Linked Queue
//Destructor
template<class Type>
Queue<Type>::~Queue() {
    QueueNode<Type> *p;
    //Release every node step by step
    while (front != nullptr) {
        p = front;
        front = front->link;
        delete p;
    }
}

template<class Type>
void Queue<Type>::EnQueue(const Type &item) {
    //append a new item into Queue
    if (front == nullptr) front = rear = new QueueNode<Type>(item, nullptr);
        //!!注意：此处的操作是先把新结点赋给rear->link，（此时rear还指向加入前的最后一个结点），即让加入前的最后一个结点的link指向新结点
        //然后再更新rear，让rear指向新结点。注意赋值号运算顺序是从右到左，先后顺序很重要!!
    else rear = rear->link = new QueueNode<Type>(item, nullptr);
}

template<class Type>
Type Queue<Type>::DeQueue() {
    //Return the front item(data) and then remove it from Queue
    assert(!IsEmpty());
    QueueNode<Type> *p = front;
    Type retvalue = p->data;
    front = front->link;
    delete p;
    return retvalue;
}

//Return the front item(data)
template<class Type>
Type Queue<Type>::GetFront() {
    assert(!IsEmpty());
    return front->data;
}

template<class Type>
void Queue<Type>::MakeEmpty() {
    QueueNode<Type> *p;
    //Release every node step by step
    while (front != nullptr) {
        p = front;
        front = front->link;
        delete p;
    }
}


#endif //DS_ALGORITHM_PRACTICE_QUEUE_H