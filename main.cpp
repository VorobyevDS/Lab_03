#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <windows.h>
#include <curl/curl.h>
#include "histogram.h"
#include "svg.h"
using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double>
input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in,  bool prompt) {
    Input data;
    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt)
        cerr << "Enter column count: ";
    in >> data.bin_count;

    return data;
}

vector<size_t>
make_histogram(Input data){
    vector<size_t>result (data.bin_count);
    double min, max;
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count) {
            bin--;
        }
        result[bin]++;
    }
    return result;
}


void
show_histogram_text(const auto bins){
    const auto SCREEN_WIDTH = 80;
    const auto MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

}

int
main() {
    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
}
