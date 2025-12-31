#include "BloomFilter.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cerr << "Usage: " << argv[0] << " <mode: standard|bloom> <file1> <file2>"
         << endl;
    return 1;
  }

  string mode = argv[1];
  string file1 = argv[2];
  string file2 = argv[3];

  if (mode == "standard") {
    string cmd =
        "sort " + file1 + " > .tmp1 && sort " + file2 +
        " > .tmp2 && comm -12 .tmp1 .tmp2 > /dev/null && rm .tmp1 .tmp2";

    auto start = chrono::high_resolution_clock::now();
    int result = system(cmd.c_str());
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "------------------------------------------------" << endl;
    cout << "Standard (Sort+Comm) Time: " << elapsed.count() << " seconds"
         << endl;
    cout << "------------------------------------------------" << endl;
    return 0;
  } else if (mode != "bloom") {
    cerr << "Invalid mode: " << mode << endl;
    cerr << "Usage: " << argv[0] << " <mode: standard|bloom> <file1> <file2>"
         << endl;
    return 1;
  }

  BloomFilter bf(50000000, 5);
  unordered_set<string> set_file1;

  ifstream f1(file1);
  if (!f1.is_open()) {
    cerr << "Could not open file1." << endl;
    return 1;
  }
  string line;
  while (getline(f1, line)) {
    if (line.empty())
      continue;
    bf.add(line);
    set_file1.insert(line);
  }
  f1.close();

  ifstream f2(file2);
  if (!f2.is_open()) {
    cerr << "Could not open file2." << endl;
    return 1;
  }

  long long lines_processed = 0;
  long long bloom_rejections = 0;
  long long matches_found = 0;
  long long bloom_false_positives = 0;

  auto start_time = chrono::high_resolution_clock::now();

  while (getline(f2, line)) {
    lines_processed++;

    if (!bf.possiblyContains(line)) {
      bloom_rejections++;
      continue;
    }

    if (set_file1.find(line) != set_file1.end()) {
      matches_found++;
    } else {
      bloom_false_positives++;
    }
  }

  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed = end_time - start_time;

  cout << "------------------------------------------------" << endl;
  cout << "Mode:            " << mode << endl;
  cout << "Time:            " << elapsed.count() << " seconds" << endl;
  cout << "Lines Processed: " << lines_processed << endl;
  cout << "Bloom Rejections:" << bloom_rejections << endl;
  cout << "False Positives: " << bloom_false_positives << endl;
  cout << "Matches Found:   " << matches_found << endl;
  cout << "Efficiency:      Skipped "
       << (double)bloom_rejections / lines_processed * 100 << "% of work."
       << endl;
  cout << "------------------------------------------------" << endl;

  return 0;
}
