# Parseur en C
Ce projet est un parseur en C conçu pour compter et renvoyer, sous la forme d'une liste de tuples (option, liste d'arguments), les éléments nécessaires à l'exploitation ultérieure des arguments associés à leurs options respectives.

## Fonctionnement
Le fonctionnement du parseur est le suivant :
Il analyse les arguments et, dès la détection d'un '-' ou d'un '--', vérifie si l'argument est valide. Si c'est le cas, il parcourt les paramètres de cet argument et les ajoute à une liste. En fin de processus, il renvoie une liste de tuples structurée de la manière suivante :

    [
        ["nom_1", [opt1, opt2, opt3]],
        ["nom_2", [opt1, opt2, opt3]],
        ["nom_3", []],
        ["nom_4", [opt1, opt2]],
        ["nom_5", [opt1]]
    ]

Vous pouvez ensuite utiliser ces listes selon vos besoins.

## Spécificités
Le parseur offre la possibilité de déterminer le nombre maximal d'arguments pour une option :
- 0 signifie aucun argument,
- 1 indique un seul argument, et 'x' pour x arguments,
- -1 autorise un nombre indéterminé d'arguments.

Il est important de noter que le parseur ne vérifie pas la validité de l'argument fourni à une option selon un paramètre défini..