#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#include "file_handler.h"
#define max_std 500



int register_students(student *s){
    student list[max_std]; // max 500
    int count = load_students(list, max_std); // count = total students loaded
    if (count < 0) count = 0;

    for (int i = 0; i < count; i++){
        if (strcmp(list[i].roll_no, s->roll_no) == 0) {
            printf("The roll exists in the database!\n");
            return 1;
        }
    }

    // If incoming student has any non-zero meals, clear them (start fresh)
    int has_meals = 0;
    for (int l = 0; l < 30; l++){
        if (s->meals_consumed[l] != 0) { has_meals = 1; break; }
    }
    if (has_meals){
        for (int l = 0; l < 30; l++) s->meals_consumed[l] = 0;
    }

    if (count >= max_std) {
        printf("Student database is full. Cannot register more students.\n");
        return 2;
    }

    // Append the new student and persist
    list[count] = *s;
    count++;
    save_students(list, count);
    printf("Student registered successfully!\n");
    return 0;
}


//view profile
int view_profile(const char *roll_no){
    student list[max_std]; //max 500
    int count = load_students(list, max_std); //count = total student loaded

    for (int i = 0; i < count; i++)
    {
        if(strcmp(list[i].roll_no, roll_no)==0){
            printf("----- Student Profile -----\n");
            printf("Roll No        : %s\n", list[i].roll_no);
            printf("Name           : %s\n", list[i].name);
            printf("Room Number    : %d\n", list[i].room_number);
            printf("Balance        : %.2lf\n", list[i].current_balance);
            printf("Meals (30 days): ");
            for(int v = 0; v<30; v++) {
                if(v%7==0) printf("\n");
                printf("%d ", list[i].meals_consumed[v]);
            }
            printf("\n---------------------------\n");
            return 0;
        }
    }
    printf("Student NOT FOUND!\n");
    return 1;
}


//chnage room
int update_room_number(const char *roll_no, int new_room_no){
    student list[max_std];
    int count = load_students(list, max_std);
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if(strcmp(list[i].roll_no, roll_no)==0){
            list[i].room_number = new_room_no;
            found = 1; break;
        }
    }
    if(found==0){
        printf("Student NOT FOUND!\n");
    }
    
    save_students(list, count);
    printf("Room updated successfully!\n");
    return 0;
}