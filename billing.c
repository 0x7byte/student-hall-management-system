#include <stdio.h>
#include <string.h>
#include <time.h>
#include "billing.h"
#include "file_handler.h"

#define max_std 500
#define meal_b 1 //0001
#define meal_l 2 //0010
#define meal_d 4 //0100

#define PRICE_BREAKFAST 30.0
#define PRICE_LUNCH     50.0
#define PRICE_DINNER    60.0

int count_meal_days(const student *s) {
    int days = 0;
    for (int i = 0; i < 30; i++) {
        if (s->meals_consumed[i] != 0) days++;
    }
    return days;
}

double calculate_monthly_bill(const char *roll_no) {
    student list[max_std];
    int count = load_students(list, max_std);
    int index = find_student_index(list, count, roll_no);
    if (index < 0) return -1.0;

    student *s = &list[index];
    double total = 0.0;

     for (int d = 0; d < 30; d++) {
        int bit = s->meals_consumed[d];
        if (bit & 1) total += PRICE_BREAKFAST;
        if (bit & 2) total += PRICE_LUNCH;
        if (bit & 4) total += PRICE_DINNER;
    }
    int meal_days = count_meal_days(s);
    double rebate = generate_rebate(total, meal_days);
    total -= rebate;

    return total;
}

double generate_rebate(double bill_amount, int total_meal_days) {
    if (total_meal_days >= 25) {
        return bill_amount * 0.05; 
    }
    return 0.0;
}

int deduct_balance(const char *roll_no, double amount) {
    student list [max_std];
    int count = load_students(list, max_std);
    int index = find_student_index(list, count, roll_no);
    if (index < 0) return 1;

    list[index].current_balance -= amount;
    save_students(list, count);
    return 0;
}