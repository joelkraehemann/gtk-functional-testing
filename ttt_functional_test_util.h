#ifndef __TTT_FUNCTIONAL_TEST_UTIL_H__
#define __TTT_FUNCTIONAL_TEST_UTIL_H__

#include <glib.h>
#include <glib-object.h>

#include <gtk/gtk.h>

#define TTT_FUNCTIONAL_TEST_UTIL_IDLE_CONDITION(f) ((TttFunctionalTestUtilIdleCondition)(f))

#define TTT_FUNCTIONAL_TEST_UTIL_REACTION_TIME (125000)
#define TTT_FUNCTIONAL_TEST_UTIL_REACTION_TIME_LONG (500000)

typedef gboolean (*TttFunctionalTestUtilIdleCondition)(gpointer data);

void ttt_functional_test_util_reaction_time();
void ttt_functional_test_util_reaction_time_long();

void ttt_functional_test_util_idle_condition_and_timeout(TttFunctionalTestUtilIdleCondition idle_condition,
							 struct timespec *timeout,
							 gpointer data);

gboolean ttt_functional_test_util_button_click(GtkButton *button);

gboolean ttt_functional_test_util_idle_test_toggle_active(GtkToggleButton **toggle_button);


#endif /*__TTT_FUNCTIONAL_TEST_UTIL_H__*/
