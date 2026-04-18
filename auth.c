#include <stdio.h>
#include <string.h>
#include "student.h"
#include "auth.h"
#include "file_handler.h"

int admin_login(){
    char temp_pass[20];
    printf("Enter admin password:");
    scanf("%19s", temp_pass);

    if (strcmp(temp_pass, "admin123")==0)
    {
        printf("Admin login SUCCESSFUL!\n"); return 1;
    }printf("Wrong admin password!\n");
    return 0;
}


int student_login(){
    char temp_roll[15];
    printf("Enter student id: ");
    scanf("%14s", temp_roll);
    if(view_profile(temp_roll)==0){
        printf("Student login Successful!\n");
        return 1;
    }
    printf("Student login FAILED!\n");
    return 0;
}