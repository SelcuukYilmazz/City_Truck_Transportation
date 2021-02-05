/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);

*/
#pragma once

template <typename T> class Stack {
	public:
	Stack();
	~Stack();
	bool isEmpty() const;
	int size() const;

	//Push: Place item on top of the stack
	void push(const T& newItem);
	//Top: Take a look at the topmost item without removing it
	void getTop(T& stackTop) const;
	//Pop: Remove item from the top of the stack
	void pop();
	private:
	struct ListNode {
		T item;
		ListNode* next;
		ListNode* prev;
		};
	ListNode* _head;
	int _size;
};



template<typename T> Stack<T>::Stack()
{
    _head = new ListNode;
    _size = 0;
}

template<typename T> Stack<T>::~Stack()
{
}

//Place item on top of stack and set next and prev values

template<typename T> void Stack<T>::push(const T & newItem)
{
    ListNode* temp = _head;
    for (int i = 0; i < _size ; i++)
    {
        temp->next->prev = temp;
        temp = temp->next;
    }
    _size++;
    temp->item=newItem;
    temp->next= new ListNode;

}

//If size is 0 then this returns true

template<typename T> bool Stack<T>::isEmpty() const
{
    if (_size == 0)
    {
        return true;
    }
    return false;
}

//Returns us size of stack

template<typename T> int Stack<T>::size() const
{
    return _size;
}

//Delete top item of stack

template<typename T> void Stack<T>::pop()
{
    ListNode* temp = _head;
    if(_size!=0)
    {

        for (int i = 0; i < _size - 1; i++)
        {
            temp = temp->next;
        }
        if (temp == _head)
        {
            temp->prev = new ListNode;
            temp->prev->next = temp;
            temp = temp->prev;
            delete temp->next;

            _head =temp;
        }
        else{
            temp = temp->prev;
            delete temp->next;
            temp->next = new ListNode;
        }
        _size--;
    }
    else{
        std::cout<<"StackException"<<std::endl;
    }

}

//Returns us top of stack and doesn't delete it

template<typename T> void Stack<T>::getTop(T &stackTop) const
{
    ListNode* temp = _head;
    if(_size!=0)
    {

        for (int i = 0; i < _size - 1; i++)
        {
            temp = temp->next;
        }
        stackTop = temp->item;
    }
    else{
        std::cout<<"StackException"<<std::endl;
    }
}
