
#include <iostream>
#include <boost/random.hpp>
#include <boost/math/distributions/normal.hpp>

int main() {
    // �������������������ά��˹�ֲ���Э�������
    boost::random::mt19937 rng; // �����������
    double mean_x = 0.0; // ��˹�ֲ��ľ�ֵ x
    double mean_y = 0.0; // ��˹�ֲ��ľ�ֵ y
    double mean_z = 0.0; // ��˹�ֲ��ľ�ֵ z
    double cov_xx = 1.0; // Э��������Ԫ�� (0, 0)
    double cov_yy = 2.0; // Э��������Ԫ�� (1, 1)
    double cov_zz = 3.0; // Э��������Ԫ�� (2, 2)
    double cov_xy = 0.5; // Э��������Ԫ�� (0, 1) = (1, 0)
    double cov_xz = 0.3; // Э��������Ԫ�� (0, 2) = (2, 0)
    double cov_yz = 0.4; // Э��������Ԫ�� (1, 2) = (2, 1)
    // boost::math::normal_distribution<> normalDist_x(mean_x, cov_xx); // ��˹�ֲ� x
    // boost::math::normal_distribution<> normalDist_y(mean_y, cov_yy); // ��˹�ֲ� y
    // boost::math::normal_distribution<> normalDist_z(mean_z, cov_zz); // ��˹�ֲ� z
    boost::random::multivariate_normal_distribution<> multivariateNormalDist(
        {mean_x, mean_y, mean_z}, // ��ֵ����
        {{cov_xx, cov_xy, cov_xz}, // Э�������
         {cov_xy, cov_yy, cov_yz},
         {cov_xz, cov_yz, cov_zz}});

    // ������ά��˹�ֲ������
    int num_samples = 10;
    for (int i = 0; i < num_samples; ++i) {
        boost::random::variate_generator<boost::random::mt19937&, boost::random::multivariate_normal_distribution<>> generator(rng, multivariateNormalDist);
        boost::math::tuple<double, double, double> sample = generator();
        std::cout << "Sample " << i + 1 << ": x = " << sample.get<0>() << ", y = " << sample.get<1>() << ", z = " << sample.get<2>() << std::endl;
    }

    return 0;
}
