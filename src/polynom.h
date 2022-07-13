#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct polynom_header Polynom;

/*************
 * Interface *
 *************/

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
char *polynom_to_string(Polynom p);
double *polynom_to_array(Polynom p, size_t *size);
Polynom polynom_from_array(double *buf, size_t len);

/* Degree */
size_t polynom_degree(Polynom p);
int polynom_degree_compare(Polynom p1, Polynom p2);
size_t polynom_degree_max(Polynom p1, Polynom p2);

/* Equality and order */
bool polynom_equal(Polynom p1, Polynom p2);
int polynom_compare(Polynom p1, Polynom p2);

/* Arithmetic */
double polynom_evaluate(Polynom p, double x);
Polynom polynom_add(Polynom p1, Polynom p2);
Polynom polynom_subtract(Polynom p1, Polynom p2);
Polynom polynom_multiply_calar(Polynom p, double c);
Polynom polynom_multiply_vector(Polynom p1, Polynom p2);
Polynom polynom_divide_scalar(Polynom p, double c);
Polynom polynom_divide_vector(Polynom p1, Polynom p2);
Polynom polynom_power(Polynom p, int k);
Polynom polynom_scale(Polynom p, int k);
Polynom polynom_reduce(Polynom p);

/* Calculus */
Polynom polynom_derive(Polynom p);
Polynom polynom_integrate(Polynom p);

#endif
