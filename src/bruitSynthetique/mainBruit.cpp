/*

    Pour compiler le fichier
    g++ mainFiltreMedian.cpp -o mainFiltreMedian

    ./mainFiltreMedian images/base/boat.pgm

*/

#include <fstream>
#include <iostream>
#include "../image.h"
#include <cstdint>
#include "../fileio.hpp"

int main(int argc,const char * argv[]){

    // if (argc != 2){
    //     std::cout << "Vous devez appelez le programme " << argv[0] << " avec 2 arguments \n";
    //     std::cout<< "Par exemple : \n" << argv[0] << " boat.pgm \n";
    //     system("pause");
    //     exit(EXIT_FAILURE);
    // }



    std::string imageEntre = argv[1];
    Image<uint8_t> image = readPGM(imageEntre);

    uint8_t matrice[9]  = {
                            140,140,140,
                            140,140,140,
                            140,140,140
                        };

    uint8_t matrice1[9]  = {
                            0,140,0,
                            140,140,140,
                            0,140,0
                        };

    Image<uint8_t> imageSimple(3,3,matrice);
    Image<uint8_t> imageSimple2(3,3,matrice1);

    Image<double> imageSimpleN = createSimpleImage(20);
    // imageSimple.print();

    // Image<uint8_t> bruitImp1 = bruitImpulsionnel(image,0.5);
    // Image<uint8_t> bruitImp2 = bruitImpulsionnel(image,0.2);
    // Image<uint8_t> bruitImp8 = bruitImpulsionnel(image,0.8);

    // Image<uint8_t> bruitGausSigma01 = bruitGaussien(image,0.0,0.1);
    // Image<uint8_t> bruitGausSigma15 = bruitGaussien(image,0.0,15);
    // Image<uint8_t> bruitGausSigma25 = bruitGaussien(image,0.0,25);
    //
    // Image<double> bruitGausSigma01Mu5 = bruitGaussien(image,5.0,0.1);
    // Image<double> bruitGausSigma15Mu5 = bruitGaussien(image,5.0,15);
    // Image<double> bruitGausSigma25Mu5 = bruitGaussien(image,5.0,25);

    // Image<uint8_t> BGS1 = convertionImage(bruitGausSigma01Mu5);
    // Image<uint8_t> BGS2 = convertionImage(bruitGausSigma15Mu5);
    // Image<uint8_t> BGS3 = convertionImage(bruitGausSigma25Mu5);

    // double MSE1 = computeMSE(image,bruitImp1);
    // double MSE2 = computeMSE(image,bruitImp2);
    // double MSE3 = computeMSE(image,bruitImp8);
    // double MSE = computeMSE(imageSimple,imageSimple);
    // double MSESimple = computeMSE(imageSimple,imageSimple2);
    //
    //
    // printf("Image Simple 1 \n"); imageSimple.print();
    // printf("Image Simple 2 \n"); imageSimple.print();
    //
    // printf("Différence : %f \n",MSE);
    //
    // printf("Deuxième test \n");
    // printf("Image Simple 1\n"); imageSimple.print();
    // printf("Image Simple 2\n"); imageSimple2.print();
    //
    // printf("différence : %f\n",MSESimple );


    // bruitImp1.print();

    // Image<uint8_t> fenetreMasque2(3,3,matrice2);
    // Image<uint8_t> fenetreMasque3(3,3,matrice3);
    //
    // // Filtre Médian
    Image<uint8_t> simpleImageNConv = convertionImage(imageSimpleN);
    Image<double> filtreMedianResultat1 = filtreMedian(simpleImageNConv,imageSimple);
    // Image<uint8_t> filtreMedianResultat2 = filtreMedian(image,fenetreMasque2);
    // Image<uint8_t> filtreMedianResultat3 = filtreMedian(image,fenetreMasque3);

    simpleImageNConv.print();
    printf("Transformation\n");
    filtreMedianResultat1.print();
    // Filtre Médian
    // writePGM(filtreMedianResultat1,"images/filtreMedian/filtreMedianResultat1.pgm");
    // writePGM(filtreMedianResultat2,"images/filtreMedian/filtreMedianResultat2.pgm");
    // writePGM(filtreMedianResultat3,"images/filtreMedian/filtreMedianResultat3.pgm");
    //

    // Restauration
    //
    // writePGM(bruitImp1,"../images/bruit/bruitImpulsion0.5.pgm");
    // writePGM(bruitImp2,"../images/bruit/bruitImpulsion0.2.pgm");
    // writePGM(bruitImp8,"../images/bruit/bruitImpulsion0.8.pgm");
    //
    // writePGM(bruitGausSigma01,"../images/bruit/bruitGausSigma01.pgm");
    // writePGM(bruitGausSigma15,"../images/bruit/bruitGausSigma15.pgm");
    // writePGM(bruitGausSigma25,"../images/bruit/bruitGausSigma25.pgm");


    // writePGM(BGS1,"../../images/bruit/bruitGausSigma01Mu5.pgm");
    // writePGM(BGS2,"../../images/bruit/bruitGausSigma15Mu5.pgm");
    // writePGM(BGS3,"../../images/bruit/bruitGausSigma25Mu5.pgm");

    // writePGM(MSE1,"../images/bruit/MSE1.pgm");
    // writePGM(MSE2,"../images/bruit/MSE2.pgm");
    // writePGM(MSE3,"../images/bruit/MSE3.pgm");
    //
    //

    // On fait le redimenssionnage
    //Image<double> imageFinale = convolution(image,matriceIdentite);

    //writePGM(imageFinale,imageSortie);

    return 0;
}
