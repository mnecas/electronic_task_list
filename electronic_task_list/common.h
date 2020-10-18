#pragma once
// TODO split to multiple header files and use: 
/*
#ifndef HEADERNAME
#define HEADERNAME
...
#endif
*/
#include "structs.c"

void render_month(Date* date);
void render_day(Date* date);
void render_week(Date* date);

void run(Date* date);
void run_day(Date* date);
void run_week(Date* date);
void run_month(Date* date);

int year_code(int year);
int number_of_weekday(int day, int month, int year);
int is_leap_year(int year);
int number_of_days(int month, int year);
void get_days_in_week(Date* date, int* resp);
//void update_date(Date *date, int change);
const char* get_month_name(int month);