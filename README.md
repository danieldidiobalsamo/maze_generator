# MazeGenerator

<h3>A propos.</h3>
MazeGenerator est un générateur de labyrinthes codé en C++ / Qt / CMake.
Les tests unitaires sont réalisés avec Boost Test / ctest.

L'interface est générée automatiquement à partir du .ui grâce à CMake auto-uic.

<h3>Utilisation du projet</h3>

Pour compiler et lancer le projet : 
- mkdir build
- cd build
- cmake ..
- make
- ./mazeGenerator

Pour lancer les tests unitaires :
- ctest --verbose

Les classes gérant les tests unitaires sont dans le dossier "test" et sont gérées dans un exécutable séparé.

Pour lancer KCacheGrind :
- ../runKCacheGrind.sh

<h3>Diagramme de classes</h3>

Le diagramme de classes, sous format .png et .mdj (StarUML), se trouve dans le dossier "archi".