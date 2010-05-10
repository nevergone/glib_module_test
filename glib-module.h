#ifndef __GLIB_MODULE_H__
#define __GLIB_MODULE_H__


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h>
#include <gtk/gtk.h>


GtkWidget * main_window = NULL;
GModule * modul = NULL;
gchar * modul_path;
gint modul_visszateresi_erteke = 0;
int (*modul_fuggveny) (gchar *);

/* foablak keszitese */  
void main_window_create ();

/* ha bezarjak az alkalmazas foablakat, lefut */
gint delete_event (GtkWidget * widget,  GdkEvent * event,  gpointer data);

#endif /* __GLIB_MODULE_H__ */
