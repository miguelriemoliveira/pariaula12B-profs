/**
 *      @file  callbacks.c
 *      @brief  Callbacks for buttons and widgets and other handlers
 *
 *     Functions that act as response to asynchronous events such as widget callbacks,
 *     signal handlers, timeout handlers
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =========================================================
 */

#define _CALLBACKS_C_

#include "myf.h"


//--- Main callbacks to process mouse events in the drawing area ---//

/**
 * @brief  What to do when there is mouse press activity in main Drawing Area
 *
 * @param  widget the causing widget
 * @param  event the associated event (argument specific for callbacks for mouse events)
 * @param  user_data the usual user data
 * @return TRUE to pass events into the hierarchy (if any)
 */
gboolean on_drawingarea1_button_press_event(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
	switch( statusG.active_g )
	{
		case STARPOLYGON:
			pari_draw_starpolygon(event);
			break;

		case REGULARPOLYGON:
			pari_draw_regularpolygon(event);
			break;

		case FREEHANDPOLYGON:
			pari_draw_freehandpolygon(event);
			break;

		case CIRCULARCROWN:
			pari_draw_circularcrown(event);
			break;

		case TEXT:
			pari_draw_text(event);
			break;

		default:
			break;
	}

	gtk_widget_queue_draw(widget);  //generate draw event
	return TRUE;
}

/**
 * @brief  What to do when there is (pressed) mouse motion activity in main Drawing Area
 *
 * @param  widget the causing widget
 * @param  event the associated event 
 * @param  user_data the usual user data
 * @return TRUE to pass events into the hierarchy (if any)
 */
gboolean on_drawingarea1_motion_notify_event(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
	switch( statusG.active_g )
	{
		case STARPOLYGON:
			//...
			break;

		case REGULARPOLYGON:
			pari_draw_regularpolygon(event);
			break;

		case FREEHANDPOLYGON:
			//...
			break;

		case CIRCULARCROWN:
			pari_draw_circularcrown(event);
			//...
			break;

		case TEXT:
			//...
			break;

		default:
			break;
	}

	gtk_widget_queue_draw(widget);  //generate draw event
	return TRUE;
}

//// Set of callbacks associated to radio buttons clicking
//// Actually, before the newly clicked button callback executes, also the
//// the previously clicked button callback is invoked. No harm in this context...!

/**
 * @brief callback when clicking starpolygon radiobutton
 * 
 * @param widget the causing widget
 * @param user_data the usual user data
 */
void on_starpolygon_rb_clicked(GtkWidget * widget, gpointer user_data)
{
	//puts("STAR");
	GtkEntry *entry = GTK_ENTRY(user_data);
	const char* txt=gtk_entry_get_text(entry);
	char *tmp=malloc(strlen(txt)+1);
	strcpy(tmp,txt);
	int n=atoi(tmp);
	if (n <3 || n > 99) //only values between 3 and 99 accepted
	{
		n=6;
		sprintf(tmp,"%d",n);
		gtk_entry_set_text( entry, tmp);
	}
	free(tmp);
	statusG.starpolygon_vertices=n;
	statusG.active_g=STARPOLYGON;
}


/**
 * @brief callback when clicking starpolygon radiobutton
 * 
 * @param widget the one that originated the call
 * @param user_data the usual user data (the entry for additional parameters)
 */
void on_regularpolygon_rb_clicked(GtkWidget * widget, gpointer user_data)
{
	//puts("REGULAR");
	GtkEntry *entry = GTK_ENTRY(user_data);
	const char* txt=gtk_entry_get_text(entry);
	char *tmp=malloc(strlen(txt)+1);
	strcpy(tmp,txt);
	int n=atoi(tmp);
	if (n <3 || n > 99) //only values between 3 and 99 accepted
	{
		n=5;
		sprintf(tmp,"%d",n);
		gtk_entry_set_text( entry, tmp);
	}
	statusG.regularpolygon_vertices=n;
	statusG.active_g=REGULARPOLYGON;
	free(tmp);

	GtkEntry *entry2 = GTK_ENTRY(gtk_builder_get_object (builderG, "regularpolygonfill_rgbcolor"));
	if( entry2)
	{
		txt=gtk_entry_get_text(entry2);
		char *tmp=malloc(strlen(txt)+1);
		strcpy(tmp,txt);
		int n=atoi(tmp);
		if ( n < 0 ) //only -1 is accepted for negatives (no filling)
		{
			n=-1;
			sprintf(tmp,"%d",n);
			gtk_entry_set_text( entry2, tmp);
		}

		statusG.regularpolygon_rgbcolor=n;

		free(tmp);
	}
}


/**
 * @brief callback when clicking free hand radiobutton
 * 
 * @param widget the usual user data
 * @param user_data the usual user data
 */
void on_freehandpolygon_rb_clicked(GtkWidget * widget, gpointer user_data)
{
	//puts("FREEHAND");
	statusG.active_g=FREEHANDPOLYGON;
}

/**
 * @brief callback when clicking the circular crown radiobutton
 * 
 * @param widget the radio button causing the event
 * @param user_data Circular crown thickness
 */
void on_circularcrown_rb_clicked(GtkWidget * widget, gpointer user_data)
{
	//puts("CIRCULARCROWN");
	statusG.active_g=CIRCULARCROWN;
	GtkEntry *entry = GTK_ENTRY(user_data);  //crown_thickness
	const char* txt=gtk_entry_get_text(entry);
	char *tmp=malloc(strlen(txt)+1);
	strcpy(tmp,txt);
	int n=atoi(tmp);
	if (n <0 || n > 99) //only values between 0 and 99 accepted
	{
		n=10;
		sprintf(tmp,"%d",n);
		gtk_entry_set_text( entry, tmp);
	}
	free(tmp);

	statusG.circularcrown_thickness=n;
	statusG.active_g=CIRCULARCROWN;

	GtkEntry *entry2 = GTK_ENTRY(gtk_builder_get_object (builderG, "circularcrownfill_rgbcolor"));
	if( entry2)
	{
		txt=gtk_entry_get_text(entry2);
		char *tmp=malloc(strlen(txt)+1);
		strcpy(tmp,txt);
		int n=atoi(tmp);
		if ( n < 0 ) //only -1 is accepted for negatives (no filling)
		{
			n=-1;
			sprintf(tmp,"%d",n);
			gtk_entry_set_text( entry2, tmp);
		}
		statusG.circularcrown_rgbcolor=n;
		free(tmp);
	}
}


/**
 * @brief callback when clicking text radiobutton
 * 
 * @param widget 
 * @param user_data the usual user data
 */
void on_text_rb_clicked(GtkWidget * widget, gpointer user_data)
{
	//puts("TEXT");
	GtkEntry *entry = GTK_ENTRY(user_data);
	const char* txt=gtk_entry_get_text(entry);
	char *tmp=malloc(strlen(txt)+1);
	strcpy(tmp,txt);
	int n=atoi(tmp);
	if (n <0 || n > 999) //only values between 0 and 999 accepted
	{
		n=900;  //R=9, G=0, B=0  (pure red)
		sprintf(tmp,"%d",n);
		gtk_entry_set_text( entry, tmp);
	}
	free(tmp);
	statusG.text_rgbcolor=n;
	statusG.active_g=TEXT;
	statusG.text_string=(char *)txt;
}


/**
 * @brief  Callback to redraw/refresh all graphics from a pari_drawing: polygons, circular crowns, texts
 *
 * @param  widget the causing widget
 * @param  cr the associated cairo context  (argument specific for callbacks for draw events)
 * @param  user_data the usual user data
 * @return TRUE to pass events into the hierarchy (if any)
 */
gboolean on_drawingarea1_draw(GtkWidget * widget, cairo_t *cr, gpointer user_data)
{
	//First the polygons (all types can be done the same way)
	for(int n=0; n< pdG->num_poly; n++)
	{
		cairo_set_source_rgb(cr, 0, 0, 0);      //define color (rgb)
        	cairo_set_line_width(cr, 1);    //line width
        	cairo_move_to(cr, pdG->polys[n]->x[0], pdG->polys[n]->y[0]);       //start  path
        	for(int i = 1; i < pdG->polys[n]->num_points; i++)  //run over all accumulated points
        	{
                	cairo_line_to(cr, pdG->polys[n]->x[i], pdG->polys[n]->y[i]);  //update the path segment by segment
        	}
		cairo_close_path(cr);  //close path

		if(pdG->polys[n]->fill_color >= 0)
		{
        		cairo_stroke_preserve(cr);              //stroke the path in the surface (drawing area in this case)
			pari_set_rgb_color(cr, pdG->polys[n]->fill_color);
			cairo_fill(cr);                         //fill the path
		}
		else
        		cairo_stroke(cr);              //stroke the path in the surface (drawing area in this case)
	}

	//Then the circular crowns
	for(int n=0; n< pdG->num_crowns; n++)
	{
		cairo_set_source_rgb(cr, 0, 0, 0);      //define color (rgb)
        	cairo_set_line_width(cr, 1);            //line width
		if(pdG->crowns[n]->fill_color >= 0)
		{
			cairo_arc (cr,  pdG->crowns[n]->x0, pdG->crowns[n]->y0, pdG->crowns[n]->radius, 0, 2*M_PI);
			cairo_arc_negative (cr,  pdG->crowns[n]->x0, pdG->crowns[n]->y0, max(0,pdG->crowns[n]->radius-pdG->crowns[n]->thickness), 2*M_PI,0);
        		cairo_stroke_preserve(cr);              //stroke the path in the surface (drawing area in this case)
			pari_set_rgb_color(cr, pdG->crowns[n]->fill_color);
			cairo_fill(cr);                         //fill the path
		}
		else  //separate to avoid connection of the circles :-(
		{
			cairo_arc (cr,  pdG->crowns[n]->x0, pdG->crowns[n]->y0, pdG->crowns[n]->radius, 0, 2*M_PI);
        		cairo_stroke(cr);              //stroke the path in the surface (drawing area in this case)
			cairo_arc_negative (cr,  pdG->crowns[n]->x0, pdG->crowns[n]->y0, max(0,pdG->crowns[n]->radius-pdG->crowns[n]->thickness), 2*M_PI,0);
        		cairo_stroke(cr);              //stroke the path in the surface (drawing area in this case)
		}
	}

	//Finally the strings
	for(int n=0; n< pdG->num_strings; n++)
	{
		//...
	}


	return TRUE;
}



//----------------------------------------------------------------------


/**
 * @brief  Callback to process the quit button
 *
 * @param  widget the associated widget
 * @param  user_data optional pojnter with user data (not used here)
 * @return void
 */
void on_button1_clicked(GtkWidget * widget, gpointer user_data)
{
	g_print("Sair normalmente\n");
	gtk_main_quit();
}

/**
 * @brief  Handler function when main window is destroyed. Nothing else to be done in the GUI!
 * 
 * Stop the GTK+ main loop function when the window is destroyed.
 *
 * @param  Widget and user data
 * @param  user_data optional pojnter with user data (not used here)
 */
void pari_destroy(GtkWidget * window, gpointer data)
{
	puts("I am leaving!");
	gtk_main_quit();
}


/**
 * @brief  Handler function for the forced closing of the main window. That can be avoided.
 *
 * @param  Widget and user data
 * @param  event the associated event (not used here)
 * @param  user_data optional pojnter with user data (not used here)
 * @return Return FALSE to destroy the widget. Return TRUE to ignore.
 */
gboolean pari_delete_event(GtkWidget * window, GdkEvent * event, gpointer data)
{
	g_print("Perhaps you should avoid using the OS window manager to force leave!\n");
	return TRUE;  //TRUE does not "pursue" the delete order
}


/**
 * @brief  Classic handler to intersect CTRL+C signal
 *
 * @param  a Number of signal (from <signal.h>) that generated the interruption (CTRL+C expected)
 */
void pari_InterceptCTRL_C( int a )
{
	g_print("Leaving with CTRL+C\n");
	gtk_main_quit();
}

