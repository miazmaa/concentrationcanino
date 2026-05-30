#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <allegro5\allegro_native_dialog.h> 
#include "logic.h"

int mx, my;

void get_mouse_input(int x, int y, logic& game_logic, int& first_row, int& first_column, int& second_row, int& second_column);
void draw_grid(int width, int height);
void draw_objects(int x, int y, int row, int col, logic& game_logic);
void draw_status(int x, int y);
void draw_circle(int x, int y);
void draw_square(int x, int y);
void draw_filled_triangle(int x, int y);
void draw_ellipse(int x, int y);
void draw_diamond(int x, int y);
void draw_filled_circle(int x, int y);
void draw_line(int x, int y);
void draw_triangle(int x, int y);
void draw_bullet(int x, int y);
void draw_ship(int x, int y);
void draw_oval(int x, int y);
void draw_arrow(int x, int y);

int main(void)
{
	logic game_logic;
	game_logic.random_create(12);
	ALLEGRO_DISPLAY* Screen = NULL;
	int width = 640, height = 550;
	int game_height = 480;
	int first_row = -1, first_column = -1;
	int second_row = -1, second_column = -1;
	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}
	Screen = al_create_display(width, height);
	if (Screen == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(Screen, "Error!", "Failed to initialize the mouse!\n.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT* bold = al_load_font("GROBOLD.ttf", 24, 0);
	bold = al_load_ttf_font("GROBOLD.ttf", 20, 0);
	if (!bold) {
		al_show_native_message_box(Screen, "Error!", "Failed to load font.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}
	bool done = false;
	bool matching = false;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				mx = ev.mouse.x;
				my = ev.mouse.y;
				get_mouse_input(mx, my, game_logic, first_row, first_column, second_row, second_column);
			}
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));
		draw_grid(width, game_height);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)
			{
				if (i == 4 && j == 4)
				{
					int x = j * 128 + 64;
					int y = i * 96 + 48;
					draw_status(x, y);
				}
				else if (game_logic.is_played(i, j)) {
					int x = j * 128 + 64;
					int y = i * 96 + 48;
					draw_objects(x, y, i, j, game_logic);
				}
			}
		}
		if (first_row != -1 && first_column != -1) {
			draw_objects(first_column * 128 + 64, first_row * 96 + 48, first_row, first_column, game_logic);
		}
		if (second_row != -1 && second_column != -1) {
			draw_objects(second_column * 128 + 64, second_row * 96 + 48, second_row, second_column, game_logic);
		}
		al_draw_filled_rectangle(0, game_height, width, height, al_map_rgb(200, 200, 200));
		al_draw_text(bold, al_map_rgb(255, 255, 255), 20, game_height + 20, ALLEGRO_ALIGN_LEFT, "Press the rectangle to reset your game.");
		al_flip_display();
	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);						//destroy our display object

	return 0;
}
void draw_grid(int width, int game_height)
{
	float box_width = (float)width / 5.0f;
	float box_height = (float)game_height / 5.0f;
	for (int i = 1; i < 5; i++) { //i starts at 1 bc the borders don't need lines
		float y = i * box_height;
		al_draw_line(0, y, width, y, al_map_rgb(255, 255, 255), 2);
	}
	for (int i = 1; i < 5; i++) {
		float x = i * box_width;
		al_draw_line(x, 0, x, game_height, al_map_rgb(255, 255, 255), 2);
	}
}
void draw_objects(int x, int y, int row, int col, logic& game_logic) {
	Shape shape;
	shape = game_logic.get_shape(row, col);

	if (shape == CIRCLE) {
		draw_circle(x, y);
	}
	else if (shape == SQUARE) {
		draw_square(x, y);
	}
	else if (shape == FILLED_TRIANGLE) {
		draw_filled_triangle(x, y);
	}
	else if (shape == ELLIPSE) {
		draw_ellipse(x, y);
	}
	else if (shape == DIAMOND) {
		draw_diamond(x, y);
	}
	else if (shape == FILLED_CIRCLE) {
		draw_filled_circle(x, y);
	}
	else if (shape == LINE) {
		draw_line(x, y);
	}
	else if (shape == TRIANGLE) {
		draw_triangle(x, y);
	} 
	else if (shape == BULLET) {
		draw_bullet(x, y);
	}
	else if (shape == SHIP) {
		draw_ship(x, y);
	}
	else if (shape == OVAL) {
		draw_oval( x,  y);
	} 
	else if (shape == ARROW) {
		draw_arrow(x, y);
	}
}
void get_mouse_input(int x, int y, logic& game_logic, int& first_row, int& first_column, int& second_row, int& second_column)
{

	int row = y / 96;
	int col = x / 128;
	if (row < 0 || row > 4 || col < 0 || col > 4) {
		return;
	}
	if (row == 4 && col == 4) {
		game_logic.random_create(12);
		first_row = -1;
		first_column = -1;
		second_row = -1;
		second_column = -1;
		return; //reset bottom right
	}
	if (game_logic.is_played(row, col)) {
		return;
	}
	if (first_row == -1 && first_column == -1)
	{
		first_row = row;
		first_column = col;
		draw_objects(col * 128 + 64, row * 96 + 48, row, col, game_logic);
		al_flip_display();
		return;
	}
	if (second_row == -1 && second_column == -1)
	{
		if (row == first_row && col == first_column) {
			return;
		}
		second_row = row;
		second_column = col;
		draw_objects(col * 128 + 64, row * 96 + 48, row, col, game_logic);
		al_flip_display();
		bool match = game_logic.compare(first_row, first_column, second_row, second_column);
		if (!match)
		{
			al_rest(5.0);
		}
		first_row = -1;
		first_column = -1;
		second_row = -1;
		second_column = -1;
	}

}
void draw_status(int x, int y) {
	al_draw_filled_rectangle(x + 30, y - 10, x - 30, y + 10, al_map_rgb(0, 255, 0)); //only to be used for get_status()
}
//drawing shape functions, simple so moving them down
void draw_circle(int x, int y) {
	al_draw_circle(x, y, 30, al_map_rgb(255, 192, 203), 3);
}
void draw_square(int x, int y) {
	al_draw_filled_rectangle(x - 30, y - 30, x + 30, y + 30, al_map_rgb(0, 0, 255));
}
void draw_filled_triangle(int x, int y) {
	al_draw_filled_triangle(x, y - 20, x + 30, y - 20, x - 30, y, al_map_rgb(255, 0, 0));
}
void draw_ellipse(int x, int y) {
	al_draw_filled_ellipse(x, y, 30, 20, al_map_rgb(255, 165, 0));
}
void draw_diamond(int x, int y) {
	al_draw_filled_triangle(x, y - 35, x - 35, y, x + 35, y, al_map_rgb(255, 255, 0));
	al_draw_filled_triangle(x, y + 35, x + 35, y, x - 35, y, al_map_rgb(255, 255, 0));
}
void draw_filled_circle(int x, int y) {
	al_draw_filled_circle(x, y, 30, al_map_rgb(93, 63, 211));
}
void draw_line(int x, int y) {
	al_draw_line(x + 20, y + 20, x, y, al_map_rgb(128, 128, 128), 5);
}
void draw_triangle(int x,int y) {
	al_draw_triangle(x - 25, y, x + 25, y + 20, x, y, al_map_rgb(64, 244, 212),5);
}
void draw_bullet(int x, int y) {
	al_draw_rectangle(x - 18, y - 18, x + 18, y + 18, al_map_rgb(70, 0, 70), 2);
	al_draw_line(x - 18, y - 18, x + 18, y + 18, al_map_rgb(12, 72, 153), 8);
}
void draw_ship(int x, int y) {
	al_draw_filled_ellipse(x, y, 40, 29, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(x, y, 18, al_map_rgb(93, 63, 211));
	al_draw_filled_rectangle(x - 5, y - 5, x + 5, y + 5, al_map_rgb(0, 0, 0));
	al_draw_filled_triangle(x, y - 44, x - 10, y - 25, x + 10, y - 25, al_map_rgb(0, 0, 255));
}
void draw_oval(int x, int y) {
	al_draw_ellipse(x, y, 25, 30, al_map_rgb(150, 75, 0), 5);
}
void draw_arrow(int x, int y) {
	al_draw_filled_triangle(x, y - 25, x + 20, y, x - 20, y, al_map_rgb(255, 215, 0));
	al_draw_filled_rectangle(x - 6, y, x + 6, y + 25, al_map_rgb(212, 0, 255));
}
