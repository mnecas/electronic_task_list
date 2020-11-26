#pragma once
// TODO split to multiple header files and use: 
/*
#ifndef HEADERNAME
#define HEADERNAME
...
#endif
*/
#include "structs.c"

enum runType { day=0, week, month };

void render_month(Date* date);
void render_day(Date* date);
void render_week(Date* date);

void run(Date* date, enum runType format);

int year_code(int year);
int number_of_weekday(int day, int month, int year);
int is_leap_year(int year);
int number_of_days(int month, int year);
void get_days_in_week(Date* date, int* resp);
void update_date(Date *date, int change);
const char* get_month_name(int month);