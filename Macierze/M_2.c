#include<stdio.h>
#include<conio.h>       // dla clrscr() (Borland) i getch() (Borland i Dev C++) // for Borland to run clrscr() & getch() (Borland & Dev C++)
#include<stdlib.h>      // dla system("cls") (Dev C++) // for Dev C++ to run system("cls") function and for exit()
#include<locale.h>      // dla znaków narodowych innych ni¿ angielskich // for non-English national characters (Eg. German)


/* Leszek Buczek, 31-09-2021, Program: Macierz_2
   Rozwi¹zywanie uk³adu 'n' równañ liniowych z 'n' niewiadomymi
   Dla maksymalnie 10 równañ z 10 niewiadomymi - metoda Cramera
   Z mo¿liwoœci¹ rozszerzenia do wiêkszej iloœci równañ z wiêksz¹ iloœci¹ niewiadomych
   Wykonane na bazie programu 'macierz6' - obliczanie wyznacznika macierzy
   (Solving a system of 'n' linear equations with 'n' variables
    For up to 10 equations with 10 variables - Cramer method
    Possible expansion to more equations with more variables
    Made on the basis of program 'Macierz6' - Calculation of a determinant of a quadratic matrix)

   A*x=WW gdzie (where):
   A  - macierz g³ówna (macierz utworzona ze wspó³czynników przy zmiennych gdy macierze zast¹pimy uk³adem równañ liniowych)
        (the coefficient matrix (the matrix made up by the coefficients of the variables on the left-hand side of the equation) )
   x  - jednokolumnowa macierz zmiennych
        (the column matrix with variables)
   WW - jednokolumnowa macierz sta³ych (jednokolumnowa macierz wyrazów wolnych)
       (the column matrix with the constants (which are on the right side of the equations) )
*/

// ----------------------------------------------------------------------------------------
// //Przyk³ad 1: (Example 1:)
//#define MAX_i 2                        // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { { -2, 3}       // macierz g³ówna (coefficient matrix)
//                      , { -4, 7}
//                      };
//int WW[MAX_i][1] = { { -1},            // macierz wyrazów wolnych (column matrix with the constants)
//                     { -1}
//                   };
// // x1=2, x2=1     <-- spodziewany wynik (expected result)

// ----------------------------------------------------------------------------------------
// //Przyk³ad 2: (Example 2:)
//#define MAX_i 3                        // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { { 1, 2, 3}  // { { 2,  1,  2}  // { { 3,  1,  2}      // macierz g³ówna (coefficient matrix)
//                      , { 3, 2, 2}  // , { 1,  1, -1}  // , { 1,  1, -1}
//                      , { 2, 0, 1}  // , { 1, -2, -6}  // , { 0, -2, -6}
//                      }; // W = -8  // }; // W = -17   // }; // W = -22       // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
//int WW[MAX_i][1] = { { 13 }  // { {  11 }  // { {  13 }                       // macierz wyrazów wolnych (column matrix with the constants)
//                   , { 14 }  // , {   0 }  // , {   0 }
//                   , {  7 }  // , { -18 }  // , { -20 }
//                   };        // };        // };
// // x1=2, x2=1, x3=3     <-- spodziewany wynik (dla wszystkich przypadków) // expected result (for all above listed cases)

// ----------------------------------------------------------------------------------------
// //Przyk³ad 3: (Example 3:)
//#define MAX_i 4                         // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { { 1,  1, -1,  1}   // { { 3, 2, 1, 7}   // { { 1, 2,  3,  4}  // macierz g³ówna (coefficient matrix)
//                      , { 2, -1,  1,  1}   // , { 8, 2, 2, 4}   // , { 2, 3,  1,  2}
//                      , { 1,  2,  3, -1}   // , { 5, 0, 3, 3}   // , { 1, 1,  1, -1}
//                      , { 3, -1,  2, -1}   // , { 1, 0, 0, 9}   // , { 1, 0, -2, -6}
//                      }; // W = 33         // }; // W = -204    // }; // W = -1       // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
//int WW[MAX_i][1] = { { 0 }  // { { 12 }  // { { 11 }                                  // macierz wyrazów wolnych (column matrix with the constants)
//                   , { 5 }  // , { 16 }  // , {  6 }
//                   , { 6 }  // , { 14 }  // , {  2 }
//                   , { 6 }  // , { 10 }  // , { -9 }
//                   };       // };        // };
// // x1=1, x2=0, x3=2, x4=1     <-- spodziewany wynik (dla wszystkich przypadków) // expected result (for all above listed cases)

// ----------------------------------------------------------------------------------------
// //Przyk³ad 4: (Example 4:)
//#define MAX_i 5                         // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { {  3,  0,  0, 3,  0}   // { { 4, 0, -7,  3, -5}    // macierz g³ówna (coefficient matrix)
//                      , { -3,  0, -2, 0,  0}   // , { 0, 0,  2,  0,  0}
//                      , {  0, -1,  0, 0, -3}   // , { 7, 3, -6,  4, -8}
//                      , {  0,  0,  0, 3,  3}   // , { 5, 0,  5,  2, -3}
//                      , {  0, -1,  2, 0,  1}   // , { 0, 0,  9, -1,  2}
//                      }; // W = -18            // }; // W = 6              // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
//int WW[MAX_i][1] = { {  6 }  // { { -22 }                                  // macierz wyrazów wolnych (column matrix with the constants)
//                   , { -7 }  // , {   4 }
//                   , { -9 }  // , { -25 }
//                   , { 12 }  // , {   8 }
//                   , {  7 }  // , {  23 }
//                   };        // };
// // x1=1, x2=0, x3=2, x4=1, x5=3     <-- spodziewany wynik (dla obydwu przypadków) // expected result (for both above listed cases)

// ----------------------------------------------------------------------------------------
// //Przyk³ad 5: (Example 5:)
//#define MAX_i 6                        // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { { 1, 0, 0, 0, 0, 2}   // { {  2,  1, -1,  3, 1,  0}   // macierz g³ówna (coefficient matrix)
//                      , { 0, 1, 0, 0, 2, 0}   // , {  1,  4, -3,  2, 5, -1}
//                      , { 0, 0, 1, 2, 0, 0}   // , { -2,  3,  0,  2, 1,  0}
//                      , { 0, 0, 2, 1, 0, 0}   // , {  3, -1,  5, -3, 0,  2}
//                      , { 0, 2, 0, 0, 1, 0}   // , {  1, -1,  2,  0, 1,  2}
//                      , { 2, 0, 0, 0, 0, 1}   // , { -1,  3,  0,  2, 4, -2}
//                      }; // W = -27           // }; // W = ?                  // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
//int WW[MAX_i][1] = { { -1 }  // { {  6 }                                      // macierz wyrazów wolnych (column matrix with the constants)
//                   , {  6 }  // , { 13 }
//                   , {  4 }  // , {  3 }
//                   , {  5 }  // , {  8 }
//                   , {  3 }  // , {  6 }
//                   , {  1 }  // , { 15 }
//                   };        // };
// // x1=1, x2=0, x3=2, x4=1, x5=3, x6=-1     <-- spodziewany wynik (dla obydwu przypadków) // expected result (for both above listed cases)

// ----------------------------------------------------------------------------------------
// //Przyk³ad 6: (Example 6:)
//#define MAX_i 7                        // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { {  2,  1, -1,  3, 1,  0,  2}  // macierz g³ówna (coefficient matrix)
//                      , {  1,  4, -3,  2, 5, -1, -1}
//                      , { -2,  3,  0,  2, 1,  0,  3}
//                      , {  3, -1,  5, -3, 0,  2,  0}
//                      , {  1, -1,  2,  0, 1,  2, -2}
//                      , { -1,  3,  0,  2, 4, -2,  1}
//                      , {  0,  2, -1,  3, 2,  1,  1}
//                      }; // W = 694  // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
//int WW[MAX_i][1] = { {  2 }          // macierz wyrazów wolnych (column matrix with the constants)
//                   , { 15 }
//                   , { -3 }
//                   , {  8 }
//                   , { 10 }
//                   , { 13 }
//                   , {  4 }
//                   };
// // x1=1, x2=0, x3=2, x4=1, x5=3, x6=-1, x7=-2     <-- spodziewany wynik (expected result)

// ----------------------------------------------------------------------------------------
// //Przyk³ad 7: (Example 7:)
//#define MAX_i 8                        // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { {  2,  1, -1,  3, 1,  0,  2,  1}   // macierz g³ówna (coefficient matrix)
//                      , {  1,  4, -3,  2, 5, -1, -1, -2}
//                      , { -2,  3,  0,  2, 1,  0,  3,  5}
//                      , {  3, -1,  5, -3, 0,  2,  0,  3}
//                      , {  1, -1,  2,  0, 1,  2, -2,  1}
//                      , { -1,  3,  0,  2, 4, -2,  1,  3}
//                      , {  0,  2, -1,  3, 2,  1,  1,  4}
//                      , {  5,  2, -1,  3, 0,  1, -3, -1}
//                      }; // W = 27340  // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
//int WW[MAX_i][1] = { {  2 }            // macierz wyrazów wolnych (column matrix with the constants)
//                   , { 15 }
//                   , { -3 }
//                   , {  8 }
//                   , { 10 }
//                   , { 13 }
//                   , {  4 }
//                   , { 11 }
//                   };
// // x1=1, x2=0, x3=2, x4=1, x5=3, x6=-1, x7=-2, x8=0     <-- spodziewany wynik (expected result)

// ----------------------------------------------------------------------------------------
// //Przyk³ad 8: (Example 8:)
//#define MAX_i 9                        // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
//int A[MAX_i][MAX_i] = { {  2,  1, -1,  3, 1,  0,  2,  1,  0}    // macierz g³ówna (coefficient matrix)
//                      , {  1,  4, -3,  2, 5, -1, -1, -2,  2}
//                      , { -2,  3,  0,  2, 1,  3,  3,  5,  3}
//                      , {  3, -1,  5, -3, 0,  0,  0,  3,  1}
//                      , {  1, -1,  2,  0, 1, -2, -2,  1, -1}
//                      , { -1,  3,  0,  2, 4,  1,  1,  3,  2}
//                      , {  0,  2, -1,  3, 2,  1,  1,  4,  0}
//                      , {  5,  2, -1,  3, 0, -3, -3, -1,  1}
//                      , {  0,  1,  3,  2, 0, -1,  1,  1, -3}
//                      }; // W = 26928  // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
//int WW[MAX_i][1] = { {   2 }           // macierz wyrazów wolnych (column matrix with the constants)
//                   , {   9 }
//                   , { -15 }
//                   , {   7 }
//                   , {  17 }
//                   , {   4 }
//                   , {   4 }
//                   , {  12 }
//                   , {  16 }
//                   };
// // x1=1, x2=0, x3=2, x4=1, x5=3, x6=-1, x7=-2, x8=0, x9=-3     <-- spodziewany wynik (expected result)

// ----------------------------------------------------------------------------------------
//Przyk³ad 9: (Example 9:)
#define MAX_i 10                       // iloœæ wierszy i kolumn macierzy A (number of rows and columns of matrix A)
int A[MAX_i][MAX_i] = { {  2,  1, -1,  3, 1,  0,  2,  1,  0,  2}   // macierz g³ówna (coefficient matrix)
		      , {  1,  4, -3,  2, 5, -1, -1, -2,  2,  3}
		      , { -2,  3,  0,  2, 1,  3,  3,  5,  3, -1}
		      , {  3, -1,  5, -3, 0,  0,  0,  3,  1,  5}
		      , {  1, -1,  2,  0, 1, -2, -2,  1, -1,  0}
		      , { -1,  3,  0,  2, 4,  1,  1,  3,  2,  2}
		      , {  0,  2, -1,  3, 2,  1,  1,  4,  0, -3}
		      , {  5,  2, -1,  3, 0, -3, -3, -1,  1,  2}
		      , {  0,  1,  3,  2, 0, -1,  1,  1, -3, -2}
		      , {  2, -2,  1,  3, 1, -3,  2,  1,  4,  1}
		      }; // W = 13634    // jej spowiedziany wyznacznik (expected determinant of the coefficient matrix)
int WW[MAX_i][1] = { {   6 }             // macierz wyrazów wolnych (column matrix with the constants)
		   , {  15 }
		   , { -17 }
		   , {  17 }
		   , {  17 }
		   , {   8 }
		   , {  -2 }
		   , {  16 }
		   , {  12 }
		   , {  -1 }
		   };
// x1=1, x2=0, x3=2, x4=1, x5=3, x6=-1, x7=-2, x8=0, x9=-3, x10=2     <-- spodziewany wynik (expected result)

// ----------------------------------------------------------------------------------------

int A10[10][10], A9[9][9], A8[8][8], A7[7][7], A6[6][6], A5[5][5], A4[4][4], A3[3][3], A2[2][2];

//***********************************************************************************************************
//  Uwaga: Wartoœæ wyznacznikaów 'W', W2 itd, mo¿e przekroczyæ rozmiar typu 'int'                             // Polski
//  (Attention: The value of the determinants 'W', W2 and so on, may exceed the size of the 'int' type)       // English
//    Maksymalna wartoœæ typu int to 2 147 483 647 dla Dev C++ (The maximum value of type int is 2 147 483 647 in Dev C++)
//    Maksymalna wartoœæ typu int to tylko  32 767 dla TurboC3 (The maximum value of type int is only   32 767 in TurboC3)
//***********************************************************************************************************

int W;                                // Wyznacznik macierzy glównej (determinant of the coefficient matrix)


void main()
{  int w = -1; // licznik wyznaczników - oprócz wyznacznika g³ównego bedzie MAX_i wyznaczników                // Polski
               // determinant counter - in addition to the main determinant, there will be MAX_i determinants // English
   int i, j;                          // indeksy elementów macierzy A (indices of elements of matrix A)
   int z;                             // zmienna pomocnicza  z = MAX_i (auxiliary variable  z = MAX_i)
   int i2, i3, i4, i5, i6, i7, i8, i9, i10;  // zmienne pomocnicze (auxiliary variables)
   int p2, p3, p4, p5, p6, p7, p8, p9, p10;  // zmienne pomocnicze (auxiliary variables)
                                             // 'pozycja' liczby pierwszego szeregu dla ró¿nych wielkoœci macierzy            // Polski
                                             // The 'position' of the number of the first row for different matrix quantities // English
   int znak_i3, znak_i4, znak_i5, znak_i6, znak_i7, znak_i8, znak_i9, znak_i10;  // 'znak' (sign) is to change a sign of a number
   int W2=0, W3=0, W4=0, W5=0, W6=0, W7=0, W8=0, W9=0, W10=0;  // wyznaczniki (determinants)

   // clrscr();     // wyczyœæ ekran - tylko dla Borland Turbo C  // clear screen - only for Borland Turbo C
   system("cls");   // wyczyœæ ekran - tylko dla Dev C++  //  clear screen - only for Dev C++
   setlocale(LC_CTYPE, "Polish");      // tylko w Dev C++ dla znaków narodowych innych ni¿ angielskich // only in Dev C++ for non-English national characters (Eg. German)
   // setlocale( LC_ALL, "German");    // This is an example to set the German language

   z = MAX_i;

   // Wydruk równañ (Equations printout)
   printf("Uk³ad równañ:\n");          // Polski
   // printf("System of equations\n"); // English
   for (i=0; i < MAX_i; i++)
   {   printf("\n");
       for (j=0; j < MAX_i; j++)
       {   printf("%d*x%d ", A[i][j], j+1);
	   if ( j != MAX_i - 1 )
	   {  if ( A[i][j+1] >= 0 )
		 printf("+");
	   }
	   else
	      printf(" = %d", WW[i][0]);
       }
   }
   printf("\n\nRozwi¹zanie tego uk³adu równañ to:");                // Polski
   // printf("\n\nThe solution to this system of equations is:");   // English
   if ( MAX_i > 5 )
      printf("\n\nProszê czekaæ a¿ do otrzymania wartoœci x%d. Obliczenia w toku...", MAX_i);              // Polski
      // printf("\n\nPlease wait until you receive the value of x%d. Calculations in progress...", MAX_i); // English
   else
      printf("\n\n");

   // Macierz A bêdzie poddana notorycznym zmianom, wiêc trzeba zrobiæ to:                   // Polski
   // Skopiowanie macierzy A do odpowiedniej rozmiarem macierzy/tablicy                      // Polski
   // Jednoczeœnie utrzymana zostaje oryginalna wartoœæ macierzy A - bêdzie ona potrzebna    // Polski
   // Matrix A will undergo notorious changes, so you have to do the following:              // English
   // Copy matrix A to the appropriate dimensions of another matrix                          // English
   // In this way, the original values of the A matrix elements are kept - it will be needed // English
   for (i=0; i < MAX_i; i++)
   {   for (j=0; j < MAX_i; j++)
       {   if ( MAX_i == 10 )
	      A10[i][j] = A[i][j];
	   else
	      if ( MAX_i == 9 )
		 A9[i][j] = A[i][j];
	      else
		 if ( MAX_i == 8 )
		    A8[i][j] = A[i][j];
		 else
		    if ( MAX_i == 7 )
		       A7[i][j] = A[i][j];
		    else
		       if ( MAX_i == 6 )
			  A6[i][j] = A[i][j];
		       else
			  if ( MAX_i == 5 )
			     A5[i][j] = A[i][j];
			  else
			     if ( MAX_i == 4 )
				A4[i][j] = A[i][j];
			     else
				if ( MAX_i == 3 )
				   A3[i][j] = A[i][j];
				else
				   if ( MAX_i == 2 )
				      A2[i][j] = A[i][j];
       }
   }

   switch (z)
   {      case 10: i10 = 10; p10 = 10; goto T10;
	  case  9: i9  =  9; p9  =  9; goto T9;
	  case  8: i8  =  8; p8  =  8; goto T8;
	  case  7: i7  =  7; p7  =  7; goto T7;
	  case  6: i6  =  6; p6  =  6; goto T6;
	  case  5: i5  =  5; p5  =  5; goto T5;
	  case  4: i4  =  4; p4  =  4; goto T4;
	  case  3: i3  =  3; p3  =  3; goto T3;
	  case  2: i2  =  2; p2  =  2; goto T2;
	  default: printf("\n\nNierozpoznawalny rozmiar macierzy");               // Polski
                   // printf("\n\nUnrecognizable matrix dimension");              // English
                   printf("\n\nPrzyciœnij dowolny klawisz aby wyjœæ z programu"); // Polski
                   // printf ("\n\nPress any key to exit the program");           // English
		   getch();
		   exit(0);      // wymagany przez Dev C++  // required by Dev C++
   }


T10:
   if ( i10 < 10 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                    // the following line will be executed the first time after the code below this line // English
      W10 = W10 + znak_i10 * A10[0][p10] * W9;

   if ( i10 > 0 )  // po raz pierwszy dla 'T10' w³aœnie ten 'if' bêdzie wykonany // Polski
                   // the first time for 'T10' just this 'if' will be executed   // English
   {  p10 = 10 - i10;
      if ( p10 % 2 == 0 ) znak_i10 = 1; else znak_i10 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli dziesiêciu macierzy 9x9        // Polski
      // Creation co-factor matrices - ten matrices 9x9                          // English
      for (i=1; i < 10; i++)
	  for (j=0; j < 9; j++)
	      if ( j >= p10 )
		 A9[i-1][j] = A10[i][j+1];
	      else
		 A9[i-1][j] = A10[i][j];

      i10--; i9=9; W9=0;
      goto T9;
   }

// if ( MAX_i == 10 )              // Zablokowane linie s¹ przygotowane na rozszerzenie macierzy powy¿ej 10x10
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
// else
//    goto T11;


T9:
   if ( i9 < 9 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                  // the following line will be executed the first time after the code below this line // English
      W9 = W9 + znak_i9 * A9[0][p9] * W8;

   if ( i9 > 0 )  // po raz pierwszy dla 'T9' w³aœnie ten 'if' bêdzie wykonany  // Polski
                  // the first time for 'T9' just this 'if' will be executed    // English
   {  p9 = 9 - i9;
      if ( p9 % 2 == 0 ) znak_i9 = 1; else znak_i9 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli dziewiêciu macierzy 8x8       // Polish
      // Creation co-factor matrices - nine matrices 8x8                        // English
      for (i=1; i < 9; i++)
	  for (j=0; j < 8; j++)
	      if ( j >= p9 )
		 A8[i-1][j] = A9[i][j+1];
	      else
		 A8[i-1][j] = A9[i][j];

      i9--; i8=8; W8=0;
      goto T8;
   }

   if ( MAX_i == 9 )
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T10;


T8:
   if ( i8 < 8 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                  // the following line will be executed the first time after the code below this line // English
      W8 = W8 + znak_i8 * A8[0][p8] * W7;

   if ( i8 > 0 )  // po raz pierwszy dla 'T8' w³aœnie ten 'if' bêdzie wykonany  // Polski
                  // the first time for 'T8' just this 'if' will be executed    // English
   {  p8 = 8 - i8;
      if ( p8 % 2 == 0 ) znak_i8 = 1; else znak_i8 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli oœmiu macierzy 7x7            // Polish
      // Creation co-factor matrices - eight matrices 7x7                       // English
      for (i=1; i < 8; i++)
	  for (j=0; j < 7; j++)
	      if ( j >= p8 )
		 A7[i-1][j] = A8[i][j+1];
	      else
		 A7[i-1][j] = A8[i][j];

      i8--; i7=7; W7=0;
      goto T7;
   }

   if ( MAX_i == 8 )
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T9;


T7:
   if ( i7 < 7 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                  // the following line will be executed the first time after the code below this line // English
      W7 = W7 + znak_i7 * A7[0][p7] * W6;

   if ( i7 > 0 )  // po raz pierwszy dla 'T7' w³aœnie ten 'if' bêdzie wykonany  // Polski
                  // the first time for 'T7' just this 'if' will be executed    // English
   {  p7 = 7 - i7;
      if ( p7 % 2 == 0 ) znak_i7 = 1; else znak_i7 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli siedmiu macierzy 6x6          // Polski
      // Creation co-factor matrices - seven matrices 6x6                       // English
      for (i=1; i < 7; i++)
	  for (j=0; j < 6; j++)
	      if ( j >= p7 )
		 A6[i-1][j] = A7[i][j+1];
	      else
		 A6[i-1][j] = A7[i][j];

      i7--; i6=6; W6=0;
      goto T6;
   }

   if ( MAX_i == 7 )
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T8;


T6:
   if ( i6 < 6 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                  // the following line will be executed the first time after the code below this line // English
      W6 = W6 + znak_i6 * A6[0][p6] * W5;

   if ( i6 > 0 )  // po raz pierwszy dla 'T6' w³aœnie ten 'if' bêdzie wykonany  // Polski
                  // the first time for 'T6' just this 'if' will be executed    // English
   {  p6 = 6 - i6;
      if ( p6 % 2 == 0 ) znak_i6 = 1; else znak_i6 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli szeœciu macierzy 5x5          // Polski
      // Creation co-factor matrices - six matrices 5x5                         // English
      for (i=1; i < 6; i++)
	  for (j=0; j < 5; j++)
	      if ( j >= p6 )
		 A5[i-1][j] = A6[i][j+1];
	      else
		 A5[i-1][j] = A6[i][j];

      i6--; i5=5; W5=0;
      goto T5;
   }

   if ( MAX_i == 6 )
      goto koniec_obl_wyznacznika;  // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T7;


T5:
   if ( i5 < 5 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                  // the following line will be executed the first time after the code below this line // English
      W5 = W5 + znak_i5 * A5[0][p5] * W4;

   if ( i5 > 0 )  // po raz pierwszy dla 'T5' w³aœnie ten 'if' bêdzie wykonany  // Polski
                  // the first time for 'T5' just this 'if' will be executed    // English
   {  p5 = 5 - i5;
      if ( p5 % 2 == 0 ) znak_i5 = 1; else znak_i5 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli piêciu macierzy 4x4           // Polski
      // Creation co-factor matrices - five matrices 4x4                        // English
      for (i=1; i < 5; i++)
	  for (j=0; j < 4; j++)
	      if ( j >= p5 )
		 A4[i-1][j] = A5[i][j+1];
	      else
		 A4[i-1][j] = A5[i][j];

      i5--; i4=4; W4=0;
      goto T4;
   }

   if ( MAX_i == 5 )
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T6;


T4:
   if ( i4 < 4 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                  // the following line will be executed the first time after the code below this line // English
      W4 = W4 + znak_i4 * A4[0][p4] * W3;

   if ( i4 > 0 )  // po raz pierwszy dla 'T4' w³aœnie ten 'if' bêdzie wykonany  // Polski
                  // the first time for 'T4' just this 'if' will be executed    // English
   {  p4 = 4 - i4;
      if ( p4 % 2 == 0 ) znak_i4 = 1; else znak_i4 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli czterech macierzy 3x3         // Polski
      // Creation co-factor matrices - four matrices 3x3                        // English
      for (i=1; i < 4; i++)
	  for (j=0; j < 3; j++)
	      if ( j >= p4 )
		 A3[i-1][j] = A4[i][j+1];
	      else
		 A3[i-1][j] = A4[i][j];

      i4--; i3=3; W3=0;
      goto T3;
   }

   if ( MAX_i == 4 )
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T5;


T3:
   if ( i3 < 3 )  // poni¿sza linia bêdzie wykonana po raz pierwszy po kodzie poni¿ej jej              // Polski
                  // the following line will be executed the first time after the code below this line // English
      W3 = W3 + znak_i3 * A3[0][p3] * W2;

   if ( i3 > 0 )  // po raz pierwszy dla 'T3' w³aœnie ten 'if' bêdzie wykonany  // Polski
                  // the first time for 'T3' just this 'if' will be executed    // English
   {  p3 = 3 - i3;
      if ( p3 % 2 == 0 ) znak_i3 = 1; else znak_i3 = -1;
      // Zrobienie dope³nieñ algebraicznych czyli trzech macierzy 2x2           // Polski
      // Creation co-factor matrices - three matrices 2x2                       // English
      for (i=1; i < 3; i++)
	  for (j=0; j < 2; j++)
	      if ( j >= p3 )
		 A2[i-1][j] = A3[i][j+1];
	      else
		 A2[i-1][j] = A3[i][j];

      i3--;                   // i2=2; W2=0;  jest tu bez sensu  ( i2=2; W2=0;  is pointless here)
      goto T2;
   }

   if ( MAX_i == 3 )
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T4;


T2:
   W2 = A2[0][0] * A2[1][1] - A2[0][1] * A2[1][0];

   if ( MAX_i == 2 )
      goto koniec_obl_wyznacznika; // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   else
      goto T3;


koniec_obl_wyznacznika:  // in Polish 'koniec obliczania wyznacznika' means in English 'end of the determinant calculation'
   if ( w == 0 )
      if ( MAX_i > 9 )
      {  for (i=0; i < 65; i++) printf("\b");
	 for (i=0; i < 65; i++) printf(" ");
	 for (i=0; i < 65; i++) printf("\b");
      }
      else
	 if ( MAX_i > 5 )
	 {  for (i=0; i < 64; i++) printf("\b");
	    for (i=0; i < 64; i++) printf(" ");
	    for (i=0; i < 64; i++) printf("\b");
	 }


   if ( MAX_i == 10 )
   {  if ( w == -1 ) W = W10;  // wyznacznik g³ówny (coefficient matrix determinant)
      else
      {  // drukuj wyniki (print results)
	 printf("\tx%d=%6.3f", w+1, (float) W10/W);
	 if ( w > 0 && (w+1) % 4 == 0 ) printf("\n");
      }
	 w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
               // the next determinant with the column matrix with the constants will be calculated // English
	 if ( w < MAX_i )
	 {  W10=0; W9=0; W8=0; W7=0; W6=0; W5=0; W4=0; W3=0; W2=0; i10=10;
	    // skopiuj A do A10 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A10 macierz¹ wyrazów wolnych                          // Polski
            // copy A to A10 and at the same time replace appropriate column of the matrix A10 with the column matrix with the constants // English
	    for (i=0; i < MAX_i; i++)
		for (j=0; j < MAX_i; j++)
		    if ( j == w )
		       A10[i][j] = WW[i][0];
		    else
		       A10[i][j] = A[i][j];

	    goto T10;
	 }
   }

   else
    if ( MAX_i == 9 )
    {  if ( w == -1 ) W = W9;  // wyznacznik g³ówny (coefficient matrix determinant)
       else
       {  // drukuj wyniki (print results)
	  printf("\tx%d=%6.3f", w+1, (float) W9/W);
	  if ( w > 0 && (w+1) % 4 == 0 ) printf("\n");
       }
	  w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                // the next determinant with the column matrix with the constants will be calculated // English
	  if ( w < MAX_i )
	  {  W9=0; W8=0; W7=0; W6=0; W5=0; W4=0; W3=0; W2=0; i9=9;
	     // skopiuj A do A9 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A9 macierz¹ wyrazów wolnych                          // Polski
             // copy A to A9 and at the same time replace appropriate column of the matrix A9 with the column matrix with the constants // English
	     for (i=0; i < MAX_i; i++)
		 for (j=0; j < MAX_i; j++)
		     if ( j == w )
			A9[i][j] = WW[i][0];
		     else
			A9[i][j] = A[i][j];

	     goto T9;
	  }
    }

    else
     if ( MAX_i == 8 )
     {  if ( w == -1 ) W = W8;  // wyznacznik g³ówny (coefficient matrix determinant)
	else
	{  // drukuj wyniki (print results)
	   printf("\tx%d=%6.3f", w+1, (float) W8/W);
	   if ( w > 0 && (w+1) % 4 == 0 ) printf("\n");
	}
	   w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                 // the next determinant with the column matrix with the constants will be calculated // English
	   if ( w < MAX_i )
	   {  W8=0; W7=0; W6=0; W5=0; W4=0; W3=0; W2=0; i8=8;
	      // skopiuj A do A8 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A8 macierz¹ wyrazów wolnych                          // Polski
              // copy A to A8 and at the same time replace appropriate column of the matrix A8 with the column matrix with the constants // English
	      for (i=0; i < MAX_i; i++)
		  for (j=0; j < MAX_i; j++)
		      if ( j == w )
			 A8[i][j] = WW[i][0];
		      else
			 A8[i][j] = A[i][j];

	      goto T8;
	   }
     }

     else
      if ( MAX_i == 7 )
      {  if ( w == -1 ) W = W7;  // wyznacznik g³ówny (coefficient matrix determinant)
	 else
	 {  // drukuj wyniki (print results)
	    printf("\tx%d=%6.3f", w+1, (float) W7/W);
	    if ( w > 0 && (w+1) % 4 == 0 ) printf("\n");
	 }
	    w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                  // the next determinant with the column matrix with the constants will be calculated // English
	    if ( w < MAX_i )
	    {  W7=0; W6=0; W5=0; W4=0; W3=0; W2=0; i7=7;
	       // skopiuj A do A7 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A7 macierz¹ wyrazów wolnych                          // Polski
               // copy A to A7 and at the same time replace appropriate column of the matrix A7 with the column matrix with the constants // English
	       for (i=0; i < MAX_i; i++)
		   for (j=0; j < MAX_i; j++)
		       if ( j == w )
			  A7[i][j] = WW[i][0];
		       else
			  A7[i][j] = A[i][j];

	       goto T7;
	    }
      }

      else
       if ( MAX_i == 6 )
       {  if ( w == -1 ) W = W6;  // wyznacznik g³ówny (coefficient matrix determinant)
	  else
	  {  // drukuj wyniki (print results)
	     printf("\tx%d=%6.3f", w+1, (float) W6/W);
	     if ( w > 0 && (w+1) % 4 == 0 ) printf("\n");
	  }
	     w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                   // the next determinant with the column matrix with the constants will be calculated // English
	     if ( w < MAX_i )
	     {  W6=0; W5=0; W4=0; W3=0; W2=0; i6=6;
		// skopiuj A do A6 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A6 macierz¹ wyrazów wolnych                          // Polski
                // copy A to A6 and at the same time replace appropriate column of the matrix A6 with the column matrix with the constants // English
		for (i=0; i < MAX_i; i++)
		    for (j=0; j < MAX_i; j++)
			if ( j == w )
			   A6[i][j] = WW[i][0];
			else
			   A6[i][j] = A[i][j];

		goto T6;
	     }
       }

       else
	if ( MAX_i == 5 )
	{  if ( w == -1 ) W = W5;  // wyznacznik g³ówny (coefficient matrix determinant)
	   else
	   {  // drukuj wyniki (print results)
	      printf("\tx%d=%6.3f", w+1, (float) W5/W);
	      if ( w > 0 && (w+1) % 4 == 0 ) printf("\n");
	   }
	      w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                    // the next determinant with the column matrix with the constants will be calculated // English
	      if ( w < MAX_i )
	      {  W5=0; W4=0; W3=0; W2=0; i5=5;
		 // skopiuj A do A5 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A5 macierz¹ wyrazów wolnych                          // Polski
                 // copy A to A5 and at the same time replace appropriate column of the matrix A5 with the column matrix with the constants // English
		 for (i=0; i < MAX_i; i++)
		     for (j=0; j < MAX_i; j++)
			 if ( j == w )
			    A5[i][j] = WW[i][0];
			 else
			    A5[i][j] = A[i][j];

		 goto T5;
	      }
	}

	else
	 if ( MAX_i == 4 )
	 {  if ( w == -1 ) W = W4;  // wyznacznik g³ówny (coefficient matrix determinant)
	    else
	    {  // drukuj wyniki (print results)
	       printf("\tx%d=%6.3f", w+1, (float) W4/W);
	    }
	       w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                     // the next determinant with the column matrix with the constants will be calculated // English
	       if ( w < MAX_i )
	       {  W4=0; W3=0; W2=0; i4=4;
		  // skopiuj A do A4 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A4 macierz¹ wyrazów wolnych                          // Polski
                  // copy A to A4 and at the same time replace appropriate column of the matrix A4 with the column matrix with the constants // English
		  for (i=0; i < MAX_i; i++)
		      for (j=0; j < MAX_i; j++)
			  if ( j == w )
			     A4[i][j] = WW[i][0];
			  else
			     A4[i][j] = A[i][j];

		  goto T4;
	       }
	 }

	 else
	  if ( MAX_i == 3 )
	  {  if ( w == -1 ) W = W3;  // wyznacznik g³ówny (coefficient matrix determinant)
	     else
	     {  // drukuj wyniki (print results)
		printf("\tx%d=%6.3f", w+1, (float) W3/W);
	     }
		w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                      // the next determinant with the column matrix with the constants will be calculated // English
		if ( w < MAX_i )
		{  W3=0; W2=0; i3=3;
		   // skopiuj A do A3 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A3 macierz¹ wyrazów wolnych                          // Polski
                   // copy A to A3 and at the same time replace appropriate column of the matrix A3 with the column matrix with the constants // English
		   for (i=0; i < MAX_i; i++)
		       for (j=0; j < MAX_i; j++)
			   if ( j == w )
			      A3[i][j] = WW[i][0];
			   else
			      A3[i][j] = A[i][j];

		   goto T3;
		}
	  }

	  else
	   if ( MAX_i == 2 )
	   {  if ( w == -1 ) W = W2;  // wyznacznik g³ówny (coefficient matrix determinant)
	      else
	      {  // drukuj wyniki (print results)
		 printf("\tx%d=%6.3f", w+1, (float) W2/W);
	      }
		 w++;  // bêdzie obliczony nastêpny wyznacznik z wyrazami wolnymi                           // Polski
                       // the next determinant with the column matrix with the constants will be calculated // English
		 if ( w < MAX_i )
		 {  W2=0; i2=2;
		    // skopiuj A do A2 i jednoczeœnie wymieñ odpowiedni¹ kolumnê macierzy A2 macierz¹ wyrazów wolnych                          // Polski
                    // copy A to A2 and at the same time replace appropriate column of the matrix A2 with the column matrix with the constants // English
		    for (i=0; i < MAX_i; i++)
			for (j=0; j < MAX_i; j++)
			    if ( j == w )
			       A2[i][j] = WW[i][0];
			    else
			       A2[i][j] = A[i][j];

		    goto T2;
		 }
	   }


   printf("\n\n\n\tPrzyciœnij dowolny klawisz aby wyjœæ z programu"); // Polski
   // printf("\n\n\nPress any key to exit the program");              // English
   getch();
   exit(0);      // wymagany przez Dev C++  (required by Dev C++)
}                // koniec funkcji 'main()' (end of the function 'main()')
