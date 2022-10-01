#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H


class Node {
public:
	Node *l;
	Node *r;
	bool hasChildren = false;
	int key;
	bool dummy = false;
	Node() {};
	Node(int key, Node *nodel = nullptr, Node *noder = nullptr, bool dummy=false);
};

struct fbpair {
	int freq;
	int byte;
	bool operator<(fbpair const &a) {
		return freq > a.freq;	//hack with > instead of < to sort in descending order
	}
};

class Tree {
	Node root;
	Node nodes[1024];	//1024 is more than will ever be needed
	int nnodes = 0;
	Node* checkDuplicateNode(Node tocheck);
public:
	Tree() {};
	fbpair addNode(fbpair l, fbpair r);
	Node* getRoot();
	int numnodes();
};

#endif