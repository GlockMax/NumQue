#include "GraphBuilder.h"
#include <winrt/Microsoft.Graphics.Canvas.UI.Xaml.h>
#pragma once

#include "GraphsPage.g.h"

namespace winrt::NumQue::implementation
{
    struct GraphsPage : GraphsPageT<GraphsPage>
    {
        GraphsPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        };

        void CanvasControl_Draw(
            winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender,
            winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args);
        //void CanvasControl_CreateResources(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender,
            //winrt::Windows::Foundation::IInspectable const& args);
        GraphBuilder gb;

        void rootB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    };
}

namespace winrt::NumQue::factory_implementation
{
    struct GraphsPage : GraphsPageT<GraphsPage, implementation::GraphsPage>
    {
    };
}
