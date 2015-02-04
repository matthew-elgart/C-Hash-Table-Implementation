#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct node {
	int grd1;
	int grd2;
	char name[256];
	int sid;
  	struct node *next;
}
node;

node *bucketlist[13] = {NULL};
node *conductor;

void insert(int id, int g1, int g2, char stu_name[256]) {
	int index;
	index = (id & 0x0000000f);

	if (index == 13) index = 10;
	if (index == 14) index = 11;
	if (index == 15) index = 12;
	
	if (bucketlist[index] == NULL) {
		node *new = malloc(sizeof(node));
		new->grd1 = g1;
		new->grd2 = g2;
		strcpy(new->name,stu_name);
		new->sid = id;
		
		bucketlist[index] = new;
		printf("Student ID added successfully\n");
	}
	
	else {
		conductor = bucketlist[index];
		if (conductor->sid == id) {
			printf("Error: student ID already exists\n");
			return;
		}
		while (conductor->next != NULL) {
			if (conductor->sid == id) {
				printf("Error: student ID already exists\n");
				return;
			}
			conductor = conductor->next;
		}
		node *new = malloc(sizeof(node));
		new->grd1 = g1;
		new->grd2 = g2;
		strcpy(new->name,stu_name);
		new->sid = id;
		conductor->next = new;
		printf("Student ID added successfully\n");
	}
}

void delete(int id) {
	int index;
	index = (id & 0x0000000f);

	if (index == 13) index = 10;
	if (index == 14) index = 11;
	if (index == 15) index = 12;
	
	if (bucketlist[index] == NULL) {
		printf("Error: specified student ID not found\n");
	}
	else {
		conductor = bucketlist[index];
		if (conductor->sid == id) {
			conductor = conductor->next;
			free(bucketlist[index]);
			bucketlist[index] = conductor;
			printf("Student removed from records\n");
			return;
		}
		while (conductor->next != NULL) {
			if (conductor->next->sid == id) {
				free(conductor->next);
				conductor->next = conductor->next->next;
				printf("Student removed from records\n");
				return;
			}
			conductor = conductor->next;
		}
		printf("Error: specified student ID not found\n");
	}
}

void lookup(int id) {
	int index;
	index = (id & 0x0000000f);

	if (index == 13) index = 10;
	if (index == 14) index = 11;
	if (index == 15) index = 12;
	
	if (bucketlist[index] == NULL) {
		printf("Error: specified student ID not found\n");
	}
	else {
		conductor = bucketlist[index];
		while (conductor != NULL) {
			if (conductor->sid == id) {
				printf("ID: %d. Name: %s. Grade 1: %d. Grade 2: %d\n",
					conductor->sid, conductor->name,
					conductor->grd1, conductor->grd2);
				return;
			}
			conductor = conductor->next;
		}
		printf("Error: specified student ID not found\n");
	}
}

void print() {
	int k;
	for (k = 0; k < 13; k++) {
		if (bucketlist[k] != NULL) {
			conductor = bucketlist[k];
			while (conductor != NULL) {
				printf("ID: %d. Name: %s. Grade 1: %d. Grade 2: %d\n",
					conductor->sid, conductor->name,
					conductor->grd1, conductor->grd2);
				conductor = conductor->next;
			}
		}
	}
}

void allstats() {
	int max1 = INT_MIN;
	char max1name[256];
	int min1 = INT_MAX;
	char min1name[256];
	int max2 = INT_MIN;
	char max2name[256];
	int min2 = INT_MAX;
	char min2name[256];
	int totalscore1 = 0;
	int totalscore2 = 0;
	int totalpeople = 0;
	
	int k;
	for (k = 0; k < 13; k++) {
		if (bucketlist[k] != NULL) {
			conductor = bucketlist[k];
			while (conductor != NULL) {
				totalscore1 += conductor->grd1;
				totalscore2 += conductor->grd2;
				totalpeople ++;
				if (conductor->grd1 > max1) {
					max1 = conductor->grd1;
					strcpy(max1name,conductor->name);
				}
				if (conductor->grd2 > max2) {
					max2 = conductor->grd2;
					strcpy(max2name,conductor->name);
				}
				if (conductor->grd1 < min1) {
					min1 = conductor->grd1;
					strcpy(min1name,conductor->name);
				}
				if (conductor->grd2 < min2) {
					min2 = conductor->grd2;
					strcpy(min2name,conductor->name);
				}
				conductor = conductor->next;
			}
		}
	}
	
	printf("Exam 1 minimum: %d. Student: %s.\n", min1, min1name);
	printf("Exam 1 maximum: %d. Student: %s.\n", max1, max1name);
	printf("Exam 1 average: %d\n\n", totalscore1/totalpeople);
	printf("Exam 2 minimum: %d. Student: %s.\n", min2, min2name);
	printf("Exam 2 maximum: %d. Student: %s.\n", max2, max2name);
	printf("Exam 2 average: %d\n", totalscore2/totalpeople);
}

void statistics(int id, char stu_name[256]) {
	int index;
	index = (id & 0x0000000f);

	if (index == 13) index = 10;
	if (index == 14) index = 11;
	if (index == 15) index = 12;
	
	if (bucketlist[index] == NULL) {
		printf("Error: specified student ID not found\n");
	}
	else {
		conductor = bucketlist[index];
		while (conductor != NULL) {
			if (conductor->sid == id) {
				printf("ID: %d. Name: %s. Average grade: %d\n",
					conductor->sid, conductor->name,
					(conductor->grd1 + conductor->grd2)/2);
				return;
			}
			conductor = conductor->next;
		}
		printf("Error: specified student ID not found\n");
	}
}

int main() {

  char stu_name[256];
  char command;
  int g1;
  int g2;
  int id;
  printf("Type a command followed by: Student ID, Grade 1, Grade 2, and Name\n");

  while (scanf("%s %d %d %d %s", &command, &id, &g1, &g2, &stu_name) != EOF) {
    if (command == 'i') {
      printf("Inserting student into records:\n");
      insert(id, g1, g2, stu_name);
    }
    if (command == 'd') {
      printf("Removing student from records:\n");
      delete(id);
      }
    if (command == 'l') {
      printf("Looking up student in records:\n");
      lookup(id);
    }
    if (command == 'p') {
      printf("Printing out all student records:\n");
      print();
    }
    if (command == 's') {
      if (strcmp(stu_name,"all")==0 && id == 0) {
        printf("Printing statistics for exams:\n");
	allstats();
      }
      else {
        printf("Printing student statistics:\n");
	statistics(id, stu_name);
      }
    }
  }

  return 0;	
}
