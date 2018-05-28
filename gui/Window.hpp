//
// FLTK Abstraction Library
//

#ifndef SG_WINDOW_H
#define SG_WINDOW_H

#include <FL/Fl_Double_Window.H>
#include <string>
#include <vector>
#include "Point.hpp"

namespace Simple_graphics {

    class Shape;
    class Widget;

    class Window : public Fl_Double_Window {
        public:
            Window(Point tl, int ww, int hh, const std::string& ss)
                : Fl_Double_Window{tl.x, tl.y, ww, hh, ss.c_str()}
            {
                init();
            }

            void attach(Shape& s) { shapes.push_back(&s); }
            void attach(Widget&);

            void detach_shapes() { shapes.clear(); }

            int x_max() const { return w(); }
            int y_max() const { return h(); }

            void draw();

        private:
            std::vector<Shape*> shapes;

            void init() { show(); }
    };
}

#endif
