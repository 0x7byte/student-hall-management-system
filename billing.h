#ifndef BILLING_H
#define BILLING_H

double calculate_monthly_bill(const char *roll_no);
double generate_rebate(double bill_amount, int total_meal_days);
int deduct_balance(const char *roll_no, double amount);

#endif