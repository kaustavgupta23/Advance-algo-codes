#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    vector<int> keys;        // An array of keys
    int min_order;           // Minimum degree (defines the range for number of keys)
    vector<Node *> children; // An array of child pointers
    int num_of_nodes;        // Current number of keys
    bool leaf;
    Node(int min_order, bool leaf)
    {

        this->min_order = min_order;
        this->leaf = leaf;
        num_of_nodes = 0;
    }
    void insertNonFull(int k);

    // function to split the child of this node. i is index of child in
    // child array children.
    void splitChild(int i, Node *child); // child node is full then csll this

    void print();

    Node *search(int k); // returns nullptr if k is not present.
};

class Btree
{
public:
    Node *root;    // Pointer to root node
    int min_order; // Minimum degree

    Btree(int min_order)
    {
        root = NULL;
        this->min_order = min_order;
    }

    void print()
    {
        if (root != nullptr)
        {
            root->print();
        }
    }

    Node *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k);
};
void Node::print()
{
    // There are num_of_nodes keys and num_of_nodes+1 children, traverse through num_of_nodes keys
    // and first num_of_nodes children
    int i;
    for (i = 0; i < num_of_nodes; i++)
    {
        // inorder traversal
        //  If this is not leaf, then before printing key[i],
        // go to the left tree
        if (leaf == false)
            children[i]->print();
        cout << " " << keys[i];
    }

    // to print num_of_nodes+1 children
    if (leaf == false)
        children[i]->print();
}

Node *Node::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < num_of_nodes && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return nullptr;

    // Go to the appropriate child
    else
        return children[i]->search(k);
}

// remember premptive shifting
void Btree::insert(int k)
{
    // If tree is empty
    if (root == NULL)
    {
        root = new Node(min_order, true);
        root->keys.push_back(k);
        root->num_of_nodes = 1; // number of nodes in root increased by 1
        return;
    }
    else // If tree is not empty
    {
        // If root is full grows in height
        if (root->num_of_nodes == 2 * min_order - 1)
        {

            // we have to create root bu ourself
            Node *newroot = new Node(min_order, false); // false because now this is not a leaf node

            // Make old root as child of new root
            newroot->children.push_back(root);

            // Split the old root and move 1 key to the new root
            newroot->splitChild(0, root); // 0 id the position of this child(root)

            // New root has two children now Decide which of the
            // two children is going to have new key
            int i = 0;
            if (newroot->keys[0] < k)
                i++;
            newroot->children[i]->insertNonFull(k);

            // Change root
            root = newroot;
        }
        else // If root is not full
            root->insertNonFull(k);
    }
}

void Node::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = num_of_nodes - 1;

    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // Finds the location of new key to be inserted
        // Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k)
        {
            cout << keys[i] << endl;
            keys[i + 1] = keys[i]; // shifting to make space
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        num_of_nodes = num_of_nodes + 1;
        return;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--; // find pos of child in i

        // See if the found child is full
        if (children[i + 1]->num_of_nodes == 2 * min_order - 1)
        {
            // If the child is full, then split it
            splitChild(i + 1, children[i + 1]);

            // After split, the middle key of children[i] goes up and
            // children[i] is splitted into two. See which of the two
            // is going to have the new key
            if (keys[i + 1] < k)
                i++; // can go into i or i+1
        }
        children[i + 1]->insertNonFull(k);
    }
}

void Node::splitChild(int i, Node *child)
{
    // Create a new node which is going to store (min_order-1) keys
    // of child
    Node *newchild = new Node(child->min_order, child->leaf);
    newchild->num_of_nodes = min_order - 1;

    // Copy the last (min_order-1) keys of child to newchild
    for (int j = 0; j < min_order - 1; j++)
        newchild->keys.push_back(child->keys[j + min_order]);

    // Copy the last min_order children of child to newchild
    if (child->leaf == false)
    {
        for (int j = 0; j < min_order; j++)
            newchild->children.push_back(child->children[j + min_order]);
    }

    // Reduce the number of keys in child
    child->num_of_nodes = min_order - 1;

    // Since this node is going to have a new child,
    // create space of new child
    children.insert(children.begin() + i + 1, NULL); // this is for the parent of child

    // Link the new child to this node
    children[i + 1] = newchild;

    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    keys.insert(keys.begin() + i, child->keys[min_order - 1]); // for the parent move one key to the parent

    // Increment count of keys in this node
    num_of_nodes = num_of_nodes + 1; // for the parent
}

int main()
{
    cout << "Enter order: ";
    int order;
    cin >> order;

    // Cast to double to ensure floating-point division
    int min_order = static_cast<int>(ceil(order / 2.0));

    Btree t(min_order); // A B-Tree with minimum degree 3
    t.insert(5);
    t.insert(3);
    t.insert(21);
    t.insert(9);
    t.insert(1);
    t.insert(13);
    t.insert(2);
    t.insert(7);
    t.insert(10);
    t.insert(12);
    t.insert(4);
    t.insert(8);

    cout << "traversal of the constructed tree is ";
    t.print();
    cout << endl;

    int k = 8;
    if (t.search(k) != nullptr)
    {
        cout << "present" << endl;
    }
    else
    {
        cout << "not present" << endl;
    }

    return 0;
}