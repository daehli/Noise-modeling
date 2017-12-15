/*

    Pour compiler le fichier
    g++ mainFiltreMedian.cpp -o mainFiltreMedian

    ./mainFiltreMedian images/base/boat.pgm
    http://stackoverflow.com/questions/10408816/how-do-i-use-the-nohup-command-without-getting-nohup-out
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

    // Image<uint8_t> bruitGausSigma10 = bruitGaussien(image,0.0,10);
    // Image<uint8_t> bruitGausSigma15 = bruitGaussien(image,0.0,15);
    // Image<uint8_t> bruitGausSigma25 = bruitGaussien(image,0.0,25);

    Image<double> bruitGausSigma01Mu5 = bruitGaussien(image,5.0,0.1);
    Image<double> bruitGausSigma15Mu5 = bruitGaussien(image,5.0,15);
    Image<double> bruitGausSigma25Mu5 = bruitGaussien(image,5.0,25);

    Image<uint8_t> BGS1 = convertionImage(bruitGausSigma01Mu5);
    Image<uint8_t> BGS2 = convertionImage(bruitGausSigma15Mu5);
    Image<uint8_t> BGS3 = convertionImage(bruitGausSigma25Mu5);

    Image<uint8_t> computeNLMeansSigma10 = computeNlMeans(BGS1,7,3,50);
    Image<uint8_t> computeNLMeansSigma15 = computeNlMeans(BGS2,21,7,50);
    Image<uint8_t> computeNLMeansSigma25 = computeNlMeans(BGS3,21,7,50);

    writePGM(computeNLMeansSigma10,"../../images/debruit/computeNLMeansSigma10.pgm");
    writePGM(computeNLMeansSigma15,"../../images/debruit/computeNLMeansSigma15.pgm");
    writePGM(computeNLMeansSigma25,"../../images/debruit/computeNLMeansSigma25.pgm");
    //

    //writePGM(imageFinale,imageSortie);

    return 0;
}
