# MazeGenerator

<h3>A propos.</h3>
Un générateur de labyrinthe codé en C++ (Boost) / Qt.

Le projet est géré avec CMake.

Pour la qualité logicielle, j'utilise boost test avec ctest et KCachegrind.


<h3>Utilisation du projet</h3>

Pour compiler et lancer le projet : 
- cloner le repo
- mkdir build
- cd build
- cmake ..
- make
- ./mazeGenerator

Pour lancer les tests unitaires :
- ctest --verbose

Pour lancer KCacheGrind :
- ../runKCacheGrind.sh

<h3>Diagramme UML</h3>

Le diagramme de classes se trouve dans le dossier "archi" et s'ouvre avec StarUML