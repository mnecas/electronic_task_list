#pragma once
// TODO split to multiple header files and use: 
/*
#ifndef HEADERNAME
#define HEADERNAME
...
#endif
*/
#include "structs.c"

#define STR_SIZE 32

enum runType { day, week, month };

void render(Date* date, Task** tasks, enum typeRun format, int move_task);
void run(Date* date, Task** tasks, enum runType format);
void add_task(int id, int time, int duration, int finished, int priority, char* label, Date date, Task** task);
void del_task(int id, Task** task);

int year_code(int year);
int number_of_weekday(int day, int month, int year);
int is_leap_year(int year);
int number_of_days(int month, int year);
void get_days_in_week(Date* date, int* resp);
void update_date(Date* date, int change);
const char* get_month_name(int month);

extern int selected;
extern int selected_id;
