/* Copyright (c) 2020 Andrew Smith
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Author: Andrew Smith
 */

#include "bloomfilter.h"
#include <iostream>
#include <fstream>

/** 
 * Example user defined struct to hash
 */
typedef struct {
  uint64_t pc;
  std::vector<int> history;
} event;

/** 
 * Need to extend on the hash function to hash an arbitrary class
 */
namespace std {
  template <>
  struct hash<event> {
    size_t operator()(const event& k) const {
      hash<uint64_t> h1;
      hash<vector<int>> h2;
      size_t seed = 0;
      seed ^= h1(k.pc) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      seed ^= h2(k.history) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      return seed;
    }
  };
}

int main() {
  Bloomfilter<event> filter(3, 2048, 0);

  event a;
  a.pc = 1023874;
  a.history.resize(10, 38247);
  event b;
  b.pc = 10242344;
  b.history.resize(10, 9876);
  event c;
  c.pc = 102923416;
  c.history.resize(10, 1234);

  filter.insert(a);
  filter.insert(c);

  c.history[8] = 4287;

  std::cout << "1: " << filter.find(a) << "; 2: " << filter.find(b) << "; 3: " << filter.find(c) << "\n";

  return 0;
}
