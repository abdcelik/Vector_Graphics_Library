#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"

#define PI 3.14159265
#define TRUE 1
#define FALSE 0

// These are my helper functions

Point2D *createPoint2D(Point2D *p);
void write_text(Figure *fig, Point2D *center, int num);
void tree_draw_helper(Figure *fig, Tree *root, Point2D *center, int depth, int situation);
void draw_tree_line(Figure *fig, Point2D *center, int r, int depth, int way);
int depthOfTree(Tree *node);
void snowflake_func(Figure *fig, double size, int num_iterations);
void add_koch(Point2D **point, double size, double slope, double x);
void free_fig(Figure *fig);
void fractal_tree_helper(Figure *fig, double center_x, double center_y, double size, int num_iterations, double current_angle, double l_add_angle, double r_add_angle);
void draw_triangle(Figure *fig, Point2D *center, double size);

/* 											*
 * In the following function				*
 * Defining a new figure and its variable	*
 *											*/

Figure *start_figure(double width, double height)
{
	Figure *fig;
	fig = (Figure*)malloc(sizeof(Figure));
	fig->width = width;
	fig->height = height;
	fig->text.flag = 0;
	fig->point = NULL;
	fig->next_figure = NULL;
	return fig;
}

/* 												*
 * In the following function					*
 * Defining figure's thickness and resolution	*
 *												*/

void set_thickness_resolution(Figure *fig, double thickness, double resolution)
{
	fig->thickness=thickness;
	fig->resolution=resolution;
}

/* 								*
 * In the following function	*
 * Defining figure's color		*
 *								*/

void set_color(Figure *fig ,Color c)
{
	fig->c.R=c.R;
	fig->c.G=c.G;
	fig->c.B=c.B;
}

/*
 * In the following function															*
 * The y point corresponding to each x point is added to the point part of the figure	*
 * The distance between two sequentially points x is 1/resolution						*
 *																						*/

void draw_fx(Figure *fig, double f(double x), double start_x, double end_x)
{
	Point2D *iter;
	fig->point = createPoint2D(fig->point);
	iter = fig->point;

	while(start_x < end_x)
	{
		iter->x = start_x;
		iter->y = f(start_x);
		start_x += 1.0/fig->resolution;
		iter->next = createPoint2D(iter->next);
		iter = iter->next;
	}
	iter->x = end_x;
	iter->y = f(end_x);
	iter->next = NULL;
}

/*															*
 * In the following function								*
 * Each successive two (x,y) points are connected together	*
 *															*/

void draw_polyline(Figure *fig, Point2D *poly_line, int n)
{
	int i = 0;
	Point2D *iter;
	fig->point = createPoint2D(fig->point);
	iter = fig->point;
	while(i < n)
	{
		iter->x = poly_line[i].x;
		iter->y = poly_line[i].y;
		i++;
		if(i < n)
			iter->next = createPoint2D(iter->next) , iter=iter->next;
	}
	iter->next=NULL;
}
	
/*																		*
 * In the two following function										*
 * It will draw the function within the range defined by “ start_x”		*
 *																		*/

void draw_circle(Figure *fig, Point2D *center, double r)
{
	draw_ellipse(fig,center,r,r);
}

void draw_ellipse(Figure *fig, Point2D *center, double a_point, double b_point)
{
	double start_x = -a_point, end_x = a_point;
	Point2D *iter;

	fig->point = createPoint2D(fig->point);
	iter=fig->point;
	while(start_x < end_x)
	{
		iter->x = start_x + center->x;
		iter->y = sqrt((1-(pow(start_x,2)/pow(a_point,2)))*pow(b_point,2)) + center->y;
		start_x += 1.0/fig->resolution;
		iter->next = createPoint2D(iter->next);
		iter = iter->next;
	}
	start_x = a_point, end_x = -a_point;
	while(start_x > end_x)
	{
		iter->x = start_x + center->x;
		iter->y = -(sqrt((1-(pow(start_x,2)/pow(a_point,2)))*pow(b_point,2))) + center->y;
		start_x -= 1.0/fig->resolution;
		iter->next = createPoint2D(iter->next);
		iter = iter->next;
	}
	iter->x = end_x + center->x;
	iter->y = -(sqrt((1-(pow(end_x,2)/pow(a_point,2)))*pow(b_point,2))) + center->y;
	iter->next=NULL;
}

/*		
 * In the following function															*
 * The center points of the circles are calculated according to the depth of our tree	*
 * As a result of the calculations, circles are drawn at those points					*
 *																						*/

void draw_binary_tree(Figure *fig, Tree *root, Point2D *center)
{
	int depth = depthOfTree(root);
	tree_draw_helper(fig,root,center,depth,TRUE);
}

void tree_draw_helper(Figure *fig, Tree *root, Point2D *center, int depth, int situation)
{
	Figure *new_circle;
	if(root != NULL)
	{
		double tempx = center->x , tempy = center->y;
		if(situation == TRUE)
		{
			draw_circle(fig,center,3);
			write_text(fig,center,root->num);
		}
		else
		{
			new_circle=start_figure(fig->width,fig->height);
			set_thickness_resolution(new_circle,fig->thickness,fig->resolution);
			set_color(new_circle,fig->c);
			draw_circle(new_circle,center,3);
			write_text(new_circle,center,root->num);
			append_figures(fig,new_circle);
		}
		
		if(root->left != NULL && depth != 1)
		{
			draw_tree_line(fig,center,3,depth,0);
			center->x -= (1.5)*3*pow(2,(depth-2));
			center->y -= 2*4;
			tree_draw_helper(fig,root->left,center,depth-1,FALSE);
		}
		if(root->right != NULL && depth != 1)
		{
			center->x = tempx , center->y = tempy;
			draw_tree_line(fig,center,3,depth,1);
			center->x += (1.5)*3*pow(2,(depth-2));
			center->y -= 2*4;
			tree_draw_helper(fig,root->right,center,depth-1,FALSE);
		}
	}
}

void draw_tree_line(Figure *fig, Point2D *center, int r, int depth, int way)
{
	Figure *line;
	line = start_figure(fig->width,fig->height);
	set_thickness_resolution(line,fig->thickness,fig->resolution);
	set_color(line,fig->c);
	line->point = createPoint2D(line->point);
	line->point->next = createPoint2D(line->point->next);;

	if(way == 0) // For left line
	{
		line->point->x = center->x - r*cos(45) , line->point->y = center->y - r*sin(45);
		line->point->next->x = center->x - (1.5)*r*pow(2,(depth-2));
	}
	else	// For right line
	{
		line->point->x = center->x + r*cos(45) , line->point->y = center->y - r*sin(45);
		line->point->next->x = center->x + (1.5)*r*pow(2,(depth-2));
	}
	line->point->next->y = center->y - 2*(r+1) + r; // This point is same for both ways
	append_figures(fig,line);
}

int depthOfTree(Tree *node)
{
	if(node == NULL)
		return 0;
	else
	{
		int lDepth=0,rDepth=0;
		lDepth=depthOfTree(node->left);
		rDepth=depthOfTree(node->right);
		if(lDepth > rDepth)
			return lDepth+1;
		else
			return rDepth+1;
	}
}

void write_text(Figure *fig, Point2D *center, int num)
{
	int digitNum=0 , i=1;
	while(num / i != 0)
		digitNum ++ , i *=10;

	fig->text.flag = 1;
	fig->text.num = num;
	fig->text.x = center->x - 0.5*(digitNum);
	fig->text.y = center->y - 0.5;
}

/*																*
 * In the following function									*
 * Scales your figure in both dimensions by scale_x and scale_y	*
 *																*/

void scale_figure(Figure *fig, double scale_x, double scale_y)
{
	Figure *iter_fig = fig;
	Point2D *iter_point;

	while(iter_fig != NULL)
	{
		iter_point = iter_fig->point;
		while(iter_point != NULL)
		{
			iter_point->x *= scale_x;
			iter_point->y *= scale_y;
			iter_point = iter_point->next;
		}
		iter_fig = iter_fig->next_figure;
	}
}

/*																			*
 * In the followin function													*
 * Crops (may oversample) the given figure to be within a rectangle defined	*
 * by  start_roi  indicating  the bottom-left corner and end_roi indicating	*
 * the top-right corner of the rectangle. Anything out of this range in the	*
 * original figure should be erased											*
 *																			*/

void resize_figure(Figure *fig, Point2D start_roi, Point2D end_roi)
{
	fig->width = end_roi.x - start_roi.x;
	fig->height = end_roi.y - start_roi.y;
}

/*																						*
 * In the following function															*
 * Merges two figures and returns it in the first one. Figures linked with  			*
 * each others(Linked list structure). So every figure has  own  thickness and color	*
 *																						*/

void append_figures(Figure *fig1, Figure *fig2)
{
	Figure *iter = fig1;
	while(iter->next_figure != NULL)
		iter = iter->next_figure;
	iter->next_figure = fig2;
}

/*																			*
 * In the following function												*
 * Exportes figures to a file(file_name) in EPS format. Figures linked with *
 * each others(Linked list structure)										*
 *																			*/

void export_eps(Figure *fig, char *file_name)
{
	Figure *iter_fig = fig;
	Point2D *iter_point;
	FILE *fp;

	fp = fopen(file_name,"w");
	fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fp,"%%%%BoundingBox %lf %lf %lf %lf\n",-(fig->width)/2.0,-(fig->height)/2.0,(fig->width)/2.0,(fig->height)/2.0);

	while(iter_fig != NULL)
	{
		if(iter_fig->point != NULL)
		{
			iter_point = iter_fig->point;
			fprintf(fp,"%lf setlinewidth\n",iter_fig->thickness);
			fprintf(fp,"%lf %lf %lf setrgbcolor\n",iter_fig->c.R,iter_fig->c.G,iter_fig->c.B);
			if(iter_fig->text.flag != 0)
			{
				fprintf(fp,"/Times-Roman findfont 2 scalefont setfont\n");
				fprintf(fp,"%lf %lf moveto\n",iter_fig->text.x,iter_fig->text.y);
				fprintf(fp,"(%d) show\n",iter_fig->text.num);
			}
			if(iter_point != NULL)
			{
				fprintf(fp,"%lf %lf moveto\n",iter_point->x,iter_point->y);
				for(;iter_point != NULL ; iter_point = iter_point->next)
				{
					if(iter_point->jump == 0)
						fprintf(fp,"%lf %lf lineto\n",iter_point->x,iter_point->y);
					else
						fprintf(fp,"%lf %lf moveto\n",iter_point->x,iter_point->y);	
				}
			}
			fprintf(fp,"stroke\n");
		}
		iter_fig = iter_fig->next_figure;
	}
	fclose(fp);
	free_fig(fig);	// Figure free
}

/*																			*
 * In the following function												*
 * Exportes figures to a file(file_name) in SVG format. Figures linked with *
 * each others(Linked list structure)										*
 *																			*/

void export_svg(Figure *fig, char *file_name)
{
	Figure *iter_fig=fig;
	Point2D *iter_point;
	FILE *fp;
	fp = fopen(file_name,"w");
	fprintf(fp,"<svg viewBox=\"%lf %lf %lf %lf\">\n",-fig->height/2,-fig->width/2,fig->height,fig->width);
	while(iter_fig != NULL)
	{
		if(iter_fig->point != NULL)
		{
			iter_point = iter_fig->point;
			if(iter_fig->text.flag == 1)
				fprintf(fp,"<text x=\"%lf\" y=\"%lf\" font-size=\"3\">%d</text>\n",iter_fig->text.x,-iter_fig->text.y,iter_fig->text.num);
			fprintf(fp,"<path d=\"\n");
			fprintf(fp,"M %lf %lf\n",iter_point->x,-iter_point->y);
			while(iter_point != NULL)
			{
				if(iter_point->jump == 0)
					fprintf(fp,"L %lf %lf\n",iter_point->x,-iter_point->y);
				else
					fprintf(fp,"M %lf %lf\n",iter_point->x,-iter_point->y);
				iter_point = iter_point->next;
			}
			fprintf(fp,"\"\n");
			fprintf(fp,"stroke=\"rgb(%lf %lf %lf)\" stroke-width=\"%lf\" fill=\"none\"/>",iter_fig->c.R,iter_fig->c.G,iter_fig->c.B,iter_fig->thickness);
		}
		iter_fig = iter_fig->next_figure;
	}
	fprintf(fp,"</svg>\n");
	fclose(fp);
	free_fig(fig);	// Free figure
}

/*															*
 * In the following function								*
 * Importes figures from a file(file_name) in SVG format	*									*
 *															*/
/*
void import_svg(char *file_name, Figure *fig)
{
	FILE *fp;
	fp = fopen(file_name,"r");
	if(fp != NULL)
	{
		
	}
	fclose(fp);
}
*/

void draw_koch_snowflake(Figure *fig, Point2D *center, double size, int num_iterations)
{
	Point2D *e1,*e2,*e3,*e4;
	if(num_iterations > 0)
	{
		e1 = createPoint2D(e1);
		e2 = createPoint2D(e2);
		e3 = createPoint2D(e3);
		e4 = createPoint2D(e4);

		e1->x = center->x - size*sqrt(3)/4.0;	// bottom-left edge
		e1->y = center->y - size/2.0;
		e2->x = center->x - size*sqrt(3)/4.0;	// top-left edge
		e2->y = center->y + size/2.0;
		e3->x = center->x + size*sqrt(3)/4.0;	// right edge
		e3->y = center->y;
		e4->x = center->x - size*sqrt(3)/4.0;	// again bottom-left edge
		e4->y = center->y - size/2.0;

		fig->point = e1;
		e1->next = e2;
		e2->next = e3;
		e3->next = e4;
		e4->next = NULL;
		snowflake_func(fig,size/3.0,num_iterations-1);
	}
}

void snowflake_func(Figure *fig, double size, int num_iterations)
{
	Point2D *iter1,*iter2;
	double a,b;

	if(num_iterations != 0)
	{
		iter1 = fig->point;
		while(iter1->next != NULL)
		{
			iter2 = iter1->next;
			a = (iter2->x - iter1->x);
			b = (iter2->y - iter1->y);
			add_koch(&iter1,size,b/a,a);
			iter1 = iter2;
		}
		snowflake_func(fig,size/3.0,num_iterations-1);
	}
}

void add_koch(Point2D **point, double size, double slope, double x)
{
	double degree = atan(slope);
	double a1,a2; // First rotation angle and second rotation angle
	Point2D *p1,*p2,*p3,*temp = (*point)->next;

	p1 = createPoint2D(p1);
	p2 = createPoint2D(p2);
	p3 = createPoint2D(p3);
	(*point)->next = p1;
	p1->next = p2;
	p2->next = p3;
	p3->next = temp;

	if(x < 0)
	{
		a1 = 240*PI/180.0;
		a2 = 120*PI/180.0;
		p1->x = (*point)->x - size*cos(degree);
		p1->y = (*point)->y - size*sin(degree);
	}
	else
	{
		a1 = 60*PI/180.0;
		a2 = 300*PI/180.0;
		p1->x = (*point)->x + size*cos(degree);
		p1->y = (*point)->y + size*sin(degree);
	}
	p2->x = p1->x + size*cos(degree + a1);
	p2->y = p1->y + size*sin(degree + a1);
	p3->x = p2->x + size*cos(degree + a2);
	p3->y = p2->y + size*sin(degree + a2);
}

void draw_fractal_tree(Figure *fig, Point2D *center, double size, int num_iterations)
{
	double current_angle = 90 , l_add_angle = 30 , r_add_angle = 30;
	double x = center->x + size*cos(current_angle*PI/180.0);
	double y = center->y + size*sin(current_angle*PI/180.0);

	if(num_iterations > 0)
	{
		fig->point = createPoint2D(fig->point);
		fig->point->x = center->x;
		fig->point->y = center->y;
		fig->point->next = createPoint2D(fig->point->next);
		fig->point->next->x = x;
		fig->point->next->y = y;
		fractal_tree_helper(fig,x,y,size*0.75,num_iterations-1,current_angle+l_add_angle,l_add_angle,r_add_angle);
		fractal_tree_helper(fig,x,y,size*0.75,num_iterations-1,current_angle-r_add_angle,l_add_angle,r_add_angle);
	}
}

void draw_fractal_atree(Figure *fig, Point2D *center, double size, int num_iterations)
{
	double current_angle = 90 , l_add_angle = 15 , r_add_angle = 45;
	double x = center->x + size*cos(current_angle*PI/180.0);
	double y = center->y + size*sin(current_angle*PI/180.0);

	if(num_iterations > 0)
	{
		fig->point = createPoint2D(fig->point);
		fig->point->x = center->x;
		fig->point->y = center->y;
		fig->point->next = createPoint2D(fig->point->next);
		fig->point->next->x = x;
		fig->point->next->y = y;
		fractal_tree_helper(fig,x,y,size*0.75,num_iterations-1,current_angle+l_add_angle,l_add_angle,r_add_angle);
		fractal_tree_helper(fig,x,y,size*0.75,num_iterations-1,current_angle-r_add_angle,l_add_angle,r_add_angle);
	}
}

void fractal_tree_helper(Figure *fig, double center_x, double center_y, double size, int num_iterations, double current_angle, double l_add_angle, double r_add_angle)
{
	Figure *new;
	double x = center_x + size*cos(current_angle*PI/180.0);
	double y = center_y + size*sin(current_angle*PI/180.0);

	if(num_iterations > 0)
	{
		new = start_figure(fig->width,fig->height);
		set_thickness_resolution(new,fig->thickness*0.75,fig->resolution);
		set_color(new,fig->c);
		new->point = createPoint2D(new->point);
		new->point->x = center_x;
		new->point->y = center_y;
		new->point->next = createPoint2D(new->point->next);
		new->point->next->x = x;
		new->point->next->y = y;
		append_figures(fig,new);
		fractal_tree_helper(new,x,y,size*0.75,num_iterations-1,current_angle+l_add_angle,l_add_angle,r_add_angle);
		fractal_tree_helper(new,x,y,size*0.75,num_iterations-1,current_angle-r_add_angle,l_add_angle,r_add_angle);
	}
}

void draw_fractal_circle(Figure *fig, Point2D *center, double radius)
{
	Figure *new_fig;
	if(radius > 0.05)
	{
		new_fig = start_figure(fig->width,fig->height);
		set_thickness_resolution(new_fig,fig->thickness,fig->resolution);
		set_color(new_fig,fig->c);
		draw_circle(new_fig,center,radius);
		append_figures(fig,new_fig);
		draw_fractal_circle(fig,center,radius*0.85);
	}
}

void draw_fractal_twice_circle(Figure *fig, Point2D *center, double radius)
{
	Figure *new_fig;
	double x = center->x , y = center->y;
	if(radius > 0.1)
	{
		new_fig = start_figure(fig->width,fig->height);
		set_thickness_resolution(new_fig,fig->thickness,fig->resolution);
		set_color(new_fig,fig->c);
		draw_circle(new_fig,center,radius);
		append_figures(fig,new_fig);
		center->x = x-radius, center->y = y;
		draw_fractal_twice_circle(fig,center,radius*0.5);
		center->x = x+radius, center->y = y;
		draw_fractal_twice_circle(fig,center,radius*0.5);
		center->x = x, center->y = y+radius;
		draw_fractal_twice_circle(fig,center,radius*0.5);
		center->x = x, center->y = y-radius;
		draw_fractal_twice_circle(fig,center,radius*0.5);
	}
}

void draw_fractal_line(Figure *fig, Point2D *center, double size)
{
	Figure *new_fig;
	double x = center->x , y = center->y;
	if(size > 0.1)
	{
		double foo(double x){return 0;}
		new_fig = start_figure(fig->width,fig->height);
		set_thickness_resolution(new_fig,fig->thickness,fig->resolution);
		set_color(new_fig,fig->c);
		new_fig->point = createPoint2D(new_fig->point);
		new_fig->point->x = center->x-size/2.0;
		new_fig->point->y = center->y;
		new_fig->point->next = createPoint2D(new_fig->point->next);
		new_fig->point->next->x = center->x+size/2.0;
		new_fig->point->next->y = center->y;
		append_figures(fig,new_fig);
		center->x = x - size/3.0 , center->y = y-1.5;
		draw_fractal_line(fig,center,size*0.33);
		center->x = x + size/3.0 , center->y = y-1.5;
		draw_fractal_line(fig,center,size*0.33);
	}
}

void draw_sierpinksi_triangle(Figure *fig, Point2D *center, double size)
{
	Figure *new_fig;
	Point2D *iter;
	double x = center->x , y = center->y;
	if(size > 0.25)
	{
		new_fig = start_figure(fig->width,fig->height);
		set_thickness_resolution(new_fig,fig->thickness,fig->resolution);
		set_color(new_fig,fig->c);
		draw_triangle(new_fig,center,size);
		append_figures(fig,new_fig);
		center->x = x, center->y = y + size*3*sqrt(3)/16.0;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x - size*0.125, center->y = y + size*sqrt(3)/16;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x + size*0.125, center->y = y + size*sqrt(3)/16;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x + size*0.125, center->y = y + size*sqrt(3)/16;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x - size*0.25, center->y = y - size*sqrt(3)/16;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x + size*0.25, center->y = y - size*sqrt(3)/16;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x - size*0.375, center->y = y - size*3*sqrt(3)/16.0;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x - size*0.125, center->y = y - size*3*sqrt(3)/16.0;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x + size*0.125, center->y = y - size*3*sqrt(3)/16.0;
		draw_sierpinksi_triangle(fig,center,size*0.25);
		center->x = x + size*0.375, center->y = y - size*3*sqrt(3)/16.0;
		draw_sierpinksi_triangle(fig,center,size*0.25);
	}
}

void draw_triangle(Figure *fig, Point2D *center, double size)
{
	Point2D *iter;
	double current_angle = 0;
	int i;

	fig->point = createPoint2D(fig->point);
	iter = fig->point;
	iter->x = center->x - size*0.5 , iter->y = center->y - size*sqrt(3)/4.0;
	for(i=0;i<3;i++)
	{
		iter->next = createPoint2D(iter->next);
		iter->next->x = iter->x + size*cos(current_angle*PI/180.0);
		iter->next->y = iter->y + size*sin(current_angle*PI/180.0);
		current_angle += 120;
		iter = iter->next;
	}
}

/*								*
 * In the following function	*
 * Free all memory allocations	*
 *								*/

void free_fig(Figure *fig)
{
	Figure *iter_fig = fig;
	Point2D *iter,*temp;

	while(iter_fig != NULL)
	{
		iter_fig = fig->next_figure;
		iter = fig->point;
		free(fig);
		while(iter != NULL)
		{
			temp = iter;
			iter = iter->next;
			free(temp);
		}
		fig = iter_fig;
	}
}

/*										*
 * In the following function			*
 * Creates a new point and its variable	*
 *										*/

Point2D *createPoint2D(Point2D *p)
{
	p = (Point2D*)malloc(sizeof(Point2D));
	p->jump = 0;
	p->next = NULL;
	return p;
}