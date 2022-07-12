#include <assert.h>
#include <string.h>

#include "polynom.h"

#ifdef DEBUG
#define debug_assert(expr) assert(expr)
#else
#define debug_assert(expr) do {} while(false)
#endif

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

/* Create and destroy */

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
    q->terms = calloc(sizeof(double), q->terms_length);
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
    q->terms = calloc(sizeof(double), q->terms_length);
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

/**
 * @brief Gets the ith coefficient of a polynomial
 * 
 * @param[in] p The polynomial
 * @param[in] i The coefficient index
 * 
 * @return The coefficient
 */
double polynom_coeff_get(Polynom p, size_t i) {
    debug_assert(i < p->terms_length);
    if (i > p->degree) return 0.0;
    return p->terms[i];
}

/**
 * @brief Sets the ith coefficient of a polynomial
 * 
 * @param[in] p The polynomial
 * @param[in] i The coefficient index
 * @param[in] a The new coefficient value 
 */
void polynom_coeff_set(Polynom p, size_t i, double a) {
    if (i >= p->terms_length) {
        double *temp = p->terms;
        p->terms = calloc(sizeof(double), i+1);
        memcpy(p->terms, temp, sizeof(double) * p->terms_length);
    }
    p->terms[i] = a;
    p->degree = i;
    return;
}

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