#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <gmodule.h>

static void list_box_add_entry(char *value);

GList *_list;
GtkWidget *_list_box;
GtkWidget *_window;

void handle_owner_change(GtkClipboard *clipboard, GdkEvent *event, gpointer data) {
    // Avoid 'unused args' warning.
    (void) event;
    (void) data;

    // Get the selected text from the clipboard; note that we could get back NULL if
    // the clipboard is empty or does not contain text.
    char *text = gtk_clipboard_wait_for_text(clipboard);
    if (text) {
        printf("'%s' added to the clipboard.\n", text);
        _list = g_list_prepend(_list, text);
        list_box_add_entry(text);
        g_free(text);
    }
}

static gboolean check_escape(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Escape) {
        gtk_main_quit();
        return TRUE;
    }
    return FALSE;
}

static void hello() {
}

static void handle_click(GtkWidget *widget, gpointer *data) {
    g_print("Hello again - %s was pressed\n", gtk_button_get_label(GTK_BUTTON(widget)));
}

int main(int argc, char **argv) {
    // Standard boilerplate: initialize the toolkit.
    gtk_init(&argc, &argv);

    // Get a handle to the given clipboard. You can also ask for
    // GDK_SELECTION_PRIMARY (the X "primary selection") or
    // GDK_SELECTION_SECONDARY.
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

    // Connect to the 'owner-change' signal which means that ownership
    // of the X clipboard has changed.
    g_signal_connect(clipboard, "owner-change", G_CALLBACK(handle_owner_change), NULL);

    // Borderless _window
    _window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated((GtkWindow *) _window, 0);

    // List box container
    _list_box = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(_list_box), GTK_SELECTION_SINGLE);
    gtk_container_add(GTK_CONTAINER(_window), _list_box);
    // Add _list box to _window


    _list = (GList*) NULL;
    _list = g_list_prepend(_list, "Hi world!");
    _list = g_list_prepend(_list, "Jesus");

    for (GList *i = g_list_first(_list); i; i = i->next) {
        GtkWidget *list_box_row;
        list_box_row = gtk_list_box_row_new();
        gtk_list_box_prepend(GTK_LIST_BOX(_list_box), list_box_row);

        GtkWidget *button;
        button = gtk_button_new_with_label(i->data);
        gtk_container_add(GTK_CONTAINER(list_box_row), button);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(handle_click), NULL);
    }

//    g_signal_connect(G_OBJECT(event_box), "clicked", G_CALLBACK(hello), NULL);

    g_signal_connect(_window, "key_press_event", G_CALLBACK(check_escape), NULL);
    gtk_widget_show_all(_window);

    // Run the GTK main loop so that we get the owner-change signal until
    // the user kills the program.
    gtk_main();

    return 0;
}

static void list_box_add_entry(char *value) {
    GtkWidget *list_box_row;
    list_box_row = gtk_list_box_row_new();
    gtk_list_box_prepend(GTK_LIST_BOX(_list_box), list_box_row);

    GtkWidget *button;
    button = gtk_button_new_with_label(value);
    gtk_container_add(GTK_CONTAINER(list_box_row), button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(handle_click), NULL);

    gtk_widget_show_all(_window);
}