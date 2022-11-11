# BeerRobot
## Membres du groupe et rôles
- Chelsea COMLAN : responsable Hardware
- Loïcia KOEHL : responsable intégration
- Quentin SIMON : responsable Software
- Alix HAVRET : responsable livrables

Encadrant du projet : Mr Fiack , Mr Tauvel

__Last update of README__ : 10/11/2022

__Github du projet ESE de Dernière année à l'ENSEA__

## Introduction
Elèves en option ESE (Electronique et Systèmes Embarqués) au sein de l'ENSEA (Ecole Nationale Supérieures de l'Electronique et de ses Applications), réalisant un robot comme projet central de leur option.  

## Objectifs du projet
Création d'un robot permettant d'attraper des canettes et les déplacer dans des zones, délimitées au préalables, selon la couleur de la canette.  

Le robot devra être capable de :  
- se déplacer
- saisir une canette 
- se déplacer avec la canette
- détecter la couleur de la canette 
- ne pas tomber 
- déplacer la canette dans la zone correspondante


### Contenus des dossiers
  #### Additional documents
* Schema_architectural_robot
* Première version du diagramme d'état

  #### Hardware
* Projet_robot_ESE : dossier kicad avec schematic, PCB et routage
* PCB 
  #### Software 
* Projet CubeIDE pour la STM32G0

__Non contenu dans les dossiers :__  
Modification du design initial du robot sur onshape. Ajout d'un roulement en plus à l'avant, modification de l'emplacement de la pince et la forme de celle ci. Une fois le PCB reçu, des modifications seront effectuées afin de permettre un bon placement de l'ensemble des fils.  
Espaces aménagés dans le design pour les différents capteurs : couleurs, bordure et distance.  
  
  
__Etapes en cours de réalisations :__
- prise en main des capteurs (couleurs, bordures, distance) et début de codage  sur CubeIDE
- soudure sur PCB
- diagramme à état
- réalisation en 3D du robot pour premier test

__09/11/2022__ Reception du PCB, début des soudures 
Soudeurs : Loïcia et Chelsea



Software :  
Le code sera utilisé dans diverses tâches (utilisation de FreeRTOS). Chaque étét décrit dans le diagramme à états correspondra à une tâche.  
Une tâche pourra faire appel à de la donnée, ou en consommer. Dans chaque tâche nous feront appel à divers bouts de code permettant de démarrer un capteur, un moteur, un servo, etc ...


