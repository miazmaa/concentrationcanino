#include"logic.h"

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

int logic::get_shape(int row, int col)
{
	return pattern[row][col];
}
void logic::set_shape(int row, int col, int shape) {
	pattern[row][col] = shape;
}
void logic::random_create(int num_shapes) {


}
bool logic::finished() {
	return false;
}