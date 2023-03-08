/**
 * What a fabulous docblock!
 * Yay!
 */
#include <iostream>
#include <algorithm>
#include <random>
#include "AVLTree.h"
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
    std::ofstream outFile("../data/BSTdata.txt");
    outFile.open("../data/BSTdata.txt");
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
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // Now search for each number from 1 through 100,
        // and record the depth of each find operation to a file.
        BinarySearchTree<int> bstTwo;
        for(int i = 0; i <= vec.size(); i++){
            bstTwo.add(vec[i]);
        }
        outFile << "Inserted in Random Order\n" << std::endl;
        outFile << std::string(40, '-') << std::endl;
        for (int i = 1; i <= 100; i++){
            result = bstTwo.find(i, depth);
            outFile << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
        }
        // Searching for 0
        bst1.find(0, depth);
        outFile << "depth: " << depth << std::endl;
        depth = 0;
        bst1.find(101, depth);
        outFile << "depth: " << depth << std::endl;

        bst1.timber();
        bstTwo.timber();
        outFile.close();
    } else {
        outFile << "Unable to open output file!" << std::endl;
        return 1;
    }
    return 0;
}