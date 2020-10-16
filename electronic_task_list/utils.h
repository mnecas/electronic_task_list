#pragma once
#pragma once

int year_code(int year);
int number_of_weekday(int day, int month, int year);
int is_leap_year(int year);
int number_of_days(int month, int year);
void get_days_in_week(int day, int month, int year, int* resp);
void update_date(int* day, int* month, int* year, int change);
const char* get_month_name(int month);