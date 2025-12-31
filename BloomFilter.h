#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <cstddef>
#include <string>
#include <vector>

using namespace std;

class BloomFilter {
private:
  vector<bool> bit_array;
  size_t size;
  int num_hashes;

public:
  BloomFilter(size_t size_in_bits, int hashes);
  void add(const string &str);
  bool possiblyContains(const string &str) const;
};

#endif
