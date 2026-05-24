#include <stdio.h>
#include "main_window.h"

void app_activate(GtkApplication *self, gpointer data);
static void load_css(void);


int main(int argc, char* argv[]) {

	const gchar *app_id = "com.github.enguessT.banking_app";
	GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  	//g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

	int res = g_application_run(G_APPLICATION(app), argc, argv);
	(void) res;
  	g_object_unref(app);

	return 0;
}

void app_activate(GtkApplication *self, gpointer data) {
	(void) data;
	load_css();
	GtkWidget*window = create_main_window(self);
	gtk_window_present(GTK_WINDOW(window));
}

static void load_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "src/ui/styles.css", NULL);

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    g_object_unref(provider);
}
