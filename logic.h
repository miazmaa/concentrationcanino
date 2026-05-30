enum Shape
{
	NONE = 0,
	CIRCLE,
	SQUARE,
	TRIANGLE,
	ELLIPSE,
	DIAMOND,
	FILLED_CIRCLE,
};
class logic
{
public:
	logic();
	void clearGame();
	bool compare(int row1, int col1, int row2, int col2); //will compare the primitive in 2 boxes
	Shape get_shape(int row, int col);
	void set_shape(int row, int col, Shape shape);
	void random_create(int num_shapes);
	bool finished();

private:
	Shape pattern[5][5];
	bool already_played[5][5];
};
