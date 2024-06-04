#include "pch.h"
#include "IntegralPage.xaml.h"
#if __has_include("IntegralPage.g.cpp")
#include "IntegralPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NumQue::implementation
{
    void IntegralPage::integB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        /*lrL().Text(L"Рассчитано");
        rrL().Text(L"Готово!");*/

        
        MathCompiler p;
        std::string q = winrt::to_string(fI().Text());
        p.Compile(q.c_str());
        MathFunctions mf(&p);
        //hstring r = to_hstring(p.Evaluate());

        //lrL().Text(r);

        int n = std::stod(nI().Text().c_str());

        hstring sa = aI().Text();
        double a = std::stod(sa.c_str());
        hstring sb = bI().Text();
        double b = std::stod(sb.c_str());

        double r1 = mf.integral_lr(a, b, n);
        double r2 = mf.integral_rr(a, b, n);
        double r3 = mf.integral_cr(a, b, n);
        double r4 = mf.integral_trapeze(a, b, n);
        double r5 = mf.integral_parabola(a, b, n);
        lrL().Text(to_hstring(r1));
        rrL().Text(to_hstring(r2));
        crL().Text(to_hstring(r3));
        trL().Text(to_hstring(r4));
        paL().Text(to_hstring(r5));
    }
}
