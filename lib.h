#ifndef lib
#define lib

typedef struct
{
	double R;
	double G;
	double B;
}Color;

typedef struct point_node
{
	double x;
	double y;
	int jump;
	struct point_node *next;
}Point2D;

typedef struct text_node
{
	int flag;
	int num;
	double x;
	double y;
}Text;

typedef struct tree_node
{
	int num;
	struct tree_node *left;
	struct tree_node *right;
}Tree;

typedef struct fig_node
{
	double width;
	double height;
	double thickness;
	double resolution;
	Color c;
	Text text;
	Point2D *point;
	struct fig_node *next_figure;
}Figure;

Figure *start_figure(double width, double height);

void set_thickness_resolution(Figure *fig, double thickness, double resolution);

void set_color(Figure *fig, Color c);

void draw_fx(Figure *fig, double f(double x), double start_x, double end_x);

void draw_polyline(Figure *fig, Point2D *poly_line, int n);

void draw_circle(Figure *fig, Point2D *center, double r);

void draw_ellipse(Figure *fig, Point2D *center, double a_point, double b_point);

void draw_binary_tree(Figure *fig, Tree *root, Point2D *center);

void scale_figure(Figure *fig, double scale_x, double scale_y);

void resize_figure(Figure *fig, Point2D start_roi, Point2D end_roi);

void append_figures(Figure *fig1, Figure *fig2);

void export_eps(Figure *fig, char *file_name);

void export_svg(Figure *fig, char *file_name);

void import_svg(char *file_name, Figure *fig);

void draw_koch_snowflake(Figure *fig, Point2D *center, double size, int num_iterations);

void draw_fractal_tree(Figure *fig, Point2D *center, double size, int num_iterations);

void draw_fractal_atree(Figure *fig, Point2D *center, double size, int num_iterations);

void draw_fractal_circle(Figure *fig, Point2D *center, double radius);

void draw_fractal_twice_circle(Figure *fig, Point2D *center, double radius);

void draw_fractal_line(Figure *fig, Point2D *center, double size);

void draw_sierpinksi_triangle(Figure *fig, Point2D *center, double size);

#endif
