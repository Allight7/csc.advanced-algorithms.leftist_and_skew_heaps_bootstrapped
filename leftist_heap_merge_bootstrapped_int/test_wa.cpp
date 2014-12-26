#include "leftist_heap_merge_bootstrapped_int.h"
#include <vector>
#include <cassert>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

void gen( int n, std::vector <int> &a ) {
  a.resize(n);
  forn(i, n)
    a[i] = rand() % 100;
}

LeftistHeapMergeBootInt h;

int main() {
  std::vector <int> x, ns(4);
  ns[0]=3;  ns[1]=5;  ns[2]=10; ns[3]=20;
  for (auto n : ns) // size of test
    forn(t, 10000) { // number of tests

	  // test add + min + pop
      gen(n, x);
      forn(i, n)
        h.add(x[i]);
      forn(i, n) {
		if(h.empty()){ fprintf(stderr, "empty too soon; break"); break;}
        auto it = min_element(x.begin(), x.end());
        assert(h.min() == *it);
        h.pop();
        x.erase(it);
      }
    }
  fprintf(stderr, "Test for WA: OK.\n");
}