#include <gtk/gtk.h>

static void on_show_text_from_buffer(GtkWidget *p_button, gpointer user_data) {
    char *p_text_in_entry = g_strdup(gtk_entry_buffer_get_text(user_data));
    g_print("%s\n", p_text_in_entry); 
    g_free(p_text_in_entry); 
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *label;
    GtkWidget *label_salida;
    GtkWidget *scrolled_window;
    GtkWidget *text_view;
    GtkWidget *p_button; 

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Compilador ESHTML");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    label = gtk_label_new("C:/");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1); // La entrada ocupa la columna 1

    p_button = gtk_button_new_with_label("Compilar");
    gtk_grid_attach(GTK_GRID(grid), p_button, 2, 0, 1, 1); // El botón ocupa la columna 2

    GtkEntryBuffer *p_buffer_1 = gtk_entry_buffer_new(NULL, -1);
    gtk_entry_set_buffer(GTK_ENTRY(entry), p_buffer_1);

    g_signal_connect(p_button, "clicked", G_CALLBACK(on_show_text_from_buffer), p_buffer_1);

    label_salida = gtk_label_new("Salida:");
    gtk_grid_attach(GTK_GRID(grid), label_salida, 0, 1, 3, 1); // La etiqueta "Salida" ocupa las 3 columnas
    gtk_label_set_xalign(GTK_LABEL(label_salida), 0.0);

    scrolled_window = gtk_scrolled_window_new();
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 2, 3, 1); // El scrolled_window ocupa las 3 columnas

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);

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