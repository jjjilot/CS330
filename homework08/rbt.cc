#include "rbt.h"

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}



// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
    /* TODO */
    RBTNode* x = (RBTNode*)y->get_left();
    y->add_left(x->get_right());

    if (x->get_right() != sentinel) {
        x->get_right()->add_parent(y);
    }

    x->add_parent(y->get_parent());

    if (y->get_parent() == sentinel) {
        root = x;
    } else if (y == y->get_parent()->get_right()) {
        y->get_parent()->add_right(x);
    } else {
        y->get_parent()->add_left(x);
    }

    x->add_right(y);
    y->add_parent(x);
}
// Left rotate
void RBT::left_rotate(RBTNode* x)
{
    /* TODO */
    RBTNode* y = (RBTNode*)x->get_right();
    x->add_right(y->get_left());

    if (y->get_left() != sentinel) {
        y->get_left()->add_parent(x);
    }

    y->add_parent(x->get_parent());

    if (x->get_parent() == sentinel) {
        root = y;
    } else if (x == x->get_parent()->get_left()) {
        x->get_parent()->add_left(y);
    } else {
        x->get_parent()->add_right(y);
    }

    y->add_left(x);
    x->add_parent(y);
}
void RBT::rb_insert_fixup(RBTNode* in)
{
    /* TODO */
    RBTNode* q = (RBTNode*)in->get_parent();
    RBTNode* r = (RBTNode*)in->get_parent()->get_parent();
    while (q->get_color() == RED) {
        if (q == (RBTNode*)r->get_left()) {
            RBTNode* y = (RBTNode*)r->get_right();
            if (y->get_color() == RED) {
                q->add_color(BLACK);
                y->add_color(BLACK);
                r->add_color(RED);
                in = r;
            } else {
                if (in == (RBTNode*)q->get_right()) {
                    in = q;
                    left_rotate(in);
                }
                q->add_color(BLACK);
                r->add_color(RED);
                right_rotate(r);
            }
        } else {
            RBTNode* y = (RBTNode*)r->get_left();
            if (y->get_color() == RED) {
                q->add_color(BLACK);
                y->add_color(BLACK);
                r->add_color(RED);
                in = r;
            } else {
                if (in == (RBTNode*)q->get_left()) {
                    in = q;
                    right_rotate(in);
                }
                q->add_color(BLACK);
                r->add_color(RED);
                left_rotate(r);
            }
        }
    }
    ((RBTNode*)root)->add_color(BLACK);
}

void RBT::rb_insert_node(RBTNode* in)
{
    /* TODO */
    BST::insert_node(in, sentinel);
    in->add_left(sentinel);
    in->add_right(sentinel);
    in->add_color(RED);

    rb_insert_fixup(in);
}

void RBT::rb_delete_fixup(RBTNode* in)
{
    /* TODO */
    RBTNode* w;
    RBTNode* q = (RBTNode*)in->get_parent();

    while (in != root && in->get_color() == BLACK) {
        if (in == in->get_parent()->get_left()) {
            w = (RBTNode*)q->get_right();
            if (w->get_color() == RED) {
                w->add_color(BLACK);
                q->add_color(RED);
                left_rotate(q);
                w = (RBTNode*)q->get_right();
            }
            if (((RBTNode*)w->get_left())->get_color() == BLACK && ((RBTNode*)w->get_right())->get_color() == BLACK) {
                w->add_color(RED);
                in = q;
            } else {
                if (((RBTNode*)w->get_right())->get_color() == BLACK) {
                    ((RBTNode*)w->get_left())->add_color(BLACK);
                    w->add_color(RED);
                    right_rotate(q);
                    w = (RBTNode*)q->get_right();
                }
                w->add_color(q->get_color());
                q->add_color(BLACK);
                left_rotate(q);
                in = (RBTNode*)root;
            }
        } else {
            w = (RBTNode*)q->get_left();
            if (w->get_color() == RED) {
                w->add_color(BLACK);
                q->add_color(RED);
                right_rotate(q);
                w = (RBTNode*)q->get_left();
            }
            if (((RBTNode*)w->get_right())->get_color() == BLACK && ((RBTNode*)w->get_left())->get_color() == BLACK) {
                w->add_color(RED);
                in = q;
            } else {
                if (((RBTNode*)w->get_left())->get_color() == BLACK) {
                    ((RBTNode*)w->get_right())->add_color(BLACK);
                    w->add_color(RED);
                    left_rotate(q);
                    w = (RBTNode*)q->get_left();
                }
                w->add_color(q->get_color());
                q->add_color(BLACK);
                right_rotate(q);
                in = (RBTNode*)root;
            }
        }
    }
    in->add_color(BLACK);
}

void RBT::rb_delete_node(RBTNode* out)
{
    /* TODO */
    RBTNode* y;
    RBTNode* x;
    if (out->get_left() == sentinel || out->get_right() == sentinel) {
        y = out;
    } else {
        y = get_succ(out);
    }

    if (y->get_left() != sentinel) {
        x = (RBTNode*)y->get_left();
    } else {
        x = (RBTNode*)y->get_right();
    }
    x->add_parent(y->get_parent());

    if (y->get_parent() == sentinel) {
        root = x;
    } else if (y == (RBTNode*)y->get_parent()->get_left()) {
        y->get_parent()->add_left(x);
    } else {
        y->get_parent()->add_right(x);
    }

    if (y != out) {
        if (root == out) { root = y; }
        y->add_left(out->get_left());
        y->add_right(out->get_right());
        y->add_parent(out->get_parent());
        y->add_color(out->get_color());
        if (out->get_left() != sentinel) { out->get_left()->add_parent(y); }
        if (out->get_right() != sentinel) { out->get_right()->add_parent(y); }
        if (out->get_parent() != sentinel) {
        if (out->get_parent()->get_left() == out) { out->get_parent()->add_left(y); }
        if (out->get_parent()->get_right() == out) { out->get_parent()->add_right(y); } }
    }

    if (y->get_color() == BLACK) {
        rb_delete_fixup(x);
    }
}

// ---------------------------------------
