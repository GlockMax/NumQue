#include "pch.h"
#include "ApplPrPage.xaml.h"
#if __has_include("ApplPrPage.g.cpp")
#include "ApplPrPage.g.cpp"
#endif
#include <winrt/Microsoft.Graphics.Canvas.Geometry.h>
#include <winrt/Microsoft.Graphics.Canvas.UI.Xaml.h>
#include "MathFunctions.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NumQue::implementation
{
    
    void ApplPrPage::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender,
        winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args) {

        winrt::Windows::Foundation::Size s = sender.Size();

        gb.Init(args);
        gb.scale = 20.0;
        gb.SetSize(s);
        //gb.SetGraph(n, xr, yr);
        gb.UpdateGeometry();

    }

    void ApplPrPage::timeB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        MathFunctions mf;

        double h = std::stod(hI().Text().c_str());
        double m = std::stod(mI().Text().c_str());
        double k = std::stod(kI().Text().c_str());
        double H = std::stod(HI().Text().c_str());

        std::vector<double> tr; 
        std::vector<double> vr;
        std::vector<double> sr; 
        std::vector<double> ar;

        double t = mf.find_time(m, H, k, h, &tr, &vr, &sr, &ar);

        tL().Text(to_hstring(t));

        gb.data_x.clear();
        gb.data_y.clear();
        gb.data_y2.clear();
        gb.data_y3.clear();

        gb.data_x = tr;
        gb.data_y = vr;
        gb.l1 = L"v(t)";
        gb.data_y2 = sr;
        gb.l2 = L"s(t)";
        gb.data_y3 = ar;
        gb.l3 = L"a(t)";

        canvas().Invalidate();

    }

}
