#include <queue>
#include <algorithm>
#include <iostream>
#include <list>

#ifndef _LNODE_
#define _LNODE_
template <class T>
struct LNode {
	int d;
	T val;
	LNode <T> * L;
	LNode <T> * R;

	LNode(T _val) { 
		d = 1; 
		val = _val; 
		L = R = 0;
	}
};
#endif

#ifndef _LHEAP_BOOT_
#define _LHEAP_BOOT_

template <class T>
class LHeapBoot {
	friend class LeftistHeapMergeBootInt;
	LNode<T> * root;
	std::list<T> addition;
	
public:
	LHeapBoot() {
		root = 0;
	}

	template <class InputIterator>
	LHeapBoot(InputIterator first, InputIterator last) { 
		root = 0;
		build(first, last); 
	}

	~LHeapBoot() { 
		clear(); 
	}

	template <class InputIterator>
	void build(InputIterator first, InputIterator last) { // O(n)
		clear();
		std::queue<LNode<T> *> ptrs;

		while(first != last)
			ptrs.push(new LNode<T>(*first++));
		
		LNode<T> * a;
		LNode<T> * b;
		while(ptrs.size() > 1){
			a = ptrs.front();
			ptrs.pop();
			b = ptrs.front();
			ptrs.pop();
			ptrs.push(merge(a,b));
		}

		root = ptrs.front();
	}

	void mergeWithHeap(LHeapBoot<T>& h){
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
			root = new LNode<T>(val);
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
		LNode<T> * oldRoot = root;
		root = merge(oldRoot->L, oldRoot->R);
		delete oldRoot;
	}

	bool empty() {
		return root == nullptr;
	}


private:

	void clear(LNode<T> * n) {
		if(n->L) clear(n->L);
		if(n->R) clear(n->R);
		delete n;
	}

	LNode<T> * merge (LNode<T> * a, LNode<T> * b) {  // returns pointer to the head of merged heap
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
		if(!a->L || a->R->d > a->L->d)
			std::swap(a->R, a->L);
		a->d = a->R ? a->R->d + 1 : 1;
		return a;
	}

	void mergeAddition(){
		LHeapBoot<T> h(addition.begin(), addition.end());
		addition.clear();
		root = merge(root, h.root);
		h.root = 0;
	}

	void printSubtree(LNode<T>* n, int level) {
		if(!n)
			std::cout << std::string(level, ' ') << "-:" << (n? n->d : 0) << std::endl;
		else{
			printSubtree(n->R, level+1);
			std::cout << std::string(level, ' ') << (n? n->val : 0) << ':' << (n? n->d : 0) << std::endl;
			printSubtree(n->L, level+1);
		}
	}

	bool checkMin(LNode<T>* n){
		if(!n) throw "NullPointerException";
		return (n->L ? (n->val <= n->L->val && checkMin(n->L)) : true) &&
				(n->R ? (n->val <= n->R->val && checkMin(n->R)) : true);
	}


};

#endif