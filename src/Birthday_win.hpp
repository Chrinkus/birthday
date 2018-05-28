// 
// Birthday project
//

#ifndef BD_BIRTHDAY_WIN_H
#define BD_BIRTHDAY_WIN_H

#include "../gui/Window.hpp"
#include "../gui/Shape.hpp"
#include "../gui/Widget.hpp"

using namespace Simple_graphics;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

class Widget_factory {
    public:
        Widget_factory() = default;

        std::unique_ptr<In_box> create_large_in_box(std::string label);
        std::unique_ptr<In_box> create_small_in_box(std::string label);
        std::unique_ptr<Button> create_button(std::string label);

    private:
        Point origin {0, 0};
        int large_box_w = 104;
        int small_box_w = 52;
        int box_h = 36;
        int button_w = 120;
        int button_h = 24;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

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
