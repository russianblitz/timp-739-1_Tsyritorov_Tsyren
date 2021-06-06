#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
   int value; // значение, которое хранит узел
   struct node *next; // ссылка на следующий элемент списка
   } node;

typedef struct list {
   struct node *head; // начало списка
   } list;

// инициализация пустого списка
void init(list *l) {
   l -> head = malloc(sizeof(node));
   l -> head = NULL;
   return;
   }

// удалить все элементы из списка
void clean(list *l) {
   if ( l -> head == NULL)
   return;

   node *current = l->head;
   node *temp;

   while (current) {
   temp = current->next;
   free(current);
   current = temp;
   }

   l->head = NULL;
   return;
 }

// проверка на пустоту списка
bool is_empty(list *l) {
   if(l -> head == NULL)
   return true;
   else
   return false;
   }

   // поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, int key) {
   node *current = l -> head;
   if(l -> head == NULL)
   return NULL;

   while(current -> value != key) {
   current = current -> next;

   if(current == NULL)
   return NULL;
   }

   return current;
   }

//поиск последнего эл-та
node* find_last(list *l) {

   if(l -> head == NULL)
   return NULL;

   node *current = l -> head;

   while(current -> next != NULL) {
   current = current -> next;
   }
   return current;
   }

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int key) {
        if (is_empty(l) == false) {
        node *last = find_last(l);
        node *current = malloc(sizeof(node));
        last -> next = current;
        current -> next = NULL;
        current -> value = key;
        }
        else {
        node *current = malloc(sizeof(node));
        current -> value = key;
        current -> next = NULL;
        l -> head = current;
        }
        return 0;
        }

 // вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int key) {
        node *current = malloc(sizeof(node));
        current -> value = key;
        current -> next = l -> head;
        l -> head = current;
        return 0;
        }

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int key) {
        if(n == NULL)
        return 1;

        node *new_node = malloc(sizeof(node));
        new_node -> value = key;
        new_node -> next = n -> next;
        n -> next = new_node;
        return 0;
        }

// удалить первый элемент из списка с указанным значением, вернуть 0 если успешно
int remove_node(list *l, int key) {
        node *current = l -> head;
        node *pre_node = NULL;

        if(l -> head == NULL)
        return 1;

        while(current -> value != key) {
        if(current -> next == NULL)
        return 1;
	else {
        pre_node = current;
        current = current -> next;
        }
        }
        if(current == l -> head) {
        l -> head = l -> head -> next;
        }
        else {
        pre_node -> next = current -> next;
        }
        free(current);
        return 0;
        }

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l) {
        node *current = l -> head;
        if (current == NULL)
        return;

        while(current != NULL) {
        printf("%d ", current-> value);
        current = current -> next;
        }
        printf("\n");
        return;
        }

node *index_finder(list *l, int index) {
        if(l -> head == NULL)
        return NULL;

        node *current = l -> head;
        int index_counter = 0;

        while(index_counter != index) {
        current = current -> next;

        if(current == NULL)
        return NULL;

        index_counter++;
        }
        return current;
        }

int main() {
        int n, m, t, j, x, z, a;
        (void) scanf("%d", &n);
        list *l_main;
        l_main = malloc(sizeof(list));
        init(l_main);

	/*заполнение списка*/
        for(int i = 1; i <= n; i++) {
        (void) scanf("%d", &a);
        push_back(l_main, a);
        }
        print(l_main);

	/*нахождение Ki*/
	int k;
	list* num = (list*)malloc(sizeof(list));
	for (int i = 0; i < 3; i++) {
	scanf("%d",&k);

	if (find(l_main, k)== NULL)
	push_back(num, 0);
	else
	push_back(num, 1);
	}
	print(num);

	/*вставка в конец*/
        (void)scanf("%d", &m);
        push_back(l_main, m);
        print(l_main);

	/*вставка в начало*/
        (void)scanf("%d", &t);
        push_front(l_main, t);
        print(l_main);

	/*вставка после*/
        (void) scanf("%d %d", &j, &x);
        node *find_node = index_finder(l_main, j - 1);
        insert_after(find_node, x);
        print(l_main);

	/*удаление первого хранящего z */
        (void) scanf("%d", &z);
        remove_node(l_main, z);
        print(l_main);

        clean(l_main);
        l_main -> head = NULL;
        return 0;
        }

