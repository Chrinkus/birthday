//
// FLTK Abstraction Library
//

#ifndef SG_SHAPE_H
#define SG_SHAPE_H

#include <FL/fl_draw.H>         // Needed for FL enumerations(Color, Font, etc)
#include <string>
#include <vector>
#include "Point.hpp"

namespace Simple_graphics {

    class Shape {
        public:
            void draw() const;      // handles color and calls draw_lines()

            void set_color(Fl_Color c) { lcolor = c; }
            Fl_Color get_color() const { return lcolor; }

            Point point(int i) const { return points[i]; }

            virtual void move(int dx, int dy);

            virtual ~Shape() = default;

        protected:
            Shape() = default;

            virtual void draw_lines() const;

            void add(Point p) { points.push_back(p); }

        private:
            std::vector<Point> points;
            Fl_Color lcolor { fl_color() };
    };

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    struct Line : Shape {
        Line(Point p1, Point p2) { add(p1); add(p2); }
    };

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

    class Text : public Shape {
        public:
            enum class Align { left, center, right };
            Text(const std::string& s, Point bl, Align a);

            void draw_lines() const override;

            void measure() const;

            // changing any of these requires new measurement
            void set_font(int f) { font = f; measured = false; }
            void set_size(int s) { size = s; measured = false; }
            void set_content(const std::string&);

        private:
            std::string content;
            Align align;
            int font { fl_font() };
            int size { 18 };

            // fl_measure requires width and height out-params
            mutable int width = 0;
            mutable int height = 0;
            mutable bool measured = false;  // has Text changed?
    };

}       // of namespace Simple_graphics

#endif  // SG_SHAPE_H
