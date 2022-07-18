#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "../src/polynom.h"

#if defined(QUIET)
    #define debug_printf(...) do {} while(false)
#else
    #define debug_printf(...) printf(__VA_ARGS__)
#endif

void new_test() {
    Polynom p = polynom_new();
    polynom_destroy(p);
}

void zero_test() {
    Polynom p = polynom_zero();
    assert(polynom_evaluate(p, 10.0) == 0.0);
    polynom_destroy(p);
}

void one_test() {
    Polynom p = polynom_one();
    assert(polynom_evaluate(p, 10.0) == 1.0);
    polynom_destroy(p);
}

void x_test() {
    Polynom p = polynom_x();
    assert(polynom_evaluate(p, 10.0) == 10.0);
    polynom_destroy(p);
}

void x_to_the_test() {
    Polynom p = polynom_x_to_the((size_t)3);
    assert(polynom_evaluate(p, 10.0) == 1000.0);
    polynom_destroy(p);
}

void coeff_get_test() {
    Polynom p = polynom_x_to_the((size_t)3);
    assert(polynom_coeff_get(p, 3) == 1.0);
    assert(polynom_coeff_get(p, 4) == 0.0);
    assert(polynom_coeff_get(p, 2) == 0.0);
    polynom_destroy(p);
}

void coeff_set_test() {
    Polynom p = polynom_x_to_the((size_t)3);
    polynom_coeff_set(p, 3, 5.0);
    polynom_coeff_set(p, 2, 4.0);
    polynom_coeff_set(p, 0, 1.0);
    assert(polynom_coeff_get(p, 4) == 0.0);
    assert(polynom_coeff_get(p, 3) == 5.0);
    assert(polynom_coeff_get(p, 2) == 4.0);
    assert(polynom_coeff_get(p, 1) == 0.0);
    assert(polynom_coeff_get(p, 0) == 1.0);
    polynom_destroy(p);
}

void degree_test() {
    Polynom p = polynom_x_to_the(3);
    assert(polynom_degree(p) == 3);
    polynom_coeff_set(p, 4, 2.0);
    assert(polynom_degree(p) == 4);
    polynom_coeff_set(p, 1000, 3.0);
    assert(polynom_degree(p) == 1000);
    polynom_coeff_set(p, 1000, 0.0);
    assert(polynom_degree(p) == 4);
    polynom_coeff_set(p, 4, 0.0);
    assert(polynom_degree(p) == 3);
    polynom_coeff_set(p, 3, 0.0);
    assert(polynom_degree(p) == 0);
    polynom_destroy(p);
}

void degree_compare_test() {
    Polynom p1 = polynom_x_to_the(4);
    Polynom p2 = polynom_x_to_the(2);
    Polynom p3 = polynom_x_to_the(2);
    assert(polynom_degree_compare(p1, p2) == 1);
    assert(polynom_degree_compare(p2, p1) == -1);
    assert(polynom_degree_compare(p2, p3) == 0);
    polynom_destroy(p1);
    polynom_destroy(p2);
    polynom_destroy(p3);
}

void degree_max_test() {
    Polynom p1 = polynom_x_to_the(4);
    Polynom p2 = polynom_x_to_the(2);
    Polynom p3 = polynom_x_to_the(2);
    assert(polynom_degree_max(p1, p2) == 4);
    assert(polynom_degree_max(p2, p1) == 4);
    assert(polynom_degree_max(p2, p3) == 2);
    polynom_destroy(p1);
    polynom_destroy(p2);
    polynom_destroy(p3);
}

void equal_test() {
    Polynom p1 = polynom_x();
    Polynom p2 = polynom_x();
    Polynom p3 = polynom_one();
    assert(polynom_equal(p1, p2));
    assert(polynom_equal(p2, p1));
    assert(!polynom_equal(p1, p3));
    assert(!polynom_equal(p3, p1));
    polynom_destroy(p1);
    polynom_destroy(p2);
    polynom_destroy(p3);
}

int main() {
    debug_printf("\n");
    debug_printf("*************************\n");
    debug_printf("* Running polynom tests *\n");
    debug_printf("*************************\n\n");

    debug_printf("Testing new_test... ");
    fflush(stdout);
    new_test();
    debug_printf("\t\tDone!\n");

    debug_printf("Testing zero_test... ");
    fflush(stdout);
    zero_test();
    debug_printf("\t\tDone!\n");

    debug_printf("Testing one_test... ");
    fflush(stdout);
    one_test();
    debug_printf("\t\tDone!\n");

    debug_printf("Testing x_test... ");
    fflush(stdout);
    x_test();
    debug_printf("\t\tDone!\n");

    debug_printf("Testing x_to_the_test... ");
    fflush(stdout);
    x_to_the_test();
    debug_printf("\tDone!\n");

    debug_printf("Testing coeff_get_test... ");
    fflush(stdout);
    coeff_get_test();
    debug_printf("\tDone!\n");

    debug_printf("Testing coeff_set_test... ");
    fflush(stdout);
    coeff_set_test();
    debug_printf("\tDone!\n");

    // to_string

    // to_array

    // from_array

    debug_printf("Testing degree... ");
    fflush(stdout);
    degree_test();
    debug_printf("\t\tDone!\n");

    debug_printf("Testing degree_compare... ");
    fflush(stdout);
    degree_compare_test();
    debug_printf("\tDone!\n");

    debug_printf("Testing degree_max... ");
    fflush(stdout);
    degree_max_test();
    debug_printf("\t\tDone!\n");

    debug_printf("Testing equal... ");
    fflush(stdout);
    equal_test();
    debug_printf("\t\tDone!\n");

    debug_printf("\n");
    debug_printf("All tests completed successfully, exiting.\n\n");
    return 0;
}

