#include <iostream>

template <typename KeyType, typename ValueType>
class Node
{
public:
    KeyType key;
    ValueType value;
    Node *left;
    Node *right;
    Node *parent;
    Node() noexcept
    {
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
    Node *GetNewNode(KeyType const &key, ValueType const &value)
    {
        Node *newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }
    Node(KeyType const &key, ValueType const &value) noexcept
    {
        this->key = key;
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

    std::string toString() const
    {
        if (this == nullptr)
        {
            return "";
        }
        KeyType key1 = key;
        ValueType value1 = value;
        std::string NodeText = "([" + std::to_string(key1) + "," + std::to_string(value1) + "],";
        if (left != nullptr)
        {
            NodeText += left->toString();
        }
        NodeText += ",";
        if (this->right != nullptr)
        {
            NodeText += right->toString();
        }
        NodeText += ")";
        return NodeText;
    }
    std::ostringstream PrintNode(int depth)
    {
        std::ostringstream stream;
        stream << "";
        if (this == nullptr)
            return stream;
        std::string gap = std::string((4 * (depth + 1)), ' ');
        depth++;
        if (this->left != nullptr)
        {
            KeyType key1 = left->key;
            ValueType value1 = left->value;
            stream << gap << "L: [" << key1 << ", " << value1 << "]\n"
                   << (left->PrintNode(depth)).str();
        }
        if (this->right != nullptr)
        {
            KeyType key2 = right->key;
            ValueType value2 = right->value;
            stream << gap << "R: [" << key2 << ", " << value2 << "]\n"
                   << (right->PrintNode(depth)).str();
        }
        return stream;
    }
};
