#!/bin/bash

IMAGE="image"
LIST_BRUIT="bruitImp15 bruitImp40 bruitGausSigma15 bruitGausSigma30"
LIST_FILTRE="filtreGausS1 filtreGausS2 filtreMoyenneur3 filtreMoyenneur7 filtreMedian3 filtreMedian7"

FILE="test.hpp"

if [[ ! -f "$FILE" ]]; then
  echo -e "Création du fichier \n"
  touch "$FILE"
else
  echo -e "Suppression + création \n"
  rm "$FILE"
  touch "$FILE"
fi
count="0"
for bruit in $LIST_BRUIT; do
  for filtre in $LIST_FILTRE; do

    echo -e "\\n// MSE pour le $bruit et le $filtre" >> "$FILE"
    myBruitConv="${bruit}Conv${count}"
    echo -e "Image<uint8_t> $myBruitConv = convertionImage(${bruit});" >> "$FILE"
    myFiltreConv="${filtre}Conv${count}"
    echo -e "Image<uint8_t> $myFiltreConv = convertionImage(${filtre});" >> "$FILE"
    myMSE="MSE${bruit}${filtre}"
    echo -e "double $myMSE = computeMSE(${myBruitConv},${filtre});" >> "$FILE"
    myImageConv="imageConv${bruit}${filtre}"
    echo -e "Image<double> $myImageConv = convolution(${myBruitConv},${filtre});" >> "$FILE"
    myImage="image${bruit}${filtre}"
    echo -e "Image<uint8_t> $myImage = convertionImage(${myImageConv});" >> "$FILE"
    newMyMSE="newMSE${bruit}${filtre}"
    echo -e "double $newMyMSE = computeMSE(${IMAGE},${myImageConv});" >> "$FILE"
    echo -e "printf(\"MSE entre ${bruit} et le ${filtre} sur l'image standart : %f \\\n\",$newMyMSE);" >> "$FILE"
    echo -e "writePGM(${myImage},\"../../images/bruit/${myImage}.pgm\");" >> "$FILE"
    count=$((count+1))
    done
done
