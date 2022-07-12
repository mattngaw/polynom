#include <string.h>

#include "polynom.h"

struct polynom_header {
    double *terms;
    size_t degree;
    size_t terms_length;
}

/********************
 * Helper functions *
 ********************/



/******************
 * Implementation *
 ******************/

/**
 * @brief Initializes a polynomial
 * 
 * @return An initialized polynomial with no guarantees about its coefficients ()
 */
Polynom polynom_new() {
    Polynom q = malloc(sizeof(struct polynom_header));
    if (q == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    q->terms = malloc(sizeof(double));
    q->degree = 0;
    q->terms_length = 0;
    return q;
}

/**
 * @brief Creates a new instance of a polynomial that is a copy of p
 * 
 * @param[in] p Polynomial to be copied
 * @return The copied polynomial
 */
Polynom polynom_copy(Polynom p) {
    Polynom q = polynom_new();
    q->terms = malloc(sizeof(double) * p->terms_length);
    memcpy(q->terms, p->terms, sizeof(double) * p->terms_length);
    q->degree = p->degree;
    q->terms_length = p->terms_length;
    return q;
}

/**
 * @brief Returns 0.0 * x^0
 * 
 * @return Zero
 */
Polynom polynom_zero() {
    Polynom q = polynom_new();
    q->terms[0] = 0.0;
    return q;
}

/**
 * @brief Returns 1.0 * x^0
 * 
 * @return One
 */
Polynom polynom_one() {
    Polynom q = polynom_new();
    q->terms[0] = 1.0;
    return q;
}

/**
 * @brief Returns 1.0 * x^1 + 0.0 * x^0
 * 
 * @return x
 */
Polynom polynom_x() {
    Polynom q = polynom_new();
    q->degree = 1;
    q->terms_length = 2;
    q->terms = calloc(sizeof(double) * q->terms_length);
    q->terms[1] = 1.0;
    return q;
}

/**
 * @brief Returns 1.0 * x^k + ... + 0.0 * x^0
 * 
 * @param[in] k The power to which x is raised
 * @return x^k
 */
Polynom polynom_x_to_the(size_t k) {
    Polynom q = polynom_new();
    q->degree = k;
    q->terms_length = k + 1;
    q->terms = calloc(sizeof(double) * q->terms_length);
    q->terms[k] = 1.0;
    return q;
}

/**
 * @brief Frees the space taken by the polynomial back to the OS
 * 
 * @param[in] p Polynomial to be freed
 */
void polynom_destroy(Polynom p) {
    if (p == NULL) {
        fprintf(stderr, "attempting to destroy a NULL Polynom\n");
        exit(-1);
    }
    free(p->terms);
    free(p)
}

/* Coefficients */
double polynom_coeff_get(Polynom p, size_t i);
void polynom_coeff_set(Polynom p, size_t i, double x);

/* Degree */
size_t polynom_degree_get(Polynom p);
int polynom_degree_compare(Polynom p);

/* Equality and order */
bool polynom_equal(Polynom p1, Polynom p2);
int polynom_compare(Polynom p1, Polynom p2);

/* Arithmetic */
double polynom_evaluate(Polynom p, double x);
void polynom_add(Polynom q, Polynom p1, Polynom p2);
void polynom_subtract(Polynom q, Polynom p1, Polynom p2);
void polynom_multiply_scalar(Polynom q, Polynom p1, double x);
void polynom_multiply_vector(Polynom q, Polynom p1, Polynom p2);
void polynom_divide_scalar(Polynom q, Polynom p1, Polynom p2);
void polynom_divide_vector(Polynom q, Polynom p1, Polynom p2);
void polynom_power(Polynom q, Polynom p, int x);
void polynom_scale(Polynom q, size_t k);
void polynom_reduce(Polynom q, Polynom p);

/* Calculus */
void polynom_derive(Polynom q, Polynom p);
void polynom_integrate(Polynom q, Polynom p);

/* Conversion */
void polynom_to_string(Polynom p, char *buf);
void polynom_to_array(Polynom p, double *buf);
Polynom polynom_from_array(double *buf);