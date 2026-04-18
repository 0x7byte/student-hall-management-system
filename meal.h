#ifndef MEAL_H
#define MEAL_H

void display_menu(void);
int add_menu(void);
int book_meal(const char *roll_no, int day, int meal_id);
int cancel_meal(const char *roll_no, int day, int meal_id);
int check_meal_status(const char *roll_no, int day);

#endif
