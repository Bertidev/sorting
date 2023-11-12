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
        v[i].key= rand();
    }
    return v;
}

void InsertionSort (info* array, unsigned long int size)
{
    unsigned long int i, j, element;

    for(i=1; i<size; i++)
    {
        element = array[i].key; 
        j = i-1;
        while (j>=0 && array[j].key>element)
        {
            array[j+1].key = array[j].key;
            j= j-1;
        }
        array[j+1].key = element;
    }
}
    
int main ()
{
    info* ten1 = create_vet (10000,22);
    info* ten2 = create_vet (10000,19);
    info* fift1 = create_vet (50000,45);
    info* fift2 = create_vet (50000,41);
    info* hund1 = create_vet (100000,89);
    info* hund2 = create_vet (100000,11);
    info* five1 = create_vet (500000,60);
    info* five2 = create_vet (500000,13);
    info* mil1 = create_vet (1000000,39);
    info* mil2 = create_vet (1000000,1);

    info* ten_ord1 = create_ord (10000,5);
    info* ten_ord2 = create_ord (10000,7);
    info* fift_ord1 = create_ord (50000,32);
    info* fift_ord2 = create_ord (50000,42);
    info* hund_ord1 = create_ord (100000,3);
    info* hund_ord2 = create_ord (100000,4);
    info* five_ord1 = create_ord (500000,59);
    info* five_ord2 = create_ord (500000,87);
    info* mil_ord1 = create_ord (1000000,10);
    info* mil_ord2 = create_ord (1000000,91);

    printf ("criacao dos vetores concluida");
    unsigned long int i;
    for(i=0; i<10000; i++)
    {
        printf("%lu, ", ten1[i].key);
    }
    InsertionSort(ten1,10000);
    printf("sorting concluido");

    return 0;
}