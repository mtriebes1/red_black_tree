//Matthew Triebes
//HW10 -> rbt_collection.h

#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include "collection.h"

template <typename K, typename V>
class RBTCollection : public Collection <K,V>
{
public :

// create an empty linked list
RBTCollection ();

// copy a linked list
RBTCollection (const RBTCollection <K,V>& rhs);

// assign a linked list
RBTCollection<K,V>& operator=(const RBTCollection <K,V>& rhs);

// delete a linked list
~RBTCollection ();

// insert a key - value pair into the collection
void insert ( const K& key, const V& val);

// remove a key - value pair from the collection
void remove (const K& key);

// find the value associated with the key
bool find (const K& key, V& val) const;

// find the keys associated with the range
void find (const K& k1, const K& k2, std::vector <K>& keys) const;

// return all keys in the collection
void keys (std::vector <K>& keys) const;

// return collection keys in sorted order
void sort (std::vector <K>& keys) const;

// return the number of keys in collection
int size () const;

// return the height of the tree
int height () const;

private :
// binary search tree node structure
struct Node {
K key;
V value;
Node* left;
Node* right;
bool is_black; // true if black , false if red
};

// root node of the search tree
Node* root;

// number of k-v pairs in the collection
int collection_size;

// helper to recursively empty search tree
void make_empty (Node* subtree_root);

// recursive helper to remove node with given key
Node* remove(const K& key, Node* subtree_root);

// recursive helper to do red - black insert key - val pair ( backtracking )
Node* insert (const K& key, const V& val, Node* subtree_root);

// helper functions to perform a single right rotation
Node* rotate_right (Node* k2);

// helper functions to perform a single left rotation
Node* rotate_left (Node* k2);

// helper to recursively build sorted list of keys
void inorder (const Node* subtree, std::vector <K>& keys) const;

// helper to recursively build sorted list of keys
void preorder (const Node* subtree, std::vector <K>& keys) const;

void preorder_copy (Node* lhs_subtree, const Node* rhs_subtree);

// helper to recursively find range of keys
void range_search (const Node* subtree_root, const K& k1, const K& k,
std::vector <K>& keys) const;

// return the height of the tree rooted at subtree_root
int height (const Node* subtree_root) const;

};

// ------------------------------------------------------------------------------- Constructor
template <typename K, typename V>
RBTCollection <K,V>::RBTCollection() :
collection_size (0), root (nullptr)
{}

// ------------------------------------------------------------------------------- Destructor
template <typename K, typename V>
RBTCollection <K,V>::~RBTCollection()
{
    make_empty(root);
}

// ------------------------------------------------------------------------------- Copy Constructor
template <typename K, typename V>
RBTCollection <K,V>::RBTCollection (const RBTCollection <K,V>& rhs)
: collection_size(0), root(nullptr)
{
    *this = rhs;
}

//---------------------------------------------------------------------------------------------- rotate_right
template <typename K, typename V>
typename RBTCollection <K,V>::Node* RBTCollection <K ,V >::rotate_right(Node* k2)
{
    Node* k1 = k2 -> left;
    k2 -> left = k1 -> right;
    k1 -> right = k2;
    return k1;
}

//---------------------------------------------------------------------------------------------- rotate_left
template <typename K, typename V>
typename RBTCollection <K ,V >::Node* RBTCollection <K ,V >::rotate_left(Node* k2)
{
    Node* k1 = k2 -> right;
    k2 -> right = k1 -> left;
    k1 -> left = k2;
    return k1;
}

//---------------------------------------------------------------------------------------------- Insert Helper
template < typename K , typename V >
typename RBTCollection <K,V>::Node*
RBTCollection <K,V>::insert(const K& key, const V& val, Node* subtree_root)
{

if (subtree_root == nullptr)
{
    Node* cur = new Node;
    cur -> key = key;
    cur -> value = val;
    cur -> is_black = false;
    cur -> left = nullptr;
    cur -> right = nullptr;
    return cur;
}

if (key <= subtree_root -> key)
{
    subtree_root -> left = insert(key, val, subtree_root -> left);
}
else if (key > subtree_root -> key)
{
    subtree_root -> right = insert(key, val, subtree_root -> right);
}

if (subtree_root -> is_black)
{
    if ((subtree_root -> left != nullptr) && (subtree_root -> right != nullptr) && !(subtree_root -> left -> is_black) && !(subtree_root -> right -> is_black)) //Case 1
    {
        if ((subtree_root -> left -> left != nullptr) && !(subtree_root -> left -> left -> is_black)) //Left - Left 
        {
            subtree_root -> left -> is_black = true;
            subtree_root -> right -> is_black = true;
            subtree_root -> is_black = false;
        }
        else if ((subtree_root -> left -> right != nullptr) && !(subtree_root -> left -> right -> is_black)) //Left - Right
        {
            subtree_root -> left -> is_black = true;
            subtree_root -> right -> is_black = true;
            subtree_root -> is_black = false;           
        } 
        else if ((subtree_root -> right -> right != nullptr) && !(subtree_root -> right -> right -> is_black)) //Right - Right
        {
            subtree_root -> left -> is_black = true;
            subtree_root -> right -> is_black = true;
            subtree_root -> is_black = false;
        }
        else if ((subtree_root -> right -> left != nullptr) && !(subtree_root -> right -> left -> is_black)) //Right - Left
        {
            subtree_root -> left -> is_black = true;
            subtree_root -> right -> is_black = true;
            subtree_root -> is_black = false;
        }
    }
    else if ((subtree_root -> left != nullptr) && !(subtree_root -> left -> is_black) && (subtree_root -> left -> left != nullptr) && !(subtree_root -> left -> left -> is_black)) //Case 2a (left - left)
    { 
        //Re-Color:
        subtree_root -> is_black = false;
        subtree_root -> left -> is_black = true;
        //Rotate:
        subtree_root = rotate_right(subtree_root);
    }
    else if ((subtree_root -> right != nullptr) && !(subtree_root -> right -> is_black) && (subtree_root -> right -> right != nullptr) && !(subtree_root -> right -> right -> is_black)) //Case 2b (right - right)
    {
        //Re-Color:
        subtree_root -> is_black = false;
        subtree_root -> right -> is_black = true;
        //Rotate:
        subtree_root = rotate_left(subtree_root);
    }
    else if((subtree_root -> left != nullptr) && (subtree_root -> left -> right != nullptr) && !(subtree_root -> left -> is_black) && !(subtree_root -> left -> right -> is_black)) // Case 3a (left - Right)
    {
        //Re-Color:
        subtree_root -> is_black = false;
        subtree_root -> left -> right -> is_black = true;
        //Rotate:
        subtree_root -> left = rotate_left(subtree_root -> left);
        subtree_root = rotate_right(subtree_root);
    }
     else if((subtree_root -> right != nullptr) && (subtree_root -> right -> left != nullptr) && !(subtree_root -> right -> is_black) && !(subtree_root -> right -> left -> is_black)) // Case 3b (Right - left)
    {
        //Re-Color:
        subtree_root -> is_black = false;
        subtree_root -> right -> left -> is_black = true;
        //Rotate:
        subtree_root -> right = rotate_right(subtree_root -> right);
        subtree_root = rotate_left(subtree_root);
    }
    
}

return subtree_root;
}

//---------------------------------------------------------------------------------------------- Insert
template < typename K , typename V >
void RBTCollection <K,V>::insert(const K& key, const V& val)
{
    root = insert(key, val, root);
    root -> is_black = true;
    collection_size++;
}

// ------------------------------------------------------------------------------- Size
template <typename K, typename V>
int RBTCollection <K,V>::size () const
{
    return collection_size;
}

// ------------------------------------------------------------------------------- Height
template <typename K, typename V>
int RBTCollection <K,V>::height() const
{
// defer to the height ( recursive ) helper function
return height (root);
}

// ------------------------------------------------------------------------------- Height (helper fxn)
template <typename K, typename V>
int RBTCollection <K,V>::height (const Node* subtree_root) const
{
    if (subtree_root == nullptr) {
        return 0;
    }

    int left_count = 0;
    int right_count = 0;

    left_count = height(subtree_root -> left);
    right_count = height(subtree_root -> right);

    if (left_count > right_count){
        return left_count + 1;
    }

    else {
        return right_count + 1;
    }
}

// ------------------------------------------------------------------------------- Sort
template <typename K, typename V>
void RBTCollection <K,V>::sort(std::vector <K>& ks) const
{
    // defer to the inorder ( recursive ) helper function
    inorder(root, ks);
}

// ------------------------------------------------------------------------------- Keys
template < typename K , typename V >
void RBTCollection <K,V>::keys(std::vector <K>& ks) const
{
    // defer to the inorder ( recursive ) helper function
    inorder(root, ks);
}

// ------------------------------------------------------------------------------- Inorder
template <typename K, typename V>
void RBTCollection <K,V>::inorder(const Node* subtree, std::vector <K>& ks) const
{
    if (subtree == nullptr)
        return;
    
    inorder(subtree->left, ks);
    ks.push_back(subtree -> key);
    inorder(subtree -> right, ks);
}

// ------------------------------------------------------------------------------- Preorder
template <typename K, typename V>
void RBTCollection <K,V>::preorder(const Node* subtree, std::vector <K>& ks) const
{
    if (subtree == nullptr)
        return;
    
    ks.push_back(subtree -> key);
    preorder(subtree -> left, ks);
    preorder(subtree -> right, ks);
}

// ------------------------------------------------------------------------------- Find
template <typename K, typename V>
bool RBTCollection<K,V>::find(const K& key, V& val) const
{
    bool found = false;
    Node* cur = root;

    if (collection_size == 0) {
        return found;
    }

    else {
        while (cur != nullptr) {
            if (cur -> key == key) {
                val = cur -> value;
                found = true;
                return found;
            }
            else if (cur -> key > key) { // Going to the LHS of the Tree
                cur = cur -> left;
            }
            else if (cur -> key < key) { // Going to the RHS of the Tree
                cur = cur -> right;
            }
        }
    }

    return found;
}

// ------------------------------------------------------------------------------- Range Find (helper fxn)
template <typename K, typename V> void
RBTCollection <K,V>::
range_search (const Node* subtree, const K& k1, const K& k2, std::vector <K>& ks) const
{
    if (subtree == nullptr) 
        return;

    if (subtree -> key >= k1 && subtree -> key <= k2) 
        ks.push_back(subtree -> key);

    range_search(subtree -> left, k1, k2, ks);
    range_search(subtree -> right, k1, k2, ks);
}

// ------------------------------------------------------------------------------- Range Find
template <typename K, typename V> void
RBTCollection <K,V>::find(const K& k1, const K& k2, std::vector <K>& ks) const
{
// defer to the range search ( recursive ) helper function
range_search (root, k1, k2, ks);
}

// ------------------------------------------------------------------------------- Remove
template <typename K, typename V>
void RBTCollection <K,V>::remove(const K& key)
{
    root = remove (key, root);
}

// ------------------------------------------------------------------------------- Remove (Helper fxn)
template <typename K, typename V>
typename RBTCollection <K,V>::Node*
RBTCollection <K,V>::remove(const K& key, Node* subtree_root)
{
    V filler;
    
    if (subtree_root == nullptr) {
        return subtree_root;
    }

    else if (!find(key, filler)){
        return subtree_root;
    }
    
    else if (subtree_root and key < subtree_root -> key) 
    {
        subtree_root -> left = remove(key, subtree_root -> left);
    } 
  
    else if (subtree_root and key > subtree_root -> key) 
    {
        subtree_root -> right = remove(key, subtree_root -> right);
    } 

    else if (subtree_root && key == subtree_root -> key)
    {
        //Case 1: Leaf Node
        if (subtree_root -> left == nullptr and subtree_root -> right == nullptr) {
            delete subtree_root;
            subtree_root = nullptr;
            collection_size--;
        } 
        //Case 2: One Child
        else if (subtree_root -> left == nullptr && subtree_root -> right != nullptr) 
        {
            Node* cur = subtree_root -> right;
            delete subtree_root;
            collection_size--;
            return cur;
        }

        else if (subtree_root -> left != nullptr && subtree_root -> right == nullptr)
        {
            Node* cur = subtree_root -> left;
            delete subtree_root;
            collection_size--;
            return cur;           
        }
        //Case 3: Two Children
        else {
            Node* cur = subtree_root -> right;
            while (cur -> left != nullptr)
            {
                cur = cur -> left;
            }
            subtree_root -> key = cur -> key;
            subtree_root -> value = cur -> value;
            subtree_root -> right = remove(cur -> key, subtree_root -> right);
            //collection_size--;
        }
    }
return subtree_root;
}

// ------------------------------------------------------------------------------- make empty
template <typename K, typename V>
void RBTCollection <K,V>:: make_empty (Node* subtree_root)
{
    if (subtree_root == nullptr)
        return;

    make_empty(subtree_root -> left);
    make_empty(subtree_root -> right);

    delete subtree_root;

    collection_size = 0;
    subtree_root == nullptr;
}

// ------------------------------------------------------------------------------- Operator =
template <typename K, typename V>
RBTCollection <K,V>& RBTCollection <K,V>::operator=(const RBTCollection <K,V>&rhs)
{
int i;

if (this == &rhs)
return *this;
// delete current
make_empty(root);
// build tree
std::vector <K> ks;
preorder (rhs.root, ks);

for (i = 0; i < ks.size(); i++){
    V cur;
    find(ks[i], cur);
    insert(ks[i], cur);
}
return *this;
}

// ------------------------------------------------------------------------------- preorder_copy
template <typename K, typename V>
void RBTCollection <K,V>:: preorder_copy (Node* lhs_subtree, const Node* rhs_subtree)
{

}
#endif