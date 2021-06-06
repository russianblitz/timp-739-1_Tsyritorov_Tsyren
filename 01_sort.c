#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printFile(int *arr, int size, char *fileName)
{
  FILE *fout; 
  fout = fopen(fileName, "a+");
  for (int i = 0; i < size; ++i)
    fprintf(fout, "%d ", arr[i]);
  fprintf(fout, "\n");
  fclose(fout);
}

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

int main()
{
  int *arr = NULL;
  int *arr2 = NULL;
  int size;
  scanf("%d", &size);
  arr = (int *)realloc(arr, size * sizeof(int));
  arr2 = (int *)realloc(arr, size * sizeof(int));
  for (int i = 0; i < size; i++)
  {
    scanf("%d", &arr[i]);
    arr2[i] = arr[i];
  }
  quickSort(arr, 0, size - 1);
  heapSort(arr2, size);
  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}