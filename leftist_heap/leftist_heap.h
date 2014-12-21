#include <vector>
#include <algorithm>
#include <iostream>


template <class T>
struct LNode {
	int d;
	T val;
	LNode <T> * L;
	LNode <T> * R;

	LNode() {
		d = 0;
		L = R = 0;
	}
	LNode(T _val) { 
		d = 1; 
		val = _val; 
		L = R = 0;
	}
};

template <class T, const T INF>
struct LHeap {
	LNode<T> * root;

	
	LHeap() {
		root = 0;
	}

	LHeap( int n, T *a ) { 
		root = 0;
		build(n, a); 
	}

	~LHeap() { 
		clear(); 
	}

	template <class POINTER>
	void build(int an, POINTER a ) { // O(n)
		clear();							//не очень элегантно, но хотелось обойтись без добавления в каждый узел инфы о его связях с родителем.
		std::vector<LNode<T> *> ptrs(an+1, 0);
		for (int i = 0; i < an; i++){
			ptrs[i] = new LNode<T>(*a++);
		}
		for(int i = an/2; i >= 0; i--){
			int j = i;
			while (j < an && ptrs[j]) {
				int m = j, l = 2 * j + 1, r = l + 1;
				if (l <= an && ptrs[l] && ptrs[l]->val < ptrs[m]->val) m = l;
				if (r <= an && ptrs[r] && ptrs[r]->val < ptrs[m]->val) m = r;
				if (m == j)
					break;
				std::swap(ptrs[m], ptrs[j]);
				j = m;
			}
		}

		root = ptrs[0];
		for(int i = 0; i < an/2; ++i){
			ptrs[i]->L = ptrs[2*i+1];
			ptrs[i]->R = ptrs[2*i+2];
		}
		dRecount(root);
	}

	int dRecount(LNode<T>* n)
	{
		if(!n)
			return 0;
		if(!n->R || !n->L)
			return n->d = 1;
		return n->d = std::min(dRecount(n->L), dRecount(n->R)) + 1;
	}

	// void down(LNode<T> * n) {
	// 	LNode<T> * smaller = n;
	// 	while(n->L || n->R){
	// 		if(n->L && n->L->val < n->val) smaller = n->L;
	// 		if(n->R && n->R->val < n->val) smaller = n->R;
	// 		if(smaller == n)
	// 			break;
	// 		std::swap(n->val, smaller->val);
	// 		n = smaller;
	// 	}
	// }

	void clear() {
		if(root)
			clear(root);
	}

	void clear(LNode<T> * n) {
		if(n->L) clear(n->L);
		if(n->R) clear(n->R);
		delete n;
	}

	LNode<T> * merge (LNode<T> * a, LNode<T> * b) {  // returns pointer to the head of merged heap
													 // if only one of nodes NOTNULL, returns it
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
		if(!a->L || a->R->d > a->L->d)
			std::swap(a->R, a->L);
		a->d = a->R ? a->R->d + 1 : 1;
		return a;
	}

	void add (T val) {
		if(!root) 
			root = new LNode<T>(val);
		else 
			root = merge(root, new LNode<T>(val));
	}

	T min (){
		return root ? root->val : INF;
	}

	T extractMin (){
		if(!root)
			return INF;
		T oldMin = root->val;
		LNode<T> * oldRoot = root;
		root = merge(oldRoot->L, oldRoot->R);
		delete oldRoot;
		return oldMin;
	}

	void printSubtree(LNode<T>* n, int level) {
		std::cout << std::string(level, ' ') << (n? n->val : 0) << ':' << (n? n->d : 0) << std::endl;
		if(!n)
			return;
		printSubtree(n->L, level+1);
		printSubtree(n->R, level+1);
	}

	bool checkMin(LNode<T>* n){
		if(!n) throw "NullPointerException";
		return (n->L ? (n->val <= n->L->val && checkMin(n->L)) : true) &&
				(n->R ? (n->val <= n->R->val && checkMin(n->R)) : true);
	}
};