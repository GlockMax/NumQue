#pragma once

#include "DifferencialPage.g.h"

namespace winrt::NumQue::implementation
{
    struct DifferencialPage : DifferencialPageT<DifferencialPage>
    {
        DifferencialPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        

        void diffB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::NumQue::factory_implementation
{
    struct DifferencialPage : DifferencialPageT<DifferencialPage, implementation::DifferencialPage>
    {
    };
}
