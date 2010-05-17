/*
   glib-module.c  --  2006.04.01
   plugin example with GLib: main application
   compile: gcc -Wall glib-module.c `pkg-config --cflags --libs gtk+-2.0 gmodule-2.0` -o glib-module
*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h>
#include <gtk/gtk.h>

GtkWidget * main_window = NULL;
GModule * module = NULL;
gchar * module_path;
gint module_results = 0;
int (*module_func) (gchar *);
gchar * module_text = NULL;

gint delete_event (GtkWidget * widget,  GdkEvent * event,  gpointer data)  {
  gtk_main_quit ();
  return FALSE;
}

void main_window_create ()  {
  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT(main_window), "delete_event", G_CALLBACK (delete_event), NULL);
  gtk_window_set_title (GTK_WINDOW(main_window), "glib-module test");
}

int main (int argc, char * argv[])  {
  gtk_init (&argc, &argv);
  /* if plugins not supported */
  if (!g_module_supported())  {
    perror ("module not supported");
    return EXIT_FAILURE;
  }
  module_path = g_new0 (gchar, 200);
  module_path = g_module_build_path ("plugins", "plug_01");
  module = g_module_open (module_path, G_MODULE_BIND_LAZY);
  if (module != NULL)
    g_message ("open\n");
  else {
        g_error ("module path not found: %s", module_path);
        return EXIT_FAILURE;
  }
  g_message ("module name: %s\n", g_module_name (module));
  g_message ("module path: %s\n", module_path);
  /* module function */
  if (g_module_symbol (module, "module_test", (gpointer*)&module_func))
    g_message ("func symbol\n");
  else {
        g_error ("module_test symbol not found");
        return EXIT_FAILURE;
  }
  module_results = module_func ("function_parameter");
  g_message ("module results: %d\n", module_results);
  /* module text constans */
  if (g_module_symbol (module, "module_text", (gpointer*)&module_text))
    g_message ("text symbol\n");
  else {
        g_error ("module_text symbol not found");
        return EXIT_FAILURE;
  }
  g_message ("module text constans: %s", module_text);
  if (g_module_close (module))
    g_message ("close\n");
  g_message ("last module error: %s", g_module_error());
  g_free (module_path);
  main_window_create ();
  gtk_widget_show_all (main_window);
  gtk_main ();
  return EXIT_SUCCESS;
}

