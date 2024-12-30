#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
    key = -1;
    parent = NULL;
    left = NULL;
    right = NULL;
}
// Constructor
Node::Node(int in) {
// TODO: Implement this
    key = in;
    parent = NULL;
    left = NULL;
    right = NULL;
}
// Destructor
Node::~Node() {
// TODO: Implement this

}

// Add parent 
void Node::add_parent(Node* in) {
// TODO: Implement this
    parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
// TODO: Implement this
    left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
// TODO: Implement this
    right = in;
}

// Get key
int Node::get_key() {
// TODO: Implement this
    return key;
}
// Get parent node
Node* Node::get_parent() {
// TODO: Implement this
    return parent;
}
// Get left node
Node* Node::get_left() {
// TODO: Implement this
    return left;
}
// Get right node
Node* Node::get_right() {
// TODO: Implement this
    return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to) {
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to) {
// TODO: Implement this
    Node* cur_node = in;
    if (in != NULL) {
        inorder_walk(cur_node->get_left(), to);
        to << cur_node->get_key() << " ";
        inorder_walk(cur_node->get_right(), to);
    }
}
// Constructor
BST::BST() {
// TODO: Implement this
    root = NULL;
}
// Destructor
BST::~BST() {
// TODO: Implement this

}
// Insert a node to the subtree
void BST::insert_node(Node* in) {
// TODO: Implement this
    // cout << "node: " << in->get_key() << endl;
    Node* cur_node = root;
    Node* par_node = NULL;
    while (cur_node != NULL) {
        par_node = cur_node;
        if (in->get_key() < cur_node->get_key()) {
            cur_node = cur_node->get_left();
        } else {
            cur_node = cur_node->get_right();
        }
    }
    in->add_parent(par_node);
    if (par_node == NULL) { 
        root = in; 
        // cout << "I'm the root" << endl;
    } else if (in->get_key() < par_node->get_key()) { 
        par_node->add_left(in);
        // cout << "I'm the left node of " << in->get_parent()->get_key() << endl;
    } else {
        par_node->add_right(in);
        // cout << "I'm the right node of " << in->get_parent()->get_key() << endl;
    }
}
// Delete a node to the subtree
void BST::delete_node(Node* out) {
// TODO: Implement this
    Node* child_node = NULL;
    Node* succ_node = NULL;

    if (out->get_left() == NULL || out->get_right() == NULL) {
        succ_node = out;
    } else {
        succ_node = get_succ(out);
    }
    if (succ_node->get_left() != NULL) {
        child_node = succ_node->get_left();
    } else {
        child_node = succ_node->get_right();
    }
    if (child_node != NULL) {
        child_node->add_parent(succ_node->get_parent());
    }
    if (succ_node->get_parent() == NULL) {
        root = child_node;
    } else if (succ_node == succ_node->get_parent()->get_left()) {
        succ_node->get_parent()->add_left(child_node);
    } else {
        succ_node->get_parent()->add_right(child_node);
    }
    if (succ_node != out) {
        if (root == out) { root = succ_node; }
        succ_node->add_left(out->get_left());
        succ_node->add_right(out->get_right());
        succ_node->add_parent(out->get_parent());
        if (out->get_left() != NULL) { out->get_left()->add_parent(succ_node); }
        if (out->get_right() != NULL) { out->get_right()->add_parent(succ_node); }
        if (out->get_parent() != NULL) {
        if (out->get_parent()->get_left() == out) { out->get_parent()->add_left(succ_node); }
        if (out->get_parent()->get_right() == out) { out->get_parent()->add_right(succ_node); } }
    }
}
// minimum key in the BST
Node* BST::tree_min() {
// TODO: Implement this
    return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max() {
// TODO: Implement this
    return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in) {
// TODO: Implement this
    Node* cur_node = in;
    while (cur_node->get_left() != NULL) {
        cur_node = cur_node->get_left();
    }
    return cur_node;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in) {
// TODO: Implement this
    Node* cur_node = in;
    while (cur_node->get_right() != NULL) {
        cur_node = cur_node->get_right();
    }
    return cur_node;
}
// Get successor of the given node
Node* BST::get_succ(Node* in) {
// TODO: Implement this
    Node* cur_node = in;
    Node* par_node = NULL;
    if (in == tree_max()) {
        return NULL;
    }
    if (cur_node->get_right() != NULL) {
        return get_min(cur_node->get_right());
    }
    par_node = cur_node->get_parent();
    while (par_node != NULL && cur_node == par_node->get_right()) {
        cur_node = par_node;
        par_node = par_node->get_parent();
    }
    // cout << "node: " << par_node << endl;
    return par_node;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in) {
// TODO: Implement this
    Node* cur_node = in;
    Node* par_node = NULL;
    if (in == tree_min()) {
        return NULL;
    }
    if (cur_node->get_left() != NULL) {
        return get_max(cur_node->get_left());
    }
    par_node = cur_node->get_parent();
    while (par_node != NULL && cur_node == par_node->get_left()) {
        cur_node = par_node;
        par_node = par_node->get_parent();
    }
    return par_node;
}
// Walk the BST from min to max
void BST::walk(ostream& to) {
// TODO: Implement this
    inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key) {
// TODO: Implement this
    Node* cur_node = root;
    while (cur_node != NULL && cur_node->get_key() != search_key) {
        if (search_key < cur_node->get_key()) {
            cur_node = cur_node->get_left();
        } else {
            cur_node = cur_node->get_right();
        }
    }
    return cur_node;
}
// ---------------------------------------
