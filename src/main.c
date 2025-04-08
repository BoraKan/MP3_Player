#include <gtk/gtk.h>
#include "functions.h"
#include "mp3_player.h"

int main(int argc, char *argv[]) {
    // Initialize GStreamer for media playback
    initialize_gstreamer();

    // Initialize the playlist for managing songs
    initialize_playlist();

    // Create and start the UI
    create_ui(argc, argv);

    // Free allocated resources when exiting
    free_playlist();

    return 0;
}
