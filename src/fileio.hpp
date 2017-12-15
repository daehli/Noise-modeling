#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>
#include <vector>
#include "image.h"

//////////////////////////////
/*
    Déclaration des fonctions pour l'interpréteur
*/
//////////////////////////////
Image<uint8_t> quantize(Image<uint8_t> &imageSource,uint8_t puissance);
Image<uint8_t> readPGM(const std::string &inputFile);
int writePGM(const Image<uint8_t> &image, const std::string &outputFile);
Image<double> filtreMedian(Image<uint8_t>& imageEntre,Image<double>& masque);
Image<double> gaussienMask(double sigma);
Image<uint8_t> computeNlMeans(Image<uint8_t>imageEntre, int patchSize, int windowSize, double h);
double computeWeight(int x1, int y1, int x2, int y2, int patchSize, double h,Image<uint8_t> imageEntre);
double computeSimilarity(int x1, int y1, int x2, int y2, Image<uint8_t>imageEntre);
Image<uint8_t> convertionImage(Image<double>& imageEntree);
Image<double> convolution(Image<uint8_t>& imageEntre,Image<double>& masque);
double computeMSE(Image<uint8_t> I,Image<double>IPrime);
Image<double> createSimpleImage(int n);

//////////////////////////////
/*

    Corps des fonctions

*/
//////////////////////////////

Image <uint8_t> readPGM(const std::string &inputFile)
{
    Image <uint8_t> result;
    std::ifstream file(inputFile);
    if(file.is_open()) {
        std::string line;
        std::getline(file,line);
        // only binary, greyscale PGM
        if(line=="P5") {
            int dx,dy,maxValue;
            std::getline(file,line);
            // remove comments beginning by '#'
            while(line[0]=='#')
                std::getline(file,line);
            std::stringstream ss(line);
            ss >> dx >> dy;
            std::getline(file,line);
            ss.clear();
            ss.str(line);
            ss>>maxValue;
            std::cout << "Reading header.\nFile "<<inputFile<< "\ndx : "  << dx << "\ndy : " <<dy << "\nmaxValue : " << maxValue << "\n";
            int size=dx*dy;
            uint8_t *buffer=new uint8_t[size];
            file.read((char *)buffer,size);
            Image <uint8_t> result(dx,dy,buffer);
            delete[] buffer;
            return result;

        }
        file.close();
    }

    return result;
}

int writePGM(const Image<uint8_t> &image, const std::string &outputFile)
{
    std::ofstream file(outputFile,std::ios_base::trunc  | std::ios_base::binary);
    if(file.is_open()) {
        std::string line;

        int dx=image.getDx();
        int dy=image.getDy();
        int size=dx*dy;

        file << "P5\n" << dx << " " << dy << "\n" << "255" ;
        file << "\n";

        file.write((char *)image.getData(),size);

        file << "\n";

        file.close();
    }
    else return -1;

    return 0;
}

Image<double> filtreMedian(Image<uint8_t>& imageEntre,Image<double>& masque)
{

    Image<double> imageSortie(imageEntre.getDx(),imageEntre.getDy());
    int dim = masque.getSize()/2;

    if ((dim%2)==0)
        dim++;
    // Mettre les elements de la
    std::vector<double> listeFenetre;
    // Parcours de l'image
    for(int x = 0;x<imageEntre.getDx();x++){
        for(int y = 0;y<imageEntre.getDy();y++){
            for(int i = -dim;i<=dim;i++){
                for(int j = -dim;j<=dim;j++){
                    int indeX = x+i;
                    int indeY = y+j;
                    // Débordement
                    if(indeX >= 0 && indeY >= 0 && indeX <= imageEntre.getDx()-1 && indeY <= imageEntre.getDy()-1){

                        double value = imageEntre(indeX,indeY);
                        // printf("Value dans le FiltreMedian %f \n",value);
                        listeFenetre.push_back(value);
                    }
                }
            }

            sort(listeFenetre.begin(),listeFenetre.end());
            int positionTrier = listeFenetre.size()/2;
            double val = listeFenetre.at(positionTrier);
            // printf("Position x : %d \t y: %d \t Value trouvé dans le vecteur %f\n",x,y,val);
            imageSortie(x,y) = val;
            listeFenetre.clear();
        }
    }

    return imageSortie;
}

Image<double> bruitImpulsionnel(Image<uint8_t> imageEntre,double probabilite)
{
        double random;
        double random1;
        double blackOrWhite = 0.5;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        Image<double> imageResultat(imageEntre.getDx(),imageEntre.getDy());

        for(int x = 0; x<imageEntre.getDx();x++){
            for(int y = 0;y<imageEntre.getDy();y++){
                random = dis(gen);
                if(probabilite >= random){
                    random1 = dis(gen);
                    // printf("%f \n",random1);
                    // Blanc
                    if(blackOrWhite>random1){
                        // printf("BlackOrWhite : %f \t random : %f \n",blackOrWhite,random1)  ;
                        imageResultat(x,y) = 255;
                    } else{
                        imageResultat(x,y) = 0;
                    }
                }
                else
                    imageResultat(x,y) = imageEntre(x,y);
            }
        }
        return imageResultat;
}

Image<double> bruitGaussien(Image<uint8_t> imageEntre,double mu,double sigma)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // std::uniform_real_distribution<> dis(0, 1);
    Image<double> imageResultat(imageEntre.getDx(),imageEntre.getDy());
    // Les paramètres de la distribution sont mu et sigma respectivement.
    std::normal_distribution<double> distribution (mu,sigma);

    for(int x = 0; x<imageEntre.getDx();x++){
        for(int y = 0;y<imageEntre.getDy();y++){
            double gauss = distribution(gen);
            // printf("gauss Avec valeur des pixels: %f \n",(gauss+imageEntre(x,y)));
            int value = (gauss + imageEntre(x,y));
            // Troncage
            if(value>255)
                {
                    // printf("Débordement de plus de 255 \n");
                    imageResultat(x,y) = 255;
                    // printf("\nImage : %i\n",imageResultat(x,y));
                }
            else if(value < 0){
                // printf("Débordement inférieur à 0 \n");
                imageResultat(x,y) = 0;
                // printf("\nImage : %i\n",imageResultat(x,y));
            }
            imageResultat(x,y) = value ;
        }
    }
    return imageResultat;
}


/*

    Les images doivent avoir la même taille.

*/

double computeMSE(Image<uint8_t> I,Image<double>IPrime)
{
    int n = I.getDx();
    int m = I.getDy();
    double sum = 0.0;
    for(int x = 0; x<I.getDx();x++){
        for(int y = 0;y<I.getDy();y++){
            double Icoor = I(x,y);
            double IcoorPrime = IPrime(x,y);
            double carre = pow((Icoor - IcoorPrime),2);
            sum += carre;
        }
    }
    return sum/n*m;
}


Image<double> gaussienMask(double sigma){

    int N = floor(6*sigma); // Environ 6 sigma

    // Convention si N est Paire. On va chercher la valeurs suivante
    // Modulo pour les doubles
    if((N%2)==0)
        N++;
    Image<double> masqueGaussien(N,N);
    int moitier = N/2;
    double somme = 0.0;

    for (int x = -moitier ; x <= moitier;x++){
        for(int y = -moitier ; y<= moitier;y++){
            // On remets au carre les coordonnées
            // Formule Mathématique pour le masque
            masqueGaussien(x+moitier,y+moitier) =  (exp(-(x*x + y*y)/(2.0*(sigma*sigma)))) / (M_PI*(2.0*(sigma*sigma)));
            somme += masqueGaussien(x+moitier,y+moitier);
        }
    }

    // Ensuite on Renormalisation

    for(int x=0;x<N;x++){
        for(int y=0;y<N;y++){
            masqueGaussien(x,y) /= somme;
        }
    }

    return masqueGaussien;
}


double computeSimilarity(int x1, int y1, int x2, int y2, int patchSize, Image<uint8_t>imageEntre)
{
  double res = 0.0;
  // Étape 1. D >= 0
  // et 2*d + 1 = -D->D
  for(int i = -(patchSize/2); i < patchSize/2; ++i){
    for(int j = -(patchSize/2); j < patchSize/2; ++j){
      if(x1+j >=0 && x1+j <imageEntre.getDx() && y1+i >=0 && y1+i <imageEntre.getDy() && x2+j >=0 && x2+j <imageEntre.getDx() && y2+i >=0 && y2+i <imageEntre.getDy())
        // Étape 2. Norme euclidienne
          res += pow((imageEntre(x1+j, y1+i) - imageEntre(x2+j, y2+i)), 2.0);
        //   printf("%i:\tCompute Similarity\n",count);
    }
  }
  return res;
}


double computeWeight(int x1, int y1, int x2, int y2, int patchSize, double h,Image<uint8_t> imageEntre)
{
    // Étape 3. On fixe un réel H et on appel notre fonction computeSimilarity.
  return exp(-(computeSimilarity(x1,y1,x2,y2,patchSize,imageEntre)/(h*h)));
}


Image<uint8_t> computeNlMeans(Image<uint8_t>imageEntre, int patchSize, int windowSize, double h)
{

    Image<uint8_t> imageResult(imageEntre.getDx(), imageEntre.getDy());
    double w = 0;
    // Fenêtre de notre image
    for (int i = 0; i < imageEntre.getDx(); i++) {
      for (int j = 0; j < imageEntre.getDy(); j++) {
        double sumWeights=0.0;
        double value=0.0;
        double weightMax=0;
        // Patch à comparer
        for (int k = 0; k < windowSize; k++) {
          for (int l = 0; l < windowSize; l++) {
            // Si les images ne sont pas au même endroit
            if (imageEntre(i, j) != imageEntre(k, l)) {
                // Étape 4. Somme les contributions des mesures de similarité
              w = computeWeight(i,j, k, l,patchSize,h,imageEntre);

              weightMax = fmax(weightMax,w);

              sumWeights += w;
              //   Étape 5. Définition des poids selon les images
              value += w * imageEntre(k, l);

            }
          }
        }
        value += weightMax * imageEntre(i,j);
        sumWeights += weightMax;
        value /= sumWeights;
        imageResult(i,j)=value;
      }
    }
    return imageResult;

  }

 Image<uint8_t> convertionImage(Image<double>& imageEntree){

      int imaX = imageEntree.getDx();
      int imaY = imageEntree.getDy();
      Image<uint8_t> imageSortie(imaX,imaY);
      for (int x = 0 ; x < imaX; x++) {
          for (int y = 0; y < imaY; y++) {
                  imageSortie(x,y) = (uint8_t) imageEntree(x,y);
              }
          }

          return imageSortie;
  }


  Image<double> convolution(Image<uint8_t>& imageEntre,Image<double> &masque)
  {

      int ImaX = imageEntre.getDx();
      int ImaY = imageEntre.getDy();
      // Avoir le centre de notre masque
      int MasqueX = (masque.getDx()/2);
      int MasqueY = (masque.getDy()/2);
      Image<double> imageFinale(ImaX,ImaY);

      // On itère sur tout les pixels de l'image
      // Pour chaque ligne
      // On prend chaque pixels
      for (int x = 0;x<ImaX;x++){
          // Ensuite on change de colonne
          for(int y = 0; y<ImaY;y++){
              // Valeur calculer pour chaque pixel de l'image
              double accumulator = 0;

              // Pour chaque colonne de notre mask
              /*

                 -1 0 1
                 -1 |0|0|0|
                 0  |0|0|0|
                 1  |0|0|0|

                 Voici comment la boucle du masque fonctionne

  */
              for(int i = -MasqueX;i <= MasqueX; i++){
                  // On prend chaque Pixel
                  for(int j = -MasqueY;j <= MasqueY; j++){
                      int indeX = x+i;
                      int indeY = y+j;
                      // Si l'index n'est pas compris dans l'image
                      if ( indeX < 0 || indeY < 0 || indeX >= ImaX-1 || indeY >= ImaY-1){
                          // On lui donne la valeur Zero
                          accumulator +=0;
                      }
                      accumulator += masque(i+MasqueX,j+MasqueY)*imageEntre(indeX,indeY);
                  }
              }
              imageFinale(x,y) = accumulator;
          }
      }
      return imageFinale;
  }

Image<double> moyenneur(int N)
{

    int grandeur = 2*N+1;

    double val = 1.0/double(grandeur*grandeur);

    Image<double> imageFinale(grandeur,grandeur);

    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            imageFinale(i,j) = val;
        }
    }
    return imageFinale;

}

Image<double> createSimpleImage(int n){
    Image<double> imageSimple25(n,n);

    for(int i = 0; i<n;i++){
        for(int j = 0;j<n;j++){
            imageSimple25(i,j) = 255;
            if (((i%2)==0)||(j%2)==0){
                imageSimple25(i,j) = ((i*j)+ 20)%255;
            }
        }
    }

    return imageSimple25;

}
