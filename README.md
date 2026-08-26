# Robot de course — évitement d'obstacles

Projet BUT1 GEII : robot autonome conçu pour suivre un parcours en évitant
des obstacles, avec pour objectif de minimiser le temps de parcours.
Premier prix du concours de robotique de la promotion.

## Matériel

- Carte driver moteur (2 moteurs, commande PWM + sens)
- Capteur ultrasonique (type HC-SR04) pour la détection d'obstacles
- LED de signalisation

## Fonctionnement

Le robot avance en ligne droite à vitesse maximale (`maxSpeed`) tant
qu'aucun obstacle n'est détecté. Le capteur ultrasonique mesure en continu
la distance à l'obstacle le plus proche :

- **Distance entre 10 et 20 cm** : manœuvre d'évitement légère (pivot).
- **Distance inférieure à 10 cm** : manœuvre d'évitement renforcée (recul
  puis pivot), pour les obstacles très proches détectés tardivement.

## Calibration de l'asservissement (défi principal du projet)

Les deux moteurs ne tournaient pas exactement à la même vitesse pour une
même commande PWM, ce qui faisait dévier le robot de sa trajectoire en
ligne droite. Ce déséquilibre a été corrigé par deux constantes de
compensation, déterminées expérimentalement :

```cpp
#define DIFF_D 5  // différence de PWM appliquée au moteur droit
#define DIFF_G -1 // différence de PWM appliquée au moteur gauche
```

Ces valeurs sont soustraites à la commande PWM de chaque moteur
(`Com_Mot_Droite` / `Com_Mot_Gauche`) pour compenser l'asymétrie
mécanique/électrique entre les deux moteurs et obtenir une trajectoire
rectiligne fiable.

## Contenu du dépôt

- `arduino/coderobot_deplacement.ino` — code de déplacement et d'évitement d'obstacles

## Compétences mobilisées (référentiel BUT GEII)

- **AC11.02** — Réaliser un prototype pour des solutions matérielles ou logicielles
- **AC12.02** — Identifier un dysfonctionnement (asymétrie des moteurs)
