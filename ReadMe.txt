Malgrés le fait que ce ReadMe soit en français, tous mes commentaires sont en anglais dans le code source,
j'espère que ça ne vous dérange pas.

Compilation
    Pour la compilation du logiciel, l'utilisation du makefile est conseillée.
    La commande make compile s'occupe de compiler correctement le logiciel.
    Gcc est utilisé pour la compilation.

Exécution:
    Le logiciel peut être exécuté de deux façons:
        - Mode console: permettant l'insertion du nombre premier à tester
        ainsi que le nombre d'itérations
        
        - Mode fichier: necéssite un argument d'exécution du programme
        lequel sera considéré comme le chemin du fichier contenant les nombres premiers à tester
        les nombres ne peuvent pas dépasser 2046 chiffres

Pour une utilisation rapide, les deux type exécutions sont dans le makefile:
- make run pour la version console 
- make runFile pour la version chargeant un fichier (le fichier fournit pour le dm est utilisé) 