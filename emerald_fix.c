/* 
apt-get install libunac1-dev
apt-get install libwnck-common libwnck-dev
gcc $(pkg-config --cflags --libs libwnck-1.0) -lunac emerald_fix.c -o emerald_fix 
*/

#define WNCK_I_KNOW_THIS_IS_UNSTABLE

#include <gdk/gdk.h>
#include <libwnck/libwnck.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unac.h>
#include <stdbool.h>

const size_t char_size = sizeof(char);

static void
on_state_changed(WnckWindow *window)
{
	char 			*window_name;
	char 			*window_name_unac;
	char 			*cmd;
	unsigned int 	state;
	bool 			empty_space_added;
	size_t 			window_name_length;
	char 			*window_old_state;

	state = wnck_window_get_state(window);
	window_name = setlocale(LC_ALL, "");
	window_name = wnck_window_get_name(window);
	window_name_length = strlen(window_name);
	window_name_unac = (char*) malloc(window_name_length + 1 * char_size);
	unac_string("UTF-8", window_name, window_name_length, &window_name_unac, &window_name_length);
	empty_space_added = (*(window_name_unac+window_name_length-1) == ' ');
	cmd = setlocale(LC_ALL, "");
	cmd = (char*) malloc(512 * char_size);
	window_old_state = wnck_window_get_icon_name(window);

	if (state == 0 && window_old_state[0] == '1') { 

		strcpy(cmd, "xdotool search --name \"");
		strncat(cmd, window_name, window_name_length);
		strcat(cmd, "\" set_window --name \"");
		strncat(cmd, window_name_unac, (empty_space_added ? window_name_length-1 : window_name_length));
		if (!empty_space_added)	{ strcat(cmd, " "); }
		strcat(cmd, "\"");

	} else {

		sprintf(cmd, "xdotool search --name \"%s\" set_window --icon-name \"%s\"", window_name, (state == 6) ? "1" : "0");

	}

	system(cmd);
	free(cmd);
	free(window_name_unac);
}

static void
on_new_window_opened(WnckScreen *screen, WnckWindow *window)
{
	g_signal_connect(window, "state-changed",
                     G_CALLBACK(on_state_changed), NULL);
}

gint
main(gint argc, gchar *argv[])
{
    GMainLoop *loop;
    WnckScreen *screen;

    gdk_init(&argc, &argv);
    screen = wnck_screen_get(0);

    g_signal_connect(screen, "window-opened",
                     G_CALLBACK(on_new_window_opened), NULL);

    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);

    return 0;
}