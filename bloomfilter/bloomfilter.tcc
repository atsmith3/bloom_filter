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

/**
 * Bloomfilter constructor, initializes the offset array and the table to
 * false.
 * @param n The number of hashes to perform on the input object
 * @param size The size of the table
 * @param seed The seed for srand() for generating the n hashes
 * @return None
 */
template<class T>
Bloomfilter<T>::Bloomfilter(unsigned int n, unsigned int size, unsigned int seed) {
  std::srand(seed);
  offset.resize(n, 0);
  table.resize(size, false);
  for(size_t i = 0; i < offset.size(); i++) {
    offset[i] = std::rand();
  }
}

/**
 * Bloomfilter find. Checks if the object is in the filter. Due to the
 * nature of the bloom filter there is a chance of a false positive.
 * @param obj Item to be hashed
 * @return True if the item is in the table
 */
template<class T>
bool Bloomfilter<T>::find(const T obj) const {
  if(table.size() == 0 || offset.size() == 0) {
    return false;
  }
  bool retval = true;
  int idx = 0;
  for(size_t i = 0; i < offset.size(); i++) {
    idx = h(offset[i], obj) % table.size();
    retval &= table[idx];
  }
  return retval;
}

/**
 * Bloomfilter insert. Adds the object to the filter.
 * @param obj Item to be hashed
 */
template<class T>
void Bloomfilter<T>::insert(const T obj) {
  if(table.size() == 0) {
    return;
  }
  int idx = 0;
  for(size_t i = 0; i < offset.size(); i++) {
    idx = h(offset[i], obj) % table.size();
    table[idx] = true;
  }
}

/**
 * resize, clears out the bloom filter and resets the seed, n hash ways and the
 * size of the underlying table.
 * @param n The number of hashes to perform on the input object
 * @param size The size of the table
 * @param seed The seed for srand() for generating the n hashes
 * @return None
 */
template<class T>
void Bloomfilter<T>::resize(unsigned int n, unsigned int size, unsigned int seed) {
  clear();
  std::srand(seed);
  offset.resize(n, 0);
  table.resize(size, false);
  for(size_t i = 0; i < offset.size(); i++) {
    offset[i] = std::rand();
  }
}

/**
 * Reset the contents of the bloom filter, as it is not possible to erase a
 * specific item.
 */
template<class T>
void Bloomfilter<T>::clear() {
  std::replace(table.begin(), table.end(), true, false);
}

/**
 * Bloomfilter hash function, hashes the object n ways with the std::hash
 * function. Uses a different "offset" for hash.
 *    https://stackoverflow.com/a/7222201/916549
 *    https://www.boost.org/doc/libs/1_35_0/libs/functional/hash/examples/point.cpp
 * @param val Item to be hashed
 * @param offset Int prepended to the hash for the n-way hash
 * @return Hashed value
 */
template<class T>
size_t Bloomfilter<T>::h(const int offset, const T& val) const {
  size_t seed = 0;
  std::hash<int> hash1;
  std::hash<T> hash2;
  seed ^= hash1(offset) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  seed ^= hash2(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  return seed;
}

/**
 * Hash function for std::vector<T>. Note that T must also have a hash
 * function if it is not part of the Standard specializations for basic
 * types. Combines the hashes of all the elements.
 *    https://stackoverflow.com/a/7222201/916549
 *    https://www.boost.org/doc/libs/1_35_0/libs/functional/hash/examples/point.cpp
 * @param k Vector to be hashed
 * @return Hashed value
 */
namespace std {
  template <class T>
  struct hash<vector<T>> {
    size_t operator()(const std::vector<T>& k) const {
      hash<T> h;
      size_t seed = 0;
      for(auto it = k.begin(); it != k.end(); it++) {
        seed ^= h(*it) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    }
  };
}
