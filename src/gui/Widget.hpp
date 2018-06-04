//
// FLTK Abstraction Library
//
// Widget abstraction for Fl_Widget warning:
// - avoid altering widget until after attachment
// - attachment is when Fl_Widget is instantiated
// - cannot access Fl_Widget inherited functions until *AFTER* widget is
//   attached to Window.
//

#ifndef SG_WIDGET_H
#define SG_WIDGET_H

#include <FL/Fl_Widget.H>
#include <string>
#include "Point.hpp"

namespace Simple_graphics {

    using Callback = void (*)(Fl_Widget*, void*);

    class Window;               // forward declaration

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    class Widget {
        public:
            Widget(Point xy, int ww, int hh, const std::string& s = "",
                   Callback pf = nullptr)
                : loc{xy}, w{ww}, h{hh}, lab{s}, cb{pf} { }

            virtual void move(int dx, int dy);
            virtual void hide() { pw->hide(); }
            virtual void show() { pw->show(); }
            virtual void attach(Window&) = 0;

            virtual void set_callback(Callback, void*);
            virtual void set_colors(Fl_Color lab, Fl_Color bg);

            int get_width() const { return w; }
            int get_height() const { return h; }

            virtual ~Widget() = default;

        protected:
            Point loc;
            int w;
            int h;
            std::string lab;
            Callback cb;
            Window* own;
            std::unique_ptr<Fl_Widget> pw;
    };

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    struct Button : Widget {
        Button(Point xy, int ww, int hh, const std::string& ss)
            : Widget{xy, ww, hh, ss} { }

        void attach(Window&) override;
    };

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    
    struct In_box : Widget {
        In_box(Point xy, int ww, int hh, const std::string& ss)
            : Widget{xy, ww, hh, ss} { }

        void attach(Window&) override;

        void set_string(const std::string& s = "");
        std::string get_string() const;

        void set_font(Fl_Font);
    };

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    struct Aligned_in_box : Widget {
        Aligned_in_box(Point xy, int ww, int hh, const std::string& ss)
            : Widget{xy, ww, hh, ss} { }

        void attach(Window&) override;

        void set_align(Fl_Align);

        void set_string(const std::string& s = "");
        std::string get_string() const;
    };

}       // of namespace Simple_graphics

#endif  // SG_WIDGET_H
