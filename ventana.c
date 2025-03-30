#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void on_show_text_from_buffer(GtkWidget *p_button, gpointer user_data) {
    char *p_text_in_entry = g_strdup(gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(user_data)));
    char command[1024];
    FILE *pipe;
    char buffer[128];
    GtkWidget *scrolled_window = gtk_grid_get_child_at(GTK_GRID(gtk_widget_get_parent(p_button)), 0, 2);
    GtkWidget *text_view = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled_window));
    GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    snprintf(command, sizeof(command), "..\\a.exe"); // Sin redirección
    pipe = popen(command, "w"); // Abrir la tubería en modo escritura
    if (pipe) {
        fprintf(pipe, "%s", p_text_in_entry); // Escribir la entrada en la tubería
        fclose(pipe); // Cerrar la tubería después de escribir
    } else {
        gtk_text_buffer_set_text(text_buffer, "Error al ejecutar el compilador.", -1);
    }

    g_free(p_text_in_entry);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Compilador ESHTML");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    GtkWidget *initial_label = gtk_label_new("Ingresa tu etiqueta ESHTML");
    gtk_grid_attach(GTK_GRID(grid), initial_label, 0, 0, 3, 1); 
    gtk_label_set_xalign(GTK_LABEL(initial_label), 0.5); 

    GtkWidget *label = gtk_label_new("C:\\");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);

    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1); // La entrada ocupa la columna 1

    GtkWidget *p_button = gtk_button_new_with_label("Compilar");
    gtk_grid_attach(GTK_GRID(grid), p_button, 2, 1, 1, 1); // El botón ocupa la columna 2

    GtkEntryBuffer *p_buffer_1 = gtk_entry_buffer_new(NULL, -1);
    gtk_entry_set_buffer(GTK_ENTRY(entry), p_buffer_1);

    g_signal_connect(p_button, "clicked", G_CALLBACK(on_show_text_from_buffer), p_buffer_1);

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 2, 2, 1); // El scrolled_window ocupa las 3 columnas

    GtkWidget *text_view = gtk_text_view_new();
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