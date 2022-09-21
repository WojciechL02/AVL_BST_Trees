#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>
#include "Node.h"

template <typename KeyType, typename ValueType>
class BinarySearchTree
{
private:
	size_t tree_size = 0;
	void transplant(Node<KeyType, ValueType> *u, Node<KeyType, ValueType> *v)
	{
		if (u->parent == nullptr)
		{
			root = v;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		if (v != nullptr)
		{
			v->parent = u->parent;
		}
	}

	void destroy(Node<KeyType, ValueType>* node)
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

	BinarySearchTree()
	{
		root = nullptr;
	}

	~BinarySearchTree()
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
		Node<KeyType, ValueType> new_node;
		Node<KeyType, ValueType> *node = new_node.GetNewNode(key, value);
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
		}
		else if (key < y->key)
		{
			y->left = node;
		}
		else
		{
			y->right = node;
		}
	}

	void remove(KeyType const &key)
	{
		Node<KeyType, ValueType> *z = root;
		while (z != nullptr && key != z->key)
		{
			if (key < z->key)
			{
				z = z->left;
			}
			else
			{
				z = z->right;
			}
		}
		if (z != nullptr)
		{
			tree_size--;
			if (z->left == nullptr)
			{
				this->transplant(z, z->right);
			}
			else if (z->right == nullptr)
			{
				this->transplant(z, z->left);
			}
			else
			{
				Node<KeyType, ValueType> *y = treeMinimum(z->right);
				if (y->parent != z)
				{
					this->transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				this->transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
			}
			delete z;
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
std::ostream &operator<<(std::ostream &stream, BinarySearchTree<KeyType, ValueType> const &tree)
{
	tree.template print<std::ostream>(stream);
	return stream;
}
