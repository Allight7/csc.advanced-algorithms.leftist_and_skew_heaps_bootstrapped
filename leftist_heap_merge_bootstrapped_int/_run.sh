for suf in wa tl; do 
  g++ -Wall -std=c++11 test_$suf.cpp -o test_$suf && ./test_$suf
done

