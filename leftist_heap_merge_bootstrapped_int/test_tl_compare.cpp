#include "leftist_heap_merge_bootstrapped_int.h"
#include "../test_param.h"
#include <climits>
#include <ctime>
#include <iostream>
#include <functional>
#include <queue>
#include <set>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

unsigned R() { return (rand() << 15) | rand(); } // mingw g++ has 15-bit rand()

void gen( int n, std::vector <int> &a ) {
  a.resize(n);
  forn(i, n)
    a[i] = R();
}




#define timeStamp(...) fprintf(stderr, __VA_ARGS__, (clock() - start) / CLOCKS_PER_SEC), start = clock()

int main() {
  // std::vector <int> x;
  int n = HEAP_SIZE;
  int k = HEAPS_NUM;
  // gen(n, x);
  // timeStamp("input is generated: %.2f\n");

  // h.build(n, x.begin());
  // // forn(i, n)
  // //   h.add(x[i]);
  // timeStamp("leftist_heap \tbuilded: \t%.2f\n");
  // forn(i, n)
  //   h.extractMin();
  // timeStamp("leftist_heap \textracted: \t%.2f\n");


  // priority_queue<int, std::vector<int>, greater<int>> q;
  // forn(i, n)
  //   q.push(x[i]);
  // timeStamp("priority_queue \tbuilded: \t%.2f\n");
  // forn(i, n)
  //   q.pop();
  // timeStamp("priority_queue \textracted: \t%.2f\n");

  // multiset<int> s;
  // forn(i, n)
  //   s.insert(x[i]);
  // timeStamp("set \t\tbuilded: \t%.2f\n");
  // forn(i, n)
  //   s.erase(s.begin());
  // timeStamp("set \t\textracted: \t%.2f\n");

  double start = 0;

  std::vector <std::vector <int>> x(k);
  std::vector <LeftistHeapMergeBootInt>   h(k);
  
  forn(i,k)
    gen(n,x[i]);
  timeStamp("input is generated: %.2f\n");

  forn(i,k)
    forn(j, n)
      h[i].add(x[i][j]);
  timeStamp("100 leftist_heaps \tbuilded: \t%.2f\n");

  for(int i = 1; i < k; ++i)
    h[0].mergeWithHeap(h[i]);
  timeStamp("100 leftist_heaps \tmerged: \t%.2f\n");

  h[0].pop();
  timeStamp("leftist_heap \tfirst accessed: \t%.2f\n");

  h[0].pop();
  timeStamp("leftist_heap \tsecond accessed: \t%.2f\n");

  while (!h[0].empty())
    h[0].pop();     
  timeStamp("leftist_heap \tfully extracted: \t%.2f\n");




  std::vector< std::priority_queue<int, std::vector<int>, std::greater<int>>> q(k);

  forn(i, k)
    forn(j, n)
      q[i].push(x[i][j]);
  timeStamp("100 priority_queues\tbuilded: \t%.2f\n");

  for(int i = 1; i < k; ++i)
    forn(j, n){
      q[0].push(q[i].top());
      q[i].pop();
    }
  timeStamp("100 priority_queues\tmerged: \t%.2f\n");
  
  while (!q[0].empty())
  q[0].pop();     
  timeStamp("priority_queue fully extracted: \t%.2f\n");



  std::vector<std::multiset<int>> s(k);
  forn(i, k)
    forn(j, n)
      s[i].insert(x[i][j]);
  timeStamp("100 sets \t\tbuilded: \t%.2f\n");

  for(int i = 1; i < k; ++i)
    forn(j, n){
      s[0].insert(*(s[i].begin()));
      s[i].erase(s[i].begin());
    }
  timeStamp("100 sets \t\tmerged: \t%.2f\n");

  while (!s[0].empty())
  s[0].erase(s[0].begin());
  timeStamp("set \t\tfully extracted: \t%.2f\n");
}
