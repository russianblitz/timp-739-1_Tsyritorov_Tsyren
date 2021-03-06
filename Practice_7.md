# Задание:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Необходимо написать следующие программы для работы с деревом:
- программа, реализующая обыструю сортировку массива;
- программа, реализующая пирамидальную сортировку массива.

# Теоретическая часть

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Ниже в виде анимированного изображения приведен порядок сортировки массива при использовании "Бытрой сортировки".

![](https://gitlab.com/Russian_Blitz/practices/-/raw/master/pr7/screenshots/quicksort.gif)
> Рисунок 1 - Пример быстрой сортировки массива

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; То есть, изначально выбирается опорный элемент. Это может быть любой из элементов массива. Но по заданию был взят серединный элемент массива. Далее разбиение - перераспределение элементов в массиве таким образом, что элементы меньше опорного помещаются перед ним, а больше или равные после. Затем рекурсивно применялись первые два шага к двум подмассивам слева и справа от опорного элемента. Рекурсия не применяется к массиву, в котором только один элемент или отсутствуют элементы.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Ниже в виде анимированного изображения приведен порядок сортировки массива при использовании "Пирамидальной сортировки".

![](https://gitlab.com/Russian_Blitz/practices/-/raw/master/pr7/screenshots/heapsort.gif)
> Рисунок 2 - Пример пирамидальной сортировки массива

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; То есть, изначально происходит перемещение на самый правый элемент предпоследнего уровня и сравнение его с потомками. Если один из его потомков больше, то происходит замена его с потомком (т.е. на место выбранного ставится наибольшей из рассматриваемой тройки). Затем на этом же уровне рассматривается элемент левее и происходят действия аналогичные тем, которые проделывались ранее. Отсортировав таким образом данный уровень происходит перемещение на правый элемент уровня выше. Отличие в следующих действиях только в том, что происходит сравнение не только в тройке родитель-и-2-потомка, но и на уровень ниже, то есть элемент, на котором произошла остановка, будет заменен самым большим из его потомков. Аналогично с другими элементами данного уровня. И так далее до самого корневого элемента. Данные действия приведут к тому, что в корневом окажется наибольший элемент во всем дереве (массиве), который будет поменян с самым правым нижним элементом (ставим его туда, так как в отсортированном массиве место самого большого элемента самое последнее). Затем все действия, описанные выше, повторяются, только уже не будет учитываться самый последний элемент. Таким образом данное дерево (массив) будет отсортирован.

# Ход работы 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Ниже представлен код, реализующий быструю сортировку массива с последующим выводом всех его элементов.

```c
void quickSort(int *array, int left, int right)
{
  int i = left; //левая граница
  int j = right; //правая граница
  int privot = array[right + (left - right) / 2]; //установка центрального элемента как опорного
  do
  {
    while (array[i] < privot) //находим слева элемент не меньше центрального
      i++;
    while (array[j] > privot) //находим справа элемент не больше центрального
      j--;
    if (i <= j) //если левая не больше правой границы
    {
      if (array[i] > array[j]) //если левый элемент больше правого, то заменяем их
      {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
      i++; 
      if (j > 0)
        j--;
      printFile(array, sizeof(array), "quicksort.log"); // запись массива в лог
    }
  } while (i <= j); //пока левая граница не больше правой
  if (i < right) //если есть элементы для сортировки справа
    quickSort(array, i, right);
  if (j > left) //если есть элементы для сортировки слева
    quickSort(array, left, j);
}
```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; На рисунке 3 представлен результат выполнения программой данного метода.

![](https://gitlab.com/Russian_Blitz/practices/-/raw/master/pr7/Sort.png)
> Рисунок 3 -Результат быстрой сортировки

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Как видно из рисунка, массив отсортирован правильно, что говорит о корректной работе программы.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Ниже представлен код, реализующий пирамидальную сортировку массива с последующим выводом всех его элементов.

```c
void heapify(int a[], int top, int bottom, int n)
{
    int maxChild; // индекс максимального потомка
    int done = 0; // флаг того, что куча сформирована
    while ((top * 2 <= bottom) && (!done)) // Пока не дошли до последнего ряда
    {
        if (top * 2 == bottom)    // если мы в последнем ряду,
            maxChild = top * 2;    // запоминаем левый потомок
        else if (a[top * 2] > a[top * 2 + 1]) // иначе запоминаем больший потомок из двух
            maxChild = top * 2;
        else
            maxChild = top * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (a[top] < a[maxChild])
        {
            int temp = a[top]; // меняем их местами
            a[top] = a[maxChild];
            a[maxChild] = temp;
            top = maxChild;
        }
        else // иначе
            done = 1; // пирамида сформирована
    }
}

void heapSort(int *array, int size)
{
  for (int i = (size / 2); i >= 0; i--) // Формируем нижний ряд пирамиды
  {
    heapify(array, i, size - 1, size);
  }
  for (int i = size - 1; i >= 1; i--) // Просеиваем через пирамиду остальные элементы
  {
    int temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    printFile(array, size, "heapsort.log"); // запись массива в лог
    heapify(array, 0, i - 1, size);
  }
}
```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; На рисунке 4 представлен результат выполнения программой данного метода.

![](https://gitlab.com/Russian_Blitz/practices/-/raw/master/pr7/Sort.png)
> Рисунок 4 -Результат пирамидальной сортировки

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Как видно из рисунка, массив отсортирован правильно, что говорит о корректной работе программы.

# Заключение
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;В результате выполнения данной практической работы были написаны программы, реализующие быструю и пирамидальную сортировку массива.
