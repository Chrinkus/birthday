// 
// Birthday project
//

#include "Prompt_window.hpp"
#include "date_time_ext.hpp"        // get_date_results
#include <sstream>
#include <iostream>                 // test

Prompt_window::Prompt_window(Point tl, int w, int h, const std::string& title,
        Widget_factory& factory)
    : Window{tl, w, h, title},
    prompt  {"Enter date of birth:", Point{0, 0}, Text::Align::center},
    date_err{"", Point{0, 0}, Text::Align::center},
    year    {factory.create_large_in_box("YYYY")},
    month   {factory.create_small_in_box("MM")},
    day     {factory.create_small_in_box("DD")},
    submit  {factory.create_button("SUBMIT")},
    reset   {factory.create_button("RESET")}
{
    const int x_mid = x_max() / 2;
    const int y_mid = y_max() / 2;
    const int horiz_pad = 12;
    const int vert_pad = 24;

    // Shapes
    attach(prompt);
    prompt.move(x_mid, y_mid - year->get_height() - vert_pad);
    prompt.set_color(FL_WHITE);
    prompt.set_font(FL_HELVETICA_BOLD);
    prompt.set_size(48);

    attach(date_err);
    date_err.move(x_mid, y_mid + vert_pad * 2);
    date_err.set_color(FL_MAGENTA);
    date_err.set_size(24);

    // Widgets
    const int input_row_w = year->get_width() + month->get_width() +
                            day->get_width() + 2 * horiz_pad;
    const int year_x = x_mid - input_row_w / 2;
    const int month_x = year_x + year->get_width() + horiz_pad;
    const int day_x = month_x + month->get_width() + horiz_pad;
    const int input_row_y = y_mid - year->get_height();
    
    attach(*year);
    attach(*month);
    attach(*day);

    year->move(year_x, input_row_y);
    month->move(month_x, input_row_y);
    day->move(day_x, input_row_y);

    year->set_colors(FL_WHITE, FL_WHITE);
    month->set_colors(FL_WHITE, FL_WHITE);
    day->set_colors(FL_WHITE, FL_WHITE);

    attach(*submit);
    submit->move(x_mid - submit->get_width() / 2, y_mid + vert_pad * 3);
    submit->set_colors(FL_BLACK, FL_WHITE);
    submit->set_callback(cb_submit, this);

    attach(*reset);
    reset->move(x_mid - reset->get_width() / 2, y_mid + vert_pad * 3);
    reset->set_colors(FL_BLACK, FL_WHITE);
    reset->set_callback(cb_reset, this);
    reset->hide();

    end();
    color(FL_BLACK);
    show();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

void Prompt_window::show_prompt()
{
    attach(prompt);
    attach(date_err);

    year->show();
    month->show();
    day->show();
    submit->show();
}

void Prompt_window::clear_prompt()
{
    date_err.set_content("");
    detach_shapes();

    year->set_string();         // clear In_box's
    month->set_string();
    day->set_string();

    year->hide();
    month->hide();
    day->hide();
    submit->hide();
}

void Prompt_window::show_results()
{
    for (auto& t : results)
        attach(t);

    reset->show();
}

void Prompt_window::clear_results()
{
    detach_shapes();
    results.clear();

    reset->hide();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

void Prompt_window::fill_results(std::vector<std::string>& vs)
{
    results.emplace_back(Text{std::move(vs[0]),
                              prompt.point(0),
                              Text::Align::center});
    results.back().set_size(36);
    results.back().set_color(FL_WHITE);

    const int fontsize = 24;

    for (auto i = 1; i < vs.size(); ++i) {
        Point loc {x_max() / 6,
                   static_cast<int>(prompt.point(0).y + i * 1.5 * fontsize)};

        results.emplace_back(Text{std::move(vs[i]), loc, Text::Align::left});
        results.back().set_size(fontsize);
        results.back().set_color(FL_WHITE);
    }
}

void Prompt_window::submit_pressed()
{
    std::stringstream ss;
    ss << year->get_string() << '-'
       << month->get_string() << '-'
       << day->get_string();

    try {
        auto date_strings = get_date_results(ss.str());
        fill_results(date_strings);
    }
    catch(...) {
        date_err.set_content(ss.str() + " is not a valid date");
        redraw();
        return;
    }

    clear_prompt();
    show_results();
}

void Prompt_window::reset_pressed()
{
    clear_results();
    show_prompt();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

std::unique_ptr<In_box>
Widget_factory::create_large_in_box(std::string label)
{
    return std::make_unique<In_box>(origin, large_box_w, box_h,
                                    std::move(label));
}

std::unique_ptr<In_box>
Widget_factory::create_small_in_box(std::string label)
{
    return std::make_unique<In_box>(origin, small_box_w, box_h,
                                    std::move(label));
}

std::unique_ptr<Button>
Widget_factory::create_button(std::string label)
{
    return std::make_unique<Button>(origin, button_w, box_h,
                                    std::move(label));
}
