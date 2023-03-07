/**
 * Splay tree
 * CS 124
 * University of Vermont
 * Lisa Dion
 * 2018-Jun-20
 *
 * Clayton Cafiero
 * 2020-Dec-23
 * Minor revisions:
 *   - Reformatting long lines
 *   - Changes to conform to course style guide
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <memory>

template <typename Comparable>
class BinarySearchTree {
private:
    struct BinaryNode {
        Comparable value;
        BinaryNode* leftChild;
        BinaryNode* rightChild;

        // Constructors
        BinaryNode() : value(Comparable()), leftChild(nullptr),
                       rightChild(nullptr) {}
        explicit BinaryNode(Comparable c) : value(c), leftChild(nullptr),
                                            rightChild(nullptr) {}
        BinaryNode(Comparable c, BinaryNode* l, BinaryNode* r) : value(c),
                                                                 leftChild(l),
                                                                 rightChild(r) {}
    };
    BinaryNode* root;

    // Helper recursive function to destroy the tree.
    void destroy(BinaryNode* &n) {
        if (n != nullptr) {
            destroy(n->leftChild);
            destroy(n->rightChild);
            delete n;
            n = nullptr;
        }
    }

    // Helper recursive function to copy the tree.
    BinaryNode* copyNode(BinaryNode* n) {
        return (n == nullptr)? nullptr : new BinaryNode(n->value,
                                                        copyNode(n->leftChild),
                                                        copyNode(n->rightChild));
    }

// modify the find() methods so that a search of the tree stores the depth of the last node visited.
    // pass an integer variable by reference into the find methods and modify it inside the methods.
    // Helper recursive function to find a value in the tree.
    // Instantiate a binary search tree (of integer values) and insert the numbers 1 through 100 in that order,
    // then search for all numbers 1 through 100 and record their depths in a file.
    bool find(const Comparable& c, BinaryNode* n, int $depth) const {

        // Make sure that you record the depth of the last node visited even if the search fails,
        // so that you know how far you had to search before failing to find the target value.
        if (n == nullptr) {
            // Reached a dead end. Value not in tree.
            return false;
        }
        if (c < n->value) {
            // Value is less than current node. Go to node's left child. Store depth of last node visited.
            return find(c, n->leftChild, ++depth);
        }

        // Now instantiate a new BST and insert the numbers 1 through 100 in random order.
        // You may use https://www.random.org to generate a shuffled list of numbers 1 through 100, or you can shuffle
        // a vector of numbers 1 through 100 using C++’s shuffle method.

        // Now search for each number from 1 through 100, and record the depth of each find operation to a file.
        // Now instantiate a BST to hold objects of your custom data type.

        // Read your objects into a vector (as you have done in earlier projects) and then insert them into the BST.
        // Make sure you have at least 1000 objects in your BST.
        // Now search for each of your objects and record its depth in a file.

        if (n->value < c) {
            // Value is greater than current node. Go to node's right child. Store depth of last node visited.
            return find(c, n->rightChild, ++depth);
        }
        // If code reaches here, c == n->value. Node found!
        return true;
    }
    // Saving your output to three separate files will make your life easier.
    // Each file should have integer value (or your custom object’s unique ID) and depth separated by a
    // comma for each row. If you use a .csv extension when naming your output files, spreadsheet software
    // will automatically recognize these as CSVs and will split the data into columns automatically when reading.

    // Helper recursive function to add a value to the tree.
    void add(const Comparable& c, BinaryNode* &n) {
        if (n == nullptr) {
            // We found the place where we can add the node.
            n = new BinaryNode(c, nullptr, nullptr);
        }
        else if (c < n->value) {
            // Value is less than current node. Go to left child.
            add(c, n->leftChild);
        }
        else if (n->value < c) {
            // Value is greater than current node. Go to right child.
            add(c, n->rightChild);
        }
        // If code reaches here, value is a duplicate. Nothing to do.
    }

    // Helper recursive method to find the maximum value from a given node.
    Comparable& findMax(BinaryNode* n) {
        if (n->rightChild == nullptr) {
            return n->value;
        }
        return findMax(n->rightChild);
    }

    // Helper recursive function to delete a value from the tree.
    void remove(const Comparable& c, BinaryNode* &n) {
        if (n == nullptr) {
            // We did not find the value. Cannot remove it. Nothing to do.
            return;
        }
        else if (c < n->value) {
            // Value is less than current node. Go to left child.
            remove(c, n->leftChild);
        }
        else if (n->value < c) {
            // Value is greater than current node. Go to right child.
            remove(c, n->rightChild);
        }
            // If code reaches here, we found the node. Now to remove it.
        else if (n->leftChild != nullptr && n->rightChild != nullptr) {
            // The node we want to remove has two children
            // Find the largest value from the left subtree
            n->value = findMax(n->leftChild);
            remove(n->value, n->leftChild);
        }
        else {
            // The node we want to remove has 0 or 1 child.
            // If it has a child, move it up. If not, set to nullptr.
            BinaryNode* oldNode = n;
            n = (n->leftChild != nullptr) ? n->leftChild : n->rightChild;
            delete oldNode;
            oldNode = nullptr;
        }
    }

public:
    // Default Constructor
    BinarySearchTree() {
        root = nullptr;
    }

    // Copy Constructor
    BinarySearchTree(const BinarySearchTree& b) {
        // calls private helper function
        root = copyNode(b.root);
    }

    // Destructor
    ~BinarySearchTree() {
        // calls private helper function
        destroy(root);
    }

    // Method to destroy tree
    void timber() {
        // calls private helper function
        destroy(root);
    }

    bool isEmpty() const {
        return (root == nullptr);
    }

    bool find(const Comparable& c, int &depth) const {
        // calls private helper function
        depth = 0;
        return find(c, root, depth);
    }

    void add(const Comparable& c) {
        // calls private helper function
        add(c, root);
    }

    void remove(const Comparable& c) {
        // calls private helper function
        remove(c, root);
    }

    // Overloaded = operator
    BinarySearchTree& operator = (const BinarySearchTree& rhs) {
        root = copyNode(rhs.root);
    }
};


#endif // BINARYSEARCHTREE_H