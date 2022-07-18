#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct polynom_header *Polynom;

/*************
 * Interface *
 *************/

/* Create and destroy */

/**
 * @brief Initializes a polynomial
 * 
 * @return An initialized polynomial with no guarantees about its coefficients
 */
Polynom polynom_new();

/**
 * @brief Creates a new instance of a polynomial that is a copy of p
 * 
 * @param[in] p struct polynom_headerial to be copied
 * @return The copied polynomial
 */
Polynom polynom_copy(Polynom p);

/**
 * @brief Returns 0.0 * x^0
 * 
 * @return Zero
 */
Polynom polynom_zero();

/**
 * @brief Returns 1.0 * x^0
 * 
 * @return One
 */
Polynom polynom_one();

/**
 * @brief Returns 1.0 * x^1 + 0.0 * x^0
 * 
 * @return x
 */
Polynom polynom_x();

/**
 * @brief Returns 1.0 * x^k + ... + 0.0 * x^0
 * 
 * @param[in] k The power to which x is raised
 * @return x^k
 */
Polynom polynom_x_to_the(size_t k);

/**
 * @brief Frees the memory taken by the polynomial
 * 
 * @param[in] p Polynomial to be destroyed
 */
void polynom_destroy(Polynom p);



/* Coefficients */

/**
 * @brief Gets the ith coefficient of a polynomial
 * 
 * @param[in] p The polynomial
 * @param[in] i The coefficient index
 * 
 * @return The coefficient
 */
double polynom_coeff_get(Polynom p, size_t i);

/**
 * @brief Sets the ith coefficient of a ial
 * 
 * @param[in] p The polynomial
 * @param[in] i The coefficient index
 * @param[in] a The new coefficient value 
 */
void polynom_coeff_set(Polynom p, size_t i, double a);

/**
 * @brief Converts a polynomial to its string representation
 * 
 * e.g. 2.0x^2 + 3x^1 + 4x^0
 * 
 * @param[in] p The polynomial
 * @return A buffer containing the string
 */
char *polynom_to_string(Polynom p);

/**
 * @brief Returns an array of coefficients indexed by their power
 * 
 * @param[in] p The polynomial
 * @param[out] size The size of the output buffer
 * @return The output buffer
 */
double *polynom_to_array(Polynom p, size_t *size);

/** TODO
 * @brief 
 * 
 * @param[] buf
 * @return Polynom 
 */
Polynom polynom_from_array(double *buf, size_t len);



/* Degree */

/**
 * @brief Returns the degree of a polynomial
 * 
 * @param[in] p The polynomial
 * @return The degree
 */
size_t polynom_degree(Polynom p);

/**
 * @brief Compares the degrees of two polynomials
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return deg(p1) < deg(p2) . -1
 *         deg(p1) == deg(p2) . 0
 *         deg(p1) > deg(p2) . 1
 */
int polynom_degree_compare(Polynom p1, Polynom p2);

/**
 * @brief The greater of the degrees of two given polynomials
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return size_t The greater degree
 */
size_t polynom_degree_max(Polynom p1, Polynom p2);

/* Equality and order */

/**
 * @brief Returns whether p1 == p2
 * 
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 * @return p1 == p2
 */
bool polynom_equal(Polynom p1, Polynom p2);



/* Arithmetic */

/**
 * @brief Returns the result of evaluating the polynomial at x via 
 *        Horner's method
 * 
 * @param[in] p The polynomial to evaluate
 * @param[in] x The value at which to evaluate p
 * @return p(x)
 */
double polynom_evaluate(Polynom p, double x);

/**
 * @brief q(x) = p1(x) + p2(x)
 * 
 * @param[out] q The result polynomial
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 */
void polynom_add(Polynom q, Polynom p1, Polynom p2);

/**
 * @brief q(x) = p1(x) - p2(x)
 * 
 * @param[out] q The result polynomial
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 */
void polynom_subtract(Polynom q, Polynom p1, Polynom p2);

/**
 * @brief q(x) = p(x) * c
 * 
 * @param[out] q The result polynomial
 * @param[in] p The polynomial
 * @param[in] c The constant
 */
void polynom_multiply_scalar(Polynom q, Polynom p, double c);

/** TODO
 * @brief 
 * 
 * @param[out] q The result polynomial
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 */
void polynom_multiply_vector(Polynom q, Polynom p1, Polynom p2);

/**
 * @brief q(x) = p(x) / c
 * 
 * @param[out] q The result polynomial
 * @param[in] p The polynomial
 * @param[in] c The constant
 */
void polynom_divide_scalar(Polynom q, Polynom p, double c);

/** TODO
 * @brief q(x) = p1(x) / p2(x)
 * 
 * @param[out] q The result polynomial
 * @param[in] p1 The first polynomial
 * @param[in] p2 The second polynomial
 */
void polynom_divide_vector(Polynom q, Polynom p1, Polynom p2);

/** TODO
 * @brief q(x) = (p(x)) ^ k
 * 
 * @param[out] q The result polynomial
 * @param[in] p The polynomial
 * @param[in] k The power
 */
void polynom_power(Polynom q, Polynom p, int k);

/** 
 * @brief q(x) = p(x) * x^k
 * 
 * @param[out] q The result polynomial
 * @param[in] p The polynomial
 * @param[in] k The power
 */
void polynom_scale(Polynom q, Polynom p, int k);



/* Calculus */

/** TODO
 * @brief 
 * 
 * @param[out] q The result polynomial
 * @param[in] p
 */
void polynom_derive(Polynom q, Polynom p);

/** TODO
 * @brief 
 * 
 * @param[out] q The result polynomial
 * @param[in] p
 */
void polynom_integrate(Polynom q, Polynom p);

#endif /* __POLYNOM_H__ */
