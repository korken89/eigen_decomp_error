#include <Eigen/Dense>

using mat = Eigen::Matrix<float, 2, 2>;

mat mat4;

int main()
{
  mat mat1, mat2;

  mat1.setOnes();
  mat2.setOnes();
  mat4 = mat1 * mat2;

  // Working
  Eigen::LLT< Eigen::Ref<mat> > qr(mat4);
  //Eigen::LDLT< Eigen::Ref<mat> > qr(mat4);
  //Eigen::FullPivLU< Eigen::Ref<mat> > qr(mat4);
  //Eigen::ColPivHouseholderQR< Eigen::Ref<mat> > qr(mat4);
  //Eigen::FullPivHouseholderQR< Eigen::Ref<mat> > qr(mat4);
  //Eigen::CompleteOrthogonalDecomposition< Eigen::Ref<mat> > qr(mat4);

  // Failing by calling abort() internally
  //Eigen::PartialPivLU< Eigen::Ref<mat> > qr(mat4);
  //Eigen::HouseholderQR< Eigen::Ref<mat> > qr(mat4);

  while(1);
}
