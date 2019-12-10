/** *     @file   myf.c
 *     @brief  Auxiliary functions that are not callbacks or handlers
 *
 *     Detailed description starts here.
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =========================================================
 */

#define _MYF_C_

#include "myf.h"


/**
 * @brief  Initialize global variables and defaults
 *
 * @return void
 */
void pari_init_vars()
{
	static int first_time=1;
	if( first_time )
	{
		first_time=0;
		pdG=(pari_drawing *)malloc(sizeof(pari_drawing));  //create the main pari_drawing variable

		pdG->polys=NULL;
		pdG->num_poly=0;
		pdG->crowns=NULL;
		pdG->num_crowns=0;
		pdG->strings=NULL;
		pdG->num_strings=0;

		statusG.active_g=STARPOLYGON;   //the default in the GUI
		statusG.starpolygon_vertices=6;
		statusG.regularpolygon_vertices=5;
		statusG.regularpolygon_rgbcolor=-1;
		statusG.starpolygon_rgbcolor=-1;
		statusG.freehandpolygon_rgbcolor=-1;
		statusG.circularcrown_rgbcolor=90;
		statusG.circularcrown_thickness=10;
		statusG.text_rgbcolor=900;
		statusG.text_string=NULL;
	}
}

//------ Auxiliary functions to update the pari_drawing structure -------------


/**
 * @brief Add a new polygon to a pari_drawing structure
 * 
 * @param pp the new polygon to add
 * @param pd the pari_drawing to update
 */
void pari_add_poly_to_main_drawing( p_polygon *pp, pari_drawing *pd)
{
	if( ! pp || ! pd) return;
	pd->polys=realloc(pd->polys, (pd->num_poly+1)*(sizeof(p_polygon**)) ); //space for one more element
	pd->polys[pd->num_poly]=pp;                                           //set that element
	pd->num_poly++;                                                       //update counter
}

/**
 * @brief add a circular crown to a pari_drawing
 * 
 * @param pc the new crown to add
 * @param pd the pari_drawing to update
 */
void pari_add_crown_to_main_drawing( p_crown *pc, pari_drawing *pd)
{
	if( ! pc || ! pd) return;
	pd->crowns=realloc(pd->crowns, (pd->num_crowns+1)*(sizeof(p_crown**)) ); //space for one more element
	pd->crowns[pd->num_crowns]=pc;                                           //set that element
	pd->num_crowns++;                                                       //update counter
}


/**
 * @brief add a string to a pari_drawing
 * 
 * @param ps The new string to add
 * @param pd the pari_drawing to update
 */
void pari_add_string_to_main_drawing( p_string *ps, pari_drawing *pd)
{
	if( ! ps || ! pd) return;
	pd->strings=realloc(pd->strings, (pd->num_strings+1)*(sizeof(p_string**)) ); //space for one more element
	pd->strings[pd->num_strings]=ps;                                           //set that element
	pd->num_strings++;                                                       //update counter
}


//------------ Other auxiliary functions -------------------------------------------

/**
 * @brief Auxiliary function to set color based on a 0-999 number for RGB
 * 
 * @param cr - the cairo context to modify
 * @param rgb_color The color to set: hundreds-red (0-9), tenths-green (0-9), units-blue (0-9)
 */
void pari_set_rgb_color(cairo_t *cr, int rgb_color)
{
	if( rgb_color < 0 ) return;

	double r=rgb_color/100;
	double g=(rgb_color-(int)r*100)/10;
	double b=(rgb_color-(int)r*100-(int)g*10);

	r=r/9;
	g=g/9;
	b=b/9;

	cairo_set_source_rgb(cr, r, g, b);  //rgb from 0 to 1
}

