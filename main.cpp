/**
 * What a fabulous docblock!
 * Yay!
 */
#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "SplayTree.h"
#include <vector>
#include <string>
#include "Spotify.h"
#include "randomNumber.cpp"
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

    // Instantiate a binary search tree (of integer values) and insert the
    // numbers 1 through 100 in that order, then search for all numbers 1 through 100.
    BinarySearchTree<int> bstOne;
    for(int i = 1; i <= 100; i++){
        bstOne.add(i);
    }
    // Print in order
    std::cout << "Inserted in order\n" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    int depth;
    bool result;
    for (int i = 1; i <= 100; i++){
        result = bstOne.find(i, depth);
        std::cout << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
    }
    // testing
    result = bstOne.find( 0, depth);
    std::cout << "Searching for " << 0 << ", result: " << result << ", depth: " << depth << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    // Now instantiate a new BST and insert the numbers 1 through 100 in random order.
    // You may use https://www.random.org to generate a shuffled list of numbers 1 through 100,
    // or you can shuffle a vector of numbers 1 through 100 using C++’s shuffle method.
    vector<int> vec;
    for(int i; i <= 100; i++){
        vec.pushback(i);
    }
    random_shuffle(vec.begin(), vec.end());

    // Now search for each number from 1 through 100,
    // and record the depth of each find operation to a file.
    BinarySearchTree<int> bstTwo;
    for(int i = 0; i <= vec.size(); i++){
        bstTwo.add(vec[i]);
    }
    std::cout << "Inserted in Random Order\n" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    for (int i = 1; i <= 100; i++){
        result = bstTwo.find(i, depth);
        std::cout << "Searching for " << i << ", result: " << result << ", depth: " << depth << std::endl;
    }

    // Now instantiate a BST to hold objects of your custom data type.
    // Read your objects into a vector (as you have done in earlier projects) and then insert them into the BST.
    // Make sure you have at least 1000 objects in your BST.
    // Now search for each of your objects and record its depth in a file.

    std::ofstream outFile;
    outFile.open("../data/example_output.csv");
    for (int i = 999; i >= 0; --i) {
        outFile << i << std::endl;
    }
    outFile.close();

    BinarySearchTree<int> bst1;
    bst1.add(8);
    bst1.timber();

    return 0;
}