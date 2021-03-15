#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>

struct Clipboard {
    int elements_max;
    int elements_count;
    gchar **elements;
} typedef Clipboard;

Clipboard* clipboard_new(int elements_max);
void clipboard_element_add(Clipboard* clipboard, char* str_value);
void clipboard_print(Clipboard* clipboard);

void handle_owner_change (GtkClipboard *clipboard, GdkEvent *event, gpointer data) {
    // Avoid 'unused args' warning.
    (void)event;
    (void)data;

    // Get the selected text from the clipboard; note that we could get back NULL if
    // the clipboard is empty or does not contain text.
    char* text = gtk_clipboard_wait_for_text(clipboard);
    if (text) {
        printf("%s\n", text);
        g_free(text);
    }
}

static gboolean check_escape(GtkWidget* widget, GdkEventKey* event, gpointer data) {
    if (event->keyval == GDK_KEY_Escape) {
        gtk_main_quit();
        return TRUE;
    }
    return FALSE;
}

void hello(GtkWidget* widget, gpointer data) {
    printf("Hello world!\n");
}

int main(int argc, char** argv) {
    // Standard boilerplate: initialize the toolkit.
    gtk_init(&argc, &argv);

    // Get a handle to the given clipboard. You can also ask for
    // GDK_SELECTION_PRIMARY (the X "primary selection") or
    // GDK_SELECTION_SECONDARY.
    GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

    // Connect to the 'owner-change' signal which means that ownership
    // of the X clipboard has changed.
    g_signal_connect(clipboard, "owner-change", G_CALLBACK(handle_owner_change), NULL);

    // Borderless window
    GtkWidget* window;
    GtkWidget* button;
    GtkWidget* list_box;
    GtkWidget* list_box_row;
    GtkWidget* list_box_row2;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    button = gtk_button_new_with_label("Hello world!");
    list_box = gtk_list_box_new();
    list_box_row = gtk_list_box_row_new();
    list_box_row2 = gtk_list_box_row_new();

    gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_SINGLE);

    gtk_container_add(GTK_CONTAINER(window), list_box);
    gtk_list_box_prepend(GTK_LIST_BOX(list_box), list_box_row);
    gtk_container_add(GTK_CONTAINER(list_box_row), button);
    gtk_container_add(GTK_CONTAINER(list_box_row2), gtk_label_new("Hello world 2!"));
    gtk_list_box_prepend(GTK_LIST_BOX(list_box), list_box_row2);

    gtk_window_set_decorated((GtkWindow*)window, 0);

    //g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), NULL);
    //g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    Clipboard* clipboard1 = clipboard_new(50);
    clipboard_element_add(clipboard1, "Hello clipboard!");
    clipboard_element_add(clipboard1, "Hopefully this works!");

    for (int i = 0; i < clipboard1->elements_count; i++) {
        GtkWidget* list_box_row = gtk_list_box_row_new();
        gtk_container_add(GTK_CONTAINER(list_box_row), gtk_label_new(clipboard1->elements[i]));
        gtk_list_box_prepend(GTK_LIST_BOX(list_box), list_box_row);
    }
    g_signal_connect(window, "key_press_event", G_CALLBACK(check_escape), NULL);

    gtk_widget_show_all(window);

    // Run the GTK main loop so that we get the owner-change signal until
    // the user kills the program.
    gtk_main();

    return 0;
}

Clipboard* clipboard_new(int elements_max) {
    Clipboard* clipboard = malloc(sizeof(Clipboard));
    clipboard->elements = malloc(elements_max * sizeof(gchar));
    clipboard->elements_max = elements_max;
    clipboard->elements_count = 0;
    return clipboard;
}

void clipboard_element_add(Clipboard* clipboard, char* str_val) {
    if (clipboard->elements_count >= clipboard->elements_max)
        return;

    //strcpy((char *)(clipboard->elements[clipboard->elements_count]), str_val);
    clipboard->elements_count++;
}

void clipboard_print(Clipboard* clipboard) {
    for (int i = 0; i < clipboard->elements_count; i++)
        printf("%s", *(clipboard->elements + i));
}
