// 
// Birthday project
//

#ifndef BD_BIRTHDAY_WIN_H
#define BD_BIRTHDAY_WIN_H

#include <memory>
#include "./gui/Window.hpp"
#include "./gui/Shape.hpp"
#include "Widget_factory.hpp"
#include "Color_scheme.hpp"

using namespace Simple_graphics;

class Birthday_win : public Simple_graphics::Window {
    public:
        Birthday_win(Point tl, int w, int h, const std::string& title,
                Widget_factory&);

    private:
        Text prompt;
        Text date_err;

        std::vector<Text> results;
        void fill_results(std::vector<std::string>&);

        std::unique_ptr<In_box> year;
        std::unique_ptr<In_box> month;
        std::unique_ptr<In_box> day;
        std::unique_ptr<Button> submit;
        std::unique_ptr<Button> reset;

        std::unique_ptr<Color_scheme> colors;

        void show_prompt();
        void clear_prompt();
        void show_results();
        void clear_results();

        void submit_pressed();
        void reset_pressed();

        static void cb_submit(Fl_Widget*, void* data)
        {
            static_cast<Birthday_win*>(data)->submit_pressed();
        }

        static void cb_reset(Fl_Widget*, void* data)
        {
            static_cast<Birthday_win*>(data)->reset_pressed();
        }
};

#endif  // BD_BIRTHDAY_WIN_H
