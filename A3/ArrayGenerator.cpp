#include <algorithm>
#include <random>
#include <vector>

class ArrayGenerator {
public:
  static const int max_len = 100000;
  static const int min_len = 20;
  static const int len_step = 100;
  static const int max_a = 6000;
  static const int min_a = 0;

  static std::vector<int> getRandomArray() {
    std::vector<int> v(max_len);
    for (int& val : v) {
      val = getRandomNumber(min_a, max_a);
    }
    return v;
  }

  static std::vector<int> getReverseSortedArray() {
    std::vector<int> v = getRandomArray();
    std::sort(v.rbegin(), v.rend());
    return v;
  }

  static std::vector<int> getAlmostSortedArray() {
    std::vector<int> v = getRandomArray();
    std::sort(v.begin(), v.end());
    int k = getRandomNumber(v.size() / 200, v.size() / 100);
    for (int i = 0; i < k; ++i) {
      std::swap(v[i], v[v.size() - i - 1]);
    }
    return v;
  }

private:
  static int getRandomNumber(int l, int r) {
    std::random_device random_dev;
    std::mt19937 generator(random_dev());
    std::uniform_int_distribution<> distr(l, r);
    return distr(generator);
  }
};
