#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <gst/gst.h>

// Playlist management functions
void initialize_playlist();
void add_song(const char *song_name);
void play_current_song();
void stop_current_song();
void play_next_song();
void play_previous_song();
void shuffle_playlist();
void free_playlist();
void stop_song();
void load_songs_from_directory(const char *directory_path);
void toggle_shuffle_mode();
void initialize_gstreamer();
int get_shuffle_mode();
void set_shuffle_mode(int mode);

// Utility functions
int get_current_song_index();
const char *get_song_name(int index);

#endif // FUNCTIONS_H
