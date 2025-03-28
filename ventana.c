#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void compilar(GtkWidget *widget, gpointer data) {
    GtkWidget *codigo_fuente = GTK_WIDGET(g_object_get_data(G_OBJECT(data), "codigo_fuente"));
    GtkWidget *salida_compilacion = GTK_WIDGET(g_object_get_data(G_OBJECT(data), "salida_compilacion"));

    GtkTextBuffer *buffer_codigo = gtk_text_view_get_buffer(GTK_TEXT_VIEW(codigo_fuente));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer_codigo, &start);
    gtk_text_buffer_get_end_iter(buffer_codigo, &end);
    char *codigo = gtk_text_buffer_get_text(buffer_codigo, &start, &end, TRUE);

    FILE *temp_file = fopen("temp.codigo", "w");
    if (temp_file) {
        fprintf(temp_file, "%s", codigo);
        fclose(temp_file);
    }

    char comando[1024];
    sprintf(comando, "..\\a.exe temp.codigo"); // Ruta relativa correcta

    FILE *pipe = _popen(comando, "r"); 
    
    if (pipe) {
        char buffer[1024];
        char salida[4096] = "";
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            strcat(salida, buffer);
        }
        pclose(pipe);

        GtkTextBuffer *buffer_salida = gtk_text_view_get_buffer(GTK_TEXT_VIEW(salida_compilacion));
        gtk_text_buffer_set_text(buffer_salida, salida, -1);
    }
    g_free(codigo);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Compilador ESHTML");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    // Etiqueta "C:/" y entrada de texto en la primera fila
    GtkWidget *label = gtk_label_new("C:/");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1); // Columna 0, fila 0
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);

    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1); // Columna 1, fila 0

    // Text view para el código fuente en la segunda fila
    GtkWidget *codigo_fuente = gtk_text_view_new();
    gtk_grid_attach(GTK_GRID(grid), codigo_fuente, 0, 1, 2, 1); // Ocupa columnas 0 y 1, fila 1

    // Botón "Compilar" en la tercera fila
    GtkWidget *boton_compilar = gtk_button_new_with_label("Compilar");
    gtk_grid_attach(GTK_GRID(grid), boton_compilar, 2, 0, 1, 1); // Cambiado a columna 2, fila 0

    // Text view para la salida de compilación en la cuarta fila
    GtkWidget *salida_compilacion = gtk_text_view_new();
    gtk_grid_attach(GTK_GRID(grid), salida_compilacion, 0, 3, 2, 1); // Ocupa columnas 0 y 1, fila 3

    g_object_set_data(G_OBJECT(window), "codigo_fuente", codigo_fuente);
    g_object_set_data(G_OBJECT(window), "salida_compilacion", salida_compilacion);

    g_signal_connect(boton_compilar, "clicked", G_CALLBACK(compilar), window);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}