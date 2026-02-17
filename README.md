Projet 2048 — Programmation impérative

Membres du groupe :
- GNONLONFOUN Sydney Schalom Eliel



1. Objectif du projet
Le but du projet est de développer un jeu 2048 en mode texte en langage C,
en respectant une architecture modulaire basée sur deux librairies :
une librairie de manipulation de grille et une librairie de logique de jeu.



2. Architecture et choix de conception
Le projet est organisé en trois sous-projets :
- grid : gestion générique d’une grille n×n avec encapsulation complète
- game : logique du jeu 2048 (déplacements, fusions, score, victoire/défaite)
- programs : exécutables utilisant les librairies

Les structures de données sont opaques afin d’empêcher toute manipulation
directe des champs internes.

La compilation est réalisée avec CMake en mode hors-source.


3. Fonctionnalités implémentées
- Jeu 2048 en mode texte
- Déplacements dans les 4 directions
- Fusion correcte des tuiles
- Score réel (ajout de la valeur fusionnée)
- Détection de victoire et de défaite
- Ajout de tuiles aléatoires
- Sauvegarde et chargement d’une partie
- Grille de taille personnalisée (n×n)
- Programme de jeu aléatoire
- Programme d’affichage des meilleurs scores
- Tests unitaires pour les librairies



4. Difficultés rencontrées
Lors de l’extension du jeu à des grilles de taille n×n, plusieurs dépassements
mémoire ont été identifiés dans le moteur du jeu, dus à des tableaux initialement
codés en dur pour une grille 4×4.
Ces problèmes ont été corrigés en utilisant des allocations dynamiques basées
sur la taille réelle de la grille et en sécurisant l’accès aux buffers.


5. Limitations connues
- Affichage uniquement en mode texte
- Entrées clavier via l’entrée standard


6. Conclusion
Le projet est fonctionnel, modulaire et respecte les consignes imposées.

