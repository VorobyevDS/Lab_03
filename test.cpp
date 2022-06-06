#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void
test_same() {
    double min = 0;
    double max = 0;
    find_minmax({2, 2, 2}, min, max);
    assert(min == 2);
    assert(max == 2);
}
void
test_uno() {
    double min = 0;
    double max = 0;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}
void
bin_height_test(double Height, const auto bin_count){
    const auto IMAGE_HEIGHT=700;
    assert(Height>0 & bin_count>0);
}

void
test_Individual_1() {
    bin_height_test(100, 2);
}
void
test_Individual_2() {
    bin_height_test(900, 4);
}

int
main() {
    test_positive();
    test_negative();
    test_same();
    test_uno();
    test_Individual_1();
    test_Individual_2();
}
