#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define N 2
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
//Структура с командами
struct _cmd {
  int id;
  char* cmd;
} cmd[] =
{
  {0,"exit"},
  {1,"addhead"},
  {2,"addtail"},
  {3,"delhead"},
  {4,"deltail"},
  {5,"dellist"},
  {6,"help"},
  {7,"count"},
  {8,"show"},
  {100,"delind"}
};

typedef struct list {
  int vert;
  int i;
  struct list *next;
  struct list *prev;
} tlist;

typedef struct vert {
  int vert;
  tlist* links;
  struct vert *next;
  struct vert *prev;
} tvert;


//Добавить узел в начало
tlist* addhead(tlist* head) {
  tlist* tmp = NULL;

  if ((tmp = malloc(sizeof(tlist))) == NULL) {
    perror("malloc");
    return head;
  }
  tmp->i = rand() % 1000;
  if (head == NULL)
  {
    tmp->next = NULL;
    tmp->prev = NULL;
    printf("### List was created ###\n");
    return tmp;
  }
  tmp->next = head;
  head->prev = tmp;
  printf("### Node was added to head ###\n");
  return tmp;
}
tlist* find(tvert *graph, int vert) { return 0; }
tvert* addvert(tvert* graph, int vert) {
  tvert* tmp, * cur = graph;
  if ((tmp = malloc(sizeof(tvert))) == NULL) {
    perror("malloc");
    return graph;
  }
  tmp->vert = vert;
  if (find(graph, vert) != NULL)
  {
    printf("Вершина существует");
    return 0;
  }
  if ((graph == NULL) || (vert < graph - vert)) {
    tmp->next = graph;
    tmp->links = NULL;
    return tmp;
  }
  while ((cur->next) || (cur->next->vert > vert))
    cur = cur->next;
  tmp->next = cur->next;
  cur->next = tmp;
  tmp->links = NULL;
  return graph;
}
// Добавляем узел в конец
tlist* addtail(tlist* head) {
  tlist* tmp, * cur = head;
  if ((tmp = malloc(sizeof(tlist))) == NULL) {
    perror("malloc");
    return head;
  }
  tmp->i = rand() % 1000;
  if (head == NULL)
  {
    //head = malloc(sizeof(tlist));

    tmp->next = NULL;
    tmp->prev = NULL;
    printf("List was created ###\n");
    return tmp;
  }

  while (cur->next)
    cur = cur->next;
  //tmp = malloc(sizeof(tlist));
  tmp->next = NULL;
  cur->next = tmp;
  tmp->prev = cur;
  printf("### Node was added to tail ###\n");
  return head;
}



//Удалить узел в началe
tlist* delhead(tlist* head) {
  tlist* tmp;

  if (head == NULL)
  {
    return NULL;
    printf("### List is empty ###\n");
  }
  else if (head->prev == NULL)
  {
    tmp = head->next;
    tmp->prev = NULL;
    free(head);
    printf("### Node was deleted from head ###\n");
    return tmp;
  }
  else
  {
    while (head->prev)
      head = head->prev;
    tmp = head->next;
    tmp->prev = NULL;
    free(head);
    return tmp;
  }
}

// Удаляем узел в конце
tlist* deltail(tlist* head) {
  tlist* tmp, * cur = head;
  if (cur == NULL)
  {
    printf("### List is empty ###");
    return cur;
  }
  if (cur->next == NULL) {
    free(cur);
    printf("### List was clear ###\n");
    return NULL;
  }
  tmp = cur;
  while (cur->next) {
    tmp = cur;
    cur = cur->next;
  }
  tmp->next = NULL;
  free(cur);
  printf("### Node was deleted from tail ###\n");
  return head;
}

tlist* dellist(tlist* head) {
  tlist* cur = head;

  while (cur != NULL) {
    tlist* tmp = cur;
    cur = cur->next;
    free(tmp);
  }
  printf("### List was clear ###\n");
  return NULL;
}

// Считаем длину списка
int listCount(tlist* head)
{
  int count = 0;
  if (head == NULL)
  {
    printf("### List is empty ###");
    return count;
  }
  while (head->next != NULL)
  {
    count++;
    head = head->next;
  }
  return ++count;
}

//вывод на экран
void showlist(tlist* head) {
  tlist* cur = head;
  int count = 0;
  while (cur != NULL) {
    printf("node[%d] is %9d %18p %18p %18p\n", count, cur->i, cur, cur->next, cur->prev);
    cur = cur->next;
    count++;
  }
}

// Удаляем узел по индексу
tlist* delind(tlist* head, int index) {
  tlist* tmp, * head1 = head;
  if (head == NULL)
  {
    printf("### List is empty ###\n");
    return head;
  }
  for (head = head1; head != NULL; head = head->next) {
    if (head->i == index) {
      if (head->prev == NULL) {
        head1 = delhead(head1);
        printf("### Node was deleted from index %d (head)###\n", index);
        return head1;
      }
      else if (head->next == NULL) {
        head1 = deltail(head1);
        printf("### Node was deleted from index %d (tail)###\n", index);
        return head1;
      }
      else {
        tmp = head;
        head->prev->next = head->next;
        head->next->prev = head->prev;
        free(tmp);
        printf("### Node was deleted from index %d ###\n", index);
        return head1;
      }
    }
  }
  printf("### Error 404 index %d not found ###\n", index);
  return head1;
}


//Перевод команды в число
int caseof(char* s, struct _cmd* cmd, int a) {
  int i, c = -1;

  for (i = 0; i < a; i++, cmd++)
  {
    if (strcmp(s, cmd->cmd) == 0)
    {
      c = cmd->id;

      return c;
    }
  }
  return -1;
}


int main(void) {
  char s[512];
  int c = -1;
  int a = ((sizeof(cmd)) / (sizeof(struct _cmd)));
  int i, ind;
  tlist* head = NULL;
  tlist* graph = NULL;
  while (1)
  {
    printf(" ~ ");
    scanf("%s", s);
//    scanf("%d", ind);
    switch (caseof(s, cmd, a))
    {
    case 0: return 1;//exit
    case 1: head = addhead(head); printf("### List has a %d nodes ###\n", listCount(head)); break; //addhead
    case 2: head = addtail(head); printf("### List has a %d nodes ###\n", listCount(head)); break; //addtail
    case 3: head = delhead(head); printf("### List has a %d nodes ###\n", listCount(head)); break; //delhead
    case 4: head = deltail(head); printf("### List has a %d nodes ###\n", listCount(head)); break; //deltail
    case 5: head = dellist(head); printf("### List has a %d nodes ###\n", listCount(head)); break;
    case 6: printf("addtail\naddhead\ndelhead\ndeltail\ndellist\ncount\nshow\n"); break; //help
    case 7: printf("### List has a %d nodes ###\n", listCount(head)); break; //count
    case 8: showlist(head); break; // show
    case 100: showlist(head); printf("Input index, which need to delete: "); scanf("%d", &i); head = delind(head, i);
      printf("### List has a %d nodes ###\n", listCount(head)); break;
    case '\n':printf("\n"); break;
    case '\t':printf("Tab\n"); break;
    default: printf("\n"); break;
    }
    c = -1;
  }
}