# <div align="center">BeerRobot</div> 
__Last update of README__ : 11/01/2023


![alt text](Additional_documents/robot_schema.JPG)


## Introduction
Elèves en option ESE (Electronique et Systèmes Embarqués) au sein de l'ENSEA (Ecole Nationale Supérieures de l'Electronique et de ses Applications), réalisant un robot comme projet central de leur option.  

## Objectifs du projet
Le but du projet est de créer un robot permettant d'attraper des canettes, de relever la couleur de cette dernière, se déplacer avec la canette attrapée et la déposer dans la zone adaptée selon sa couleur. Par ailleurs le robot devra se repérer sur une table afin de ne pas tomber.   

## Membres du groupe et rôles
Le groupe de projet est constitué de 4 membres, chacun ayant divers responsabilités.  
- __Chelsea COMLAN__ : responsable Hardware
- __Loïcia KOEHL__ : responsable intégration
- __Quentin SIMON__ : responsable Software
- __Alix HAVRET__ : responsable livrables

Encadrants du projet : Mr Fiack , Mr Tauvel

### Contenus des dossiers
  #### Additional documents
* Schema_architectural_robot
* Première version du diagramme d'état
* Rapport de mi-projet (avec diagramme de Gantt, Cahier des charges, ...)
* Images 

  #### Hardware
* Projet_robot_ESE : dossier kicad avec schematic, PCB et routage
* PCB 

  #### Software 
* Projet CubeIDE pour la STM32G0

  #### 3D 
* Fichier 3D pour la réalisation du robot

## Architecture générale du projet

Au debut du projet nous avons eu la liste de l'ensemble des composants auxquels nous avions accès pour la réalisation du robot et afin de remplir ses divers fonctionnalités.   
Le schéma architectural au début du projet nous a permit de définir l'ensemble des entrées necessaires dans notre microcontroleur et les divers flux de données qui allaient entrer en jeu.  

### Rôles et utilité des divers composants, capteurs 
#### Moteurs FIT501
Deux Moteurs à courant continu, alimenté en xx V, permettant de faire tourner 2 roues. Le moteur a également un encodeur.  

### Servomoteur XL320
Servomoteur qui permettra de faire bouger la pince necessaire pour saisir les canettes.

### Capteur couleur TCS3200

### Capteur de bordure 

### Capteur TOF 

## 3D du robot 
Nous avons prit la décision de modifier le design initial du robot sur onshape.  
Ajout d'un roulement en plus à l'avant, modification de l'emplacement de la pince et la forme de celle ci. Une fois le PCB reçu, des modifications seront effectuées afin de permettre un bon placement de l'ensemble des fils.  
Par ailleurs nous avons aménagés divers emplacements pour les différents capteurs : couleurs, bordure et distance, ainsi que pour les fils.  
  
 
## Hardware 

__09/11/2022__ Reception du PCB, début des soudures 
Soudeurs : Loïcia et Chelsea
25/11/2022 : ensemble des composants soudés sur la carte, sauf certains connecteurs, test en cours de réalisation




## Software

Le code sera utilisé dans diverses tâches (utilisation de FreeRTOS). Chaque état décrit dans le diagramme à états correspondra à une tâche.  
Une tâche pourra faire appel à de la donnée, ou en consommer. Dans chaque tâche nous feront appel à divers bouts de code permettant de démarrer un capteur, un moteur, un servo, etc ...

Les premiers tests sont effectués via un shell, puis une tache sera implémentée afin de faire fonctionner notre robot de manière autonome (avec une séquence lancée automatiquement).


### Moteurs : 
Problème de vitesse. Asservissement necessaire.
Asservissement : ...



### Capteurs 
#### Capteur bordure 
#### Capteur TOF 
#### Capteur couleurs





Objectif de la présentation finale : 
Présenter son robot avec un code intégré et prévoir une echainement d'action :  
- repérer la canette
- avancer vers elle 
- l'attraper
- vérifier qu'elle est attrapée
- 

