#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <utility>
#include <cstddef>
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

template<typename Function, typename... Args>
std::chrono::milliseconds time_function (Function function, Args... args) {
    auto before_test = std::chrono::steady_clock::now();
    function(args...);
    auto after_test = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(after_test - before_test);
}

int main () {
    std::vector<double>::size_type test_matrix_height = 5000;
    std::vector<double>::size_type test_matrix_width = 5000;
    std::vector<double> data(test_matrix_height * test_matrix_width);
    std::generate(data.begin(), data.end(), tc::random::random_standard_normal<double>);

    tc::matrix_view::matrix_view<double> matrix(data.data(), test_matrix_height, test_matrix_width);

    std::vector<double> output_data_1(test_matrix_height * test_matrix_width);
    tc::matrix_view::matrix_view<double> output_1(output_data_1.data(), test_matrix_height, test_matrix_width);
    std::vector<double> output_data_2(test_matrix_height * test_matrix_width);
    tc::matrix_view::matrix_view<double> output_2(output_data_2.data(), test_matrix_height, test_matrix_width);

    std::cout << "Slow function application: " <<
        time_function(tc::matrix_ops::m_fn<std::size_t, tc::matrix_view::matrix_view<double>, tc::matrix_view::matrix_view<double>, double(double)>,
        matrix, output_1, tc::math::sigmoid<double>).count() << " ms\n";
    std::cout << "Fast function application: " <<
        time_function(tc::matrix_ops_f::m_fn<std::size_t, tc::matrix_view::matrix_view<double>, tc::matrix_view::matrix_view<double>, double(double)>,
        matrix, output_2, tc::math::sigmoid<double>).count() << " ms\n";
    assert(underlying_view_data(output_1) == underlying_view_data(output_2));

    std::cout << "Slow copy: " <<
        time_function(tc::matrix_ops::m_cpy<std::size_t, tc::matrix_view::matrix_view<double>, tc::matrix_view::matrix_view<double>>,
        matrix, output_1).count() << " ms\n";
    std::cout << "Fast copy: " <<
        time_function(tc::matrix_ops_f::m_cpy<std::size_t, tc::matrix_view::matrix_view<double>, tc::matrix_view::matrix_view<double>>,
        matrix, output_2).count() << " ms\n";
    assert(underlying_view_data(output_1) == underlying_view_data(output_2));

    std::cout << "Slow fill: " <<
        time_function(tc::matrix_ops::m_fill<std::size_t, tc::matrix_view::matrix_view<double>, double>,
        output_1, 4.6).count() << " ms\n";
    std::cout << "Fast fill: " <<
        time_function(tc::matrix_ops_f::m_fill<std::size_t, tc::matrix_view::matrix_view<double>, double>,
        output_2, 4.6).count() << " ms\n";
    assert(underlying_view_data(output_1) == underlying_view_data(output_2));

    return 0;
}
