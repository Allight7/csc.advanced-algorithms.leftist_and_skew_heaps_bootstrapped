#include <vector>
#include <algorithm>
#include <iostream>
#include <list>


template <class T>
struct SNode {
	T val;
	SNode <T> * L;
	SNode <T> * R;

	SNode() {
		L = R = 0;
	}
	SNode(T _val) { 
		val = _val; 
		L = R = 0;
	}
};

template <class T, const T INF>
class SHeapBoot {
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
		clear();							//не очень элегантно, но хотелось обойтись без добавления в каждый узел инфы о его связях с родителем.	
		std::vector<SNode<T> *> ptrs;

		while(first != last)
			ptrs.push_back(new SNode<T>(*first++));
		int size = ptrs.size();
		ptrs.resize(size+1);
		
		
		for(int i = size/2; i >= 0; i--){
			int j = i;
			while (j < size && ptrs[j]) {
				int m = j, l = 2 * j + 1, r = l + 1;
				if (l <= size && ptrs[l] && ptrs[l]->val < ptrs[m]->val) m = l;
				if (r <= size && ptrs[r] && ptrs[r]->val < ptrs[m]->val) m = r;
				if (m == j)
					break;
				std::swap(ptrs[m], ptrs[j]);
				j = m;
			}
		}

		root = ptrs[0];
		for(int i = 0; i < size/2; ++i){
			ptrs[i]->L = ptrs[2*i+1];
			ptrs[i]->R = ptrs[2*i+2];
		}
	}

	void clear() {
		addition.clear();
		if(root)
			clear(root);
	}

	void mergeWithHeap(SHeapBoot<T,INF>& h){
		addition.splice(addition.end(), h.addition);
		root = merge(root, h.root);
		h.root = 0;
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
		return root ? root->val : INF;
	}

	T extractMin (){
		if(!root)
			return INF;
		if(!addition.empty())
			mergeAddition();
		T oldMin = root->val;
		SNode<T> * oldRoot = root;
		root = merge(oldRoot->L, oldRoot->R);
		delete oldRoot;
		return oldMin;
	}

	void print() {
		printSubtree(root,1);
	}

	bool checkMin(){
		return checkMin(root);
	}

private:

// --------------------------------------------------------------------------------

	SNode<T> * merge (SNode<T> * a, SNode<T> * b) {  // returns pointer to the head of merged heap
													 // if only one of nodes NOTNULL, returns it
//		if(!addition.empty())
//			mergeAddition();
		if(!a || !b || a == b){
			if(a && !b) return a;
			if(a == b && a != 0) throw "NullPointerException";
			return b;
		}
		if(a->val > b->val)
			std::swap(a, b);
		if(!a->R)
			a->R = b;
		else 
			a->R = merge (a->R, b);
		// if(!a->L || a->R->d > a->L->d)
		std::swap(a->R, a->L);
		// a->d = a->R ? a->R->d + 1 : 1;
		return a;
	}

	void mergeAddition(){
		SHeapBoot<T,INF> h(addition.begin(), addition.end());
		addition.clear();
		root = merge(root, h.root);
		h.root = 0;
	}

	void printSubtree(SNode<T>* n, int level) {
		std::cout << std::string(level, ' ') << (n? n->val : 0) << ':' << (n? n->d : 0) << std::endl;
		if(!n)
			return;
		printSubtree(n->L, level+1);
		printSubtree(n->R, level+1);
	}

	bool checkMin(SNode<T>* n){
		if(!n) throw "NullPointerException";
		return (n->L ? (n->val <= n->L->val && checkMin(n->L)) : true) &&
				(n->R ? (n->val <= n->R->val && checkMin(n->R)) : true);
	}
	
	void clear(SNode<T> * n) {
		if(n->L) clear(n->L);
		if(n->R) clear(n->R);
		delete n;
	}
	
};