#include "common.h"

Task *get_selected_task(Task **tasks)
{
	Task *this_task = *tasks;
	if (selected_id == -1)
		return NULL;
	while (this_task && this_task->next)
	{
		if (selected_id == this_task->id)
			return this_task;
		this_task = this_task->next;
	}
	return this_task;
}

int get_max_id(Task **tasks)
{
	Task *this_task = *tasks;
	int resp = 0;
	while (this_task)
	{
		if (this_task->id > resp)
			resp = this_task->id;
		this_task = this_task->next;
	}
	return resp;
}

void on_add(Date date, Task **tasks)
{
	clear();
	int priority;
	Time duration;
	char label[STR_SIZE];
	printf("Time in format hh:mm\n\r");
	scanf("%d:%d", &date.tm_hour, &date.tm_min);
	printf("Duration in format hh:mm\n\r");
	scanf("%d:%d", &duration.hour, &duration.min);
	printf("Priority [0-normal, 1-minimal, 2-maximum]\n\r");
	scanf("%d", &priority);
	printf("Label\n\r");
	scanf("%s", label, STR_SIZE);

	add_task(get_max_id(tasks) + 1, duration, 0, priority, label, date, tasks);
}

void on_copy(Date date, Task **tasks)
{
	Task *this_task = get_selected_task(tasks);
	if (this_task != NULL)
	{
		clear();
		Date new_date = this_task->date;
		printf("Day\n\r");
		scanf("%d", &new_date.tm_mday);
		printf("Month\n\r");
		scanf("%d", &new_date.tm_mon);
		printf("Year\n\r");
		scanf("%d", &new_date.tm_year);
		new_date.tm_mon--;
		new_date.tm_year -= 1900;

		add_task(get_max_id(tasks) + 1, this_task->duration, this_task->finished, this_task->priority, this_task->label, new_date, tasks);
	}
}

void on_edit(Date date, Task **tasks)
{
	Task *this_task = get_selected_task(tasks);
	if (this_task != NULL)
	{
		clear();
		int option = 0;
		int ch;
		char *options[8] = {"day", "month", "year", "time", "duration", "priority", "finished", "label"};
		printf("\tOptions to edit: \n\r");
		for (int i = 0; i < 8; i++)
		{
			if (i == option)
				printf("\t[x] - %s\n\r", options[i]);
			else
				printf("\t[ ] - %s\n\r", options[i]);
		}

		while ((ch = getchar()) != 27)
		{
			clear();
			if (ch == 0 || ch == 224)
			{
				int arrow = getchar();
				switch (arrow)
				{
				case 107:
					// Arrow up
					if (option <= 0)
						option = 7;
					else
						option--;
					break;
				case 106:
					// Arrow down
					if (option >= 7)
						option = 0;
					else
						option++;
					break;
				}
			}
			else
			{
				switch (option)
				{
				case 0:
					printf("Day (%d)\n\r", this_task->date.tm_mday);
					scanf("%d", &this_task->date.tm_mday);
					break;
				case 1:
					printf("Month (%d)\n\r", this_task->date.tm_mon + 1);
					scanf("%d", &this_task->date.tm_mon);
					this_task->date.tm_mon--;
					break;
				case 2:
					printf("Year (%d)\n\r", this_task->date.tm_year + 1900);
					scanf("%d", &this_task->date.tm_year);
					this_task->date.tm_year -= 1900;
					break;
				case 3:
					printf("Time (%02d:%02d) in format hh:mm\n\r", this_task->date.tm_hour, this_task->date.tm_min);
					scanf("%d:%d", &this_task->date.tm_hour, &this_task->date.tm_min);
					break;
				case 4:
					printf("Duration (%02d:%02d) in format hh:mm\n\r", this_task->duration.hour, this_task->duration.min);
					scanf("%d:%d", &this_task->duration.hour, &this_task->duration.min);
					break;
				case 5:
					printf("Priority (%d) [0-normal, 1-minimal, 2-maximum]\n\r", this_task->priority);
					scanf("%d", &this_task->priority);
					break;
				case 6:
					printf("Finished (%d) [0-no, 1-yes]\n\r", this_task->finished);
					scanf("%d", &this_task->finished);
					break;
				case 7:
					printf("Label (%s)\n\r", this_task->label);
					scanf("%s", this_task->label, STR_SIZE);
					break;
				}
				mktime(&this_task->date);
				clear();
				return;
			}
			printf("\tOptions to edit: \n\r");
			for (int i = 0; i < 8; i++)
			{
				if (i == option)
					printf("\t[x] - %s\n\r", options[i]);
				else
					printf("\t[ ] - %s\n\r", options[i]);
			}
		}
	}
}

void on_remove(Date date, Task **tasks)
{
	Task *this_task = get_selected_task(tasks);
	if (this_task != NULL)
	{
		del_task(this_task->id, tasks);
	}
}

void run(Date *date, Task **tasks, RunType format)
{
	render(date, tasks, format, 0);
	int ch;
	int move_task;
	while ((ch = getchar()) != 113)
	{
		switch (ch)
		{
		case 107:
			// Arrow up
			if (format == month)
				update_date(date, -7);
			else if (format == week)
				update_date(date, -1);
			move_task = -1;
			break;
		case 104:
			// Arrow left
			if (format != week)
				update_date(date, -1);
			else
				move_task = 0;
			break;
		case 106:
			// Arrow down
			if (format == month)
				update_date(date, 7);
			else if (format == week)
				update_date(date, 1);
			move_task = 1;
			break;
		case 108:
			// Arrow right
			if (format != week)
				update_date(date, 1);
			else
				move_task = 0;
			break;
		}

		if ((char)ch == 'd')
			format = day;
		else if ((char)ch == 'w')
			format = week;
		else if ((char)ch == 'm')
			format = month;
		else if ((char)ch == 'a')
			on_add(*date, tasks);
		else if ((char)ch == 'c' && format == day)
			on_copy(*date, tasks);
		else if ((char)ch == 'e' && format == day)
			on_edit(*date, tasks);
		else if ((char)ch == 'r' && format == day)
			on_remove(*date, tasks);
		render(date, tasks, format, move_task);
	}
}