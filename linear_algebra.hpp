#pragma once

#include <cmath>
#include <Eigen/Dense>

#define COL_MAJOR

#define SIGN(a, b) ((b) >= 0 ? std::abs(a) : -std::abs(a))

#ifdef COL_MAJOR
#define A(i, j) (a[(i) + (j)*(m)])
#define A2(i, j) (a[(i) + (j)*(2*n)])
#elif
#define A(i, j) (a[(i)*(n) + (j)])
#define A2(i, j) (a[(i)*(n) + (j)])
#endif

/*
 * @brief               QR Decomposition of skinny (tall) matrices where m >= n.
 * @note                This algorithm uses solving householder matrices.
 * @test                This implementation is a few % slower than Eigen.
 *
 * @author              Emil Fresk, Luleå University of Technology
 * @param[in/out] a     Input/output matrix, a points to the first element.
 * @param[in] m         Number of rows in matrix.
 * @param[in] n         Number of columns in matrix.
 * @return              Returns the upper triangular matrix R in the top of A.
 */
template <int m, int n, typename T>
inline void qr_decomp(T *a)
{
    int i, j, k;
    T sum;

    // Loop over every column
    for (k = 0; k < n; k++)
    {
        // Calculate the norm of the vector
        for (j = k, sum = T(0); j < m; j++)
            sum += A(j, k) * A(j, k);

        const T norm = std::sqrt(sum);
        const T sigma = SIGN(norm, A(k, k));
        const T u1 = A(k, k) + sigma;
        const T u2 = T(1) / u1;
        const T tau = u1 / sigma;

        // Find Hk and Hk * A

        for (j = k + 1; j < m; j++)
            A(j, k) *= u2;

        A(k, k) = -sigma;

        for (j = k + 1; j < n; j++)
        {
            for (sum = A(k, j), i = k + 1; i < m; i++)
                sum += A(i, k) * A(i, j);

            A(k, j) -= tau * sum;

            for (i = k + 1; i < m; i++)
                A(i, j) -= tau * sum * A(i, k);
        }
    }
}


/*
 * @brief               Optimized QR Decomposition of matrices where m = 2n and
 *                      where the last n rows is an upper triangular matrix.
 * @note                This algorithm uses solving householder matrices.
 * @test                This special case beats Eigen, about 30-40% faster.
 *
 * @author              Emil Fresk, Luleå University of Technology
 * @param[in/out] a     Input/output matrix, a points to the first element.
 * @param[in] n         Number of columns in matrix.
 * @return              Returns the upper triangular matrix R in the top of A.
 */

template <int n, typename T>
inline void qr_decomp_tria(T *a)
{
    static_assert(n > 0, "Size must be larger than 0.");

    int i, j, k;
    T sum;

    // Loop over every column
    for (k = 0; k < n; k++)
    {
        // Calculate the norm of the vector
        for (j = k, sum = T(0); j < k + n + 1; j++)
            sum += A2(j, k) * A2(j, k);

        const T norm = std::sqrt(sum);
        const T sigma = SIGN(norm, A2(k, k));
        const T u1 = A2(k, k) + sigma;
        const T u2 = T(1) / u1;
        const T tau = u1 / sigma;

        // Find Hk and Hk * A

        for (j = k + 1; j < k + n + 1; j++)
            A2(j, k) *= u2;

        A2(k, k) = -sigma;

        for (j = k + 1; j < n; j++)
        {
            for (sum = A2(k, j), i = k + 1; i < k + n + 1; i++)
                sum += A2(i, k) * A2(i, j);

            A2(k, j) -= tau * sum;

            for (i = k + 1; i < k + n + 1; i++)
                A2(i, j) -= tau * sum * A2(i, k);
        }
    }
}


/*
 * Eigen interface
 */
template <int m, int n, typename T>
inline void qr_inplace(Eigen::Matrix<T, m, n> &a)
{
  qr_decomp<m, n, T>(a.data());
}

template <int m, int n, typename T>
inline void qr_triangular_inplace(Eigen::Matrix<T, m, n> &a)
{
  static_assert(m == 2*n, "There must be 2x number of rows as columns");

  qr_decomp_tria<n, T>(a.data());
}
