#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <allegro5\allegro_native_dialog.h> 
#include "logic.h"


void set_graphics_x_o(int x, int y, logic& game_logic);
void draw_grid(int width, int height);
void draw_objects(int x, int y, int row, int col, logic& game_logic);
void game_message(bool& gameover, logic& game_logic); //using for testing, ignore later
void draw_circle(int x, int y);
void draw_square(int x, int y);
void draw_triangle(int x, int y);
void draw_ellipse(int x, int y);
void draw_diamond(int x, int y);
void draw_filled_circle(int x, int y);
void draw_rectangle(int x, int y);

//all of these are from tic tac toe, delete later
void draw_x(int x, int y);
void draw_o(int x, int y);
void game_message(bool& gameover, logic& game_logic);
void turn_xo(int x, int y, int& turn, int boardx, int boardy, logic& game_logic);

int main(void)
{
	logic game_logic;
	game_logic.random_create(12);
	int posX = 0, posY = 0;
	bool gameover = false;
	ALLEGRO_DISPLAY* Screen = NULL;
	int width = 640, height = 550;
	int game_height = 480;

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

	bool draw = false, done = false;;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_register_event_source(event_queue, al_get_mouse_event_source());
	draw_grid(width, game_height);
	float box_width = width / 5.0f;
	float box_height = game_height / 5.0f;

	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			if (row == 4 && col == 4)
				continue; //skip bottom right box

			float x = col * box_width + box_width / 2;
			float y = row * box_height + box_height / 2;

			draw_objects(x, y, row, col, game_logic);
		}
	}
	//game_message(gameover, game_logic);

	al_flip_display();
	while (!done && !gameover)
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
				posX = ev.mouse.x;
				posY = ev.mouse.y;

				draw = true;
			}
		}
		draw_grid(width, game_height);
		float box_width = width / 5.0f;
		float box_height = game_height / 5.0f;

		for (int row = 0; row < 5; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (row == 4 && col == 4)
					continue; 

				float x = col * box_width + box_width / 2;
				float y = row * box_height + box_height / 2;

				draw_objects(x, y, row, col, game_logic);
			}
		}
		game_message(gameover, game_logic);
		if (draw)
		{

			set_graphics_x_o(posX, posY, game_logic);

			draw = false;
		}
		al_flip_display();
	}
	al_rest(5.0);
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
	else if (shape == TRIANGLE) {
		draw_triangle(x, y);
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
}

//drawing shape functions, simple so moving them down
void draw_circle(int x, int y) {
	al_draw_circle(x, y, 10, al_map_rgb(255, 192, 203), 30);
}
void draw_square(int x, int y) { //NEEDS FIXING so it looks like a square
	al_draw_filled_rectangle(x - 10, y + 30, x + 10, y - 30, al_map_rgb(0, 0, 255));
}
void draw_triangle(int x, int y) {
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
void draw_rectangle(int x, int y) {
	al_draw_filled_rectangle(x + 30, y - 10, x - 30, y + 10, al_map_rgb(0, 255, 0)); //only to be used for get_status()
}

//leftovers from tic tac toe, remove later
void draw_x(int x, int y)
{
	al_draw_line(x - 106, y - 62, x + 106, y + 62, al_map_rgb(255, 0, 0), 2);
	al_draw_line(x - 106, y + 62, x + 106, y - 62, al_map_rgb(255, 0, 0), 2);
}
void draw_o(int x, int y)
{
	al_draw_circle(x, y, 62, al_map_rgb(255, 255, 0), 4);

}
void turn_xo(int x, int y, int& turn, int boardx, int boardy, logic& game_logic)
{
	ALLEGRO_FONT* font = al_load_font("GROBOLD.ttf", 24, 0);
}
void set_graphics_x_o(int x, int y, logic& game_logic)
{
	static int turn = 0;
	if ((x < 213) && (y < 125))
	{
		turn_xo(106, 62, turn, 0, 0, game_logic);
	}
	else if ((x > 213) && (x < 426) && (y < 125))
	{
		turn_xo(319, 62, turn, 0, 1, game_logic);
	}
	else if ((x > 426) && (y < 125))
	{
		turn_xo(533, 62, turn, 0, 2, game_logic);
	}
	else if ((x < 213) && (y > 125) && (y < 250))
	{
		turn_xo(106, 186, turn, 1, 0, game_logic);

	}
	else if ((x > 213) && (x < 426) && (y > 125) && (y < 250))
	{
		turn_xo(319, 186, turn, 1, 1, game_logic);
	}
	else if ((x > 426) && (y > 125) && (y < 250))
	{
		turn_xo(533, 186, turn, 1, 2, game_logic);
	}
	else if ((x < 213) && (y > 250) && (y < 375))
	{
		turn_xo(106, 314, turn, 2, 0, game_logic);

	}
	else if ((x > 213) && (x < 426) && (y > 250) && (y < 375))
	{
		turn_xo(319, 314, turn, 2, 1, game_logic);
	}
	else if ((x > 426) && (y > 250) && (y < 375))
	{
		turn_xo(533, 314, turn, 2, 2, game_logic);
	}
}

void game_message(bool& gameover, logic& game_logic)
{
	//game_logic.done(tie, xwon, owon);
	ALLEGRO_FONT* font = al_load_font("GROBOLD.ttf", 24, 0);
	al_draw_filled_rectangle(0, 480, 640, 550, al_map_rgb(200, 200, 200));
	al_draw_text(font, al_map_rgb(255, 255, 255), 320, 515, ALLEGRO_ALIGN_LEFT, "testing");

}