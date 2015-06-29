#include "..\\leftist_heap_bootstrapped\\leftist_heap_bootstrapped.h"
#include <algorithm>
#include <climits>

#ifndef _LHEAP_MERGE_BOOT_
#define _LHEAP_MERGE_BOOT_

struct LeftistHeapMergeBootIntNode {
	int min;
	LHeapBoot <LeftistHeapMergeBootIntNode> * subheap;

	LeftistHeapMergeBootIntNode(){
		subheap = nullptr;
	}

	LeftistHeapMergeBootIntNode(int _min, LHeapBoot <LeftistHeapMergeBootIntNode> * _subheap = nullptr){
		min = _min;
		subheap = _subheap;
		_subheap = nullptr;
	};
};

inline bool operator <(const LeftistHeapMergeBootIntNode &a, const LeftistHeapMergeBootIntNode &b){ 
	return a.min < b.min;
};

inline bool operator >(const LeftistHeapMergeBootIntNode &a, const LeftistHeapMergeBootIntNode &b){ 
	return a.min > b.min;
};


class LeftistHeapMergeBootInt {
	LeftistHeapMergeBootIntNode * root;

public:
	LeftistHeapMergeBootInt(){
		root = nullptr;
	}

	~LeftistHeapMergeBootInt(){
		clear();
	}

	void add(int _val){
		root = merge(root, new LeftistHeapMergeBootIntNode (_val, nullptr));	
	}

	void mergeWithHeap(LeftistHeapMergeBootInt & h){
		root = merge(root, h.root); //ok if arg would be null
		h.root = nullptr;
	}

	bool empty(){
		return root == nullptr;
	}

	int min (){		//undefined behavior if !root
		return root->min;
	}

	void pop(){		//undefined behavior if !root
		if(!root->subheap || root->subheap->empty()){
			if(root->subheap){
				delete root->subheap;
				root->subheap = nullptr;
			}
			delete root;
			root = nullptr;
			return;
		}
		LeftistHeapMergeBootIntNode new_min = root->subheap->min();
		root->min = new_min.min;
		root->subheap->pop();
		if(new_min.subheap) root->subheap->mergeWithHeap(*(new_min.subheap));
	}

	void clear() {
		if(root)
			clear(root, true);
		root = nullptr;
	}

private:
	LeftistHeapMergeBootIntNode * merge(LeftistHeapMergeBootIntNode * a, LeftistHeapMergeBootIntNode * b){
		if(!a || !b || a == b){
			if(a && !b) return a;
			if(a == b && a != 0) throw "attempt of self merge";
			return b;
		}		
		if(a->min > b->min)
			std::swap(a,b);
		if(a->subheap)
			a->subheap->add(*b);	//copied
		else{
			a->subheap = new LHeapBoot<LeftistHeapMergeBootIntNode>;
			a->subheap->add(*b);	//copied
		}
		if(b) delete b;
		return a;
	}

	void clear(LeftistHeapMergeBootIntNode * n, bool to_del){
		if(n->subheap) {
			if(!n->subheap->addition.empty()){
				for (auto nn : n->subheap->addition)
					clear(&nn, false);
				n->subheap->addition.clear();
			}
			if(n->subheap->root){
				clear(n->subheap->root);
				n->subheap->root = nullptr; //?
			}

			delete n->subheap;
			n->subheap = nullptr;
		}
		if(to_del)delete n;
	}

	void clear(LNode<LeftistHeapMergeBootIntNode>* n){
		clear(&n->val, false);
		if(n->L) clear(n->L);
		if(n->R) clear(n->R);
		delete n;
	}
};

#endif