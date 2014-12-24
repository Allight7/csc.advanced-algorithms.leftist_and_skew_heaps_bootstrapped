#include "skew_heap_bootstrapped.h"

#include <cassert>
#include <climits>


#define forn(i, n) for (int i = 0; i < (int)(n); i++)

void gen( int n, std::vector <int> &a ) {
  a.resize(n);
  forn(i, n)
    a[i] = rand() % 100;
}

SHeapBoot<int, INT_MAX> h;

int main() {
  std::vector <int> x, ns(4);
  ns[0]=3;  ns[1]=5;  ns[2]=10; ns[3]=20;
  for (auto n : ns) // size of test
    forn(t, 10000) { // number of tests
      gen(n, x);
      // test build + extract
      h.build(x.begin(), x.end());
      h.checkMin();
      forn(i, n) {
        auto it = min_element(x.begin(), x.end());
        assert(h.extractMin() == *it);
        x.erase(it);
      }
      // test add + extract + min
      gen(n, x);
      forn(i, n)
        h.add(x[i]);
      h.checkMin();
      forn(i, n) {
        auto it = min_element(x.begin(), x.end());
        assert(h.min() == *it);
        assert(h.extractMin() == *it);
        x.erase(it);
      }
    }
  fprintf(stderr, "Test for WA: OK.\n");
}
