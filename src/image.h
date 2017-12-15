//
//  image.h
//  tp-P4y
//
//  Created by Benoit Naegel on 25/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#ifndef image_h
#define image_h

template<class T>
class Image {
    /// classe générique codant une image de type T. T doit être précisé lors de l'instanciation.
    /// Exemple :
    /// Image<uint8_t> image(10,5);  // instancie une image dont les pixels sont de type uint8_t, de taille 10x5
    /// Image<float> image(512,512); // instancie une image dont les pixels sont de type float, de taille 512x512

private:
    int dx; /// largeur
    int dy; /// hauteur
    int size; /// nombre de pixels de l'image
    T *data; /// Pointeur vers les valeurs des pixels de l'image. Les pixels sont stockés ligne par ligne.
             /// Les valeurs des pixels ont le type T, qui est le paramètre de la classe générique.
             /// Par exemple, dans le cas d'une image 8 bits, le type est Image<uint8_t> et les valeurs ont toutes le type uint8_t

public:
    /// construit une image de taille (dx,dy) (par défaut 0) avec le buffer data (optionnel)
    Image(int dx=0, int dy=0, T *data=0);

    /// constructeur de copie, permettant d'écrire Image B; Image A(B);
    Image(const Image& image);

    /// opérateur d'affectation permettant d'écrire Image B; Image A=B;
    Image& operator=(const Image&);

    ///destructeur : instructions pour désallouer les ressources de la classe (ici, le pointeur data)
    ~Image();
    int getDx() const;
    int getDy() const;
    int getSize() const;
    T *getData() const;

    /// affiche sur la sortie standard la valeur des pixels de l'image
    void print() const;

    /// surcharge de l'opérateur () permettant d'écrire une valeur à la position (x,y) : A(x,y)=v
    T &operator()(const int &x, const int &y);
    /// surcharge de l'opérateur () permettant de lire une valeur à la position (x,y) : v=A(x,y)
    T operator()  (const int &x, const int &y) const;
};

#include "image.hpp"

#endif /* image_h */
