#include "item.h"
#include "io.h"
#include <time.h>

extern void quick_sort_top_down(Item *a, int lo, int hi);
extern void quick_sort_top_down_cut_off(Item *a, int lo, int hi);
extern void quick_sort_top_down_median_of_3(Item *a, int lo, int hi);

int main(int argc, char *argv[])
{
    FILE *entrada = NULL, *saida = NULL, *stats = NULL;
    int N = 0;
    char statsFileName[1000];
    char *tipo_sorted = "Nearly Sorted";
    // Linha de comando: ./lab6 entrada.txt saida.txt N

    if (argc != 4)
    {
        printf("Há falta ou excesso de argumentos. Tente novamente.\nAbortando programa...\n");
        return 1;
    }

    entrada = fopen(argv[1], "r");
    saida = fopen(argv[2], "w");
    strcpy(statsFileName, "stats_");
    strcat(statsFileName, argv[3]);
    strcat(statsFileName, tipo_sorted);
    strcat(statsFileName, ".csv");
    stats = fopen(statsFileName, "w");
    N = atoi(argv[3]);

    if (entrada == NULL || saida == NULL || N <= 0)
    {
        printf("Um ou mais parâmetros não foram informados corretamente.\nAbortando programa...\n");
        return 1;
    }

    int *array;
    array = (int *)malloc(N * sizeof(int));

    lerItensParaArray(entrada, array);
    fprintf(stats, "%s (%s): Tempo de execução para diferentes versões do Quick Sort (CUTOFF = 10)\n,,\n", argv[1], tipo_sorted);


    clock_t start_top_down = clock();
    quick_sort_top_down(array, 0, (N - 1));
    clock_t end_top_down = clock();
    double seconds_top_down = ((double)end_top_down - start_top_down) / CLOCKS_PER_SEC;
    fprintf(stats, "Top Down,%lf s,\n", seconds_top_down);

    rewind(entrada);
    lerItensParaArray(entrada, array);

    clock_t start_top_down_cut_off = clock();
    quick_sort_top_down_cut_off(array, 0, (N - 1));
    clock_t end_top_down_cut_off = clock();
    double seconds_top_down_cut_off = ((double)end_top_down_cut_off - start_top_down_cut_off) / CLOCKS_PER_SEC;
    fprintf(stats, "Top Down Cut Off,%lf s,\n", seconds_top_down_cut_off);

    clock_t start_top_down_median_of_3 = clock();
    quick_sort_top_down_median_of_3(array, 0, (N - 1));
    clock_t end_top_down_median_of_3 = clock();
    double seconds_top_down_median_of_3 = ((double)end_top_down_median_of_3 - start_top_down_median_of_3) / CLOCKS_PER_SEC;
    fprintf(stats, "Top Down Median of 3,%lf s,\n", seconds_top_down_median_of_3);

    // rewind(entrada);
    // lerItensParaArray(entrada, array);
    // clock_t start_top_down_merge_skip = clock();
    // int o = ((N - 1) - 0) + 1;
    // Item *aux3 = malloc(o * sizeof(Item));
    // merge_sort_top_down_merge_skip(array, aux3, 0, (N - 1));
    // free(aux3);
    // clock_t end_top_down_merge_skip = clock();
    // double seconds_top_down_merge_skip = ((double)end_top_down_merge_skip - start_top_down_merge_skip) / CLOCKS_PER_SEC;
    // fprintf(stats, "Top Down Merge Skip,%lf s,\n", seconds_top_down_merge_skip);

    // Algum erro... Localizar depois.
    // rewind(entrada);
    // lerItensParaArray(entrada, array);
    // clock_t start_top_down_cut_off_merge_skip = clock();
    // int p = ((N - 1) - 0) + 1;
    // Item *aux4 = malloc(p * sizeof(Item));
    // merge_sort_top_down_cut_off_merge_skip(array, aux4, 0, (N - 1));
    // free(aux4);
    // clock_t end_top_down_cut_off_merge_skip = clock();
    // double seconds_top_down_cut_off_merge_skip = ((double)end_top_down_cut_off_merge_skip - start_top_down_cut_off_merge_skip) / CLOCKS_PER_SEC;
    // fprintf(stats, "Top down Merge Skip e Cut Off,%lf s,\n", seconds_top_down_cut_off_merge_skip);

    imprimeArquivoSaida(saida, array, N);

    free(array);
    fclose(entrada);
    fclose(saida);
    return 0;
}