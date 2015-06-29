# for suf in wa tl tl_compare; do 
for suf in tl_compare; do 
  g++ -Wall -std=c++11 test_$suf.cpp -o test_$suf && ./test_$suf
done

