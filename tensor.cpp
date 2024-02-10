
#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>

int main()
{
    auto tensor1 = Eigen::TensorFixedSize<double, Eigen::Sizes<3,3>>();
    tensor1.setValues({ {1, 0, 0},
                        {0, 1, 0},
                        {0, 0, 1} });
    std::cout << "tensor1:\n" << tensor1 << "\n";

    auto tensor2 = Eigen::TensorFixedSize<double, Eigen::Sizes<3,3>>();
    tensor2.setValues({ {2, 0, 0},
                        {0, 2, 0},
                        {0, 0, 2} });
    std::cout << "tensor2:\n" << tensor2 << "\n";


    Eigen::array<Eigen::IndexPair<int>, 2> contraction_pair0011
        = { Eigen::IndexPair<int>(0, 0), Eigen::IndexPair<int>(1, 1)};

    Eigen::TensorFixedSize<double, Eigen::Sizes<>> tensor1_tensor2 = tensor1.contract(tensor2, contraction_pair0011);
    std::cout << "tensor1 : tensor1:\n" << tensor1_tensor2 << "\n";

    double t1_t2 = tensor1_tensor2(0);
    std::cout << "result in double:\n" << t1_t2 << "\n";
}
