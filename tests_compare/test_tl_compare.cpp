#include "../leftist_heap/leftist_heap.h"
#include "../leftist_heap_bootstrapped/leftist_heap_bootstrapped.h"
#include "../leftist_heap_merge_bootstrapped_int/leftist_heap_merge_bootstrapped_int.h"
#include "../skew_heap/skew_heap.h"
#include "../skew_heap_bootstrapped/skew_heap_bootstrapped.h"
#include "../skew_heap_merge_bootstrapped_int/skew_heap_merge_bootstrapped_int.h"
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
  // int n = HEAP_SIZE;
  // int k = HEAPS_NUM;

  double start = 0;

  forn(a,1){
    fprintf(stderr, "a = %d\n",a);
  
    forn(b,2){
      int n = 1; //heap size;
      int k = 1; //heaps num;
      int * p = b ? &n : &k;
    
      for(*p = (int)1e4; *p < (int)1e6; *p *= 10){
        fprintf(stderr, "\n============================================================\n");
        fprintf(stderr, "k = %d, n = %d\n",k,n);
        std::vector <std::vector <int>> x(k);
        std::vector <LHeap<unsigned>>         hl(k);
        std::vector <LHeapBoot<unsigned>>     hla(k);
        std::vector <LeftistHeapMergeBootInt> hlam(k);
        std::vector <SHeap<unsigned>>         hs(k);
        std::vector <SHeapBoot<unsigned>>     hsa(k);
        std::vector <SkewHeapMergeBootInt>    hsam(k);
        std::vector< std::priority_queue<int, std::vector<int>, std::greater<int>>> q(k);

        forn(i,k)
          gen(n,x[i]);
        timeStamp("gen: %.2f\n");


        // ----------------------------------------- //
        fprintf(stderr, "\n\nleftist\n\n");

        forn(i,k)
          forn(j, n)
            hl[i].add(x[i][j]);
        timeStamp("k heaps builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          hl[0].mergeWithHeap(hl[i]);
        timeStamp("k heaps merged: \t%.2f\n");

        hl[0].pop();
        timeStamp("heap firts acc: \t%.2f\n");

        while (!hl[0].empty())
          hl[0].pop();     
        timeStamp("heap extracted: \t%.2f\n");
        
        forn(i,k)
          hl[i].clear();
        timeStamp("cleared: \t%.2f\n");

      // ----------------------------------------- //
        fprintf(stderr, "\n\nleftist add\n\n");

        forn(i,k)
          forn(j, n)
            hla[i].add(x[i][j]);
        timeStamp("k heaps builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          hla[0].mergeWithHeap(hla[i]);
        timeStamp("k heaps merged: \t%.2f\n");

        hla[0].pop();
        timeStamp("heap firts acc: \t%.2f\n");

        while (!hla[0].empty())
          hla[0].pop();     
        timeStamp("heap extracted: \t%.2f\n");
        
        forn(i,k)
          hla[i].clear();
        timeStamp("cleared: \t%.2f\n");

      // ----------------------------------------- //
        fprintf(stderr, "\n\nleftist add merge\n\n");

        forn(i,k)
          forn(j, n)
            hlam[i].add(x[i][j]);
        timeStamp("k heaps builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          hlam[0].mergeWithHeap(hlam[i]);
        timeStamp("k heaps merged: \t%.2f\n");

        hlam[0].pop();
        timeStamp("heap firts acc: \t%.2f\n");

        while (!hlam[0].empty())
          hlam[0].pop();     
        timeStamp("heap extracted: \t%.2f\n");
        
        forn(i,k)
          hlam[i].clear();
        timeStamp("cleared: \t%.2f\n");

      // ----------------------------------------- //
        fprintf(stderr, "\n\nskew\n\n");

        forn(i,k)
          forn(j, n)
            hs[i].add(x[i][j]);
        timeStamp("k heaps builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          hs[0].mergeWithHeap(hs[i]);
        timeStamp("k heaps merged: \t%.2f\n");

        hs[0].pop();
        timeStamp("heap firts acc: \t%.2f\n");

        while (!hs[0].empty())
          hs[0].pop();     
        timeStamp("heap extracted: \t%.2f\n");
        
        forn(i,k)
          hs[i].clear();
        timeStamp("cleared: \t%.2f\n");

      // ----------------------------------------- //
        fprintf(stderr, "\n\nskew add\n\n");

        forn(i,k)
          forn(j, n)
            hsa[i].add(x[i][j]);
        timeStamp("k heaps builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          hsa[0].mergeWithHeap(hsa[i]);
        timeStamp("k heaps merged: \t%.2f\n");

        hsa[0].pop();
        timeStamp("heap firts acc: \t%.2f\n");

        while (!hsa[0].empty())
          hsa[0].pop();     
        timeStamp("heap extracted: \t%.2f\n");
        
        forn(i,k)
          hsa[i].clear();
        timeStamp("cleared: \t%.2f\n");

      // ----------------------------------------- //
        fprintf(stderr, "\n\nskew add merge\n\n");

        forn(i,k)
          forn(j, n)
            hsam[i].add(x[i][j]);
        timeStamp("k heaps builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          hsam[0].mergeWithHeap(hsam[i]);
        timeStamp("k heaps merged: \t%.2f\n");

        hsam[0].pop();
        timeStamp("heap firts acc: \t%.2f\n");

        while (!hsam[0].empty())
          hsam[0].pop();     
        timeStamp("heap extracted: \t%.2f\n");
        
        forn(i,k)
          hsam[i].clear();
        timeStamp("cleared: \t%.2f\n");

      // ----------------------------------------- //
        fprintf(stderr, "\n\npriority queue\n\n");

        forn(i, k)
          forn(j, n)
            q[i].push(x[i][j]);
        timeStamp("k queues builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          forn(j, n){
            q[0].push(q[i].top());
            q[i].pop();
          }
        timeStamp("k queues merged: \t%.2f\n");

        q[0].pop();
        timeStamp("queue firts acc: \t%.2f\n");
        
        while (!q[0].empty())
          q[0].pop();     
        timeStamp("queue extracted: \t%.2f\n");

      // ----------------------------------------- //
        fprintf(stderr, "\n\nset\n\n");

        std::vector<std::multiset<int>> s(k);
        forn(i, k)
          forn(j, n)
            s[i].insert(x[i][j]);
        timeStamp("k sets builded: \t%.2f\n");

        for(int i = 1; i < k; ++i)
          forn(j, n){
            s[0].insert(*(s[i].begin()));
            s[i].erase(s[i].begin());
          }
        timeStamp("k sets merged: \t\t%.2f\n");

        s[0].erase(s[0].begin());
        timeStamp("set firts acc: \t\t%.2f\n");
        
        while (!s[0].empty())
        s[0].erase(s[0].begin());
        timeStamp("set extracted: \t\t%.2f\n");
      }
    }
  }
}
