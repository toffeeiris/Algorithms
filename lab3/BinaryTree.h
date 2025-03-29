template <typename B>

struct BT_node
{
	B value;
	BT_node* parent;
	BT_node* l_child;
	BT_node* r_child;

	BT_node(B my_value)
	{
		value = my_value;
		parent = nullptr;
		l_child = r_child = nullptr;
	}

	BT_node(B my_value, BT_node* my_parent)
	{
		value = my_value;
		parent = my_parent;
		l_child = r_child = nullptr;
	}
};

template <typename B>

class BinaryTree
{
	BT_node<B>* root;
	

public:
	BinaryTree() : root(nullptr) {}
	BinaryTree(B);
	
	BT_node<B>* get_root();
	BT_node<B>* get_parent(BT_node<B>*);
	BT_node<B>* l_child_add(BT_node<B>*, B);
	BT_node<B>* r_child_add(BT_node<B>*, B);
	bool has_l_child(BT_node<B>*);
	bool has_r_child(BT_node<B>*);
	BT_node<B>* get_l_child(BT_node<B>*);
	BT_node<B>* get_r_child(BT_node<B>*);
	//traverse
	void pre_order(BT_node<B>*);
	void in_order(BT_node<B>*);
	void post_order(BT_node<B>*);
};

template <typename B>
BinaryTree<B>::BinaryTree(B my_value)
{
	root = new BT_node<B>(my_value);
}

template <typename B>
BT_node<B>* BinaryTree<B>::get_root()
{
	return root;
}

template <typename B>
BT_node<B>* BinaryTree<B>::get_parent(BT_node<B>* curr)
{
	return curr->parent;
}

template <typename B>
BT_node<B>* BinaryTree<B>::get_l_child(BT_node<B>* curr)
{
	return curr->l_child;
}

template <typename B>
BT_node<B>* BinaryTree<B>::get_r_child(BT_node<B>* curr)
{
	return curr->r_child;
}

template <typename B>
BT_node<B>* BinaryTree<B>::l_child_add(BT_node<B>* curr_parent, B my_value)
{
	BT_node<B>* new_child = new BT_node<B>(my_value, curr_parent);
	curr_parent->l_child = new_child;
	return new_child;
}

template <typename B>
BT_node<B>* BinaryTree<B>::r_child_add(BT_node<B>* curr_parent, B my_value)
{
	BT_node<B>* new_child = new BT_node<B>(my_value, curr_parent);
	curr_parent->r_child = new_child;
	return new_child;
}

template <typename B>
bool BinaryTree<B>::has_l_child(BT_node<B>* curr)
{
	return (curr->l_child != nullptr);
}

template <typename B>
bool BinaryTree<B>::has_r_child(BT_node<B>* curr)
{
	return (curr->r_child != nullptr);
}

template <typename B>
void BinaryTree<B>::pre_order(BT_node<B>* curr)
{
	if (curr == nullptr)
		return;

	std::cout << curr->value << " ";
	pre_order(curr->l_child);
	pre_order(curr->r_child);
}

template <typename B>
void BinaryTree<B>::in_order(BT_node<B>* curr)
{
	if (curr == nullptr)
		return;

	in_order(curr->l_child);
	std::cout << curr->value << " ";
	in_order(curr->r_child);
}

template <typename B>
void BinaryTree<B>::post_order(BT_node<B>* curr)
{
	if (curr == nullptr)
		return;

	post_order(curr->l_child);
	post_order(curr->r_child);
	std::cout << curr->value << " ";
}