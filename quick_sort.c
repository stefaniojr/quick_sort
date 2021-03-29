#include "item.h"
#include <time.h>

#define CUTOFF 15

extern void insertion_sort(Item *a, int lo, int hi);

int median_of_3(Item *a, int lo, int hi)
{
    srand(time(NULL));
    int zero = lo + rand() % ((hi+1)-lo);
    int um = -1;
    int dois = -1;

    while (1)
    {
        um = lo + rand() % ((hi+1)-lo);
        if (um != zero)
            break;
    }

    while (1)
    {
        dois = lo + rand() % ((hi+1)-lo);
        if (dois != zero && dois != um)
            break;
    }
    printf("indices: %d %d %d\n", zero, um, dois);
    printf("%d %d %d\n", a[zero], a[um], a[dois]);
    if (a[zero] < a[dois])
    {
        if (a[um] < a[zero])
            return zero;
        else if (a[dois] < a[um])
            return dois;
        else
            return um;
    }
    else if (a[um] < a[dois])
        return dois;
    else if (a[zero] < a[um])
        return zero;
    else
        return um;
}

int partition(Item *a, int lo, int hi)
{
    int i = lo, j = hi + 1;
    Item v = a[lo];
    while (1)
    {
        while (less(a[++i], v)) // Find item on left to swap.
            if (i == hi)
                break;
        while (less(v, a[--j])) // Find item on right to swap.
            if (j == lo)
                break;
        if (i >= j)
            break; // Check if pointers cross.
        exch(a[i], a[j]);
    }
    exch(a[lo], a[j]); // Swap with partitioning item.
    return j;          // Return index of item known to be in place.
}

void quick_sort_top_down(Item *a, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }
    int j = partition(a, lo, hi);
    quick_sort_top_down(a, lo, j - 1);
    quick_sort_top_down(a, j + 1, hi);
}

void quick_sort_top_down_cut_off(Item *a, int lo, int hi)
{
    if (hi <= lo + CUTOFF - 1)
    {
        insertion_sort(a, lo, hi);
        return;
    }
    int j = partition(a, lo, hi);
    quick_sort_top_down_cut_off(a, lo, j - 1);
    quick_sort_top_down_cut_off(a, j + 1, hi);
}

void quick_sort_top_down_median_of_3(Item *a, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }

    if (hi > 3)
    {
        int median = median_of_3(a, lo, hi);
        exch(a[lo], a[median]);
        printf("%d\n", median);
    }

    int j = partition(a, lo, hi);
    quick_sort_top_down_median_of_3(a, lo, j - 1);
    quick_sort_top_down_median_of_3(a, j + 1, hi);
}