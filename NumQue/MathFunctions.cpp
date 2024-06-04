#include "pch.h"
#include "MathFunctions.h"


MathFunctions::MathFunctions(MathCompiler* p) {
    ph = p;
}

MathFunctions::MathFunctions() {
    ph = nullptr;
}

double MathFunctions::f(double x) {
    ph->SetVariable(x);
    return ph->Evaluate();
}

double MathFunctions::ff(double x, double y) {
    ph->SetVariableX(x);
    ph->SetVariableY(y);
    return ph->Evaluate();
}

double MathFunctions::derivative_dc(double x, double dx) {
    return (f(x + (dx / 2)) - f(x - (dx / 2))) / dx;
}

double MathFunctions::derivative_dl(double x, double dx) {
    return (f(x) - f(x - dx)) / dx;
}

double MathFunctions::derivative_dr(double x, double dx) {
    return (f(x + dx) - f(x)) / dx;
}

double MathFunctions::find_root_newton(double x0, double e) {
    double xx = x0;
    double xx1 = x0 - (f(x0)) / (derivative_dc(x0));

    while (fabs(xx1 - xx) >= e) {
        double xx2 = xx1 - (f(xx1)) / (derivative_dc(xx1));
        xx = xx1;
        xx1 = xx2;
    }
    return xx;
}

double MathFunctions::find_root_secant(double a, double b, double e) {
    double x1, x2, xm;
    x1 = a; x2 = b;

    while (fabs(x2 - x1) >= e) {
        xm = x1 - f(x1) * (x2 - x1) / (f(x2) - f(x1));
        x1 = x2;
        x2 = xm;
    }
    return xm;
}


double MathFunctions::integral_lr(double a, double b, int n) {
    double dx = (b - a) / n;
    double s = 0;

    for (double xx = a; xx < b; xx += dx)
        s += f(xx) * dx;

    return s;
}

double MathFunctions::integral_rr(double a, double b, int n) {
    double dx = (b - a) / n;
    double s = 0;

    for (double xx = a + dx; xx < b; xx += dx)
        s += f(xx) * dx;

    return s;
}

double MathFunctions::integral_cr(double a, double b, int n) {
    double dx = (b - a) / n;
    double s = 0;

    for (double xx = a + (dx / 2); xx < b; xx += dx)
        s += f(xx) * dx;

    return s;
}

double MathFunctions::integral_trapeze(double a, double b, int n) {
    double dx = (b - a) / n;
    double s = 0;

    for (double xx = a + dx; xx < b - dx; xx += dx)
        s += f(xx);

    return (s + (f(a) + f(b)) * 0.5) * dx;
}

double MathFunctions::integral_parabola(double a, double b, int n) {
    double h = (b - a) / (n * 1.0);
    double r = (f(a) + 4 * f(a + h) + f(b));
    for (int i = 1; i < n / 2; i++) {
        r += 2 * f(a + (2 * i) * h) + 4 * f(a + (2 * i + 1) * h);
    }
    return r * h / 3;
}

void MathFunctions::euler_method(double x0, double y0, double h, double n,
    std::vector<double>* xr, std::vector<double>* yr) {
    xr->push_back(x0);
    yr->push_back(y0);
    for (int i = 1; i < n + 1; i++) {
        yr->push_back(yr->at(i - 1) +
            h * ff((xr->at(i - 1) ? xr->at(i - 1) : 0.00000001), yr->at(i - 1)));
        xr->push_back(xr->at(i - 1) + h);
    }
}

void MathFunctions::runge_kutta_method(double x0, double y0, double h, double n,
    std::vector<double>* xr, std::vector<double>* yr) {
    xr->push_back(x0);
    yr->push_back(y0);
    for (int i = 1; i < n + 1; i++) {
        double k1 = ff(xr->at(i - 1), yr->at(i - 1));
        double k2 = ff(xr->at(i - 1) + h / 2, yr->at(i - 1) + k1 * h / 2);
        double k3 = ff(xr->at(i - 1) + h / 2, yr->at(i - 1) + k2 * h / 2);
        double k4 = ff(xr->at(i - 1) + h, yr->at(i - 1) + k3 * h);
        yr->push_back(yr->at(i - 1) + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6);
        xr->push_back(xr->at(i - 1) + h);
    }
}

void MathFunctions::runge_kutta_method_3(double x0, double y0, double h, double n,
    std::vector<double>* xr, std::vector<double>* yr) {
    xr->push_back(x0);
    yr->push_back(y0);
    for (int i = 1; i < n + 1; i++) {
        double k1 = ff(xr->at(i - 1), yr->at(i - 1));
        double k2 = ff(xr->at(i - 1) + h / 3, yr->at(i - 1) + k1 * h / 3);
        double k3 = ff(xr->at(i - 1) + 2 * h / 3, yr->at(i - 1) + 2 * k2 * h / 3);
        yr->push_back(yr->at(i - 1) + h * (k1 + 3 * k3) / 4);
        xr->push_back(xr->at(i - 1) + h);
    }
}

double MathFunctions::find_time(double m, double H, double k, double h,
    std::vector<double>* tr, std::vector<double>* vr,
    std::vector<double>* sr, std::vector<double>* ar) {

    auto f = [&k, &m](double t, double v) { return 9.8 - k * v / m; };

    tr->push_back(0);
    vr->push_back(0);
    sr->push_back(0);
    ar->push_back(f(0, 0));
    int i = 1;
    while (true) {
        double k1 = f(tr->at(i - 1), vr->at(i - 1));
        double k2 = f(tr->at(i - 1) + h / 2, vr->at(i - 1) + k1 * h / 2);
        double k3 = f(tr->at(i - 1) + h / 2, vr->at(i - 1) + k2 * h / 2);
        double k4 = f(tr->at(i - 1) + h, vr->at(i - 1) + k3 * h);

        tr->push_back(tr->at(i - 1) + h);
        vr->push_back(vr->at(i - 1) + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6);
        ar->push_back(f(tr->at(i), vr->at(i)));

        double s = 0.0;
        for (int j = 0; j < vr->size(); ++j)
            s += vr->at(j);

        sr->push_back((s + (vr->at(0) + vr->at(i)) * 0.5) * h);

        if (sr->at(i) > H) {
            break;
        }
        i++;
    }

    return tr->at(i - 1) - (sr->at(i - 1) - H) * (tr->at(i) - tr->at(i - 1)) / (sr->at(i) - sr->at(i - 1));
}
