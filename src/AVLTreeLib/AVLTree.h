#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>
#include "Node.h"

template <typename KeyType, typename ValueType>
class AVLTree
{
private:
	size_t tree_size = 0;

	void leftRotate(Node<KeyType, ValueType> *x)
	{
		if (x == root)
		{
			x->right->parent = nullptr;
		}
		else
		{
			x->right->parent = x->parent;
			if (x->parent->left == x)
			{
				x->parent->left = x->right;
			}
			else
			{
				x->parent->right = x->right;
			}
		}
		Node<KeyType, ValueType> *tmp = x->right;
		if (tmp->left != nullptr)
		{
			x->right->left->parent = x;
			x->right = x->right->left;
		}
		else
		{
			x->right = nullptr;
		}
		tmp->left = x;
		x->parent = tmp;
		if (x == root)
		{
			root = tmp;
		}
	}

	void rightRotate(Node<KeyType, ValueType> *y)
	{
		if (y == root)
		{
			y->left->parent = nullptr;
		}
		else
		{
			y->left->parent = y->parent;
			if (y->parent->right == y)
			{
				y->parent->right = y->left;
			}
			else
			{
				y->parent->left = y->left;
			}
		}
		Node<KeyType, ValueType> *tmp = y->left;
		if (tmp->right != nullptr)
		{
			y->left->right->parent = y;
			y->left = y->left->right;
		}
		else
		{
			y->left = nullptr;
		}
		tmp->right = y;
		y->parent = tmp;
		if (y == root)
		{
			root = tmp;
		}
	}

	void Balance(Node<KeyType, ValueType> *node, int side)
	{
		node->balance += side;
		while (node->parent != nullptr && node->balance != 0)
		{
			if (node->balance == 1)
			{
				if (node->parent->left == node)
				{
					if (node->parent->balance == 1)
					{
						rightRotate(node->parent);
						UpdateBalanceAfterOneRotationAfterInsert(node->right);
						return;
					}
					side = 1;
				}
				else
				{
					if (node->parent->balance == -1)
					{

						rightRotate(node);
						leftRotate(node->parent->parent);
						UpdateBalanceAfterDoubleRotationAfterInsert(node->parent->left, -1);
						return;
					}
					side = -1;
				}
			}
			else
			{
				if (node->parent->left == node)
				{
					if ((node->parent->balance == 1))
					{
						leftRotate(node);
						rightRotate(node->parent->parent);
						UpdateBalanceAfterDoubleRotationAfterInsert(node->parent->right, 1);
						return;
					}
					side = 1;
				}
				else
				{
					if (node->parent->balance == -1)
					{
						leftRotate(node->parent);
						UpdateBalanceAfterOneRotationAfterInsert(node->left);
						return;
					}
					side = -1;
				}
			}
			node = node->parent;
			if (node != nullptr)
				node->balance += side;
		}
	}

	void UpdateBalanceAfterOneRotationAfterInsert(Node<KeyType, ValueType> *node) noexcept
	{
		node->balance = 0;
		node->parent->balance = 0;
	}

	void UpdateBalanceAfterDoubleRotationAfterInsert(Node<KeyType, ValueType> *node, int side) noexcept
	{
		node->balance = 0;
		node->parent->balance = 0;
		if (side == 1)
		{
			if (node->parent->left != nullptr)
			{
				node->parent->left->balance = 0;
			}
			else
			{
				node->parent->left->balance = 1;
			}
		}
		else
		{
			if (node->parent->right != nullptr)
			{
				node->parent->right->balance = 0;
			}
			else
			{
				node->parent->right->balance = -1;
			}
		}
	}

	void destroy(Node<KeyType, ValueType> *node)
	{
		if (node != nullptr)
		{
			if (node->left != nullptr)
			{
				destroy(node->left);
			}
			if (node->right != nullptr)
			{
				destroy(node->right);
			}
			delete node;
		}
	}

public:
	Node<KeyType, ValueType> *root;

	AVLTree()
	{
		root = nullptr;
	}

	~AVLTree()
	{
		destroy(root);
	}

	size_t size() const
	{
		return tree_size;
	}

	Node<KeyType, ValueType> *treeMinimum(Node<KeyType, ValueType> *x)
	{
		while (x->left != nullptr)
		{
			x = x->left;
		}
		return x;
	}

	void insert(KeyType const &key, ValueType const &value)
	{
		Node<KeyType, ValueType> *node = new Node(key, value);
		Node<KeyType, ValueType> *y = nullptr;
		Node<KeyType, ValueType> *x = root;
		while (x != nullptr)
		{
			y = x;
			if (key < x->key)
			{
				x = x->left;
			}
			else if (key > x->key)
			{
				x = x->right;
			}
			else
			{
				x->value = value;
				return;
			}
		}
		tree_size++;
		node->parent = y;
		if (y == nullptr)
		{
			root = node;
			return;
		}
		else if (key < y->key)
		{
			y->left = node;
			Balance(y, 1);
		}
		else
		{
			y->right = node;
			Balance(y, -1);
		}
	}

	ValueType *find(KeyType const &key)
	{
		Node<KeyType, ValueType> *node = root;
		while (node != nullptr && key != node->key)
		{
			if (key < node->key)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}
		if (node == nullptr)
		{
			return nullptr;
		}
		return &(node->value);
	}

	std::string toString() const
	{
		return root->toString();
	}

	template <typename StreamType>
	void print(StreamType &stream) const
	{
		if (root != nullptr)
		{
			KeyType key1 = root->key;
			ValueType value1 = root->value;
			stream << "[" << key1 << ", " << value1 << "]\n"
				   << (root->PrintNode(0)).str();
		}
	}
};

template <typename KeyType, typename ValueType>
std::ostream &operator<<(std::ostream &stream, AVLTree<KeyType, ValueType> const &tree)
{
	tree.template print<std::ostream>(stream);
	return stream;
}
