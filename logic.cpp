#include"logic.h"
#include <ctime>
#include <cstdlib>
logic::logic()
{
	clearGame();
}
void logic::clearGame() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			pattern[i][j] = Shape::NONE;
			already_played[i][j] = false;
		}
	}
}
bool logic::compare(int row1, int col1, int row2, int col2) {
	if (pattern[row1][col1] == pattern[row2][col2]) {
		already_played[row1][col1] = true;
		already_played[row2][col2] = true;
		return true;
	}
	return false;
}

Shape logic::get_shape(int row, int col)
{
	return pattern[row][col];
}
void logic::set_shape(int row, int col, Shape shape)
{
	pattern[row][col] = shape;
}
void logic::random_create(int num_shapes) {
	clearGame();
	srand(time(NULL)); 
	Shape shapes[24];
	int index = 0;

	for (int i = 0; i < 12; i++) {
		int shapeValue = (i % 6) + 1;

		shapes[index] = (Shape)shapeValue;
		index++;

		shapes[index] = (Shape)shapeValue;
		index++; //puts each shape in the array twice
	}
	for (int i = 23; i > 0; i--)
	{
		int j = rand() % (i + 1);

		Shape temp = shapes[i];
		shapes[i] = shapes[j];
		shapes[j] = temp;
	}
	index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 4 && j == 4) {
				pattern[i][j] = NONE; //saves bottom right square for draw_status
			}
			else {
				pattern[i][j] = shapes[index];
				index++;
			}
			already_played[i][j] = false;
		}
	}

}
bool logic::finished() {
	return false;
}