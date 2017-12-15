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
                            140,140,140,
                            140,139,140,
                            140,140,140
                        };

    uint8_t matrice2[9]  = {
                            140,140,140,
                            140,0,140,
                            140,140,140
                        };

    uint8_t matrice3[9]  = {
                            140,140,140,
                            140,0,140,
                            140,140,140
                        };

    uint8_t matrice4[9]  = {
                            0,140,140,
                            140,0,140,
                            140,140,0
                        };

    uint8_t matrice5[9]  = {
                            0,140,140,
                            140,0,140,
                            140,140,0
                        };




    Image<uint8_t> imageSimple(3,3,matrice);
    Image<uint8_t> imageSimple2(3,3,matrice1);
    Image<uint8_t> imageSimple25(10,10);

    for(int i = 0; i<10;i++){
        for(int j = 0;j<10;j++){
            imageSimple25(i,j) = 255;
            if (((i%2)==0)&&(j%2)==0){
                imageSimple25(i,j) = 0;
            }
        }
    }

    Image<double> ImageGaussSimple = gaussienMask(3);
    Image<double> ImageGaussSimple2 = gaussienMask(7);

    Image<double> bruitSimple = convolution(imageSimple25,ImageGaussSimple);
    Image<double> bruitSimple2 = convolution(imageSimple25,ImageGaussSimple);

    Image<uint8_t> c1 = convertionImage(bruitSimple);
    Image<uint8_t> c2 = convertionImage(bruitSimple2);
    writePGM(imageSimple25,"../../images/simple.pgm");
    writePGM(c1,"../../images/simpleAvecGauss3.pgm");
    writePGM(c2,"../../images/simpleAvecGauss7.pgm");
    double sim = 0;
    double w = 0;
    for(int i = 0;i<imageSimple.getDx();i++){
        for(int j = 0;j<imageSimple.getDy();j++){
            for(int k = 0; k<imageSimple2.getDx();k++){
                for(int l = 0;l<imageSimple2.getDy();l++){
                    sim += computeSimilarity(i,j,k,l,3,imageSimple2);
                    w = computeWeight(i,j,k,l,3,50,imageSimple2);
                    printf("Position : (i:%d,j:%d)\t(k:%d,l:%d)\tPoids : %f\n",i,j,k,l,w);
                }
            }
        }
    }

    printf("Similarity %f\n",sim);

    Image<uint8_t> imageSimple3(3,3,matrice2);
    sim = 0;
    w = 0;
    for(int i = 0;i<imageSimple.getDx();i++){
        for(int j = 0;j<imageSimple.getDy();j++){
            for(int k = 0; k<imageSimple3.getDx();k++){
                for(int l = 0;l<imageSimple3.getDy();l++){
                    sim += computeSimilarity(i,j,k,l,3,imageSimple3);
                }
            }
        }
    }

    printf("Similarity %f\n",sim);

    Image<uint8_t> imageSimple4(3,3,matrice3);
    sim = 0;
    w = 0;
    for(int i = 0;i<imageSimple.getDx();i++){
        for(int j = 0;j<imageSimple.getDy();j++){
            for(int k = 0; k<imageSimple4.getDx();k++){
                for(int l = 0;l<imageSimple4.getDy();l++){
                    sim += computeSimilarity(i,j,k,l,3,imageSimple4);
                }
            }
        }
    }

    printf("Similarity %f\n",sim);

    Image<uint8_t> imageSimple5(3,3,matrice4);
    sim = 0;
    w = 0;
    for(int i = 0;i<imageSimple.getDx();i++){
        for(int j = 0;j<imageSimple.getDy();j++){
            for(int k = 0; k<imageSimple5.getDx();k++){
                for(int l = 0;l<imageSimple5.getDy();l++){
                    sim += computeSimilarity(i,j,k,l,3,imageSimple5);
                }
            }
        }
    }

    printf("Similarity %f\n",sim);

    printf("Image Simple de 5X5 \n");
    imageSimple25.print();

    Image<uint8_t> computeNLMeansSigma10 = computeNlMeans(imageSimple25,7,3,50);
    Image<uint8_t> computeNLSimpleC1 = computeNlMeans(c1,21,7,50);
    Image<uint8_t> computeNLSimpleC2 = computeNlMeans(c2,21,7,50);
    Image<uint8_t> computeNLSimple2C1XS = computeNlMeans(c1,3,3,50);
    Image<uint8_t> computeNLSimple2C2XS = computeNlMeans(c2,3,3,50);
    printf("Image synthétique fait avec le ComputeNLMEANS Fenêtre de patchSize %d & windows Size %d \n",21,7);
    computeNLSimpleC1.print();
    printf("Image synthétique fait avec le ComputeNLMEANS Fenêtre de patchSize %d & windows Size %d \n",21,7);
    computeNLSimpleC2.print();
    printf("Image synthétique fait avec le ComputeNLMEANS Fenêtre de patchSize %d & windows Size %d \n",3,3);
    computeNLSimple2C1XS.print();
    printf("Image synthétique fait avec le ComputeNLMEANS Fenêtre de patchSize %d & windows Size %d \n",3,3);
    computeNLSimple2C2XS.print();

    writePGM(computeNLSimpleC1,"../../images/computeNLSimpleC1.pgm");
    writePGM(computeNLSimpleC2,"../../images/computeNLSimpleC2.pgm");
    writePGM(computeNLSimple2C1XS,"../../images/computeNLSimple2C1XS.pgm");
    writePGM(computeNLSimple2C2XS,"../../images/computeNLSimple2C2XS.pgm");
    // Image<uint8_t> computeNLMeansSigma15 = computeNlMeans(imageGaussSigma15,21,7,50);
    // Image<uint8_t> computeNLMeansSigma25 = computeNlMeans(imageGaussSigma25,21,7,50);


    // writePGM(computeNLMeansSigma10,"../images/debruit/computeNLMeansSigma10.pgm");
    // writePGM(computeNLMeansSigma15,"../images/debruit/computeNLMeansSigma15.pgm");
    // writePGM(computeNLMeansSigma25,"../images/debruit/computeNLMeansSigma25.pgm");
    //

    //writePGM(imageFinale,imageSortie);

    return 0;
}
