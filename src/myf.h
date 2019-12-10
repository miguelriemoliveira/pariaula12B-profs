/**
 *       @file  myf.h
 *      @brief  Header file for the entire project
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * ===========================================================
 */
#ifndef _MYF_H_
#define _MYF_H_


#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <gtk/gtk.h>
#include <cairo.h>


#define max(a,b) ((a)>(b)?(a):(b))


/** \brief Data type to store a polygon */
typedef struct { double *x;                   //!<array with polygon x vertices
                 double *y;                   //!<array with polygon y vertices
		 double x0, y0;               //!<polygon center (when applicable)
                 int num_points;              //!<number of polygon vertices
		 int fill_color;              //!<fill color of polygon
                 int line_color;              //!<line color of polygon (not used)
               } p_polygon;

/** \brief Data type to sore a circular crown */
typedef struct { double x0, y0;               //!<crown center
		 double radius;               //!<crown external radius
                 double thickness;            //!<thickness of crown
		 int fill_color;              //!<fill color of crown
                 int line_color;              //!<line color of crown (not used)
               } p_crown;

/** \brief Data type to sore a string based graphic */
typedef struct { char *str;                   //!<The actual string
                 int   num_chars;             //!<String length
                 double   xpos, ypos;         //!<String position
                 int   text_color;            //!<Text color
                 } p_string;

/** \brief Data type to store an entire drawing */
typedef struct  { p_polygon **polys;        //!<Array of p_polygon's pointers
                  int        num_poly;      //!<Num of p_polygon's
                  p_string  **strings;      //!<List of p_string's  (char pointers)
                  int        num_strings;   //!<Num of p_string's
		  p_crown   **crowns;       //!<List of p_crown's pointers
		  int        num_crowns;    //!<Num of p_crown's
                } pari_drawing;

/** \brief Enumeration of the possible graphics objects */
typedef enum { STARPOLYGON, REGULARPOLYGON, FREEHANDPOLYGON, CIRCULARCROWN, TEXT} drawings_type;

/** \brief Data type to store program defaults */
typedef struct {
		drawings_type active_g; 
		int starpolygon_vertices;
		int regularpolygon_vertices;
		int starpolygon_rgbcolor;
		int regularpolygon_rgbcolor;
		int freehandpolygon_rgbcolor;
		int circularcrown_rgbcolor;
		int circularcrown_thickness;
		int text_rgbcolor;
		char *text_string;             //!<pointer to the active string in the text entry
              } drawings_default_status;
	

#if defined (_MAIN_C_)
	GtkBuilder *builderG;                  //!<The global variable with GUI structure
	pari_drawing *pdG;                     //!<The global variable with pari_drawing structure
	drawings_default_status statusG;       //!<The global variable with defaults for a common status
#else
	extern GtkBuilder *builderG;
	extern pari_drawing *pdG;
	extern drawings_default_status statusG;
#endif


/* prototypes */
#include "prototypes.h"

#endif /* _MYF_H_ */

