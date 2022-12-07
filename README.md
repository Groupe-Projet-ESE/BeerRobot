# BeerRobot
## Membres du groupe et rôles
- Chelsea COMLAN : responsable Hardware
- Loïcia KOEHL : responsable intégration
- Quentin SIMON : responsable Software
- Alix HAVRET : responsable livrables

Encadrant du projet : Mr Fiack , Mr Tauvel

__Last update of README__ : 07/12/2022

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
Espaces aménagés dans le design pour les différents capteurs : couleurs, bordure et distance.  Ainsi que pour les fils
  
  
__Etapes en cours de réalisations :__
- prise en main des capteurs ainsi que des composants (couleurs, bordures, distance) et début de codage sur CubeIDE
Capteurs opérationnels seuls (fonctionnement solo, sur carte STM32F746NG Discovery)
    - Capteur TOF 
    - Capteur de bordure 
Autres élèments 
    - Servomoteur opérationnel, ouverture et fermeture avec notre pince imprimée en 3D
    - moteurs opérationnels, vitesse inégale entre les 2, un asservissement en vitesse sera necessaire pour faire tourner les 2 moteurs à la même vitesse
    

- diagramme à état
- réalisation en 3D du robot pour premier test : montage finalisé, seule le sujet de placement des fils est à revoir ou à modifier/améliorer.

__09/11/2022__ Reception du PCB, début des soudures 
Soudeurs : Loïcia et Chelsea
25/11/2022 : ensemble des composants soudés sur la carte, sauf certains connecteurs, test en cours de réalisation

Moteurs : 
Moteurs opérationnels sur la carte, avec les drivers. Problème de vitesse. Les 2 moteurs ne tournent pas à la même vitesse, il faudrait faire l'asservissement de ces derniers. Par ailleurs, on fera fonctionner l'odométrie pour avoir la position du robot en direct.


Software :  
Le code sera utilisé dans diverses tâches (utilisation de FreeRTOS). Chaque étét décrit dans le diagramme à états correspondra à une tâche.  
Une tâche pourra faire appel à de la donnée, ou en consommer. Dans chaque tâche nous feront appel à divers bouts de code permettant de démarrer un capteur, un moteur, un servo, etc ...

Le shell utilisé aura pour base le shell de Mr Fiack. Et sera amélioré afin de correspondre à nos attentes.




