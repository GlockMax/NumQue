#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NumQue::implementation
{
    void MainWindow::NavView_ItemInvoked(Controls::NavigationView sender, Controls::NavigationViewItemInvokedEventArgs args) {
        if (args.InvokedItemContainer() != NULL)
        {
            IInspectable tag = args.InvokedItemContainer().Tag();
            hstring bs = unbox_value<hstring>(tag);
            Windows::UI::Xaml::Interop::TypeName t;
            if (bs == L"Integrals") {
                t = xaml_typename<NumQue::IntegralPage>();
            }
            else if (bs == L"Differens") {
                t = xaml_typename<NumQue::DifferencialPage>();
            }
            else if (bs == L"Graphs") {
                t = xaml_typename<NumQue::GraphsPage>();
            }
            else if (bs == L"Diffeq") {
                t = xaml_typename<NumQue::DiffeqPage>();
            }
            else if (bs == L"ApplPr") {
                t = xaml_typename<NumQue::ApplPrPage>();
            }
            NavView_Navigate(t);
        }
    }
    void MainWindow::NavView_Navigate(Windows::UI::Xaml::Interop::TypeName pageType) {
        Windows::UI::Xaml::Interop::TypeName u = ContentFrame().CurrentSourcePageType();
        if (u.Name != pageType.Name) {
            ContentFrame().Navigate(pageType);
            hstring s;
            if (pageType.Name == L"NumQue.IntegralPage") s = L"Интегрирование";
            else if (pageType.Name == L"NumQue.DifferencialPage") s = L"Дифференцирование";
            else if (pageType.Name == L"NumQue.GraphsPage") s = L"Нелинейные уравнения";
            else if (pageType.Name == L"NumQue.DiffeqPage") s = L"Дифференциальные уравнения";
            else if (pageType.Name == L"NumQue.ApplPrPage") s = L"Прикладная задача";
            NavView().Header(box_value(s));
        }
    }

    void MainWindow::NavView_Loaded(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        NavView().SelectedItem(NavView().MenuItems().GetAt(0));
        NavView_Navigate(xaml_typename<NumQue::IntegralPage>());
    }
}
