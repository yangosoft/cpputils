#ifndef __CCPUTILS_BTREE_h__
#define __CCPUTILS_BTREE_h__


namespace CppUtils
{
template <typename KeyType>
class BTree
{
public:
    BTree(): m_root(nullptr) {};
    ~BTree()
    {
        destroy();
    };



    struct Node
    {
        KeyType keyValue;
        Node *left;
        Node *right;
    };

    void insert(KeyType key)
    {
        if(m_root!=nullptr)
        {
            insert(key, m_root);
        }
        else
        {
            m_root = new Node;
            m_root->key_value = key;
            m_root->left = nullptr;
            m_root->right = nullptr;
        }
    }
    Node *search(KeyType key)
    {
        return search(key, m_root);
    }
    void destroy()
    {
        destroy(m_root);
    }

private:
    void destroy(Node *leaf)
    {
        if(leaf != nullptr)
        {
            destroy(leaf->left);
            destroy(leaf->right);
            delete leaf;
        }
    }

    void insert(KeyType key, Node *leaf)
    {
        if(key < leaf->key_value)
        {
            if(leaf->left!=nullptr)
            {
                insert(key, leaf->left);
            }
            else
            {
                leaf->left = new Node;
                leaf->left->key_value = key;
                leaf->left->left = nullptr;    
                leaf->left->right = nullptr;   
            }
        }
        else if(key >= leaf->key_value)
        {
            if(leaf->right != nullptr)
            {
                insert(key, leaf->right);
            }
            else
            {
                leaf->right = new Node;
                leaf->right->key_value = key;
                leaf->right->left = nullptr;  
                leaf->right->right = nullptr; 
            }
        }
    }

    Node *search(KeyType key, Node *leaf)
    {
        if(leaf != nullptr)
        {
            if(key == leaf->key_value)
            {
                return leaf;
            }
            if(key < leaf->key_value)
            {
                return search(key, leaf->left);
            }
            else
            {
                return search(key, leaf->right);
            }
        }
        
        return nullptr;
    }

    Node *m_root;
};
}

#endif //__CCPUTILS_BTREE_h__
