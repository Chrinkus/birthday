// 
// birthday project
//

#include <iostream>
#include <FL/Fl.H>
#include "Prompt_window.hpp"

using namespace Simple_graphics;

int main()
{
    constexpr int x_max = 800;
    constexpr int y_max = 450;

    Widget_factory fac;
    Prompt_window pwin {Point{100, 100}, x_max, y_max, "Birthday", fac};
    return Fl::run();
}
