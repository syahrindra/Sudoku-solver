/*
Kelompok 4

Mochammad Syahrindra Akbar Suharno
Raihan nur Hanif
Juan Marten Daniel Lolowang
Jie Catur Nugraha

*/

#include <stdio.h>
#include <time.h>       // for time()

int valid(int[][9], int, int, int);
int solve(int[][9]); // fungsi 
int find_empty_cell(int[][9], int *, int *);

int main() {
    
    //hitung runtime
    double time_spent = 0.0;
        clock_t begin = clock();

	// sudoku yang akan dipecahkan
  int puzzle[9][9] = {{0, 0, 3, 	0, 0, 4, 	1, 0, 0},
                      {0, 0, 0, 	0, 0, 8, 	3, 7, 0},
                      {4, 0, 0, 	0, 3, 0, 	0, 0, 5},
                      
                      {9, 0, 0, 	0, 0, 0, 	0, 0, 8},
                      {0, 0, 5, 	6, 0, 0, 	9, 0, 0},
                      {0, 7, 0, 	0, 0, 0, 	0, 3, 0},
                      
                      {0, 5, 0, 	8, 7, 0, 	2, 9, 0},
                      {0, 0, 2, 	0, 0, 0, 	5, 0, 1},
                      {0, 1, 0, 	2, 0, 0, 	7, 0, 3}};
  int row = 0;
  int column = 0;
	
  if (solve(puzzle)) {
    printf("___________________\n");
    for (int x = 0; x < 9; ++x) {
      for (int y = 0; y < 9; ++y) printf("|%d", puzzle[x][y]);
      printf("|\n");
      if (x % 3 == 2) printf("___________________\n");
    }
  }
  // jika solusi tidak ditemukan
  else {
    printf("\n\nNO SOLUTION FOUND\n\n");
  }
  
    printf("\n\n");
    clock_t end = clock(); //menghentikan penghitungan runtime
	
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 
	
    printf("The elapsed time is %f seconds", time_spent); 


  return 0;
}

//cek apakah valid atau nggak
int valid(int puzzle[][9], int row, int column, int guess) {
  int corner_x = row / 3 * 3;
  int corner_y = column / 3 * 3;

  //printf("___________________\n");
  for (int x = 0; x < 9; ++x) {
    if (puzzle[row][x] == guess) return 0;
    
	/*printf("|%d", puzzle[row][x]);
    printf("|\n");*/
    
	if (puzzle[x][column] == guess) return 0;
    if (puzzle[corner_x + (x % 3)][corner_y + (x / 3)] == guess) return 0;
  }
  //printf("___________________\n");
  return 1;
}

//fungsi untuk menemukan cell yang kosong atau yg bernilai 0
int find_empty_cell(int puzzle[][9], int *row, int *column) {
  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      if (!puzzle[x][y]) {
        *row = x;
        *column = y;

        return 1;
      }
    }
  }
  return 0;
}

// fungsi untuk menyelesaikan sudoku dengan backtracking
int solve(int puzzle[][9]) {
  int row;
  int column;

  if(!find_empty_cell(puzzle, &row, &column)) return 1; // seluruh sel telah terisi
	
  for (int guess = 1; guess < 10; guess++) { // opsinya adalah 1-9
	if (valid(puzzle, row, column, guess)) { // mencoba mengisi dengan angka 
      puzzle[row][column] = guess; // jika tebakan valid maka angka akan diinput ke array sudoku

      if(solve(puzzle)) return 1; //berulang jika berhasil berhenti
      puzzle[row][column] = 0; // ulang dan mencoba kembali
    }
  }
  return 0;
}
