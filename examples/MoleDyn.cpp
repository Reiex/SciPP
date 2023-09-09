#include "MoleDyn.hpp"
#include "SimAnim.hpp"


namespace
{
	void randomParticles(scp::Matrix<double>& p, scp::Matrix<double>& v, double L, double T, double m, double sigmaSq)
	{
		// static const double k = 1.380649e-23;
		// 
		// const double speed = std::sqrt(3*k*T/m);
		// 
		// std::srand(2);
		// 
		// for (uint64_t i(0); i < p.getSize(0); i++)
		// {
		// 	p[{i, 0}] = L * static_cast<double>(std::rand()) / RAND_MAX;
		// 	p[{i, 1}] = L * static_cast<double>(std::rand()) / RAND_MAX;
		// 	
		// 	double theta = 2*std::numbers::pi*static_cast<double>(std::rand()) / RAND_MAX;
		// 	v[{i, 0}] = speed*std::cos(theta);
		// 	v[{i, 1}] = speed*std::sin(theta);
		// }
		// 
		// bool tooClose = true;
		// while (tooClose)
		// {
		// 	tooClose = false;
		// 	for (uint64_t i(0); i < p.getSize(0); i++)
		// 	{
		// 		for (uint64_t j(0); j < p.getSize(0); j++)
		// 		{
		// 			if (i != j && (p[i] - p[j]).normSq() < sigmaSq)
		// 			{
		// 				tooClose = true;
		// 
		// 				p[{j, 0}] = L * static_cast<double>(std::rand()) / RAND_MAX;
		// 				p[{j, 1}] = L * static_cast<double>(std::rand()) / RAND_MAX;
		// 	
		// 				double theta = 2*std::numbers::pi*static_cast<double>(std::rand()) / RAND_MAX;
		// 
		// 				v[{j, 0}] = speed*std::cos(theta);
		// 				v[{j, 1}] = speed*std::sin(theta);
		// 			}
		// 		}
		// 	}
		// }
	}
}

void lennardJones2D(const std::string& name, uint64_t N, double tSimu, double L, double mass, double sigma, double epsilon, double temperature)
{
	// const double k = 1.380649e-23;
	// const double dl = sigma / 100;
	// const double I = 24 * epsilon * k / sigma;
	// const double sigmaSq = sigma * sigma;
	// double t = 0;
	// double dt = dl / std::sqrt(3*k*temperature/mass);
	// 
	// scp::Matrix<double> p(N, 2), v(N, 2), a(N, 2);
	// randomParticles(p, v, L, temperature, mass, sigmaSq);
	// 
	// simanim::createAnimation(name, N, 2);
	// simanim::saveAnimationFrame(name, t, p/L);
	// uint64_t iterations = 0;
	// while (t < tSimu)
	// {
	// 	iterations++;
	// 	if (iterations % 10 == 0)
	// 		std::cout << "> Iteration " << iterations << " a t=" << t << std::endl;
	// 
	// 	for (uint64_t i(0); i < N; i++)
	// 	{
	// 		a[{i, 0}] = 0;
	// 		a[{i, 1}] = 0;
	// 	}
	// 
	// 	#pragma omp parallel for
	// 	for (int i = 0; i < N; i++)
	// 	{
	// 		for (uint64_t j(0); j < N; j++)
	// 		{
	// 			if (i == j)
	// 				continue;
	// 
	// 			scp::Vector<double> diff = p[i] - p[j];
	// 			double dSq = diff.normSq();
	// 			double ratioSq = sigmaSq / dSq;
	// 			double d = std::sqrt(dSq);
	// 			double ratio = sigma / d;
	// 			double ratioSx = ratioSq * ratioSq * ratioSq;
	// 			double F = I*ratioSx*ratio*(2*ratioSx - 1);
	// 
	// 			a[i] += F/(d*mass)*diff;
	// 		}
	// 	}
	// 
	// 	v += a * dt;
	// 	p += v * dt;
	// 
	// 	double vMaxSq = 0.0;
	// 	for (uint64_t i(0); i < N; i++)
	// 	{
	// 		if (p[{i, 0}] > L)
	// 		{
	// 			p[{i, 0}] = L;
	// 			v[{i, 0}] *= -1.0;
	// 		}
	// 
	// 		if (p[{i, 1}] > L)
	// 		{
	// 			p[{i, 1}] = L;
	// 			v[{i, 1}] *= -1.0;
	// 		}
	// 
	// 		if (p[{i, 0}] < 0.0)
	// 		{
	// 			p[{i, 0}] = 0.0;
	// 			v[{i, 0}] *= -1.0;
	// 		}
	// 
	// 		if (p[{i, 1}] < 0.0)
	// 		{
	// 			p[{i, 1}] = 0.0;
	// 			v[{i, 1}] *= -1.0;
	// 		}
	// 
	// 		double vSq = v[i].normSq();
	// 		if (vSq > vMaxSq)
	// 			vMaxSq = vSq;
	// 	}
	// 
	// 	dt = dl / std::sqrt(vMaxSq);
	// 	t += dt;
	// 
	// 	if (iterations % 10 == 0)
	// 		simanim::saveAnimationFrame(name, t, p/L);
	// }
}