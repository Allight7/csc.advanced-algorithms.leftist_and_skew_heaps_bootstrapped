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
// #define timeStamp(...) fprintf(stderr, __VA_ARGS__, clock() - start), start = clock()

int main() {
  // int n = HEAP_SIZE;
  // int k = HEAPS_NUM;

  const int rounds          = 10;
  const int memoryInit      = (int)1e4;
  const int memoryCapacity  = (int)5e6;
  const int memoryMult      = 2;

  double start = 0;

  forn(r,rounds){
    fprintf(stderr, "\nr = %2d\t",r+1);
    fprintf(stdout, "\nr = %2d\t",r+1);
  
    forn(b,2){
      int n = 2; //heap size;
      int k = 2; //heaps num;
      int * p = b ? &n : &k;
    
      for(*p = memoryInit; *p < memoryCapacity+1; *p *= memoryMult){
        // fprintf(stderr, "============================================================\n");
        fprintf(stderr, "k = %8d\tn = %8d\t",k,n);
        fprintf(stdout, "\n\tk = %8d\tn = %8d\t",k,n);
        std::vector <std::vector <int>> x(k);
        std::vector <LHeap<unsigned>>         hl(k);
        std::vector <LHeapBoot<unsigned>>     hla(k);
        std::vector <LeftistHeapMergeBootInt> hlam(k);
        std::vector <SHeap<unsigned>>         hs(k);
        std::vector <SHeapBoot<unsigned>>     hsa(k);
        std::vector <SkewHeapMergeBootInt>    hsam(k);
        std::vector< std::priority_queue<int, std::vector<int>, std::greater<int>>> q(k);
        std::vector<std::multiset<int>>       s(k);

        forn(i,k)
          gen(n,x[i]);
        start = clock();


        // ----------------------------------------- //
        // fprintf(stderr, "\n\nleftist\n\n");
        fprintf(stderr, "|\tlh\t");

        forn(i,k)
          forn(j, n)
            hl[i].add(x[i][j]);
        // timeStamp("k heaps builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          hl[0].mergeWithHeap(hl[i]);
        // timeStamp("k heaps merged: \t%.2f\n");
        timeStamp("%.2f\t");

        hl[0].pop();
        // timeStamp("heap firts acc: \t%.2f\n");
        timeStamp("%.2f\t");

        while (!hl[0].empty())
          hl[0].pop();     
        // timeStamp("heap extracted: \t%.2f\n");
        timeStamp("%.2f\t");
        
        forn(i,k)
          hl[i].clear();
        start = clock();

      // ----------------------------------------- //
        // fprintf(stderr, "\n\nleftist add\n\n");
        fprintf(stderr, "|\tlah\t");

        forn(i,k)
          forn(j, n)
            hla[i].add(x[i][j]);
        // timeStamp("k heaps builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          hla[0].mergeWithHeap(hla[i]);
        // timeStamp("k heaps merged: \t%.2f\n");
        timeStamp("%.2f\t");

        hla[0].pop();
        // timeStamp("heap firts acc: \t%.2f\n");
        timeStamp("%.2f\t");

        while (!hla[0].empty())
          hla[0].pop();     
        // timeStamp("heap extracted: \t%.2f\n");
        timeStamp("%.2f\t");
        
        forn(i,k)
          hla[i].clear();
        start = clock();

      // ----------------------------------------- //
        // fprintf(stderr, "\n\nleftist add merge\n\n");
        fprintf(stderr, "|\tlamh\t");

        forn(i,k)
          forn(j, n)
            hlam[i].add(x[i][j]);
        // timeStamp("k heaps builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          hlam[0].mergeWithHeap(hlam[i]);
        // timeStamp("k heaps merged: \t%.2f\n");
        timeStamp("%.2f\t");

        hlam[0].pop();
        // timeStamp("heap firts acc: \t%.2f\n");
        timeStamp("%.2f\t");

        while (!hlam[0].empty())
          hlam[0].pop();     
        // timeStamp("heap extracted: \t%.2f\n");
        timeStamp("%.2f\t");
        
        forn(i,k)
          hlam[i].clear();
        start = clock();

      // ----------------------------------------- //
        // fprintf(stderr, "\n\nskew\n\n");
        fprintf(stderr, "|\tsh\t");

        forn(i,k)
          forn(j, n)
            hs[i].add(x[i][j]);
        // timeStamp("k heaps builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          hs[0].mergeWithHeap(hs[i]);
        // timeStamp("k heaps merged: \t%.2f\n");
        timeStamp("%.2f\t");

        hs[0].pop();
        // timeStamp("heap firts acc: \t%.2f\n");
        timeStamp("%.2f\t");

        while (!hs[0].empty())
          hs[0].pop();     
        // timeStamp("heap extracted: \t%.2f\n");
        timeStamp("%.2f\t");
        
        forn(i,k)
          hs[i].clear();
        start = clock();

      // ----------------------------------------- //
        // fprintf(stderr, "\n\nskew add\n\n");
        fprintf(stderr, "|\tsah\t");

        forn(i,k)
          forn(j, n)
            hsa[i].add(x[i][j]);
        // timeStamp("k heaps builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          hsa[0].mergeWithHeap(hsa[i]);
        // timeStamp("k heaps merged: \t%.2f\n");
        timeStamp("%.2f\t");

        hsa[0].pop();
        // timeStamp("heap firts acc: \t%.2f\n");
        timeStamp("%.2f\t");

        while (!hsa[0].empty())
          hsa[0].pop();     
        timeStamp("%.2f\t");
        // timeStamp("heap extracted: \t%.2f\n");
        
        forn(i,k)
          hsa[i].clear();
        start = clock();

      // ----------------------------------------- //
        // fprintf(stderr, "\n\nskew add merge\n\n");
        fprintf(stderr, "|\tsamh\t");

        forn(i,k)
          forn(j, n)
            hsam[i].add(x[i][j]);
        // timeStamp("k heaps builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          hsam[0].mergeWithHeap(hsam[i]);
        // timeStamp("k heaps merged: \t%.2f\n");
        timeStamp("%.2f\t");

        hsam[0].pop();
        // timeStamp("heap firts acc: \t%.2f\n");
        timeStamp("%.2f\t");

        while (!hsam[0].empty())
          hsam[0].pop();     
        // timeStamp("heap extracted: \t%.2f\n");
        timeStamp("%.2f\t");
        
        forn(i,k)
          hsam[i].clear();
        start = clock();

      // ----------------------------------------- //
        // fprintf(stderr, "\n\npriority queue\n\n");
        fprintf(stderr, "|\tqu\t");

        forn(i, k)
          forn(j, n)
            q[i].push(x[i][j]);
        // timeStamp("k queues builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          forn(j, n){
            q[0].push(q[i].top());
            q[i].pop();
          }
        // timeStamp("k queues merged: \t%.2f\n");
        timeStamp("%.2f\t");

        q[0].pop();
        // timeStamp("queue firts acc: \t%.2f\n");
        timeStamp("%.2f\t");
        
        while (!q[0].empty())
          q[0].pop();     
        // timeStamp("queue extracted: \t%.2f\n");
        timeStamp("%.2f\t");

      // ----------------------------------------- //
        // fprintf(stderr, "\n\nset\n\n");
        fprintf(stderr, "|\tset\t");

        forn(i, k)
          forn(j, n)
            s[i].insert(x[i][j]);
        // timeStamp("k sets builded: \t%.2f\n");
        timeStamp("%.2f\t");

        for(int i = 1; i < k; ++i)
          forn(j, n){
            s[0].insert(*(s[i].begin()));
            s[i].erase(s[i].begin());
          }
        // timeStamp("k sets merged: \t\t%.2f\n");
        timeStamp("%.2f\t");

        s[0].erase(s[0].begin());
        // timeStamp("set firts acc: \t\t%.2f\n");
        timeStamp("%.2f\t");
        
        while (!s[0].empty())
        s[0].erase(s[0].begin());
        // timeStamp("set extracted: \t\t%.2f\n");
        timeStamp("%.2f\t");


        fprintf(stderr, "|\t");
      }
    }
  }
}
