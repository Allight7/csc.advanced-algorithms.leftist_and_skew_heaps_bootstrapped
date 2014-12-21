#include "leftist_heap_bootstraped.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

unsigned R() { return (rand() << 15) | rand(); } // mingw g++ has 15-bit rand()

void gen( int n, vector <int> &a ) {
  a.resize(n);
  forn(i, n)
    a[i] = R();
}

const int maxN = 1e6;
LHeapBoot<unsigned, INT_MAX> h;
LHeapBoot<unsigned, INT_MAX> h1,h2;

double start = 0;
#define timeStamp(...) fprintf(stderr, __VA_ARGS__, (clock() - start) / CLOCKS_PER_SEC), start = clock()

int main() {
  vector <int> x;
  int n = maxN;
  gen(n, x);
  timeStamp("input is generated: %.2f\n");

  h.build(n, x.begin());
  // forn(i, n)
  //   h.add(x[i]);
  timeStamp("leftist_heap \tbuilded: \t%.2f\n");
  forn(i, n)
    h.extractMin();
  timeStamp("leftist_heap \textracted: \t%.2f\n");


  priority_queue<int, vector<int>, greater<int>> q;
  forn(i, n)
    q.push(x[i]);
  timeStamp("priority_queue \tbuilded: \t%.2f\n");
  forn(i, n)
    q.pop();
  timeStamp("priority_queue \textracted: \t%.2f\n");

  multiset<int> s;
  forn(i, n)
    s.insert(x[i]);
  timeStamp("set \t\tbuilded: \t%.2f\n");
  forn(i, n)
    s.erase(s.begin());
  timeStamp("set \t\textracted: \t%.2f\n");

  // vector <int> x1,x2;
  // gen(n, x1);
  // gen(n, x2);
  // timeStamp("input2 is generated: %.2f\n");

  // h1.build(n,x1.begin());
  // timeStamp("leftist_heap1 \tbuilded: \t%.2f\n");
  // cout << h1.root->d << endl; 
  // h2.build(n,x2.begin());
  // timeStamp("leftist_heap2 \tbuilded: \t%.2f\n");
  // cout << h2.root->d<< endl;
  // h1.root = h1.merge(h1.root, h2.root);
  // h2.root = 0;
  // cout << h1.root->d<< endl;
  // timeStamp("leftist_heaps \tmerged: \t%.10f\n");


  // priority_queue<int, vector<int>, greater<int>> q1;
  // forn(i, n)
  //   q1.push(x1[i]);
  // timeStamp("priority_queue1\tbuilded: \t%.2f\n");
  // priority_queue<int, vector<int>, greater<int>> q2;
  // forn(i, n)
  //   q2.push(x2[i]);
  // timeStamp("priority_queue2\tbuilded: \t%.2f\n");
  // forn(i, n){
  //   q1.push(q2.top());
  //   q2.pop();
  // }
  // timeStamp("priority_queues\tmerged: \t%.2f\n");

  // multiset<int> s1;
  // forn(i, n)
  //   s1.insert(x1[i]);
  // timeStamp("set1 \t\tbuilded: \t%.2f\n");
  // multiset<int> s2;
  // forn(i, n)
  //   s2.insert(x2[i]);
  // timeStamp("set2 \t\tbuilded: \t%.2f\n");
  // forn(i, n){
  //   s1.insert(*(s2.begin()));
  //   s2.erase(s2.begin());
  // }
  // timeStamp("sets \t\tmerged: \t%.2f\n");
}
