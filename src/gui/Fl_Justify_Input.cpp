//
// Details in header
//

#include "Fl_Justify_Input.hpp"

Fl_Justify_Input::Fl_Justify_Input(int X, int Y, int W, int H, const char* L)
    : Fl_Group(X, Y, W, H, L)
{
    Fl_Group::box(FL_NO_BOX);

    //box = std::make_unique<Fl_Box>(X, Y, W, H);
    box = new Fl_Box(X,Y,W,H);
    box->color(FL_WHITE);
    box->box(FL_DOWN_BOX);

    //inp = std::make_unique<Fl_Input>(X, Y, W, H);
    inp = new Fl_Input(X,Y,W,H);
    inp->hide();
    inp->color(FL_WHITE);

    end();
}

void Fl_Justify_Input::value(const char* val)
{
    box->copy_label(val);
    inp->value(val);
}

const char* Fl_Justify_Input::value() const
{
    return inp->value();
}

int Fl_Justify_Input::handle(int e)
{
    switch (e) {
        case FL_PUSH:
        case FL_FOCUS:
            if (!inp->visible()) {
                box->hide();
                inp->show();
                inp->value(box->label());
                redraw();
            }
            break;
        case FL_UNFOCUS:
            if (inp->visible()) {
                box->show();
                inp->hide();
                box->label(inp->value());
                redraw();
            }
            break;
        default:
            break;
    }
    return (Fl_Group::handle(e));
}
