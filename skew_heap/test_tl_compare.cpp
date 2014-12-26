#include "skew_heap.h"
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

const int maxN = 1e6;
// LHeapBoot<unsigned, &i_max> h;


double start = 0;
#define timeStamp(...) fprintf(stderr, __VA_ARGS__, (clock() - start) / CLOCKS_PER_SEC), start = clock()

int main() {
  // std::vector <int> x;
  int n = maxN;
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

  std::vector <int> x1,x2;
  gen(n, x1);
  gen(n, x2);
  timeStamp("input2 is generated: %.2f\n");

  SHeap<unsigned> h1,h2;
  forn(i, n)
    h1.add(x1[i]);
  timeStamp("leftist_heap1 \tbuilded: \t%.2f\n");
//  h2.build(n,x2.begin());
  forn(i, n)
    h2.add(x2[i]);
  timeStamp("leftist_heap2 \tbuilded: \t%.2f\n");
//  std::cout << h1.root->d << std::endl; 
//  std::cout << h2.root->d << std::endl;
  h1.mergeWithHeap(h2);
//  std::cout << h1.root->d<< std::endl;
  timeStamp("leftist_heaps \tmerged: \t%.2f\n");
  h1.pop();
  timeStamp("leftist_heap1 \tfirst access: \t%.2f\n");
  h1.pop();
  timeStamp("leftist_heap1 \tsecond access: \t%.2f\n");
  while (!h1.empty())
  h1.pop();     
  timeStamp("leftist_heap1 \tfull extract: \t%.2f\n");


  std::priority_queue<int, std::vector<int>, std::greater<int>> q1;
  forn(i, n)
    q1.push(x1[i]);
  timeStamp("priority_queue1\tbuilded: \t%.2f\n");
  std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
  forn(i, n)
    q2.push(x2[i]);
  timeStamp("priority_queue2\tbuilded: \t%.2f\n");
  forn(i, n){
    q1.push(q2.top());
    q2.pop();
  }
  timeStamp("priority_queues\tmerged: \t%.2f\n");
  while (!q1.empty())
  q1.pop();     
  timeStamp("priority_queue1 full extract: \t%.2f\n");

  std::multiset<int> s1;
  forn(i, n)
    s1.insert(x1[i]);
  timeStamp("set1 \t\tbuilded: \t%.2f\n");
  std::multiset<int> s2;
  forn(i, n)
    s2.insert(x2[i]);
  timeStamp("set2 \t\tbuilded: \t%.2f\n");
  forn(i, n){
    s1.insert(*(s2.begin()));
    s2.erase(s2.begin());
  }
  timeStamp("sets \t\tmerged: \t%.2f\n");
  while (!s1.empty())
  s1.erase(s1.begin());
  timeStamp("set1 \tfull extracted: \t%.2f\n");
}
