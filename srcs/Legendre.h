#ifndef LEGENDRE_H_
#define LEGENDRE_H_
#include <cstdlib>
#include "Basis.h"

/**
 * \brief A Basis which uses the Legendre polynomials.
 *
 * A class to represent a truncated set of Legendre polynomial
 * basis functions. The abscissas and weights are pulled out of the
 * LegendreAbscissas namespace where they are saved from maple output.
 */
class Legendre: public Basis {
  public:
    /**
     * The constructor does nothing. This is necessary as I don't want
     * to throw an exception from the constructor in the case that the
     * chosen number of basis functions does not have collocation points
     * implemented in the LegendreAbscissas namespace.
     */
    Legendre(): Basis() {};

    /**
     * Sets the pointers to the abscissas and weights. Returns a
     * non-zero return code if the abscissas are not implemented in
     * LegendreAbscissas.
     * \param N The number of basis functions to use.
     * \retval Returns 0 if the abscissas exist, -1 otherwise.
     */
    virtual bool setRank(int N);

    virtual double evaluate(double x, const double* coeffs) const;

  protected:

    /**
     * The parameter alpha in the recursion relation for the family of
     * polynomials:
     * \f[
     *   \phi_n(x) + \alpha_n(x)\phi_{n-1}(x) + \beta_n(x)\phi_{n-2}(x)
     *   = 0
     * \f]
     * \param n The order of the highest order basis function.
     * \param x The coordinate to evaluate the coefficient at.
     * \retval The parameter alpha.
     */
    virtual double alpha(int n, double x) const ;

    /**
     * The parameter beta in the recursion relation for the family of
     * polynomials:
     * \f[
     *   \phi_n(x) + \alpha_n(x)\phi_{n-1}(x) + \beta_n(x)\phi_{n-2}(x)
     *   = 0
     * \f]
     * \param n The order of the highest order basis function.
     * \param x The coordinate to evaluate the coefficient at.
     * \retval The parameter beta.
     */
    virtual double beta(int n, double x) const;

    /**
     * The individual Legendre basis functions. Not meant to be used
     * directly as they are low-level for doing spectral methods.
     * \param n The order of the basis function.
     * \param x The coordinate to evaluate the basis function at.
     * \retval P_n(x) the Legendre polynomial of n'th order evaluated at
     * x.
     */
    virtual double function(int n, double x) const;

    /**
     * Builds and returns the matrix that takes a vector of coefficients
     * of a function and returns the coefficients of the derivative of
     * that function.
     * \retval The coefficients-to-coefficients-of-derivative operator.
     */
    virtual double* coefficientsOfDerivativeMatrix() const;
};
#endif
