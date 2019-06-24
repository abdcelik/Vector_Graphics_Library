#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"

// Creating tree for testing
Tree *newNode(int num);
Tree *insert(Tree *node, int num);
void free_root(Tree *node);

int main()
{
	int i;
	Figure *fig_fx, *fig_polyline, *fig_circle, *fig_ellipse;
	Figure *fig_binarytree, *fig_snowflake, *fig_tree, *fig_atree, *fig_frac_circle, *fig_frac_tcircle, *fig_frac_line, *fig_frac_triangle;
	Point2D center , arr_polyline[10] , start_roi , end_roi;
	Tree *root = NULL;
	Color c;

	// EPS Examples

	c.R = 255 , c.G = 0 , c.B = 0;
	fig_fx=start_figure(50,50);		// Testing draw_fx
	set_thickness_resolution(fig_fx,0.01,10);
	set_color(fig_fx,c);
	draw_fx(fig_fx,sin,-10,10);
	export_eps(fig_fx,"01-fx.eps");

	
	for(i=0 ; i<10 ; i++)
	{
		arr_polyline[i].x=i;
		arr_polyline[i].y=i*i;
	}
	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_polyline=start_figure(50,50);	// Testing draw_polyline
	set_thickness_resolution(fig_polyline,0.01,10);
	set_color(fig_polyline,c);
	draw_polyline(fig_polyline,arr_polyline,10);
	export_eps(fig_polyline,"02-polyline.eps");


	c.R = 0 , c.G = 255 , c.B = 0;
	center.x = -10 , center.y = 5;
	fig_circle=start_figure(50,50);		// Testing draw_circle
	set_thickness_resolution(fig_circle,0.01,10);
	set_color(fig_circle,c);
	draw_circle(fig_circle,&center,5);
	export_eps(fig_circle,"03-circle.eps");
	

	c.R = 0 , c.G = 0 , c.B = 255;
	center.x = 10 , center.y = 10;
	fig_ellipse = start_figure(50,50);	// Testing draw_ellipse
	set_thickness_resolution(fig_ellipse,0.01,10);
	set_color(fig_ellipse,c);
	draw_ellipse(fig_ellipse,&center,5,10);
	export_eps(fig_ellipse,"04-ellipse.eps");


	root = insert(root,50);
	root = insert(root,30);
	root = insert(root,20);
	root = insert(root,40);
	root = insert(root,70);
	root = insert(root,60);
	root = insert(root,80);
	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 20;
	fig_binarytree = start_figure(25,25);	// Testing draw_binary_tree and resize_figure
	set_thickness_resolution(fig_binarytree,0.1,10);
	set_color(fig_binarytree,c);
	draw_binary_tree(fig_binarytree,root,&center);
	export_eps(fig_binarytree,"05-binarytree_before_resize.eps");
	

	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 20;
	fig_binarytree = start_figure(25,25);	// Testing draw_binary_tree and resize_figure
	set_thickness_resolution(fig_binarytree,0.1,10);
	set_color(fig_binarytree,c);
	draw_binary_tree(fig_binarytree,root,&center);
	start_roi.x = -50 , start_roi.y = -50;
	end_roi.x = 50 , end_roi.y = 50;
	resize_figure(fig_binarytree,start_roi,end_roi);
	export_eps(fig_binarytree,"05-binarytree_after_resize.eps");
	free_root(root);


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_snowflake = start_figure(500,500);	// Testing draw_koch_snowflake and scale_figure
	set_thickness_resolution(fig_snowflake,0.01,10);
	set_color(fig_snowflake,c);
	draw_koch_snowflake(fig_snowflake,&center,50,5);
	export_eps(fig_snowflake,"06-snowflake_before_scale.eps");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_snowflake = start_figure(500,500);	// Testing draw_koch_snowflake and scale_figure
	set_thickness_resolution(fig_snowflake,0.01,10);
	set_color(fig_snowflake,c);
	draw_koch_snowflake(fig_snowflake,&center,50,5);
	scale_figure(fig_snowflake,4,4);
	export_eps(fig_snowflake,"06-snowflake_after_scale.eps");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_tree = start_figure(100,100);		// Testing draw_fractal_tree
	set_thickness_resolution(fig_tree,1,10);
	set_color(fig_tree,c);
	draw_fractal_tree(fig_tree,&center,10,11);
	export_eps(fig_tree,"07-fractal_tree.eps");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_atree = start_figure(100,100);		// Testing draw_fractal_atree
	set_thickness_resolution(fig_atree,0.5,10);
	set_color(fig_atree,c);
	draw_fractal_atree(fig_atree,&center,10,11);
	export_eps(fig_atree,"08-fractal_atree.eps");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_circle = start_figure(100,100);
	set_thickness_resolution(fig_frac_circle,0.01,10);
	set_color(fig_frac_circle,c);
	draw_fractal_circle(fig_frac_circle,&center,30);
	export_eps(fig_frac_circle,"09-fractal_circle.eps");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_tcircle = start_figure(100,100);
	set_thickness_resolution(fig_frac_tcircle,0.01,10);
	set_color(fig_frac_tcircle,c);
	draw_fractal_twice_circle(fig_frac_tcircle,&center,10);
	export_eps(fig_frac_tcircle,"10-fractal_twice_circle.eps");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_line = start_figure(100,100);
	set_thickness_resolution(fig_frac_line,0.01,10);
	set_color(fig_frac_line,c);
	draw_fractal_line(fig_frac_line,&center,80);
	export_eps(fig_frac_line,"11-fractal_line.eps");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_triangle = start_figure(100,100);
	set_thickness_resolution(fig_frac_triangle,0.01,10);
	set_color(fig_frac_triangle,c);
	draw_sierpinksi_triangle(fig_frac_triangle,&center,30);
	export_eps(fig_frac_triangle,"12-fractal_sierpinksi_triangle.eps");


	c.R = 255 , c.G = 0 , c.B = 0;
	fig_fx=start_figure(50,50);				// Testing append_figures
	set_thickness_resolution(fig_fx,0.01,10);
	set_color(fig_fx,c);
	draw_fx(fig_fx,sin,-10,10);

	c.R = 0 , c.G = 255 , c.B = 0;
	center.x = -15 , center.y = -15;
	fig_circle=start_figure(50,50);			// Testing append_figures
	set_thickness_resolution(fig_circle,0.01,10);
	set_color(fig_circle,c);
	draw_circle(fig_circle,&center,5);
	
	c.R = 0 , c.G = 0 , c.B = 255;
	center.x = 15 , center.y = 15;
	fig_ellipse = start_figure(50,50);		// Testing append_figures
	set_thickness_resolution(fig_ellipse,0.01,10);
	set_color(fig_ellipse,c);
	draw_ellipse(fig_ellipse,&center,4,8);

	append_figures(fig_fx,fig_circle);
	append_figures(fig_fx,fig_ellipse);
	export_eps(fig_fx,"13-mix.eps");


	// SVG Examples
	
	c.R = 255 , c.G = 0 , c.B = 0;
	fig_fx=start_figure(50,50);		// Testing draw_fx
	set_thickness_resolution(fig_fx,0.5,10);
	set_color(fig_fx,c);
	draw_fx(fig_fx,sin,-10,10);
	export_svg(fig_fx,"01-fx.svg");

	
	for(i=0 ; i<10 ; i++)
	{
		arr_polyline[i].x=i;
		arr_polyline[i].y=i*i;
	}
	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_polyline=start_figure(50,50);	// Testing draw_polyline
	set_thickness_resolution(fig_polyline,0.5,10);
	set_color(fig_polyline,c);
	draw_polyline(fig_polyline,arr_polyline,10);
	export_svg(fig_polyline,"02-polyline.svg");


	c.R = 0 , c.G = 255 , c.B = 0;
	center.x = -10 , center.y = 5;
	fig_circle=start_figure(50,50);		// Testing draw_circle
	set_thickness_resolution(fig_circle,0.5,10);
	set_color(fig_circle,c);
	draw_circle(fig_circle,&center,5);
	export_svg(fig_circle,"03-circle.svg");
	

	c.R = 0 , c.G = 0 , c.B = 255;
	center.x = 10 , center.y = 10;
	fig_ellipse = start_figure(50,50);	// Testing draw_ellipse
	set_thickness_resolution(fig_ellipse,0.5,10);
	set_color(fig_ellipse,c);
	draw_ellipse(fig_ellipse,&center,5,10);
	export_svg(fig_ellipse,"04-ellipse.svg");

	root = NULL;
	root = insert(root,50);
	root = insert(root,30);
	root = insert(root,20);
	root = insert(root,40);
	root = insert(root,70);
	root = insert(root,60);
	root = insert(root,80);
	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 20;
	fig_binarytree = start_figure(25,25);	// Testing draw_binary_tree and resize_figure
	set_thickness_resolution(fig_binarytree,0.5,10);
	set_color(fig_binarytree,c);
	draw_binary_tree(fig_binarytree,root,&center);
	export_svg(fig_binarytree,"05-binarytree_before_resize.svg");
	

	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 20;
	fig_binarytree = start_figure(25,25);	// Testing draw_binary_tree and resize_figure
	set_thickness_resolution(fig_binarytree,0.5,10);
	set_color(fig_binarytree,c);
	draw_binary_tree(fig_binarytree,root,&center);
	start_roi.x = -50 , start_roi.y = -50;
	end_roi.x = 50 , end_roi.y = 50;
	resize_figure(fig_binarytree,start_roi,end_roi);
	export_svg(fig_binarytree,"05-binarytree_after_resize.svg");
	free_root(root);


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_snowflake = start_figure(500,500);	// Testing draw_koch_snowflake and scale_figure
	set_thickness_resolution(fig_snowflake,0.5,10);
	set_color(fig_snowflake,c);
	draw_koch_snowflake(fig_snowflake,&center,50,5);
	export_svg(fig_snowflake,"06-snowflake_before_scale.svg");

	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_snowflake = start_figure(500,500);	// Testing draw_koch_snowflake and scale_figure
	set_thickness_resolution(fig_snowflake,0.5,10);
	set_color(fig_snowflake,c);
	draw_koch_snowflake(fig_snowflake,&center,50,5);
	scale_figure(fig_snowflake,4,4);
	export_svg(fig_snowflake,"06-snowflake_after_scale.svg");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_tree = start_figure(100,100);		// Testing draw_fractal_tree
	set_thickness_resolution(fig_tree,1,10);
	set_color(fig_tree,c);
	draw_fractal_tree(fig_tree,&center,10,11);
	export_svg(fig_tree,"07-fractal_tree.svg");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_atree = start_figure(100,100);		// Testing draw_fractal_atree
	set_thickness_resolution(fig_atree,0.5,10);
	set_color(fig_atree,c);
	draw_fractal_atree(fig_atree,&center,10,11);
	export_svg(fig_atree,"08-fractal_atree.svg");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_circle = start_figure(100,100);
	set_thickness_resolution(fig_frac_circle,1,10);
	set_color(fig_frac_circle,c);
	draw_fractal_circle(fig_frac_circle,&center,30);
	export_svg(fig_frac_circle,"09-fractal_circle.svg");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_tcircle = start_figure(100,100);
	set_thickness_resolution(fig_frac_tcircle,0.08,10);
	set_color(fig_frac_tcircle,c);
	draw_fractal_twice_circle(fig_frac_tcircle,&center,10);
	export_svg(fig_frac_tcircle,"10-fractal_twice_circle.svg");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_line = start_figure(100,100);
	set_thickness_resolution(fig_frac_line,1,10);
	set_color(fig_frac_line,c);
	draw_fractal_line(fig_frac_line,&center,80);
	export_svg(fig_frac_line,"11-fractal_line.svg");


	c.R = 0 , c.G = 0 , c.B = 0;
	center.x = 0 , center.y = 0;
	fig_frac_triangle = start_figure(100,100);
	set_thickness_resolution(fig_frac_triangle,0.07,10);
	set_color(fig_frac_triangle,c);
	draw_sierpinksi_triangle(fig_frac_triangle,&center,30);
	export_svg(fig_frac_triangle,"12-fractal_sierpinksi_triangle.svg");


	c.R = 255 , c.G = 0 , c.B = 0;
	fig_fx=start_figure(50,50);				// Testing append_figures
	set_thickness_resolution(fig_fx,1,10);
	set_color(fig_fx,c);
	draw_fx(fig_fx,sin,-10,10);

	c.R = 0 , c.G = 255 , c.B = 0;
	center.x = -15 , center.y = -15;
	fig_circle=start_figure(50,50);			// Testing append_figures
	set_thickness_resolution(fig_circle,1,10);
	set_color(fig_circle,c);
	draw_circle(fig_circle,&center,5);
	
	c.R = 0 , c.G = 0 , c.B = 255;
	center.x = 15 , center.y = 15;
	fig_ellipse = start_figure(50,50);		// Testing append_figures
	set_thickness_resolution(fig_ellipse,1,10);
	set_color(fig_ellipse,c);
	draw_ellipse(fig_ellipse,&center,4,8);

	append_figures(fig_fx,fig_circle);
	append_figures(fig_fx,fig_ellipse);
	export_svg(fig_fx,"13-mix.svg");
	return 0;
}

Tree *newNode(int num)
{
	Tree *temp = (Tree*)malloc(sizeof(Tree));
	temp->num = num;
	temp->left = temp->right = NULL;
	return temp;
}

Tree *insert(Tree *node, int num)
{
	if(node == NULL)
		return newNode(num);
	if(num < node->num)
		node->left = insert(node->left, num);
	else if(num > node->num)
		node->right = insert(node->right, num);
	return node;
}

void free_root(Tree *node)
{
	if(node != NULL)
	{
		free_root(node->left);
		free_root(node->right);
		free(node);
	}
}