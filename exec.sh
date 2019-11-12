#!/bin/bash
if [ -f "grafo.gv" ]; then
    rm grafo.gv
fi
gcc *.c *.h -o app
./app
sfdp -T png -o "grafo.png" "grafo.gv"