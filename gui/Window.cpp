//
// FLTK Abstraction Library
//

#include "Window.hpp"
#include "Shape.hpp"
#include "Widget.hpp"

namespace Simple_graphics {

    void Window::draw()
    {
        Fl_Double_Window::draw();
        for (const auto& s : shapes)
            s->draw();
    }

    void Window::attach(Widget& w)
    {
        begin();
        w.attach(*this);
        end();
    }
}
