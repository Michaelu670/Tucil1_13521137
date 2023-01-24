# Tugas Kecil 1 Strategi Algoritma - 24 Solver

24 Solver merupakan program berbasis CLI (Command-Line Interface) yang dapat membantu menyelesaikan [permainan kartu 24](https://en.wikipedia.org/wiki/24_(puzzle)).

## Requirement

### Compile

- g++ yang dapat melakukan kompilasi c++11 atau versi yang lebih baru

## Usage

### Compile

1. Buka command prompt pada lokasi repositori lokal
2. Pada command prompt, jalankan `g++ -std=c++11 src/solution.cpp -o bin/solution`

### Run

Seluruh command dijalankan pada lokasi repositori lokal

##### Without Argument

Pada command prompt, jalankan `bin\solution`

##### With Two Arguments

Pada command prompt, jalankan `bin\solution INPUT_FILE_LOCATION OUTPUT_FILE_LOCATION`

Lokasi INPUT_FILE_LOCATION dan OUTPUT_FILE_LOCATION relatif terhadap folder test/

`INPUT_FILE_LOCATION` dapat diganti menjadi `cin` untuk input dari command prompt\
`OUTPUT_FILE_LOCATION` dapat diganti menjadi `cout` untuk output ke command prompt

### Input Format
Masukan berupa satu baris berisi 4 string kartu (A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K) yang dipisahkan spasi.\
Masukan dapat diganti menjadi * (asterisk) untuk menandakan kartu random

Contoh masukan yang benar:\
8 7 Q A\
2 3 5 6\
\* \* \* \*

Contoh masukan yang salah:\
8 7 6\
1 2 3 4\
\*

## Notes

Kasus yang sama seperti 2 + (3 + (4 + 5)) dan ((4 + 5) + 3) + 2 tetap dianggap 2 kasus yang berbeda oleh program. 

## Author
Michael Utama (13521137)
