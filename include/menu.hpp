#include <ncurses.h>
#include "constants.hpp"

#pragma once

class Menu{
    public:
    Menu(): menu_items_{"Game", "Exit"}{
    }
    void print_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices) {
        int x, y, i;
        x = 2;
        y = 2;
        box(menu_win, 0, 0);
        for (i = 0; i < n_choices; ++i) {
            if (highlight == i + 1) {
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, y, x, "%s", choices[i]);
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, y, x, "%s", choices[i]);
            }
            ++y;
        }
        wrefresh(menu_win);
    }

    void RenderMenu(){
        clear();

        menu_win_ = newwin(10, 40, kMenuWindow_X, kMenuWindow_Y);
        keypad(menu_win_, TRUE);
        mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");

        int highlight = 1;
        int choice = 0;
        print_menu(menu_win_, highlight, menu_items_, kAmountOfMenuItems);

        while (1) {
        user_input_ = wgetch(menu_win_);
        switch (user_input_) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = kAmountOfMenuItems;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == kAmountOfMenuItems)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        print_menu(menu_win_, highlight, menu_items_, kAmountOfMenuItems);
        if (choice != 0)
            break;
    }

        refresh();
    }
    private:
    WINDOW *menu_win_;
    const char* menu_items_[kAmountOfMenuItems];
    char user_input_;
};