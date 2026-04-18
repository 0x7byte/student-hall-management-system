#include <stdio.h>
#include <string.h>
#include "file_handler.h"
// #define STUDENT_FILE "students.txt"
#define MEAL_LOG_FILE "meal_log.txt"


int load_students(student students[], int max){
    FILE *fp = fopen("students.txt", "r");
    if (!fp) return 0;

    int count = 0;
    while (count < max) {
        student s;
        if (fscanf(fp, "%14s %49s %d %lf",
                   s.roll_no, s.name, &s.room_number, &s.current_balance) != 4)
            break;

        for (int i = 0; i < 30; i++)
            fscanf(fp, "%d", &s.meals_consumed[i]);

        students[count++] = s;
    }

    fclose(fp);
    return count;
}

void save_students(student students[], int count){
    FILE *fp = fopen("students.txt", "w");
    if (!fp) return;

    for (int i = 0; i < count; i++){
        student *s = &students[i];
        fprintf(fp, "%s %s %d %.2f",
                s->roll_no, s->name, s->room_number, s->current_balance);

        for (int j = 0; j < 30; j++)
            fprintf(fp, " %d", s->meals_consumed[j]);

        fprintf(fp, "\n");
    }
    fclose(fp);
}

void save_meal_log(const char *roll_no, int day, int meal_id){
    FILE *fp = fopen("meal_log.txt", "a");
    if (!fp) return;
    fprintf(fp, "%s %d %d\n", roll_no, day, meal_id);
    fclose(fp);
}

int find_student_index(student students[], int count, const char *roll_no){
    for (int i = 0; i < count; i++)
        if (strcmp(students[i].roll_no, roll_no) == 0) return i;
    return -1;
}
