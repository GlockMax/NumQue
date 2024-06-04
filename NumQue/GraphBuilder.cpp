#include "pch.h"
#include "GraphBuilder.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::Graphics::Canvas::Geometry;
using namespace winrt::Microsoft::Graphics::Canvas::Text;

void GraphBuilder::UpdateGeometry() {

    // Сетка
    auto pbw = CanvasPathBuilder(args->DrawingSession().Device());
    for (double x = -12; x <= 12; x += 1) {
        pbw.BeginFigure(w / 2 - scale * x, h/2 - 12*scale);
        pbw.AddLine(w / 2 - scale * x, h/2 + 12*scale);
        pbw.EndFigure(CanvasFigureLoop::Open);
    }

    for (double y = -12; y <= 12; y += 1) {
        pbw.BeginFigure(w/2-12*scale, h/2 + scale * y);
        pbw.AddLine(w/2+12*scale, h / 2 + scale * y);
        pbw.EndFigure(CanvasFigureLoop::Open);
    }

    CanvasGeometry gr = CanvasGeometry::CreatePath(pbw);
    
    args->DrawingSession().DrawGeometry(gr, gridColor, 0.25);

    // Оси

    auto pba = CanvasPathBuilder(args->DrawingSession().Device());
    pba.BeginFigure(w / 2, h / 2 - 14 * scale);
    pba.AddLine(w / 2, h / 2 + 14 * scale);
    pba.EndFigure(CanvasFigureLoop::Open);
    pba.BeginFigure(w/2 - 14*scale, h / 2);
    pba.AddLine(w/2 + 14*scale, h / 2);
    pba.EndFigure(CanvasFigureLoop::Open);

    pba.BeginFigure(w / 2, h / 2 - 14 * scale);
    pba.AddLine(w / 2 - 0.5*scale, h / 2 - 14 * scale + 1.5*scale);
    pba.AddLine(w / 2 + 0.5 * scale, h / 2 - 14 * scale + 1.5 * scale);
    pba.EndFigure(CanvasFigureLoop::Closed);

    pba.BeginFigure(w / 2 + 14 * scale, h / 2);
    pba.AddLine(w / 2 + 14 * scale-1.5*scale, h / 2 - 0.5 * scale);
    pba.AddLine(w / 2 + 14 * scale-1.5*scale, h / 2 + 0.5 * scale);
    pba.EndFigure(CanvasFigureLoop::Closed);

    CanvasGeometry ar = CanvasGeometry::CreatePath(pba);

    args->DrawingSession().DrawGeometry(ar, axisColor, 0.5);

    // График
    
    
    if (data_y.size() != 0) {
        auto pbg = CanvasPathBuilder(args->DrawingSession().Device());
        pbg.BeginFigure(w / 2 + scale * data_x[0], h / 2 - scale * data_y[0]);
        for (int i = 1; i < data_x.size(); i++) {
            pbg.AddLine(w / 2 + scale * data_x[i], h / 2 - scale * data_y[i]);
        }
        pbg.EndFigure(CanvasFigureLoop::Open);
        CanvasGeometry g = CanvasGeometry::CreatePath(pbg);

        args->DrawingSession().DrawGeometry(g, lineColor, 2);

        if (l1 != L"") {
            CanvasTextFormat f;
            CanvasTextLayout lay(args->DrawingSession().Device(), l1, f, 100, 100);
            args->DrawingSession().DrawTextLayout(lay, w / 2 + scale * data_x[data_x.size() - 1],
                h / 2 - scale * data_y[data_x.size() - 1] - 0.2 * scale, lineColor);
        }
    }

    if (data_y2.size() != 0) {
        auto pbg = CanvasPathBuilder(args->DrawingSession().Device());
        pbg.BeginFigure(w / 2 + scale * data_x[0], h / 2 - scale * data_y2[0]);
        for (int i = 1; i < data_x.size(); i++) {
            pbg.AddLine(w / 2 + scale * data_x[i], h / 2 - scale * data_y2[i]);
        }
        pbg.EndFigure(CanvasFigureLoop::Open);
        CanvasGeometry g = CanvasGeometry::CreatePath(pbg);

        args->DrawingSession().DrawGeometry(g, lineColor2, 2);

        if (l2 != L"") {
            CanvasTextFormat f;
            CanvasTextLayout lay(args->DrawingSession().Device(), l2, f, 100, 100);
            args->DrawingSession().DrawTextLayout(lay, w / 2 + scale * data_x[data_x.size()-1],
                h / 2 - scale * data_y2[data_x.size() - 1]-0.2*scale, lineColor2);
        }
    }

    if (data_y3.size() != 0) {
        auto pbg = CanvasPathBuilder(args->DrawingSession().Device());
        pbg.BeginFigure(w / 2 + scale * data_x[0], h / 2 - scale * data_y3[0]);
        for (int i = 1; i < data_x.size(); i++) {
            pbg.AddLine(w / 2 + scale * data_x[i], h / 2 - scale * data_y3[i]);
        }
        pbg.EndFigure(CanvasFigureLoop::Open);
        CanvasGeometry g = CanvasGeometry::CreatePath(pbg);

        args->DrawingSession().DrawGeometry(g, lineColor3, 2);

        if (l3 != L"") {
            CanvasTextFormat f;
            CanvasTextLayout lay(args->DrawingSession().Device(), l3, f, 100, 100);
            args->DrawingSession().DrawTextLayout(lay, w / 2 + scale * data_x[data_x.size() - 1],
                h / 2 - scale * data_y3[data_x.size() - 1] - 0.2 * scale, lineColor3);
        }
    }
    
}

void GraphBuilder::SetGraph(int n, double* xr, double* yr) {
    
    //CanvasCachedGeometry t = CanvasCachedGeometry::CreateFill(g);
    //gra = &t;
}

void GraphBuilder::SetSize(winrt::Windows::Foundation::Size s) {
    w = s.Width;
    h = s.Height;
}

void GraphBuilder::Init(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& _args) {
    args = &_args;
}