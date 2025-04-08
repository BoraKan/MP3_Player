#ifndef MP3_PLAYER_H
#define MP3_PLAYER_H

#include <gtk/gtk.h>

// Function declarations for creating the UI
void create_ui(int argc, char *argv[]);

// Callback function declarations for button interactions
void play_stop_button_clicked(GtkWidget *widget, gpointer data);
void next_button_clicked(GtkWidget *widget, gpointer data);
void previous_button_clicked(GtkWidget *widget, gpointer data);
void shuffle_button_clicked(GtkWidget *widget, gpointer data);

#endif // MP3_PLAYER_H
