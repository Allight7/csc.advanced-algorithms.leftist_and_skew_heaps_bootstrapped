#include "..\\skew_heap_bootstrapped\\skew_heap_bootstrapped.h"
#include <algorithm>
#include <climits>

struct SkewHeapMergeBootIntNode {
	int min;
	SHeapBoot <SkewHeapMergeBootIntNode> * subheap;

	SkewHeapMergeBootIntNode(){
		subheap = nullptr;
	}

	SkewHeapMergeBootIntNode(int _min, SHeapBoot <SkewHeapMergeBootIntNode> * _subheap = nullptr){
		min = _min;
		subheap = _subheap;
		_subheap = nullptr;
	};
};

inline bool operator <(const SkewHeapMergeBootIntNode &a, const SkewHeapMergeBootIntNode &b){ 
	return a.min < b.min;
};

inline bool operator >(const SkewHeapMergeBootIntNode &a, const SkewHeapMergeBootIntNode &b){ 
	return a.min > b.min;
};


class SkewHeapMergeBootInt {
	SkewHeapMergeBootIntNode * root;

public:
	SkewHeapMergeBootInt(){
		root = nullptr;
	}

	~SkewHeapMergeBootInt(){
		clear();
	}

	void add(int _val){
		root = merge(root, new SkewHeapMergeBootIntNode (_val, nullptr));	
	}

	void mergeWithHeap(SkewHeapMergeBootInt & h){
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
		SkewHeapMergeBootIntNode new_min = root->subheap->min();
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
	SkewHeapMergeBootIntNode * merge(SkewHeapMergeBootIntNode * a, SkewHeapMergeBootIntNode * b){
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
			a->subheap = new SHeapBoot<SkewHeapMergeBootIntNode>;
			a->subheap->add(*b);	//copied
		}
		if(b) delete b;
		return a;
	}

	void clear(SkewHeapMergeBootIntNode * n, bool to_del){
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

	void clear(SNode<SkewHeapMergeBootIntNode>* n){
		clear(&n->val, false);
		if(n->L) clear(n->L);
		if(n->R) clear(n->R);
		delete n;
	}
};



