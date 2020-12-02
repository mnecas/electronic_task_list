#include "common.h"

Task* get_Task_p(Task** tasks) {
	Task* this_task = *tasks;
	if (selected_id == -1) return NULL;
	while (this_task && this_task->next) {
		if (selected_id == this_task->id) return this_task;
		this_task = this_task->next;
	}
	return this_task;
}

int get_max_id(Task** tasks) {
	Task* this_task = *tasks;
	while (this_task && this_task->next) {
		this_task = this_task->next;
	}
	if (this_task) return this_task->id;
	else return 0;
}

void on_add(Date date, Task** tasks) {

	Task* this_task = get_Task_p(tasks);
	system("cls");
	int time, duration, priority;
	char label[STR_SIZE];
	printf("Time\n");
	scanf_s("%d", &time);
	printf("Duration\n");
	scanf_s("%d", &duration);
	printf("Priority\n");
	scanf_s("%d", &priority);
	printf("Label\n");
	scanf_s("%s", label, STR_SIZE);
	add_task(get_max_id(tasks) + 1, time, duration, 0, priority, label, date, tasks);
}

void on_copy(Date date, Task** tasks) {
	Task* this_task = get_Task_p(tasks);
	if (this_task!=NULL){
		system("cls");
		Date new_date;
		printf("Day\n");
		scanf_s("%d", &new_date.day);
		printf("Month\n");
		scanf_s("%d", &new_date.month);
		printf("Year\n");
		scanf_s("%d", &new_date.year);
		add_task(get_max_id(tasks) + 1, this_task->time, this_task->duration, this_task->finished, this_task->priority, this_task->label, new_date, tasks);
	}
	
}

void on_edit(Date date, Task** tasks) {
	Task* this_task = get_Task_p(tasks);
	if (this_task != NULL) {
		system("cls");
		int option = 0;
		int ch;
		char* options[8] = { "day","month","year","time", "duration", "priority", "finished", "label" };
		printf("\tOptions to edit: \n");
		for (int i = 0; i < 8; i++) {
			if (i == option)printf("\t[x] - %s\n", options[i]);
			else printf("\t[ ] - %s\n", options[i]);
		}

		while ((ch = _getch()) != 27) {
			system("cls");
			if (ch == 0 || ch == 224)
			{
				int arrow = _getch();
				switch (arrow)
				{
				case 72:
					// Arrow up
					if (option <= 0) option = 7;
					else option--;
					break;
				case 80:
					// Arrow down
					if (option >= 7) option = 0;
					else option++;
					break;
				}
			}
			else {
				switch (option) {
				case 0:
					printf("Day (%d)\n", this_task->date.day);
					scanf_s("%d", &this_task->date.day);
					break;
				case 1:
					printf("Month (%d)\n", this_task->date.month);
					scanf_s("%d", &this_task->date.month);
					break;
				case 2:
					printf("Year (%d)\n", this_task->date.year);
					scanf_s("%d", &this_task->date.year);
					break;
				case 3:
					printf("Time (%d)\n", this_task->time);
					scanf_s("%d", &this_task->time);
					break;
				case 4:
					printf("Duration (%d)\n", this_task->duration);
					scanf_s("%d", &this_task->duration);
					break;
				case 5:
					printf("Priority (%d) [0-normal, 1-minimal, 2-maximum]\n", this_task->priority);
					scanf_s("%d", &this_task->priority);
					break;
				case 6:
					printf("Finished (%d) [0-no, 1-yes]\n", this_task->finished);
					scanf_s("%d", &this_task->finished);
					break;
				case 7:
					printf("Label (%s)\n", this_task->label);
					scanf_s("%s", this_task->label, STR_SIZE);
					break;
				}
				system("cls");
				return;
			}
			printf("\tOptions to edit: \n");
			for (int i = 0; i < 8; i++) {
				if (i == option)printf("\t[x] - %s\n", options[i]);
				else printf("\t[ ] - %s\n", options[i]);
			}
		}
	}
}

void on_remove(Date date, Task** tasks) {
	Task* this_task = get_Task_p(tasks);
	if (this_task != NULL) {
		del_task(this_task->id, tasks);
	}
}

void run(Date* date, Task** tasks, enum runType format) {
	render(date, tasks, format, 0);
	int ch;
	int move_task;
	while ((ch = _getch()) != 27)
	{
		move_task = 0;
		if (ch == 0 || ch == 224)
		{
			int arrow = _getch();
			switch (arrow)
			{
			case 72:
				// Arrow up
				if (format == month) update_date(date, -7);
				else if (format == week) update_date(date, -1);
				move_task = -1;
				break;
			case 75:
				// Arrow left
				if (format != week) update_date(date, -1);
				else move_task = -1;
				break;
			case 80:
				// Arrow down
				if (format == month) update_date(date, 7);
				else if (format == week) update_date(date, 1);
				move_task = 1;
				break;
			case 77:
				// Arrow right
				if (format != week) update_date(date, 1);
				else move_task = 1;
				break;
			}
		}
		else if ((char)ch == 'd') format = day;
		else if ((char)ch == 'w') format = week;
		else if ((char)ch == 'm') format = month;
		else if ((char)ch == 'a') on_add(*date, tasks);
		else if ((char)ch == 'c' && format == day) on_copy(*date, tasks);
		else if ((char)ch == 'e' && format == day) on_edit(*date, tasks);
		else if ((char)ch == 'r' && format == day) on_remove(*date, tasks);
		render(date, tasks, format, move_task);
	}
}