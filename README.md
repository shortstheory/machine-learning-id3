# ID3, Reduced Error Pruing, and Random Forests - BITS F464 Assigment 2

## Introduction

There are several methods to classify data from a dataset. One notable method is to use decision trees which are recursively generated data structures based on the training data.

For this assignment, the task is to classify whether a given instance of a person's details can be used to deduce if they earn more or less than 50,000 USD per annum.

This project is a modern, C++11 implementation of a Decision Tree.

## Installation

This project has dependencies on the SQLite3 library and SQLiteCpp for interfacing SQL with C++ code. The project has been built with CMake. The libraries can be downloaded with:

```
sudo apt install libsqlite3-dev cmake
```

The SQLiteCpp must be built from source. Instructions for doing so can be found here: [https://github.com/SRombauts/SQLiteCpp/](https://github.com/SRombauts/SQLiteCpp/)

Once the library has been installed, clone or unzip the files to your favorite folder and run:

```
mkdir build
cd build
cmake ..
make -j4
```

## Code Base

The code depends on two main header files:

### DataEngine.h

The ID3 algorithm requires several lookups to find data satisfying a certain attribute to classify it accurately. The DataEngine header file encapsulates all of the common lookups required in the ID3 algorithm, such as getting the count of an instance satisfying certain properties and the list of distinct attributes of the dataset among many others.

The DataEngine works by using an instance of an SQLite3 database loaded in RAM. As the given database is only 5MB, this can be done without having to worry about running out of memory.

### DecisionTree.h

This header file contains the functions to generate a DecisionTree. The class encapsulates a structure called DecisionTreeNode which specifies the data contained in each node of the Decision Tree.

The struct definition of DecisionTreeNode is as follows:

```
enum NodeType {
    TerminalNode,
    AttributeNode,
    RootNode
};

struct DecisionTreeNode {
    std::vector<DecisionTreeNode*> children; // each node of the DecisionTreeNode has a vector of pointers to the next nodes in the tree
    NodeType type; // useful for letting us know whether we are at the "Top" (root) or "Bottom" (terminal) of the tree
    ItemPair attributePair; // attributes and values are stored as pairs, like <"outlook", "'sunny'">
};
```

Given a dataset, the DecisionTree first stores the data in its member DataEngine object. which in turns initialises the database in RAM. After this, the DecisionTree builds the tree starting from its member root node.

Using ```traverseTree(..)```, the list of the deduced rules is linearized and printed to standard output. This can be output redirected to a file.

This greatly speeds up testing the DecisionTree as training the DecisionTree can take several hours depending on the computational power of the target computer. However, reading a list of rules from the file and computing the DecisionTree can be done in a matter of seconds on a reasonably fast computer.

The DecisionTree class has been completely created from scratch and can handle an dataset with any number of attributes without any modifications in the code.

### test.cpp

This file is used for testing the performance of a given DecisionTree based on its Accuracy, Precision, F-Value, and Recall.

This works by taking a rule base, that is the list of deduced rules from a file and building a DecisionTree from the deduced rules. The first argument passed to the program is used as the path to the file containing the list of rules.

If the last argument if the constructor of the DecisionTree is set to ```false```, the tree is built from the rules defined in the rule base. If it is set to ```true```, the tree is built from training it from the training instances. This can be upto 100 times slower than just building the tree from the file.

The properties of the DecisionTree, such as the schema of the SQL database, the list of discrete and continuous attributes, and the path of the training and test data is specified in this file.

The pre-built ```rule_base``` file contains the list of the rules deduced from the standard ID3 algorithm.

### prune_rules.cpp

This file initialises the tree from the ```rule_base``` file which contains the rules deduced from the training of the Decision Tree.

The tree is then aggressively pruned, very heavily favouring nodes which improve the overall accuracy of the tree.

random_dataset
build_random_trees
rebuild_forest
libsqlite3-0