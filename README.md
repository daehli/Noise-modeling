# Modélisation du bruit - filtre des moyennes non locales


Réalisé par **Daehli Nadeau-Otis**  


## Bruit synthétique  

Il est possible d'ajouter du bruit sur une image. Le `bruitImpulsionnel`  permet d'ajouter des pixels noir et blanc selon une probabilité. La probabilité envoyée en paramètre doit être compris entre $`0 \leq p \leq 1`$.  

```c++
// C++11
#include <random>
double nonRealisable;
std::random_device rd; // Graine
std::mt19937 gen(rd()); // Génération de la graine
std::uniform_real_distribution<> dis(0, 1); // Valeur comprise entre 0 & 1
nonRealisable = dis(gen); // Valeur pour comparer avec notre probabilité
```

À titre d'exemple pour démontrer le fonctionnement de la fonction. La matrice de base va être.
```math
M_1 =
\begin{bmatrix}
140 & 140 & 140\\
140 & 140 & 140\\
140 & 140 & 140
\end{bmatrix}
```

La $`M_1`$ va être passer dans la [fonction](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP5/src/fileio.hppL128-157) suivante. Elle va être traitée et la matrice $`M_1`$ va devenir la matrice résultante $`M^\prime_1`$. La fonction a été faite avec une probabilité de `0.5`.

```math
M^\prime_1 =
\begin{bmatrix}
0 & 0 & 140\\
0 & 140 & 0\\
0 & 0 & 255
\end{bmatrix}
```

Il est aussi possible d'appliquer les résultats sur des images en niveau de gris.  

|Original|`0.2`|`0.5`|`0.8`|
|---|---|---|---|
|![alt text][barbara]|![alt text][bruitImpulsion0.2]|![alt text][bruitImpulsion0.5]|![alt text][bruitImpulsion0.8]

On observe que le bruit impulsionnel créer un effet de poivre et sel sur les images. Ce type de bruit est facile à éliminer.

La prochaine fonction à être implémentée est le `bruitGaussien`. Le bruit gaussien permet d'ajouter une valeur générée par une loi normale. Cette loi normale est paramétrée par $`\mu`$ et $`\sigma`$. Le résultat obtenu sur une image en gris devrait être un effet de flou.

La loi de probabilité gaussienne est $`\mathcal{N}(\mu,\sigma^2)`$. Plus $`\sigma`$ est grand , plus les pixels seront rassemblés dans la pointe de $`\sigma`$.

|Originale avec $`\mu=0`$|$`\sigma 0.1`$|$`\sigma 15`$|$`\sigma 25`$|
|---|---|---|---|
|![alt text][barbara]|![alt text][bruitGausSigma1]|![alt text][bruitGausSigma15]|![alt text][bruitGausSigma25]

|Originale avec $`\mu=5`$|$`\sigma 0.1`$|$`\sigma 15`$|$`\sigma 25`$|
|---|---|---|---|
|![alt text][barbara]|![alt text][bruitGausSigma01Mu5]|![alt text][bruitGausSigma15Mu5]|![alt text][bruitGausSigma25Mu5]  

On observe l'effet de flou. Lorsque $`\sigma`$ augmente, l'effet de floue est plus accentué.

### MSE  

Le mean square error `MSE` est une fonction qui compare 2 images. Les images doivent être de même taille. L'une telle doit être différent de l'original. Par exemple, elle pourrait avoir été modifié par le filtre de gaussien.

Il suffit d'appliquer la formule mathématique suivante.  

```math
MSE(I,I^\prime) = \frac{ \sum_{x=1}^{N-1} \sum_{y=0}^{M-1}(I(x,y)-I^\prime
```  

Pour obtenir le `MSE`.

La démonstration suivante va permettre d'illustrer le fonctionnement de `MSE`.

La première matrice est représentée par $`M_1`$ et la deuxième matrice par $`M^\prime_1`$.
```math
M_1 =
\begin{bmatrix}
140 & 140 & 140\\
140 & 140 & 140\\
140 & 140 & 140
\end{bmatrix}
```
```math
M^\prime_1 =
\begin{bmatrix}
0 & 140 & 0\\
140 & 140 & 140\\
0 & 0 & 0
\end{bmatrix}
```

La première matrice a été comparée à elle-même. Le résultat devrait être 0 puisque la matrice est identique. Le deuxième exemple devrait être différent, puisque  $`M_1`$ est comparé avec $`M^\prime_1`$.

```c++
// Construction des matrices
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
// Transformation des matrices en images
Image<uint8_t> imageSimple(3,3,matrice);
Image<uint8_t> imageSimple2(3,3,matrice1);
// Comparaison avec les matrices
double MSE = computeMSE(imageSimple,imageSimple);
printf("Différence : %f \n",MSE);
// Résultat attendu : 0
// Résultat obtenu : 0
double MSESimple = computeMSE(imageSimple,imageSimple2);
printf("différence : %f\n",MSESimple );
// Résultat attendu : < 0
// Résultat obtenu : 78400.000000
```

## Test  

La série de tests s’est révélée très révélatrice. Elle permettait d'observer les meilleurs filtres et ceux qui étaient moins efficaces pour réduire le bruit sur une image. Le tableau suivant illustre chacun des bruits et filtre. Lorsqu'un filtre et un bruit sont dans la même ligne et colonne. L’image a été convoluée avec le filtre et le bruit. Ensuite, l'image convoluée a été comparée au MSE de l'image d'origine.  


|| Bruit impulsionnel 15 % | Bruit impulsionnel 40 % | Bruit gaussien $`\sigma`$ 15 | Bruit gaussien $`\sigma`$ 30  |
|---|---|---|---|---|
|Original|761257677.000000|2018626472.000000|58930680.000000|236050440.000000|133389198.716640|
|Filtre gaussien $`\sigma`$ 1|{- 130411267.297260 -}|332921180.364566|{+ 57201380.448215 +}|{+ 135609912.173834 +}|
|Filtre gaussien $`\sigma`$ 2|{- 116656155.124916 -}|247137519.215511|{+ 81729059.515926 +}|{+ 135609912.173834 +}|
|Filtre Moyenneur 3|2986611749.092858|3022384061.596872|2974858654.126204|2988005553.025825|
|Filtre Moyenneur 7|2784620084.969670|2816392136.686254|2776450268.289253|2785942672.319296|

## NL-means  

Tout d'abord, l'algorithme de NL-means permet d'éliminer le plus efficacement possible le bruit gaussien. Ce type de bruit est très difficile à éliminer. Le NL-means est un algorithme qui permet de trouver des parties d'images semblables et de  corriger la partie bruitée. Cependant, l'algorithme est très couteux en temps.

La première implémentation de l'algorithme de Nl-means fut un désastre. Les paramètres envoyés à la fonction n'étaient pas efficaces.  


```c++
double computeSimilarity(Image<uint_8> f1, Image<uint_8> f2, int patchSize);
```

Lorsque l'algorithme de computeNlMeans itérait sur les emplacements des `patchs`. Il fallait envoyer une image complexe. Ce qui compliquant, les boucles et la gestion des patchs. Les paramètres de l'algorithme sont devenus les suivants.

```c++
double computeSimilarity(int x1, int y1, int x2, int y2, int d, Image<uint8_t>imageEntre);
```

Les `Image<uint_8>` on été remplacées par des coordonnées.

En fait, `computeNlmeans` est attachée avec 2 autres fonctions. La première fonction est utilisée pour calculer la similarité entre 2 images. Si les deux images sont identiques, la fonction retourne 0.

```c++
uint8_t matrice[9]  = {
                        140,140,140,
                        140,140,140,
                        140,140,140
                    };

uint8_t matrice1[9]  = {
                        140,140,140,
                        140,140,140,
                        140,140,140
                    };

Image<uint8_t> imageSimple(3,3,matrice);
Image<uint8_t> imageSimple2(3,3,matrice1);
double sim;
for(int i = 0;i<imageSimple.getDx();i++){
    for(int j = 0;j<imageSimple.getDy();j++){
        for(int k = 0; k<imageSimple2.getDx();k++){
            for(int l = 0;l<imageSimple2.getDy();l++){
                sim += computeSimilarity(i,j,k,l,3,imageSimple2);
            }
        }
    }
}

printf("Similarity %f\n",sim);

// Similarity 0
```

Maintenant que l'algorithme peut voir la différence entre 2 images. Essayons-le avec d'autres matrices simples.


```c++
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
                        0,140,140,
                        140,0,140,
                        140,140,0
                    };

/* Boucle */

/*
Matrice -> Matrice = 0.000000
Matrice -> Matrice 1 = 42.000000
Matrice -> Matrice 2 = 823200.000000
Matrice -> Matrice 3 = 1489600.000000
*/
```

La prochaine fonction assigne des poids à des patchs. Les matrices vont être les mêmes que dans l'exemple ci-haut.

```c++
/* Même Matrice */

/*
    boucle : Matrice -> Matrice1
        w = computeWeight(i,j,k,l,3,50,imageSimple2);
        printf("Poids sur chaque pixel : %d",w);

Position : (i:0,j:0)	(k:0,l:0)	Poids : 1.000000
Position : (i:0,j:0)	(k:0,l:1)	Poids : 1.000000
Position : (i:0,j:0)	(k:0,l:2)	Poids : 1.000000
Position : (i:0,j:0)	(k:1,l:0)	Poids : 1.000000
Position : (i:0,j:0)	(k:1,l:1)	Poids : 0.999600
Position : (i:0,j:0)	(k:1,l:2)	Poids : 1.000000
Position : (i:0,j:0)	(k:2,l:0)	Poids : 1.000000
Position : (i:0,j:0)	(k:2,l:1)	Poids : 1.000000
Position : (i:0,j:0)	(k:2,l:2)	Poids : 1.000000
Position : (i:0,j:1)	(k:0,l:0)	Poids : 1.000000
Position : (i:0,j:1)	(k:0,l:1)	Poids : 1.000000
Position : (i:0,j:1)	(k:0,l:2)	Poids : 1.000000
Position : (i:0,j:1)	(k:1,l:0)	Poids : 1.000000
Position : (i:0,j:1)	(k:1,l:1)	Poids : 0.999600
Position : (i:0,j:1)	(k:1,l:2)	Poids : 0.999600
...
...
*/
```

Pour terminer, nous implémentons les 3 fonctions ensemble. L'algorithme ressemble à celle de la convolution. Sauf qu'il calcule la différence entre les points de chaque pixel et on assigne des poids sur chaque pixel. Après on fait la convolution sur chaque pixel et on récupère les pixels qui ont le plus gros poids pour réduire le bruit.

```javascript
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
Image<uint8_t> computeNLSimple = computeNlMeans(imageSimple25,21,7,50);
Image<double> bruitSimple = convolution(imageSimple25,ImageGaussSimple);
Image<uint8_t> c1 = convertionImage(bruitSimple);
Image<uint8_t> computeNLSimpleC1 = computeNlMeans(c1,21,7,50);


imageSimple25.print();
// Image Simple de 5X5
----------------------------------------
  0|255|  0|255|  0|255|  0|255|  0|255|
----------------------------------------
255|255|255|255|255|255|255|255|255|255|
----------------------------------------
  0|255|  0|255|  0|255|  0|255|  0|255|
----------------------------------------
255|255|255|255|255|255|255|255|255|255|
----------------------------------------
  0|255|  0|255|  0|255|  0|255|  0|255|
----------------------------------------
255|255|255|255|255|255|255|255|255|255|
----------------------------------------
  0|255|  0|255|  0|255|  0|255|  0|255|
----------------------------------------
255|255|255|255|255|255|255|255|255|255|
----------------------------------------
  0|255|  0|255|  0|255|  0|255|  0|255|
----------------------------------------
255|255|255|255|255|255|255|255|255|255|
----------------------------------------



computeNLSimpleC1.print();

----------------------------------------
124|124|124|124|125|126|126|128|130|136|
----------------------------------------
140|141|141|142|143|143|144|145|146|148|
----------------------------------------
156|156|157|157|158|158|159|159|160|160|
----------------------------------------
167|168|168|169|169|169|169|170|170|169|
----------------------------------------
175|175|175|175|175|175|175|175|174|173|
----------------------------------------
177|177|177|176|176|176|176|176|176|174|
----------------------------------------
174|174|174|174|174|174|174|174|173|170|
----------------------------------------
168|169|170|170|169|167|163|159|155|153|
----------------------------------------
133|133|133|132|130|130|131|132|134|138|
----------------------------------------
129|129|129|129|129|129|129|130|132|135|
----------------------------------------
```

L'une des matrices a été convolution avec un masque gaussien de 3. L'image à été flutée par ce masque. Elle est donc très différente de l'image d'origine. Les tests peuvent être faussés, car l'image est seulement de 10X10.  

Plus la fenêtre de recherche est grande, plus notre image bruitée va devenir comme l'image de départ. Plus la fenêtre est petite, plus l'image restera brouillée.  

## Conclusion

Les bruits synthétiques sont des algorithmes qui permettent d'ajouter du bruit aux images. Il est possible de calculer la différence entre 2 images avec l'algorithme de **Mean Square Error**.

Le débruitage par moyennes non locales est un algorithme efficace pour réduire le bruit gaussien. Le filtre médian ne permet pas de réduire le bruit gaussien. Il faut utiliser l'algorithme de **Compute Nl-means**. Cet algorithme permet de couvrir une certaine zone dans une image et de vérifier les voisins afin de réduire le bruit dans l'image.

J'ai testé mon algorithme sur de petites images pour vérifier son fonctionnement. Je n'ai pas réussi à faire les images de `barbara.pgm` avec mon ordinateur. J'ai essayé sur le serveur avec la commande `hohup` et je crois qu'il ferme la connexion, car je me connecte avec le `sterne.iutrs.unistra.fr` en premier et ensuite je me connecte sur le `troglo.iutrs.unistra.fr`. J'ai lancé l'algorithme  avec la commande `nohup`sur le troglo.

## Perspective

Il aurait été intéressant de trouver un autre algorithme moins gourmand pour réduire le bruit gaussien ou seulement d'optimiser le code de **Compute Nl-means**.

[bruitImpulsion0.2]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitImpulsion0.2.png
[bruitImpulsion0.5]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitImpulsion0.5.png
[bruitImpulsion0.8]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitImpulsion0.8.png
[bruitGausSigma1]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma1.png
[bruitGausSigma01Mu5]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma01Mu5.png
[bruitGausSigma10]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma10.png
[bruitGausSigma10Mu5]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma10Mu5.png
[bruitGausSigma15]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma15.png
[bruitGausSigma15Mu5]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma15Mu5.png
[bruitGausSigma25]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma25.png
[bruitGausSigma25Mu5]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP5/src/images/bruit/bruitGausSigma25Mu5.png
[barbara]:https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/base/barbara.png
