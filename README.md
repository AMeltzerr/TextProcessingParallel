# Text Processing - Varianta Paralela

## Descriere
Acest proiect implementeaza numararea frecventei cuvintelor folosind fire de executie (threads).

## Tehnologii utilizate
- C++
- STL Threads
- mutex
- chrono

## Algoritm
1. Citirea fisierului text
2. Impartirea cuvintelor in mai multe parti
3. Procesarea fiecarei parti pe thread separat
4. Combinarea rezultatelor
5. Afisarea frecventelor

## Rezultate experimentale

Varianta secventiala:
- 16 ms

Varianta paralela:
- 7 ms
