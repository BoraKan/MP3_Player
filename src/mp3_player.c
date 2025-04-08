#include <gtk/gtk.h>
#include "functions.h"

// Global variables
GtkWidget *window;
GtkWidget *now_playing_label;
GtkWidget *play_stop_button;
GtkWidget *next_button;
GtkWidget *previous_button;
GtkWidget *shuffle_button;
int is_playing = 0; // 0: Stopped, 1: Playing

// Constants for layout
const int BUTTON_SIZE = 50;       // Button size (square)
const int BUTTON_SPACING = 5;    // Spacing between buttons
const int WINDOW_MARGIN = 3;     // Margin around buttons

// Updates the "Now Playing" label with the current song name
void update_now_playing_label() {
    const char *current_song = get_song_name(get_current_song_index());

    if (current_song) {
        char current_song_copy[256];
        strncpy(current_song_copy, current_song, sizeof(current_song_copy));
        current_song_copy[sizeof(current_song_copy) - 1] = '\0'; // Ensure null-termination

        // Remove the ".mp3" extension if present
        char *dot = strrchr(current_song_copy, '.');
        if (dot && strcmp(dot, ".mp3") == 0) {
            *dot = '\0';
        }

        gtk_label_set_text(GTK_LABEL(now_playing_label), current_song_copy);
    } else {
        gtk_label_set_text(GTK_LABEL(now_playing_label), "No song playing");
    }
}

// Callback for Play/Stop button
void play_stop_button_clicked(GtkWidget *widget, gpointer data) {
    if (is_playing) {
        stop_current_song();
        GtkWidget *play_image = gtk_image_new_from_file("/Users/borakan/eclipse-workspace/MP3_Player/icons/play.png");
        gtk_image_set_pixel_size(GTK_IMAGE(play_image), 35);
        gtk_button_set_image(GTK_BUTTON(play_stop_button), play_image);
    } else {
        play_current_song();
        GtkWidget *stop_image = gtk_image_new_from_file("/Users/borakan/eclipse-workspace/MP3_Player/icons/stop-button.png");
        gtk_image_set_pixel_size(GTK_IMAGE(stop_image), 35);
        gtk_button_set_image(GTK_BUTTON(play_stop_button), stop_image);
    }
    is_playing = !is_playing;
    update_now_playing_label();
}

// Callback for Next button
void next_button_clicked(GtkWidget *widget, gpointer data) {
    play_next_song();
    update_now_playing_label();
}

// Callback for Previous button
void previous_button_clicked(GtkWidget *widget, gpointer data) {
    play_previous_song();
    update_now_playing_label();
}

// Callback for Shuffle button
void shuffle_button_clicked(GtkWidget *widget, gpointer data) {
    toggle_shuffle_mode();
    const char *icon_path = get_shuffle_mode() ? "/Users/borakan/eclipse-workspace/MP3_Player/icons/shuffle.png"
                                               : "/Users/borakan/eclipse-workspace/MP3_Player/icons/NoShuffle.png";

    GtkWidget *image = gtk_image_new_from_file(icon_path);
    gtk_image_set_pixel_size(GTK_IMAGE(image), 30);
    gtk_button_set_image(GTK_BUTTON(shuffle_button), image);
}

// Creates the main UI window
void create_ui(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Calculate dynamic window dimensions
    int button_count = 4; // Number of buttons in the row
    int window_width = (button_count * BUTTON_SIZE) + ((button_count - 1) * BUTTON_SPACING) + (2 * WINDOW_MARGIN);
    int window_height = BUTTON_SIZE + (2 * WINDOW_MARGIN) + 30; // Include space for the label

    // Main window setup
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "mp3Player");
    gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical layout container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // "Now Playing" label
    now_playing_label = gtk_label_new("No song playing");
    gtk_box_pack_start(GTK_BOX(vbox), now_playing_label, FALSE, FALSE, 5);

    // Horizontal layout for buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, BUTTON_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Previous button
    previous_button = gtk_button_new();
    GtkWidget *previous_image = gtk_image_new_from_file("/Users/borakan/eclipse-workspace/MP3_Player/icons/PreviousButton.png");
    gtk_image_set_pixel_size(GTK_IMAGE(previous_image), 30);
    gtk_button_set_image(GTK_BUTTON(previous_button), previous_image);
    g_signal_connect(previous_button, "clicked", G_CALLBACK(previous_button_clicked), NULL);
    gtk_widget_set_size_request(previous_button, BUTTON_SIZE, BUTTON_SIZE);
    gtk_box_pack_start(GTK_BOX(hbox), previous_button, FALSE, FALSE, 0);

    // Play/Stop button
    play_stop_button = gtk_button_new();
    GtkWidget *play_image = gtk_image_new_from_file("/Users/borakan/eclipse-workspace/MP3_Player/icons/play.png");
    gtk_image_set_pixel_size(GTK_IMAGE(play_image), 35);
    gtk_button_set_image(GTK_BUTTON(play_stop_button), play_image);
    g_signal_connect(play_stop_button, "clicked", G_CALLBACK(play_stop_button_clicked), NULL);
    gtk_widget_set_size_request(play_stop_button, BUTTON_SIZE, BUTTON_SIZE);
    gtk_box_pack_start(GTK_BOX(hbox), play_stop_button, FALSE, FALSE, 0);

    // Next button
    next_button = gtk_button_new();
    GtkWidget *next_image = gtk_image_new_from_file("/Users/borakan/eclipse-workspace/MP3_Player/icons/nextButton.png");
    gtk_image_set_pixel_size(GTK_IMAGE(next_image), 30);
    gtk_button_set_image(GTK_BUTTON(next_button), next_image);
    g_signal_connect(next_button, "clicked", G_CALLBACK(next_button_clicked), NULL);
    gtk_widget_set_size_request(next_button, BUTTON_SIZE, BUTTON_SIZE);
    gtk_box_pack_start(GTK_BOX(hbox), next_button, FALSE, FALSE, 0);

    // Shuffle button
    shuffle_button = gtk_button_new();
    GtkWidget *shuffle_image = gtk_image_new_from_file("/Users/borakan/eclipse-workspace/MP3_Player/icons/NoShuffle.png");
    gtk_image_set_pixel_size(GTK_IMAGE(shuffle_image), 30);
    gtk_button_set_image(GTK_BUTTON(shuffle_button), shuffle_image);
    g_signal_connect(shuffle_button, "clicked", G_CALLBACK(shuffle_button_clicked), NULL);
    gtk_widget_set_size_request(shuffle_button, BUTTON_SIZE, BUTTON_SIZE);
    gtk_box_pack_start(GTK_BOX(hbox), shuffle_button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();
}
