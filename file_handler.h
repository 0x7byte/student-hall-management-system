#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include "student.h"

int load_students(student students[], int max);
void save_students(student students[], int count);
void save_meal_log(const char *roll_no, int day, int meal_id);
int find_student_index(student students[], int count, const char *roll_no);
#endif