#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <gst/gst.h>
#include "functions.h"
#include "mp3_player.h"

// Directory path for songs
#define SONG_DIRECTORY_PATH "/Users/borakan/eclipse-workspace/MP3_Player/mp3_songs"

// GStreamer pipeline
static GstElement *pipeline = NULL;

// Dynamic playlist
static char **playlist = NULL;
static int playlist_size = 0;
static int current_song_index = 0;
static int shuffle_mode = 0; // 0: Off, 1: On

// Getter for shuffle_mode
int get_shuffle_mode() {
    return shuffle_mode;
}

// Setter for shuffle_mode
void set_shuffle_mode(int mode) {
    shuffle_mode = mode;
}

// Initialize GStreamer
void initialize_gstreamer() {
    gst_init(NULL, NULL);
    g_print("GStreamer initialized successfully.\n");
}

// Helper function to compare two strings (used by qsort)
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Sort the playlist alphabetically
void sort_playlist() {
    if (playlist_size > 1) {
        qsort(playlist, playlist_size, sizeof(char *), compare_strings);
    }
}

// Scan the directory for song files and add them to the playlist
void load_songs_from_directory(const char *directory_path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory_path);
    if (dir == NULL) {
        printf("Error: Could not open directory: %s\n", directory_path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Only add files with .mp3 extension
        if (strstr(entry->d_name, ".mp3")) {
            add_song(entry->d_name);
        }
    }

    closedir(dir);

    // Sort the playlist alphabetically after loading
    sort_playlist();

    printf("Songs loaded from directory: %s\n", directory_path);
}

// Get the index of the currently playing song
int get_current_song_index() {
    return current_song_index;
}

// Get the name of the song at a specific index
const char *get_song_name(int index) {
    if (index >= 0 && index < playlist_size) {
        return playlist[index];
    }
    return NULL;
}

// Stop the current song
void stop_current_song() {
    stop_song();
}

// Toggle the shuffle mode
void toggle_shuffle_mode() {
    shuffle_mode = !shuffle_mode;
    printf("Shuffle mode %s\n", shuffle_mode ? "ON" : "OFF");
}

// Play a song by its name
void play_song_by_name(const char *song_name) {
    if (!pipeline) {
        pipeline = gst_element_factory_make("playbin", "playbin");
    }

    if (!pipeline) {
        g_printerr("Failed to create GStreamer pipeline.\n");
        return;
    }

    char uri[512];
    snprintf(uri, sizeof(uri), "file://%s/%s", SONG_DIRECTORY_PATH, song_name);

    // Check if the file exists
    if (g_file_test(uri + 7, G_FILE_TEST_EXISTS)) { // Remove "file://"
        g_object_set(pipeline, "uri", uri, NULL);

        GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
        if (ret == GST_STATE_CHANGE_FAILURE) {
            g_printerr("Failed to set pipeline to PLAYING state.\n");
        } else {
            g_print("Playing: %s\n", song_name);
        }
    } else {
        g_printerr("Error: File does not exist -> %s\n", uri + 7);
    }
}

// Stop the current song
void stop_song() {
    if (pipeline) {
        GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_NULL);
        if (ret == GST_STATE_CHANGE_FAILURE) {
            g_printerr("Failed to stop playback.\n");
        } else {
            g_print("Playback stopped.\n");
        }
    } else {
        g_printerr("No active pipeline to stop.\n");
    }
}

// Initialize the playlist
void initialize_playlist() {
    playlist = NULL;
    playlist_size = 0;
    current_song_index = 0;

    // Automatically load songs from the directory
    load_songs_from_directory(SONG_DIRECTORY_PATH);
}

// Add a new song to the playlist
void add_song(const char *song_name) {
    playlist = realloc(playlist, (playlist_size + 1) * sizeof(char *));
    playlist[playlist_size] = malloc(strlen(song_name) + 1);
    strcpy(playlist[playlist_size], song_name);
    playlist_size++;
    printf("Added song: %s\n", song_name);
}

// Play the current song
void play_current_song() {
    if (playlist_size == 0) {
        printf("No songs in the playlist.\n");
        return;
    }
    play_song_by_name(playlist[current_song_index]);
}

// Play the next song
void play_next_song() {
    if (playlist_size == 0) {
        printf("No songs in the playlist.\n");
        return;
    }

    stop_song();

    if (shuffle_mode) {
        int random_index;
        do {
            random_index = rand() % playlist_size;
        } while (random_index == current_song_index);

        current_song_index = random_index;
    } else {
        current_song_index = (current_song_index + 1) % playlist_size;
    }

    play_song_by_name(playlist[current_song_index]);
    printf("Next song: %s\n", playlist[current_song_index]);
}

// Play the previous song
void play_previous_song() {
    if (playlist_size == 0) {
        printf("No songs in the playlist.\n");
        return;
    }

    stop_song();

    if (shuffle_mode) {
        int random_index;
        do {
            random_index = rand() % playlist_size;
        } while (random_index == current_song_index);

        current_song_index = random_index;
    } else {
        current_song_index = (current_song_index - 1 + playlist_size) % playlist_size;
    }

    play_song_by_name(playlist[current_song_index]);
    printf("Previous song: %s\n", playlist[current_song_index]);
}

// Free memory allocated for the playlist
void free_playlist() {
    for (int i = 0; i < playlist_size; i++) {
        free(playlist[i]);
    }
    free(playlist);
    playlist = NULL;
    playlist_size = 0;
    current_song_index = 0;
}
