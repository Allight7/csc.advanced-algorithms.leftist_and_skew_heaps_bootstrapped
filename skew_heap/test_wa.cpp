#include "skew_heap.h"
 
 #include <vector>
 #include <cassert>
 #include <climits>


#define forn(i, n) for (int i = 0; i < (int)(n); i++)

void gen( int n, std::vector <int> &a ) {
  a.resize(n);
  forn(i, n)
    a[i] = rand() % 100;
}

SHeap<int> h;

int main() {
  std::vector <int> x, ns(4);
  ns[0]=3;  ns[1]=5;  ns[2]=10; ns[3]=20;
  for (auto n : ns) // size of test
    forn(t, 10000) { // number of tests

      // test build + min
      gen(n, x);
      h.build(x.begin(),x.end());
      forn(i, n) {
        auto it = min_element(x.begin(), x.end());
        assert(h.min() == *it);
        h.pop();
        x.erase(it);
      }
      
	  // test add + min
      gen(n, x);
      forn(i, n)
        h.add(x[i]);
      forn(i, n) {
        auto it = min_element(x.begin(), x.end());
        assert(h.min() == *it);
        h.pop();
        x.erase(it);
      }
    }
  fprintf(stderr, "Test for WA: OK.\n");
}
