#include "pch.h"
#include "GraphsPage.xaml.h"
#if __has_include("GraphsPage.g.cpp")
#include "GraphsPage.g.cpp"
#endif
#include <winrt/Microsoft.Graphics.Canvas.Geometry.h>
#include <winrt/Microsoft.Graphics.Canvas.UI.Xaml.h>
#include "MathCompiler.h"
#include "MathFunctions.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::Graphics::Canvas::Geometry;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NumQue::implementation
{

    void GraphsPage::rootB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        MathCompiler p;
        std::string q = winrt::to_string(fI().Text());
        p.Compile(q.c_str());
        MathFunctions mf(&p);

        double e = std::stod(eI().Text().c_str());
        double x0 = std::stod(x0I().Text().c_str());
        double x1 = std::stod(x1I().Text().c_str());

        double r1 = mf.find_root_newton(x0, e);
        double r2 = mf.find_root_secant(x0, x1, e);
        mnL().Text(to_hstring(r1));
        msL().Text(to_hstring(r2));

        gb.data_x.clear();
        gb.data_y.clear();
        for (double xx = 0.00001; xx < 12; xx += 0.01) {
            gb.data_x.push_back(xx);
            gb.data_y.push_back(mf.f(xx));
        }
        canvas().Invalidate();
    }

    void GraphsPage::CanvasControl_Draw(
        winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender,
        winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
    {
        winrt::Windows::Foundation::Size s = sender.Size();

        gb.Init(args);
        gb.SetSize(s);
        //gb.SetGraph(n, xr, yr);
        gb.UpdateGeometry();

    }
}
