# Projet-Capteur-4e-INSATOULOUSE
Ce projet s'inscrit dans l'UF "Du capteur au banc de test" en 4ème année au département de Génie Physique de l'INSA Toulouse.
# 2021-2022_Paccard_Lemaire_Projet_Capteur
Ce projet s'inscrit dans l'UF **"Du capteur au banc de test"** en 4ème année au département de Génie Physique de l'INSA Toulouse.
***
L'objectif de ce dernier est d'élaborer un **capteur de déformation** low-tech à base de graphite. L'application d'une contrainte mécanique sur un capteur en papier sur lequel un dépôt de crayon à papier à été fait, modifie la distance entre les particules de graphite. La conductivité électrique de la couche de graphite est elle aussi modifiée et celà induit une variation de la résistance. C'est cette donnée qui va nous intéresser.

<p align="center"><img src="/Images/Capteur.png">

L'ensemble des étapes menées pour réaliser ce capteur, en allant du **design** jusqu'à la **réalisation** en passant par le **codage** seront détaillées dans ce dossier.

## Sommaire
* [1. Description du projet et détail des livrables](#PremiereSection)
* [2. Matériel nécessaire](#DeuxiemeSection)
* [3. Arduino](#TroisiemeSection)
  * [3.1. Librairies utilisées](#TroisiemeSection1)
  * [3.2. Code Arduino](#TroisiemeSection1)
* [4. Application Android](#QuatriemeSection)
* [5. KiCad](#CinquiemeSection)
  * [5.1. Symboles et empreintes des composants](#CinquiemeSection1)
  * [5.2. Schématique](#CinquiemeSection2)
  * [5.3. Placement des composants](#CinquiemeSection3)
  * [5.4. Visualisation 3D](#CinquiemeSection4)
* [6. Fabrication du shield](#SixiemeSection)
  * [6.1. Réalisation du PCB](#SixiemeSection1)
  * [6.2. Perçage et soudure](#SixiemeSection2)
* [7. Simulation](#SeptiemeSection)
* [8. Tests et résultats](#HuigtiemeSection)
  * [8.1. Banc de test](#HuigtiemeSection1)
  * [8.2. Résultats obtenus](#HuigtiemeSection2)
  * [8.3. Analyse des résultats et pistes d'améliorations](#HuigtiemeSection3)
* [9. Datasheet](#NeuviemeSection)
* [Contacts](#DixiemeSection)

## 1. Détail des livrables et description du projet <a id="PremiereSection"></a>
Voici l'ensemble des livrables du projet :
- Un **shield PCB** se connectant à une carte **Arduino UNO** contenant un amplificateur transimpédance, un module bluetooth, un écran OLED et un encodeur rotatoire
- Un **code Arduino** permettant de mesurer la déformation du capteur et de piloter le module bluetooth, l'écran OLED et l'encodeur rotatoire
- Une **application Android APK**
- Un **protocole de test** 
- La **datasheet** du capteur de déformation

Tout d'abord, nous avons réalisé un code Arduino permettant de vérifier notre montage contenant un amplificateur transimpédance, un écran OLED, un module bluetooth et un encodeur rotatoire. Une fois le montage fonctionnel, nous avons réalisé le design de notre shield sur le logiciel *KiCad*. Nous l'avons ensuite fabriqué et assemblé (lithographie, perçage, soudage des composants, etc.). En parallèle de cela, nous avons utilisé le logiciel *MIT App Inventor* afin de développer une application Android APK, capable de communiquer et recevoir les informations envoyées par le module bluetooth telles que les valeurs de résistance du capteur mesurées. Nous avons par la suite mis en place un banc de test pour pour caractériser les différents types de capteurs en fonction de leur déformation et de la mine de crayon utilisée (HB, B, 9B, etc.). Enfin, nous avons établi une datasheet à l'aide des résulats obtenus par le banc de test.

## 2. Matériel nécessaire
Pour réaliser le capteur ainsi que le PCB associé, voici la liste des composants nécessaires :
* x2 résistance 100kΩ
* x1 résistance 10kΩ
* x2 résistance 1kΩ
* x1 capacité 1μF
* x3 capacité 100nF
* x1 amplificateur opérationnel LTC1050
* x1 module Bluetooth HC05
* x1 encodeur rotatoire KY_040
* x1 écran OLED I2C 0.91

## 3. Arduino <a id="TroisiemeSection"></a>
### 3.1. Librairies utilisées <a id="TroisiemeSection1"></a>
Nous avons utilisé différentes librairies dans notre code Arduino. La librarie ["Adafruit_SSD1306"](/Libraries/Adafruit_SSD1306) permet de contrôller l'écran OLED. La librairie ["Adafruit_BusIO"](/Libraries/Adafruit_busIO) permet de gérer la connexion en I2C et SPI.

### 3.2. Code Arduino <a id="TroisiemeSection2"></a>
[Deux codes Arduino](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/tree/main/Arduino) ont été développés sous Arduino IDE pour profiter au mieux des fonctionnalités de notre capteur.

#### Code Graphite_sensor
Le [premier code](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/blob/main/Arduino/Graphite_sensor/Graphite_sensor.ino) permet d'assurer la communication entre la carte Arduino, qui récupère la valeur de tension renvoyée par le capteur, et les différents éléments ajoutés sur le shield soit : l'écran OLED, le module bluetooth et l'encodeur rotatoire. Différents menus sont accessibles sur l'écran OLED :
* Le premier menu permet un simple affichage de la résistance
* Le deuxième menu permet de selectionner le calibre de la résistance affichée sur le menu 1. Cette dernière peut ainsi être affichée en Ω, kΩ ou MΩ.
* Le troisème menu est un chronomètre permettant de savoir le temps d'execution du programme. C'est à dire le temps depuis le programme à été démarré.
* Le quatrième menu permet l'affichage d'une image.

En parallèle, le module bluetooth envoie les données de tension et de résistance à une application mobile qui sera détaillée dans la partie suivante.

#### Code Angle_calibration
Le [second code](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/blob/main/Arduino/Angle_calibration/Angle_calibration.ino) Arduino permet d'effectuer un calcul d'angle par rapport à la calibration du capteur. L'utilisateur rentre les valeurs de la résistance à plat et à la position la plus courbée possible en appuyant sur le bouton poussoir présent sur l'encodeur rotatoire. En considérant la variation de résistance linéaire, un produit en croix est ensuite fait pour asssocier une valeur de résistance à un angle de déformation.

## 4. Application Android <a id="QuatriemeSection"></a>

Nous avons réalisé une [application Android](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/tree/main/Application%20bluetooth) grâce au site *MIT App Inventor* afin d'instaurer une communication entre notre module bluetooth HC-05 et un smartphone Android. Cette application possède différentes fonctionnalités : après avoir choisi dans un menu l'appareil auquel on souhaite se connecter, et que la connexion a été effectuée, différentes informations sont affichées sur l'écran du téléphone. En premier, on trouve la tension VADC en volts de sortie du circuit, elle est envoyée sous forme d'un byte à l'application depuis la carte Arduino, puis elle est reconvertie dans le code de l'application en float permettant d'afficher les décimales. C'est ensuite la valeur de la résistance du capteur en graphite qui est affichée en Méga Ohms, la valeur est directement calculée depuis l'application à partir de la valeur de VADC reconvertie en float. Finalement, la variation de la valeur de résistance est tracée en fonction du temps dans un graphique (canva) au-dessous. Nous avons enregistré un graphique avec uniquement des axes et leurs titres sous forme d'image que nous avons ensuite mis en fond du graphique pour le tracé. 

## 5. KiCad <a id="CinquiemeSection"></a>
### 5.1. Symboles et empreintes des composants <a id="CinquiemeSection1"></a>
* Amplificateur LTC1050

<img src="/Images/LTC1050_schematic.png" height="200"> <img src="/Images/LTC1050_footprint.png" height="200">

* Ecran OLED

<img src="/Images/OLED_schematic.png" height="200"> <img src="/Images/OLED_footprint.png" height="200">

* Encodeur rotatoire KY_040

<img src="/Images/KY_040_schematic.png" height="200"> <img src="/Images/KY_040_footprint.png" height="200">

* Module bluetooth HC05

<img src="/Images/Bluetooth-HC05_schematic.png" height="200"> <img src="/Images/Bluetooth_HC05_footprint.png" height="200">


### 5.2. Schématique <a id="CinquiemeSection2"></a>
<p align="center"><img src="/Images/Schematic.png">

Une fois les empreintes créées, nous avons réalisé le schéma de notre shield. En haut à droite sont représentées les broches de la carte Arduino. En haut au milieu est représenté l'amplificateur transimpédance et en bas du schématique se trouvent l'écran OLED, le module bluetooth et l'encodeur rotatoire.

### 5.3. Placement des composants <a id="CinquiemeSection3"></a>
<p align="center"><img src="/Images/PCB_2D.png">

### 5.4. Visualisation 3D <a id="CinquiemeSection4"></a>
<p align="center"><img src="/Images/PCB_3D.png">

## 6. Fabrication du shield <a id="SixiemeSection"></a>
<img src="/Images/PCB_front.png" height="300"> <img src="/Images/PCB_back.png" height="300">

### 6.1. Réalisation du PCB <a id="SixiemeSection1"></a> 
Le PCB a été réalisé au sein des départements de Génie Physique (GP) et Génie Électrique et Informatique (GEI) de l'INSA Toulouse avec l'aide de Catherine Crouzet. Notre PCB à été fabriqué à partir d'une plaquette d'epoxy recouverte d'une fine couche de cuivre (environ 60μm). 
Nous avons imprimé sur du papier calque la modélisation de notre PCB effectuée sur le logiciel *KICAD* pour ensuite insoler aux UV notre plaquette avec la silouhette par-dessus pendant quelques minutes. À l'aide d'un révelateur, nous avons retiré la partie de la résine non insolée.
La plaquette d'expoxy est ensuite placée dans un bain de perchlorure de fer pour la gravure, opération durant 7 minutes. Le cuivre non protégé par la résine est ainsi retiré de la plaquette ce qui nous permet d'obtenir le PCB avec les pistes souhaitées.
Enfin, de l'acétone est appliquée sur la plaquette pour éliminer les dernières traces de résine.

### 6.2. Perçage et soudure <a id="SixiemeSection2"></a> 
Nous avons ensuite percé notre PCB aux endroits où les différents composants seront insérés à l'aide d'une perceuse électrique. Le diamètre des trous dépend des différents composants à placer :
* ⌀ 0.8mm : AOP LTC1050, résistances et capacités
* ⌀ 1.0mm : Broches de connexion de la carte Arduino Uno et headers des différents modules (OLED, bluetooth, encodeur rotatoire)
* ⌀ 1.2mm : Broches de connexion du capteur de déformation

Notre PCB ayant été imprimé en face avant, certains composants ont été placé en face avant et d'autres en face arrière pour faciliter la soudure et la connexion à la carte Arduino Uno.

## 7. Simulation <a id="SeptiemeSection"></a> 
Nous avons simulé notre amplificateur transimpédance sur le logiciel *LTSpice* afin de savoir le comportement que notre circuit aura une fois branché à de réelles valeurs de tension. Les différentes simulations réalisées sur le logiciel nous ont permis d'une part de vérifier le bon fonctionnement du circuit et de chacun des composants intégrés, et d'autre part de comprendre l'utilité de chacun. Le détail de la démarche suivie et des résultats obtenus est disponible dans le document [Simulation_LTspice](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/blob/main/Simulation_LTspice.pdf).

## 8. Tests et résultats <a id="HuigtiemeSection"></a> 
### 8.1. Banc de test <a id="HuigtiemeSection1"></a> 
<p align="center"><img src="/Images/Bench_test.png">

Nous avons testé notre capteur sur un banc de test que nous avons conçu à partir de feuilles de papier épais. Nous avons fabriqué 7 cylindres de diamètre variable, allant de 5cm à 2cm par pas de 0,5cm.
En enrobant les différents cylindres avec notre capteur, nous appliquons une déformation maitrisée que nous pouvons calculer avec la formule : 
*ε = e / (2•R)*, avec ε la déformation, e l'épaisseur de notre capteur, et R le rayon de courbure appliqué soit le rayon de nos cylindres.

Nous avons décidé de réaliser des mesures de compression (graphite vers le cylindre) du capteur et pas en tension (graphite vers l'extérieur), car bien que ces deux méthodes soient possibles, les valeurs de  résistance renvoyées par notre capteur en tension n'étaient pas exploitables.

### 8.2. Résultats obtenus <a id="SeptiemeSection2"></a> 
Les résultats complets de notre banc de test sont disponibles dans le dossier [Results](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/tree/main/Results). 

### 8.3. Analyse des résultats et pistes d'améliorations <a id="HuigtiemeSection3"></a> 
En comprimant notre capteur, les particules de graphite se rapprochent les unes des autres, ce qui facilite la conduction dans le réseau percolé du système. De la même manière, en mettant notre capteur en tension, certains chemins de percolation se retrouvent brisés ce qui augmente la résistance du capteur.
En fonction du type de crayon utilisé, les variations relatives de résistance changent. En effet, plus le crayon est gras, c'est à dire qu'il dépose plus de graphite, moins sa variation relative de résistance est élevée. Cette caractéristique se vérifie sur nos [résultats](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/tree/main/Results) et dans notre [datasheet](https://github.com/MOSH-Insa-Toulouse/2021-2022_Paccard_Lemaire_Projet_Capteur/blob/main/datasheet.pdf).
 
#### Comparaison avec le Flex-Sensor SEN-10264

 <p align="center"><img src="/Results/Tension_Pencils_vs_FlexSensor.png" width="600">  
 <p align="center"><img src="/Results/Compression_Pencils_vs_FlexSensor.png" width="600">
 
Nous avons étudié la réponse en résistance du flex-sensor SEN-10264 pour le comparer à nos capteurs low-tech à base de graphite. Nous avons observé que le flex-sensor industriel est plus sensible à la déformation (i.e. ΔR/R0 augmente plus rapidement avec la déformation) que nos capteurs de graphite lorsque l'on applique une déformation en tension. Cependant, en compression, le flex-sensor SEN-10264 possède une sensibilité du même ordre de grandeur que nos différents capteurs.
 
#### Pistes d'améliorations 
Certains point peuvent être améliorés dans notre projet :
* Le dépot de graphite sur le capteur est difficile à maîtriser et il est ainsi difficile de fabriquer plusieurs capteurs identiques
* Notre banc de test fourni des résultats répétables, il pourrait cependant être envisageable de fabriquer ce même banc de test en impression 3D pour augmenter sa résistance et longévitée.
* Sur notre PCB, l'ajout d'un potentiomètre digital permettrait de pouvoir travailler sur une gamme de résistance plus grande car ce dernier modulera la valeur de tension de sortie en fonction de la résistance du capteur

## 9. Datasheet <a id="NeuviemeSection"></a> 
La datasheet de notre capteur est disponible ici.

## Contacts <a id="DixiemeSection"></a> 
Pour toutes questions relatives aux différentes parties du projet, que ce soit du KiCad au code Arduino, n'hésitez pas à nous contacter !
* PHAN Nhat Tien : ntphan@insa-toulouse.fr
* TRUONG Minh Thang : mttruong@insa-toulouse.fr
