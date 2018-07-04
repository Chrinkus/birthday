#include "Widget_factory.hpp"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Widget_factory
std::unique_ptr<In_box>
Widget_factory::create_in_box(Window& win, std::string label, int w, int h)
{
    auto pw = std::make_unique<In_box>(origin, w, h, std::move(label));
    win.attach(*pw);
    return pw;
}

std::unique_ptr<Button>
Widget_factory::create_button(Window& win, std::string label, int w, int h)
{
    auto pw = std::make_unique<Button>(origin, w, h, std::move(label));
    win.attach(*pw);
    return pw;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Thin_factory
std::unique_ptr<In_box>
Thin_factory::create_in_box(Window& win, std::string label, int w, int h)
{
    auto pw = Widget_factory::create_in_box(win, std::move(label), w, h);
    pw->set_box(in_box_type);
    return pw;
}

std::unique_ptr<Button>
Thin_factory::create_button(Window& win, std::string label, int w, int h)
{
    auto pw = Widget_factory::create_button(win, std::move(label), w, h);
    pw->set_box(button_type);
    return pw;
}
