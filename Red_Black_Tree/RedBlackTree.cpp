#include "stdafx.h"
#include "RedBlackTree.h"


RedBlackTree::RedBlackTree()
{
}


RedBlackTree::~RedBlackTree()
{
}
rbtree* RedBlackTree::createRBTree()
{
	rbtree *t = new rbtree;
	t->root = NULL;
	verify_properties(t);
	return t;
}
node* RedBlackTree::newNode(int key, Color c, node *left, node *right)
{
	node *result = new node;
	
	result->key = key;
	result->color = c;
	result->left = left;
	result->right = right;
	if (left != NULL)
		left->parent = result;
	if (right != NULL)
		right->parent = result;
	result->parent = NULL;
	return result;
}

Color RedBlackTree::node_color(node *n)
{
	return n == NULL ? BLACK : n->color;
}

node* RedBlackTree::sibling(node *n)
{
	assert(n != NULL);
	assert(n->parent != NULL);
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

node* RedBlackTree::grandparent(node *n)
{
	assert(n != NULL);
	assert(n->parent != NULL);
	assert(n->parent->parent != NULL);
	return n->parent->parent;
}

void RedBlackTree::verify_properties(rbtree *t)
{
	verify_property_1(t->root);
	verify_property_2(t->root);
	verify_property_4(t->root);
	verify_property_5(t->root);
}

void RedBlackTree::verify_property_1(node *n)
{
	assert(node_color(n) == RED || node_color(n) == BLACK);
	if (n == NULL)
		return;
	verify_property_1(n->left);
	verify_property_1(n->right);
}

void RedBlackTree::verify_property_2(node *root)
{
	assert(node_color(root) == BLACK);
}

void RedBlackTree::verify_property_4(node *n)
{
	if (node_color(n) == RED)
	{
		assert(node_color(n->left) == BLACK);
		assert(node_color(n->right) == BLACK);
		assert(node_color(n->parent) == BLACK);
	}
	if (n == NULL) return;

	verify_property_4(n->left);
	verify_property_4(n->right);
}

void RedBlackTree::verify_property_5(node *n)
{
	int black_count_path = -1;
	verify_property_5_SP(n, 0, &black_count_path);
}

void RedBlackTree::verify_property_5_SP(node *n, int count, int* black_count)
{
	if (node_color(n) == BLACK)
	{
		count++;
	}
	if (n == NULL)
	{
		if (*black_count == -1)
		{
			*black_count = count;
		}
		else
		{
			assert(count == *black_count);
		}
		return;
	}
	verify_property_5_SP(n->left, count, black_count);
	verify_property_5_SP(n->right, count, black_count);
}


void RedBlackTree::insert(rbtree *t, int key)
{
	node *insertedNode = newNode(key, RED, NULL, NULL);
	if (t->root == NULL) {
		t->root = insertedNode;
	}
	else
	{
		node *n = t->root;
		while (true)
		{
			if (key == n->key) {
				n->key = key;
				return;
			}
			else if (key < n->key)
			{
				if (n->left == NULL) {
					n->left = insertedNode;
					break;
				}
				else {
					n = n->left;
				}
			}
			else
			{
				 assert(key > n->key);
				if (n->right == NULL){
					n->right = insertedNode;
					break;
				}
				else {
					n = n->right;
				}
			}
		}
		insertedNode->parent = n;
	}
	insert_case1(t, insertedNode);
	verify_properties(t);
}

void RedBlackTree::insert_case1(rbtree *t, node *n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(t, n);
}

void RedBlackTree::insert_case2(rbtree *t, node *n)
{
	if (node_color(n->parent) == BLACK)
		return;
	else
		insert_case3(t, n);
}

void RedBlackTree::insert_case3(rbtree *t, node *n)
{
	if (node_color(sibling(n->parent)) == RED) //sibling of parent is uncle
	{
		n->parent->color = BLACK;
		sibling(n->parent)->color = BLACK;
		grandparent(n)->color = RED;
		insert_case1(t, grandparent(n));
	}
	else
	{
		insert_case4(t, n);
	}
}

void RedBlackTree::insert_case4(rbtree *t, node *n)
{
	if (n == n->parent->right && n->parent == grandparent(n)->left)
	{
		rotate_left(t, n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == grandparent(n)->right)
	{
		rotate_right(t, n->parent);
		n = n->right;
	}
	insert_case5(t, n);
}

void RedBlackTree::insert_case5(rbtree *t, node *n)
{
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if (n == n->parent->left && n->parent == grandparent(n)->left)
	{
		rotate_right(t, grandparent(n));
	}
	else
	{
		assert(n == n->parent->right && n->parent == grandparent(n)->right);
		rotate_left(t, grandparent(n));
	}
}
/* 
					N							R
				  	  \						  /   \	
					   R(RED)	=>			N	   T
					    \
						 T (RED)

*/
void RedBlackTree::rotate_left(rbtree *t, node *n)
{
	node *r = n->right;
	replaceNode(t, n, r);	//swap node n and node r
	n->right = r->left;
	if (r->left != NULL)	//check if there is a sub tree in r node
	{
		r->left->parent = n;// get n as the parent of the sub tree
	}
	r->left = n;
	n->parent = r;
}

/*
							N					L
						  /					  /   \
					L(RED)			=>	  	 T     N
					/
				T (RED)

*/
void RedBlackTree::rotate_right(rbtree *t, node *n)
{
	node *L = n->left;
	replaceNode(t, n, L);
	n->left = L->right;
	if (L->right != NULL)
	{
		L->right->parent = n;
	}
	L->right = n;
	n->parent = L;
}
void RedBlackTree::replaceNode(rbtree *t, node *oldn, node *newn)
{
	if (oldn->parent == NULL)
	{
		t->root = newn;
	}
	else
	{
		if (oldn == oldn->parent->left)		//if oldn is a left child node
			oldn->parent->left = newn;
		else                                //else oldn is a right child node
			oldn->parent->right = newn;
	}
	if (newn != NULL)
	{
		newn->parent = oldn->parent;
	}
}

node* RedBlackTree::search(rbtree *t, int key)
{
	node *n = t->root;
	while (n != NULL)
	{
		if (key == n->key)
		{
			return n;
		}
		else if (key < n->key)
		{
			n = n->left;
		}
		else
		{
			assert(key > n->key);
			n = n->right;
		}
	}
	return n;
}

node* RedBlackTree::maximum_node(node *n)
{
	assert(n != NULL);
	while (n->right != NULL)
	{
		n = n->right;
	}
	return n;
}

void RedBlackTree::deleteNode(rbtree *t, int key)
{
	node *child;
	node *n = search(t, key);
	if (n == NULL)
		// No such node, do nothing.
		return;
	if (n->left != NULL && n->right != NULL)
	{
		// Node has two children, coppy predecessor key in.
		node *pred = maximum_node(n->left);
		n->key = pred->key;
		n = pred;
	}
	// At this point node has zero or one child
	assert(n->left == NULL || n->right == NULL);
	child = n->right == NULL ? n->left : n->right;
	// Double black case, move to fix tree functions 
	// after deleting a node (delete_case functions)
	if (node_color(n) == BLACK)
	{
		n->color = node_color(child);
		delete_case1(t, n);
	}
	replaceNode(t, n, child);
	free(n);
	verify_properties(t);
}

void RedBlackTree::delete_case1(rbtree *t, node *n)
{
	if (n->parent == NULL)
		return;
	else
		delete_case2(t, n);
}

void RedBlackTree::delete_case2(rbtree *t, node *n)
{
	if (node_color(sibling(n)) == RED)
	{
		n->parent->color = RED;
		sibling(n)->color = BLACK;
		if (n == n->parent->left)
			rotate_left(t, n->parent);
		else
			rotate_right(t, n->parent);
	}
	delete_case3(t, n);
}

void RedBlackTree::delete_case3(rbtree *t, node *n)
{
	if (node_color(n->parent) == BLACK && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		delete_case1(t, n->parent);
	}
	else
		delete_case4(t, n);
}

void RedBlackTree::delete_case4(rbtree *t, node *n)
{
	if (node_color(n->parent) == RED && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		n->parent->color = BLACK;
	}
	else
		delete_case5(t, n);
}

void RedBlackTree::delete_case5(rbtree *t, node *n)
{
	if (n == n->parent->left && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == RED && node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->left->color = BLACK;
		rotate_right(t, sibling(n));
	}
	else if (n == n->parent->right && node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->right) == RED && node_color(sibling(n)->left) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->right->color = BLACK;
		rotate_left(t, sibling(n));
	}
	delete_case6(t, n);
}

void RedBlackTree::delete_case6(rbtree *t, node *n)
{
	sibling(n)->color = node_color(n->parent);
	n->parent->color = BLACK;
	if (n == n->parent->left)
	{
		assert(node_color(sibling(n)->right) == RED);
		sibling(n)->right->color = BLACK;
		rotate_left(t, n->parent);
	}
	else
	{
		assert(node_color(sibling(n)->left) == RED);
		sibling(n)->left->color = BLACK;
		rotate_right(t, n->parent);
	}
}

void RedBlackTree::printTreeSP(node *n, int indent)
{
	int i;
	if (n == NULL)
	{
		fputs("<empty tree>", stdout);
		return;
	}
	if (n->right != NULL)
	{
		printTreeSP(n->right, indent + INDENT_STEP);
	}
	for (i = 0; i < indent; i++)
		fputs(" ", stdout);
	if (n->color == BLACK)
		cout << (int)n->key << endl;
	else
		cout << "<" << (int)n->key << ">" << endl;
	if (n->left != NULL)
	{
		printTreeSP(n->left, indent + INDENT_STEP);
	}
}

void RedBlackTree::printTree(rbtree *t)
{
	printTreeSP(t->root, 0);
	puts("");
}
