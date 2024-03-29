# <div align="center">BeerRobot</div> 
__Last update of README__ : 23/01/2023

![alt text](Additional_documents/robot_reel_petite.jpg)

## Introduction
Elèves en option ESE (Electronique et Systèmes Embarqués) au sein de l'ENSEA (Ecole Nationale Supérieures de l'Electronique et de ses Applications), réalisant un robot comme projet central de leur option.  

## Objectifs du projet
Le but du projet est de créer un robot permettant d'attraper des canettes, de relever la couleur de cette dernière, se déplacer avec la canette attrapée et la déposer dans la zone adaptée selon sa couleur. Par ailleurs le robot devra se repérer sur une table afin de ne pas tomber.   

## Matériels et composants à notre disposition

__Microcontroleur__ : STM32G070RBT6 (Farnell : 3365377)  
__Quartz 16 MHz__ : (Farnell : 2853935)  
__Connecteur SWD/STLink__ : (Farnell : 3226055)  
__Driver moteur__ : ZXBM5210-S (Farnell : 3935372)   
__Moteurs__ : DfRobot FIT0520 ou FIT0521   
__Régulateur 5V__ : AZ1117CH2-5.0TRG1 (Farnell : 3942512)  
__Régulateur 3.3V__ : MIC5317-3.3YM5 (Farnell : 2920683)  
__Batterie NIMH 7.2V 1.3Ah__ (RS : 777-0377)    
__Capteur bordure__ : Sharp GP2Y0D805Z0F (Generationrobots : A-000000-00046)   
__Capteur TOF__ : VL53L0X (Generationrobots : A-000000-03233)   
__Capteur de couleur__ : VEML3328 (Farnell : 3517203)  
__Servomoteur__ : XL320 (Generationrobots : A-000000-01282)  
Connecteurs JST 2.54mm  


![alt text](Additional_documents/fonctionnalites_robot_schema.png)


## Membres du groupe et rôles
Le groupe de projet est constitué de 4 membres, chacun ayant divers responsabilités.  
- __Chelsea COMLAN__ : responsable Hardware
- __Loïcia KOEHL__ : responsable intégration
- __Quentin SIMON__ : responsable Software
- __Alix HAVRET__ : responsable livrables


![alt text](Additional_documents/gantt.JPG)

__Encadrants du projet__ : Mr Fiack , Mr Tauvel  
__Intervenants extérieur__ : Mme Quittel, Mr Jauffrey, Mr Le Bidan  

### Contenus des dossiers
La démonstration finale se trouve sur la master. 

#### Additional documents
Contient l'ensemble des images necessaire à la rédaction de ce README, le rapport de mi-projet rédigé en novembre ainsi que le diaporama de notre présentation du robot en décembre.   

  #### Hardware
Contient le projet Kicad avec l'ensemble des fichiers electronique ainsi que le fichier de routage du PCB.  
Le PCB a été produit à l'extérieur de l'ENSEA.  

  #### Software 
Contient les codes "annexes", c'est à dire les codes des composants testé sur le STM32F746NG.  
Le projet CubeIDE a destination de la STM32G0 (notre microcontroleur de projet) se trouve sur la master. 

  #### 3D 
  Contient certains fichiers 3D pour la réalisation du robot

## Architecture générale du projet

Au debut du projet nous avons eu la liste de l'ensemble des composants auxquels nous avions accès pour la réalisation du robot et afin de remplir ses divers fonctionnalités.   
Le schéma architectural au début du projet nous a permit de définir l'ensemble des entrées necessaires dans notre microcontroleur et les divers flux de données qui allaient entrer en jeu.  
![alt text](Additional_documents/schema_architectural.png)

### Rôles et utilité des divers composants, capteurs 
#### Moteurs FIT501
Deux Moteurs à courant continu, alimenté en xx V, permettant de faire tourner 2 roues. Le moteur a également un encodeur.  

### Servomoteur XL320
Servomoteur qui permettra de faire bouger la pince necessaire pour saisir les canettes.

### Capteur couleur TCS3200
Capteur permettant de detecter la couleur de la canette à l'aide de filtres superposés à des LEDS.

### Capteur de bordure 
Capteur infra-rouge qui détecte si il y a un object en face de lui.

### Capteur TOF 
Time Of Flight, renvoie le temps qu'a prit la source lumineuse du capteur pour rebondir sur un object et revenir. Cela nous permet d'avoir notre distance par rapport à un objet. (en mm)


## 3D du robot 
Nous avons prit la décision de modifier le design initial du robot sur onshape.  
Ajout d'un roulement en plus à l'avant, modification de l'emplacement de la pince et la forme de celle ci. Une fois le PCB reçu, des modifications ont été effectuées afin de permettre un bon placement de l'ensemble des fils.  
Par ailleurs nous avons aménagés divers emplacements pour les différents capteurs : couleurs, bordure et distance. 

  
  
![alt text](Additional_documents/3D_robot.JPG)
 
 
## Hardware 
### Schema electrique
A partir du schema architectural réalisé au début du projet, nous avons commencé le schéma électrique du projet sur Kicad.  
Ce dernier a été séparé en plusieurs feuilles afin de pouvoir organiser les différentes partie : STM32, alimentation, capteurs, moteurs, servomoteur.

![alt text](Additional_documents/schematic_kicad.JPG)

### PCB
__09/11/2022__ Reception du PCB  
__Soudeurs__ : Loïcia et Chelsea  
L'ensemble des soudures ont été réalisées à la main, lee 25/11/2022  l'ensemble des composants étaient soudés sur la carte.   
Nous avons soudés les connecteurs au fur et à mesure de la réalisation des tests.

![alt text](Additional_documents/PCB_routage.JPG)


## Software

Le code sera utilisé dans diverses tâches (utilisation de FreeRTOS). Chaque état décrit dans le diagramme à états correspondra à une tâche.  
Une tâche pourra faire appel à de la donnée, ou en consommer. Dans chaque tâche nous feront appel à divers bouts de code permettant de démarrer un capteur, un moteur, un servo, etc ...  

Pour effectuer nos tests sur les capteurs, nous avons implémentés un shell. Chacun des capteurs ont été validé sur la STM32F746NG, et ensuite leur code était intégré à la STM32G0.
La shell nous a permit de faire une première démonstration. 

### Moteurs : 
Après les premiers tests, nous avons remarqué que pour une même commande vitesse, les 2 roues ne tournaient pas à la même vitesse, de ce fait le robot n'allait pas droit.  Afin de régler ce problème il était nécessaire de mettre en place un asservissement.
#### Asservissement 
Nous avons décidé de faire un correcteur PI (Proportionnel Intégral).  

**schéma**

Pour cela il nous fallait donc récupérer des informations venant du robot et du microcontroleur :  
-	Valeur vitesse demandée  pour les roues
-	Valeur vitesse réelle des 2 roues (les 2 étant différentes du à la qualité des moteurs)  
-	Nombre de tick moteur  

Ces infos nous permettaient alors de créer le correcteur PI avec :  
-	Coefficient proportionnel Kp  
-	Coefficient intégrateur Ki  

Une fois avoir réussi à récupérer la valeur de la vitesse en entrée et le nombre de tick nous avons pu commencer à coder l’asservissement.  

Pour ce faire il fallait que l’on fasse la différence de valeur entre la valeur actuelle et la valeur précédente de vitesse. Par la suite, nous pouvions calculer l’erreur entre la valeur d’entrée et la vitesse du robot pour voir si il avançait à la vitesse souhaitée.  
Une fois toutes la valeurs et calculs mis en place, nous avons pu commencer la recherche des valeurs pour nos coefficients. Il fallait trouver les valeurs avec lesquelles il y avait le moins d’oscillation possible.  




### Fonctionnement des capteurs 
#### Capteur bordure 


#### Capteur TOF 
Le capteur TOF a un driver déja créé, ce qui nous a permit de réutiliser les fonctions déja existantes permettant l'initialisation du capteur, et la récupération des valeurs .L'activation de la pin GPIO nous permet d'acquérir les valeurs en continue tant que le TOF est actif.   
Lorsque que l'on veut utiliser 2 TOF, c'est la pin XSHUT qui rentre en jeux. Les 2 TOF étant sur le même I2C, on activera uniquement le TOF du capteur que l'on veut utiliser.  


#### Capteur couleurs
Non fonctionnel.



__Objectif de la présentation finale :__

La démo implémentée et téléchargée sur la master permet au robot de faire une première phase de démarrage, de se lancer en mode "recherche" canette. Une fois une canette repérée à une certaine distance, le robot continue sa recherche vers la zone où il a capté une canette. Une fois que la canette est captée dans le creue du robot, alors la pince est déclenchée en mode fermeture. 

