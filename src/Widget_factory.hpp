// 
// Widget_factory class
//
// The idea here is to make it easy to change look and feel by swapping the
// supplied factory to the Window class.
//

#ifndef BD_WIDGET_FACTORY_H
#define BD_WIDGET_FACTORY_H

#include "./gui/Widget.hpp"
#include "./gui/Window.hpp"

using namespace Simple_graphics;

class Widget_factory {
    public:
        Widget_factory() = default;

        virtual ~Widget_factory() = default;

        virtual std::unique_ptr<In_box> create_in_box(
                Simple_graphics::Window&,
                std::string,
                int w = default_width,
                int h = default_height );

        virtual std::unique_ptr<Button> create_button(
                Simple_graphics::Window&,
                std::string,
                int w = default_width,
                int h = default_height );

    protected:
        Point origin {0, 0};
        static constexpr int default_width = 128;
        static constexpr int default_height = 32;
};

class Thin_factory : public Widget_factory {
    public:
        Thin_factory() = default;

        std::unique_ptr<In_box> create_in_box(
                Simple_graphics::Window&,
                std::string,
                int w = default_width,
                int h = default_height ) override;

        std::unique_ptr<Button> create_button(
                Simple_graphics::Window&,
                std::string,
                int w = default_width,
                int h = default_height ) override;

    private:
        Fl_Boxtype in_box_type = FL_THIN_DOWN_BOX;
        Fl_Boxtype button_type = FL_THIN_UP_BOX;
};

#endif  // BD_WIDGET_FACTORY_H
