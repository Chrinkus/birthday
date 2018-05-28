//
// FLTK Abstraction Library
//

#include "Shape.hpp"

namespace Simple_graphics {

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    void Shape::move(int dx, int dy)
    {
        for (auto& p : points) {
            p.x += dx;
            p.y += dy;
        }
    }

    void Shape::draw() const
    {
        fl_color(lcolor);
        draw_lines();
    }

    void Shape::draw_lines() const
    {
        if (1 < points.size())
            for (auto i = 1; i < points.size(); ++i)
                fl_line(points[i-1].x, points[i-1].y,
                        points[i].x, points[i].y);
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    Text::Text(const std::string& s, Point bl, Align a)
        : content{s}, align{a}
    {
        add(bl);
    }

    void Text::draw_lines() const
    {
        fl_font(font, size);

        if (!measured)
            measure();

        const auto pt = point(0);

        switch (align) {
            case Text::Align::left:
                fl_draw(content.c_str(), pt.x, pt.y);
                break;
            case Text::Align::center:
                fl_draw(content.c_str(), pt.x - width / 2, pt.y);
                break;
            case Text::Align::right:
                fl_draw(content.c_str(), pt.x - width, pt.y);
                break;
        }
    }

    void Text::measure() const
    {
        width = 0;                  // FLTK requirement
        fl_measure(content.c_str(), width, height);
        measured = true;
    }

    void Text::set_content(const std::string& s)
    {
        content = s;
        measured = false;
    }
}
