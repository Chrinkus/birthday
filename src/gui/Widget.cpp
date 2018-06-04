//
// FLTK Abstraction Library
//

#include "Widget.hpp"
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include "Fl_Justify_Input.hpp"

namespace Simple_graphics {

    void Widget::move(int dx, int dy)
    {
        hide();
        pw->position(loc.x += dx, loc.y += dy);
        show();
    }

    void Widget::set_callback(Callback pf, void* data)
    {
        pw->callback(pf, data);
        cb = pf;
    }

    void Widget::set_colors(Fl_Color lab, Fl_Color bg)
    {
        pw->labelcolor(lab);
        pw->color(bg);
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    void Button::attach(Window& win)
    {
        auto pb = std::make_unique<Fl_Button>(loc.x, loc.y, w, h, lab.c_str());
        pb->labelsize(h * 0.75);
        pw = std::move(pb);
        own = &win;
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    void In_box::attach(Window& win)
    {
        auto pi = std::make_unique<Fl_Input>(loc.x, loc.y, w, h, lab.c_str());
        pi->align(FL_ALIGN_BOTTOM);
        pi->labelsize(24);
        pi->textsize(h);
        pw = std::move(pi);
        own = &win;
    }

    void In_box::set_string(const std::string& s)
    {
        static_cast<Fl_Input*>(pw.get())->value(s.c_str());
    }

    std::string In_box::get_string() const
    {
        return std::string{ static_cast<Fl_Input*>(pw.get())->value() };
    }

    void In_box::set_font(Fl_Font f)
    {
        static_cast<Fl_Input*>(pw.get())->textfont(f);
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    void Aligned_in_box::attach(Window& win)
    {
        auto pa = std::make_unique<Fl_Justify_Input>(loc.x, loc.y, w, h,
                lab.c_str());
        pa->align(FL_ALIGN_BOTTOM);
        pa->labelsize(24);
        pa->textsize(h);
        pw = std::move(pa);
        own = &win;
    }

    void Aligned_in_box::set_align(Fl_Align a)
    {
        static_cast<Fl_Justify_Input*>(pw.get())->justify(a);
    }

    void Aligned_in_box::set_string(const std::string& s)
    {
        static_cast<Fl_Justify_Input*>(pw.get())->value(s.c_str());
    }

    std::string Aligned_in_box::get_string() const
    {
        return std::string{
            static_cast<Fl_Justify_Input*>(pw.get())->value()
        };
    }

}       // of namespace Simple_graphics
