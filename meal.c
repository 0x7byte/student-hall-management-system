#include <stdio.h>
#include <string.h>
#include <time.h>
#include "meal.h"
#include "student.h"
#include "file_handler.h"
#define max_std 500

#define meal_b 1 // 001 
#define meal_l 2 // 010 
#define meal_d 4 // 100 



int meal_no_to_bin(int meal_no){
    if (meal_no == 1) return meal_b;
    if (meal_no == 2) return meal_l;
    if (meal_no == 3) return meal_d;
    return 0;
}

void display_menu(void){
    printf("----- Meal Menu -----\n");
    printf("1) Breakfast --> (egg, paratha)\n");
    printf("2) Lunch --> (chicken, rice, vegetable)\n");
    printf("3) Dinner --> (beef[kala bhuna], plain rice, dal, salad)\n");
    printf("Price: Breakfast = 30, Lunch = 50, Dinner = 60\n");
    printf("---------------------\n");
}

int book_meal(const char *roll_no, int day, int meal_no){
    if (day < 1 || day > 30) {
        printf("Invalid day. Eg.(1-30)\n");
        return 1;
    }

    int bit = meal_no_to_bin(meal_no);
    if (bit == 0) {
        printf("Invalid meal no.\n");
        return 1;
    }

    student list[max_std];
    int count = load_students(list, max_std);
    int index = find_student_index(list, count, roll_no);

    if (index < 0) {
        printf("Student not found.\n");
        return 1;
    }

    int temp_day = day - 1;
    list[index].meals_consumed[temp_day] |= bit;
    save_students(list, count);

    printf("Meal booked! Roll=%s Day=%d Meal_No=%d\n", roll_no, day, meal_no);
    return 0;
}

int cancel_meal(const char *roll_no, int day, int meal_no){
    if (day < 1 || day > 30) {
        printf("Invalid day. Eg.(1-30)\n");
        return 1;
    }

    int bit = meal_no_to_bin(meal_no);
    if (bit == 0) {
        printf("Invalid meal no.\n");
        return 1;
    }

    if (meal_no == 3) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        if (tm.tm_hour >= 16) {
            printf("Can't cancel dinner.\n");
            return 1;
        }
    }

    student list[max_std];
    int count = load_students(list, max_std);
    int index = find_student_index(list, count, roll_no);

    if (index < 0) {
        printf("Student not found.\n");
        return 1;
    }

    int temp_day = day - 1;
    list[index].meals_consumed[temp_day] &= ~bit;
    save_students(list, count);

    printf("Meal Cancelled! Roll=%s Day=%d Meal_No=%d\n", roll_no, day, meal_no);
    return 0;
}

int check_meal_status(const char *roll_no, int day){
    if (day < 1 || day > 30) {
        printf("Invalid day. Eg.(1-30)\n");
        return 1;
    }

    student list[max_std];
    int count = load_students(list, max_std);
    int index = find_student_index(list, count, roll_no);
    if (index < 0) {
        printf("Student not found.\n");
        return 1;
    }

    int bit = list[index].meals_consumed[day - 1];
    printf("Meal status for %s on day %d: ", roll_no, day);
    if (bit & meal_b) printf("Breakfast ");
    if (bit & meal_l) printf("Lunch ");
    if (bit & meal_d) printf("Dinner ");
    if (bit == 0) printf("No meals booked");
    printf("\n");
    return 0;
}


#define MAX_STUDENTS 200
#define MAX_DAYS 30

typedef struct {
    char roll[20];
    char name[50];
    int room;
    double balance;
    int meal[MAX_DAYS];
} Student;

void log_meal(const char *roll, int day, int meal_code) {
    FILE *fp = fopen("students.txt", "r");
    Student students[MAX_STUDENTS];
    int count = 0, i, d;

    if (fp) {
        while (fscanf(fp, "%s %s %d %lf",
                      students[count].roll,
                      students[count].name,
                      &students[count].room,
                      &students[count].balance) == 4) {
            for (d = 0; d < MAX_DAYS; d++) {
                fscanf(fp, "%d", &students[count].meal[d]);
            }
            count++;
        }
        fclose(fp);
    }

    for (i = 0; i < count; i++) {
        if (strcmp(students[i].roll, roll) == 0) {
            if (day >= 1 && day <= MAX_DAYS) {
                students[i].meal[day - 1] = meal_code;
            }
            break;
        }
    }

    fp = fopen("meal_log.txt", "w");
    if (!fp) return;

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s %s %d %.2f ",
                students[i].roll,
                students[i].name,
                students[i].room,
                students[i].balance);
        for (d = 0; d < MAX_DAYS; d++) {
            fprintf(fp, "%d ", students[i].meal[d]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}
