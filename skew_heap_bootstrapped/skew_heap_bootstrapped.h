#include <queue>
#include <algorithm>
#include <iostream>
#include <list>

#ifndef _SNODE_
#define _SNODE_
template <class T>
struct SNode {
	T val;
	SNode <T> * L;
	SNode <T> * R;

	SNode(T _val) { 
		val = _val; 
		L = R = 0;
	}
};
#endif


#ifndef _SHEAP_BOOT_
#define _SHEAP_BOOT_

template <class T>
class SHeapBoot {
	friend class SkewHeapMergeBootInt;
	SNode<T> * root;
	std::list<T> addition;

public:

	SHeapBoot() {
		root = 0;
	}

	template <class InputIterator>
	SHeapBoot(InputIterator first, InputIterator last) { 
		root = 0;
		build(first, last); 
	}

	~SHeapBoot() { 
		clear(); 
	}

	template <class InputIterator>
	void build(InputIterator first, InputIterator last) { // O(n)
		clear();
		std::queue<SNode<T> *> ptrs;

		while(first != last)
			ptrs.push(new SNode<T>(*first++));
		
		SNode<T> * a;
		SNode<T> * b;
		while(ptrs.size() > 1){
			a = ptrs.front();
			ptrs.pop();
			b = ptrs.front();
			ptrs.pop();
			ptrs.push(merge(a,b));
		}

		root = ptrs.front();
	}

	void mergeWithHeap(SHeapBoot<T>& h){
		addition.splice(addition.end(), h.addition);
		root = merge(root, h.root);
		h.root = 0;
	}

	void print() {
		mergeAddition();
		printSubtree(root,1);
	}

	bool checkMin(){
		mergeAddition();
		return checkMin(root);
	}

	void clear() {
		addition.clear();
		if(root)
			clear(root);
		root = nullptr;
	}

	void add (T val) {
		if(!root) 
			root = new SNode<T>(val);
		else 
			if(val < root->val){
				addition.push_back(root->val);
				root->val = val;
			}
			else 
				addition.push_back(val);
	}

	T min (){
		return root->val;
	}

	void pop(){
		if(!addition.empty())
			mergeAddition();
		SNode<T> * oldRoot = root;
		root = merge(oldRoot->L, oldRoot->R);
		delete oldRoot;
	}

	bool empty() {
		return root == nullptr;
	}


private:


	void clear(SNode<T> * n) {
		if(n->L) clear(n->L);
		if(n->R) clear(n->R);
		delete n;
	}

	SNode<T> * merge (SNode<T> * a, SNode<T> * b) {  // returns pointer to the head of merged heap
													 // if only one of nodes NOTNULL, returns it
//		if(!addition.empty())
//			mergeAddition();
		if(!a || !b || a == b){
			if(a && !b) return a;
			if(a == b && a != 0) throw "attempt of self merge";
			return b;
		}
		if(a->val > b->val)
			std::swap(a, b);
		if(!a->R)
			a->R = b;
		else 
			a->R = merge (a->R, b);
		std::swap(a->R, a->L);
		return a;
	}

	void mergeAddition(){
		SHeapBoot<T> h(addition.begin(), addition.end());
		addition.clear();
		root = merge(root, h.root);
		h.root = 0;
	}

	void printSubtree(SNode<T>* n, int level) {
		if(!n)
			std::cout << std::string(level, ' ') << "-" << std::endl;
		else{
			printSubtree(n->R, level+1);
			std::cout << std::string(level, ' ') << (n? n->val : 0) << std::endl;
			printSubtree(n->L, level+1);
		}
	}

	bool checkMin(SNode<T>* n){
		if(!n) throw "NullPointerException";
		return (n->L ? (n->val <= n->L->val && checkMin(n->L)) : true) &&
				(n->R ? (n->val <= n->R->val && checkMin(n->R)) : true);
	}


};

#endif