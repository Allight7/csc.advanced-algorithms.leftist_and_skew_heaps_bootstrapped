#include "leftist_heap_merge_bootstrapped_int.h"
#include <ctime>
#include <climits>


#define forn(i, n) for (int i = 0; i < (int)(n); i++)

void gen( int n, std::vector <int> &a ) {
  a.resize(n);
  forn(i, n)
    a[i] = rand()%100;
}

const int maxN = static_cast<int>(1e5);
LeftistHeapMergeBootInt h;

int main() {
  std::vector <int> x;
  int n = maxN;
  forn(t, 10) { // number of tests
    // test extractMin
    gen(n, x);
     forn(i, n)
        h.add(x[i]);
     forn(i, n){
		 if(h.empty()){ fprintf(stderr, "empty too soon; break"); break;}
      h.pop();
	  }
    // test add
    gen(n, x);
    forn(i, n)
      h.add(x[i]);
	forn(i,n/3)
		h.pop();
    h.clear();
	h.add(12);
  }
  fprintf(stderr, "Test for TL: OK. Time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC);
}
