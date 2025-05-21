#!/bin/bash

# Premier argument : fichier source
# Deuxième argument : numéro de la map à décommenter (1-5)
# Troisième argument : fichier de sortie

SRC=$1
MAP_NUM=$2
DEST=$3

# Copier le fichier source
cp $SRC $DEST

# Variables pour définir les lignes de début et de fin de chaque map
case $MAP_NUM in
  1) # Map non fermée (Unclosed map)
    START_LINE=20
    END_LINE=24
    ;;
  2) # Map sans joueur (No player)
    START_LINE=28
    END_LINE=32
    ;;
  3) # Map avec caractère invalide (X aint valid char)
    START_LINE=36
    END_LINE=40
    ;;
  4) # Map simple valide (Kanye West)
    START_LINE=46
    END_LINE=51
    ;;
  5) # Map complexe (Eazy-East)
    START_LINE=55
    END_LINE=86
    ;;
  *)
    echo "Numéro de map invalide. Utilisez 1-5."
    exit 1
    ;;
esac

# Décommenter la map sélectionnée en supprimant les # au début des lignes
for (( i=$START_LINE; i<=$END_LINE; i++ ))
do
  # Supprimer le # au début de la ligne
  sed -i "${i}s/^# //" $DEST
  sed -i "${i}s/^#//" $DEST
done

echo "Map $MAP_NUM décommentée dans $DEST"