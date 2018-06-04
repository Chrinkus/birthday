//
// Justified Input Widget
//
// written by: erco 12/16/13
//

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>

class Fl_Justify_Input : public Fl_Group {
    public:
        Fl_Justify_Input(int X, int Y, int W, int H, const char* L = 0);

        void justify(Fl_Align val) { box->align(val | FL_ALIGN_INSIDE); }
        Fl_Align justify() const { return box->align(); }

        void textsize(Fl_Fontsize s) { inp->textsize(s); box->labelsize(s); }
        Fl_Fontsize textsize() const { return inp->textsize(); }

        void value(const char* val);
        const char* value() const;

        int handle(int e);

    private:
        /*
        std::unique_ptr<Fl_Input> inp;
        std::unique_ptr<Fl_Box> box;
        */
        Fl_Input* inp;
        Fl_Box* box;
};
