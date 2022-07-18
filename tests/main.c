#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "../src/polynom.h"

void polynom_new_test() {
    Polynom p = polynom_new();
    char *p_str = polynom_to_string(p);
    printf("%s", p_str);
    free(p_str);
    polynom_destroy(p);
}

void polynom_one_test() {
    Polynom p = polynom_new();
    char *p_str = polynom_to_string(p);
    printf("%s", p_str);
    free(p_str);
    polynom_destroy(p);
}

int main() {
    create_test();
}

