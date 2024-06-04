#include "pch.h"
#include "DifferencialPage.xaml.h"
#if __has_include("DifferencialPage.g.cpp")
#include "DifferencialPage.g.cpp"
#endif
#include "MathCompiler.h"
#include "MathFunctions.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NumQue::implementation
{

    void DifferencialPage::diffB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        MathCompiler p;
        std::string q = winrt::to_string(fI().Text());
        p.Compile(q.c_str());
        MathFunctions mf(&p);

        double dx = std::stod(dxI().Text().c_str());
        double x0 = std::stod(x0I().Text().c_str());

        double r1 = mf.derivative_dl(x0, dx);
        double r2 = mf.derivative_dr(x0, dx);
        double r3 = mf.derivative_dc(x0, dx);

        dlL().Text(to_hstring(r1));
        drL().Text(to_hstring(r2));
        dcL().Text(to_hstring(r3));

    }
    
}
