/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/
#pragma once

template<typename T> class Queue {
	public:
	Queue();
	~Queue();
	bool isEmpty() const;
	int size() const;
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T& newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T& queueTop) const;
	private:
	struct QueueNode {
		T item;
		QueueNode *next;
        QueueNode *prev;
		};
	int _size;
	/* to avoid the traversal to the last node,
	 an additional pointer to the last node is defined*/
	QueueNode* _lastNode;
    QueueNode* _head;
};


template<typename T> Queue<T>::Queue()
{
    _head = new QueueNode;
    _lastNode = _head;
    _size = 0;

}

template<typename T> Queue<T>::~Queue<T>(){}

//We can see is queue empty or not with this function. If size is 0 then it is empty

template<typename T> bool Queue<T>::isEmpty() const
{
    if (_size == 0)
    {
        return true;
    }
    return false;
}

//This function gives us size of queue

template<typename T> int Queue<T>::size() const
{
    return _size;
}


//This function adds element to queue's head. And set next prev and item values

template<typename T> void Queue<T>::enqueue(const T &newItem)
{
    QueueNode* temp = new QueueNode;
    _size++;
    temp->item=newItem;
    temp->next= _head;
    _head->prev = temp;
    _head = temp;
}

//This function simply deletes last item

template<typename T> void Queue<T>::dequeue()
{
    QueueNode* temp = _head;
    if(_size!=0)
    {
        for (int i = 0; i < _size - 1; i++)
        {
            temp = temp->next;
        }
        if (temp == _head)
        {
            temp->prev = new QueueNode;
            temp->prev->next = temp;
            temp = temp->prev;
            delete temp->next;

            _head =temp;
        }
        else{

            delete _lastNode;
            _lastNode=temp;
        }
        _size--;
    }
    else{
        std::cout<<"QueueException"<<std::endl;
    }
}

//This function gives us top of queue and doesn't delete it

template<typename T> void Queue<T>::getFront(T &queueTop) const
{
    QueueNode* temp = _head;
    if(_size!=0)
    {

        for (int i = 0; i < _size - 1; i++)
        {
            temp = temp->next;
        }
        queueTop = temp->item;
    }
    else{
        std::cout<<"QueueException"<<std::endl;
    }
}
