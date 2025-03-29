template <typename S>
struct s_Node
{
	S data;
	s_Node* next;

	s_Node(s_Node* my_next, S my_data)
	{
		next = my_next;
		data = my_data;
	}
};

template <typename S>
class Stack
{
private:
	s_Node<S>* head;

public:
	Stack()
	{
		head = nullptr;
	}

	~Stack()
	{
		while (!empty())
		{
			pop();
		}
	}

	void push(S data)
	{
		s_Node<S>* ptr = new s_Node<S>(head, data);
		head = ptr;
	}

	void pop()
	{
		if (empty())
		{
			return;
		}

		s_Node<S>* ptr = head;
		head = head->next;
		delete ptr;
	}

	S top()
	{
		if (empty())
		{
			return 0;
		}

		return head->data;
	}

	bool empty()
	{
		if (head == nullptr)
			return true;
		else
			return false;
	}

	void show()
	{
		if (empty())
		{
			std::cout << "(cтек пуст)" << std::endl;
		}

		s_Node<S>* ptr = head;
		while (ptr != nullptr)
		{
			std::cout << ptr->data << " ";
			ptr = ptr->next;
		}
	}
};