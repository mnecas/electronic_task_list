#include "common.h"

int selected = 0;
int selected_id = 0;
const char* week_day_names[7] = { "Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

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

void render_month(Date* date, Task** tasks)
{
	// Clear previous render
	system("cls");

	// Redner header
	printf("\t%d\t\t\t%s\n\t", date->tm_year+1900, get_month_name(date->tm_mon));
	for (int i = 0; i < 7; i++)printf("%s\t", week_day_names[i]);
	printf("\n\t");
	for (int i = 0; i < 52; i++)
		printf("-");
	printf("\n");

	// Copy date to tmp for render of the month
	Date tmp = *date;
	tmp.tm_mday = 1;
	mktime(&tmp);

	// Padding for first week
	for (int i = 0; i < tmp.tm_wday; i++) printf("\t");

	// Render month days
	do{
		// Selected date
		if (date->tm_mday == tmp.tm_mday) printf(WHITE_BACK "\t%d" RESET, tmp.tm_mday);
		else if (date_has_tasks(tmp, tasks)) printf(YELLOW "\t%d" RESET, tmp.tm_mday);
		else printf("\t%d", tmp.tm_mday);

		// New line for end of week
		if (tmp.tm_wday == 6) printf("\n");
		tmp.tm_mday++;
		mktime(&tmp);
	} while (tmp.tm_mday != 1);
	render_options(month);
}

int get_size(Date* date, Task** tasks) {
	// Returns size of the linked list
	Task* this_task = *tasks;

	int resp = 0;
	while (this_task) {
		if (this_task->date.tm_mday == date->tm_mday && this_task->date.tm_mon == date->tm_mon && this_task->date.tm_year == date->tm_year) {
			resp++;
		}
		this_task = this_task->next;
	}
	return resp;

}
Date get_end_time(Date start, Time duration) {
	// Get ending time from duration
	Date end_time = start;
	end_time.tm_min += duration.min;
	end_time.tm_hour += duration.hour;
	mktime(&end_time);
	return end_time;
}

void render_day(Date* date, Task** tasks, int move_task)
{
	system("cls");

	printf("\t%d. %s %d\n", date->tm_mday, get_month_name(date->tm_mon), date->tm_year+1900);
	printf("\n");

	Task* this_task = *tasks;

	// Select Task from list
	int size = get_size(date, tasks);
	selected += move_task;
	if (selected < 0) selected = size-1;
	else if (selected >= size) selected = 0;

	// Render tasks for that day
	int count = 0;
	while (this_task) {
		if (this_task->date.tm_mday == date->tm_mday && this_task->date.tm_mon == date->tm_mon && this_task->date.tm_year == date->tm_year) {
			Date end_time = get_end_time(this_task->date, this_task->duration);

			if (count == selected) {
				printf("\t[x]");
				selected_id = this_task->id;
			}
			else printf("\t[ ]");
			
			// Render Task
			printf(" (%02d:%02d-%02d:%02d) ", this_task->date.tm_hour, this_task->date.tm_min, end_time.tm_hour, end_time.tm_min);
			print_task_label(*this_task);
			printf("\n");
			count++;
		}
		this_task = this_task->next;
	}
	render_options(day);
}

void render_week(Date* date, Task** tasks, int move_task)
{
	// Clear previous render
	system("cls");


	// Copy date to tmp for render of the month
	Date tmp = *date;
	mktime(&tmp);

	// Go to Sunday
	while (tmp.tm_wday != 0) {
		tmp.tm_mday--;
		mktime(&tmp);
	}

	// List all days from Sunday to Saturday
	for (int i = 0; i < 7; i++) {
		if (tmp.tm_mday == date->tm_mday) printf("\t%s " WHITE_BACK "%d" RESET, week_day_names[i], tmp.tm_mday);
		else printf("\t%s %d", week_day_names[i], tmp.tm_mday);
		printf(" ");

		// Render tasks for that day
		Task* this_task = *tasks;
		while (this_task) {
			if (this_task->date.tm_mday == tmp.tm_mday && this_task->date.tm_mon == tmp.tm_mon) {
				print_task_label(*this_task);
				printf(" ");
			}
			this_task = this_task->next;
		}
		printf("\n");
		// Go to next day
		tmp.tm_mday++;
		mktime(&tmp);
	}
	render_options(week);
}

void render(Date* date, Task** tasks, enum typeRun format, int move_task) {
	if (format == day) render_day(date, tasks, move_task);
	else if (format == week) render_week(date, tasks, move_task);
	else if (format == month) render_month(date, tasks);
}