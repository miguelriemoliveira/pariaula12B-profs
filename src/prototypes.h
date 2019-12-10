/*File generated automatically. Do not edit*/
/*Generated on diplodocossd1 , sáb dez 7 13:07:01 WET 2019 */
#ifdef __cplusplus
extern "C" {
#endif
/* src/main.c */
int main(int argc, char *argv[]);
/* src/myf.c */
void pari_init_vars(void);
void pari_add_poly_to_main_drawing(p_polygon *pp, pari_drawing *pd);
void pari_add_crown_to_main_drawing(p_crown *pc, pari_drawing *pd);
void pari_add_string_to_main_drawing(p_string *ps, pari_drawing *pd);
void pari_set_rgb_color(cairo_t *cr, int rgb_color);
/* src/callbacks.c */
gboolean on_drawingarea1_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
gboolean on_drawingarea1_motion_notify_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void on_starpolygon_rb_clicked(GtkWidget *widget, gpointer user_data);
void on_regularpolygon_rb_clicked(GtkWidget *widget, gpointer user_data);
void on_freehandpolygon_rb_clicked(GtkWidget *widget, gpointer user_data);
void on_circularcrown_rb_clicked(GtkWidget *widget, gpointer user_data);
void on_text_rb_clicked(GtkWidget *widget, gpointer user_data);
gboolean on_drawingarea1_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void on_button1_clicked(GtkWidget *widget, gpointer user_data);
void pari_destroy(GtkWidget *window, gpointer data);
gboolean pari_delete_event(GtkWidget *window, GdkEvent *event, gpointer data);
void pari_InterceptCTRL_C(int a);
/* src/auxcallbacks.c */
void pari_draw_regularpolygon(GdkEvent *event);
void pari_draw_starpolygon(GdkEvent *event);
void pari_draw_freehandpolygon(GdkEvent *event);
void pari_draw_circularcrown(GdkEvent *event);
void pari_draw_text(GdkEvent *event);
#ifdef __cplusplus
}
#endif
