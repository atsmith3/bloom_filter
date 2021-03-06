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

#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <string>

template<class T>
class Bloomfilter {
  unsigned int n;           // Number of Hash Functions 
  unsigned int size;        // Size of the underlying table
  unsigned int seed;        // Seed to create offsets from
  std::vector<int> offset;
  std::vector<bool> table;

  size_t h(const int offset, const T& val) const;

protected:

public:
  Bloomfilter(unsigned int n = 0, unsigned int size = 0, unsigned int seed = 0);

  bool find(const T obj) const;

  void insert(const T obj);

  void resize(unsigned int n = 0, unsigned int size = 0, unsigned int seed = 0);

  void clear();
};

#include "bloomfilter.tcc"

#endif // __BLOOMFILTER_H__
