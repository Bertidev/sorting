#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct informacao 
{
    unsigned long int key;
    float num;
} info;

info * create_ord (unsigned long int size, int seed)
{
    info *v = (info*)malloc(size* sizeof (info));
    unsigned long int i = 0, growth = 0;
    srand(seed);

    for(i=0; i<size; i++)
    {
        v[i].num = rand();
        growth += (rand()%10 +1);
        v[i].key = growth;
    }
    return v;
}

info* create_vet (unsigned long int size, int seed)
{
    info* v = (info*)malloc(size* sizeof (info));
    unsigned long int i = 0;
    srand(seed);

    for(i=0; i<size; i++)
    {
        v[i].num = rand();
        v[i].key= rand()*rand();
    }
    return v;
}

void InsertionSort(info* array, long int size)
{
    long int i, j;
    unsigned long int element;

    for (i = 1; i < size; i++)
    {
        element = array[i].key;
        j = i - 1;
        while (j >= 0 && array[j].key < element) 
        {
            array[j + 1].key = array[j].key;
            j = j - 1;
        }
        array[j + 1].key = element;
    }
}

void swap(info* array, long int i, long int j) 
{ 
    unsigned long int element = array[i].key; 
    array[i].key = array[j].key; 
    array[j].key = element; 
} 
  
void BubbleSort(info* array, long int size) 
{ 
    long int i, j; 
    for (i = 0; i < size - 1; i++) 
    {
        for (j = 0; j < size - i - 1; j++)
        { 
            if (array[j].key < array[j + 1].key)
            { 
                swap(array, j, j + 1);
            }
        }
    } 
}

void ShellSort(info* array, long int size) 
{
    long int interval, i, j;
    unsigned long int element;
    for (interval = size / 2; interval > 0; interval /= 2) 
    {
        for (i = interval; i < size; i += 1) 
        {
            element = array[i].key;
            for (j = i; j >= interval && array[j - interval].key < element; j -= interval) 
            {
                array[j].key = array[j - interval].key;
            }
            array[j].key = element;
        }
    }
}

unsigned long int GetMax(info* array, long int size) 
{
    unsigned long int max = array[0].key;

    for (int i = 1; i < size; i++)
    {
        if (array[i].key > max)
        {
            max = array[i].key;
        }
    }
    return max;
}

void CountingSort(info* array, long int size, long int place, info* output) 
{
    unsigned long int max = array[0].key % 10;
    unsigned long int i;

    for (i = 1; i < (unsigned long int)size; i++) 
    {
        if ((array[i].key % 10) > max)
        {
            max = array[i].key % 10;
        }
    }

    unsigned long int* count = (unsigned long int*)malloc((max + 1) * sizeof(unsigned long int));

    if (count == NULL)
    {
        // Tratar erro de alocação de memória, se necessário
        return;
    }

    for (i = 0; i <= max; ++i)
    {
        count[i] = 0;
    }

    for (i = 0; i < (unsigned long int)size; i++)
    {
        count[(array[i].key / place) % 10]++;
    }    

    for (i = max; i > 0; i--)
    {
        count[i - 1] += count[i];
    }
  
    for (i = size - 1; (long int)i >= 0; i--) 
    {
        output[count[(array[i].key / place) % 10] - 1] = array[i];
        count[(array[i].key / place) % 10]--;
    }

    // Copia os elementos ordenados de volta para o array original
    for (int i = 0; i < size; i++)
    {
        array[i] = output[i];
    }

    // Libera a memória alocada para o vetor count
    free(count);
}


void RadixSort(info* array, long int size) 
{
    unsigned long int max = GetMax(array, size);

    // Aloca memória para o vetor de saída
    info* output = (info*)malloc(size * sizeof(info));

    if (output == NULL) 
    {
        // Tratar erro de alocação de memória, se necessário
        return;
    }

    long int i;
    for (i = 1; max/i > 0; i *= 10)
    {
        CountingSort(array, size, i, output);
    }

    // Copia os elementos ordenados de volta para o array original
    for (int i = 0; i < size; i++)
    {
        array[i] = output[i];
    }

    // Libera a memória alocada para o vetor de saída
    free(output);
}


void merge(info* array, info* c, long int i, long int m, long int f)
{
    long int z, iv=i, ic=m+1;
    for(z=i; z<= f; z++)
    {
        c[z].key = array[z].key;
    }
    z = i;
    while(iv<=m && ic<= f)
    {
        if(c[iv].key >= c[ic].key) 
        {
            array[z++].key = c[iv++].key;
        }
        else
        {
            array[z++].key = c[ic++].key;
        }
    }

    while(iv <= m)
    {
        array[z++].key = c[iv++].key;
    }
    
    while(ic <= f)
    {
        array[z++].key = c[ic++].key;
    }
}

void sort(info* array, info* c, long int i, long int f)
{
    if(i < f)
    {
        long int m = (i+f)/2;
        sort(array,c,i,m);
        sort(array,c,m+1,f);
        if(array[m].key < array[m+1].key) 
        {
            merge(array,c,i,m,f);
        }
    }
}

void MergeSort(info* array, long int size)
{
    info* c = malloc(sizeof(info)*size);
    sort(array,c,0,size-1);
    free(c);
}

long int partition(info* array, long int low, long int high, long int mid) 
{
    unsigned long int pivot = array[mid].key;

    swap(array, mid, high);

    long int i = low - 1;

    for (long int j = low; j <= high - 1; j++) 
    {
        if (array[j].key >= pivot) 
        {
            i++;
            swap(array, i, j);
        }
    }
    swap(array, i + 1, high);
    return (i + 1);
}

void QuickSort(info* array, long int low, long int high) 
{
    if (low < high) 
    {
        long int mid = (low + high) / 2;

        long int pi = partition(array, low, high, mid);
        
        QuickSort(array, low, pi - 1);
        QuickSort(array, pi + 1, high);
    }
}

void unordered(long int size, int seed) 
{
    struct timespec begin, end;

    info* array = create_vet(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    InsertionSort(array, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double insert = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array);
    printf("\ttempo da insertionsort: %f\n", insert);

    info* array2 = create_vet(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    BubbleSort(array2, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double bubble = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array2);
    printf("\ttempo da bubblesort: %f\n", bubble);

    info* array3 = create_vet(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    ShellSort(array3, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double shell = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array3);
    printf("\ttempo da shellsort: %f\n", shell);

    info* array4 = create_vet(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    RadixSort(array4, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double radix = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array4);
    printf("\ttempo da radixsort: %f\n", radix);

    info* array5 = create_vet(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    QuickSort(array5, 0, size - 1);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double quick = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array5);
    printf("\ttempo da quicksort: %f\n", quick);

    info* array6 = create_vet(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    MergeSort(array6, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double merge = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array6);
    printf("\ttempo da mergesort: %f\n", merge);
}

void all_unordered (long int size)
{
    printf("Tipo 1 com tamanho %ld (1): \n",size);
    unordered(size,12);
    printf("Tipo 1 com tamanho %ld (2): \n",size);
    unordered(size,54);
    printf("Tipo 1 com tamanho %ld (3): \n",size);
    unordered(size,59);
    printf("Tipo 1 com tamanho %ld (4): \n",size);
    unordered(size,41);
    printf("Tipo 1 com tamanho %ld (5): \n",size);
    unordered(size,75);
    printf("Tipo 1 com tamanho %ld(6): \n",size);
    unordered(size,97);
    printf("Tipo 1 com tamanho %ld (7): \n",size);
    unordered(size,71);
    printf("Tipo 1 com tamanho %ld (8): \n",size);
    unordered(size,74);
    printf("Tipo 1 com tamanho %ld (9): \n",size);
    unordered(size,44);
    printf("Tipo 1 com tamanho %ld (10): \n",size);
    unordered(size,24);
    printf("Sorting dos vetores de tamanho %ld concluido, aperte enter para continuar",size);
}

void ordered(long int size, int seed) 
{
    struct timespec begin, end;

    info* array = create_ord(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    InsertionSort(array, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double insert = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array);
    printf("\ttempo da insertionsort: %f\n", insert);

    info* array2 = create_ord(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    BubbleSort(array2, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double bubble = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array2);
    printf("\ttempo da bubblesort: %f\n", bubble);

    info* array3 = create_ord(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    ShellSort(array3, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double shell = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array3);
    printf("\ttempo da shellsort: %f\n", shell);

    info* array4 = create_ord(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    RadixSort(array4, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double radix = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array4);
    printf("\ttempo da radixsort: %f\n", radix);

    info* array5 = create_ord(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    QuickSort(array5, 0, size - 1);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double quick = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array5);
    printf("\ttempo da quicksort: %f\n", quick);

    info* array6 = create_ord(size, seed);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    MergeSort(array6, size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double merge = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
    free(array6);
    printf("\ttempo da mergesort: %f\n", merge);
}

void all_ordered (long int size)
{
    printf("Tipo 2 com tamanho %ld (1): \n",size);
    ordered(size,95);
    printf("Tipo 2 com tamanho %ld (2): \n",size);
    ordered(size,72);
    printf("Tipo 2 com tamanho %ld (3): \n",size);
    ordered(size,66);
    printf("Tipo 2 com tamanho %ld (4): \n",size);
    ordered(size,77);
    printf("Tipo 2 com tamanho %ld (5): \n",size);
    ordered(size,19);
    printf("Tipo 2 com tamanho %ld(6): \n",size);
    ordered(size,85);
    printf("Tipo 2 com tamanho %ld (7): \n",size);
    ordered(size,40);
    printf("Tipo 2 com tamanho %ld (8): \n",size);
    ordered(size,7);
    printf("Tipo 2 com tamanho %ld (9): \n",size);
    ordered(size,90);
    printf("Tipo 2 com tamanho %ld (10): \n",size);
    ordered(size,33);
    printf("Sorting dos vetores de tamanho %ld concluido, aperte enter para continuar",size);
}

int main ()
{
    all_unordered(10000);
    all_unordered(50000);
    all_unordered(100000);
    all_unordered(500000);
    all_unordered(1000000);

    all_ordered(10000);
    all_ordered(50000);
    all_ordered(100000);
    all_ordered(500000);
    all_ordered(1000000);
    
    return 0;
}