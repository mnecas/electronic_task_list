#pragma once
// TODO split to multiple header files and use: 
/*
#ifndef HEADERNAME
#define HEADERNAME
...
#endif
*/
#include "structs.c"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STR_SIZE 32
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define WHITE_BACK "\x1b[7m"
#define RESET "\x1b[0m"


typedef struct tm Date;

typedef struct {
	int hour;
	int min;
}Time;

typedef struct task
{
	Date date;
	int id;
	Time duration;
	enum priority priority;
	char label[32];
	int finished;
	struct task* next;

} Task;

enum runType { day, week, month };
enum priority { normal, minimal, maximal };

void render(Date* date, Task** tasks, enum typeRun format, int move_task);
void run(Date* date, Task** tasks, enum runType format);
void add_task(int id, Time duration, int finished, int priority, char* label, Date date, Task** task);
void del_task(int id, Task** task);

void update_date(Date* date, int change);
const char* get_month_name(int month);
void print_task_label(Task task);

extern int selected;
extern int selected_id;
