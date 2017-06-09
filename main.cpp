
#include "stm32f411xe.h"
#include <Eigen/Dense>


#define MSIZE 16
using mat = Eigen::Matrix<float, MSIZE, MSIZE>;
using vec = Eigen::Matrix<float, MSIZE, 1>;

mat mat1;
mat mat2;
mat mat4;
size_t diff;

int main()
{
  CoreDebug->DEMCR |= (1UL << CoreDebug_DEMCR_TRCENA_Pos);
  DWT->CYCCNT = 0;
  DWT->CTRL |= (1UL << DWT_CTRL_CYCCNTENA_Pos);

  mat1.setOnes();
  mat1.diagonal() += vec::Ones();
  //for (auto i = 0; i < MSIZE; i++)
  //  mat1(i,i) += 1;

  mat2.setOnes();
  size_t now = DWT->CYCCNT;
  mat4 = mat1 * mat2 * mat1.transpose() + mat2;
  diff = DWT->CYCCNT - now;

  // Working
  //Eigen::LLT< Eigen::Ref<mat> > qr(mat4);
  //Eigen::LDLT< Eigen::Ref<mat> > qr(mat4);
  //Eigen::FullPivLU< Eigen::Ref<mat> > qr(mat4);
  //Eigen::ColPivHouseholderQR< Eigen::Ref<mat> > qr(mat4);
  //Eigen::FullPivHouseholderQR< Eigen::Ref<mat> > qr(mat4);
  //Eigen::CompleteOrthogonalDecomposition< Eigen::Ref<mat> > qr(mat4);

  // Failing by calling abort() internally
  //Eigen::PartialPivLU< Eigen::Ref<mat> > qr(mat4);
  Eigen::HouseholderQR< Eigen::Ref<mat> > qr(mat1);
  mat1.triangularView<Eigen::StrictlyLower>().setZero();

  while(1)
  {
    for (volatile int i = 0; i < 1000; i++);
  }
}
