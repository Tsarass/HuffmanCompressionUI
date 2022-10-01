#include "BinaryTree.h"

Node::Node(int key, Node *nodel, Node *noder, bool dummy) {
	this->key = key;
	this->l = nodel;
	this->r = noder;
	if ((nodel) && (noder)) {
		this->hasChildren = true;
	}
	this->dummy = dummy;
}

Node* Tree::checkDuplicateNode(Node tocheck) {
	for (int i = 0; i < nnodes; i++) {
		if ((tocheck.key == nodes[i].key) && (nodes[i].dummy)) {
			return &nodes[i];
		}
	}
	return nullptr;
}

fbpair Tree::addNode(fbpair l, fbpair r) {
	Node *nodel=nullptr, *noder=nullptr;
	Node* dupl = nullptr;
	/*frequency parameters are -1 by default, if not they need
	to be turned to actual leaves*/
	if (l.freq > 0) {
		nodel = new Node(l.byte, nullptr, nullptr, false);
		dupl = checkDuplicateNode(*nodel);
		if (dupl) {
			nodel = dupl;
		}
		nodes[nnodes] = *nodel;
		nnodes++;
	} else {
		l.freq = 0;
	}

	if (r.freq > 0) {
		noder = new Node(r.byte, nullptr, nullptr, false);
		dupl = checkDuplicateNode(*noder);
		if (dupl) {
			noder = dupl;
		}
		nodes[nnodes] = *noder;
		nnodes++;
	} else {
		r.freq = 0;
	}
	
	//create master (dummy) node
	int dummyid = -nnodes;
	Node nodemaster (dummyid, nodel, noder, true);
	nodes[nnodes] = nodemaster;
	this->root = nodemaster;
	nnodes++;

	fbpair dummydat;
	dummydat.byte = dummyid;
	dummydat.freq = l.freq + r.freq;

	return dummydat;
}

Node* Tree::getRoot() {
	return &root;
}

int Tree::numnodes() {
	return this->nnodes;
}