#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "auth.h"
#include "billing.h"
#include "student.h"
#include "meal.h"

void admin_menu();
void student_menu(const char *roll_no);

int main(){
    int choice;
    while(1){
        printf("\n===== MESS MANAGEMENT SYSTEM =====\n");
        printf("1. Admin Login\n");
        printf("2. Student Login\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Exiting system...\n");
            break;
        }

        else if (choice == 1)
        {
            if (admin_login()==1) 
                admin_menu();
            
        }
        else if(choice == 2){
            char roll[15];
            printf("Enter the roll no: ");
            scanf("%14s", roll);

            if (view_profile(roll)==0)
            {
                student_menu(roll);
            }else {
                printf("Student login failed.\n");
            }
            
        }else {
            printf("Invalid choice.\n");
        }
        
    }
}


void admin_menu() {
    int choice;
    char roll_no[15];

    while (1) {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Register Student\n");
        printf("2. Calculate Monthly Bill\n");
        printf("3. Deduct Balance\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Admin logged out.\n");
            return;
        }

        else if (choice == 1) {
            student s;
            printf("Enter Roll No: ");
            scanf("%14s", s.roll_no);
            printf("Enter Name: ");
            scanf("%49s", s.name);
            printf("Enter Room Number: ");
            scanf("%d", &s.room_number);
            printf("Enter Initial Balance: ");
            scanf("%lf", &s.current_balance);
            for (int i = 0; i < 30; i++) s.meals_consumed[i] = 0;

            register_students(&s);
        }

        else if (choice == 2) {
            printf("Enter Roll No: ");
            scanf("%14s", roll_no);

            double bill = calculate_monthly_bill(roll_no);
            if (bill < 0)
                printf("Student not found.\n");
            else
                printf("Total Bill for %s = %.2f\n", roll_no, bill);
        }

        else if (choice == 3) {
            double amount;
            printf("Enter Roll No: ");
            scanf("%14s", roll_no);
            printf("Enter amount to deduct: ");
            scanf("%lf", &amount);

            if (deduct_balance(roll_no, amount) == 0) //auto 5%
                printf("Balance deducted successfully.\n");
            else
                printf("Student not found.\n");
        }else {
            printf("Invalid choice.\n");
        }
    }
}



void student_menu(const char *roll_no) {
    int choice, day, meal;

    while (1) {
        printf("\n===== STUDENT MENU =====\n");
        printf("1. View Profile\n");
        printf("2. Book Meal\n");
        printf("3. Cancel Meal\n");
        printf("4. Check Meal Status\n");
        printf("5. View Menu\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input.\n");
            continue;
        }

        if (choice == 0) {
            printf("Student logged out.\n");
            return;
        } else if (choice == 1) {
            view_profile(roll_no);
        } else if (choice == 2) {
            printf("Enter Day (1–30): ");
            if (scanf("%d", &day) != 1) {
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Invalid day.\n");
                continue;
            }
            printf("Enter Meal (1=Breakfast, 2=Lunch, 3=Dinner): ");
            if (scanf("%d", &meal) != 1) {
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Invalid meal.\n");
                continue;
            }

            book_meal(roll_no, day, meal);
        } else if (choice == 3) {
            printf("Enter Day (1–30): ");
            if (scanf("%d", &day) != 1) {
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Invalid day.\n");
                continue;
            }
            printf("Enter Meal (1=Breakfast, 2=Lunch, 3=Dinner): ");
            if (scanf("%d", &meal) != 1) {
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Invalid meal.\n");
                continue;
            }

            cancel_meal(roll_no, day, meal);
        } else if (choice == 4) {
            printf("Enter Day (1 - 30): ");
            if (scanf("%d", &day) != 1) {
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Invalid day.\n");
                continue;
            }

            check_meal_status(roll_no, day);
        } else if (choice == 5) {
            display_menu();
        } else {
            printf("Invalid choice.\n");
        }
    }
}