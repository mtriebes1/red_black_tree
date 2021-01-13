//Matthew Triebes
//HW11 -> rbt_collection.h

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

void pre_order_print () const;

private :
// binary search tree node structure
struct Node {
K key;
V value;
Node* left;
Node* right;
bool is_black; // true if black , false if red
bool is_dbl_black_left; // for remove rotations
bool is_dbl_black_right; // for remove rotations
};

// root node of the search tree
Node* root;

// number of k-v pairs in the collection
int collection_size;

// helper to recursively empty search tree
void make_empty (Node* subtree_root);

// recursive helper to remove node with given key
Node* remove (const K& key, Node* parent, Node* subtree_root, bool& found);

// helper to perform a single rebalance step on a red - black tree on remove
Node* remove_color_adjust (Node* parent);

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
    cur -> is_dbl_black_left = false;
    cur -> is_dbl_black_right = false;
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
// check if anything to remove
if (root == nullptr)
    return;
// create a " fake " root to pass in as parent of root
Node* root_parent = new Node;
root_parent -> key = root -> key;
root_parent -> left = nullptr;
root_parent -> right = root;
root_parent -> is_black = true;
root_parent -> is_dbl_black_left = false;
root_parent -> is_dbl_black_right = false;
// call remove
bool found = false;
root_parent = remove (key, root_parent, root, found);
// update results
if (found) {
    collection_size--;
    root = root_parent -> right;
    if (root){
        root -> is_black = true;
        root -> is_dbl_black_right = false;
        root -> is_dbl_black_left = false ;
    }
}
delete root_parent;
}

// ------------------------------------------------------------------------------- Remove (Helper fxn)

template < typename K , typename V >
typename RBTCollection <K ,V >::Node*
RBTCollection <K,V>::remove(const K& key, Node* parent, Node* subtree_root, bool& found)
{
    if(subtree_root && key < subtree_root -> key)
        subtree_root = remove(key, subtree_root, subtree_root -> left, found);

    else if (subtree_root && key > subtree_root -> key)
        subtree_root = remove (key, subtree_root, subtree_root -> right, found);

    else if (subtree_root && key == subtree_root -> key) 
    {
        found = true;
        // leaf node
        if (!subtree_root -> left && !subtree_root -> right) 
        {
            if (subtree_root -> is_black)
            {
                if (parent -> left == subtree_root)
                {
                    parent -> is_dbl_black_left = true;
                    parent -> left = nullptr; // check 
                    delete subtree_root;
                }
                else 
                {
                    parent -> is_dbl_black_right = true;
                    parent -> right = nullptr; // check
                    delete subtree_root;
                }
            }
            else if (!(subtree_root -> is_black)) 
            {
                if (parent -> left == subtree_root)
                {
                    parent -> left = nullptr;
                    delete subtree_root;
                }
                else 
                {
                    parent -> right = nullptr;
                    delete subtree_root;
                }
            }
        }

        // left not empty but right empty (1 Child - Left)
        else if (subtree_root -> left && !subtree_root -> right) 
        {
            if (parent -> left == subtree_root)
            {
                if (!(subtree_root -> is_black)) //Node to delete is RED
                {
                    parent -> left = subtree_root -> left;
                    subtree_root -> left = nullptr;
                }
                else // Node to delete is black
                {
                    parent -> left = subtree_root -> left;
                    parent -> is_dbl_black_left = true;
                    subtree_root -> left = nullptr;
                }
            }
            else if (parent -> right == subtree_root)
            {
                if (!(subtree_root -> is_black)) //Node to delete is RED
                {
                    parent -> right = subtree_root -> left;
                    subtree_root -> left = nullptr;
                }
                else // Node to delete is Black
                {
                    parent -> right = subtree_root -> left;
                    parent -> is_dbl_black_right = true;
                    subtree_root -> left = nullptr;
                }
            delete subtree_root;
            subtree_root = nullptr;
            }
        }
        
        // left empty but right non - empty (1 Child - Right)
        else if (!subtree_root -> left && subtree_root -> right) 
        {
            if (parent -> left == subtree_root)
            {
                if (!(subtree_root -> is_black)) //Node to delete is RED
                {
                    parent -> left = subtree_root -> right;
                    subtree_root -> right = nullptr;
                }
                else //Node to delete is BLACK
                {
                    parent -> left = subtree_root -> right;
                    parent -> is_dbl_black_left = true;
                    subtree_root -> right = nullptr;
                }
            }
            else if (parent -> right == subtree_root)
            {
                if (!(subtree_root -> is_black)) //Node to delete is RED
                {
                    parent -> right = subtree_root -> right;
                    subtree_root -> right = nullptr;
                }
                else //Node to delete is BLACK
                {
                    parent -> right = subtree_root -> right;
                    parent -> is_dbl_black_right = true;
                    subtree_root -> right = nullptr;
                }
            }
            delete subtree_root;
            subtree_root = nullptr;
        }

        // left and right non empty (2 Children)
        else 
        {
            Node* cur = subtree_root -> right;
            while (cur != nullptr && cur -> left != nullptr)
            {
                cur = cur -> left;
            }
            subtree_root -> key = cur -> key;
            subtree_root -> value = cur -> value;
            subtree_root = remove(cur -> key, subtree_root, subtree_root -> right, found);
        }
    }

    if (!found)
        return parent;

    // backtracking , adjust color at parent
    return remove_color_adjust(parent);
}

// ------------------------------------------------------------------------------- color re-adjust

template <typename K, typename V>
typename RBTCollection <K ,V >:: Node*
RBTCollection <K ,V >::remove_color_adjust(Node* subtree_root)
{
    // subtree root is " grandparent " g, with left child gl and right child gr
    Node* g = subtree_root;
    Node* gl = g -> left;
    Node* gr = g -> right;
    // parent p is either gl or gr
    Node* p = nullptr;
    bool left_parent = false;
    
    if (gl && (gl -> is_dbl_black_left || gl -> is_dbl_black_right)) 
    {
        p = gl;
        left_parent = true;
    }

    else if (gr && ( gr -> is_dbl_black_left || gr -> is_dbl_black_right))
        p = gr;
    else
        return subtree_root;

    // parent ’s left child is a double black node
    if (p -> is_dbl_black_left) 
    {
        // case 0: Left exists and IS Red
        if (p -> left && !p -> left -> is_black) 
        {								
			p -> is_dbl_black_left = false;
			p -> left -> is_black = true;
		}
        // case 1: red sibling
        else if (!p -> right -> is_black) 
        {								
			p = rotate_left(p);												
			p -> is_black = true;
			// Run Case 3a
			p -> left -> is_black = true;
			p -> left -> is_dbl_black_left = false;
			p -> left -> right -> is_black = false; 
		}
        // case 2a: black sibling with red child (outside)
        else if (p -> right -> right && !p -> right -> right -> is_black) 
        {	
			p -> right -> is_black = p -> is_black;
			p -> right -> right -> is_black = true;
			p -> is_black = true;
			p = rotate_left(p);
			p -> left -> is_dbl_black_left = false;
		}
        // case 2b: black sibling with red child (inside)
        else if (p -> right -> left && !p -> right -> left -> is_black) 
        {
			p -> right = rotate_right(p -> right);
			p = rotate_left(p);
			p -> is_black = p -> left -> is_black;
			p -> left -> is_black = true;
			p -> left -> is_dbl_black_left = false;
		}
        // case 3a: black sibling with black children, red parent
        else if (!p -> is_black) 
        {
			p -> is_black = true;
			p -> is_dbl_black_left = false;
			p -> right -> is_black = false;
		}
        // case 3b: black sibling with black children, black parent
        else 
        {
			if (left_parent) {
				g -> is_dbl_black_left = true;
			} 
            else {
				g -> is_dbl_black_right = true;
			}
			p -> is_dbl_black_left = false;
			p -> right -> is_black = false;
		}
    }

    // parent ’s right child is a double black node
    if (p -> is_dbl_black_right) 
    {
        // case 0: Right exists and IS Red
        if (p -> right && !p -> right -> is_black) 
        {
			p -> is_dbl_black_right = false;
			p -> right -> is_black = true;
		}
        // case 1: red sibling
        else if (!p -> left -> is_black) 
        {
			p = rotate_right(p);
			p -> is_black = true;
			// Run case 3a
			p -> right -> is_black = true;
			p -> right -> is_dbl_black_right = false;
			p -> right -> left -> is_black = false; 
			
		}
        // case 2a: black sibling with red child (outside)
        else if (p -> left -> left && !p -> left -> left -> is_black) 
        {
			p -> left -> is_black = p -> is_black;
			p -> left -> left -> is_black = true;
			p -> is_black = true;
			p = rotate_right(p);
			p -> right -> is_dbl_black_right = false;
		}
        // case 2b: black sibling with red child (inside)
        else if (p -> left -> right && !p -> left -> right -> is_black) 
        {	
			p -> left = rotate_left(p -> left);
			p = rotate_right(p);
			p -> is_black = p -> right -> is_black;
			p -> right -> is_black = true;
			p -> left -> is_black = true;
			p -> right -> is_dbl_black_right = false;
		}
        // case 3a: black sibling with black children, red parent
        else if (!p -> is_black) 
        {										
			p -> is_black = true;
			p -> is_dbl_black_right = false;
			p -> left -> is_black = false;
		}
        // case 3b: black sibling with black children, black parent
        else {
			if (left_parent) {
				g -> is_dbl_black_left = true;
			} 
            else {
				g -> is_dbl_black_right = true;
			}
			p -> is_dbl_black_right = false;
			p -> left -> is_black = false;
		}
    }
    // connect up the subtree_root to the parent
    if (left_parent)
        subtree_root -> left = p;
    else
        subtree_root -> right = p;

    return subtree_root ;
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

// ------------------------------------------------------------------------------- Operator '='
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