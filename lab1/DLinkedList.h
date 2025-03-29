template <typename T>
struct Node 
{
	T data;
	Node* prev;
	Node* next;

	Node(T data)
	{
		this->data = data;
		this->prev = this->next = nullptr; 
	}
};

template <typename T>
class DLinkedList
{ 
private:
	Node<T>* head;
	Node<T>* tail;
	int size = 0;

public:
	DLinkedList() 
	{ 
		head = nullptr; 
		tail = nullptr;
	}

	Node<T>* push_front(T data)
	{
		Node<T>* ptr = new Node<T>(data);
		ptr->next = head;
		if (head != nullptr) 
		{ 
			head->prev = ptr; 
		}
		else
		{
			tail = ptr; 
		}
		head = ptr; 
		size++;
		return ptr;
	}

	Node<T>* push_back(T data) 
	{
		Node<T>* ptr = new Node<T>(data);
		ptr->prev = tail;
		if (tail != nullptr)
		{ 
			tail->next = ptr; 
		}
		else
		{
			head = ptr; 
		}
		tail = ptr; 
		size++;
		return ptr;
	}

	void pop_front()
	{
		if (head == nullptr) 
			return;

		Node<T>* ptr = head->next;
		if (ptr != nullptr) 
		{
			ptr->prev = nullptr; 
		}
		else 
		{
			tail = nullptr; 
		}
		delete head;
		size--;
		head = ptr; 
	}

	void pop_back() 
	{
		if (tail == nullptr) 
			return;

		Node<T>* ptr = tail->prev;
		if (ptr != nullptr)
		{
			ptr->next = nullptr; 
		}
		else
		{
			head = nullptr; 
		}
		delete tail;
		size--;
		tail = ptr; 
	}

	Node<T>* get_item(int index) 
	{ 
		Node<T>* ptr = head;
		int n = 0;

		while (n != index)
		{
			if (ptr == nullptr)
				return nullptr; 

			ptr = ptr->next;
			n++;
		}
		return ptr;
	}

	T operator[](int index) 
	{
		Node<T>* ptr = get_item(index);

		if (ptr)
		{
			return ptr->data;
		}
	}

	Node<T>* insert(int index, T data) 
	{
		Node<T>* right = get_item(index);
		if (right == nullptr)
			return push_back(data);

		Node<T>* left = right->prev;
		if (left == nullptr)
			return push_front(data);

		Node<T>* ptr = new Node<T>(data);

		ptr->prev = left;
		ptr->next = right;

		left->next = ptr;
		right->prev = ptr;

		size++;

		return ptr;
	}

	void remove(int index)
	{
		Node<T>* ptr = get_item(index);
		if (ptr == nullptr)
			return;

		if (ptr->prev == nullptr)
		{
			pop_front();
			return;
		}

		if (ptr->next == nullptr) 
		{
			pop_back();
			return;
		}

		Node<T>* left = ptr->prev;
		Node<T>* right = ptr->next;

		left->next = right;
		right->prev = left;

		size--;

		delete ptr;
	}


	int get_size()
	{
		return size;
	}

	~DLinkedList()
	{
		while (head != nullptr) 
		{
			pop_front();
		}
	}
};