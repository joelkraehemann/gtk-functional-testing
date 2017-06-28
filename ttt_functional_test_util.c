#include "ttt_functional_test_util.h"

#include <glib.h>
#include <glib-object.h>

#include <gtk/gtk.h>

struct timespec ttt_functional_test_util_default_timeout = {
  20,
  0,
};

void
ttt_functional_test_util_reaction_time()
{
  usleep(TTT_FUNCTIONAL_TEST_UTIL_REACTION_TIME);
}

void
ttt_functional_test_util_reaction_time_long()
{
  usleep(TTT_FUNCTIONAL_TEST_UTIL_REACTION_TIME_LONG);
}

void
ttt_functional_test_util_idle_condition_and_timeout(TttFunctionalTestUtilIdleCondition idle_condition,
                                                    struct timespec *timeout,
					            gpointer data)
{
  struct timespec start_time, current_time;

  clock_gettime(CLOCK_MONOTONIC,
                &start_time);

  while(TTT_FUNCTIONAL_TEST_UTIL_IDLE_CONDITION(idle_condition)(data)){
    ttt_functional_test_util_reaction_time();

    clock_gettime(CLOCK_MONOTONIC,
                  &current_time);

    if(start_time.tv_sec + timeout->tv_sec < current_time.tv_sec){
      break;
    }
  }

  ttt_functional_test_util_reaction_time();
}

gboolean
ttt_functional_test_util_button_click(GtkButton *button)
{
  GtkWidget *widget;

  GdkWindow *window;

  gint x, y;
  gint origin_x, origin_y;

  if(button == NULL ||
     !GTK_IS_BUTTON(button)){
    return(FALSE);
  }

  widget = button;

  if(!GTK_WIDGET_REALIZED(widget)){
    ttt_functional_test_util_reaction_time_long();
  }

  /* retrieve window and pointer position */
  gdk_threads_enter();

  window = gtk_widget_get_window(widget);

  x = widget->allocation.x + widget->allocation.width / 2.0;
  y = widget->allocation.y + widget->allocation.height / 2.0;

  gdk_window_get_origin(window, &origin_x, &origin_y);

  gdk_display_warp_pointer(gtk_widget_get_display(widget),
                           gtk_widget_get_screen(widget),
                           origin_x + x, origin_y + y);

  gdk_threads_leave();

  /* click the button */
  ttt_functional_test_util_reaction_time();

  gdk_test_simulate_button(window,
                           x,
                           y,
                           1,
                           GDK_BUTTON1_MASK,
                           GDK_BUTTON_PRESS);

  ttt_functional_test_util_reaction_time();

  gdk_test_simulate_button(window,
                           x,
                           y,
                           1,
                           GDK_BUTTON1_MASK,
                           GDK_BUTTON_RELEASE);

  ttt_functional_test_util_reaction_time();

  ttt_functional_test_util_reaction_time_long();

  return(TRUE);
}

gboolean
ttt_functional_test_util_idle_test_toggle_active(GtkToggleButton **toggle_button)
{
  gboolean do_idle;

  do_idle = TRUE;

  gdk_threads_enter();

  if(*toggle_button != NULL &&
     GTK_IS_TOGGLE_BUTTON(*toggle_button) &&
     gtk_toggle_button_get_active(*toggle_button)){
    do_idle = FALSE;
  }

  gdk_threads_leave();

  return(do_idle);
}
