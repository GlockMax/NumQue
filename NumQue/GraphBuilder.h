#include <winrt/Microsoft.Graphics.Canvas.Geometry.h>
#include <winrt/Microsoft.Graphics.Canvas.UI.Xaml.h>
#include <winrt/Microsoft.Graphics.Canvas.Text.h>

using namespace winrt::Microsoft::Graphics::Canvas::Geometry;

#pragma once
class GraphBuilder
{
	winrt::Windows::UI::Color gridColor{ winrt::Windows::UI::ColorHelper::FromArgb(255, 200, 200, 200) };
	winrt::Windows::UI::Color lineColor{ winrt::Windows::UI::ColorHelper::FromArgb(255, 200, 15, 0) };
	winrt::Windows::UI::Color axisColor{ winrt::Windows::UI::ColorHelper::FromArgb(255, 255, 255, 255) };
	winrt::Windows::UI::Color lineColor2{ winrt::Windows::UI::ColorHelper::FromArgb(255, 15, 0, 200) };
	winrt::Windows::UI::Color lineColor3{ winrt::Windows::UI::ColorHelper::FromArgb(255, 15, 200, 0) };
	float w, h;
	CanvasCachedGeometry* gra;
	CanvasCachedGeometry* gri;
	winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const* args;

public:
	void Init(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& _args);
	void SetSize(winrt::Windows::Foundation::Size s);
	double scale = 10.0;
	void SetGraph(int n, double* xr, double* yr);
	void UpdateGeometry ();
	std::vector<double> data_x;
	std::vector<double> data_y;
	std::vector<double> data_y2;
	std::vector<double> data_y3;
	winrt::hstring l1 = L"";
	winrt::hstring l2 = L"";
	winrt::hstring l3 = L"";

};

