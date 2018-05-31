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

    void Window::attach(Shape& s)
    {
        shapes.push_back(&s);
    }

    void Window::attach(Widget& w)
    {
        begin();
        w.attach(*this);
        end();
    }

    void Window::detach(Shape& s)
        // ok if &s not found
    {
        auto it = std::find(std::begin(shapes), std::end(shapes), &s);

        if (it != shapes.end())
            shapes.erase(it);
    }

    void Window::detach(Widget& w)
    {
        w.hide();
    }

}       // of namespace Simple_graphics
