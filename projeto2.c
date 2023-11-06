#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct lulalivre
{
    unsigned long int key;
    float num;
} lulu;

lulu *create_vet_ord (unsigned long int size, int seed)
{
    lulu *v = (lulu*)malloc(size* sizeof(lulu));
    unsigned long int i=0, growth=0;
    srand(seed);
    for(i=0;i<size;i++)
    {
        v[i].num = rand();
        growth += (rand()%10 +1);
        v[i].key = growth;
    }
    return v;
}

lulu *create_vet (unsigned long int size, int seed)
{
    lulu *v = (lulu*)malloc(size* sizeof(lulu));
    unsigned long int i=0;
    srand(seed);
    for(i=0;i<size;i++)
    {
        v[i].num = rand();
        v[i].key = rand();
    }
    return v;
}

void InsertionSort(lulu *array, unsigned long int size) 
{ 
    unsigned long int i, j, element; 
    for (i = 0; i < size; i++) 
    {
        element = array[i].key; j = i - 1; 
        while (j > 0 && array[j].key > element) 
        { 
            array[j + 1].key = array[j].key; 
            j = j - 1; 
        } 
        array[j + 1].key = element; 
    }
}

void swap(lulu* array, unsigned long int i, unsigned long int j) 
{ 
    unsigned long int temp = array[i].key; 
    array[i].key = array[j].key; 
    array[j].key = temp; 
} 

void bubbleSort(lulu *array, unsigned long int size) 
{ 
    unsigned long int i, j; 
    for (i = 0; i < size - 1; i++) 
    {
        for (j = 0; j < size - i - 1; j++) 
        {
            if (array[j].key > array[j + 1].key) 
            {
                swap(array, j, j + 1);
            }
        } 
    }
} 


int main () 
{
    lulu *ten_ord1 = create_vet_ord(10000,5);
    lulu *ten_ord2 = create_vet_ord(10000,7);
    lulu *fift_ord1 = create_vet_ord(50000,32);
    lulu *fift_ord2 = create_vet_ord(50000,42);
    lulu *hund_ord1 = create_vet_ord(100000,3);
    lulu *hund_ord2 = create_vet_ord(100000,4);
    lulu *five_ord1 = create_vet_ord(500000,59);
    lulu *five_ord2 = create_vet_ord(500000,87);
    lulu *mil_ord1 = create_vet_ord(1000000,10);
    lulu *mil_ord2 = create_vet_ord(1000000,91);

    lulu *ten1 = create_vet(10000,22);
    lulu *ten2 = create_vet(10000,19);
    lulu *fift1 = create_vet(50000,45);
    lulu *fift2 = create_vet(50000,41);
    lulu *hund1 = create_vet(100000,89);
    lulu *hund2 = create_vet(100000,11);
    lulu *five1 = create_vet(500000,60);
    lulu *five2 = create_vet(500000,13);
    lulu *mil1 = create_vet(1000000,39);
    lulu *mil2 = create_vet(1000000,1);
    unsigned long int i = 0;
    for(i=0;i<10000;i++)
    {
        printf("%lu, ",ten1[i].key);
    }
    InsertionSort(ten1,10000);
    printf("\n\naperte enter para continuar\n\n");
    getchar();
    for(i=0;i<10000;i++)
    {
        printf("%lu, ",ten1[i].key);
    }
    return 0;
}