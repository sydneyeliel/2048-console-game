/* GNONLONFOUN Sydney Schalom Eliel*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SCORES 100

int compare_desc(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

int main(void)
{
    FILE *file = fopen("scores.txt", "r");
    if (!file) {
        printf("No scores found.\n");
        return 0;
    }

    int scores[MAX_SCORES];
    int count = 0;

    while (fscanf(file, "%d", &scores[count]) == 1 && count < MAX_SCORES) {
        count++;
    }
    fclose(file);

    qsort(scores, count, sizeof(int), compare_desc);

    printf("Top 3 scores:\n");
    for (int i = 0; i < count && i < 3; i++) {
        printf("%d. %d\n", i + 1, scores[i]);
    }

    return 0;
}

