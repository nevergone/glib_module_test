#include "libplug_01.h"

G_MODULE_EXPORT extern gint modul_teszt (gchar * szoveg)  {
	g_message ("ez a modulbol jon: %s\n", szoveg);
	g_message ("ez pedig a modul valtozoja: %d\n", modul_valtozo);
	GtkWidget * plugin_window = NULL;
	plugin_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(plugin_window), "plugin_window");
	gtk_widget_show (plugin_window);
	return modul_valtozo;
}
