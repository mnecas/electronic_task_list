#include "common.h"
#include <stdio.h>
#include <stdlib.h>

#define WHITE_BACK "\x1b[7m"
#define RESET "\x1b[0m"
int selected = 0;
int selected_id = 0;

void render_header(Date* date)
{
	printf("\t%d\t\t\t%s\n", date->year, get_month_name(date->month));
	printf("\tSun\tMon\tTue\tWed\tThu\tFri\tSat\n");
	printf("\t");
	for (int i = 0; i < 52; i++)
		printf("-");
	printf("\n");
}
void render_options(enum runType format)
{

	printf("\n\n");
	printf("\t View options:");
	printf("\n");
	printf("\t m - month");
	printf("\t w - week");
	printf("\t d - day");
	printf("\n");
	printf("\n");
	printf("\t Control options:");
	printf("\n");
	printf("\t a - add");
	if (format == day) {
		printf("\t c - copy");
		printf("\t e - edit");
		printf("\t r - remove");
	}
	printf("\n");
}
void render_month(Date* date)
{
	// Clear previous render
	system("cls");

	// Redner header
	render_header(date);

	int _numberDay = number_of_weekday(1, date->month, date->year) - 1;
	int _numberOfDays = number_of_days(date->month, date->year);
	// Padding

	for (int i = 0; i < (_numberDay + 7) % 7; i++) printf("\t");

	for (int i = 1; i < _numberOfDays + 1; i++)
	{
		if (date->day == i) printf(WHITE_BACK "\t%d" RESET, i);
		else printf("\t%d", i);
		if ((_numberDay + i) % 7 == 0) printf("\n");
	}
	render_options(month);
}

int get_size(Date* date, Task** tasks) {
	Task* this_task = *tasks;

	int resp = 0;
	while (this_task && this_task->next) {
		if (this_task->date.day == date->day && this_task->date.month == date->month && this_task->date.year == date->year) {
			resp++;
		}
		this_task = this_task->next;
	}
	return resp;

}

void render_day(Date* date, Task** tasks, int move_task)
{
	system("cls");

	printf("\t%d. %s %d\n", date->day, get_month_name(date->month), date->year);
	printf("\n");

	Task* this_task = *tasks;
	int size = get_size(date, tasks);

	selected += move_task;

	if (selected < 0) selected = size;
	else if (selected > size) selected = 0;

	int count = 0;
	while (this_task && this_task->next) {
		if (this_task->date.day == date->day && this_task->date.month == date->month && this_task->date.year == date->year) {
			if (count == selected) {
				printf("\t[x]");
				selected_id = this_task->id;
			}
			//else if (check duration) printf("\t[-]");
			else printf("\t[ ]");
			printf(" %s\n", this_task->label);
			count++;
		}
		this_task = this_task->next;
	}

	if (this_task && this_task->date.day == date->day && this_task->date.month == date->month && this_task->date.year == date->year) {
		if (count == selected) {
			printf("\t[x]");
			selected_id = this_task->id;
		}
		//else if (check duration) printf("\t[-]");
		else printf("\t[ ]");
		printf(" %s\n", this_task->label);
		count++;
	}
	render_options(day);
}
void render_week(Date* date, Task** tasks, int move_task)
{
	// Clear previous render
	system("cls");

	// Redner header
	render_header(date);
	int daysInWeek[7];
	get_days_in_week(date, daysInWeek);
	for (int i = 0; i < 7; i++) {
		if (daysInWeek[i] == date->day) printf(WHITE_BACK "\t%d" RESET, daysInWeek[i]);
		else printf("\t%d", daysInWeek[i]);
	}

	render_options(week);
}

void render(Date* date, Task** tasks, enum typeRun format, int move_task) {
	if (format == day) render_day(date, tasks, move_task);
	else if (format == week) render_week(date, tasks, move_task);
	else if (format == month) render_month(date);
}