
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

template <typename T>
using Vector3 = Eigen::Matrix<T, 3, 1>;

Eigen::Quaternion<float> q_old;

template <typename T>
void imu_propagation(
    const Vector3<T> &omega,
    const Vector3<T> &omega_old,
    const Vector3<T> &acc, T dt)
{
  using namespace Eigen;

  Vector3<T> om = (omega + omega_old) / 2;

  T norm = om.norm();

  if (std::abs(norm) > 1e-6)
  {
    Eigen::Quaternion<T> q_w;

    q_w.vec() = om / norm * std::sin(norm * dt);
    q_w.w() = std::cos(norm * dt);

    q_w.vec() += dt*dt/24*omega_old.cross(omega);

    q_w.normalize();

    q_old = q_old * q_w;
  }


}

Vector3<float> w{0.1,0.2,0.3};
Vector3<float> wo{0.15,0.25,0.35};
Vector3<float> a{0.1,0.1,9.8};
volatile float test;

int main()
{
  CoreDebug->DEMCR |= (1UL << CoreDebug_DEMCR_TRCENA_Pos);
  DWT->CYCCNT = 0;
  DWT->CTRL |= (1UL << DWT_CTRL_CYCCNTENA_Pos);

  size_t now;

  q_old.setIdentity();
  mat_qr.block<MSIZE, MSIZE>(0,0).setIdentity();
  mat_qr.block<MSIZE, MSIZE>(0,0).array() += 1;
  mat_qr.block<MSIZE, MSIZE>(MSIZE,0).setIdentity();
  test = 3.1415f;

  imu_propagation<float>(w,wo,a,0.01);

  now = DWT->CYCCNT;
  //Eigen::HouseholderQR< Eigen::Ref<matq> > qr(mat_qr);
  //qr_triangular_inplace(mat_qr);
  w = q_old * a;
  wo = q_old.toRotationMatrix() * a;
  diff = DWT->CYCCNT - now;

  // Zero lower triangular
  mat_qr.triangularView<Eigen::StrictlyLower>().setZero();



  while(1)
  {
    for (volatile int i = 0; i < 1000; i++);
  }
}
