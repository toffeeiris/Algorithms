#include <stack>
#include <queue>
using std::cout;
using std::endl;
using std::max;

template <typename A>
struct AVL_node
{
	A value = 0;
	AVL_node<A>* parent = nullptr;
	AVL_node<A>* l_child = nullptr;
	AVL_node<A>* r_child = nullptr;
	int height = 0;
	int dublicate;

	AVL_node()
	{
		value = 0;
		parent = nullptr;
		l_child = r_child = nullptr;
		height = 0;
		dublicate = 0;
	}

	AVL_node(AVL_node<A>* my_parent, A my_value)
	{
		value = my_value;
		parent = my_parent;
		height = 1;
		dublicate = 0;
	}
};

template <typename A>
class AVLTree
{
	AVL_node<A>* root;
	

	int get_height(AVL_node<A>*);
	void update_height(AVL_node<A>*);
	int balance_factor(AVL_node<A>*);
	AVL_node<A>* unbalanced_node(AVL_node<A>*);
	AVL_node<A>* l_child_add(AVL_node<A>*, A);
	AVL_node<A>* r_child_add(AVL_node<A>*, A);
	bool has_l_child(AVL_node<A>*);
	bool has_r_child(AVL_node<A>*);

	void LL_rotation(AVL_node<A>*);
	void RR_rotation(AVL_node<A>*);
	void LR_rotation(AVL_node<A>*);
	void RL_rotation(AVL_node<A>*);

	AVL_node<A>* find_min(AVL_node<A>*);

public:

	AVLTree() : root(nullptr) {};
	AVLTree(A);

	AVL_node<A>* get_root();
	void get_info(AVL_node<A>*);
	void insert(A);
	void remove(A);
	

	void breadth_search(AVL_node<A>*);
	//depth traverse
	void pre_order_search(AVL_node<A>*);
	void in_order_search(AVL_node<A>*);
	void post_order_search(AVL_node<A>*);
	AVL_node<A>* search(AVL_node<A>*, A);
};

template <typename A>
AVLTree<A>::AVLTree(A my_value)
{
	root = new AVL_node<A>(nullptr, my_value);
}

template <typename A>
AVL_node<A>* AVLTree<A>::get_root()
{
	return root;
}

template <typename A>
AVL_node<A>* AVLTree<A>::l_child_add(AVL_node<A>* curr, A my_value)
{
	AVL_node<A>* new_child = new AVL_node<A>(curr, my_value);
	curr->l_child = new_child;
	return new_child;
}

template <typename A>
AVL_node<A>* AVLTree<A>::r_child_add(AVL_node<A>* curr, A my_value)
{
	AVL_node<A>* new_child = new AVL_node<A>(curr, my_value);
	curr->r_child = new_child;
	return new_child;
}

template <typename A>
bool AVLTree<A>::has_l_child(AVL_node<A>* curr)
{
	return (curr->l_child != nullptr);
}

template <typename A>
bool AVLTree<A>::has_r_child(AVL_node<A>* curr)
{
	return (curr->r_child != nullptr);
}

template <typename A>
void AVLTree<A>::get_info(AVL_node<A>* curr)
{
	if (curr->parent != nullptr)
		cout << "Родитель: " << curr->parent->value << endl;
	else
		cout << "Это корень дерева" << endl;
	//-------------------------------------
	if (curr->l_child != nullptr)
		cout << "Левый сын: " << curr->l_child->value << endl;
	else
		cout << "Левого сына нет" << endl;
	//-------------------------------------
	if (curr->r_child != nullptr)
		cout << "Правый сын: " << curr->r_child->value << endl;
	else
		cout << "Правого сына нет" << endl;
	cout << "Баланс узла: " << balance_factor(curr) << endl;
	cout << "Количество дубликатов: " << curr->dublicate << endl;
}

template <typename A>
int AVLTree<A>::get_height(AVL_node<A>* curr)
{
	if (curr == nullptr)
		return 0;
	else
		return curr->height;
}

template <typename A>
void AVLTree<A>::update_height(AVL_node<A>* curr)
{
	AVL_node<A>* node = curr;
	while (node != nullptr)
	{
		int l = get_height(node->l_child);
		int r = get_height(node->r_child);
		node->height = max(l, r) + 1;
		node = node->parent;
	}
}

template <typename A>
int AVLTree<A>::balance_factor(AVL_node<A>* curr)
{
	if (curr == nullptr)
		return 0;
	else
	{
		int l = get_height(curr->l_child);
		int r = get_height(curr->r_child);
		return (l - r);
	}
}

template <typename A>
AVL_node<A>* AVLTree<A>::unbalanced_node(AVL_node<A>* node)
{
	if (node == nullptr) 
		return nullptr; 

	AVL_node<A>* l = unbalanced_node(node->l_child);
	if (l != nullptr) return l;

	AVL_node<A>* r = unbalanced_node(node->r_child);
	if (r != nullptr) return r;

	int balance = balance_factor(node);
	if (abs(balance) > 1)
		return node;

	return nullptr;
}


template <typename A>
void AVLTree<A>::LL_rotation(AVL_node<A>* grand_p) 
{
	AVL_node<A>* temp = grand_p->r_child;
	AVL_node<A>* g_temp = grand_p->parent;

	grand_p->r_child = temp->l_child;
	if (temp->l_child != nullptr)
		temp->l_child->parent = grand_p;
	temp->l_child = grand_p;
	temp->parent = g_temp;

	if (g_temp == nullptr)
	{
		temp->parent = nullptr;
		root = temp;
	}
	else if (g_temp->l_child == grand_p)
	{
		g_temp->l_child = temp;
	}
	else if (g_temp->r_child == grand_p)
	{
		g_temp->r_child = temp;
	}

	grand_p->parent = temp;

	update_height(grand_p);
}

template <typename A>
void AVLTree<A>::RR_rotation(AVL_node<A>* grand_p)
{
	AVL_node<A>* temp = grand_p->l_child;
	AVL_node<A>* g_temp = grand_p->parent;
	
	grand_p->l_child = temp->r_child;
	if (temp->r_child != nullptr)
		temp->r_child->parent = grand_p;
		
	temp->r_child = grand_p;
	temp->parent = g_temp;

	if (g_temp == nullptr)
	{
		temp->parent = nullptr;
		root = temp;
	}
	else if(g_temp->l_child == grand_p)
	{
		g_temp->l_child = temp;
	}
	else if (g_temp->r_child == grand_p)
	{
		g_temp->r_child = temp;
	}

	grand_p->parent = temp;

	update_height(grand_p);
}

template <typename A>
void AVLTree<A>::LR_rotation(AVL_node<A>* grand_p) //большой правый поворот
{
	LL_rotation(grand_p->l_child);
	RR_rotation(grand_p);
}

template <typename A>
void AVLTree<A>::RL_rotation(AVL_node<A>* grand_p) //большой левый поворот
{
	RR_rotation(grand_p->r_child);
	LL_rotation(grand_p);
}

template <typename A>
void AVLTree<A>::insert(A my_value)
{
	AVL_node<A>* node = root;
	AVL_node<A>* p_node = nullptr;
	bool dubl_flag(false), l_flag(false), r_flag(false);

	if (node != nullptr && node->value == 0)
		root->value = my_value;
	else
	{
		while (node != nullptr)
		{
			if (node->value < my_value)
			{
				p_node = node;
				node = node->r_child;
				l_flag = false;
				r_flag = true;
			}
			else if (node->value > my_value)
			{
				p_node = node;
				node = node->l_child;
				l_flag = true;
				r_flag = false;
			}
			else if (node->value == my_value)
			{
				node->dublicate++;
				dubl_flag = true;
				break;
			}
		}

		if (!dubl_flag)
		{
			if (l_flag)
				AVL_node<A>* new_node = l_child_add(p_node, my_value);
			else if (r_flag)
				AVL_node<A>* new_node = r_child_add(p_node, my_value);

			update_height(p_node);

			AVL_node<A>* bad_node = unbalanced_node(root);
			int balance = balance_factor(bad_node);
			int l_balance = 0;
			int r_balance = 0;
			if (bad_node != nullptr)
			{
				l_balance = balance_factor(bad_node->l_child);
				r_balance = balance_factor(bad_node->r_child);
			}

			if ((balance < -1) && (r_balance < 0))
				LL_rotation(bad_node);
			else if ((balance > 1) && (l_balance > 0))
				RR_rotation(bad_node);
			else if ((balance < -1) && (r_balance > 0))
				RL_rotation(bad_node);
			else if ((balance > 1) && (l_balance < 0))
				LR_rotation(bad_node);
		}
		
	}
}

template <typename A>
void AVLTree<A>::remove(A my_value) 
{
	if (root == nullptr)
	{
		cout << endl << "Дерева не существует!" << endl;
		return;
	}
	
	AVL_node<A>* rem_node = search(root, my_value);
	AVL_node<A>* p_node = nullptr;
	bool dubl_flag(false);

	if (rem_node == nullptr)
	{
		cout << endl << "Элемента с заданным значением не существует!" << endl;
	}
	else if (rem_node->dublicate > 0)
	{
		rem_node->dublicate--;
		dubl_flag = true;
	}
	else if (rem_node->r_child == nullptr)
	{
		if (rem_node->l_child == nullptr)
		{
			if (rem_node->parent == nullptr)
				cout << endl << "Был только корень дерева! Дерева больше не существует!" << endl;
			else
			{
				if (rem_node->parent->l_child == rem_node)
					rem_node->parent->l_child = nullptr;
				else if (rem_node->parent->r_child == rem_node)
					rem_node->parent->r_child = nullptr;
			}

			rem_node = nullptr;
		}
		else
		{
			rem_node->value = rem_node->l_child->value;
			rem_node->dublicate = rem_node->l_child->dublicate;
			rem_node->l_child = nullptr;
		}
	}
	else
	{
		if (rem_node->l_child == nullptr)
		{
			rem_node->value = rem_node->r_child->value;
			rem_node->dublicate = rem_node->r_child->dublicate;
			rem_node->r_child = nullptr;
		}
		else
		{
			AVL_node<A>* found_node = find_min(rem_node->r_child);
			
			rem_node->value = found_node->value;
			rem_node->dublicate = found_node->dublicate;
			
			p_node = found_node->parent;

			if (found_node->r_child == nullptr)
			{
				if (p_node->l_child == found_node)
					p_node->l_child = nullptr;
				else if (p_node->r_child == found_node)
					p_node->r_child = nullptr;

				found_node = nullptr;
			}
			else
			{
				found_node->value = found_node->r_child->value;
				found_node->dublicate = found_node->r_child->dublicate;
				found_node->r_child = nullptr;
				p_node = found_node;
			}
		}
	}

	if (!dubl_flag)
	{
		update_height(p_node);

		AVL_node<A>* bad_node = unbalanced_node(root);
		int balance = balance_factor(bad_node);
		int l_balance = 0;
		int r_balance = 0;
		if (bad_node != nullptr)
		{
			l_balance = balance_factor(bad_node->l_child);
			r_balance = balance_factor(bad_node->r_child);
		}

		if ((balance < -1) && (r_balance < 0))
			LL_rotation(bad_node);
		else if ((balance > 1) && (l_balance > 0))
			RR_rotation(bad_node);
		else if ((balance < -1) && (r_balance > 0))
			RL_rotation(bad_node);
		else if ((balance > 1) && (l_balance < 0))
			LR_rotation(bad_node);
	}
}

template <typename A>
void AVLTree<A>::breadth_search(AVL_node<A>* curr)
{
	AVL_node<A>* node = curr;
	std::queue<AVL_node<A>*> q;
	q.push(node);
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		cout << node->value << " ";

		if (node->l_child != nullptr)
			q.push(node->l_child);
		if (node->r_child != nullptr)
			q.push(node->r_child);
	}
}

template <typename A>
void AVLTree<A>::pre_order_search(AVL_node<A>* curr)
{
	if (curr == nullptr)
		return;

	std::stack<AVL_node<A>*> s;
	s.push(curr);

	while (!s.empty())
	{
		AVL_node<A>* node = s.top();
		s.pop();
		std::cout << node->value << " ";

		if (node->r_child != nullptr)
			s.push(node->r_child);

		if (node->l_child != nullptr)
			s.push(node->l_child);
	}

}

template <typename A>
void AVLTree<A>::in_order_search(AVL_node<A>* curr)
{
	if (curr == nullptr)
		return;

	std::stack<AVL_node<A>*> s;
	AVL_node<A>* node = curr;

	while (!s.empty() || node != nullptr)
	{
		if (node != nullptr)
		{
			s.push(node);
			node = node->l_child;
		}
		else
		{
			node = s.top();
			s.pop();
			std::cout << node->value << " ";
			node = node->r_child;
		}
	}
}

template <typename A>
void AVLTree<A>::post_order_search(AVL_node<A>* curr) 
{
	if (curr == nullptr)
		return;

	std::stack<AVL_node<A>*> s;
	AVL_node<A>* node = curr;
	AVL_node<A>* last_visited = nullptr;
	AVL_node<A>* top_node = nullptr;

	while (!s.empty() || node != nullptr)
	{
		if (node != nullptr)
		{
			s.push(node);
			node = node->l_child;
		}
		else 
		{
			top_node = s.top();
			if (top_node->r_child != nullptr && last_visited != top_node->r_child)
				node = top_node->r_child;
			else
			{
				std::cout << top_node->value << " ";
				last_visited = s.top();
				s.pop();
			}
		}
	}
}

template <typename A>
AVL_node<A>* AVLTree<A>::search(AVL_node<A>* curr, A my_value)
{
	AVL_node<A>* node = curr;
	while (node != nullptr)
	{
		if (node->value == my_value)
			return node;
		else if (node->value > my_value)
			node = node->l_child;
		else if (node->value < my_value)
			node = node->r_child;
	}

	return nullptr;
}

template <typename A>
AVL_node<A>* AVLTree<A>::find_min(AVL_node<A>* curr)
{
	AVL_node<A>* node = curr;
	while (node->l_child != nullptr)
		node = node->l_child;

	return node;
}