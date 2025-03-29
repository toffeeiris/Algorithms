template <typename D>

class DynamicArray
{
private:
	D* data;
	int capacity, size;

	bool check(int index)
	{
		if (index < 0 || index > size)
		{
			std::cout << "Нет такого индекса!";
			return false;
		}
		else if (index == size)
		{
			ensureCapacity(index);
		}
		return true;
	}

public:

	DynamicArray()
	{
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	DynamicArray(int size)
	{
		capacity = size;
		size = 0;
		data = new D[capacity];
	}

	~DynamicArray()
	{
		delete[] data;
	}

	DynamicArray(const DynamicArray& other) : capacity(other.capacity), size(other.size)
	{
		data = new D[capacity];
		for (int i = 0; i < size; ++i)
		{
			data[i] = other.data[i];
		}
	}

	DynamicArray& operator=(const DynamicArray& other)
	{
		if (this != &other)
		{
			delete[] data;
			capacity = other.capacity;
			size = other.size;
			data = new D[capacity];
			for (int i = 0; i < size; ++i)
			{
				data[i] = other.data[i];
			}
		}
		return *this;
	}


	D& operator[](int index)
	{
		if (check(index))
		{
			return data[index];
			if (index == size) size++;
		}
	}

	void ensureCapacity(int index)
	{
		if (index >= capacity)
		{
			int new_capacity = (capacity == 0) ? 1 : (capacity * 2);
			D* new_data = new D[new_capacity];
			for (int i = 0; i < size; i++)
				new_data[i] = data[i];

			if (data != nullptr)
				delete[] data;

			data = new_data;
			capacity = new_capacity;
		}
	}

	void insert(int index, D value)
	{
		if (check(index))
		{
			for (int i = size; i > index; i--)
			{
				data[i] = data[i - 1];
			}
			data[index] = value;
			size++;
		}
	}

	void remove(int index)
	{
		if (check(index))
		{
			for (int i = index; i < size - 1; i++)
			{
				data[i] = data[i + 1];
			}
			size--;
		}
	}

	void push_back(const D& value)
	{
		ensureCapacity(size + 1);
		data[size++] = value;
	}

	int get_size()
	{
		return size;
	}

	void change_item(int index, D value)
	{
		if (index < 0 || index >= size)
			std::cout << "Нет такого индекса!";
		else
			data[index] = value;
	}
};


