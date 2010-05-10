/* glib-module.c  --  2006.04.01
   Modulkeszites (pluginek hasznalata) GLib segitsegevel. */

#include "glib-module.h"

void main_window_create ()  {
  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT(main_window), "delete_event", G_CALLBACK (delete_event), NULL);
  gtk_window_set_title (GTK_WINDOW(main_window), "glib-module test");
}


gint delete_event (GtkWidget * widget,  GdkEvent * event,  gpointer data)  {
  gtk_main_quit ();
  return FALSE;
}


int main (int argc, char * argv[])  {
  gtk_init (&argc, &argv);
  /* ha a modulkezeles nem tamogatott a rendszeren */
  if (!g_module_supported())  {
    perror ("module not supported");
    return EXIT_FAILURE;
  }
  modul_path = g_new0 (gchar, 200);
  modul_path = g_module_build_path ("plugins", "plug_01");
  modul = g_module_open (modul_path, G_MODULE_BIND_LAZY);
  if (modul != NULL)  g_message ("open\n");
	else {
	  g_error ("modulpath nem talalhato: %s", modul_path);
    return EXIT_FAILURE;
	}
  g_message ("modul neve: %s\n", g_module_name (modul));
  g_message ("modul path: %s\n", modul_path);
  if (g_module_symbol (modul, "modul_teszt", (gpointer*)&modul_fuggveny))  g_message ("symbol\n");
	else {
	  g_error ("szimbolum nem talalhato");
    return EXIT_FAILURE;
	}

  modul_visszateresi_erteke = modul_fuggveny ("fuggveny_parameter");
  g_message ("modul visszateresi erteke: %d\n", modul_visszateresi_erteke);
  if (g_module_close (modul))  g_message ("close\n");
  g_free (modul_path);
  main_window_create ();
  gtk_widget_show_all (main_window);
  gtk_main ();
  return EXIT_SUCCESS;
}
