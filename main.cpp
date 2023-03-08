/**
 * What a fabulous docblock!
 * Yay!
 */
#include <iostream>
#include <algorithm>
#include <random>
#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SplayTree.h"
#include <vector>
#include <string>
#include "Spotify.h"
#include <fstream>

int main() {
    // Example of writing out to a file
    std::vector<Spotify> songs;
    std::string filename = "../spotifysongs.csv";
    if (loadFromFile(filename, songs)) {
        std::cout << songs.size()
                  << " records read from file" << std::endl;
        int firstId = songs.front().getPosition();
        std::cout << "The last row ID read was " << firstId << std::endl;
        int lastId = songs.back().getPosition();
        std::cout << "The last row ID read was " << lastId << std::endl;
    } else {
        std::cout << "Something went wrong." << std::endl;
    }

    // Now instantiate a BST to hold objects of your custom data type.
    // Read your objects into a vector (as you have done in earlier projects) and then insert them into the BST.
    // Make sure you have at least 1000 objects in your BST.
    // Now search for each of your objects and record its depth in a file.
    BinarySearchTree<int> bst1;
    BinarySearchTree<int> bstTwo;
    std::ofstream outFile;
    outFile.open("../data/bstData.txt");
    if (outFile.is_open()) {
        // Instantiate a binary search tree (of integer values) and insert the
        // numbers 1 through 100 in that order, then search for all numbers 1 through 100.
        for (int i = 1; i <= 100; i++) {
            bst1.add(i);
        }
        // Print out in order
        outFile << "Inserted in order\n" << std::endl;
        outFile << std::string(40, '-') << std::endl;
        int depth = 0;
        bool result;
        for (int i = 1; i <= 100; i++){
            result = bst1.find(i, depth);
            outFile << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
        }
        // Print shuffled
        // Now instantiate a new BST and insert the numbers 1 through 100 in random order.
        std::random_device rd;
        std::vector<int> vec;
        for(int i = 1; i <= 100; i++){
            vec.push_back(i);
        }
        // Requires std::random_device rd; from above ^^^
        std::shuffle(vec.begin(), vec.end(), rd);

        // Prove that it's shuffled
        for (int& n : vec) {
            outFile << n << " ";
        }
        outFile << std::endl;

        // Now search for each number from 1 through 100,
        // and record the depth of each find operation to a file.
        BinarySearchTree<int> bstTwo;
        for(int i = 0; i <= vec.size(); i++){
            bstTwo.add(vec[i]);
        }
        outFile << "Inserted in Random Order\n" << std::endl;
        outFile << std::string(40, '-') << std::endl;
        for (int i = 1; i <= 100; i++){
            depth = 0;
            result = bstTwo.find(i, depth);
            outFile << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
        }
        // Searching for 0
        bst1.find(0, depth);
        outFile << "depth: " << depth << std::endl;
        depth = 0;
        bst1.find(101, depth);
        outFile << "depth: " << depth << std::endl;

        outFile.close();
    } else {
        outFile << "Unable to open output file!" << std::endl;
        return 1;
    }

    // AVL Tree
    AvlTree<int> avl1;
    AvlTree<int> avlTwo;
    std::ofstream outFileTwo;
    outFileTwo.open("../data/avlData.txt");
    if (outFileTwo.is_open()) {
        // Instantiate a binary search tree (of integer values) and insert the
        // numbers 1 through 100 in that order, then search for all numbers 1 through 100.
        for (int i = 1; i <= 100; i++) {
            avl1.add(i);
        }
        // Print out in order
        outFileTwo << "Inserted in order\n" << std::endl;
        outFileTwo << std::string(40, '-') << std::endl;
        int depth = 0;
        bool result;
        for (int i = 1; i <= 100; i++){
            result = avl1.find(i, depth);
            outFileTwo << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
        }
        // Print shuffled
        // Now instantiate a new BST and insert the numbers 1 through 100 in random order.
        std::random_device rd;
        std::vector<int> vec;
        for(int i = 1; i <= 100; i++){
            vec.push_back(i);
        }
        // Requires std::random_device rd; from above ^^^
        std::shuffle(vec.begin(), vec.end(), rd);

        // Prove that it's shuffled
        for (int& n : vec) {
            outFileTwo << n << " ";
        }
        outFileTwo << std::endl;

        // Now search for each number from 1 through 100,
        // and record the depth of each find operation to a file.
        for(int i = 0; i <= vec.size(); i++){
            avlTwo.add(vec[i]);
        }
        outFileTwo << "Inserted in Random Order\n" << std::endl;
        outFileTwo << std::string(40, '-') << std::endl;
        for (int i = 1; i <= 100; i++){
            depth = 0;
            result = avlTwo.find(i, depth);
            outFileTwo << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
        }
        // Searching for 0
        avl1.find(0, depth);
        outFileTwo << "depth: " << depth << std::endl;
        depth = 0;
        avl1.find(101, depth);
        outFileTwo << "depth: " << depth << std::endl;

        outFileTwo.close();
    } else {
        outFileTwo << "Unable to open output file!" << std::endl;
        return 1;
    }

    // Splay Tree
    SplayTree<int> spt1;
    SplayTree<int> sptTwo;
    std::ofstream outFile3;
    outFile3.open("../data/SplayData.txt");
    if (outFile3.is_open()) {
        // Instantiate a binary search tree (of integer values) and insert the
        // numbers 1 through 100 in that order, then search for all numbers 1 through 100.
        for (int i = 1; i <= 100; i++) {
            spt1.add(i);
        }
        // Print out in order
        outFile3 << "Inserted in order\n" << std::endl;
        outFile3 << std::string(40, '-') << std::endl;
        int depth = 0;
        bool result;
        for (int i = 1; i <= 100; i++){
            result = spt1.find(i, depth);
            outFile << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
        }
        // Print shuffled
        // Now instantiate a new BST and insert the numbers 1 through 100 in random order.
        std::random_device rd;
        std::vector<int> vec;
        for(int i = 1; i <= 100; i++){
            vec.push_back(i);
        }
        // Requires std::random_device rd; from above ^^^
        std::shuffle(vec.begin(), vec.end(), rd);

        // Prove that it's shuffled
        for (int& n : vec) {
            outFile3 << n << " ";
        }
        outFile3 << std::endl;

        for(int i = 0; i <= vec.size(); i++){
            sptTwo.add(vec[i]);
        }

        outFile3 << "Inserted in Random Order\n" << std::endl;
        outFile3 << std::string(40, '-') << std::endl;
        for (int i = 1; i <= 100; i++){
            depth = 0;
            result = sptTwo.find(i, depth);
            outFile3 << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
        }
        // Searching for 0
        spt1.find(0, depth);
        outFile3 << "depth: " << depth << std::endl;
        depth = 0;
        spt1.find(101, depth);
        outFile3 << "depth: " << depth << std::endl;

        outFile3.close();
    } else {
        outFile3 << "Unable to open output file!" << std::endl;
        return 1;
    }
    return 0;
}