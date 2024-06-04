#pragma once

#include "IntegralPage.g.h"
#include "MathCompiler.h"
#include "MathFunctions.h"

namespace winrt::NumQue::implementation
{
    struct IntegralPage : IntegralPageT<IntegralPage>
    {
        IntegralPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void integB_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::NumQue::factory_implementation
{
    struct IntegralPage : IntegralPageT<IntegralPage, implementation::IntegralPage>
    {
    };
}
