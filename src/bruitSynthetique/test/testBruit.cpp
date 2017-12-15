/*

    Pour compiler le fichier
    g++ mainFiltreMedian.cpp -o mainFiltreMedian

    ./mainFiltreMedian images/base/boat.pgm

*/

#include <fstream>
#include <iostream>
#include "../../image.h"
#include <cstdint>
#include "../../fileio.hpp"

using namespace std;

int main(int argc,const char * argv[]){

    printf("Lecture de l\'image en entré.\n");
    std::string imageEntre = argv[1];
    Image<uint8_t> image = readPGM(imageEntre);
    double matrice1[9] = {
                        1/9,1/9,1/9,
                        1/9,1/9,1/9,
                        1/9,1/9,1/9
    };

    double matrice2[49] = {
                        1/49,1/49,1/49,1/49,1/49,1/49,1/49,
                        1/49,1/49,1/49,1/49,1/49,1/49,1/49,
                        1/49,1/49,1/49,1/49,1/49,1/49,1/49,
                        1/49,1/49,1/49,1/49,1/49,1/49,1/49,
                        1/49,1/49,1/49,1/49,1/49,1/49,1/49,
                        1/49,1/49,1/49,1/49,1/49,1/49,1/49,
                        1/49,1/49,1/49,1/49,1/49,1/49,1/49
    };

    Image<double> masque3Dou(3,3,matrice1);
    Image<double> masque7Dou(7,7,matrice2);
    Image<uint8_t> masque3 = convertionImage(masque3Dou);
    Image<uint8_t> masque7 = convertionImage(masque7Dou);
    // Les images avec les brui
    Image<double> bruitImp15 = bruitImpulsionnel(image,0.15);
    Image<double> bruitImp40 = bruitImpulsionnel(image,0.40);

    Image<double> bruitGausSigma15 = bruitGaussien(image,0.0,15);
    Image<double> bruitGausSigma30 = bruitGaussien(image,0.0,30);


    Image<double> filtreMoyenneur3 = moyenneur(3);
    Image<double> filtreMoyenneur7 = moyenneur(7);

    Image<double> filtreMedian3 = filtreMedian(image,masque3Dou);
    Image<double> filtreMedian7 = filtreMedian(image,masque7Dou);

    Image<double> filtreGausS1 = gaussienMask(1);
    Image<double> filtreGausS2 = gaussienMask(2);


    // Image<uint8_t> filtreMoyen3 = convertionImage(filtreMoyen3D);
    // Image<uint8_t> filtreMoyen3 = convertionImage(filtreMoyen3D);
    // Image<uint8_t> filtreGaus1 = convertionImage(filtreGausS1);
    // Image<uint8_t> filtreGaus2 = convertionImage(filtreGausS2);


    // Convertion des images
    //
    // Image<uint8_t> filtreGaus1Conv = convertionImage(filtreGaus1);
    // Image<uint8_t> filtreGaus2Conv = convertionImage(filtreGaus2);

    double MSE1 = computeMSE(image,bruitImp15);
    double MSE2 = computeMSE(image,bruitImp40);
    double MSE3 = computeMSE(image,bruitGausSigma15);
    double MSE4 = computeMSE(image,bruitGausSigma30);
    printf("Image référence et Image Bruité\n");
    printf("\n---------------------\n");
    printf("Image de référence et le bruit impulsionnel 15 : %f \n",MSE1);
    printf("Image de référence et le bruit impulsionnel 40 : %f \n",MSE2);
    printf("Image de référence et le bruit gaussien d'écart-type 15 : %f \n",MSE3);
    printf("Image de référence et le bruit gaussien d'écart-type 30 : %f \n",MSE4);
    printf("\n---------------------\n" );

    printf("Image Débruité et l'image de référence\n");



    // MSE pour le bruitImp15 et le filtreGausS1
    Image<uint8_t> bruitImp15Conv0 = convertionImage(bruitImp15);
    Image<uint8_t> filtreGausS1Conv0 = convertionImage(filtreGausS1);
    double MSEbruitImp15filtreGausS1 = computeMSE(bruitImp15Conv0,filtreGausS1);
    Image<double> imageConvbruitImp15filtreGausS1 = convolution(bruitImp15Conv0,filtreGausS1);
    Image<uint8_t> imagebruitImp15filtreGausS1 = convertionImage(imageConvbruitImp15filtreGausS1);
    double newMSEbruitImp15filtreGausS1 = computeMSE(image,imageConvbruitImp15filtreGausS1);
    printf("MSE entre bruitImp15 et le filtreGausS1 sur l'image standart : %f \n",newMSEbruitImp15filtreGausS1);
    writePGM(imagebruitImp15filtreGausS1,"../../images/bruit/imagebruitImp15filtreGausS1.pgm");

    // MSE pour le bruitImp15 et le filtreGausS2
    Image<uint8_t> bruitImp15Conv1 = convertionImage(bruitImp15);
    Image<uint8_t> filtreGausS2Conv1 = convertionImage(filtreGausS2);
    double MSEbruitImp15filtreGausS2 = computeMSE(bruitImp15Conv1,filtreGausS2);
    Image<double> imageConvbruitImp15filtreGausS2 = convolution(bruitImp15Conv1,filtreGausS2);
    Image<uint8_t> imagebruitImp15filtreGausS2 = convertionImage(imageConvbruitImp15filtreGausS2);
    double newMSEbruitImp15filtreGausS2 = computeMSE(image,imageConvbruitImp15filtreGausS2);
    printf("MSE entre bruitImp15 et le filtreGausS2 sur l'image standart : %f \n",newMSEbruitImp15filtreGausS2);
    writePGM(imagebruitImp15filtreGausS2,"../../images/bruit/imagebruitImp15filtreGausS2.pgm");

    // MSE pour le bruitImp15 et le filtreMoyenneur3
    Image<uint8_t> bruitImp15Conv2 = convertionImage(bruitImp15);
    Image<uint8_t> filtreMoyenneur3Conv2 = convertionImage(filtreMoyenneur3);
    double MSEbruitImp15filtreMoyenneur3 = computeMSE(bruitImp15Conv2,filtreMoyenneur3);
    Image<double> imageConvbruitImp15filtreMoyenneur3 = convolution(bruitImp15Conv2,filtreMoyenneur3);
    Image<uint8_t> imagebruitImp15filtreMoyenneur3 = convertionImage(imageConvbruitImp15filtreMoyenneur3);
    double newMSEbruitImp15filtreMoyenneur3 = computeMSE(image,imageConvbruitImp15filtreMoyenneur3);
    printf("MSE entre bruitImp15 et le filtreMoyenneur3 sur l'image standart : %f \n",newMSEbruitImp15filtreMoyenneur3);
    writePGM(imagebruitImp15filtreMoyenneur3,"../../images/bruit/imagebruitImp15filtreMoyenneur3.pgm");

    // MSE pour le bruitImp15 et le filtreMoyenneur7
    Image<uint8_t> bruitImp15Conv3 = convertionImage(bruitImp15);
    Image<uint8_t> filtreMoyenneur7Conv3 = convertionImage(filtreMoyenneur7);
    double MSEbruitImp15filtreMoyenneur7 = computeMSE(bruitImp15Conv3,filtreMoyenneur7);
    Image<double> imageConvbruitImp15filtreMoyenneur7 = convolution(bruitImp15Conv3,filtreMoyenneur7);
    Image<uint8_t> imagebruitImp15filtreMoyenneur7 = convertionImage(imageConvbruitImp15filtreMoyenneur7);
    double newMSEbruitImp15filtreMoyenneur7 = computeMSE(image,imageConvbruitImp15filtreMoyenneur7);
    printf("MSE entre bruitImp15 et le filtreMoyenneur7 sur l'image standart : %f \n",newMSEbruitImp15filtreMoyenneur7);
    writePGM(imagebruitImp15filtreMoyenneur7,"../../images/bruit/imagebruitImp15filtreMoyenneur7.pgm");

    // MSE pour le bruitImp15 et le filtreMedian3
    Image<uint8_t> bruitImp15Conv4 = convertionImage(bruitImp15);
    Image<uint8_t> filtreMedian3Conv4 = convertionImage(filtreMedian3);
    double MSEbruitImp15filtreMedian3 = computeMSE(bruitImp15Conv4,filtreMedian3);
    Image<double> imageConvbruitImp15filtreMedian3 = convolution(bruitImp15Conv4,filtreMedian3);
    Image<uint8_t> imagebruitImp15filtreMedian3 = convertionImage(imageConvbruitImp15filtreMedian3);
    double newMSEbruitImp15filtreMedian3 = computeMSE(image,imageConvbruitImp15filtreMedian3);
    printf("MSE entre bruitImp15 et le filtreMedian3 sur l'image standart : %f \n",newMSEbruitImp15filtreMedian3);
    writePGM(imagebruitImp15filtreMedian3,"../../images/bruit/imagebruitImp15filtreMedian3.pgm");

    // MSE pour le bruitImp15 et le filtreMedian7
    Image<uint8_t> bruitImp15Conv5 = convertionImage(bruitImp15);
    Image<uint8_t> filtreMedian7Conv5 = convertionImage(filtreMedian7);
    double MSEbruitImp15filtreMedian7 = computeMSE(bruitImp15Conv5,filtreMedian7);
    Image<double> imageConvbruitImp15filtreMedian7 = convolution(bruitImp15Conv5,filtreMedian7);
    Image<uint8_t> imagebruitImp15filtreMedian7 = convertionImage(imageConvbruitImp15filtreMedian7);
    double newMSEbruitImp15filtreMedian7 = computeMSE(image,imageConvbruitImp15filtreMedian7);
    printf("MSE entre bruitImp15 et le filtreMedian7 sur l'image standart : %f \n",newMSEbruitImp15filtreMedian7);
    writePGM(imagebruitImp15filtreMedian7,"../../images/bruit/imagebruitImp15filtreMedian7.pgm");

    // MSE pour le bruitImp40 et le filtreGausS1
    Image<uint8_t> bruitImp40Conv6 = convertionImage(bruitImp40);
    Image<uint8_t> filtreGausS1Conv6 = convertionImage(filtreGausS1);
    double MSEbruitImp40filtreGausS1 = computeMSE(bruitImp40Conv6,filtreGausS1);
    Image<double> imageConvbruitImp40filtreGausS1 = convolution(bruitImp40Conv6,filtreGausS1);
    Image<uint8_t> imagebruitImp40filtreGausS1 = convertionImage(imageConvbruitImp40filtreGausS1);
    double newMSEbruitImp40filtreGausS1 = computeMSE(image,imageConvbruitImp40filtreGausS1);
    printf("MSE entre bruitImp40 et le filtreGausS1 sur l'image standart : %f \n",newMSEbruitImp40filtreGausS1);
    writePGM(imagebruitImp40filtreGausS1,"../../images/bruit/imagebruitImp40filtreGausS1.pgm");

    // MSE pour le bruitImp40 et le filtreGausS2
    Image<uint8_t> bruitImp40Conv7 = convertionImage(bruitImp40);
    Image<uint8_t> filtreGausS2Conv7 = convertionImage(filtreGausS2);
    double MSEbruitImp40filtreGausS2 = computeMSE(bruitImp40Conv7,filtreGausS2);
    Image<double> imageConvbruitImp40filtreGausS2 = convolution(bruitImp40Conv7,filtreGausS2);
    Image<uint8_t> imagebruitImp40filtreGausS2 = convertionImage(imageConvbruitImp40filtreGausS2);
    double newMSEbruitImp40filtreGausS2 = computeMSE(image,imageConvbruitImp40filtreGausS2);
    printf("MSE entre bruitImp40 et le filtreGausS2 sur l'image standart : %f \n",newMSEbruitImp40filtreGausS2);
    writePGM(imagebruitImp40filtreGausS2,"../../images/bruit/imagebruitImp40filtreGausS2.pgm");

    // MSE pour le bruitImp40 et le filtreMoyenneur3
    Image<uint8_t> bruitImp40Conv8 = convertionImage(bruitImp40);
    Image<uint8_t> filtreMoyenneur3Conv8 = convertionImage(filtreMoyenneur3);
    double MSEbruitImp40filtreMoyenneur3 = computeMSE(bruitImp40Conv8,filtreMoyenneur3);
    Image<double> imageConvbruitImp40filtreMoyenneur3 = convolution(bruitImp40Conv8,filtreMoyenneur3);
    Image<uint8_t> imagebruitImp40filtreMoyenneur3 = convertionImage(imageConvbruitImp40filtreMoyenneur3);
    double newMSEbruitImp40filtreMoyenneur3 = computeMSE(image,imageConvbruitImp40filtreMoyenneur3);
    printf("MSE entre bruitImp40 et le filtreMoyenneur3 sur l'image standart : %f \n",newMSEbruitImp40filtreMoyenneur3);
    writePGM(imagebruitImp40filtreMoyenneur3,"../../images/bruit/imagebruitImp40filtreMoyenneur3.pgm");

    // MSE pour le bruitImp40 et le filtreMoyenneur7
    Image<uint8_t> bruitImp40Conv9 = convertionImage(bruitImp40);
    Image<uint8_t> filtreMoyenneur7Conv9 = convertionImage(filtreMoyenneur7);
    double MSEbruitImp40filtreMoyenneur7 = computeMSE(bruitImp40Conv9,filtreMoyenneur7);
    Image<double> imageConvbruitImp40filtreMoyenneur7 = convolution(bruitImp40Conv9,filtreMoyenneur7);
    Image<uint8_t> imagebruitImp40filtreMoyenneur7 = convertionImage(imageConvbruitImp40filtreMoyenneur7);
    double newMSEbruitImp40filtreMoyenneur7 = computeMSE(image,imageConvbruitImp40filtreMoyenneur7);
    printf("MSE entre bruitImp40 et le filtreMoyenneur7 sur l'image standart : %f \n",newMSEbruitImp40filtreMoyenneur7);
    writePGM(imagebruitImp40filtreMoyenneur7,"../../images/bruit/imagebruitImp40filtreMoyenneur7.pgm");

    // MSE pour le bruitImp40 et le filtreMedian3
    Image<uint8_t> bruitImp40Conv10 = convertionImage(bruitImp40);
    Image<uint8_t> filtreMedian3Conv10 = convertionImage(filtreMedian3);
    double MSEbruitImp40filtreMedian3 = computeMSE(bruitImp40Conv10,filtreMedian3);
    Image<double> imageConvbruitImp40filtreMedian3 = convolution(bruitImp40Conv10,filtreMedian3);
    Image<uint8_t> imagebruitImp40filtreMedian3 = convertionImage(imageConvbruitImp40filtreMedian3);
    double newMSEbruitImp40filtreMedian3 = computeMSE(image,imageConvbruitImp40filtreMedian3);
    printf("MSE entre bruitImp40 et le filtreMedian3 sur l'image standart : %f \n",newMSEbruitImp40filtreMedian3);
    writePGM(imagebruitImp40filtreMedian3,"../../images/bruit/imagebruitImp40filtreMedian3.pgm");

    // MSE pour le bruitImp40 et le filtreMedian7
    Image<uint8_t> bruitImp40Conv11 = convertionImage(bruitImp40);
    Image<uint8_t> filtreMedian7Conv11 = convertionImage(filtreMedian7);
    double MSEbruitImp40filtreMedian7 = computeMSE(bruitImp40Conv11,filtreMedian7);
    Image<double> imageConvbruitImp40filtreMedian7 = convolution(bruitImp40Conv11,filtreMedian7);
    Image<uint8_t> imagebruitImp40filtreMedian7 = convertionImage(imageConvbruitImp40filtreMedian7);
    double newMSEbruitImp40filtreMedian7 = computeMSE(image,imageConvbruitImp40filtreMedian7);
    printf("MSE entre bruitImp40 et le filtreMedian7 sur l'image standart : %f \n",newMSEbruitImp40filtreMedian7);
    writePGM(imagebruitImp40filtreMedian7,"../../images/bruit/imagebruitImp40filtreMedian7.pgm");

    // MSE pour le bruitGausSigma15 et le filtreGausS1
    Image<uint8_t> bruitGausSigma15Conv12 = convertionImage(bruitGausSigma15);
    Image<uint8_t> filtreGausS1Conv12 = convertionImage(filtreGausS1);
    double MSEbruitGausSigma15filtreGausS1 = computeMSE(bruitGausSigma15Conv12,filtreGausS1);
    Image<double> imageConvbruitGausSigma15filtreGausS1 = convolution(bruitGausSigma15Conv12,filtreGausS1);
    Image<uint8_t> imagebruitGausSigma15filtreGausS1 = convertionImage(imageConvbruitGausSigma15filtreGausS1);
    double newMSEbruitGausSigma15filtreGausS1 = computeMSE(image,imageConvbruitGausSigma15filtreGausS1);
    printf("MSE entre bruitGausSigma15 et le filtreGausS1 sur l'image standart : %f \n",newMSEbruitGausSigma15filtreGausS1);
    writePGM(imagebruitGausSigma15filtreGausS1,"../../images/bruit/imagebruitGausSigma15filtreGausS1.pgm");

    // MSE pour le bruitGausSigma15 et le filtreGausS2
    Image<uint8_t> bruitGausSigma15Conv13 = convertionImage(bruitGausSigma15);
    Image<uint8_t> filtreGausS2Conv13 = convertionImage(filtreGausS2);
    double MSEbruitGausSigma15filtreGausS2 = computeMSE(bruitGausSigma15Conv13,filtreGausS2);
    Image<double> imageConvbruitGausSigma15filtreGausS2 = convolution(bruitGausSigma15Conv13,filtreGausS2);
    Image<uint8_t> imagebruitGausSigma15filtreGausS2 = convertionImage(imageConvbruitGausSigma15filtreGausS2);
    double newMSEbruitGausSigma15filtreGausS2 = computeMSE(image,imageConvbruitGausSigma15filtreGausS2);
    printf("MSE entre bruitGausSigma15 et le filtreGausS2 sur l'image standart : %f \n",newMSEbruitGausSigma15filtreGausS2);
    writePGM(imagebruitGausSigma15filtreGausS2,"../../images/bruit/imagebruitGausSigma15filtreGausS2.pgm");

    // MSE pour le bruitGausSigma15 et le filtreMoyenneur3
    Image<uint8_t> bruitGausSigma15Conv14 = convertionImage(bruitGausSigma15);
    Image<uint8_t> filtreMoyenneur3Conv14 = convertionImage(filtreMoyenneur3);
    double MSEbruitGausSigma15filtreMoyenneur3 = computeMSE(bruitGausSigma15Conv14,filtreMoyenneur3);
    Image<double> imageConvbruitGausSigma15filtreMoyenneur3 = convolution(bruitGausSigma15Conv14,filtreMoyenneur3);
    Image<uint8_t> imagebruitGausSigma15filtreMoyenneur3 = convertionImage(imageConvbruitGausSigma15filtreMoyenneur3);
    double newMSEbruitGausSigma15filtreMoyenneur3 = computeMSE(image,imageConvbruitGausSigma15filtreMoyenneur3);
    printf("MSE entre bruitGausSigma15 et le filtreMoyenneur3 sur l'image standart : %f \n",newMSEbruitGausSigma15filtreMoyenneur3);
    writePGM(imagebruitGausSigma15filtreMoyenneur3,"../../images/bruit/imagebruitGausSigma15filtreMoyenneur3.pgm");

    // MSE pour le bruitGausSigma15 et le filtreMoyenneur7
    Image<uint8_t> bruitGausSigma15Conv15 = convertionImage(bruitGausSigma15);
    Image<uint8_t> filtreMoyenneur7Conv15 = convertionImage(filtreMoyenneur7);
    double MSEbruitGausSigma15filtreMoyenneur7 = computeMSE(bruitGausSigma15Conv15,filtreMoyenneur7);
    Image<double> imageConvbruitGausSigma15filtreMoyenneur7 = convolution(bruitGausSigma15Conv15,filtreMoyenneur7);
    Image<uint8_t> imagebruitGausSigma15filtreMoyenneur7 = convertionImage(imageConvbruitGausSigma15filtreMoyenneur7);
    double newMSEbruitGausSigma15filtreMoyenneur7 = computeMSE(image,imageConvbruitGausSigma15filtreMoyenneur7);
    printf("MSE entre bruitGausSigma15 et le filtreMoyenneur7 sur l'image standart : %f \n",newMSEbruitGausSigma15filtreMoyenneur7);
    writePGM(imagebruitGausSigma15filtreMoyenneur7,"../../images/bruit/imagebruitGausSigma15filtreMoyenneur7.pgm");

    // MSE pour le bruitGausSigma15 et le filtreMedian3
    Image<uint8_t> bruitGausSigma15Conv16 = convertionImage(bruitGausSigma15);
    Image<uint8_t> filtreMedian3Conv16 = convertionImage(filtreMedian3);
    double MSEbruitGausSigma15filtreMedian3 = computeMSE(bruitGausSigma15Conv16,filtreMedian3);
    Image<double> imageConvbruitGausSigma15filtreMedian3 = convolution(bruitGausSigma15Conv16,filtreMedian3);
    Image<uint8_t> imagebruitGausSigma15filtreMedian3 = convertionImage(imageConvbruitGausSigma15filtreMedian3);
    double newMSEbruitGausSigma15filtreMedian3 = computeMSE(image,imageConvbruitGausSigma15filtreMedian3);
    printf("MSE entre bruitGausSigma15 et le filtreMedian3 sur l'image standart : %f \n",newMSEbruitGausSigma15filtreMedian3);
    writePGM(imagebruitGausSigma15filtreMedian3,"../../images/bruit/imagebruitGausSigma15filtreMedian3.pgm");

    // MSE pour le bruitGausSigma15 et le filtreMedian7
    Image<uint8_t> bruitGausSigma15Conv17 = convertionImage(bruitGausSigma15);
    Image<uint8_t> filtreMedian7Conv17 = convertionImage(filtreMedian7);
    double MSEbruitGausSigma15filtreMedian7 = computeMSE(bruitGausSigma15Conv17,filtreMedian7);
    Image<double> imageConvbruitGausSigma15filtreMedian7 = convolution(bruitGausSigma15Conv17,filtreMedian7);
    Image<uint8_t> imagebruitGausSigma15filtreMedian7 = convertionImage(imageConvbruitGausSigma15filtreMedian7);
    double newMSEbruitGausSigma15filtreMedian7 = computeMSE(image,imageConvbruitGausSigma15filtreMedian7);
    printf("MSE entre bruitGausSigma15 et le filtreMedian7 sur l'image standart : %f \n",newMSEbruitGausSigma15filtreMedian7);
    writePGM(imagebruitGausSigma15filtreMedian7,"../../images/bruit/imagebruitGausSigma15filtreMedian7.pgm");

    // MSE pour le bruitGausSigma30 et le filtreGausS1
    Image<uint8_t> bruitGausSigma30Conv18 = convertionImage(bruitGausSigma30);
    Image<uint8_t> filtreGausS1Conv18 = convertionImage(filtreGausS1);
    double MSEbruitGausSigma30filtreGausS1 = computeMSE(bruitGausSigma30Conv18,filtreGausS1);
    Image<double> imageConvbruitGausSigma30filtreGausS1 = convolution(bruitGausSigma30Conv18,filtreGausS1);
    Image<uint8_t> imagebruitGausSigma30filtreGausS1 = convertionImage(imageConvbruitGausSigma30filtreGausS1);
    double newMSEbruitGausSigma30filtreGausS1 = computeMSE(image,imageConvbruitGausSigma30filtreGausS1);
    printf("MSE entre bruitGausSigma30 et le filtreGausS1 sur l'image standart : %f \n",newMSEbruitGausSigma30filtreGausS1);
    writePGM(imagebruitGausSigma30filtreGausS1,"../../images/bruit/imagebruitGausSigma30filtreGausS1.pgm");

    // MSE pour le bruitGausSigma30 et le filtreGausS2
    Image<uint8_t> bruitGausSigma30Conv19 = convertionImage(bruitGausSigma30);
    Image<uint8_t> filtreGausS2Conv19 = convertionImage(filtreGausS2);
    double MSEbruitGausSigma30filtreGausS2 = computeMSE(bruitGausSigma30Conv19,filtreGausS2);
    Image<double> imageConvbruitGausSigma30filtreGausS2 = convolution(bruitGausSigma30Conv19,filtreGausS2);
    Image<uint8_t> imagebruitGausSigma30filtreGausS2 = convertionImage(imageConvbruitGausSigma30filtreGausS2);
    double newMSEbruitGausSigma30filtreGausS2 = computeMSE(image,imageConvbruitGausSigma30filtreGausS2);
    printf("MSE entre bruitGausSigma30 et le filtreGausS2 sur l'image standart : %f \n",newMSEbruitGausSigma30filtreGausS2);
    writePGM(imagebruitGausSigma30filtreGausS2,"../../images/bruit/imagebruitGausSigma30filtreGausS2.pgm");

    // MSE pour le bruitGausSigma30 et le filtreMoyenneur3
    Image<uint8_t> bruitGausSigma30Conv20 = convertionImage(bruitGausSigma30);
    Image<uint8_t> filtreMoyenneur3Conv20 = convertionImage(filtreMoyenneur3);
    double MSEbruitGausSigma30filtreMoyenneur3 = computeMSE(bruitGausSigma30Conv20,filtreMoyenneur3);
    Image<double> imageConvbruitGausSigma30filtreMoyenneur3 = convolution(bruitGausSigma30Conv20,filtreMoyenneur3);
    Image<uint8_t> imagebruitGausSigma30filtreMoyenneur3 = convertionImage(imageConvbruitGausSigma30filtreMoyenneur3);
    double newMSEbruitGausSigma30filtreMoyenneur3 = computeMSE(image,imageConvbruitGausSigma30filtreMoyenneur3);
    printf("MSE entre bruitGausSigma30 et le filtreMoyenneur3 sur l'image standart : %f \n",newMSEbruitGausSigma30filtreMoyenneur3);
    writePGM(imagebruitGausSigma30filtreMoyenneur3,"../../images/bruit/imagebruitGausSigma30filtreMoyenneur3.pgm");

    // MSE pour le bruitGausSigma30 et le filtreMoyenneur7
    Image<uint8_t> bruitGausSigma30Conv21 = convertionImage(bruitGausSigma30);
    Image<uint8_t> filtreMoyenneur7Conv21 = convertionImage(filtreMoyenneur7);
    double MSEbruitGausSigma30filtreMoyenneur7 = computeMSE(bruitGausSigma30Conv21,filtreMoyenneur7);
    Image<double> imageConvbruitGausSigma30filtreMoyenneur7 = convolution(bruitGausSigma30Conv21,filtreMoyenneur7);
    Image<uint8_t> imagebruitGausSigma30filtreMoyenneur7 = convertionImage(imageConvbruitGausSigma30filtreMoyenneur7);
    double newMSEbruitGausSigma30filtreMoyenneur7 = computeMSE(image,imageConvbruitGausSigma30filtreMoyenneur7);
    printf("MSE entre bruitGausSigma30 et le filtreMoyenneur7 sur l'image standart : %f \n",newMSEbruitGausSigma30filtreMoyenneur7);
    writePGM(imagebruitGausSigma30filtreMoyenneur7,"../../images/bruit/imagebruitGausSigma30filtreMoyenneur7.pgm");

    // MSE pour le bruitGausSigma30 et le filtreMedian3
    Image<uint8_t> bruitGausSigma30Conv22 = convertionImage(bruitGausSigma30);
    Image<uint8_t> filtreMedian3Conv22 = convertionImage(filtreMedian3);
    double MSEbruitGausSigma30filtreMedian3 = computeMSE(bruitGausSigma30Conv22,filtreMedian3);
    Image<double> imageConvbruitGausSigma30filtreMedian3 = convolution(bruitGausSigma30Conv22,filtreMedian3);
    Image<uint8_t> imagebruitGausSigma30filtreMedian3 = convertionImage(imageConvbruitGausSigma30filtreMedian3);
    double newMSEbruitGausSigma30filtreMedian3 = computeMSE(image,imageConvbruitGausSigma30filtreMedian3);
    printf("MSE entre bruitGausSigma30 et le filtreMedian3 sur l'image standart : %f \n",newMSEbruitGausSigma30filtreMedian3);
    writePGM(imagebruitGausSigma30filtreMedian3,"../../images/bruit/imagebruitGausSigma30filtreMedian3.pgm");

    // MSE pour le bruitGausSigma30 et le filtreMedian7
    Image<uint8_t> bruitGausSigma30Conv23 = convertionImage(bruitGausSigma30);
    Image<uint8_t> filtreMedian7Conv23 = convertionImage(filtreMedian7);
    double MSEbruitGausSigma30filtreMedian7 = computeMSE(bruitGausSigma30Conv23,filtreMedian7);
    Image<double> imageConvbruitGausSigma30filtreMedian7 = convolution(bruitGausSigma30Conv23,filtreMedian7);
    Image<uint8_t> imagebruitGausSigma30filtreMedian7 = convertionImage(imageConvbruitGausSigma30filtreMedian7);
    double newMSEbruitGausSigma30filtreMedian7 = computeMSE(image,imageConvbruitGausSigma30filtreMedian7);
    printf("MSE entre bruitGausSigma30 et le filtreMedian7 sur l'image standart : %f \n",newMSEbruitGausSigma30filtreMedian7);
    writePGM(imagebruitGausSigma30filtreMedian7,"../../images/bruit/imagebruitGausSigma30filtreMedian7.pgm");

    return 0;
}
