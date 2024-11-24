#include "ArrayGenerator.cpp"
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

class SortTester {
public:
    void run(const std::string& filename) {
        std::ofstream csv{filename};
        csv << "n;array_type;sorting_type;time\n";

        std::vector<std::string> types{"random", "reversed", "almost_sorted"};
        ArrayGenerator generator{};
        std::vector<std::vector<int>> data{
            generator.get_random_array(),
            generator.get_reverse_sorted_array(),
            generator.get_almost_sorted_array()
        };

        std::vector<std::pair<std::function<void(std::vector<int>&, size_t, size_t)>, std::string>> sort_algorithms = {
            {quick_sort, "quick"},
            {intro_sort, "intro"}
        };

        for (const auto& [sort_algo, sort_name] : sort_algorithms) {
            for (size_t type = 0; type < types.size(); ++type) {
                for (size_t n = 500; n <= 15000; n += 500) {
                    run_sorting_test(csv, data[type], n, types[type], sort_algo, sort_name);
                }
            }
        }
    }

private:
    void run_sorting_test(std::ofstream& csv, const std::vector<int>& input_data, size_t n, const std::string& array_type,
                          const std::function<void(std::vector<int>&, size_t, size_t)>& sort_algo, const std::string& sort_name) {
        std::vector<int> v{input_data.begin(), input_data.begin() + n};

        auto start = std::chrono::high_resolution_clock::now();
        sort_algo(v, 0, n); // Sorting call
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        csv << n << ";\"" << array_type << "\";\"" << sort_name << "\";" << elapsed.count() << '\n';
    }
};

int main() {
    Tester test{};
    test.run("tested_data.csv");
}
