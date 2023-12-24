#pragma once

#include "AVL_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Wordlist : public Wordlist_base
{
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height;
    };

    Node *root = nullptr;

public:

    //Default Constructor sets root to null
    Wordlist(){

        root = nullptr;
    }

    //Constructor which intakes a file and generates AVL tree using add_word
    Wordlist(const string &filename){

        root = nullptr;

        //Open file
        ifstream file;
        file.open(filename);

        string temp;

        //Use while loop to iterate through text
        while(file >> temp){

            add_word(temp);
        }
    }

    //Inherited from base class, counts appearance of a word
    int get_count(const string &w) const{

        //Uses helper function to return node containing word
        Node* temp = search_word(root, w);

        if(temp == nullptr){
            return 0;
        }

        else{

            return temp->count;
        }
    }

    //Inherited from base class, checks if a word is in the text
    bool contains(const string &w) const{

        //If the count of a word is more than 0, it is in the text
        return get_count(w) > 0;
    }

    //Inherited from base class, counts number of unique words
    int num_different_words() const{ 

        //Helper function returns different words
        return count_nodes(root);
    }

    //Inherited from base class, counts number of total words
    int total_words() const{

        //Helper function which sums all counts
        return sum_count(root);
    }

    //Inherited from base class, checks if a tree is sorted
    bool is_sorted() const{

        //Checks sorting by checking if tree is a BST
        return is_BST(root, nullptr, nullptr);
    }

    //Inherited from base class, finds most frequent word and count
    string most_frequent() const{

        //Calls helper to find node with largest count
        Node* max_node = nullptr;
        max_count(root, max_node);

        string number = to_string(max_node->count);
        string space = " ";

        return max_node->word + space + number;
    }

    //Inherited from base class, find number of words that appear once
    int num_singletons() const{
        
        int count = 0;

        //Uses helper to iterate through AVL tree
        singleton_count(root, count);

        return count;
    }

    //Inherited from base class, uses helper function
    void add_word(const string &w){

        //Will return new root with added word, or same root if balanced
        root = insert_node(root, w);
    }

    ///Inherited from base class, prints words in alphabetical order
    void print_words() const{

        //Starts count with 1 for displaying
        int count = 1; 

        //Helper which prints in order through AVL tree
        print_inOrder(root, count);
    }

    //Destructor for wordlist class
    ~Wordlist(){

        //Helper which deletes nodes bottom to top
        delete_tree(root);
    }

//Helper Function for Inherited Methods:

    //Helper function for add_word, adds word to AVL tree and returns root
    Node* insert_node(Node* root, string w){

        //If the root is empty, makes current word new root and returns node
        if(root == nullptr){

            return create_node(w);
        }

        //If not empty, checks if word is larger; moves down to left
        if(w < root->word){

            root->left = insert_node(root->left, w);
        }

        //If word is smaller, moves down the right
        else if(w > root->word){

            root->right = insert_node(root->right, w);
        }

        //If neither, then word is equal, so add to the count
        else{

            root->count++;
        }

        //Get balance of current node using helper function
        root->height = 1 + max(get_height(root->right), get_height(root->left));

        //Gets the difference between the two nodes children's heights
        int difference = balance_factor(root);

        //If tree is unbalanced from left side, and word is smaller than left child
        if(difference > 1 && w < root->left->word){

            return rotation_right(root);
        }
          
        //If tree is unbalanced from right side, and word is larger than right child
        if(difference < -1 && w > root->right->word){

            return rotation_left(root);
        }

        //If tree is unbalanced from left side, and word is larger than left child
        if(difference > 1 && w > root->left->word){

            root->left = rotation_left(root->left);
            return rotation_right(root);
        }

        //If tree is unbalanced from right side, and word is smaller than right child
        if(difference < -1 && w < root->right->word){

            root->right = rotation_right(root->right);
            return rotation_left(root);
        }

        //Return the new root, or old root if unchanged
        return root;
    }

    //Helper function used to rotate subtree left
    Node* rotation_left(Node* z){

        //set y as right child, and x as left grandchild
        Node* y = z->right;
        Node* x = y->left;
 
        //Switch nodes to rotate left
        y->left = z;
        z->right = x;
    
        //Change heights to new heights
        z->height = max(get_height(z->left), get_height(z->right)) + 1;
        y->height = max(get_height(y->left), get_height(y->right)) + 1;
    
        //Return new root of subtree
        return y;
    }

    //Helper function used to rotate subtree to the right
    Node* rotation_right(Node* z){

        //set y as left child, and x as right grandchild
        Node* y = z->left;
        Node* x = y->right;
 
        //Switch nodes to rotate right
        y->right = z;
        z->left = x;
    
        //Change heights to new heights
        z->height = max(get_height(z->left), get_height(z->right)) + 1;
        y->height = max(get_height(y->left), get_height(y->right)) + 1;
    
        //Return new root of subtree
        return y;
    }

    //Helper function used to get difference in height between siblings
    int balance_factor(Node* node){

        if(node == nullptr){

            return 0;
        }

        //Subtract height of right child from left child
        return (get_height(node->left) - get_height(node->right));
    }

    //Helper function return the height of a node
    int get_height(Node* node){

        if (node == NULL){
            
            return -1;
        }
            
        return node->height;
    }

    //Helper function that returns the node containing specific word
    Node* search_word(Node* node, const string &w) const{

        if(node == nullptr || root->word == w){

            return node;
        }

        if(w < node->word){

            return search_word(node->left, w);
        }
        
        else{

            return search_word(node->right, w);
        }
    }

    //Helper function that returns the number of nodes, which is number of words
    int count_nodes(Node* node) const{

        if(node == nullptr){

            return 0;
        }

        //Recursivley count all nodes in the AVL tree
        int number_left = count_nodes(node->left);
        int number_right = count_nodes(node->right);

        return (1 + number_left + number_right);
    }

    //Helper function which sums all counts in all nodex
    int sum_count(Node* node) const{

        if(node == nullptr){

            return 0;
        }

        //Recursively adds the counts of all unique words
        int sum_left = sum_count(node->left);
        int sum_right = sum_count(node->right);

        //Returns the total word count of text
        return node->count + sum_left + sum_right;
    }

    //Helper function used to check if a tree is a BST, should always return true
    bool is_BST(Node* node, Node* min_node, Node* max_node) const{

        if(node == nullptr){

            return true;
        }
           
        // Check if the current node's value is between the childrens
        if((min_node != nullptr && node->word <= min_node->word) ||
            (max_node != nullptr && node->word >= max_node->word)){

                return false;
            }

        //Recursively check the left and right sides of the node
        return is_BST(node->left, min_node, node) && is_BST(node->right, node, max_node);
    }

    //Helper sets the node with largest count through reference
    void max_count(Node* node, Node* &max_node) const{

        if (node == nullptr){
            
            return;
        }
        
        //Recurvsiely check all nodes to find max count
        max_count(node->left, max_node);

        if(max_node == nullptr || node->count > max_node->count){

            max_node = node;
        }
        
        max_count(node->right, max_node);
    }

    //Helper function sets total number of singletons through reference
    void singleton_count(Node* node, int &total) const{

        if (node == nullptr){
            
            return;
        }
        
        //Moves through AVL tree recurisvely
        singleton_count(node->left, total);

        //If the node's count is 1, add to singleton tally
        if(node->count == 1){

            total++;
        }
        
        singleton_count(node->right, total);
    }

    //Helper function creates a new node with a word
    Node* create_node(const string &w){

        Node* add = new Node;

        add->word = w;
        add->count = 1;
        add->left = nullptr;
        add->right = nullptr;
        add->height = 0;

        return add;
    }
    
    //Helper function that prints words in numbered and alphabetical order
    void print_inOrder(Node* node, int& count) const{

        if(node == nullptr){
            
            return;
        }

        //Recrusively goes to smallest value first, works its way up
        print_inOrder(node->left, count);

        cout << count << ". {"<<'"'<< node->word <<'"'<< ", " << node->count << "}"<< endl;
        count++;

        //Moves to right side after root
        print_inOrder(node->right, count);
    }

    //Helper function for destructor, starts at root
    void delete_tree(Node* node){

        if (node == nullptr){

            return;
        }
            
        //Recurvsely delets AVL tree bottom to top
        delete_tree(node->left);
        delete_tree(node->right);

        delete node;
    }
};