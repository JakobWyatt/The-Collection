#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../include/tc/matrix_view.hpp"
#include "../include/tc/random.hpp"
#include "../include/tc/matrix_view.hpp"
#include "../include/tc/matrix_ops.hpp"
#include "../include/tc/math.hpp"

int main () {
    std::vector<double>::size_type test_matrix_height = 5000;
    std::vector<double>::size_type test_matrix_width = 5000;
    std::vector<double> data(test_matrix_height * test_matrix_width);

    std::generate(data.begin(), data.end(), tc::random::random_standard_normal<double>);

    tc::matrix_view::matrix_view<double> matrix(data.data(), test_matrix_height, test_matrix_width);

    auto before_slow_test = std::chrono::steady_clock::now();
    tc::matrix_ops::m_fn(matrix, matrix, tc::math::sigmoid<double>);
    auto after_slow_test = std::chrono::steady_clock::now();
    std::chrono::milliseconds slow_time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(after_slow_test - before_slow_test);

    std::cout << "Slow testing took: " << slow_time_taken.count() << " ms\n";

    return 0;
}
