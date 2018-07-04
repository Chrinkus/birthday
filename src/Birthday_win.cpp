// 
// Birthday project
//

#include "Birthday_win.hpp"
#include "date_time_ext.hpp"        // get_date_results
#include <sstream>
#include <iostream>                 // test

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Birthday_win::Birthday_win(Point tl, int w, int h, const std::string& title,
        Widget_factory& factory)
    : Window{tl, w, h, title},
    prompt  {"Enter date of birth:", Point{0, 0}, Text::Align::center},
    date_err{"", Point{0, 0}, Text::Align::center},
    year    {factory.create_in_box(*this, "YYYY")},
    month   {factory.create_in_box(*this, "MM", 64)},
    day     {factory.create_in_box(*this, "DD", 64)},
    submit  {factory.create_button(*this, "SUBMIT")},
    reset   {factory.create_button(*this, "RESET")},
    colors  {std::make_unique<Color_scheme>()}
{
    /*
    colors->background  = 0x0c0f0a00;       // black
    colors->primary     = 0xffffff00;       // white
    colors->secondary   = 0xfbff1200;       // yellow
    colors->tertiary    = 0x41ead400;       // blue
    colors->auxilliary  = 0xff007f00;       // pink
    */

    const int x_mid = x_max() / 2;
    const int y_mid = y_max() / 2;
    const int horiz_pad = 12;
    const int vert_pad = 24;

    // Shapes
    attach(prompt);
    prompt.move(x_mid, y_mid - year->get_height() - vert_pad * 2);
    prompt.set_color(colors->primary);
    prompt.set_font(FL_HELVETICA_BOLD);
    prompt.set_size(48);

    attach(date_err);
    date_err.move(x_mid, y_mid + vert_pad * 2);
    date_err.set_color(colors->auxilliary);
    date_err.set_size(24);

    // Widgets
    const int input_row_w = year->get_width() + month->get_width() +
                            day->get_width() + 2 * horiz_pad;
    const int year_x = x_mid - input_row_w / 2;
    const int month_x = year_x + year->get_width() + horiz_pad;
    const int day_x = month_x + month->get_width() + horiz_pad;
    const int input_row_y = y_mid - year->get_height();
    
    year->move(year_x, input_row_y);
    month->move(month_x, input_row_y);
    day->move(day_x, input_row_y);

    year->set_colors(colors->primary, colors->primary, colors->background);
    month->set_colors(colors->primary, colors->primary, colors->background);
    day->set_colors(colors->primary, colors->primary, colors->background);

    submit->move(x_mid - submit->get_width() / 2, y_mid + vert_pad * 3);
    submit->set_colors(colors->primary, colors->secondary);
    submit->set_callback(cb_submit, this);

    reset->move(x_mid - reset->get_width() / 2, y_mid + vert_pad * 3);
    reset->set_colors(colors->primary, colors->secondary);
    reset->set_callback(cb_reset, this);
    reset->hide();

    end();
    color(colors->background);
    show();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

void Birthday_win::show_prompt()
{
    attach(prompt);
    attach(date_err);

    year->show();
    month->show();
    day->show();
    submit->show();
}

void Birthday_win::clear_prompt()
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

void Birthday_win::show_results()
{
    for (auto& t : results)
        attach(t);

    reset->show();
}

void Birthday_win::clear_results()
{
    detach_shapes();
    results.clear();

    reset->hide();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

void Birthday_win::fill_results(std::vector<std::string>& vs)
{
    results.emplace_back(Text{std::move(vs[0]),
                              prompt.point(0),
                              Text::Align::center});
    results.back().set_size(36);
    results.back().set_color(colors->primary);

    const int fontsize = 24;

    for (auto i = 1; i < vs.size(); ++i) {
        Point loc {x_max() / 6,
                   static_cast<int>(prompt.point(0).y + i * 1.5 * fontsize)};

        results.emplace_back(Text{std::move(vs[i]), loc, Text::Align::left});
        results.back().set_size(fontsize);
        results.back().set_color(colors->primary);
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

void Birthday_win::submit_pressed()
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

void Birthday_win::reset_pressed()
{
    clear_results();
    show_prompt();
}

