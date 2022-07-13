#include <assert.h>
#include <math.h>
#include <stdio.h>
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
};

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
 * @brief Frees the memory taken by the polynomial
 * 
 * @param[in] p Polynomial to be freed
 */
void polynom_destroy(Polynom p) {
    if (p == NULL) {
        fprintf(stderr, "attempting to destroy a NULL Polynom\n");
        exit(-1);
    }
    free(p->terms);
    free(p);
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

/**
 * @brief Returns the degree of a polynomial
 * 
 * @param[in] p The polynomial
 * @return The degree
 */
size_t polynom_degree(Polynom p) {
    return p->degree;
}

/**
 * @brief Compares the degrees of two polynomials
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return deg(p1) < deg(p2) -> -1
 *         deg(p1) == deg(p2) -> 0
 *         deg(p1) > deg(p2) -> 1
 */
int polynom_degree_compare(Polynom p1, Polynom p2) {
    if (p1->degree < p2->degree) return -1;
    else if (p1->degree == p2->degree) return 0;
    else return 1;
}

size_t polynom_degree_max(Polynom p1, Polynom p2) {
    if (polynom_degree_compare(p1, p2) == -1) return p2->degree;
    else return p1->degree;
}

/* Equality */

/**
 * @brief Returns whether p1 == p2
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return p1 == p2
 */
bool polynom_equal(Polynom p1, Polynom p2) {
    if (p1->degree != p2->degree) return false;
    for (int i = 0; i <= p1->degree; i++) {
        if (p1->terms[i] != p2->terms[i]) return false;
    }
    return true;
}

/* Arithmetic */

/**
 * @brief Returns the result of evaluating the polynomial at x via 
 *        Horner's method
 * 
 * @param[in] p The polynomial to evaluate
 * @param[in] x The value at which to evaluate p
 * @return p(x)
 */
double polynom_evaluate(Polynom p, double x) {
    double result = p->terms[p->degree];
    for (int i = p->degree - 1; i >= 0; i--) {
        result *= x;
        result += p->terms[i];
    }
    return result;
}

/**
 * @brief q(x) = p1(x) + p2(x)
 * 
 * @param[out] q The resulting polynomial
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 */
void polynom_add(Polynom q, Polynom p1, Polynom p2) {
    size_t deg_max = polynom_degree_max(p1, p2);
    size_t size_min = (deg_max+1);
    q->degree = deg_max;
    if (q->terms_length < size_min) {
        q->terms = malloc(sizeof(double) * size_min);
        q->terms_length = size_min;
    } else {
        memset(q->terms, 0, sizeof(double) * q->terms_length);
    }
    for (int i = 0; i <= deg_max; i++) {
        q->terms[i] = polynom_coeff_get(p1, i) + polynom_coeff_get(p2, i);
    }
    return;
}

/**
 * @brief q(x) = p1(x) - p2(x)
 * 
 * @param[out] q The resulting polynomial
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 */
void polynom_subtract(Polynom q, Polynom p1, Polynom p2) {
    size_t deg_max = polynom_degree_max(p1, p2);
    size_t size_min = (deg_max+1);
    q->degree = deg_max;
    if (q->terms_length < size_min) {
        q->terms = malloc(sizeof(double) * size_min);
        q->terms_length = size_min;
    } else {
        memset(q->terms, 0, sizeof(double) * q->terms_length);
    }
    for (int i = 0; i <= deg_max; i++) {
        q->terms[i] = polynom_coeff_get(p1, i) - polynom_coeff_get(p2, i);
    }
    return;
}

/**
 * @brief q(x) = p(x) * c
 * 
 * @param[out] q The resulting polynomial
 * @param[in] p The polynomial
 * @param[in] c The constant
 */
void polynom_multiply_scalar(Polynom q, Polynom p, double c) {
    size_t deg = p->degree;
    for (int i = 0; i <= deg; i++) {
        q->terms[i] = polynom_coeff_get(p, i) * c;
    }
    return;
}

/** TODO:
 * @brief 
 * 
 * @param[] q
 * @param[] p1
 * @param[] p2
 */
void polynom_multiply_vector(Polynom q, Polynom p1, Polynom p2) {
    return;
}

/**
 * @brief q(x) = p(x) / c
 * 
 * @param[out] q The resulting polynomial
 * @param[in] p The polynomial
 * @param[in] c The constant
 */
void polynom_divide_scalar(Polynom q, Polynom p, double c) {
    size_t deg = p->degree;
    for (int i = 0; i <= deg; i++) {
        q->terms[i] = polynom_coeff_get(p, i) / c;
    }
    return;
}

/** TODO:
 * @brief 
 * 
 * @param[] q
 * @param[] p1
 * @param[] p2
 */
void polynom_divide_vector(Polynom q, Polynom p1, Polynom p2);

/** TODO:
 * @brief 
 * 
 * @param[] q
 * @param[] p
 * @param[] k
 */
void polynom_power(Polynom q, Polynom p, int k);

/** 
 * @brief q = x^k
 * 
 * @param[out] q The resulting polynomial
 * @param[in] p The polynomial
 * @param[in] k The power
 */
void polynom_scale(Polynom q, Polynom p, size_t k) {

}

/**
 * @brief 
 * 
 * @param[] q
 * @param[] p
 */
void polynom_reduce(Polynom q, Polynom p);

/* Calculus */

/** TODO:
 * @brief 
 * 
 * @param[] q
 * @param[] p
 */
void polynom_derive(Polynom q, Polynom p);

/** TODO:
 * @brief 
 * 
 * @param[] q
 * @param[] p
 */
void polynom_integrate(Polynom q, Polynom p);
