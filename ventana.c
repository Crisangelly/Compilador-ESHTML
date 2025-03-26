#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *entry;
  GtkWidget *label;
  GtkWidget *label_salida;
  GtkWidget *scrolled_window;
  GtkWidget *text_view;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Compilador ESHTML");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  label = gtk_label_new("C:/");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

  label_salida = gtk_label_new("Salida:");
  gtk_grid_attach(GTK_GRID(grid), label_salida, 0, 1, 2, 1);

  scrolled_window = gtk_scrolled_window_new();
  gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 2, 2, 1);

  text_view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);

  gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}