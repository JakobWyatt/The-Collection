#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../include/tc/matrix_view.hpp"
#include "../include/tc/random.hpp"
#include "../include/tc/matrix_view.hpp"
#include "../include/tc/matrix_ops.hpp"
#include "../include/tc/math.hpp"
#include "../include/tc/matrix_ops_f.hpp"

template<typename T>
std::vector<T> underlying_view_data(tc::matrix_view::matrix_view<T> view) {
    return std::vector<T>(view.data(), view.data() + view.size());
}

int main () {
    std::vector<double>::size_type test_matrix_height = 5000;
    std::vector<double>::size_type test_matrix_width = 5000;
    std::vector<double> data(test_matrix_height * test_matrix_width);

    std::generate(data.begin(), data.end(), tc::random::random_standard_normal<double>);

    tc::matrix_view::matrix_view<double> matrix(data.data(), test_matrix_height, test_matrix_width);

    auto output1_data = data;
    auto output2_data = data;
    tc::matrix_view::matrix_view<double> output1(output1_data.data(), test_matrix_height, test_matrix_width);
    tc::matrix_view::matrix_view<double> output2(output2_data.data(), test_matrix_height, test_matrix_width);

    auto before_slow_test = std::chrono::steady_clock::now();
    tc::matrix_ops::m_fn(matrix, output1, tc::math::sigmoid<double>);
    auto after_slow_test = std::chrono::steady_clock::now();
    std::chrono::milliseconds slow_time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(after_slow_test - before_slow_test);

    auto before_fast_test = std::chrono::steady_clock::now();
    tc::matrix_ops_f::m_fn(matrix, output2, tc::math::sigmoid<double>);
    auto after_fast_test = std::chrono::steady_clock::now();
    std::chrono::milliseconds fast_time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(after_fast_test - before_fast_test);

    assert(underlying_view_data(output1) == underlying_view_data(output2));

    std::cout << "Slow testing took: " << slow_time_taken.count() << " ms\n";
    std::cout << "Fast testing took: " << fast_time_taken.count() << " ms\n";

    return 0;
}
