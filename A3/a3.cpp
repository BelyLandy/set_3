#include <cmath>
#include <iostream>
#include <vector>

void siftDown(std::vector<int> &array, int index, int end) {
  while (2 * index + 1 <= end) {
    int childIndex = 2 * index;
    if ((childIndex + 1 < end) && (array[childIndex] < array[childIndex + 1]))
      ++childIndex;
    if (!(array[index] < array[childIndex]))
      break;
    std::swap(array[index], array[childIndex]);
    index = childIndex;
  }
}

void buildMaxHeap(std::vector<int> &array, int start, int end) {
  for (int i = (end + start) / 2; i >= start; --i) {
    siftDown(array, i, end);
  }
}

void heapSort(std::vector<int> &array, int start, int end) {
  buildMaxHeap(array, start, end);

  int heapSize = end;
  for (int i = heapSize - 1; i >= start; --i) {
    std::swap(array[i], array[1]);
    --heapSize;
    siftDown(array, 1, heapSize);
  }
}

int partition(std::vector<int> &array, int start, int end) {
  int pivotIndex = start;
  ++start;
  --end;
  while (start <= end) {
    if (array[start] < array[pivotIndex]) {
      ++start;
      continue;
    }
    if (array[end] >= array[pivotIndex]) {
      --end;
      continue;
    }
    if (array[end] < array[start]) {
      std::swap(array[start], array[end]);
      continue;
    }
  }
  std::swap(array[end], array[pivotIndex]);
  return end;
}

void insertionSort(std::vector<int> &array, int start, int end) {
  for (int i = start; i < end; ++i) {
    int currentValue = array[i];
    int j = i - 1;
    while (j >= start && array[j] > currentValue) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = currentValue;
  }
}

void hybridQuickSort(std::vector<int> &array, int start, int end, int depth,
                     int maxDepth, int threshold = 16) {
  if (depth == maxDepth) {
    heapSort(array, 1, array.size());
    return;
  }
  if (end - start <= threshold) {
    insertionSort(array, start, end);
    return;
  }
  if (start < end) {
    int pivotIndex = partition(array, start, end);
    hybridQuickSort(array, start, pivotIndex, depth + 1, maxDepth);
    hybridQuickSort(array, pivotIndex + 1, end, depth + 1, maxDepth);
  }
}

void introSort(std::vector<int> &array) {
  hybridQuickSort(array, 1, array.size(), 0, 2 * log2(array.size()));
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int arraySize;
  std::cin >> arraySize;
  std::vector<int> array(arraySize + 1);
  for (int i = 1; i <= arraySize; ++i) {
    std::cin >> array[i];
  }
  introSort(array);
  for (int i = 1; i <= arraySize; ++i) {
    std::cout << array[i] << ' ';
  }

  return 0;
}
