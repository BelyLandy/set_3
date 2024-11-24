#include <iostream>
#include <algorithm>
#include <vector>

void mergeSegments(int left, int right, std::vector<int> &array)
{

  int mid = (left + right) / 2;

  int leftSize = mid - left;
  int rightSize = right - mid;

  std::vector<int> leftSegment(leftSize), rightSegment(rightSize);

  for (int i = 0; i < leftSize; ++i)
  {
    leftSegment[i] = array[left + i];
  }

  for (int j = 0; j < rightSize; ++j)
  {
    rightSegment[j] = array[mid + j];
  }

  int i = 0, j = 0, k = left;

  while (i < leftSize && j < rightSize)
  {
    if (leftSegment[i] <= rightSegment[j])
    {
      array[k] = leftSegment[i];
      ++i;
    }
    else
    {
      array[k] = rightSegment[j];
      ++j;
    }
    ++k;
  }

  while (i < leftSize)
  {
    array[k] = leftSegment[i];
    ++i;
    ++k;
  }

  while (j < rightSize)
  {
    array[k] = rightSegment[j];
    ++j;
    ++k;
  }
}

void insertionSort(int left, int right, std::vector<int> &array)
{
  for (int i = left; i < right; ++i)
  {
    int current = array[i];
    int j = i - 1;
    while (j >= left && array[j] > current)
    {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = current;
  }
}

void hybridMergeSort(int left, int right, std::vector<int> &array, int threshold)
{
  if (left + 1 >= right)
  {
    return;
  }
  if (right - left <= threshold)
  {
    insertionSort(left, right, array);
    return;
  }

  int mid = (left + right) / 2;

  hybridMergeSort(left, mid, array, threshold);
  hybridMergeSort(mid, right, array, threshold);

  mergeSegments(left, right, array);
}

void mergeSort(int left, int right, std::vector<int> &array)
{
  if (left + 1 >= right)
  {
    return;
  }
  int mid = (left + right) / 2;

  mergeSort(left, mid, array);
  mergeSort(mid, right, array);
  mergeSegments(left, right, array);
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int arraySize;
  std::cin >> arraySize;
  std::vector<int> array(arraySize);

  for (int i = 0; i < arraySize; ++i)
  {
    std::cin >> array[i];
  }

  hybridMergeSort(0, arraySize, array, 15);

  for (int i = 0; i < arraySize; ++i)
  {
    std::cout << array[i] << ' ';
  }

  return 0;
}