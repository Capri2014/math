#ifndef STAN_MATH_PRIM_FUN_LOG_SUM_EXP_HPP
#define STAN_MATH_PRIM_FUN_LOG_SUM_EXP_HPP

#include <stan/math/prim/fun/log1p_exp.hpp>
#include <boost/math/tools/promotion.hpp>




#include <stan/math/prim/fun/log1p.hpp>
#include <stan/math/prim/fun/Eigen.hpp>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <vector>


















namespace stan {
namespace math {

/**
 * Calculates the log sum of exponetials without overflow.
 *
 * \f$\log (\exp(a) + \exp(b)) = m + \log(\exp(a-m) + \exp(b-m))\f$,
 *
 * where \f$m = max(a, b)\f$.
 *
 *
   \f[
   \mbox{log\_sum\_exp}(x, y) =
   \begin{cases}
     \ln(\exp(x)+\exp(y)) & \mbox{if } -\infty\leq x, y \leq \infty \\[6pt]
     \textrm{NaN} & \mbox{if } x = \textrm{NaN or } y = \textrm{NaN}
   \end{cases}
   \f]

   \f[
   \frac{\partial\, \mbox{log\_sum\_exp}(x, y)}{\partial x} =
   \begin{cases}
     \frac{\exp(x)}{\exp(x)+\exp(y)} & \mbox{if } -\infty\leq x, y \leq \infty
 \\[6pt] \textrm{NaN} & \mbox{if } x = \textrm{NaN or } y = \textrm{NaN}
   \end{cases}
   \f]

   \f[
   \frac{\partial\, \mbox{log\_sum\_exp}(x, y)}{\partial y} =
   \begin{cases}
     \frac{\exp(y)}{\exp(x)+\exp(y)} & \mbox{if } -\infty\leq x, y \leq \infty
 \\[6pt] \textrm{NaN} & \mbox{if } x = \textrm{NaN or } y = \textrm{NaN}
   \end{cases}
   \f]
 *
 * @param a the first variable
 * @param b the second variable
 */
template <typename T1, typename T2>
inline typename boost::math::tools::promote_args<T1, T2>::type log_sum_exp(
    const T2& a, const T1& b) {
  using std::exp;
  if (a > b)
    return a + log1p_exp(b - a);
  return b + log1p_exp(a - b);
}
















/**
 * Return the log of the sum of the exponentiated values of the specified
 * sequence of values.
 *
 * The function is defined as follows to prevent overflow in exponential
 * calculations.
 *
 * \f$\log \sum_{n=1}^N \exp(x_n) = \max(x) + \log \sum_{n=1}^N \exp(x_n -
 * \max(x))\f$.
 *
 * @param[in] x array of specified values
 * @return The log of the sum of the exponentiated vector values.
 */
inline double log_sum_exp(const std::vector<double>& x) {
  using std::exp;
  using std::log;
  using std::numeric_limits;
  double max = -numeric_limits<double>::infinity();
  for (double xx : x)
    if (xx > max)
      max = xx;

  double sum = 0.0;
  for (size_t ii = 0; ii < x.size(); ii++)
    if (x[ii] != -numeric_limits<double>::infinity())
      sum += exp(x[ii] - max);

  return max + log(sum);
}

















/**
 * Return the log of the sum of the exponentiated values of the specified
 * matrix of values.  The matrix may be a full matrix, a vector,
 * or a row vector.
 *
 * The function is defined as follows to prevent overflow in exponential
 * calculations.
 *
 * \f$\log \sum_{n=1}^N \exp(x_n) = \max(x) + \log \sum_{n=1}^N \exp(x_n -
 * \max(x))\f$.
 *
 * @param[in] x Matrix of specified values
 * @return The log of the sum of the exponentiated vector values.
 */
template <int R, int C>
double log_sum_exp(const Eigen::Matrix<double, R, C>& x) {
  using std::exp;
  using std::log;
  using std::numeric_limits;
  double max = -numeric_limits<double>::infinity();
  for (int i = 0; i < x.size(); i++)
    if (x(i) > max)
      max = x(i);

  double sum = 0.0;
  for (int i = 0; i < x.size(); i++)
    if (x(i) != -numeric_limits<double>::infinity())
      sum += exp(x(i) - max);

  return max + log(sum);
}

}  // namespace math
}  // namespace stan

#endif
