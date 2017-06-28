#include "tictactoe.h"

#include "ttt_functional_test_util.h"

#include <glib.h>
#include <glib-object.h>

#include <gtk/gtk.h>

GtkWindow *window;
Tictactoe *ttt;

extern struct timespec ttt_functional_test_util_default_timeout;

void*
ttt_functional_test_gtk_main(void *ptr)
{
  gtk_main();

  pthread_exit(NULL);
}

void
ttt_functional_test_dumb_player_b()
{
  GtkButton *buttons[3][3];

  guint i;
  
  /* to avoid race-conditions copy the buttons */
  gdk_threads_enter();
  
  memcpy(buttons, ttt->buttons, 9 * sizeof(GtkButton *));

  gdk_threads_leave();

  /* TEST 1 - the dumb player B */
  for(i = 0; i < 3; i++){
    /* assert player A clicks the button successfully */
    if(!ttt_functional_test_util_button_click(buttons[0][i])){
      exit(-1);
    }

    ttt_functional_test_util_idle_condition_and_timeout(ttt_functional_test_util_idle_test_toggle_active,
							&ttt_functional_test_util_default_timeout,
							&buttons[0][i]);


    /* assert player B clicks the button successfully */
    if(!ttt_functional_test_util_button_click(buttons[1][i])){
      exit(-1);
    }

    ttt_functional_test_util_idle_condition_and_timeout(ttt_functional_test_util_idle_test_toggle_active,
							&ttt_functional_test_util_default_timeout,
							&buttons[1][i]);
  }
}

int
main(int argc, char **argv)
{
  pthread_t thread;

  gtk_init(&argc, &argv);
		 
  /* start the tictactoe application */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  ttt = tictactoe_new();
  gtk_container_add(window, ttt);

  gtk_widget_show_all(window);

  /* start the Gtk+ dispatcher */
  pthread_create(&thread, NULL,
                 ttt_functional_test_gtk_main, NULL);

  /* launch test routines */
  ttt_functional_test_dumb_player_b();

  /* terminate the application */
  gdk_threads_enter();

  gtk_main_quit();
  
  gdk_threads_leave();

  return(0);
}
