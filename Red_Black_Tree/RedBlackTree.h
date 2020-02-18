#pragma once
/*	RED - BLACK TREE PROPERTIES
1. A node is either red or black
2. The root is black
3. All the leaves (NIL) are black.
4. if a node is red, then its children are black
5. All paths from a node to its NIL descendants contain the same number of black nodes.
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#define INDENT_STEP  6
using namespace std;

enum Color {RED, BLACK};

//struct for a red black tree node
struct node
{
	enum Color color;
	int key;
	//left child, right child, and parent node
	node *left, *right, *parent;
};

struct rbtree
{
	node *root;
};

class RedBlackTree
{
public:
	rbtree* createRBTree();
	node* newNode(int key, Color c, node *left, node *right);
	Color node_color(node *n);

	//Return Sibling of Node
	node* sibling(node *n);
	//Return Grandparent of Node
	node* grandparent(node *n);
	/*
	The function to insert a node to the tree
	1. 	Adds a single data item to the tree as a regular binary tree. If there is already an item 
	in the tree that is the same with the item being inserted, it is overwritten by the new item.
	2. Recolor and rotate nodes to fix violation (in other functions)
	** The reason to always add a red node because it might violate the
	properties 1. and 4., but these properties are easier to be fixed than the others.
	*/
	void insert(rbtree *t, int key);

	/*
	Case 1: add the first node (root is black)
	*/
	void insert_case1(rbtree *t, node *n);
	/*
	Case 2: there is no violation if the inserted node's parent is BLACK
	*/
	void insert_case2(rbtree *t, node *n);

	//Correct double red problem for case 3,4,5

	/*
	Case 3: Recolor, and move up to see if more work needed
	*/
	void insert_case3(rbtree *t, node *n);
	/*
	Restructure for a parent who is the left child of the grandparent.
	This will require a single right rotation if n is also a left child,
	or a left-right rotation otherwise.
	*/
	void insert_case4(rbtree *t, node *n);
	/*
	Restructure for a parent who is the right child of the grandparent.
	This will require a single left rotation if n is also a right child,
	or a right-left rotation otherwise.
	*/
	void insert_case5(rbtree *t, node *n);

	void rotate_right(rbtree *t, node *n);
	void rotate_left(rbtree *t, node *n);
	void replaceNode(rbtree *t, node *oldn, node *newn);
	void verify_properties(rbtree *t);

	//Property 1. A node is either RED or BLACK
	void verify_property_1(node *n);
	//Property 2. The root is always BLACK
	void verify_property_2(node *root);
	/*
	Property 4. if a node is red, then its children are black
	(or double red problem)
	*/
	void verify_property_4(node *n);
	//Property 5. All paths from a node to its NIL descendants contain the same number of black nodes.
	void verify_property_5(node *n);
	//Function to support for verify_property_5 function
	void verify_property_5_SP(node *n, int count, int* black_count);

	//Look up through Node
	node* search(rbtree *t, int key);

	/*
	Returns Maximum node(the most right node)
	*/
	node* maximum_node(node *n);

	/**
	Removes the node containning the given key.
	Does nothing if there is no such node
	*/
	void deleteNode(rbtree *t, int key);

	/*
	Case 1: Nothing to delete when removing a root means we emptied the tree
	*/
	void delete_case1(rbtree *t, node *n);
	/*
	Case 2: The node to be deleted is BLACK, has a BLACK child, and a RED sibling
	*/
	void delete_case2(rbtree *t, node *n);
	/*
	Case 3: The node to be deleted is BLACK, has a BLACK parent,
	a BLACK sibling with 2 BLACK children.
	*/
	void delete_case3(rbtree *t, node *n);
	/*
	Case 4: The node to be deleted is BLACK, has a RED parent,
	a BLACK sibling with 2 BLACK children.
	*/
	void delete_case4(rbtree *t, node *n);
	/*
	Case 5: The node to be deleted is BLACK, has a BLACK sibling 
	with 1 inner RED child.
	*/
	void delete_case5(rbtree *t, node *n);
	/*
	Case 6: The node to be deleted is BLACK, has a "no matter color" parent,
	and a BLACK sibling with 1 outer RED child.
	*/
	void delete_case6(rbtree *t, node *n);

	/*
	Print the RED BLACK tree as HORIZONTAL direction
	*/
	void printTreeSP(node *n, int indent);
	void printTree(rbtree *t);

	RedBlackTree();
	~RedBlackTree();
};

