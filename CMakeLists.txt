cmake_minimum_required(VERSION 3.27)
project(Benoit_Sergent_ing1_quoridor_2024_groupe3_equipe3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Benoit_Sergent_ing1_quoridor_2024_groupe3_equipe3
        main.c
        Menu.c
        Jeu.h
        Jeu.c
        Plateau.c
        Plateau.h
        Affichage.h
        Affichage.c
        fonctionsUtiles.h
        Actions.h
        Actions.c
        ScoreCalcul.c
        ScoreCalcul.h
        score.txt
        souris.c
        souris.h
)
