#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parseur.h"
#include "fonctions_base.h"

int valide_opt(int argc, char *argv[])
{
    for (int k = 1; k < argc; k++)
    {
        if (str_len(argv[k]) == 1)
        {
            if (argv[k][0] == '-')
            {
                fprintf(stderr, "Error with '-' no option after.\n");
                return 1;
            }
        }
        else if (str_len(argv[k]) == 2)
        {
            if (argv[k][0] == '-' && argv[k][1] == '-')
            {
                fprintf(stderr, "Error with '--' no option after.\n");
                return 1;
            }
            else if (argv[k][0] == '-')
            {
                continue;
            }
        }
        else if (str_len(argv[k]) == 3)
        {
            if (argv[k][0] == '-' && argv[k][1] == '-')
            {
                fprintf(stderr, "Error with '--%c' one letter after '--' is not permited.\n", argv[k][2]);
                return 1;
            }
            else if (argv[k][0] == '-')
            {
                fprintf(stderr, "Erreur d'options un seul tiret donné sans rien apres.\n");
                return 1;
            }
        }
        else if (str_len(argv[k]) >= 4)
        {
            if (argv[k][0] == '-' && argv[k][0] == '-')
            {
                continue;
            }
        }
    }
    return 0;
}

void tiret_to_normal(char *opt)
{
    if (opt == NULL) return;
    int decalage = 0;
    if (opt[0] == '-')
    {
        decalage = 1;

        if (opt[1] == '-')
        {
            decalage = 2;
        }
    }
    if (decalage > 0)
    {
        memmove(opt, opt + decalage, strlen(opt) - decalage + 1);
    }
}

void char_to_string(char **opt, struct option *registre, int t_registre)
{
    if (str_len(*opt) == 1)
    {
        for (int k = 0; k < t_registre; k++)
        {
            if (**opt == registre[k].lettre)
            {
                char *temp = realloc(*opt, strlen(registre[k].complet) + 1);
                *opt = temp;
                strcpy(*opt, registre[k].complet);
            }
        }
    }
}

int in_registre(struct option *registre, int nbr_opt_registre, int cpt_opt, char **tab_opt_s_t)
{
    for (int k = 0; k < cpt_opt; k++)
    {
        int trouve = 0;
        int size_tab = str_len(tab_opt_s_t[k]);
        if (size_tab == 1)
        {
            for (int i = 0; i < nbr_opt_registre; i++)
            {
                if (*tab_opt_s_t[k] == registre[i].lettre)
                {
                    trouve = 1;
                }
            }
        }
        else if (size_tab >= 2)
        {
            for (int i = 0; i < nbr_opt_registre; i++)
            {
                if (strcmp(tab_opt_s_t[k], registre[i].complet) == 0)
                {
                    trouve = 1;
                }
            }
        }
        if (trouve == 0)
        {
            fprintf(stderr, "The option '%s' is not in the authorized registry of options.\n", tab_opt_s_t[k]);
            return 1;
        }
    }
    return 0;
}

int double_opt(int argc, char **liste_opt)
{
    for (int k = 1; k < argc; k++)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(liste_opt[k], liste_opt[i]) == 0 && i != k)
            {
                fprintf(stderr, "Option '%s' is duplicated.\n", liste_opt[k]);
                return 1;
            }
        }
    }
    return 0;
}

int cpt_option(int argc, char *argv[])
{
    int cpt = 0;
    for (int k = 1; k < argc; k++)
    {
        if (argv[k][0] == '-')
        {
            cpt++;
        }
    }
    return cpt;
}

char **liste_opt_s_tirets(int argc, char *argv[])
{
    int nbr_opt = cpt_option(argc, argv);
    char **liste_fin = malloc(nbr_opt * sizeof(char *));
    int index_liste = 0;
    for (int k = 1; k < argc; k++)
    {
        if (argv[k][0] == '-')
        {
            liste_fin[index_liste] = malloc((str_len(argv[k]) + 1) * sizeof(char));
            strcpy(liste_fin[index_liste], argv[k]);
            index_liste++;
        }
    }

    for (int k = 0; k < nbr_opt; k++)
    {
        tiret_to_normal(liste_fin[k]);
    }
    return liste_fin;
}

int **liste_arg_count(int nbr_opt, int argc, char **argv)
{
    int **liste = malloc(sizeof(int *) * nbr_opt);
    for (int k = 0; k < nbr_opt; k++)
    {
        liste[k] = malloc(sizeof(int));
        *liste[k] = cpt_parameter_in_opt(argc, argv, k + 1);
    }
    return liste;
}

void afficher_opt(char **liste, int taille)
{
    printf("--------------------------------\n");
    for (int k = 0; k < taille; k++)
    {
        printf("Option %d : %s\n", k + 1, liste[k]);
    }
    printf("--------------------------------\n");

}

void afficher_nbr_arg(char **liste_opt, int **liste_arg, int taille)
{
    printf("--------------------------------\n");
    for (int k = 0; k < taille; k++)
    {
        printf("Option %d : %s -> %d arguments.\n", k + 1, liste_opt[k], *liste_arg[k]);
    }
    printf("--------------------------------\n");

}

int cpt_parameter_in_opt(int argc, char **argv, int num_opt)
{
    int cpt = 0;
    int index_opt = 1;
    for (int k = 1; k < argc; k++)
    {
        if (argv[k][0] == '-')
        {
            if (index_opt == num_opt)
            {
                k++;
                while (k < argc && argv[k][0] != '-' )
                {
                    k++;
                    cpt++;
                }
                return cpt;
            }
            index_opt++;
        }
    }
    return cpt;
}

int verif_specificites(struct option *registre);

int parsing(int argc, char *argv[], struct option *registre, ...)
{
    
}
