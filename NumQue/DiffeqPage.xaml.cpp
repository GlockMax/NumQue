#include "pch.h"
#include "DiffeqPage.xaml.h"
#if __has_include("DiffeqPage.g.cpp")
#include "DiffeqPage.g.cpp"
#endif
#include "MathCompiler.h"
#include "MathFunctions.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NumQue::implementation
{
	void DiffeqPage::fvB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args) {
		MathCompiler p;
		std::string q = winrt::to_string(fI().Text());
		p.Compile(q.c_str());
		MathFunctions mf(&p);

		double n = std::stod(nI().Text().c_str());
		double x0 = std::stod(x0I().Text().c_str());
		double y0 = std::stod(y0I().Text().c_str());
		double h = std::stod(hI().Text().c_str());

		std::vector<double> x_e;
		std::vector<double> y_e;
		std::vector<double> x_r;
		std::vector<double> y_r;

		mf.runge_kutta_method(x0, y0, h, n, &x_r, &y_r);
		mf.euler_method(x0, y0, h, n, &x_e, &y_e);

		std::string res1 = "";
		std::string n_l = "\n";
		std::string tab = "\t";

		for (int i = 0; i < x_e.size(); i++) {
			std::string xi = std::to_string(x_e[i]);
			std::string yi = std::to_string(y_e[i]);
			res1 += xi + tab + yi + n_l;
		}
		outputT1().Text(to_hstring(res1));

		std::string res2 = "";

		for (int i = 0; i < x_r.size(); i++) {
			std::string xi = std::to_string(x_r[i]);
			std::string yi = std::to_string(y_r[i]);
			res2 += xi + tab + yi + n_l;
		}
		outputT2().Text(to_hstring(res2));



	}
}
