
#include "stm32f411xe.h"
#include <Eigen/Dense>
#include "linear_algebra.hpp"


#define MSIZE 16
using mat = Eigen::Matrix<float, MSIZE, MSIZE>;
using matq = Eigen::Matrix<float, 2*MSIZE, MSIZE>;
using vec = Eigen::Matrix<float, MSIZE, 1>;

matq mat_qr;
size_t diff;

template <typename T1, typename T2>
void cross_on_cols(
    Eigen::MatrixBase<T1> &matrix,
    const Eigen::MatrixBase<T2> &vec)
{
  for (auto i = 0; i < T1::ColsAtCompileTime; i++)
    matrix.col(i) = vec.cross( matrix.col(i) );
}

int main()
{
  CoreDebug->DEMCR |= (1UL << CoreDebug_DEMCR_TRCENA_Pos);
  DWT->CYCCNT = 0;
  DWT->CTRL |= (1UL << DWT_CTRL_CYCCNTENA_Pos);

  size_t now;

  mat_qr.block<MSIZE, MSIZE>(0,0).setIdentity();
  mat_qr.block<MSIZE, MSIZE>(0,0).array() += 1;
  mat_qr.block<MSIZE, MSIZE>(MSIZE,0).setIdentity();

  now = DWT->CYCCNT;
  //Eigen::HouseholderQR< Eigen::Ref<matq> > qr(mat_qr);
  qr_triangular_inplace(mat_qr);
  diff = DWT->CYCCNT - now;

  // Zero lower triangular
  mat_qr.triangularView<Eigen::StrictlyLower>().setZero();

  while(1)
  {
    for (volatile int i = 0; i < 1000; i++);
  }
}
