#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) {
	(void) user_data;
	
	GtkWidget *window = gtk_application_window_new(app);
	GtkWidget *grid   = gtk_grid_new();
	
	GtkWidget *label  = gtk_label_new(NULL);
	gtk_label_set_markup (GTK_LABEL(label), "<span weight='bold' font_style='italic' size='36pt'>GTA V Pauser</span>");
	
	GtkWidget *label2  = gtk_label_new("");

	// Grid setup
	gtk_grid_set_column_spacing(GTK_GRID(grid), 64);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 64);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

	// Buttons yay
	GtkWidget *button1 = gtk_button_new_with_label("Pause GTA");
	GtkWidget *button2 = gtk_button_new_with_label("Resume GTA");

	// Place them in the grid
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 4, 2);
	gtk_grid_attach(GTK_GRID(grid), button1, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), button2, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label2, 0, 4, 4, 2);

	gtk_window_set_child (GTK_WINDOW (window), grid);
  
	gtk_window_set_title(GTK_WINDOW(window), "GTA V Pauser");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

	g_signal_connect_swapped(button1, "clicked", G_CALLBACK(gtk_window_close), window);
	g_signal_connect_swapped(button2, "clicked", G_CALLBACK(gtk_window_close), window);
	
	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
