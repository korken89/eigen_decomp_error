
#include "stm32f411xe.h"
#include <Eigen/Dense>
#include "linear_algebra.hpp"


#define MSIZE 16
using mat = Eigen::Matrix<float, MSIZE, MSIZE>;
using matq = Eigen::Matrix<float, 2*MSIZE, MSIZE>;
using vec = Eigen::Matrix<float, MSIZE, 1>;

mat mat1;
mat mat2;
mat mat4;
matq mat_qr;
size_t diff1;
size_t diff2;

int main()
{
  CoreDebug->DEMCR |= (1UL << CoreDebug_DEMCR_TRCENA_Pos);
  DWT->CYCCNT = 0;
  DWT->CTRL |= (1UL << DWT_CTRL_CYCCNTENA_Pos);

  mat1.setIdentity();
  mat1.array() += 1;
  mat2.setOnes();

  mat_qr.block<MSIZE, MSIZE>(0,0).setIdentity();
  mat_qr.block<MSIZE, MSIZE>(0,0).array() += 1;
  mat_qr.block<MSIZE, MSIZE>(MSIZE,0).setIdentity();

  size_t now = DWT->CYCCNT;
  mat4 = mat1 * mat2 * mat1.transpose() + 5.0*mat::Identity();
  diff1 = DWT->CYCCNT - now;


  // Working
  //Eigen::LLT< Eigen::Ref<mat> > qr(mat4);
  //Eigen::LDLT< Eigen::Ref<mat> > qr(mat4);
  //Eigen::FullPivLU< Eigen::Ref<mat> > qr(mat4);
  //Eigen::ColPivHouseholderQR< Eigen::Ref<mat> > qr(mat4);
  //Eigen::FullPivHouseholderQR< Eigen::Ref<mat> > qr(mat4);
  //Eigen::CompleteOrthogonalDecomposition< Eigen::Ref<mat> > qr(mat4);

  // Failing by calling abort() internally
  //Eigen::PartialPivLU< Eigen::Ref<mat> > qr(mat4);
  now = DWT->CYCCNT;
  //Eigen::HouseholderQR< Eigen::Ref<matq> > qr(mat_qr);
  qr_decomp_tria<MSIZE>(mat_qr.data());
  diff2 = DWT->CYCCNT - now;
  //mat_qr.triangularView<Eigen::StrictlyLower>().setZero();

  while(1)
  {
    for (volatile int i = 0; i < 1000; i++);
  }
}
