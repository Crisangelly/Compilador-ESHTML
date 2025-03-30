#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void compilar(GtkWidget *widget, gpointer data) {
    GtkWidget *entry = GTK_WIDGET(g_object_get_data(G_OBJECT(data), "entry")); // Obtener el GtkEntry
    GtkWidget *salida_compilacion = GTK_WIDGET(g_object_get_data(G_OBJECT(data), "salida_compilacion"));

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    const char *codigo = gtk_entry_buffer_get_text(buffer);

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
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Compilador ESHTML");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    GtkWidget *initial_label = gtk_label_new("Ingresa tu etiqueta ESHTML");
    gtk_grid_attach(GTK_GRID(grid), initial_label, 0, 0, 3, 1); 
    gtk_label_set_xalign(GTK_LABEL(initial_label), 0.5); 

    // Etiqueta "C:/" y entrada de texto en la primera fila
    GtkWidget *label = gtk_label_new("C:\\");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1); // Columna 0, fila 0
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 150);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 20, 1); // Columna 1, fila 0

    // Botón "Compilar" en la tercera fila
    GtkWidget *boton_compilar = gtk_button_new_with_label("Compilar");
    gtk_grid_attach(GTK_GRID(grid), boton_compilar, 21, 1, 1, 1); // Cambiado a columna 2, fila 0

    // Text view para la salida de compilación en la cuarta fila
    GtkWidget *salida_compilacion = gtk_text_view_new();
    GtkWidget *scrolled_salida = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_salida), salida_compilacion);
    gtk_grid_attach(GTK_GRID(grid), scrolled_salida, 0, 3, 200, 1);

    // Permitir que la ventana de desplazamiento se expanda verticalmente
    gtk_widget_set_hexpand(scrolled_salida, TRUE);
    gtk_widget_set_vexpand(scrolled_salida, TRUE);
    
    // Configurar la fuente monoespaciada
    gtk_widget_set_css_classes(salida_compilacion, (const char*[]){ "monospace", NULL });
    const char *css = "textview.monospace { font-family: Monospace; }";
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, css);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    g_object_set_data(G_OBJECT(window), "entry", entry); // Guardar el GtkEntry
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