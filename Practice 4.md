# Задачи

Необходимо реализовать функции для работы с двусвязным списком:

    // инициализация пустого списка
    void init(list *l);
    
    // удалить все элементы из списка
    void clean(list *l);
    
    // проверка на пустоту списка
    bool is_empty(list *l);
    
    // поиск элемента по значению. вернуть NULL если элемент не найден
    node *find(list *l, int value);
    
    // вставка значения в конец списка, вернуть 0 если успешно
    int push_back(list *l, int value);
    
    // вставка значения в начало списка, вернуть 0 если успешно
    int push_front(list *l, int value);
    
    // вставка значения после указанного узла, вернуть 0 если успешно
    int insert_after(list *l, node *n, int value);
    
    // вставка значения перед указанным узлом, вернуть 0 если успешно
    int insert_before(list *l, node *n, int value);
    
    // удалить первый элемент из списка с указанным значением, 
    // вернуть 0 если успешно
    int remove_first(list *l, int value);
    
    // удалить последний элемент из списка с указанным значением, 
    // вернуть 0 если успешно
    int remove_last(list *l, int value);
    
    // вывести все значения из списка в прямом порядке через пробел,
    // после окончания вывода перейти на новую строку
    void print(list *l);
    
    // вывести все значения из списка в обратном порядке через пробел,
    // после окончания вывода перейти на новую строку
    void print_invers(list *l);

Используя функции реализовать программу, которая:

1. считывает количество элементов n, 0 < n <= 2147483647;
2. создает пустой список, считывает n элементов a, |a| <= 2147483647 и заносит их в список;
3. выводит содержимое списка, используя функцию print;
4. считывает k1, k2, k3 (|k| <= 2147483647) и выводит "1", если в списке существует элемент с таким значением и "0" если нет (выводить через пробел, например "1 0 1");
5. считывает m, |m| <= 2147483647 и вставляет его в конец списка;
6. выводит содержимое списка, используя функцию print_invers;
7. считывает t, |t| <= 2147483647 и вставляет его в начало списка;
8. выводит содержимое списка, используя функцию print;
9. считывает j и x (0 < j <= 2147483647, |x| <= 2147483647) и вставляет значение x после j-ого элемента списка;
10. выводит содержимое списка, используя функцию print_invers;
11. считывает u и y (0 < u <= 2147483647, |y| <= 2147483647) и вставляет значение y перед u-ым элементом списка;
12. выводит содержимое списка, используя функцию print;
13. считывает z, |z| <= 2147483647 и удаляет первый элемент (при его наличии), хранящий значение z из списка;
14. выводит содержимое списка, используя функцию print_invers;
15. считывает r, |r| <= 2147483647 и удаляет последний элемент (при его наличии), хранящий значение r из списка;
16. выводит содержимое списка, используя функцию print;
17. очищает список.

# Ход работы

Из методического пособия были взяты следующие структуры списка и узла:

    typedef struct node 
    {
    	int value;          // значение, которое хранит узел 
    	struct node *next;  // ссылка на следующий элемент списка
    	struct node *prev;  // ссылка на предыдущий элемент списка
    } node;
    
    typedef struct list 
    {
    	struct node *head;  // начало списка
    	struct node *tail;  // конец списка
    } list;

Инициализация пустого списка представлена на языке С следующим образом:

    // инициализация пустого списка
    void init(list *l)
    {
        l->head = NULL; //начало списка пусто
        l->tail = NULL; //конец списка пуст
    }

Для очистки списка, необходимо удалить все элементы из списка, для чего и нужна следующая функция:

    // удалить все элементы из списка
    void clean(list *l)
    { 
        node *temp = l->tail; //выбираем конец списка
        if (temp == NULL) //если список пуст, то он уже очищен
            return;
        while (temp->prev != NULL) //пока в списке temp не единственный элемент
        {
            temp = temp->prev; //переходим к предыдущему элементу
            free(temp->next); //очищаем тот, на котором только что были
        }
        free(temp); //очищаем память от последнего элемент
        l->head = NULL; //указываем, что первого элемента нет
        l->tail = NULL; //указываем, что последнего элемента нет
    }

В самом начале проверяется, если список пуст, то в очистке список не нуждается, иначе алгоритм продолжается. Цикл будет продолжаться, пока не останется единственный элемент - текущий. После цикла последний элемент тоже очищается, а конец и начало списка указываются пустыми.
Чтобы вставить значение в конец списка, необходима следующая функция:

    // вставка значения в конец списка, вернуть 0 если успешно
    int push_back(list *l, int value)
    {
        node *temp = l->tail; //запоминаем конец списка
        l->tail = malloc(sizeof(node)); //концу списка выделяем новую память
        if (temp == NULL) //если список был пуст
        {
            l->head = l->tail; //начало и конец списка - один и тот же элемент
            l->tail->next = NULL; //следующего элемента не существует
            l->tail->prev = NULL; //предыдущего тоже
        }
        else //иначе
        {
            temp->next = l->tail; //следующий элемент от бывшего конца - это новый
            l->tail->prev = temp; //указываем новому концу на старый
        }
        l->tail->value = value; //присваиваем новому элементу значение
        return 0; //успешно
    }

Запоминается конец списка, а к указателю конца присваивается адрес новой ячейки памяти. Дальнейшие действия разделены на две части: если список был пуст, то это учитывается, иначе указатель следующего элемента указывает на новый, а у нового указатель предыдущего на прошлый конец списка. Но в обоих случаях необходимо ячейке присвоить значение.
С функцией вставки в начало списка происходят аналогичные действия:

    // вставка значения в начало списка, вернуть 0 если успешно
    int push_front(list *l, int value)
    {
        node *temp = l->head; //запоминаем начало списка
        l->head = malloc(sizeof(node)); //началу выделяем новую память
        if (temp == NULL) //если список был пуст
        {
            l->tail = l->head; //начало и конец списка - один и тот же элемент
            l->head->prev = NULL; //предыдущего элемента не существует
            l->head->next = NULL; //следующего тоже
        }
        else //иначе
        {
            temp->prev = l->head; //предыдущий элемент от бывшего начала - это новое
            l->head->next = temp; //указываем новому начало на старый
        }
        l->head->value = value; //присваиваем новому элементу значение
        return 0; //успешно
    }

Далее необходимо реализовать функция вывода значений:

    // вывести все значения из списка в прямом порядке через пробел
    void print(list *l)
    {
        node *temp = l->head; //запоминаем начало списка
        while (temp != NULL) //пока не дойдем до несуществующего элемента
        {
            printf("%d ", temp->value); //печатаем значение данного элемента
            temp = temp->next; //переходим к следующему элементу в списке
        }
        printf("\n"); //переходим на новую строку в консоли
    }                   

Начиная с начала списка, продвигаемся к следующим элементам и выводим значения элементом, через которые проходим. Вывод в обратном порядке действует аналогичным образом, но начинает с конца и переходит к предыдущим элементам:

    // вывести все значения из списка в обратном порядке через пробел
    void print_invers(list *l)
    {
        node *temp = l->tail; //запоминаем конец списка
        while (temp != NULL) //пока текущий элемент не является несуществующим
        {
            printf("%d ", temp->value); //выводим значение текущего элемента
            temp = temp->prev; //переходим к предыдущему элементу в списке
        }
        printf("\n"); //переходим на новую строку в консоли
    }

Для поиска элемента в списке необходима следующая реализованная функция:

    // поиск элемента по значению с начала. вернуть NULL если элемент не найден
    node *find(list *l, int value) 
    {
        node *temp = l->head; //запоминаем начало списка
        while (temp != NULL && temp->value != value) //пока не дошли до несуществующего элемента и пока не нашли нужный
        {
            temp = temp->next; //переходим к следующему
        }
        return temp; //возвращаем либо элемент с нужным значение, либо NULL
    }

В данной функции необходимо перемещаться к следующему элементу, пока не будет достигнут элемент с нужным значением, либо пустой элемент (со значением NULL), который и будет вернут по окончанию.
Поиск с конца списка действует похожим образом:

    // поиск элемента по значению с конца списка
    node *find_invers(list *l, int value)
    {
        node *temp = l->tail; //запоминаем начало списка
        while (temp != NULL && temp->value != value) //пока не дошли до несуществующего элемента и пока не нашли нужный
        {
            temp = temp->prev; //переходим к предыдущему
        }
        return temp; //возвращаем либо элемент с нужным значение, либо NULL
    }

Вставить значение после определенного значения необходимо сначала выделить память для нового элемента, присвоить ему все возможные значения (значение элемента, указатели на предыдущий и следующий элементы), а также обновить указатели для следующих и предыдущих элементов:

    // вставка значения после указанного узла, вернуть 0 если успешно
    int insert_after(list *l, node *n, int value)
    {
        node *temp = NULL; //инициализация нового элемента
        temp = malloc(sizeof(node)); //выделяем память новому элементу
        temp->value = value; //присваиваем значение
        temp->next = n->next; //указываем на следующий элемент для нового
        temp->prev = n; //указываем на предыдущий для нового
        n->next = temp; //новый элемент является следующим, после которого вставляется
        if (temp->next == NULL) //если новый элемент теперь конец списка
        {
            l->tail = temp; //сообщаем об этом списку
        } 
        else //иначе
        {
            temp->next->prev = temp; //указываем следующему элементу, что предыдущий у него изменился
        }
        return 0; //успешно
    }

В данной функции было создано условие, которое проверяет, был ли последним элемент, после которого вставляется значение, ведь в этом случае не нужно будет обновлять указатель у следующего элемента (так как его не существует), но придется обновить указатель списка.
Аналогичным образом действует и добавление элемента до определенного. Но в нем условие предполагает, что вставляемый элемент может стать новым началом списка:

    // вставка значения перед указанным узлом, вернуть 0 если успешно
    int insert_before(list *l, node *n, int value)
    {
        node *temp = NULL; //инициализация нового элемента
        temp = malloc(sizeof(node)); //выделяем память новому элементу
        temp->value = value; //присваиваем значение
        temp->prev = n->prev; //указываем на предыдущий элемент для нового
        temp->next = n; //указываем на следующий для нового
        n->prev = temp; //новый элемент является предыдущим, до которого вставляется
        if (temp->prev == NULL) //если новый элемент теперь конец списка
        {
            l->head = temp; //сообщаем об этом списку
        } 
        else //иначе
        {
            temp->prev->next = temp; //указываем предыдущему элементу, что следующий у него изменился
        }
        return 0; //успешно
    }

Также в данной работе требуется удалить элемент из списка по значению (первый с начала и первый с конца). Для удаления первого нужного элемента с начала списка была реализована следующая функция:

    // удалить первый элемент из списка с указанным значением, вернуть 0 если успешно
    int remove_first(list *l, int value)
    {
        if (l->head == NULL) //если список пуст
            return 1; //неудачно
        node *removing = find(l, value); //находим элемент, который будет удален
        if (removing == NULL) //если элемента с таким значением не существует
            return 1; //неудачно
        if (l->head == removing) //если удаляемый элемент является началом
        {
            l->head = l->head->next; //обновляем начало списка
            l->head->prev = NULL; //указываем новому началу списку, что предыдущего элемента нет
        } 
        else if (l->tail == removing) //иначе если удаляемый элемент является концом
        {
            l->tail = l->tail->prev; //обновляем конец списка
            l->tail->next = NULL; //указываем новому концу списка, что следующего элемента нет
        } 
        else //иначе элемент находится где-то в середине списка
        {
            node *temp = removing->prev; //запоминаем предыдущий элемент
            temp->next = removing->next; //у него изменяем следующий
            removing->next->prev = temp; //у следующего изменяем предыдущий
        }
        free(removing); //удаляем из памяти
        return 0; //успешно
    }

В первую очередь проверяется две ситуации: список пустой или в списке нет нужного элемента. После них стоит проверить будет ли удаляемый элемент концом списка или началом списка. В этих случаях нужно обновить данные самого списка, а также указатель ближайшего к удаляемому элемента. Если элемент находится где-то в середине списка, то требуется работать только с указателями элементов: у предыдущего обновить следующий, а у следующего - предыдущий. В конце функции память освобождается от удаляемого элемента.
Чтобы удалить последний элемент с нужным значением, необходимо провести такие же действия:

    // удалить последний элемент из списка с указанным значением, вернуть 0 если успешно
    int remove_last(list *l, int value)
    {
        if (l->tail == NULL) //если список пуст
            return 1; //неудачно
        node *removing = find_invers(l, value); //находим элемент, который будет удален
        if (removing == NULL) //если элемента с таким хначением не существует
            return 1; //неудачно
        if (l->tail == removing) //если удаляемый элемент является концом
        {
            l->tail = l->tail->prev; //обновляем конец списка
            l->tail->next = NULL; //указываем новому концу списка, что следующего элемента нет
        } 
        else if (l->head == removing) //иначе если удаляемый элемент является началом
        {
            l->head = l->head->next; //обновляем начало списка
            l->head->prev = NULL; //указываем новому началу списку, что предыдущего элемента нет
        } 
        else //иначе элемент находится где-то в середине списка
        {
            node *temp = removing->next; //запоминаем следующий элемент
            temp->prev = removing->prev; //у него изменяем следующий
            removing->prev->next = temp; //у следующего изменяем предыдущий
        }
        free(removing); //удаляем из памяти
        return 0; //успешно
    }

Функция main представляет собой следующий код:

    int main() 
    {
        //1
        int n; 
        scanf("%d", &n); //ввод количества элементов
        //2
        list *l = NULL; 
        l = malloc(sizeof(list)); //выделение памяти
        init(l); //инициализация
        int i, a;
        for (i = 0; i < n; i++) 
        {
            scanf("%d", &a); //ввод элемента
            push_back(l, a); //добавление элемента в список
        }
        //3
        print(l); //прямой вывод списка
        //4
        int k1, k2, k3; //элементы, которые будут проверяться на наличие в списке
        scanf("%d %d %d", &k1, &k2, &k3);
        k1 = (find(l, k1) != NULL)? 1 : 0; //при нахождении k1 в списке значение будет 1, иначе 0
        k2 = (find(l, k2) != NULL)? 1 : 0;
        k3 = (find(l, k3) != NULL)? 1 : 0;
        printf("%d %d %d\n", k1, k2, k3); //вывод этих значений
        //5
        int m; 
        scanf("%d", &m); //ввод числа, которое будет добавлено в конец списка
        push_back(l, m); //добавление числа в конец списка
        //6
        print_invers(l); //обратный вывод списка 
        //7
        int t;
        scanf("%d", &t); //ввод числа, которое будет добавлено в начало списка
        push_front(l, t); //добавление числа в начало списка
        //8
        print(l); //прямой вывод списка
        //9
        int j, x; 
        scanf("%d %d", &j, &x); //вставить x элемент после j-го
        node *temp = l->head; //запоминаем первый элемент
        for (i = 1; i < j; i++) //доходим до j-го
            temp = temp->next;
        insert_after(l, temp, x); //вставляем элемент со значением x после j-го
        //10
        print_invers(l); //обратный вывод списка
        //11
        int u, y;
        scanf("%d %d", &u, &y); //вставить y элемент после u-го
        temp = l->head; //запоминаем первый элемент
        for (i = 1; i < u; i++) //доходим до u-го
            temp = temp->next;
        insert_before(l, temp, y); //вставляем элемент со значением y после u-го
        //12
        print(l); //прямой вывод списка
        //13
        int z; 
        scanf("%d", &z); //ввод значения элемента, который будет удален с начала списка
        remove_first(l, z); //удаление первого элемента со значением z
        //14
        print_invers(l); //обратный вывод списка
        //15
        int r;
        scanf("%d", &r); //ввод значения элемента, который будет удален с конца списка
        remove_last(l, r); //удаление первого элемента со значением r
        //16
        print(l); //прямой вывод списка
        //17
        clean(l); //очистка списка
        return 0;
    }

    
Результат работы программы с данными из примера показывает то, что и ожидалось (рисунок 1).

![result](https://gitlab.com/Russian_Blitz/practices/-/raw/master/pr4/pictures/result.png)

Рисунок 1 - Результат работы программы

Успешные результаты тестов pipeline представлены на рисунке 2.

![tests](https://gitlab.com/Russian_Blitz/practices/-/raw/master/pr4/pictures/tests.png)


Рисунок 2 - Пройденные тесты pipeline

# Заключение

В процессе данной работы были выполнены все заданные задачи, реализованы функции для двусвязных списках, создана программа, успешно прошедшая тесты pipeline. Были изучены основные действия с двухсвязными списками.
