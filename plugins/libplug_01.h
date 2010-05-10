#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <gmodule.h>

G_MODULE_EXPORT extern gint modul_teszt (gchar * szoveg);

int modul_valtozo = 42;
