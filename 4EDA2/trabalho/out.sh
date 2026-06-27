 #!/bin/bash

gcc main.c src/avl.c src/b.c src/rubro-negra.c src/conjunto.c -o main
./main

source .venv/bin/activate
python graficos.py
