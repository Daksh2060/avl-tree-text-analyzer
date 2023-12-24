# AVL Tree Text Analyzer

This C++ program is a simple text file analyzer, utilizing a self-balancing AVL tree to store and extract information from text. The program takes a text file and produces useful information such as the counts of each unique word, the total word count, the most common word, etc. By utilizing a self-balancing AVL Tree, the program is able to scan large text files fast and efficiently when compared to more common data structures such as linked lists or arrays.

## Features

- **Self-Balancing AVL Tree:** The program scans through the text file and creates a node for every unique word, holding both the word, and the number of times it is used in the text. This node is then added to a self-balancing AVL Tree, which applies height-balancing to the tree every time a node is added.

- **Text Word Count:** By storing individual word counts in each node, the program can keep track of the total word count, the number of unique words, and the appearance count of each unique word.

- **Extra-Information:** The program can scan the AVL Tree to get extra pieces of information, such as the number of singleton words (unique words that only appear once in the text) and the single most repeated word in the text

## How does it work?


## Installation and Use

1. Clone the repository to your local machine:

   ```bash
   git clone 
   ```

2. Use the provided makefile to compile:

   ```bash
   make
   ```

