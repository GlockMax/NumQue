#include "pch.h"
#include "MathCompiler.h"
#include <vector>
#pragma once

class MathFunctions
{
public:
	MathCompiler* ph;
	MathFunctions(MathCompiler* p);
	MathFunctions();
	double f(double x);
	double ff(double x, double y);

	double derivative_dr(double x, double dx = 0.00000001);
	double derivative_dl(double x, double dx = 0.00000001);
	double derivative_dc(double x, double dx = 0.00000001);
	double find_root_newton(double x0, double e);
	double find_root_secant(double a, double b, double e);
	double integral_lr(double a, double b, int n);
	double integral_rr(double a, double b, int n);
	double integral_cr(double a, double b, int n);
	double integral_trapeze(double a, double b, int n);
	double integral_parabola(double a, double b, int n);
	void runge_kutta_method(double x0, double y0, double h, double n,
		std::vector<double>* xr, std::vector<double>* yr);
	void euler_method(double x0, double y0, double h, double n,
		std::vector<double>* xr, std::vector<double>* yr);
	void runge_kutta_method_3(double x0, double y0, double h, double n,
		std::vector<double>* xr, std::vector<double>* yr);
	double find_time(double m, double H, double k, double h,
		std::vector<double>* tr, std::vector<double>* vr,
		std::vector<double>* sr, std::vector<double>* ar);
};

