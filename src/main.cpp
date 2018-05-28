// 
// Birthday app
//
// Create a window that pretty much runs itself.
//

#include <FL/Fl.H>
#include "Birthday_win.hpp"

using namespace Simple_graphics;

int main()
{
    constexpr int x_max = 800;
    constexpr int y_max = 450;
    constexpr Point top_left {100, 100};

    Widget_factory fac;             // factory determines widget sizes
    Birthday_win pwin {top_left, x_max, y_max, "Birthday", fac};
    return Fl::run();
}
