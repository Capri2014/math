#ifndef STAN_MATH_PRIM_FUN_COMMON_TYPE_HPP
#define STAN_MATH_PRIM_FUN_COMMON_TYPE_HPP

#include <boost/math/tools/promotion.hpp>


#include <stan/math/prim/fun/Eigen.hpp>
#include <vector>







namespace stan {
namespace math {
/**
 * Struct which calculates type promotion given two types.
 *
 * <p>This is the base implementation for scalar types.
 * Allowed promotions are:
 * - int to double
 * - int to var
 * - double to var
 *
 * <p>Promotion between differing var types is not allowed, i.e.,
 * cannot promote fvar to var or vice versa.
 *
 * @tparam T1 scalar type
 * @tparam T2 scalar type
 */
template <typename T1, typename T2>
struct common_type {
  typedef typename boost::math::tools::promote_args<T1, T2>::type type;
};














/**
 * Struct which calculates type promotion over two types.
 *
 * <p>This specialization is for vector types.
 *
 * @tparam T1 type of elements contined in std::vector<T1>
 * @tparam T2 type of elements contined in std::vector<T2>
 */
template <typename T1, typename T2>
struct common_type<std::vector<T1>, std::vector<T2> > {
  typedef std::vector<typename common_type<T1, T2>::type> type;
};














/**
 * Struct which calculates type promotion over two types.
 *
 * <p>This specialization is for matrix types.
 *
 * @tparam T1 type of elements contained in Eigen::Matrix<T1>
 * @tparam T2 type of elements contained in Eigen::Matrix<T2>
 * @tparam R number of rows
 * @tparam C number of columns
 */
template <typename T1, typename T2, int R, int C>
struct common_type<Eigen::Matrix<T1, R, C>, Eigen::Matrix<T2, R, C> > {
  typedef Eigen::Matrix<typename common_type<T1, T2>::type, R, C> type;
};

}  // namespace math
}  // namespace stan

#endif
