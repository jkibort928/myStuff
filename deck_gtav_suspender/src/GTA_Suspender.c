#include <gtk/gtk.h>

int ranSudo = 0;

void suspendGTA(GtkButton *button, GtkWidget *thing) {
	(void) button;
	(void) thing;

	system("/bin/kill -SIGSTOP $(pgrep GTA5.exe)");
}

void resumeGTA(GtkButton *button, GtkWidget *thing) {
	(void) button;
	(void) thing;

	system("/bin/kill -SIGCONT $(pgrep GTA5.exe)");
}

void disableSave(GtkButton *button, GtkWidget *thing) {
	(void) button;
	(void) thing;

	ranSudo = 1;

	system("sudo -A iptables -F");
	system("sudo -A iptables -I INPUT -s 8.8.8.8 -j DROP");
	system("sudo -A iptables -I OUTPUT -s 8.8.8.8 -j DROP");
}

void enableSave(GtkButton *button, GtkWidget *thing) {
	(void) button;
	(void) thing;

	if(ranSudo == 0) {
		return;
	}

	system("sudo -A iptables -F");
}

static void activate(GtkApplication* app, gpointer user_data) {
	(void) user_data;
	
	GtkWidget *window = gtk_application_window_new(app);
	GtkWidget *grid   = gtk_grid_new();
	
	GtkWidget *label  = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label), "<span font_family='serif' weight='bold' font_style='italic' size='36pt'> GTA V Suspender </span>");
	
	GtkWidget *label2  = gtk_label_new("");

	GtkWidget *label3  = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label3), "<span foreground='red' font_family='serif' weight='bold' size='20pt'> [sudo] </span>");
	gtk_widget_set_halign(label3, GTK_ALIGN_END);

	// Grid setup
	gtk_grid_set_column_spacing(GTK_GRID(grid), 16);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 64);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

	// Buttons yay
	GtkWidget *button1 = gtk_button_new_with_label("Suspend GTA");
	GtkWidget *button2 = gtk_button_new_with_label("Resume GTA");
	GtkWidget *button3 = gtk_button_new_with_label("Disable Saving");
	GtkWidget *button4 = gtk_button_new_with_label("Enable Saving");

	// Place them in the grid
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 4, 2);		// Title

	gtk_grid_attach(GTK_GRID(grid), button1, 1, 2, 1, 1);	// Suspend Button
	gtk_grid_attach(GTK_GRID(grid), button2, 2, 2, 1, 1);	// Resume Button

	gtk_grid_attach(GTK_GRID(grid), label3, 0, 3, 1, 1);	// Sudo Warning Label

	gtk_grid_attach(GTK_GRID(grid), button3, 1, 3, 1, 1);	// Disable Save Button
	gtk_grid_attach(GTK_GRID(grid), button4, 2, 3, 1, 1);	// Enable Save Button

	gtk_grid_attach(GTK_GRID(grid), label2, 0, 5, 4, 2);	// Blank Space

	// Put the grid on
	gtk_window_set_child (GTK_WINDOW (window), grid);
  
	gtk_window_set_title(GTK_WINDOW(window), "GTA V Suspender");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

	g_signal_connect_swapped(button1, "clicked", G_CALLBACK(suspendGTA), window);
	g_signal_connect_swapped(button2, "clicked", G_CALLBACK(resumeGTA), window);
	g_signal_connect_swapped(button3, "clicked", G_CALLBACK(disableSave), window);
	g_signal_connect_swapped(button4, "clicked", G_CALLBACK(enableSave), window);
	
	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	if(ranSudo==1){
		system("sudo -A iptables -F");
		system("echo cleaned up");
	}

	return status;
}
