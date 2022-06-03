#include "sequoia.h"

using namespace std;

//insert function called from main()
void Sequoia::insert(int x) {
    //creates new node if tree is empty
    if (size == 0)
        root = new SequoiaNode(x);
    //if not empty call SequoiaNode::insert()
    else
        root->insert(x);

    size++;
    if (root->parent != nullptr)
        root = root->parent;
}

//insert function called from Sequoia::insert()
void SequoiaNode::insert(int x) {
    //inserting value to the correct location recursively
    if (x < value)
    {
        if (left != nullptr)
        left->insert(x);
        else
        {
        left = new SequoiaNode(x);
        ((SequoiaNode*)left)->parent = this;
        }
    }
    else
    {
        if (right != nullptr)
        right->insert(x);
        else
        {
        right = new SequoiaNode(x);
        ((SequoiaNode*)right)->parent = this;
        }
    }


    SequoiaNode* root;
    SequoiaNode* current = this;

    //find location of root
    while (true) {
        if (current->parent == nullptr) {
            root = current;
            break;
        }
        current = current->parent;
    }

    //call updateHeight() on all the nodes
    //height needs to be updated before calling fixBalance()
    current = this;
    while (true) {
        if (current == nullptr)
            break;
        current->updateHeight();
        current = current->parent;
    }

    //call fixBalance() on root as it will run through all the nodes below root
    root->fixBalance();
    
    //update height after balance is fixed
    current = this;
    while (true) {
        if (current == nullptr)
            break;
        current->updateHeight();
        current = current->parent;
    }
}

//remove function called from main()
void Sequoia::remove(int x) {
    //return if tree is empty
    if (root == nullptr)
        return;

    SequoiaNode* victim = root->search(x);

    //return if x doesn't exist in the tree
    if (victim == nullptr)
        return;
    
    //if victim is found call SequoiaNode::remove() to victim
    if (victim == root)
        root = victim->remove();
    else
        victim->remove();
}

//remove function called from Sequoia::remove()
SequoiaNode* SequoiaNode::remove() {

    //leaf node
    if (left == nullptr && right == nullptr) {
        parent->left = nullptr;
        parent->right = nullptr;
    }

    //has child
    else {
        //when node is left child to parent
        if (isLeftChild()) {
            if (left != nullptr && right != nullptr) {
                parent->left = left;
                parent->right = right;
                left->parent = parent;
                right->parent = parent;
            } else if (left != nullptr) {
                parent->left = left;
                left->parent = parent;
            } else {
                parent->left = right;
                right->parent = parent;
            }
        }

        //when node is right child to parent
        else if (isRightChild()) {
            if (left != nullptr && right != nullptr) {
                parent->left = left;
                parent->right = right;
                left->parent = parent;
                right->parent = parent;
            } else if (left != nullptr) {
                parent->right = left;
                left->parent = parent;
            } else {
                parent->right = right;
                right->parent = parent;
            }
        }
    }

    SequoiaNode* root;
    SequoiaNode* current = this;

    //find location of root
    while (true) {
        if (current->parent == nullptr) {
            root = current;
            break;
        }
        current = current->parent;
    }

    //call updateHeight() on all the nodes
    //height needs to be updated before calling fixBalance()
    current = this->parent;
    while (true) {
        if (current == nullptr)
            break;
        current->updateHeight();
        current = current->parent;
    }

    //call fixBalance() on root as it will run through all the nodes below root
    root->fixBalance();
    
    //update height after balance is fixed
    current = this->parent;
    while (true) {
        if (current == nullptr)
            break;
        current->updateHeight();
        current = current->parent;
    }

    return parent;

}

//only should be called from the root node
//recuresively fixes the balance of all the nodes under this node (the whole tree)
void SequoiaNode::fixBalance() {
    //set lh and rh accordingly
    int lh, rh;
    if (left != nullptr)
        lh = left->height;
    else
        lh = 0;
    if (right != nullptr)
        rh = right->height;
    else
        rh = 0;

    //check if tree meets the tall condition
    if (2*lh <= rh || 2*rh <= lh) {
        if (left != nullptr)
            left->fixBalance();
        if (right != nullptr)
            right->fixBalance();
    }
    //if tree is not tall, fix balance
    else {
        //case 1
        if (lh >= rh) {
            right->rotateLeft();
        }
        //case 2
        else if (rh > lh) {
            left->rotateRight();
        }
    }
}

//rotates the node left (called in fixBalance)
void SequoiaNode::rotateLeft() {
    ((SequoiaNode*)parent)->right = left;
    if (left != nullptr)
        ((SequoiaNode*)left)->parent = parent;

    left = parent;
    parent = ((SequoiaNode*)parent)->parent;

    if (left->isLeftChild())
        ((SequoiaNode*)parent)->left = this;
    else if (left->isRightChild())
        ((SequoiaNode*)parent)->right = this;
    ((SequoiaNode*)left)->parent = this;
}

//rotates the node right (called in fixBalance)
void SequoiaNode::rotateRight() {
    ((SequoiaNode*)parent)->left = right;
    if (right != nullptr)
        ((SequoiaNode*)right)->parent = parent;

    right = parent;
    parent = ((SequoiaNode*)parent)->parent;

    if (right->isLeftChild())
        ((SequoiaNode*)parent)->left = this;
    else if (right->isRightChild())
        ((SequoiaNode*)parent)->right = this;
    ((SequoiaNode*)right)->parent = this;
}

//check if the node is a left child of parent
bool SequoiaNode::isLeftChild() const {
  return parent != nullptr && parent->left == this;
}

//check if the node is a right child of parent
bool SequoiaNode::isRightChild() const {
  return parent != nullptr && parent->right == this;
}

//update the height of the current node (not the whole tree so this function is in a loop in insert() and remove())
void SequoiaNode::updateHeight() {
    //return if this is leaf node
    if (left == nullptr && right == nullptr) {
        height = 1;
        return;
    }

    //set lh and rh accordingly
    int lh, rh;
    if (left != nullptr)
        lh = this->left->height;
    else
        lh = 1;
    if (right != nullptr)
        rh = this->right->height;
    else
        rh = 1;

    //compare lh and rh and add 1 to the larger value, that is the height of the node
    if (lh <= rh)
        height = rh+1;
    else
        height = lh+1;
}

//recursively searches the location of x in the tree
//called from Sequoia::remove to find the victim
SequoiaNode* SequoiaNode::search(int x) {
    if (x == value)
        return this;
    else if (x < value)
    {
        if (left != nullptr)
        return left->search(x);
        else
        return nullptr;
    }
    else
    {
        if (right != nullptr)
        return right->search(x);
        else
        return nullptr;
    }
}
