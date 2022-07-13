#include <assert.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "polynom.h"

#ifdef DEBUG
#define debug_assert(expr) assert(expr)
#define debug_printf(...) printf(__VA_ARGS__)
#else
// #define debug_assert(expr) do {} while(false)
#define debug_assert(expr) (sizeof(expr), 1)
#define debug_printf(...) (sizeof(__VA_ARGS__), -1)
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
 * @return An initialized polynomial with no guarantees about its coefficients
 */
Polynom polynom_new() {
    Polynom q;
    q.terms = malloc(sizeof(double));
    q.degree = 0;
    q.terms_length = 0;
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
    q.terms = malloc(sizeof(double) * p.terms_length);
    memcpy(q.terms, p.terms, sizeof(double) * p.terms_length);
    q.degree = p.degree;
    q.terms_length = p.terms_length;
    return q;
}

/**
 * @brief Returns 0.0 * x^0
 * 
 * @return Zero
 */
Polynom polynom_zero() {
    Polynom q = polynom_new();
    q.terms[0] = 0.0;
    return q;
}

/**
 * @brief Returns 1.0 * x^0
 * 
 * @return One
 */
Polynom polynom_one() {
    Polynom q = polynom_new();
    q.terms[0] = 1.0;
    return q;
}

/**
 * @brief Returns 1.0 * x^1 + 0.0 * x^0
 * 
 * @return x
 */
Polynom polynom_x() {
    Polynom q = polynom_new();
    q.degree = 1;
    q.terms_length = 2;
    q.terms = calloc(sizeof(double), q.terms_length);
    q.terms[1] = 1.0;
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
    q.degree = k;
    q.terms_length = k + 1;
    q.terms = calloc(sizeof(double), q.terms_length);
    q.terms[k] = 1.0;
    return q;
}

/**
 * @brief Frees the memory taken by the polynomial
 * 
 * @param[in] p Polynomial to be cleaned
 */
void polynom_clean(Polynom p) {
    if (p.terms == NULL) {
        fprintf(stderr, "attempting to free NULL terms\n");
        exit(-1);
    }
    free(p.terms);
    return;
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
    debug_assert(i < p.terms_length);
    if (i > p.degree) return 0.0;
    return p.terms[i];
}

/**
 * @brief Sets the ith coefficient of a ial
 * 
 * @param[in] p The polynomial
 * @param[in] i The coefficient index
 * @param[in] a The new coefficient value 
 */
void polynom_coeff_set(Polynom p, size_t i, double a) {
    if (i >= p.terms_length) {
        double *temp = p.terms;
        p.terms = calloc(sizeof(double), i+1);
        memcpy(p.terms, temp, sizeof(double) * p.terms_length);
    }
    p.terms[i] = a;
    p.degree = i;
    return;
}

/** TODO:
 * @brief 
 * 
 * @param[] p
 * @param[] buf
 */
char *polynom_to_string(Polynom p) {
    char *str = malloc(sizeof(char) * 10);
    return str;
}

/**
 * @brief Returns an array of coefficients indexed by their power
 * 
 * @param[in] p The polynomial
 * @param[out] size The size of the output buffer
 * @return The output buffer
 */
double *polynom_to_array(Polynom p, size_t *size) {
    double *buf = malloc(sizeof(double) * p.terms_length);
    memcpy(buf, p.terms, p.terms_length);
    *size = p.terms_length;
    return buf;
}

/** TODO:
 * @brief 
 * 
 * @param[] buf
 * @return Polynom 
 */
Polynom polynom_from_array(double *buf, size_t len) {
    Polynom q;
    return q;
}

/* Degree */

/**
 * @brief Returns the degree of a polynomial
 * 
 * @param[in] p The polynomial
 * @return The degree
 */
size_t polynom_degree(Polynom p) {
    return p.degree;
}

/**
 * @brief Compares the degrees of two polynomials
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return deg(p1) < deg(p2) . -1
 *         deg(p1) == deg(p2) . 0
 *         deg(p1) > deg(p2) . 1
 */
int polynom_degree_compare(Polynom p1, Polynom p2) {
    if (p1.degree < p2.degree) return -1;
    else if (p1.degree == p2.degree) return 0;
    else return 1;
}

size_t polynom_degree_max(Polynom p1, Polynom p2) {
    if (polynom_degree_compare(p1, p2) == -1) return p2.degree;
    else return p1.degree;
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
    if (p1.degree != p2.degree) return false;
    for (int i = 0; i <= p1.degree; i++) {
        if (p1.terms[i] != p2.terms[i]) return false;
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
    double result = p.terms[p.degree];
    for (int i = p.degree - 1; i >= 0; i--) {
        result *= x;
        result += p.terms[i];
    }
    return result;
}

/**
 * @brief q(x) = p1(x) + p2(x)
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return The resulting polynomial
 */
Polynom polynom_add(Polynom p1, Polynom p2) {
    Polynom q;
    size_t deg_max = polynom_degree_max(p1, p2);
    size_t size_min = (deg_max+1);
    q.degree = deg_max;
    if (q.terms_length < size_min) {
        q.terms = malloc(sizeof(double) * size_min);
        q.terms_length = size_min;
    } else {
        memset(q.terms, 0, sizeof(double) * q.terms_length);
    }
    for (int i = 0; i <= deg_max; i++) {
        q.terms[i] = polynom_coeff_get(p1, i) + polynom_coeff_get(p2, i);
    }
    return q;
}


/**
 * @brief q(x) = p1(x) - p2(x)
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return The resulting polynomial
 */
Polynom polynom_subtract(Polynom p1, Polynom p2) {
    Polynom q;
    size_t deg_max = polynom_degree_max(p1, p2);
    size_t size_min = (deg_max+1);
    q.degree = deg_max;
    if (q.terms_length < size_min) {
        q.terms = malloc(sizeof(double) * size_min);
        q.terms_length = size_min;
    } else {
        memset(q.terms, 0, sizeof(double) * q.terms_length);
    }
    for (int i = 0; i <= deg_max; i++) {
        q.terms[i] = polynom_coeff_get(p1, i) - polynom_coeff_get(p2, i);
    }
    return q;
}

/**
 * @brief q(x) = p(x) * c
 * 
 * @param[in] p The polynomial
 * @param[in] c The constant
 * @return The resulting polynomial
 */
Polynom polynom_multiply_scalar(Polynom p, double c) {
    Polynom q;
    size_t deg = p.degree;
    for (int i = 0; i <= deg; i++) {
        q.terms[i] = polynom_coeff_get(p, i) * c;
    }
    return q;
}

/** TODO:
 * @brief 
 * 
 * @param[] p1
 * @param[] p2
 * @return The resulting polynomial
 */
Polynom polynom_multiply_vector(Polynom p1, Polynom p2) {
    Polynom q;
    return q;
}

/**
 * @brief q(x) = p(x) / c
 * 
 * @param[in] p The polynomial
 * @param[in] c The constant
 * @return The resulting polynomial
 */
Polynom polynom_divide_scalar(Polynom p, double c) {
    Polynom q;
    size_t deg = p.degree;
    for (int i = 0; i <= deg; i++) {
        q.terms[i] = polynom_coeff_get(p, i) / c;
    }
    return q;
}

/** TODO:
 * @brief 
 * 
 * @param[] p1
 * @param[] p2
 * @return The resulting polynomial
 */
Polynom polynom_divide_vector(Polynom p1, Polynom p2) {
    Polynom q;
    return q;
}

/** TODO:
 * @brief 
 * 
 * @param[] p
 * @param[] k
 * @return The resulting polynomial
 */
Polynom polynom_power(Polynom p, int k) {
    Polynom q;
    return q;
}

/** 
 * @brief q(x) = p(x) * x^k
 * 
 * @param[in] p The polynomial
 * @param[in] k The power
 * @return The resulting polynomial
 */
Polynom polynom_scale(Polynom p, int k) {
    Polynom q;
    size_t new_deg = p.degree + k;
    size_t min_length = new_deg + 1;
    if (q.terms_length < min_length) {
        q.terms_length = min_length;
        q.terms = calloc(sizeof(double), min_length);
    }
    q.degree = new_deg;
    for (int i = 0; i <= p.degree; i++) {
        q.terms[i+k] = p.terms[i];
    }
    return q;
}

/** TODO:
 * @brief Compacts a polynomial to use minimal space
 * 
 * @param[in] p Polynomial to reduce
 */
Polynom polynom_reduce(Polynom p) {
    Polynom q;
    return q;
}

/* Calculus */

/** TODO:
 * @brief 
 * 
 * @param[] p
 * @return The resulting polynomial
 */
Polynom polynom_derive(Polynom p) {
    Polynom q;
    return q;
}

/** TODO:
 * @brief 
 * 
 * @param[] p
 * @return The resulting polynomial
 */
Polynom polynom_integrate(Polynom p) {
    Polynom q;
    return q;
}
