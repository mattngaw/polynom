#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "polynom.h"

#if !defined(NAIVE) && !defined(FFT)
    #define NAIVE = 1
    #define FFT = 0
#elif defined(NAIVE) && defined(FFT)
    #define NAIVE = 0
    #define FFT = 1
#endif

#if defined(DEBUG)
    #define debug_assert(expr) assert(expr)
    #define debug_printf(...) printf(__VA_ARGS__)
#else
    #define debug_assert(expr) do {} while(false)
    #define debug_printf(...) do {} while(false)
#endif

struct polynom_header {
    double *terms;
    size_t degree;
    size_t terms_length;
};

/********************
 * Helper functions *
 ********************/

static void polynom_optimize(Polynom p, size_t min_length) {
    if (p->terms_length < min_length || p->terms_length > 2 * min_length) {
        double *temp = p->terms;
        p->terms = malloc(sizeof(double) * min_length);
        p->terms_length = min_length;
        free(temp);
    } else if (p->terms_length > min_length) {
        double *rest = &(p->terms[min_length]);
        size_t rest_length = p->terms_length - min_length;
        memset(rest, 0, sizeof(double) * rest_length);
    }
    return;
}

static void polynom_degree_fix(Polynom p, size_t degree_max) {
    for (size_t i = degree_max; i-- > 0; ) {
        if (p->terms[i] != 0.0) {
            p->degree = i; 
            return;
        }
    }
    p->degree = 0;
    return;
}

/******************
 * Implementation *
 ******************/

/* Create and destroy */

Polynom polynom_new() {
    Polynom q = malloc(sizeof(struct polynom_header));
    q->terms = malloc(sizeof(double));
    q->degree = 0;
    q->terms_length = 1;
    return q;
}

Polynom polynom_copy(Polynom p) {
    Polynom q = polynom_new();
    q->terms = malloc(sizeof(double) * p->terms_length);
    memcpy(q->terms, p->terms, sizeof(double) * p->terms_length);
    q->degree = p->degree;
    q->terms_length = p->terms_length;
    return q;
}

Polynom polynom_zero() {
    Polynom q = polynom_new();
    q->terms[0] = 0.0;
    return q;
}

Polynom polynom_one() {
    Polynom q = polynom_new();
    q->terms[0] = 1.0;
    return q;
}

Polynom polynom_x() {
    Polynom q = polynom_new();
    q->degree = 1;
    q->terms_length = 2;
    q->terms = calloc(sizeof(double), 2);
    q->terms[1] = 1.0;
    return q;
}

Polynom polynom_x_to_the(size_t k) {
    Polynom q = polynom_new();
    q->degree = k;
    q->terms_length = k + 1;
    q->terms = calloc(sizeof(double), q->terms_length);
    q->terms[k] = 1.0;
    return q;
}

void polynom_destroy(Polynom p) {
    if (p == NULL) {
        fprintf(stderr, "attempting to free NULL polynomial\n");
        exit(-1);
    }
    if (p->terms == NULL) {
        fprintf(stderr, "attempting to free NULL terms\n");
        exit(-1);
    }
    free(p->terms);
    free(p);
    return;
}



/* Coefficients */

inline double polynom_coeff_get(Polynom p, size_t i) {
    if (i > p->degree) return 0.0;
    return p->terms[i];
}

void polynom_coeff_set(Polynom p, size_t i, double a) {
    if (i >= p->terms_length) {
        double *temp = p->terms;
        p->terms = calloc(sizeof(double), i+1);
        memcpy(p->terms, temp, sizeof(double) * p->terms_length);
        p->terms_length = i+1;
        free(temp);
    }
    p->terms[i] = a;
    if (i > p->degree && a != 0.0) p->degree = i;
    else if (i == p->degree && a == 0.0) polynom_degree_fix(p, p->degree);
    return;
}

char *polynom_to_string(Polynom p) {
    char **terms_str = malloc(sizeof(char *) * p->degree);
    int total_len = 0;
    for (size_t i = p->degree+1; i-- > 0; ) {
        int len = snprintf(NULL, 0, "%.3fx^%zu ", p->terms[i], i);
        total_len += len + 3;
        terms_str[i] = malloc(sizeof(char) * len);
        snprintf(terms_str[i], len, "%.3fx^%zu ", p->terms[i], i);
    }
    char *str = malloc(sizeof(char) * total_len);
    str[0] = '\0';
    for (size_t i = p->degree+1; i-- > 0; ) {
        strcat(str, terms_str[i]);
        if (i > 0) strcat(str, " + ");
    }
    return str;
}

double *polynom_to_array(Polynom p, size_t *size) {
    size_t min_length = p->degree+1;
    double *buf = malloc(sizeof(double) * min_length);
    memcpy(buf, p->terms, min_length);
    *size = min_length;
    return buf;
}

// TODO
Polynom polynom_from_array(double *buf, size_t len) {
    Polynom q = polynom_new();
    return q;
}



/* Degree */

size_t polynom_degree(Polynom p) {
    return p->degree;
}

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

bool polynom_equal(Polynom p1, Polynom p2) {
    if (p1->degree != p2->degree) return false;
    for (size_t i = 0; i <= p1->degree; i++) {
        if (p1->terms[i] != p2->terms[i]) return false;
    }
    return true;
}



/* Arithmetic */

double polynom_evaluate(Polynom p, double x) {
    double result = p->terms[p->degree];
    for (size_t i = p->degree; i-- > 0; ) {
        result *= x;
        result += p->terms[i];
    }
    return result;
}

void polynom_add(Polynom q, Polynom p1, Polynom p2) {
    size_t deg_max = polynom_degree_max(p1, p2);
    size_t min_length = deg_max+1;
    polynom_optimize(q, min_length);
    polynom_degree_fix(q, deg_max);
    for (size_t i = 0; i <= deg_max; i++) {
        q->terms[i] = polynom_coeff_get(p1, i) + polynom_coeff_get(p2, i);
    }
    return;
}

void polynom_subtract(Polynom q, Polynom p1, Polynom p2) {
    size_t deg_max = polynom_degree_max(p1, p2);
    size_t min_length = deg_max+1;
    polynom_optimize(q, min_length);
    polynom_degree_fix(q, deg_max);
    for (size_t i = 0; i <= deg_max; i++) {
        q->terms[i] = polynom_coeff_get(p1, i) - polynom_coeff_get(p2, i);
    }
    return;
}

void polynom_multiply_scalar(Polynom q, Polynom p, double c) {
    for (size_t i = 0; i <= p->degree; i++) {
        q->terms[i] = p->terms[i] * c;
    }
    return;
}

// TODO
void polynom_multiply_vector(Polynom q, Polynom p1, Polynom p2) {
    #if defined(NAIVE)
    size_t deg_max = p1->degree + p2->degree;
    size_t min_length = deg_max+1;
    if (q->terms_length < min_length) {
        
    }
    for (size_t i = 0; i <= p1->degree; i++) {
        for (size_t j = 0; j <= p2->degree; i++) {
            q->terms[i+j] += p1->terms[i] * p2->terms[j];
        }
    }
    #elif defined(FFT)

    #endif
    return;
}

void polynom_divide_scalar(Polynom q, Polynom p, double c) {
    for (size_t i = 0; i <= p->degree; i++) {
        q->terms[i] = p->terms[i] / c;
    }
    return;
}

// TODO
void polynom_divide_vector(Polynom q, Polynom p1, Polynom p2) {
    return;
}

// TODO
void polynom_power(Polynom q, Polynom p, int k) {
    return;
}

void polynom_scale(Polynom q, Polynom p, int k) {
    size_t new_deg = p->degree + (size_t)k;
    size_t min_length = new_deg + 1;
    polynom_optimize(q, min_length);
    if (k < 0) {
        if (new_deg > p->degree) return;
        for (size_t i = 0; i <= new_deg; i++) {
            q->terms[i] = p->terms[i-k];
        }
    } else {
        for (size_t i = 0; i <= new_deg; i++) {
            q->terms[i] = p->terms[i+k];
        }
    }
    return;
}



/* Calculus */

// TODO
void polynom_derive(Polynom q, Polynom p) {
    return;
}

// TODO
void polynom_integrate(Polynom q, Polynom p) {
    return;
}
