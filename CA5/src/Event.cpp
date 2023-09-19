#include "Event.hpp"

using namespace std;


void process_event(Window *window, Player &player, Enemy *enemy)
{
    static Point mouse_position;
    static bool is_clicked;
    char tower_type;
    while (window->has_pending_event())
    {
        Event event = window->poll_for_event();
        switch (event.get_type())
        {
        case Event::QUIT:
            exit(0);
            break;
        case Event::LCLICK:
            is_clicked = true;
            mouse_position = event.get_mouse_position();
            break;
        case Event::KEY_PRESS:
            if (is_clicked)
            {
                tower_type = event.get_pressed_key();
                player.build_towers(mouse_position, tower_type, enemy);
                is_clicked = false;
                break;
            }
        }
    }
}