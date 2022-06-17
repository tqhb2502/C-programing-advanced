#include <stdio.h>
#include "jval.h"
#include <time.h>
#include <stdlib.h>

Jval *create_array_i(int n)
{
    Jval *a = (Jval *)malloc(n * sizeof(Jval));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        a[i] = new_jval_i(rand() % 10);
    return a;
}

void print_array_i(Jval *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", jval_i(a[i]));
    printf("\n");
    return;
}

void swap(Jval *a, Jval *b)
{
    Jval tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

int compare_i(Jval *a, Jval *b)
{
    if (jval_i(*a) == jval_i(*b)) return 0;
    return jval_i(*a) > jval_i(*b) ? 1 : -1;
}

void quick_sort(Jval *a, int l, int r, int (*compare)(Jval *, Jval *))
{
    //3-way quick sort
    if (l >= r) return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (compare(a + (++i), a + r) == -1);
        while (compare(a + (--j), a + r) == 1)
            if (j == l) break;
        if (i >= j) break;
        swap(a + i, a + j);
        if (compare(a + i, a + r) == 0) swap(a + i, a + (++p));
        if (compare(a + j, a + r) == 0) swap(a + j, a + (--q));
    }
    swap(a + i, a + r);
    j = i + 1;
    i = i - 1;
    for (int k = l; k <= p; k++) swap(a + k, a + (i--));
    for (int k = r - 1; k >= q; k--) swap(a + k, a + (j++));
    quick_sort(a, l, i, compare);
    quick_sort(a, j, r, compare);
    return;
}

int search(Jval *a, int l, int r, Jval *key, int (*compare)(Jval *, Jval *))
{
    if (l > r) return -1;
    int mid = (l + r) / 2;
    if (compare(a + mid, key) == 0) return mid;
    if (compare(a + mid, key) == -1) return search(a, mid + 1, r, key, compare);
    else return search(a, l, mid - 1, key, compare);
}

int search_right(Jval *a, int l, int r, Jval *key, int (*compare)(Jval *, Jval *))
{
    if (l + 1 == r)
    {
        if (compare(a + r, key) == 0) return r;
        if (compare(a + l, key) == 0) return l;
        return -1;
    }
    int mid = (l + r) / 2;
    if (compare(a + mid, key) != 1) return search_right(a, mid, r, key, compare);
    else return search_right(a, l, mid, key, compare);
}

int search_left(Jval *a, int l, int r, Jval *key, int (*compare)(Jval *, Jval *))
{
    if (l + 1 == r)
    {
        if (compare(a + l, key) == 0) return l;
        if (compare(a + r, key) == 0) return r;
        return -1;
    }
    int mid = (l + r) / 2;
    if (compare(a + mid, key) != -1) return search_left(a, l, mid, key, compare);
    else return search_left(a, mid, r, key, compare);
}

int main()
{
    int n = 20;
    Jval *a = create_array_i(n);
    print_array_i(a, n);
    quick_sort(a, 0, n - 1, compare_i);
    print_array_i(a, n);
    int x;
    printf("Nhap so can tim: ");
    scanf("%d", &x);
    Jval key = new_jval_i(x);
    //printf("Vi tri: %d\n", search(a, 0, n - 1, &key, compare_i) + 1);
    printf("Vi tri: %d -> %d\n", search_left(a, 0, n - 1, &key, compare_i) + 1, search_right(a, 0, n - 1, &key, compare_i) + 1);
    return 0;
}