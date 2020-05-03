#include <stdio.h>
#define Va (sir + 50) // [ -50, 49 ]
#define Vb (sir + 30) // [ -30, 69 ]
#define N 10
#define M 20
int sir[100];
int functie(int n);
int main(void) {
  /* A
  * In C-ul din Linux nu avem functia clrscr(),
  * dar putem lansa in executie comada "clear"
  * pentru a sterge Terminalul
  */
  system("clear");
  /* B
  * Afisesam dimensiunile tipurilor fundamentale
  */
  printf("\nB\nDimensiunea tipurilor fundamentale"
         "\n\t sizeof( char ) = %2d bytes"
         "\n\t sizeof( int ) = %2d bytes"
         "\n\t sizeof( long ) = %2d bytes"
         "\n\t sizeof( long long ) = %2d bytes"
         "\n\t sizeof( float ) = %2d bytes"
         "\n\t sizeof( double ) = %2d bytes"
         "\n\t sizeof( long double ) = %2d bytes\n",
         sizeof(char), sizeof(int), sizeof(long), sizeof(long long),
         sizeof(float), sizeof(double), sizeof(long double));
  /* C
  * Afisam dimensiunea sirului alocat STATIC in functie
  */
  printf("\nC\nDimensiunea sirului = %d pentru functie( 10 );", functie(10));
  printf("\nDimensiunea sirului = %d pentru functie( 20 );\n", functie(20));
  /* D
  * Operam cu SIRURI CENTRATE
  */
  printf("\nD\nSIR[...] = %d ", Vb[69]);
  Va[49] = 123;
  printf("\nSIR[...] = %d ", Vb[69]);
  Vb[-30] = 321;
  printf("\nSIR[...] = %d\n", Va[-50]);
  /* E
  * In C INDEXAREA este echivalenta cu INDIRECTAREA
  * ... astfel sir[ i ] este transformat in *( sir + i )
  * pornind de aici, rezulta ca: 'sir[ i ]' echivalent cu 'i[ sir ]'
  */
  sir[20] = 0xFF;
  printf("\nE\nSIR[...] = ( %2X %2X )\n", sir[20], 20 [sir]);
  /*
  * Alocarea dinamica a bancurilor mari de date
  * SIRURI si MATRICI
  */
  int **pMat, Mat[N][M], i, j;
  // Alocare matrice alocata dinamic
  pMat = (int **)malloc(N * sizeof(int *));
  pMat[0] = (int *)malloc(N * M * sizeof(int));
  for (i = 1; i < N; i++)
    pMat[i] = pMat[i - 1] + M;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++) {
      Mat[i][j] = i * M + j;
      pMat[i][j] = i * M + j;
    } // Verificare neconcordanta
  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      if (pMat[i][j] != i * M + j) // if( pMat[ i ][ j ] != Mat[ i ][ j ] )
        printf("\nDIFERENTA");
  // Dealocare
  free(pMat[0]);
  free(pMat);
  return 0; // sau exit( 0 );
}
/*
* Functia isi aloca static un vector de N intregi,
* ... cu N primit ca parametru
*/
int functie(int n) {
  int s[n];
  return sizeof(s);
}