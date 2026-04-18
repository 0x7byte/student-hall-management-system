#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    char roll_no[15];
    char name[50];
    int room_number;
    double current_balance;
    int meals_consumed[30];
} student;

int register_students(student *s);
int view_profile(const char *roll_no);
int update_room_number(const char *roll_no, int new_room_no);

#endif