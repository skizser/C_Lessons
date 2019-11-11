#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define N 2

//Структура с командами
struct _cmd {
	int id;
	char *cmd;
}
 cmd[] = 
	{	
		{0,"exit"},
		{1,"addhead"},
		{2,"addtail"},
		{3,"delhead"},
		{4,"deltail"},
		{5,"dellist"},
		{6,"help"},
		{7,"count"},
		{8,"show"}
	};

typedef struct node {
  char first_name[10];
  char second_name[10];
  char phone_number[10]; 
  int i;
  struct node *next;
} tlist;

//Добавить узел в начало
tlist *addhead(tlist *head) {
	tlist *tmp = NULL;
	tmp = malloc(sizeof(tlist));
	if (head == NULL)
	{
		tmp -> next = NULL;
		return tmp;
	}
	tmp -> next = head;
	return tmp;
}

// Добавляем узел в конец
tlist *addtail(tlist *head) {
	tlist *tmp, *head1 = head;

		if ((tmp = malloc(sizeof(tlist))) == NULL){
			perror ("malloc");
			return head1;
		}
	if (head == NULL)
	{
		//head = malloc(sizeof(tlist));
		tmp -> next = NULL;
		return tmp;
	}

	while (head -> next)
		head = head -> next;
	//tmp = malloc(sizeof(tlist));
	tmp -> next = NULL;
	head -> next = tmp;
	return head1;
}



//Удалить узел в началe
tlist* delhead(tlist* head) {
  tlist* tmp;
  
  if (head == NULL)
  {
    return NULL;
  }
  tmp = head->next;
  free(head);
  return tmp;
}

// Удаляем узел в конце
tlist* deltail(tlist* head) {
  tlist* tmp, * head1 = head;
  if (head == NULL)
  {
    return head;
  }
  if (head->next == NULL){
        free(head);
        return NULL;
    }

  while (head->next) {
  	tmp = head;
    head = head->next;
  }
  tmp->next = NULL;
  free(head);
  return head1;
}

tlist *dellist(tlist *head) {
    tlist * current = head;

    while (current != NULL) {
    	tlist*temp = current;
        current = current->next;
        free(temp);
    }
    return NULL;
}

// Считаем длину списка
int listCount(tlist *head)
{
	int count=0;
	if (head == NULL)
		return count;
	while (head -> next != NULL)
	{
		count++;
		head = head -> next;
	}
	return ++count;
}

//вывод на экран
void showlist(tlist *head) { 
    tlist *current = head;
    int count = 0;
    while (current != NULL) {
        printf("node[%d] is %d\n", count, current->i);
        current = current->next;
        count++;
    }
}



//Перевод команды в число
int caseof(char *s, struct _cmd *cmd, int a){
	int i, c = -1;
	
	for (i = 0; i < a; i++,cmd++)
	{
			if (strcmp(s,cmd -> cmd) == 0) 
				{
					c = cmd -> id;
					 
					return c;
				}
	}
	return -1;
}


int main(void) {
	char s[512];
	int i, c = -1;
	int a = ((sizeof(cmd)) / (sizeof(struct _cmd)));
	tlist *head = NULL;
	while (1)
	{
		printf (" ~ ");
		scanf ("%s", s);
		switch (caseof(s, cmd, a))
		{
			case 0: return 1;//exit
			case 1: head = addhead(head); printf ("### Node was added to head ###\n### List has a %d nodes ###\n", listCount(head)); break; //addhead
			case 2: head = addtail(head); printf ("### Node was added to tail ###\n### List has a %d nodes ###\n", listCount(head)); break; //addtail
			case 3: head = delhead(head); printf ("### Node was deleted from head ###\n### List has a %d nodes ###\n", listCount(head)); break; //delhead
			case 4: head = deltail(head); printf ("### Node was deleted from tail ###\n### List has a %d nodes ###\n", listCount(head)); break; //deltail
			case 5: head = dellist(head); printf ("### List was clear ###\n"); dellist(head); break;
			case 6: printf ("addtail\naddhead\ndelhead\ndeltail\ndellist\ncount\nshow\n"); break; //help
			case 7: printf ("### List has a %d nodes ###\n",listCount(head)); break; //count
			case 8: showlist(head); break; // show
			case '\n':printf ("\n"); break;
			case '\t':printf ("Tab\n"); break;
			default: printf ("\n"); break;
		}
		c = -1;
	}
}

