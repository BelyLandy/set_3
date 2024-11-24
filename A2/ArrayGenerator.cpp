#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class ArrayGenerator {
public:
    ArrayGenerator(int maxSize, int valueRange)
        : maxSize(maxSize), valueRange(valueRange), engine(std::random_device{}()) {
        generateBaseArray();
    }

    // Генерация массива случайных значений
    std::vector<int> getRandomArray(int size) {
        if (size > maxSize) {
            throw std::invalid_argument("Size exceeds maximum allowed size.");
        }

        std::vector<int> randomArray(baseArray.begin(), baseArray.begin() + size);
        std::shuffle(randomArray.begin(), randomArray.end(), engine);
        return randomArray;
    }

    // Генерация массива, отсортированного в обратном порядке
    std::vector<int> getReversedArray(int size) {
        if (size > maxSize) {
            throw std::invalid_argument("Size exceeds maximum allowed size.");
        }

        std::vector<int> reversedArray(baseArray.begin(), baseArray.begin() + size);
        std::sort(reversedArray.begin(), reversedArray.end(), std::greater<int>());
        return reversedArray;
    }

    // Генерация "почти" отсортированного массива
    std::vector<int> getNearlySortedArray(int size, int swaps) {
        if (size > maxSize) {
            throw std::invalid_argument("Size exceeds maximum allowed size.");
        }

        std::vector<int> nearlySortedArray(baseArray.begin(), baseArray.begin() + size);
        std::sort(nearlySortedArray.begin(), nearlySortedArray.end());

        for (int i = 0; i < swaps; ++i) {
            int index1 = getRandomIndex(size);
            int index2 = getRandomIndex(size);
            std::swap(nearlySortedArray[index1], nearlySortedArray[index2]);
        }

        return nearlySortedArray;
    }

private:
    int maxSize;
    int valueRange;
    std::vector<int> baseArray;
    std::mt19937 engine;

    void generateBaseArray() {
        std::uniform_int_distribution<int> dist(0, valueRange);
        baseArray.resize(maxSize);
        for (int i = 0; i < maxSize; ++i) {
            baseArray[i] = dist(engine);
        }
    }

    int getRandomIndex(int size) {
        std::uniform_int_distribution<int> dist(0, size - 1);
        return dist(engine);
    }
};
