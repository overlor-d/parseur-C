#include <stdlib.h>

int str_len(char *chaine)
{
    int cpt = 0;
    while (*chaine++ != '\0')
    {
        cpt++;
    }
    return cpt;
}

void free_double_tab(void *double_tab, int taille)
{
    void **tab = double_tab;
    for (int k = 0; k < taille; k++)
    {
        free(tab[k]);
    }
    free(tab);
}
