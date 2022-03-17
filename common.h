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

#define clear() printf("\033[H\033[J")

typedef struct tm Date;

typedef struct {
	int hour;
	int min;
}Time;

typedef enum runType { day, week, month } RunType;
typedef enum priority { normal, minimal, maximal } Priority;

typedef struct task
{
	Date date;
	int id;
	Time duration;
	Priority priority;
	char label[32];
	int finished;
	struct task* next;

} Task;

void render(Date* date, Task** tasks, RunType format, int move_task);
void add_task(int id, Time duration, int finished, int priority, char* label, Date date, Task** task);
void del_task(int id, Task** task);
void run(Date* date, Task** tasks, RunType format);

void update_date(Date* date, int change);
const char* get_month_name(int month);
void print_task_label(Task task);

extern int selected;
extern int selected_id;
