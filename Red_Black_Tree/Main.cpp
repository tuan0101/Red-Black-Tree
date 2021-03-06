// Red_Black_Tree.cpp : Defines the entry point for the console application.
// Created by <Tuan Pham> on <4/10/2019>

#include "stdafx.h"
#include "RedBlackTree.h"

//Find a node then print the result
void findNode(RedBlackTree RBTree, rbtree *t, int y)
{
	node *n = RBTree.search(t, y);
	if (n != NULL) {
		cout << "Find the node " << y << " successfully.\n";
	}
	else {
		cout << "Could not find the node " << y << " in the tree.\n\n";
	}
}

int main()
{
	RedBlackTree RBTree;
	rbtree *t = RBTree.createRBTree();

	int arrayNode[10];
	// Generate 10 random number and add to arrayNode[]
	cout << "Print the array: ";
	for (int i = 0; i < 10; i++)
	{
		int x = rand() % 30;
		arrayNode[i] = x;
		cout << x << " ";
	}

	cout << "\n\nBuild a RED BLACK tree by the array\n";
	RBTree.printTree(t);
	for (int i = 0; i < 10; i++)
	{
		cout << "Inserting " << arrayNode[i] << endl << endl;
		RBTree.insert(t, arrayNode[i]);
		RBTree.printTree(t);
	}

	//Test to find a node inside the array
	int y = rand() % 10; //get the index from 0 to 9
	findNode(RBTree, t, arrayNode[y]);
	//Test to find a node outside the array
	findNode(RBTree, t,31);

	// Delete 5 random nodes from the array
	for (int i = 0; i < 5; i++)
	{
		int x = rand() % 10;
		cout << "Deleting " << arrayNode[x] << endl << endl;
		RBTree.deleteNode(t, arrayNode[i]);
		RBTree.printTree(t);
	}

	system("pause");
    return 0;
}



