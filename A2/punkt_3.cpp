#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>

class ArrayGenerator {
public:
    static std::vector<int> generateRandomArray(int size, int minValue, int maxValue) {
        std::vector<int> array(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minValue, maxValue);

        for (int &value : array) {
            value = dis(gen);
        }
        return array;
    }

    static std::vector<int> generateReverseSortedArray(int size) {
        std::vector<int> array(size);
        for (int i = 0; i < size; ++i) {
            array[i] = size - i;
        }
        return array;
    }

    static std::vector<int> generateNearlySortedArray(int size, int swaps) {
        std::vector<int> array(size);
        for (int i = 0; i < size; ++i) {
            array[i] = i;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size - 1);

        for (int i = 0; i < swaps; ++i) {
            int idx1 = dis(gen);
            int idx2 = dis(gen);
            std::swap(array[idx1], array[idx2]);
        }
        return array;
    }
};

class SortTester {
public:
    static double measureHybridMergeSort(std::vector<int> array, int threshold) {
        auto start = std::chrono::high_resolution_clock::now();
        hybridMergeSort(0, array.size(), array, threshold);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        return elapsed.count();
    }

private:
    static void insertionSort(int left, int right, std::vector<int> &array) {
        for (int i = left; i < right; ++i) {
            int current = array[i];
            int j = i - 1;
            while (j >= left && array[j] > current) {
                array[j + 1] = array[j];
                --j;
            }
            array[j + 1] = current;
        }
    }

    static void mergeSegments(int left, int right, std::vector<int> &array) {
        int mid = (left + right) / 2;
        int leftSize = mid - left;
        int rightSize = right - mid;
        std::vector<int> leftSegment(leftSize), rightSegment(rightSize);

        for (int i = 0; i < leftSize; ++i) {
            leftSegment[i] = array[left + i];
        }

        for (int j = 0; j < rightSize; ++j) {
            rightSegment[j] = array[mid + j];
        }

        int i = 0, j = 0, k = left;

        while (i < leftSize && j < rightSize) {
            if (leftSegment[i] <= rightSegment[j]) {
                array[k] = leftSegment[i];
                ++i;
            } else {
                array[k] = rightSegment[j];
                ++j;
            }
            ++k;
        }

        while (i < leftSize) {
            array[k] = leftSegment[i];
            ++i;
            ++k;
        }

        while (j < rightSize) {
            array[k] = rightSegment[j];
            ++j;
            ++k;
        }
    }

    static void hybridMergeSort(int left, int right, std::vector<int> &array, int threshold) {
        if (left + 1 >= right) {
            return;
        }
        if (right - left <= threshold) {
            insertionSort(left, right, array);
            return;
        }

        int mid = (left + right) / 2;

        hybridMergeSort(left, mid, array, threshold);
        hybridMergeSort(mid, right, array, threshold);

        mergeSegments(left, right, array);
    }
};

int main() {
    const int minSize = 500;
    const int maxSize = 10000;
    const int stepSize = 500;
    const int minValue = 0;
    const int maxValue = 6000;
    const int swaps = 50;

    std::vector<int> thresholds = {5, 10, 20, 30, 50};

    std::cout << std::fixed << std::setprecision(6);
    
    for (int threshold : thresholds) {
        std::cout << "Threshold: " << threshold << '\n';

        for (int size = minSize; size <= maxSize; size += stepSize) {
            std::vector<int> randomArray = ArrayGenerator::generateRandomArray(size, minValue, maxValue);
            std::vector<int> reverseArray = ArrayGenerator::generateReverseSortedArray(size);
            std::vector<int> nearlySortedArray = ArrayGenerator::generateNearlySortedArray(size, swaps);

            double randomTime = SortTester::measureHybridMergeSort(randomArray, threshold);
            double reverseTime = SortTester::measureHybridMergeSort(reverseArray, threshold);
            double nearlySortedTime = SortTester::measureHybridMergeSort(nearlySortedArray, threshold);

            std::cout << "Size: " << size << ", Random: " << randomTime
                      << ", Reverse: " << reverseTime
                      << ", Nearly Sorted: " << nearlySortedTime << '\n';
        }
        std::cout << "\n";
    }

    return 0;
}
