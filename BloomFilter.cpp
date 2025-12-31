#include "BloomFilter.h"
#include "murmur3.h"

BloomFilter::BloomFilter(size_t size_in_bits, int hashes)
    : size(size_in_bits), num_hashes(hashes) {
  bit_array.resize(size, false);
}

void BloomFilter::add(const string &str) {
  for (int i = 0; i < num_hashes; ++i) {
    uint32_t h;
    MurmurHash3_x86_32(str.c_str(), str.length(), i, &h);
    bit_array[h % size] = true;
  }
}

bool BloomFilter::possiblyContains(const string &str) const {
  for (int i = 0; i < num_hashes; ++i) {
    uint32_t h;
    MurmurHash3_x86_32(str.c_str(), str.length(), i, &h);
    if (!bit_array[h % size]) {
      return false;
    }
  }
  return true;
}