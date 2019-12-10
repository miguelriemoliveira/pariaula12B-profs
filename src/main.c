/**
 *     @file  main.c
 *     @brief Example main file to create a GUI using GTK and Glade
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * ============================================================
 */

#define _MAIN_C_

#include "myf.h"

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	/* load the interface */
	builderG = gtk_builder_new();
	gtk_builder_add_from_file(builderG, "paridraw.glade", NULL);

	/* connect the signals in the interface */
	gtk_builder_connect_signals(builderG, NULL);

	/* get main window ID and connect special handler/signals */
	GtkWidget *t = GTK_WIDGET(gtk_builder_get_object(builderG, "window1"));
	if(t)
	{
		g_signal_connect(G_OBJECT(t), "destroy",      G_CALLBACK(pari_destroy), NULL);
		g_signal_connect(G_OBJECT(t), "delete_event", G_CALLBACK(pari_delete_event), NULL);
	}

	//gtk_widget_show_all (t);   //sometimes needed to ensure initial display of windows...

	/*This could be in a special init function... */
	signal(SIGINT, pari_InterceptCTRL_C);

	pari_init_vars(); //crate initial variables
	
	gtk_main();

	return 0;
}

