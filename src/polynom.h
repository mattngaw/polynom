#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct polynom_header *Polynom;

/* Create and destroy */
Polynom polynom_new();
Polynom polynom_copy(Polynom p);
Polynom polynom_zero();
Polynom polynom_one();
Polynom polynom_x();
Polynom polynom_x_to_the(size_t k);
void polynom_destroy(Polynom p);

/* Coefficients */
double polynom_coeff_get(Polynom p, size_t i);
void polynom_coeff_set(Polynom p, size_t i, double a);
void polynom_to_string(Polynom p, char *buf);
void polynom_to_array(Polynom p, double *buf);
Polynom polynom_from_array(double *buf);

/* Degree */
size_t polynom_degree(Polynom p);
int polynom_degree_compare(Polynom p);

/* Equality and order */
bool polynom_equal(Polynom p1, Polynom p2);
int polynom_compare(Polynom p1, Polynom p2);

/* Arithmetic */
double polynom_evaluate(Polynom p, double x);
void polynom_add(Polynom q, Polynom p1, Polynom p2);
void polynom_subtract(Polynom q, Polynom p1, Polynom p2);
void polynom_multiply_scalar(Polynom q, Polynom p1, double c);
void polynom_multiply_vector(Polynom q, Polynom p1, Polynom p2);
void polynom_divide_scalar(Polynom q, Polynom p1, Polynom p2);
void polynom_divide_vector(Polynom q, Polynom p1, Polynom p2);
void polynom_power(Polynom q, Polynom p, int k);
void polynom_scale(Polynom q, size_t k);
void polynom_reduce(Polynom q, Polynom p);

/* Calculus */
void polynom_derive(Polynom q, Polynom p);
void polynom_integrate(Polynom q, Polynom p);
