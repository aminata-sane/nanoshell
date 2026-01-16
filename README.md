<<<<<<< HEAD
# nanoshell
=======
# NanoShell - Version Modulaire

Une implémentation simple d'un shell en C, version modulaire.

## Fonctionnalités

- **Prompt avec répertoire courant** : Affiche le chemin actuel avant le prompt `?>`.
- **Commande cd** : Permet de changer de répertoire.
- **Résolution de chemin** : Recherche les commandes dans le PATH si elles ne sont pas absolues.
- **Exécution de commandes** : Utilise fork, execve et wait pour exécuter les commandes.
- **Sortie** : Tapez `exit` pour quitter.

## Compilation

Pour compiler le programme modulaire :

```
gcc main.c shell_functions.c -o nanoshell
```

## Lancement

Pour lancer le programme :

```
./nanoshell
```

Tapez des commandes au prompt `?>`. Tapez `exit` pour quitter.

## Structure du code

- `main.c` : Fonction principale avec la boucle du shell.
- `shell_functions.c` : Fonctions utilitaires (affichage, lecture, cd, résolution de chemin, exécution).
- `shell_functions.h` : Déclarations des fonctions.
>>>>>>> origin/modular-nanoshell
