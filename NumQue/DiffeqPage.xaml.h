#pragma once

#include "DiffeqPage.g.h"

namespace winrt::NumQue::implementation
{
    struct DiffeqPage : DiffeqPageT<DiffeqPage>
    {
        DiffeqPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void fvB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::NumQue::factory_implementation
{
    struct DiffeqPage : DiffeqPageT<DiffeqPage, implementation::DiffeqPage>
    {
    };
}
