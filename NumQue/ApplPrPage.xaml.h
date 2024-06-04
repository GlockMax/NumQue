#include "GraphBuilder.h"
#include <winrt/Microsoft.Graphics.Canvas.UI.Xaml.h>

#pragma once

#include "ApplPrPage.g.h"

namespace winrt::NumQue::implementation
{
    struct ApplPrPage : ApplPrPageT<ApplPrPage>
    {
        ApplPrPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void CanvasControl_Draw(
            winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender,
            winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args);
        GraphBuilder gb;

        void timeB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        
    };
}

namespace winrt::NumQue::factory_implementation
{
    struct ApplPrPage : ApplPrPageT<ApplPrPage, implementation::ApplPrPage>
    {
    };
}
