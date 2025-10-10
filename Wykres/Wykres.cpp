/*****************************************************************
 *     WYKRES.cpp   -	wykres funkcji, wersja podstawowa
 *
 *	Pozostaje do zrobienia:
 *	 etap1:	1. StworzyÜ tablic© moæliwych nazw funkcji np. "Kosinus" byàby
 *			   przerobiony na "cos".
 *	 etap2: 1. Rozszerzenie analizy do trzech funkcji rysowanych
 *					na jednym ukàadzie wsp¢àrz©dnych w tym tylko
 *					jednej "funkcji dowolnej postaci".
 *	 etap3:	1. Zmiana parametr¢w dla tych samych wykres¢w funkcji,
 *			2. Analiza paru funkcji w tym samym czasie,
 *			3. Aktywacja klawisza [ESC] i "pomocy" dla reszty programu,
 *			4. Poprawa funkcjonalnoòci dowolnych klawiszy dla reszty programu,
 *			5. Faza ostateczna analizy:
 *				- ostateczne zatwierdzenie funkcji programu,
 *				- testowanie programu,
 *				- implementacja programu.
 *****************************************************************/

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <process.h>
#include <math.h>
#include <alloc.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h> 	/*  dla isdigit(), tolower()	*/

#define XMAX    640
#define YMAX    480
#define lewa  22	/* pozycje obrazu tekstowego "PORZUCENIE PROGRAMU" */
#define gora   8
#define prawa 58
#define dol   14
#define lewa_gr  180	/* pozycje obrazu graficznego "PORZUCENIE PROGRAMU" */
#define gora_gr  140
#define prawa_gr 460
#define dol_gr   280

int i, j, k, l;	/* liczniki; m, mm,... s• licznikami, zmiennymi lokalnymi...*/
int opcja = 0;	/*... n jest zarezerwowane dla stopnia wielomianu */
int kolor_tla_ekranu_opcji = 11;
int kolor_tla_wyboru_parametrow = 7;
int zle, z;
char znak;
char *ptr_znak;
char Z[100];        /* 100 ze wzgl©du na tablic© A[] */
int dl_lancucha;
int proba_poprawienia = 0;
int proba_porzucenia = 0;
int wezwanie_pomocy = 0;
int pozycja_kursora_x, pozycja_kursora_y;
int sygnal = 0;

/* Pierwsze przypisania s• konieczne w przypadku omini©cia wyboru parametr¢w wykresu funkcji
   Drugie - gdy parametry s• wybierane */
int dl_jedn_na_osi_OX = 50; int dl_jedn_OX = 50;
int dl_jedn_na_osi_OY = 50; int dl_jedn_OY = 50;
int zmniejszenie_jednostki_OY = 1;
int nr_wzoru_tla = 1; int nr_wz_tla = 1;
int nr_koloru_tla = 7; int nr_kol_tla = 7;
int nr_koloru_osi = 12; int nr_kol_osi = 12;
int nr_koloru_wykresu = 10; int nr_kol_wykresu = 10;

/* wielomian */
char W[11][15];	       /* Tablica wsp¢àczynnik¢w dla wielomianu */
char *ptr_W[11];
float w[11];
int n;		       /* stopie‰ wielomianu */
int ilosc_kropek_dziesietnych;

int ilosc_skokow = 0;  /* licznik przeskok¢w z "Tak" do "Nie" i odwrotnie...*/
		       /*...do funkcji "czy_porzucic_program" odnawiany po liczbie 20  */
int buff[52][14]; /* bufor dla obrazu zast©powanego przez "czy_porzucic_... */
/*...program" i "pomoc". Ten bufor jest lekko nadmiarowy na wszelki wypadek */
int strona;	       /* nr strony "POMOC" */
float x, y, y1;        /* wartoòci faktyczne */
int wielomian = 0;
/*-------------------------------------------------------------------------*/
/* Poniæej: zmienne i ich typy dla "funkcji dowolnej" */
int funkcja_dowolna = 0;
int jest_cyfra = 0;
char A[100];
char *ptrA;
int d_l_A;
int d_l;
char B[100];	/*  wierna kopia àa‰cucha A - w celu ewentualnej poprawy A  */
char C[150];	/*  faktyczny àa‰cuch poddany obliczeniom  */
int d_l_C;
float a;
int jest_x = 0;
int zmniejsz_d_l;
int wskaznik;
float aa, bb;
float yy;
int dodawanie = 0, odejmowanie = 0, mnozenie = 0, dzielenie = 0;
int dzialanie;

int nr_nawiasu_otwartego;
int nr_nawiasu_zamknietego;
int poczatek_operacji;
int koniec_operacji;
int pozycja_nawiasu;
char D[100];    /* to àa‰cuch w nawiasie najbardziej wewn©trznym lub w og¢le caày */
int d_l_D;
char *ptrD;
char D1[65];	/* drugi argument dla mod( , ) lub pow( , )	*/
char *ptrD1;	/* 		-- " --				*/

char E[78];	/*  miejsce raportu bà©d¢w  */
char *ptrE;

char CF[150];
int d_l_CF;
int jest_funkcja;   /* jeæeli jest jakaò litera<>'x' to MUSI to byÜ funkcja;
		       'e' i 'pi' zostaày juæ wykryte;
		       obydwa: poz_ i p_ znacz• 'pozycja notacji funkcji;
		       _1 - pierwsza funkcja', _2 - druga taka sama funkcja */
int jest_ln  , poz_ln_1  , poz_ln_2  , p_ln_1  , p_ln_2  ;
int jest_lg  , poz_lg_1  , poz_lg_2  , p_lg_1  , p_lg_2  ;
int jest_cos , poz_cos_1 , poz_cos_2 , p_cos_1 , p_cos_2 ;
int jest_sin , poz_sin_1 , poz_sin_2 , p_sin_1 , p_sin_2 ;
int jest_tan , poz_tan_1 , poz_tan_2 , p_tan_1 , p_tan_2 ;
int jest_cosh, poz_cosh_1, poz_cosh_2, p_cosh_1, p_cosh_2;
int jest_sinh, poz_sinh_1, poz_sinh_2, p_sinh_1, p_sinh_2;
int jest_tanh, poz_tanh_1, poz_tanh_2, p_tanh_1, p_tanh_2;
int jest_acos, poz_acos_1, poz_acos_2, p_acos_1, p_acos_2;
int jest_asin, poz_asin_1, poz_asin_2, p_asin_1, p_asin_2;
int jest_atan, poz_atan_1, poz_atan_2, p_atan_1, p_atan_2;
int jest_abs , poz_abs_1 , poz_abs_2 , p_abs_1 , p_abs_2 ;
int jest_mod , poz_mod_1 , poz_mod_2 , p_mod_1 , p_mod_2 ;
int jest_pow , poz_pow_1 , poz_pow_2 , p_pow_1 , p_pow_2 ;
int jest_exp , poz_exp_1 , poz_exp_2 , p_exp_1 , p_exp_2 ;
int jest_sq  , poz_sq_1  , poz_sq_2  , p_sq_1  , p_sq_2  ;
int p; /* wsp¢lny wska´nik dla wszystkich funkcji dla testu na ich niepustoòÜ */
int operacje_na_funkcji = 0;
int ilosc_przecinkow_faktyczna, ilosc_przecinkow_przewidywana;
int jest_przecinek = 0;
/*-------------------------------------------------------------------------*/
int porzuc;
int jest_problem_z_dziedzina = 0; /* czyli nie ma problemu - dla pot©gowania */
unsigned rozmiar;
void far *ptr_do_alokacji_pamieci;
int blad = 0;			  /* dla funkcji "znaleziono_blad()" */

/* tablicowane zmienne do analizy funkcji */
float d_p[30];		     /* dziedzina funkcji - pocz•tek zapisu w nawiasie */
float d_k[30];		     /* dziedzina funkcji - koniec zapisu w nawiasie */
int l_d = 0;
int dziedzina;
float m_z[15];		     /* miejsca zerowe funkcji */
int l_m_z = 0;
float e_max[15];	     /* ekstrema funkcji - maksimum */
float e_max_x[15];
int l_e_max = 0;
float e_min[15];	     /* ekstrema funkcji - minimum */
float e_min_x[15];
int l_e_min = 0;

void wprowadzenie(void);
void wybieranie_postaci_funkcji(void);
void okno_najwieksze(void);
void wybieranie_wielomianu(void);
void usun_spacje_i_analizuj(void);
void popraw_zapis_liczby(void);
void zbadaj_wielkosc_liczby(void);
void wybieranie_funkcji_dowolnej(void);
void pytanie_o_zapis(void);
void tablica_operatorow_i_funkcji(void);
void grafika_wstepu(void);
void wybory_parametrow(void);
void dlugosc_jednostki_osi_OX(void);
void dlugosc_jednostki_osi_OY(void);
void nr_wzoru_tla_ekranu(void);
void okno_wzorow_tla_i_barw(void);
void nr_koloru_tla_ekranu(void);
void nr_koloru_osi_ukladu_wspolrz(void);
void nr_koloru_wykresu_funkcji(void);
void wstep_rutynowy(void);
void wstepna_analiza_znakow(void);
void brak_mozliwosci_poprawiania(void);
void tlo_wykresu_funkcji(void);
void wykres_funkcji(void);

/* raport bà©d¢w */
void nie_liczba_rzeczywista(void);
void za_dlugi_lancuch(void);
void usun_spacje(void);
void nie_liczba_naturalna(void);
void liczba_poza_zakresem(void);
void kolor_ten_sam(void);
void wyczysc_raport_bledu(void);
void wyczysc_informacje(void);
void znaleziono_blad(void);	/* raport bà©du (jednego z 4-ech) pojawiaj•cy...*/
				/*...si© na ekranie graficznym - wczeòniej nie..*/
				/*..wykryty lub po prostu bà•d transmisji danych*/
/* porzucenie programu i pomoc*/
void czy_porzucic_program(void);
void zdania_sprzeczne_ze_soba(int ilosc_skokow);
void czy_porzucic_program_gr(void);
void pomoc(void);
void pomoc_gr(void);

/*-------------------------------------------------------------------------*/
/* Poniæej: funkcje i ich typy dla "funkcji dowolnej" */
void wpisz_lancuch_i_analizuj_go(void);	       /* ... aæ do skutku */
void popraw_wyrazenie(void);
void czy_jest_argument(void);
void dzialania_w_nawiasie_wewn_test(void);
void dzialania_w_nawiasie_wewn(void);
void usun_tylko_nawiasy(void);
void wprowadz_liczbe_do_lancucha(void);
float wynik_prostego_dzialania(float aa, float bb);

void funkcja_dowolnej_postaci(void);
void oblicz_wartosc_funkcji_matem(void);
int czy_brak_obliczen(void);
/*-------------------------------------------------------------------------*/
void menu(void);
void analiza_funkcji(void);
void okno_analizy_funkcji(void);

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//      Funkcja inicjuj•ca					        //
//									//
//			wprowadzenie();					//
//	  		wybieranie_postaci_funkcji();                   //
//			grafika_wstepu();				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void main(void)
{       wprowadzenie();
	wybieranie_postaci_funkcji();
	grafika_wstepu();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	main() 	 <-- Funkcje wywoàuj•ce ten moduà			//
//                                                                      //
//			Graficzny obraz wprowadzenia do programu        //
//								        //
//			czy_porzucic_program_gr() <-- Funkcje wywoàane  //
//                                                    z tego moduàu     //
//			pomoc_gr()  					//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wprowadzenie(void)
{	int driver = VGA, mode = VGAHI, errorcode;
	int kwadrat_maksymalny[] = {0, 0, XMAX-1, 0, XMAX-1, YMAX-5, 0, YMAX-5, 0, 0};
	unsigned rozmiar;
	void far *ptr_do_alokacji_pamieci;

	initgraph(&driver, &mode, "c:\\TURBOC3\\bgi");   /*  d:\\tc\\bgi"  */

	errorcode = graphresult();
	if(errorcode != grOk)
	{	printf("\nBà•d grafiki (moduà 'wprowadzenie'): %s\n", grapherrormsg(errorcode));
		printf("Przyciònij dowolny klawisz aby wejòÜ do edytora : ");
		getch();
		exit(1);
	}

	setfillstyle(1, 8);
	fillpoly(5, kwadrat_maksymalny);
	setcolor(9);

	setcolor(3);
	moveto(185,20);     // moveto(260,20);
	settextstyle(1, HORIZ_DIR, 1);
	outtext("Leszek Buczek (czerwiec 1998)");
	moveto(215,45);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("przedstawia program o nazwie");

	setcolor(9);
	moveto(150,60);
	settextstyle(1, HORIZ_DIR, 5);
	outtext("WYKRES FUNKCJI");

	i = 50;
	setcolor(10);
	settextstyle(2, HORIZ_DIR, 6);
	moveto(i+15,120);
	outtext("To Tw¢j program! Mozesz go skopiowac od koleg¢w lub");
	moveto(i,140);
	outtext("kolezanek i wykorzystywac go do lekcji matematyki jak");
	moveto(i,160);
	outtext("i dla wlasnych cel¢w poznawczych. Korzystajac z niego");
	moveto(i,180);
	outtext("zadawaj sobie zawsze pytania dlaczego jest tak a nie");
	moveto(i,200);
	outtext("inaczej i szukaj zgodnosci z wlasnymi rozwiazaniami.");

	setcolor(9);
	moveto(i+15,225);
	outtext("Nigdy nie wierz bezgranicznie w to co zobaczysz. Sam");
	moveto(i,245);
	outtext("program nosi w sobie bledy przyblizen ale opr¢cz tego");
	moveto(i,265);
	outtext("w naukach scislych staraj sie miec postawe krytyczna");
	moveto(i,285);
	outtext("wobec tego co widzisz, czujesz i w og¢le doswiadczasz.");

	setcolor(14);
	moveto(i+15,310);
	outtext("Pamietaj ze 'patrzec' to jeszcze nie znaczy 'widziec'.");
	moveto(i,330);
	outtext("Widziec mozna tylko to, co mozna sobie wyobrazic.");
	moveto(i,350);
	outtext("Gdy znajdziesz powiazania pomiedzy liniami wykresu a tym,");
	moveto(i,370);
	outtext("co obserwujesz, osiagniesz najwyzszy etap poznawczy");
	moveto(i,390);
	outtext("matematyki a ja bede zachwycony ze osiagnalem sw¢j cel...");
	setcolor(9);
	moveto(i+250,410);
	outtext("...dajac Tobie ten program.");

	setcolor(7);
	moveto(90,440);
	outtext("NACISNIJ DOWOLNY KLAWISZ ABY WEJSC DO PROGRAMU");

	do
	{	proba_porzucenia = 0;
		wezwanie_pomocy = 0;
		znak = getch();
		if(znak == 27)
		{	proba_porzucenia = 1;
			rozmiar = imagesize(lewa_gr, gora_gr, prawa_gr, dol_gr);
			if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
			{	closegraph();
				printf("\nBà•d (1): W pami©ci nie ma miejsca dla przechowania obrazu");
				printf("\nJego rozmiar = %u bajt¢w jest za duæy", rozmiar);
				printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(lewa_gr, gora_gr, prawa_gr, dol_gr, ptr_do_alokacji_pamieci);
			czy_porzucic_program_gr();
			putimage(lewa_gr, gora_gr, ptr_do_alokacji_pamieci, COPY_PUT);
			farfree(ptr_do_alokacji_pamieci);
		} else
		if(znak == 0)
		{	if(getch() == 59)
			{	wezwanie_pomocy = 1;
			rozmiar = imagesize(lewa_gr-30, gora_gr-30, prawa_gr+30, dol_gr+30);
			if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
			{	closegraph();
				printf("\nBà•d (2): W pami©ci nie ma miejsca dla przechowania obrazu\n");
				printf("\nJego rozmiar = %u bajt¢w jest za duæy ", rozmiar);
				printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(lewa_gr-30, gora_gr-30, prawa_gr+30, dol_gr+30, ptr_do_alokacji_pamieci);
			pomoc_gr();
			putimage(lewa_gr-30, gora_gr-30, ptr_do_alokacji_pamieci, COPY_PUT);
			farfree(ptr_do_alokacji_pamieci);
			} else getch();
		}
	} while( proba_porzucenia || wezwanie_pomocy);

	closegraph();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	main()  							//
//	menu() 								//
//	znaleziono_blad() 						//
//                                                                      //
//			Wyb¢r postaci funkcji				//
//									//
//			okno_najwieksze() 				//
//			czy_porzucic_program() 			        //
//			wyczysc_informacje() 			        //
//			pomoc() 					//
//			wybieranie_wielomianu() 		        //
//			wybieranie_funkcji_dowolnej() 	                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wybieranie_postaci_funkcji(void)
{	textbackground(2); clrscr();
	textcolor(14); /* textbackground(10);  */
	okno_najwieksze();
	textcolor(9); gotoxy(28, 3);
	cprintf("Wybierz postaÜ funkcji");
	textcolor(5); gotoxy(10, 6);
	cprintf("1.  Wielomian postaci ax^n + ... + bx^2 + cx + d");
	gotoxy(10, 8);
	cprintf("2.  Dowolna postaÜ wyraæenia f(x)");
	textcolor(11); gotoxy(2, 25);
	cprintf("                                 Tw¢j wyb¢r:               "
			"                   "); textcolor(1); gotoxy(47, 25);
	znak = getch();
	while( znak != '1' && znak != '2' )
	{	if(znak == 27)
		{	gettext(lewa, gora, prawa, dol, buff);
			czy_porzucic_program();
			wyczysc_informacje();
			textcolor(11); textbackground(10); gotoxy(2, 25);
			cprintf("                                 Tw¢j wyb¢r:          "
					"                        "); textcolor(1); gotoxy(47, 25);
			znak = getch();
			continue;
		}
		if(znak == 0)
		{	if(getch() == 59)
			{	gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
				strona = 2;
				pomoc();
				textcolor(11); textbackground(10); gotoxy(2, 25);
				cprintf("                                 Tw¢j wyb¢r:"
						"                                  ");
				textcolor(1); gotoxy(47, 25);
				znak = getch();
				continue;
			} else getch();
		}
		textcolor(14); textbackground(4); gotoxy(2, 25);
		cprintf("                     çLE !  Masz do wyboru \"1\" albo \"2\"                       ");
		delay(1000);
		textcolor(11); textbackground(10); gotoxy(2, 25);
		cprintf("                  Wybierz jedn• z dw¢ch opcji (1 albo 2)                      ");
		textcolor(1); gotoxy(59, 25);
		znak = getch();
	}
	cprintf("%c", znak); delay(500);
	if(znak == '1') wybieranie_wielomianu(); else wybieranie_funkcji_dowolnej();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_postaci_funkcji() 					//
//                                                                      //
//			Definiowanie wielomianu				//
//									//
//			okno_najwieksze() 				//
//			czy_porzucic_program() 			        //
//			wyczysc_informacje() 			        //
//			pomoc() 					//
//			wstep_rutynowy() 				//
//			usun_spacje_i_analizuj() 		        //
//			popraw_zapis_liczby() 			        //
//			zbadaj_wielkosc_liczby() 		        //
//                      tlo_wykresu_funkcji()                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wybieranie_wielomianu(void)
{       wielomian = 1; funkcja_dowolna = 0;

	clrscr();
	textcolor(14); textbackground(7);
	okno_najwieksze();
	textcolor(9); gotoxy(36, 3);
	cprintf("Wielomian");
	textcolor(5); gotoxy(27, 4);
	cprintf("ax^n + ... + bx^2 + cx + d");
	textcolor(6); gotoxy(24, 6);
	cprintf("Podaj stopie‰ wielomianu (1ˆ9): ");
	textcolor(1);

	znak = getch();
	while( znak < '1' || znak > '9' )
	{	if(znak == 27)
		{	pozycja_kursora_x = wherex();
			pozycja_kursora_y = wherey();
			gettext(lewa, gora, prawa, dol, buff);
			czy_porzucic_program();
			wyczysc_informacje();
			textbackground(kolor_tla_wyboru_parametrow);
			gotoxy(pozycja_kursora_x, pozycja_kursora_y);
			znak = getch();
			continue;
		}
		if(znak == 0)
		{	if(getch() == 59)
			{	pozycja_kursora_x = wherex();
				pozycja_kursora_y = wherey();
				gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
				strona = 3;
				pomoc();
				textcolor(1); textbackground(7);
				gotoxy(pozycja_kursora_x, pozycja_kursora_y);
				znak = getch();
				continue;
			} else getch();
		}
		if(znak > 32 && znak < 127) cprintf("%c", znak);

		textcolor(14); textbackground(4); gotoxy(2, 25);
		cprintf("            çLE !  Masz do wyboru cyfry 1, 2, 3, 4, 5, 6, 7, 8 i 9            ");
		delay(1000);
		textcolor(11); textbackground(10); gotoxy(2, 25);
		cprintf("                Wybierz jedn• z dziewi©ciu opcji (od 1 do 9)                  ");
		textcolor(1); textbackground(7); gotoxy(56, 6); printf(" \b");
		znak = getch();
	}

	cprintf("%c", znak);
	textcolor(11); textbackground(10); gotoxy(2, 25);
	cprintf("                                       "
			"                                       ");
	textcolor(4); textbackground(7); gotoxy(12, 8);
	cprintf("y(x) = "); *ptr_znak = znak; n = atoi(ptr_znak);
	for(l=0; l<n-1; l++)
	{	if(l == 5) gotoxy(19, 9);
		cprintf("a(%d)x^%d + ", l+1, n-l);
	}
	if(l == 5) gotoxy(19, 9);
	cprintf("a(%d)x + a(%d)", l+1, l+2);
	textcolor(5); gotoxy(12, 11);
	cprintf("Podaj wsp¢àczynniki wielomianu %d-go stopnia :", n);
	j = 0;

	for(l=1; l<n+2; l++)
	{   zle = 0;
		j++;
		textcolor(6); textbackground(7);
		if(l>5) gotoxy(45, 1+l+j); else gotoxy(20, 11+l+j);
		cprintf("a(%d) = ", l);
		textcolor(9);

		do
		{	wstep_rutynowy();
			for(k=0; k<=i; k++)
				W[l][k] = Z[k];
			if(i == 0)
			{   zle = 0;
				W[l][i] = '0';	   /* przykrycie '\0' przez '0' */
				W[l][++i] = '\0';
			}
			else
			if(sygnal)
			{	if(znak != 13)     /* && znak != 27) ???????? chyba juæ zbyteczne*/
				{   zle = 1;
					printf("\x07");
					W[l][i] = '\0';
					textcolor(14); textbackground(4); gotoxy(2, 25);
					cprintf("  Niedozwolona wi©ksza iloòÜ znak¢w. "
							"[ENTER] - akceptuj, [<--] - usu‰ cyfry.  ");
					delay(1000);
					textcolor(11); textbackground(10); gotoxy(2, 25);
					cprintf("   Liczba moæe skàadaÜ si© maksymalnie z 14 "
							"znak¢w.  Dopuszczone s• spacje.   ");
					textcolor(9); textbackground(7);
					if(l>5)
						if(l==10) gotoxy(67, 1+l+j); else gotoxy(66, 1+l+j);
					else gotoxy(41, 11+l+j);
				}
			} else
				zle = 0;
		} while(zle);

		if(i!=0)		/* 'i' nigdy nie b©dzie == 0 ale...(?) */
		{	if(l>5)
				if(l==10) gotoxy(53, 1+l+j); else gotoxy(52, 1+l+j);
			else gotoxy(27, 11+l+j);
			printf("               ");
		}
		if(W[l][0] != '0' && i != 1)
		{	usun_spacje_i_analizuj();
			popraw_zapis_liczby();	   /* np. +.4500 -> 0.45 ; -000.0 -> 0 */
		}
		if(zle) continue;
		ptr_W[l] = W[l];	/* tu jest liczba ale trzeba zbadaÜ jej wielkoòÜ */
		w[l] = atof(ptr_W[l]);
		zbadaj_wielkosc_liczby();
		if(zle) continue;
		if(l>5)			/* tu liczba jest zaakceptowana */
			if(l==10) gotoxy(53, 1+l+j); else gotoxy(52, 1+l+j);
		else gotoxy(27, 11+l+j);
		textcolor(1);
		cprintf("%s", W[l]);
				/* printf("k = %d", k);    NIE MAM POJECIA DLACZEGO TU k=101 A NIE 100... */
		if(k < 100 )    /* ...DLA OBCINANYCH LICZB */
		{	textbackground(10); gotoxy(2, 25);
			cprintf("                                                      "
					"                       ");
		}
	}

	do
	{       gotoxy(2,25); textcolor(4); textbackground(10);
		cprintf("       [Enter] - wykres funkcji;         "
			"[p] - wyb¢r parametr¢w wykresu       ");
		znak = getch();
		if(znak == 13) tlo_wykresu_funkcji();
		/* W przypadku rezygnacji ze zmian parametr¢w wykresu funkcji,
		   nast©puj•ce zmienne wchodz•ce do moduà¢w wykresu maj• opcjonalne wartoòci:
		   dl_jedn_na_osi_OX = 50
		   dl_jedn_na_osi_OY = 50
		   zmniejszenie_jednostki_OY = 1  // znaczy ignoruj skal©; 10 - zmniejsz jednostk© 10 razy
		   nr_wzoru_tla = 1               // niebieski
		   nr_koloru_tla = 7              // jasnoszary
		   nr_koloru_osi = 12             // jasnoczerwony
		   nr_koloru_wykresu = 10         // jasnozielony
		*/
		if(znak == 'p') break;  // wyjdzie z p©tli 'do' i z caàego moduàu

		proba_porzucenia = wezwanie_pomocy = 0;
		if(znak == 27)
		{	proba_porzucenia = 1;
			gettext(lewa, gora, prawa, dol, buff);
			czy_porzucic_program();
			continue;
		}
		if(znak == 0)
			if(getch() == 59)
			{   wezwanie_pomocy = 1;
				gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
				strona = 3;
				pomoc();
			}
	} while( proba_porzucenia || wezwanie_pomocy );
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_wielomianu()						//
//                                                                      //
//			Usuwanie spacji i test na liczb© rzeczywist•	//
//									//
//			nie_liczba_rzeczywista() 		        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void usun_spacje_i_analizuj(void)
{       int m, mm;
	int jest_cyfra = 0;

	ilosc_kropek_dziesietnych = 0;
	dl_lancucha = i;
	for(k=0; k<dl_lancucha; k++)
	{	if(W[l][k]==32)
		{	for(mm=k; mm<dl_lancucha; mm++) W[l][mm] = W[l][mm+1];
			dl_lancucha--;
			k--;
		}
	}
			/*	k = dl_lancucha;*/	/* to jest zbyteczne bo "k" jest juæ nieuæywane */
	if(W[l][0] == '-' || W[l][0] == '+')
		m = 1;
	else
		m = 0;
	for(mm=m; mm<dl_lancucha; mm++)
		if(W[l][mm] >= '0' && W[l][mm] <= '9') { jest_cyfra = 1; break; }
	if(!jest_cyfra) nie_liczba_rzeczywista();
	else
		for(mm=m; mm<dl_lancucha; mm++)
		{	if(W[l][mm]=='.')
				ilosc_kropek_dziesietnych++;
			if( ( ( W[l][mm] < '0' || W[l][mm] > '9') && W[l][mm] != '.')
				|| ilosc_kropek_dziesietnych > 1)
			{	nie_liczba_rzeczywista();
				if(zle) break;
			}
		}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	usun_spacje_i_analizuj() 					//
//                                                                      //
//			Raport bà©du liczby rzeczywistej		//
//									//
//////////////////////////////////////////////////////////////////////////
void nie_liczba_rzeczywista(void)
{	textcolor(14); textbackground(4); gotoxy(2, 25);
	cprintf("          çLE !  Tu ma byÜ liczba rzeczywista w "
			"zapisie dziesi©tnym.          ");
	delay(1000);
	textcolor(11); textbackground(10); gotoxy(2, 25);
	cprintf("     Przykàady:  3,  4.55,  .61,  0.61,  -.61,  -0.61,  "
			"-123.45,  +123.45     ");
	for(k=dl_lancucha; k>0; k--) W[l][k-1] = W[l][k]; /* skasuj liczb© na.. */
	zle = 1; l--; j--; /*..wszelki wypadek. "k" i tak jest odnawiane jako 0 */
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_wielomianu() 					//
//                                                                      //
//			Poprawa formatu liczby				//
//									//
//////////////////////////////////////////////////////////////////////////
void popraw_zapis_liczby(void)		/* np. +.4500 -> 0.45 ; -000.0 -> 0 */
{       int jest_cyfra_znaczaca = 0;
	int usun_tylko_kropke = 0;
	int m;

	for(k=0; k<dl_lancucha; k++)
	{	if( W[l][k] >= '1' && W[l][k] <= '9' ) jest_cyfra_znaczaca = 1;
		if(jest_cyfra_znaczaca || W[l][k] == '.') break;
		else
			if(W[l][k] != '-')
			{	for(m=k; m<dl_lancucha; m++) W[l][m] = W[l][m+1];
				dl_lancucha--;
				k--;
			}
	}

	if(!jest_cyfra_znaczaca && W[l][k] == '.')
	{	for(m=dl_lancucha; m>=k; m--) W[l][m+1] = W[l][m];
		W[l][m+1] = '0';
		dl_lancucha++;
	}

	if(jest_cyfra_znaczaca && ilosc_kropek_dziesietnych) usun_tylko_kropke = 1;
	jest_cyfra_znaczaca = 0;
	for(k=dl_lancucha-1; k>=0; k--)
	{	if(W[l][k] >= '1' && W[l][k] <= '9') break; /*jest_cyfra_znaczaca = 1*/
		else
		{   if(usun_tylko_kropke && W[l][k] == '.') usun_tylko_kropke = 2;
			if(usun_tylko_kropke)
			{	W[l][dl_lancucha-1] = W[l][dl_lancucha];
				dl_lancucha--;
			}
			if(usun_tylko_kropke == 2) break;
		}
	}
	if(dl_lancucha == 0) { W[l][0] = '0'; dl_lancucha = 1; }
	k = dl_lancucha;     /* odnowienie dàugoòci àa‰cucha */
	W[l][k] = '\0';      /* .. - dla pewnoòci */
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_wielomianu() 					//
//                                                                      //
//  Odrzucenie liczby za duæej, za maàej lub obci©cie cyfr dziesi©tnych	//
//									//
//////////////////////////////////////////////////////////////////////////
void zbadaj_wielkosc_liczby(void)
{       int m, mm = 0;

	if( w[l] >= 1000000 || w[l] <= -1000000 )
	{	if( w[l] >= 1000000 )
		{	textcolor(14); textbackground(4); gotoxy(2, 25);
			cprintf("         Nie przyj•àem!  Dopuszczalna g¢rna granica"
					" liczby to 999999.         ");
			delay(1000);
			textcolor(11); textbackground(10); gotoxy(2, 25);
			cprintf("               Juæ MILION (1000000) to dla mnie"
					" liczba za duæa.               ");
		} else
			{	textcolor(14); textbackground(4); gotoxy(2, 25);
				cprintf("         Nie przyj•àem!  Dopuszczalna dolna granica"
						" liczby to -999999.        ");
				delay(1000);
				textcolor(11); textbackground(10); gotoxy(2, 25);
				cprintf("     Liczba MINUS MILION (-1000000) i mniejsze"
						" to dla mnie liczby za maàe.    ");
			}
		for(k=dl_lancucha; k>0; k--) W[l][k-1] = W[l][k]; /* skasuj liczb© na.. */
		zle = 1; l--; j--;     /*..wszelki wypadek. "k" i tak jest odnawiane jako 0 */
	} else
		if(ilosc_kropek_dziesietnych)
		{	for(k=0; k<dl_lancucha; k++)
				if(W[l][k] == '.')
					for(m=k+1; m<dl_lancucha; m++)
					{	mm++;
						if(mm > 6)
						{   for(m=dl_lancucha; m>k+7; m--)
								W[l][m-1] = W[l][m];
							dl_lancucha = k+mm;
							k = 100;
							textcolor(11); textbackground(10); gotoxy(2, 25);
							cprintf("    Uwaga:  Ograniczyàem zapis liczby "
									"obcinaj•c j• do 6-iu cyfr po kropce.    ");
							textbackground(kolor_tla_wyboru_parametrow);
							break;
						}
					}
		}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_postaci_funkcji() 				        //
//	tablica_operatorow_i_funkcji() 					//
//                                                                      //
//			Wybieranie funkcji dowolnej			//
//									//
//			okno_najwieksze() 				//
//			czy_porzucic_program() 			        //
//			wyczysc_informacje() 			        //
//			pomoc() 					//
//			tablica_operatorow_i_funkcji() 	                //
//			wpisz_lancuch_i_analizuj_go() 	                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wybieranie_funkcji_dowolnej(void)
{       char wybor;
	clrscr();
	textcolor(14); textbackground(1);
	okno_najwieksze();
	gotoxy(26, 3);
	cprintf("Dowolna postaÜ wyraæenia f(x)");

	textcolor(5); textbackground(7); gotoxy(5, 13);
	cprintf("…ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ"
			"ÕÕÕÕÕÕÕÕÕÕª");
	for(i=0; i<9; i++)
	{	gotoxy(5, i+14);
		cprintf("∫                                                        "
				"              ∫");
	}
	gotoxy(5, i+14);
	cprintf("»ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ"
			"ÕÕÕÕÕÕÕÕÕÕº");
	textcolor(1); gotoxy(19, 14);
	cprintf("Dost©pne operacje na wyraæeniach (tu: & i ·)");
	textcolor(0); gotoxy(10, 16); cprintf("Operatory                 :  ");
	textcolor(4); cprintf("  +     -     *     /");
	textcolor(0); gotoxy(10, 17); cprintf("Funkcje logarytmiczne     :  ");
	textcolor(4); cprintf("ln(&)        lg(&)");
	textcolor(0); gotoxy(10, 18); cprintf("Funkcje trygonometryczne  :  ");
	textcolor(4); cprintf("cos(&)       sin(&)       tan(&)");
		gotoxy(39, 19); cprintf("acos(&)      asin(&)      atan(&)");
	textcolor(0); gotoxy(10, 20); cprintf("Funkcje hiperboliczne     :  ");
	textcolor(4); cprintf("cosh(&)      sinh(&)      tanh(&)");
	textcolor(0); gotoxy(10, 21); cprintf("Inne funkcje matematyczne :  ");
	textcolor(4); cprintf("abs(&)       mod(&,·)     sq(&)");
		gotoxy(39, 22); cprintf("pow(&,·)     exp(&)");

	textcolor(3); textbackground(1); gotoxy(3, 5);
	cprintf("Czy chcesz otrzymaÜ dokàadne informacje o oznaczeniach w tabeli? (T/N) [N] ");

	wybor = getch();
	while(1)
	{	if(wybor == 27)
		{	pozycja_kursora_x = wherex();
			pozycja_kursora_y = wherey();
			gettext(lewa, gora, prawa, dol, buff);
			czy_porzucic_program();
			wyczysc_informacje();
			textbackground(kolor_tla_wyboru_parametrow);
			gotoxy(pozycja_kursora_x, pozycja_kursora_y);
			wybor = getch();
			continue;
		} else
			if(wybor == 0)
			{	if(getch() == 59)
				{	pozycja_kursora_x = wherex();
					pozycja_kursora_y = wherey();
					gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
					strona = 4;
					pomoc();
					gotoxy(pozycja_kursora_x, pozycja_kursora_y);
					wybor = getch();
					continue;
				} else
				{	getch();
					break;
				}
			} break;
	}

	if(wybor == 't' || wybor == 'T') tablica_operatorow_i_funkcji();
	textcolor(2); textbackground(1); cprintf("N");
	textcolor(9); gotoxy(3, 7); cprintf("f(x) = ");
	wpisz_lancuch_i_analizuj_go();

	// Pytanie o ewentualne zmiany parametr¢w wykresu b©dzie zadawane w trakcie operacji na wprowadzonym wyraæeniu
	/* W przypadku rezygnacji ze zmian parametr¢w wykresu funkcji,
	   nast©puj•ce zmienne wchodz•ce do moduà¢w wykresu maj• opcjonalne wartoòci:
	   dl_jedn_na_osi_OX = 50
	   dl_jedn_na_osi_OY = 50
	   zmniejszenie_jednostki_OY = 1  // znaczy ignoruj skal©; 10 - zmniejsz jednostk© 10 razy
	   nr_wzoru_tla = 1               // niebieski
	   nr_koloru_tla = 7              // jasnoszary
	   nr_koloru_osi = 12             // jasnoczerwony
	   nr_koloru_wykresu = 10         // jasnozielony
	*/
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_funkcji_dowolnej()					//
//                                                                      //
//			Tablica operator¢w i funkcji			//
//									//
//			okno_najwieksze() 				//
//			czy_porzucic_program() 			        //
//			wyczysc_informacje() 			        //
//			pomoc() 					//
//			wybieranie_funkcji_dowolnej() 	                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void tablica_operatorow_i_funkcji(void)
{	clrscr();
	textcolor(1); textbackground(3);
	okno_najwieksze();
	textcolor(14); gotoxy(14, 3);
	cprintf("Operatory i funkcje matematyczne na wyraæeniach & i ·");
	textcolor(4); gotoxy(6, 6);
	cprintf("Operatory                           Funkcje trygonometryczne");
	textcolor(5); gotoxy(8, 7);
	cprintf("+  "); textcolor(8); cprintf("dodawanie                        ");
	textcolor(5); cprintf("cos(&)   "); textcolor(8); cprintf("kosinus &");
	textcolor(5); gotoxy(8, 8);
	cprintf("-  "); textcolor(8); cprintf("odejmowanie                      ");
	textcolor(5); cprintf("sin(&)   "); textcolor(8); cprintf("sinus &");
	textcolor(5); gotoxy(8, 9);
	cprintf("*  "); textcolor(8); cprintf("mnozenie                         ");
	textcolor(5); cprintf("tan(&)   "); textcolor(8); cprintf("tangens &");
	textcolor(5); gotoxy(8, 10);
	cprintf("/  "); textcolor(8); cprintf("dzielenie                        ");
	textcolor(5); cprintf("acos(&)  "); textcolor(8); cprintf("arcus kosinus &");
	textcolor(5); gotoxy(44, 11);
	cprintf("asin(&)  "); textcolor(8); cprintf("arcus sinus &");
	textcolor(4); gotoxy(6, 12);
	cprintf("Funkcje logarytmiczne                 ");
	textcolor(5); cprintf("atan(&)  "); textcolor(8); cprintf("arcus tangens &");
	textcolor(5); gotoxy(8, 13);
	cprintf("ln(&)  "); textcolor(8); cprintf("logarytm naturalny &");
	textcolor(5); gotoxy(8, 14);
	cprintf("lg(&)  "); textcolor(8); cprintf("logarytm dziesi©tny &      ");
	textcolor(4); cprintf("Inne funkcje matematyczne");
	textcolor(5); gotoxy(44, 15);
	cprintf("abs(&)    "); textcolor(8); cprintf("wartoòÜ bezwzgl©dna &");
	textcolor(4); gotoxy(6, 16);
	cprintf("Funkcje hiperboliczne                 ");
	textcolor(5); cprintf("mod(&,·)  "); textcolor(8); cprintf("reszta z dzielenia &/·");
	textcolor(5); gotoxy(8, 17);
	cprintf("cosh(&)  "); textcolor(8); cprintf("kosinus hiperboliczny &    ");
	textcolor(5); cprintf("pow(&,·)  "); textcolor(8); cprintf("& do pot©gi ·");

	textcolor(5); gotoxy(8, 18);
	cprintf("sinh(&)  "); textcolor(8); cprintf("sinus hiperboliczny &      ");
	textcolor(5); cprintf("exp(&)    "); textcolor(8); cprintf("e do pot©gi &");

	textcolor(5); gotoxy(8, 19);
	cprintf("tanh(&)  "); textcolor(8); cprintf("tangens hiperboliczny &    ");
	textcolor(5); cprintf("sq(&)     "); textcolor(8); cprintf("pierwiastek kwadratowy &");
	textcolor(11); gotoxy(12, 22);
	cprintf("Szczeg¢àowych informacji szukaj w podr©cznikach szkolnych");

	while(1)
	{	textcolor(1); textbackground(2); gotoxy(2, 25);
		cprintf("              Naciònij dowolny klawisz aby wpisaÜ wyraæenie "
				"f(x)              \b\b\b\b\b\b\b\b\b\b\b\b\b");
		znak = getch();
		if(znak == 27)
		{	gettext(lewa, gora, prawa, dol, buff);
			czy_porzucic_program();
			wyczysc_informacje();
		} else
			if(znak == 0)
			{	if(getch() == 59)
				{	gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
					strona = 4;
					wyczysc_informacje();
					pomoc();
				} else
				{	getch();
					break;
				}
			} else
				break;
	}

	wybieranie_funkcji_dowolnej();
}

  /********************************************************************
   *------------------------------------------------------------------*
   *			Proces przed obliczeniami		      *
   *------------------------------------------------------------------*
   ********************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_funkcji_dowolnej()					//
//	popraw_wyrazenie()						//
//                                                                      //
//			Wpisywanie znak¢w do àa‰cucha i ich analiza	//
//			( najdàuæszy moduà )				//
//									//
//			wstep_rutynowy() 				//
//			popraw_wyrazenie() 				//
//			czy_jest_argument() 			        //
//			wyczysc_informacje() 			        //
//			pytanie_o_zapis() 				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wpisz_lancuch_i_analizuj_go(void)
{	int m;
	int d_l_fikcja;
	char F[150];

funkcja_dowolna = 1; wielomian = 0;
jest_funkcja = 0;	  /*jeæeli jest jakaò litera<>'x' to MUSI to byÜ funkcja*/
jest_ln   = 0; poz_ln_1   = -1; poz_ln_2   = -1; p_ln_1   = -1; p_ln_2   = -1;
jest_lg   = 0; poz_lg_1   = -1; poz_lg_2   = -1; p_lg_1   = -1; p_lg_2   = -1;
jest_cos  = 0; poz_cos_1  = -1; poz_cos_2  = -1; p_cos_1  = -1; p_cos_2  = -1;
jest_sin  = 0; poz_sin_1  = -1; poz_sin_2  = -1; p_sin_1  = -1; p_sin_2  = -1;
jest_tan  = 0; poz_tan_1  = -1; poz_tan_2  = -1; p_tan_1  = -1; p_tan_2  = -1;
jest_cosh = 0; poz_cosh_1 = -1; poz_cosh_2 = -1; p_cosh_1 = -1; p_cosh_2 = -1;
jest_sinh = 0; poz_sinh_1 = -1; poz_sinh_2 = -1; p_sinh_1 = -1; p_sinh_2 = -1;
jest_tanh = 0; poz_tanh_1 = -1; poz_tanh_2 = -1; p_tanh_1 = -1; p_tanh_2 = -1;
jest_acos = 0; poz_acos_1 = -1; poz_acos_2 = -1; p_acos_1 = -1; p_acos_2 = -1;
jest_asin = 0; poz_asin_1 = -1; poz_asin_2 = -1; p_asin_1 = -1; p_asin_2 = -1;
jest_atan = 0; poz_atan_1 = -1; poz_atan_2 = -1; p_atan_1 = -1; p_atan_2 = -1;
jest_abs  = 0; poz_abs_1  = -1; poz_abs_2  = -1; p_abs_1  = -1; p_abs_2  = -1;
jest_mod  = 0; poz_mod_1  = -1; poz_mod_2  = -1; p_mod_1  = -1; p_mod_2  = -1;
jest_pow  = 0; poz_pow_1  = -1; poz_pow_2  = -1; p_pow_1  = -1; p_pow_2  = -1;
jest_exp  = 0; poz_exp_1  = -1; poz_exp_2  = -1; p_exp_1  = -1; p_exp_2  = -1;
jest_sq   = 0; poz_sq_1   = -1; poz_sq_2   = -1; p_sq_1   = -1; p_sq_2   = -1;

	textcolor(7); gotoxy(10, 7);

	do
	{   wstep_rutynowy();
		for(k=0; k<=i; k++)
			A[k] = Z[k];
		if(i == 0)
		{	zle = 1;
			textcolor(14); textbackground(4); gotoxy(2, 25);
			cprintf("              W tym miejscu wpisz dow"
					"olne wyraæenie algebraiczne.             ");
			delay(1000);
			textcolor(11); textbackground(10); gotoxy(2, 25);
			cprintf("          Przykàad: 4abs(sin(2.5"
					"pi/cos(x2tanh(3.2x))))-pow(e,-x/pi)           ");
			textcolor(7); textbackground(1);
			gotoxy(10, 7);
		}
		else
		if(sygnal)
		{	if(znak != 13) /* && znak != 27) ???????? chyba juæ zbyteczne*/
			{   zle = 1;
				printf("\x07");
				if(jest_cyfra > 6)
				{	pozycja_kursora_x = wherex();
					pozycja_kursora_y = wherey();
					textcolor(14); textbackground(4); gotoxy(2, 25);
					cprintf("                           Zbyt duæo "
							"cyfr w liczbie.                          ");
					delay(1000);
					textcolor(11); textbackground(10); gotoxy(2, 25);
					cprintf("Liczba nie moæe mieÜ wi©cej niæ 6 cyfr"
							" cz©òci caàkowitej i tyle samo uàamkowej");
					textcolor(7); textbackground(1);
					gotoxy(pozycja_kursora_x, pozycja_kursora_y);
				} else
				{	A[i] = '\0';
					textcolor(14); textbackground(4); gotoxy(2, 25);
					cprintf("                  Nie poradz© sobie z"
							" wi©ksz• iloòci• znak¢w.                 ");
					delay(1000);
					textcolor(11); textbackground(10); gotoxy(2, 25);
					cprintf("   Moæesz wpisaÜ tylko do 70 znak¢w. "
							"[ENTER] - akceptuj, [<--] - usu‰ cyfry.  ");
					textcolor(7); textbackground(1);
					gotoxy(79, 7);
				}
			}
		} else
			zle = 0;
	} while(zle);

	d_l = d_l_A = strlen(A);
	strcpy(B,A);

	/*--------------------------------------------------------------*
	 *      Usu‰ wszystkie napotkane spacje				*
	 *--------------------------------------------------------------*/
	zmniejsz_d_l = 0;
	for(i=0; i<d_l; i++)
	if( A[i] == 32 )
	{   zmniejsz_d_l++;
		for(k=i; k<d_l; k++) A[k] = A[k+1];
		i--;
	}
	d_l = d_l - zmniejsz_d_l;

	/*--------------------------------------------------------------*
	 *	Wymie‰ litery duæe na maàe - jeæeli to konieczne	*
	 *--------------------------------------------------------------*/
	for(i=0; i<d_l; i++) A[i] = tolower(A[i]);

	/*--------------------------------------------------------------*
	 *	Sprawd´ obecnoòÜ niedopuszczalnych znak¢w		*
	 *--------------------------------------------------------------*/
	for(i=0; i<d_l; i++)
		if( (A[i]>32 && A[i]<40) || (A[i]>57 && A[i]<97) || (A[i]==102) ||
			(A[i]==106) || (A[i]==107) || (A[i]==114) || (A[i]==117) ||
			(A[i]==118) || (A[i]>120) )
			{   ptrE = E;
				ptrE="   Stwierdzono istnienie niedopuszczalnego znaku.   "
					 "Popraw zapis wyraæenia.   ";
				popraw_wyrazenie();
			}

	/*--------------------------------------------------------------*
	 *	Sprawd´ obecnoòÜ "pi" i "e"				*
	 *--------------------------------------------------------------*/
	/* "pi" zostanie zamienione na: 3.141593 dla procesu obliczeniowego */
	/* "À" dla podgl•du wyraæenia */
	for(i=0; i<d_l; i++)
		if(A[i] == 'p' && A[i+1] == 'i')
		{	for(j=0; j<6; j++)
			{	for(k=d_l; k>i+2; k--) A[k] = A[k-1];
				d_l = d_l++;
			}
			A[i] = '3'; A[i+1] = '.'; A[i+2] = '1'; A[i+3] = '4';
			A[i+4] = '1'; A[i+5] = '5'; A[i+6] = '9'; A[i+7] = '3';
			if(i+8 < d_l)	/* najpierw popatrz czy po "pi" nie ma liczby... */
				if( A[i+8] == '.' || (A[i+8] >47 && A[i+8] <58) )
				{	for(k=d_l; k>i+8; k--) A[k] = A[k-1];
					A[i+8] = '*';
					d_l++;
				}
			if(i > 0)	/*...a p¢´niej czy przed "pi" nie ma liczby */
				if( A[i-1] == '.' || (A[i-1] >47 && A[i-1] <58) )
				{	for(k=d_l; k>i; k--) A[k] = A[k-1];
					A[i] = '*';
					d_l++;
				}
			i = i + 7;
		}
	/* "e" zostanie zamienione na: 2.718282 dla procesu obliczeniowego,
	       takæe "e" dla podgl•du wyraæenia
	*/
	for(i=0; i<d_l; i++)
		if(A[i] == 'e' && A[i+2] != 'p')
		{	for(j=0; j<7; j++)
			{	for(k=d_l; k>i+1; k--) A[k] = A[k-1];
				d_l = d_l++;
			}
			     //gotoxy(2,2); printf("A = %s, d_l = %d", A, d_l);
			A[i] = '2'; A[i+1] = '.'; A[i+2] = '7'; A[i+3] = '1';
			A[i+4] = '8'; A[i+5] = '2'; A[i+6] = '8'; A[i+7] = '2';
			     //gotoxy(2,3); printf("A = %s, d_l = %d", A, d_l);
			if(i+8 < d_l)	/* najpierw popatrz czy po "e" nie ma liczby... */
				if( A[i+8] == '.' || (A[i+8] >47 && A[i+8] <58) )
				{	for(k=d_l; k>i+8; k--) A[k] = A[k-1];
					A[i+8] = '*';
					d_l++;
				}
			if(i > 0)	/*...a p¢´niej czy przed "e" nie ma liczby */
				if( A[i-1] == '.' || (A[i-1] >47 && A[i-1] <58) )
				{	for(k=d_l; k>i; k--) A[k] = A[k-1];
					A[i] = '*';
					d_l++;
				}
			i = i + 7;
		}

	/*--------------------------------------------------------------*
	 *	Sprawd´ pozycje znak¢w dziaàania			*
	 *--------------------------------------------------------------*/
	if( A[0] == '*' || A[0] == '/' || A[d_l-1] == '+' || A[d_l-1] == '-' ||
		A[d_l-1] == '*' || A[d_l-1] == '/')
		{   ptrE = E;
			ptrE="            Dziaàanie wymaga dw¢ch liczb.  Popraw zapis "
				 "wyraæenia.            ";
			popraw_wyrazenie();
		}
	for(i=0; i<d_l-1; i++)
	if( (A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/') &&
	  (A[i+1] == '+' || A[i+1] == '-' || A[i+1] == '*' || A[i+1] == '/') )
		{   ptrE = E;
			ptrE="           Bà•d w zapisie znak¢w dziaàania.  Popraw zapis "
				 "wyraæenia.          ";
			popraw_wyrazenie();
		}
	if(A[0] == '+')		/* usu‰ '+' na pocz•tku àa‰cucha */
	{	for(i=0; i<d_l; i++) A[i] = A[i+1];
		d_l--;
	}

	/*--------------------------------------------------------------*
	 *	Sprawd´ pozycje i liczb© nawias¢w			*
	 *--------------------------------------------------------------*/
	nr_nawiasu_otwartego = 0;
	nr_nawiasu_zamknietego = 0;
	for(i=0; i<d_l; i++)
	{   if( A[i] == '(' )
			nr_nawiasu_otwartego++;
		else
			if(A[i] == ')' && (nr_nawiasu_otwartego > nr_nawiasu_zamknietego))
				nr_nawiasu_zamknietego++;
	}
	if(nr_nawiasu_otwartego != nr_nawiasu_zamknietego)
	{   ptrE = E;
		ptrE="               Bà•d w zapisie nawias¢w.  Popraw zapis "
			 "wyraæenia.              ";
		popraw_wyrazenie();
	}

	/****************************************************************
	 *	Wprowadzenie nowych znak¢w do àa‰cucha			*
	 ****************************************************************
	 *--------------------------------------------------------------*
	 *  a)  Wprowad´ dodatkowy znak mnoæenia przed liczbami...	*
	 *--------------------------------------------------------------*/
	for(i=1; i<d_l; i++)	      /*  Jeæeli przed cyfr• jest znak  */
		if( A[i]==46 || (A[i]>47 && A[i]<58) )
			if( (A[i-1]<48 || A[i-1]>57) && A[i-1]!='+' && A[i-1]!='-' &&
				 A[i-1]!='*' && A[i-1]!='/' && A[i-1]!='.' && A[i-1]!='(' &&
				 A[i-1]!=',' )
			{   for(k=d_l; k>i; k--) A[k] = A[k-1];
				A[i] = '*';
				d_l++;
				i++;
			}

	/*--------------------------------------------------------------*
	 *  b)	...po liczbach...					*
	 *--------------------------------------------------------------*/
	for(i=1; i<d_l; i++)	   /*  Jeæeli przed znakiem jest cyfra  */
		if( (A[i]<48 || A[i]>57) && A[i]!='+' && A[i]!='-' &&
			 A[i]!='*' && A[i]!='/' && A[i]!='.' && A[i]!=')' && A[i]!=',' )
			if( A[i-1]==46 || (A[i-1]>47 && A[i-1]<58) )
			{   for(k=d_l; k>i; k--) A[k] = A[k-1];
				A[i] = '*';
				d_l++;
				i++;
			}

	/*--------------------------------------------------------------*
	 *  c)	...pomi©dzy "x" i innymi znakami			*
	 *--------------------------------------------------------------*/
	for(i=0; i<d_l; i++)
	{	if( A[i]>96 && A[i]<123 )
			if( i > 0 && A[i-1] ==')')
			{	for(k=d_l; k>i; k--) A[k] = A[k-1];
				A[i] = '*';
				d_l++;
				i++;
			}
		if( A[i]=='x' )
			if( A[i+1] =='(')
			{	for(k=d_l; k>i+1; k--) A[k] = A[k-1];
				A[i+1] = '*';
				d_l++;
				i++;
			} else
				if( A[i+1]>96 && A[i+1]<123)
				{	if( A[i+1] == 'p' && A[i+2]!='o') continue;
					{	for(k=d_l; k>i+1; k--) A[k] = A[k-1];
						A[i+1] = '*';
						d_l++;
						i++;
					}
				}
	}

	/*--------------------------------------------------------------*
	 *  d)	...i pomi©dzy nawiasami: ) i (				*
	 *--------------------------------------------------------------*/
	for(i=0; i<d_l; i++)
	{	if( A[i] == ')' && A[i+1] == '(' )
		{	for(k=d_l; k>i+1; k--) A[k] = A[k-1];
			A[i+1] = '*';
			d_l++;
			i++;
		}
	}

	/*--------------------------------------------------------------*
	 *  e)  Wprowad´ dodatkowe nawiasy (dla mnoæenia i dzielenia)	*
	 *--------------------------------------------------------------*/
	for(i=1; i<d_l; i++)
	{	nr_nawiasu_otwartego = 0;
		nr_nawiasu_zamknietego = 0;
		if( A[i]=='*' || A[i]=='/' )
		{	k = i;	/* etap 1: Jest okazja postawienia "(". Szukaj miejsca */
			do
			{	do
				{	k--;
					if( A[k]==')' ) nr_nawiasu_zamknietego++;
					if( A[k]=='(' ) nr_nawiasu_otwartego++;
					if(!nr_nawiasu_zamknietego && nr_nawiasu_otwartego)
						break;
					if( nr_nawiasu_zamknietego == nr_nawiasu_otwartego )
					{	nr_nawiasu_otwartego = 0;
						nr_nawiasu_zamknietego = 0;
					}
				} while( !((A[k]=='+' || A[k]=='-') && A[k-1]!='(') && k!=0 && A[k]!=',' );

				if(!nr_nawiasu_zamknietego && nr_nawiasu_otwartego) break;
				} while( ( nr_nawiasu_zamknietego>nr_nawiasu_otwartego )
					&& k!=0 && A[k]!=',');

			if( !(!nr_nawiasu_zamknietego && nr_nawiasu_otwartego) &&
				k!=0 && A[k]!=',' && A[k-1]!='(' && A[k-1]!=',' )
			{	/* Szuka gdzie wstawiÜ "(" bo tu juæ musi gdzieò go wstawiÜ */
/*	Gdyby jakiò test dawaà bà•d to pami©taj æe moæe byÜ wprowadzona
	zmienna o nazwie "roznica_ilosci_nawiasow" wàaònie w tym miejscu
*/				pozycja_nawiasu = k+1;
				for(k=d_l; k>pozycja_nawiasu; k--) A[k] = A[k-1];
				A[pozycja_nawiasu] = '(';
				d_l++;
				i++;
				k = i;  /* etap 2: Skoro byà "(" to szukaj gdzie wstawiÜ ")"... */
				nr_nawiasu_otwartego = 0;  /*...do miejsca gdzie byà * lub / */
				nr_nawiasu_zamknietego = 0;
				jest_funkcja = 0;
				do
				{	do
					{	k++;
						if( A[k]==')' ) nr_nawiasu_zamknietego++;
						if( A[k]=='(' ) nr_nawiasu_otwartego++;
						if( A[k]>96 && A[k]<123 && A[k]!='x' ) jest_funkcja=1;
						if( (A[k]=='*' || A[k]=='/') &&
							nr_nawiasu_zamknietego >= nr_nawiasu_otwartego )
						{	nr_nawiasu_otwartego = 0;
							nr_nawiasu_zamknietego = 0;
						}
					} while(A[k]!='+' && A[k]!='-' && k!=d_l &&
						A[k]!=',' && A[k]!=')' );
				} while( (nr_nawiasu_zamknietego<nr_nawiasu_otwartego ||
						  ((nr_nawiasu_zamknietego==nr_nawiasu_otwartego) &&
						   (A[k]!='+' && A[k]!='-'))) &&
					k!=d_l && (A[k]!=',' || jest_funkcja) );
				pozycja_nawiasu = k;
				for(k=d_l; k>pozycja_nawiasu; k--) A[k] = A[k-1];
				A[pozycja_nawiasu] = ')';
				d_l++;
				i=i+2;
			}
		}
	}

	/************************************************************************
	 *	Rozpoznaj funkcje i analizuj je pod wzgl©dem skladni		*
	 *									*
	 *	Moæliwe do zastosowania funkcje s• nast©pujace:			*
	 * ln(),	lg(),	cos(),	sin(),	tan(),	acos(),	asin(),	atan(),	*
	 * cosh(),	sinh(),	tanh(),	abs(),	mod(),	pow(),	exp(),	sq().	*
	 *	Dowoln• funkcj© moæna uæyÜ tylko dwa razy.			*
	 ************************************************************************
	 *------------------------------------------------------------------*
	 *	   Stwierdzenie obecnoòci funkcji matematycznych i	    *
	 *	 analiza ich skàadni zewn©trznej (wewn•trz nawias¢w)	    *
	 *------------------------------------------------------------------*/
	for(i=0; i<d_l; i++)
	{ if( (i==0 && A[i]>96 && A[i]<123 && A[i]!='x') || /* litera dla i==0 */
		  (i!=0 && A[i]>96 && A[i]<123 && A[i]!='x' &&  /* litera dla i!=0 */
		   (A[i-1]<97 || A[i-1]>122) ) ) 	   /*..a poprzednia nie litera */
	 { jest_funkcja = 0;				   /* zakàadamy æe jej nie ma */
	   if(A[i] == 'l')
	   { if(A[i+1]=='n' && A[i+2]=='(')
		 { if(poz_ln_1 == -1)
		   { jest_funkcja = jest_ln = 1; poz_ln_1 = i; p = p_ln_1 = i+3;
			 czy_jest_argument();
		   }
		   else
		   { if(poz_ln_2 == -1)
			 { jest_funkcja = 1; poz_ln_2 = i; p = p_ln_2 = i+3;
			   czy_jest_argument();
			 }
			 else
			 { ptrE = E;
			   ptrE=" Funkcja \"ln()\" moæe byÜ uæyta tylko dwukrotnie.  "
					"Uwzgl©dnij to w wyraæeniu.  ";
			   popraw_wyrazenie();
			 }
		   }
		 }
		 else if(A[i+1]=='g' && A[i+2]=='(')
			  { if(poz_lg_1 == -1)
				{ jest_funkcja = jest_lg = 1; poz_lg_1 = i; p = p_lg_1 = i+3;
				  czy_jest_argument();
				}
				else
				{ if(poz_lg_2 == -1)
				  { jest_funkcja = 1; poz_lg_2 = i; p = p_lg_2 = i+3;
					czy_jest_argument();
				  }
				  else
				  { ptrE = E;
					ptrE=" Funkcja \"lg()\" moæe byÜ uæyta tylko dwukrotnie."
						 "  Uwzgl©dnij to w wyraæeniu.  ";
					popraw_wyrazenie();
				  }
				}
			  }
	   } else
		 if(A[i] == 'c')
		 { if(A[i+1]=='o' && A[i+2]=='s')
			if(A[i+3]=='(')
			{ if(poz_cos_1 == -1)
			  { jest_funkcja = jest_cos = 1; poz_cos_1 = i; p = p_cos_1 = i+4;
				czy_jest_argument();
			  }
			  else
			  { if(poz_cos_2 == -1)
				{ jest_funkcja = 1; poz_cos_2 = i; p = p_cos_2 = i+4;
				  czy_jest_argument();
				}
				else
				{ ptrE = E;
				  ptrE=" Funkcja \"cos()\" moæe byÜ uæyta tylko dwukrotnie."
					   " Uwzgl©dnij to w wyraæeniu.  ";
				  popraw_wyrazenie();
				}
			  }
			}
			else if(A[i+3]=='h' && A[i+4]=='(')
				 { if(poz_cosh_1 == -1)
				   { jest_funkcja = jest_cosh = 1; poz_cosh_1 = i;
					 p = p_cosh_1 = i+5; czy_jest_argument();
				   }
				   else
				   { if(poz_cosh_2 == -1)
					 { jest_funkcja = 1; poz_cosh_2 = i; p = p_cosh_2 = i+5;
					   czy_jest_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" Funkcja \"cosh()\" moæe byÜ uæyta tylko "
							"dwukrotnie. Uwzgl©dnij to w wyraæeniu. ";
					   popraw_wyrazenie();
					 }
				   }
				 }
		 } else
		   if(A[i] == 's')
		   { if(A[i+1]=='i' && A[i+2]=='n')
			 { if(A[i+3]=='(')
			   { if(poz_sin_1 == -1)
				 { jest_funkcja = jest_sin = 1; poz_sin_1 = i;
				   p = p_sin_1 = i+4; czy_jest_argument();
				 }
				 else
				 { if(poz_sin_2 == -1)
				   { jest_funkcja = 1; poz_sin_2 = i; p = p_sin_2 = i+4;
					 czy_jest_argument();
				   }
				   else
				   { ptrE = E;
					 ptrE=" Funkcja \"sin()\" moæe byÜ uæyta tylko "
						  "dwukrotnie. Uwzgl©dnij to w wyraæeniu.  ";
					 popraw_wyrazenie();
				   }
				 }
			   }
			   else if(A[i+3]=='h' && A[i+4]=='(')
					{ if(poz_sinh_1 == -1)
					  { jest_funkcja = jest_sinh = 1; poz_sinh_1 = i;
						p = p_sinh_1 = i+5; czy_jest_argument();
					  }
					  else
					  { if(poz_sinh_2 == -1)
						{ jest_funkcja = 1; poz_sinh_2 = i;
						  p = p_sinh_2 = i+5; czy_jest_argument();
						}
						else
						{ ptrE = E;
						  ptrE=" Funkcja \"sinh()\" moæe byÜ uæyta tylko "
							   "dwukrotnie. Uwzgl©dnij to w wyraæeniu. ";
						  popraw_wyrazenie();
						}
					  }
					}
			 } else if(A[i+1]=='q' && A[i+2]=='(')
					{ if(poz_sq_1 == -1)
					  { jest_funkcja = jest_sq = 1; poz_sq_1 = i;
						p = p_sq_1 = i+3; czy_jest_argument();
					  }
					  else
					  { if(poz_sq_2 == -1)
						{ jest_funkcja = 1; poz_sq_2 = i; p = p_sq_2 = i+3;
						  czy_jest_argument();
						}
						else
						{ ptrE = E;
						  ptrE=" Funkcja \"sq()\" moæe byÜ uæyta tylko "
							   "dwukrotnie.  Uwzgl©dnij to w wyraæeniu.  ";
						  popraw_wyrazenie();
						}
					  }
					}
		   } else
			 if(A[i] == 't')
			 { if(A[i+1]=='a' && A[i+2]=='n')
				if(A[i+3]=='(')
				{ if(poz_tan_1 == -1)
				  { jest_funkcja = jest_tan = 1; poz_tan_1 = i;
					p = p_tan_1 = i+4; czy_jest_argument();
				  }
				  else
				  { if(poz_tan_2 == -1)
					{ jest_funkcja = 1; poz_tan_2 = i; p = p_tan_2 = i+4;
					  czy_jest_argument();
					}
					else
					{ ptrE = E;
					  ptrE=" Funkcja \"tan()\" moæe byÜ uæyta tylko "
						   "dwukrotnie. Uwzgl©dnij to w wyraæeniu.  ";
					  popraw_wyrazenie();
					}
				  }
				}
				else if(A[i+3]=='h' && A[i+4]=='(')
					 { if(poz_tanh_1 == -1)
					   { jest_funkcja = jest_tanh = 1; poz_tanh_1 = i;
						 p = p_tanh_1 = i+5; czy_jest_argument();
					   }
					   else
					   { if(poz_tanh_2 == -1)
						 { jest_funkcja = 1; poz_tanh_2 = i;
						   p = p_tanh_2 = i+5; czy_jest_argument();
						 }
						 else
						 { ptrE = E;
						   ptrE=" Funkcja \"tanh()\" moæe byÜ uæyta tylko "
								"dwukrotnie. Uwzgl©dnij to w wyraæeniu. ";
						   popraw_wyrazenie();
						}
					   }
					 }
			 } else
			   if(A[i] == 'a')
			   { if(A[i+4] == '(')
				 { if(A[i+1]=='c' && A[i+2]=='o' && A[i+3]=='s')
				   { if(poz_acos_1 == -1)
					 { jest_funkcja = jest_acos = 1; poz_acos_1 = i;
					   p = p_acos_1 = i+5; czy_jest_argument();
					 }
					 else
					 { if(poz_acos_2 == -1)
					   { jest_funkcja = 1; poz_acos_2 = i; p = p_acos_2 = i+5;
						 czy_jest_argument();
					   }
					   else
					   { ptrE = E;
						 ptrE=" Funkcja \"acos()\" moæe byÜ uæyta tylko "
							  "dwukrotnie. Uwzgl©dnij to w wyraæeniu. ";
						 popraw_wyrazenie();
					   }
					 }
				   }
				   else if(A[i+1]=='s' && A[i+2]=='i' && A[i+3]=='n')
						{ if(poz_asin_1 == -1)
						  { jest_funkcja = jest_asin = 1; poz_asin_1 = i;
							p = p_asin_1 = i+5; czy_jest_argument();
						  }
						  else
						  { if(poz_asin_2 == -1)
							{ jest_funkcja = 1; poz_asin_2 = i;
							  p = p_asin_2 = i+5; czy_jest_argument();
							}
							else
							{ ptrE = E;
							  ptrE=" Funkcja \"asin()\" moæe byÜ uæyta tylko"
								   " dwukrotnie. Uwzgl©dnij to w wyraæeniu. ";
							  popraw_wyrazenie();
							}
						  }
						}
						else if(A[i+1]=='t' && A[i+2]=='a' && A[i+3]=='n')
							 { if(poz_atan_1 == -1)
							   { jest_funkcja = jest_atan = 1; poz_atan_1 = i;
								 p = p_atan_1 = i+5; czy_jest_argument();
							   }
							   else
							   { if(poz_atan_2 == -1)
								 { jest_funkcja = 1; poz_atan_2 = i;
								   p = p_atan_2 = i+5; czy_jest_argument();
								 }
								 else
								 { ptrE = E;
								   ptrE=" Funkcja \"atan()\" moæe byÜ uæyta "
										"tylko dwukrotnie. Uwzgl©dnij to w "
										"wyraæeniu. ";
								   popraw_wyrazenie();
								 }
							   }
							 }
				 } else if(A[i+1]=='b' && A[i+2]=='s' && A[i+3]=='(')
						{ if(poz_abs_1 == -1)
						  { jest_funkcja = jest_abs = 1; poz_abs_1 = i;
							p = p_abs_1 = i+4; czy_jest_argument();
						  }
						  else
						  { if(poz_abs_2 == -1)
							{ jest_funkcja = 1; poz_abs_2 = i;
							  p = p_abs_2 = i+4; czy_jest_argument();
							}
							else
							{ ptrE = E;
							  ptrE=" Funkcja \"abs()\" moæe byÜ uæyta tylko "
								   "dwukrotnie. Uwzgl©dnij to w wyraæeniu.  ";
							  popraw_wyrazenie();
							}
						  }
						}
			   } else
				 if(A[i] == 'm' && A[i+1]=='o' && A[i+2]=='d' && A[i+3]=='(')
				 { if(poz_mod_1 == -1)
				   { jest_funkcja = jest_mod = 1; poz_mod_1 = i;
					 p = p_mod_1 = i+4; czy_jest_argument();
				   }
				   else
				   { if(poz_mod_2 == -1)
					 { jest_funkcja = 1; poz_mod_2 = i; p = p_mod_2 = i+4;
					   czy_jest_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" Funkcja \"mod()\" moæe byÜ uæyta tylko "
							"dwukrotnie. Uwzgl©dnij to w wyraæeniu.  ";
					   popraw_wyrazenie();
					 }
				   }
				 }
				 else
				 if(A[i] == 'p' && A[i+1]=='o' && A[i+2]=='w' && A[i+3]=='(')
				 { if(poz_pow_1 == -1)
				   { jest_funkcja = jest_pow = 1; poz_pow_1 = i;
					 p = p_pow_1 = i+4; czy_jest_argument();
				   }
				   else
				   { if(poz_pow_2 == -1)
					 { jest_funkcja = 1; poz_pow_2 = i; p = p_pow_2 = i+4;
					   czy_jest_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" Funkcja \"pow()\" moæe byÜ uæyta tylko "
							"dwukrotnie. Uwzgl©dnij to w wyraæeniu.  ";
					   popraw_wyrazenie();
					 }
				   }
				 }
				 else
				 if(A[i] == 'e' && A[i+1]=='x' && A[i+2]=='p' && A[i+3]=='(')
				 { if(poz_exp_1 == -1)
				   { jest_funkcja = jest_exp = 1; poz_exp_1 = i;
					 p = p_exp_1 = i+4; czy_jest_argument();
				   }
				   else
				   { if(poz_exp_2 == -1)
					 { jest_funkcja = 1; poz_exp_2 = i; p = p_exp_2 = i+4;
					   czy_jest_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" Funkcja \"exp()\" moæe byÜ uæyta tylko "
							"dwukrotnie. Uwzgl©dnij to w wyraæeniu.  ";
					   popraw_wyrazenie();
					 }
				   }
				 }
	  if(jest_funkcja == 0)
	  { ptrE = E;
		ptrE=" Spodziewana funkcja a jest niepoprawny jej zapis. Napisz "
			 "poprawne wyraæenie. ";
		popraw_wyrazenie();
	  }
	 }
	}

	/*------------------------------------------------------------------*
	 *	Analiza skàadni wewn©trznej pod wzgl©dem przecink¢w.	    *
	 *------------------------------------------------------------------*/
	ilosc_przecinkow_faktyczna = 0;
	for(i=0; i<d_l; i++)
	{	if(A[i] == ',')
		{	ilosc_przecinkow_faktyczna++;
			//	ptrC = "+";	/* wynik poprzedniego podejòcia - zmiana A[] na C[]...*/
			//	C[i] = *ptrC;   /*...w celu sprawdzenia àancucha bez funkcji matematycznych */
		}
	}
	ilosc_przecinkow_przewidywana = 0;
	if(jest_funkcja)
		if(jest_mod || jest_pow)
		{	if(poz_mod_1 != -1) ilosc_przecinkow_przewidywana++;
			if(poz_mod_2 != -1) ilosc_przecinkow_przewidywana++;
			if(poz_pow_1 != -1) ilosc_przecinkow_przewidywana++;
			if(poz_pow_2 != -1) ilosc_przecinkow_przewidywana++;
		}
	if(ilosc_przecinkow_faktyczna != ilosc_przecinkow_przewidywana)
	{	ptrE = E;
		ptrE="   Coò si© nie zgadza z przecinkami.  Pami©taj \".\" "
			 "zast©puje \",\" w liczbie.   ";
		popraw_wyrazenie();
	} else
	{   gotoxy(10, 8); printf("                                        "
							  "                              ");
	///////////// wstawienie "À" zamiast 3.141593 //////////////////
	//    Pierwsza poniæsza linia jest wprowadzona sztucznie aby
	//    zamkn•Ü àa‰cuch bo zauwaæylem, æe program tego nie robi
	////////////////////////////////////////////////////////////////
	A[d_l] = '\0';

	d_l_fikcja = d_l;
	strcpy(F,A);
	for(i=0; i<d_l-7; i++)				/* moæe i<d_l-8 */
		if(F[i] == '3')
		 if(F[i+1] == '.')
		  if(F[i+2] == '1')
		   if(F[i+3] == '4')
			if(F[i+4] == '1')
			 if(F[i+5] == '5')
			  if(F[i+6] == '9')
			   if(F[i+7] == '3')
			   {	F[i] = 'À';
					for(j=0; j<7; j++)
					{	for(k=i+1; k< d_l_fikcja; k++)
							F[k] = F[k+1];
						d_l_fikcja--;
					}
			   }
	for(i=0; i<d_l-7; i++)				/* moæe i<d_l-8 */
		if(F[i] == '2')
		 if(F[i+1] == '.')
		  if(F[i+2] == '7')
		   if(F[i+3] == '1')
			if(F[i+4] == '8')
			 if(F[i+5] == '2')
			  if(F[i+6] == '8')
			   if(F[i+7] == '2')
			   {	F[i] = 'e';
					for(j=0; j<7; j++)
					{	for(k=i+1; k< d_l_fikcja; k++)
							F[k] = F[k+1];
						d_l_fikcja--;
					}
			   }
		gotoxy(10, 9); textcolor(7); cprintf("Tw¢j zapis zamieniàem na:");
		gotoxy(10,10); printf("                                        "
							  "                              ");
		gotoxy(10,11); printf("                                        "
							  "                              ");
		textcolor(9); gotoxy(3,10); cprintf("f(x) = ");
			/* àancuch wydruku F[] */
		gotoxy(10,10); textcolor(11);
		if(d_l_fikcja<=70) cprintf("%s", F);
		else
		{	for(i=70; i>0; i--)
				if(F[i] == '+' || F[i] == '/' || F[i] == '*') break;
			for(m=0; m<=i; m++)	cprintf("%c", F[m]);
			gotoxy(10,11); for(m=i+1; m<d_l_fikcja; m++) cprintf("%c", F[m]);
		}  /* przejòcie na àa‰cuch operacyjny A[] */
		if( A[0] == '-' && (A[1] < 48 || A[1] > 57) ) /* wstaw 0 przed '-' na pocz•tku àa‰cucha */
		{	for(i=d_l; i>=0; i--) A[i+1] = A[i];
			A[0] = '0';
			d_l++;
		}

		strcpy(CF,A);	/* zapamietaj orginalny àa‰cuch */
		d_l_CF = d_l;

		wyczysc_informacje();
		pytanie_o_zapis();
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wpisz_lancuch_i_analizuj_go()					//
//                                                                      //
//	  Analiza skàadni wewn©trznej pod wzgl©dem obecnoòci argument¢w	//
//									//
//			popraw_wyrazenie() 				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void czy_jest_argument(void)
{   	while(A[p]=='(')
	{	p++;
	}

	if( ( A[p]<43 || A[p]==44 || A[p]==47 || (A[p]>57 && A[p]<97) || A[p]>122 )
	 || ( (A[p]=='+' || A[p]=='-') && (A[p+1]<46 || A[p+1]==47 ||
		  (A[p+1]>57 && A[p+1]<97) || A[p+1]>122) ) )
		{	ptrE = E;
			ptrE="  Kaæda funkcja wymaga argumentu. Sprawd´ w powyæszej "
				 "tabeli i popraw bà©dy.  ";
			popraw_wyrazenie();
		} else
		  if( p==p_mod_1 || p==p_mod_2 || p==p_pow_1 || p==p_pow_2 )
		  {	do
			{	p++;
			} while(A[p]!=',' && p!=d_l);
			p++;
			while(A[p]=='(')
			{	p++;
			}
			if( ( A[p]<43 || A[p]==44 || A[p]==47 || (A[p]>57 && A[p]<97) ||
				  A[p]>122 )
			 || ( (A[p]=='+' || A[p]=='-') && (A[p+1]<46 || A[p+1]==47 ||
				  (A[p+1]>57 && A[p+1]<97) || A[p+1]>122) ) )
				{	ptrE = E;
					ptrE=" Funkcje \"mod()\" i \"pow()\" s• dwuargumentowe "
						 "co widaÜ w tabeli. Popraw bà©dy. ";
					popraw_wyrazenie();
				}
		  }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wpisz_lancuch_i_analizuj_go()					//
//	czy_jest_argument()						//
//	pytanie_o_zapis()						//
//                                                                      //
// Stwierdzenie bà©du i ponowne wywoàanie procedury wpisywania àa‰cucha	//
//							                //
//			wpisz_lancuch_i_analizuj_go() 	                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void popraw_wyrazenie(void)
{   int m;

	gotoxy(2,25); textcolor(4); textbackground(7);
	cprintf("%s\b", ptrE);
	gotoxy(10,7); textbackground(1);
	printf("                                   "
		   "                                   ");
	for(i=0; i<4; i++)
	{	gotoxy(3,8+i);
		printf("                                       "
			   "                                      ");
	}
	gotoxy(10,8); textcolor(2); cprintf("%s", B);
	// Kasuj© caày àa‰cuch i na wszelki wypadek odnawiam "d_l".
	d_l = strlen(A);
	for(m=d_l; m>0; m--) A[m-1] = A[m];
	d_l = 0;

	wpisz_lancuch_i_analizuj_go();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wpisz_lancuch_i_analizuj_go()					//
//                                                                      //
//	   Zapytanie o zgod© uæytkownika czy przerobiony przez program	//
//	   àa‰cuch jest przez niego akceptowany				//
//									//
//                      tlo_wykresu_funkcji()                           //
//                      grafika_wstepu() 				//
//			popraw_wyrazenie() 				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void pytanie_o_zapis(void)
{       int m,/* mm,*/ mmm=1;
	char m_ch1, m_ch2;

	gettext(lewa, gora+6, prawa, dol+6, buff);
	textbackground(2);
	textcolor(8); gotoxy(lewa, gora+6);
	cprintf("…ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕª");
	for(m=1; m<6; m++)
	{	gotoxy(lewa, gora+6+m);
		cprintf("∫                                   ∫");
	}
	gotoxy(lewa, gora+6+m);
	cprintf("»ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕº");
	textcolor(10); gotoxy(lewa+3, gora+8); cprintf("Czy zgadzasz si© z moim zapisem?");
	_setcursortype(_NOCURSOR);
	textcolor(11); gotoxy(lewa+6, gora+10); cprintf("Tak                  Nie");

	do
	{	gotoxy(lewa+6, gora+10);
		for(m=0; m<10; m++)
		{   if( kbhit() )
				if( (m_ch1 = getch()) == 0 )
				{       m_ch2 = getch(); /* zdefiniowane w getch(): #define KEY_RIGHT 77 */
					if( m_ch2 == 77 ) { ilosc_skokow++; break; }
		// Ten zapis robi ostrzeæenie -->  if( (m_ch2 = getch()) == 77 ) { ilosc_skokow++; break; }
				}
				else
				{	if( m_ch1 == 13 )
		// Nie ma tu: _setcursortype(_NORMALCURSOR); ciekawe dlaczego nie jest potrzebny
					// Pytanie: Czy zmieniaÜ parametry rysunku, czy zostawiÜ wartoòci opcjonalne?
					// Na ekranie pozostaje okno zapytania o zapis ale juæ nieaktywne - nie przejmuj si© nim.
					{       gotoxy(2,25); textcolor(4); textbackground(10);
						cprintf(" [Enter] - wykres funkcji;  "
							"[Inny dowolny klawisz] - wyb¢r parametr¢w wykresu ");
						znak = getch();
						if(znak == 13) tlo_wykresu_funkcji();
						else grafika_wstepu();
					}
					else
						if( m_ch1 == 9 ) { ilosc_skokow++;	break; }
				}
			textcolor(9); cprintf("Tak\b\b\b"); delay(100);
			textcolor(11); cprintf("Tak\b\b\b"); delay(100);
			if(m > 8) m = 0;
		}
		if(!mmm) break;
		gotoxy(lewa+27, gora+10);
		for(m=0; m<10; m++)
		{   if( kbhit() )
				if( (m_ch1 = getch()) == 0 )
				{       m_ch2 = getch(); /* zdefiniowane w getch(): #define KEY_LEFT 75 */
					if( m_ch2 == 75 ) { ilosc_skokow++; break; }
		// Ten zapis robi ostrzeæenie -->  if( (m_ch2 = getch()) == 75 ) { ilosc_skokow++; break; }
				}
				else
				{	if( m_ch1 == 13 )
					{   puttext(lewa, gora+6, prawa, dol+6, buff);
						_setcursortype(_NORMALCURSOR);
						ptrE = E;
						ptrE="Zapisz wyraæenie jeszcze raz ale w inny "
							 "spos¢b abym wiedziaà co masz na myòli.";
						popraw_wyrazenie();
					}
					else
						if( m_ch1 == 9 ) { ilosc_skokow++; break; }
				}
			textcolor(9); cprintf("Nie\b\b\b"); delay(100);
			textcolor(11); cprintf("Nie\b\b\b"); delay(100);
			if(m > 8) m = 0;
		}
	if(ilosc_skokow == 21) ilosc_skokow = 0;
	} while(1); // wykonuj aæ nie wyjdzie ze òrodka p©tli

	textbackground(1);
//	_setcursortype(_NORMALCURSOR);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	main()								//
//	pytanie_o_zapis()						//
//	wybory_parametrow()						//
//	wstepna_analiza_znakow()					//
//                                                                      //
//	   Graficzny obraz statyczny, informacyjny moæliwy do ponownego	//
//	   wykorzystania z "opcji" jako obraz dynamiczny		//
//									//
//                      czy_porzucic_program_gr()		        //
//			pomoc_gr()					//
//			wybory_parametrow()			        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void grafika_wstepu(void)
{	int driver = VGA, mode = VGAHI, errorcode;
	int kwadrat_maksymalny[] = {0, 0, XMAX-1, 0, XMAX-1, YMAX-5, 0, YMAX-5, 0, 0};
	unsigned rozmiar;
	void far *ptr_do_alokacji_pamieci;

	initgraph(&driver, &mode, "c:\\TURBOC3\\bgi");  /*  "d:\\tc\\bgi");  */

	errorcode = graphresult();
	if(errorcode != grOk)
	{	printf("\nBà•d grafiki (moduà 'grafika_wstepu'): %s\n", grapherrormsg(errorcode));
		printf("Przyciònij dowolny klawisz aby wejòÜ do edytora : ");
		getch();
		exit(1);
	}

	setfillstyle(10, 9);
	fillpoly(5, kwadrat_maksymalny);
	setcolor(9);
	moveto(150,15);
	settextstyle(1, HORIZ_DIR, 5);
	outtext("WYKRES FUNKCJI");

	setcolor(2);
	settextstyle(2, HORIZ_DIR, 6);
	if(opcja==0)
	{   j = 0;
		moveto(10,75);
		outtext("Bedziesz wybierac parametry odpowiadajac na nastepujace "
				"pytania:");
	} else
	{   j = 10;
		moveto(185,75);
		outtext("Aktualnie wybierany parametr");
	}

	setcolor(3);
	i = 100;
	moveto(i-65+j,i+j);
	settextstyle(2, HORIZ_DIR, 5);
	outtext("Dlugosc jednostki na osi OX w punktach ekranu (od 10 do 300) [opcjonalnie]");
	moveto(i-65+j,i+20+j);
	outtext("Dlugosc jednostki na osi OY w punktach ekranu (od 5 do 220) [opcjonalnie]");
	moveto(i-65+j,i+40+j);
	outtext("Numer wzoru tla z listy wzor¢w innego ekranu (od 0 do 11) [opcjonalnie]");
	moveto(i-65+j,i+60+j);
	outtext("Numer koloru tla z ponizszej palety barw (od 0 do 15) [opcjonalnie]");
	moveto(i-65+j,i+80+j);
	outtext("Numer koloru osi ukladu wsp¢lrzednych (od 0 do 15) [opcjonalnie]");
	moveto(i-65+j,i+100+j);
	outtext("Numer koloru wykresu funkcji (od 0 do 15) [opcjonalnie]");
	if(opcja==0)
	{	setcolor(2);
		moveto(27,230);
		settextstyle(2, HORIZ_DIR, 6);
		outtext("Do tego obrazu bedziesz miec zawsze podglad poprzez znak \"?\"");
	}
	setcolor(14);
	settextstyle(2, HORIZ_DIR, 6);
	if(opcja==0)
	{	moveto(90,260);
		outtext("NACISNIJ DOWOLNY KLAWISZ ABY WEJSC DO PROGRAMU");
	} else
	{	moveto(120,247);
		outtext("NACISNIJ DOWOLNY KLAWISZ ABY WYBRAC OPCJE");
	}
	setcolor(7);
	moveto(95,420);
	settextstyle(4, HORIZ_DIR, 5);
	outtext("Programy Leszka Buczka");
	setcolor(3);
	moveto(270,290);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("PALETA BARW");

	j = 0; k = 0; l = 330;
	for(i=0; i<16; i++)
	{   if(i==0) setcolor(8); else setcolor(i);
		if(i==8) { k = 0; l = 390; }
		j = 60+k*75;
		circle(j, l, 20);
		if(i==0) { setfillstyle(1, 0); floodfill(j, l, 8); } else
		{	setfillstyle(1, i);
			floodfill(j, l, i);
		}
		if(i>9) moveto(j-40, l); else	moveto(j-30, l);
		settextstyle(2, HORIZ_DIR, 7);
		if(i==0) outtext("0"); else if(i==1) outtext("1"); else
		 if(i==2) outtext("2"); else if(i==3) outtext("3"); else
		  if(i==4) outtext("4"); else if(i==5) outtext("5"); else
		   if(i==6) outtext("6"); else if(i==7) outtext("7"); else
			if(i==8) outtext("8"); else if(i==9) outtext("9"); else
			 if(i==10) outtext("10"); else if(i==11) outtext("11"); else
			  if(i==12) outtext("12"); else if(i==13) outtext("13"); else
			   if(i==14) outtext("14"); else outtext("15");
		k++;
	}
	if(opcja>0)
	{	setcolor(10);
		for(i=1; i<opcja; i++)
		{	circle(27, 97+i*20, 3);
			setfillstyle(1, 10);
			floodfill(27, 97+i*20, 10);
		}
		circle(27, 97+i*20, 3);
	} else opcja = 1;

	do
	{	proba_porzucenia = 0;
		wezwanie_pomocy = 0;
		znak = getch();
		if(znak == 27)
		{	proba_porzucenia = 1;
			rozmiar = imagesize(lewa_gr, gora_gr, prawa_gr, dol_gr);
			if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
			{	closegraph();
				printf("\nBà•d (3): W pami©ci nie ma miejsca dla przechowania obrazu");
				printf("\nJego rozmiar = %u bajt¢w jest za duæy", rozmiar);
				printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
				exit(1);
			}
			getimage(lewa_gr, gora_gr, prawa_gr, dol_gr, ptr_do_alokacji_pamieci);
			czy_porzucic_program_gr();
			putimage(lewa_gr, gora_gr, ptr_do_alokacji_pamieci, COPY_PUT);
			farfree(ptr_do_alokacji_pamieci);
		} else
		if(znak == 0)
		{	if(getch() == 59)
			{	wezwanie_pomocy = 1;
			rozmiar = imagesize(lewa_gr-30, gora_gr-30, prawa_gr+30, dol_gr+30);
			if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
			{	closegraph();
				printf("\nBà•d (4): W pami©ci nie ma miejsca dla przechowania obrazu");
				printf("\nJego rozmiar = %u bajt¢w jest za duæy", rozmiar);
				printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
				exit(1);
			}
			getimage(lewa_gr-30, gora_gr-30, prawa_gr+30, dol_gr+30, ptr_do_alokacji_pamieci);
			pomoc_gr();
			putimage(lewa_gr-30, gora_gr-30, ptr_do_alokacji_pamieci, COPY_PUT);
			farfree(ptr_do_alokacji_pamieci);
			} else getch();
		}
	} while( proba_porzucenia || wezwanie_pomocy);

	closegraph();
	wybory_parametrow();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	grafika_wstepu()						//
//	wybory_parametrow()						//
//	menu()								//
//                                                                      //
//	   Moduà speàniaj•cy rol© "rozdzielni" pomi©dzy wyborem "opcji"	//
//								        //
//			okno_najwieksze()				//
//			dlugosc_jednostki_osi_OX()		        //
//			dlugosc_jednostki_osi_OY()		        //
//			nr_wzoru_tla_ekranu()			        //
//			nr_koloru_tla_ekranu()			        //
//			nr_koloru_osi_ukladu_wspolrz()	                //
//			nr_koloru_wykresu_funkcji()	                //
//			grafika_wstepu()				//
//			czy_porzucic_program()			        //
//			wyczysc_informacje()			        //
//			tlo_wykresu_funkcji()		          	//
//			wybory_parametrow()			        //
//			pomoc()						//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wybory_parametrow(void)
{	clrscr();
	textcolor(1); textbackground(kolor_tla_ekranu_opcji);
	okno_najwieksze();
	cprintf("                                        "
			"                                       ");
	textcolor(5); textbackground(kolor_tla_wyboru_parametrow);
	gotoxy(8, 3);
	cprintf("…ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ"
			"ÕÕÕÕª");
	for(i=0; i<9; i++)
	{	gotoxy(8, i+4);
		cprintf("∫                                                        "
				"        ∫");
	}
	gotoxy(8, i+4);
	cprintf("»ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ"
			"ÕÕÕÕº");
	textcolor(14); gotoxy(30, 5); cprintf("USTAWIENIE PARAMETR‡W");

	if(opcja==1) dlugosc_jednostki_osi_OX(); else
	  if(opcja==2) dlugosc_jednostki_osi_OY(); else
		if(opcja==3) nr_wzoru_tla_ekranu(); else
		  if(opcja==4) nr_koloru_tla_ekranu(); else
			if(opcja==5) nr_koloru_osi_ukladu_wspolrz(); else
			  if(opcja==6) nr_koloru_wykresu_funkcji();

	/*  rysuj wykres funkcji  */

	if(opcja > 3 && opcja < 8)
	{	textbackground(kolor_tla_ekranu_opcji);
		for(i=0; i<9; i++)
		{   gotoxy(5, 15+i);
			cprintf("                                                      "
					"                  ");
		}
	}

	gotoxy(15, 18); textcolor(8); textbackground(kolor_tla_ekranu_opcji);
	if(opcja==7)
	{   textcolor(15);
		cprintf("Naciònij dowolny klawisz aby zobaczyÜ wykres funkcji ");
	}
	else
	{   cprintf("Naciònij dowolny klawisz aby wybraÜ nast©pny parametr");
		gotoxy(34, 19); cprintf("Podgl•d [?] ");
	}
	while(1) /* robota do wiecznoòci albo ...do wywoàania funkcji, innych... */
	{	znak = getch();		/*... opcji lub rysowania funkcji matematycznych */
		if(opcja < 7 && (znak == '?' || znak == '/'))
		{	grafika_wstepu();
			continue;
		}
		if(znak == 27)
		{	pozycja_kursora_x = wherex();
			pozycja_kursora_y = wherey();
			gettext(lewa, gora, prawa, dol, buff);
			czy_porzucic_program();
			wyczysc_informacje();
			textbackground(kolor_tla_ekranu_opcji);
			gotoxy(pozycja_kursora_x, pozycja_kursora_y);
			continue;
		}
		else
		if(znak != 0)
		{	if(opcja == 7)
				tlo_wykresu_funkcji();
			else
				wybory_parametrow();
		} else
			if(getch() == 59)
			{   pozycja_kursora_x = wherex();
				pozycja_kursora_y = wherey();
				gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
				strona = 5;
				pomoc();
				wyczysc_informacje();
				textcolor(11); textbackground(kolor_tla_wyboru_parametrow);
				gotoxy(pozycja_kursora_x, pozycja_kursora_y);
				continue;
			} else
			{	if(opcja == 7)
					tlo_wykresu_funkcji();
				else
					wybory_parametrow();
			}
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_postaci_funkcji()					//
//	wybieranie_wielomianu()						//
//	wybieranie_funkcji_dowolnej()					//
//	tablica_operatorow_i_funkcji()					//
//	wybory_parametrow()						//
//                                                                      //
//	    Rysunek pustego okna na caày ekran (opr¢cz linii ostatniej)	//
//									//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void okno_najwieksze(void)
{	cprintf("⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ"
			"ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø");
	for(i=0; i<22; i++)
		cprintf("≥                                                        "
				"                      ≥");
	cprintf("¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ"
			"ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybory_parametrow()						//
//                                                                      //
//		  Wyb¢r dàugoòci jednostki na osi OX w punktach ekranu  //
//								        //
//			wstep_rutynowy()				//
//			za_dlugi_lancuch()				//
//			usun_spacje()					//
//			nie_liczba_naturalna()			        //
//			liczba_poza_zakresem()		          	//
//			wyczysc_raport_bledu()		        	//
//			wyczysc_informacje()		        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void dlugosc_jednostki_osi_OX(void)
{       opcja = 1;
	zle = 0;			/* znaczy: jest dobrze */
	if(dl_jedn_OX<100) j = 2; else j = 3;
		/* j - tu: dàugoòÜ akceptowanego (default) àa‰cucha "dl_jedn_OX"... */
		/*... jeszcze przed wejòciem do moduàu bo zaloæeniem jest, æe po ...*/
		/*... wykresie robimy nast©pny wykres nie wychodz•c z programu.     */
		/* Dodatkowa uwaga:
		   Do tej pory moæliwy jest tylko jeden wykres w ukàadzie wsp¢àrz©dnych
		   dwa lub trzy wykresy w jednym ukàadzie wsp¢àrz©dnych jest jeszcze nie
		   zrobione a wi©c niemoæliwe do wykonania na chwil© obecn•. */
	gotoxy(18,7); textcolor(8);
	cprintf("DàugoòÜ jednostki na osi OX w punktach ekranu");
	gotoxy(32, 8); cprintf("(10ˆ300) [%d] ", dl_jedn_OX);

	do
	{	wstep_rutynowy();
		if(i == 0)
		{	zle = 0;
			dl_jedn_na_osi_OX = dl_jedn_OX;
			dl_lancucha = 0;	 /* to chyba jest zb©dne */
		}
		else
		{   if(sygnal)
				za_dlugi_lancuch();
			else
			{	dl_lancucha = strlen(Z);
				usun_spacje();
				for(i=0; i<dl_lancucha; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ nie_liczba_naturalna(); break;
					} else zle = 0;
				}
			}
			if(zle == 0 && i != 0)			/* jak do tej pory jest dobrze */
			{	z = atoi(Z);
				if( (z<10 || z>300) && dl_lancucha>0 )
				{   liczba_poza_zakresem();
				} else
				{	zle = 0;		/* mimo wszystko jest dobrze */
					dl_jedn_na_osi_OX = z;
				}
			}
			gotoxy(44+j, 8); printf("         ");
		}
		if(zle == 0)					/* ostatecznie jest dobrze */
		{	dl_jedn_OX = dl_jedn_na_osi_OX;
			gotoxy(44+j, 8);
			textcolor(9); textbackground(kolor_tla_wyboru_parametrow);
			cprintf("%d", dl_jedn_na_osi_OX);
			wyczysc_raport_bledu();
		} else
		{	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
			gotoxy(44+j, 8);
		}
	} while(zle);

	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
	wyczysc_informacje();
	opcja++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybory_parametrow()						//
//                                                                      //
//		  Wyb¢r dàugoòci jednostki na osi OY w punktach ekranu  //
//									//
//			wstep_rutynowy()				//
//			za_dlugi_lancuch()				//
//			usun_spacje()					//
//			nie_liczba_naturalna()		        	//
//			liczba_poza_zakresem()		        	//
//			wyczysc_raport_bledu()		        	//
//			wyczysc_informacje()		        	//
//			czy_porzucic_program()	                	//
//			pomoc()						//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void dlugosc_jednostki_osi_OY(void)
{       opcja = 2;
	zle = 0;			/* znaczy: jest dobrze */
	if(dl_jedn_OY<10) j = 1; else if(dl_jedn_OY<100) j = 2; else j = 3;
		/* j - tu: dàugoòÜ akceptowanego (default) àancucha "dl_jedn_OY"... */
		/*... jeszcze przed wejòciem do moduàu bo zaàoæeniem jest, æe po ...*/
		/*... wykresie robimy nast©pny wykres nie wychodz•c z programu.     */
	gotoxy(18,7); textcolor(8);
	cprintf("DàugoòÜ jednostki na osi OY w punktach ekranu");
	gotoxy(33, 8); cprintf("(5ˆ220) [%d] ", dl_jedn_OY);

	do
	{	wstep_rutynowy();
		if(i == 0)
		{	zle = 0;
			dl_jedn_na_osi_OY = dl_jedn_OY;
			dl_lancucha = 0;
		}
		else
		{   if(sygnal)
				za_dlugi_lancuch();
			else
			{	dl_lancucha = strlen(Z);
				usun_spacje();
				for(i=0; i<dl_lancucha; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ nie_liczba_naturalna(); break;
					} else zle = 0;
				}
			}
			if(zle == 0 && i != 0)			/* jak do tej pory jest dobrze */
			{	z = atoi(Z);
				if( (z<5 || z>220) && dl_lancucha>0 )
				{	liczba_poza_zakresem();
				} else
				{	zle = 0;		/* mimo wszystko jest dobrze */
					dl_jedn_na_osi_OY = z;
				}
			}
			gotoxy(44+j, 8); printf("         ");
		}
		if(zle == 0)					/* ostatecznie jest dobrze */
		{	dl_jedn_OY = dl_jedn_na_osi_OY;
			gotoxy(44+j, 8);
			textcolor(9); textbackground(kolor_tla_wyboru_parametrow);
			cprintf("%d", dl_jedn_na_osi_OY);
			wyczysc_raport_bledu();
		} else
		{	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
			gotoxy(44+j, 8);
		}
	} while(zle);

	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
	wyczysc_informacje();

	gotoxy(17, 10); textcolor(8); textbackground(kolor_tla_wyboru_parametrow);
	cprintf("ZmniejszyÜ dàugoòÜ jednostki dziesi©ciokrotnie");
	gotoxy(16, 11);
	cprintf("( T(tak) / N(nie - inny dowolny klawisz) ) [");
	if(zmniejszenie_jednostki_OY == 1) cprintf("N] ? ");
	else cprintf("T] ? ");

	while(1)
	{	znak = getch();
		if(znak == 27)
		{	pozycja_kursora_x = wherex();
			pozycja_kursora_y = wherey();
			gettext(lewa, gora, prawa, dol, buff);
			czy_porzucic_program();
			wyczysc_informacje();
			textbackground(kolor_tla_wyboru_parametrow);
			gotoxy(pozycja_kursora_x, pozycja_kursora_y);
			continue;
		} else
			if(znak == 0)
			{	if(getch() == 59)
				{	pozycja_kursora_x = wherex();
					pozycja_kursora_y = wherey();
					gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
					strona = 5;
					pomoc();
					gotoxy(pozycja_kursora_x, pozycja_kursora_y);
					continue;
				} else
				{	getch();
					break;
				}
			} break;
	}

	textcolor(9); textbackground(kolor_tla_wyboru_parametrow);
	if(znak == 't' || znak == 'T')
	{   cprintf("Tak");
		zmniejszenie_jednostki_OY = 10;
	} else
		if(znak == 'n' || znak == 'N')
		{	cprintf("Nie");
			zmniejszenie_jednostki_OY = 1;
		} else	/* kaædy inny znak zignoruj i przyjmij "default" */
			if(zmniejszenie_jednostki_OY == 1) cprintf("Nie");
			else cprintf("Tak");
	opcja++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybory_parametrow()						//
//                                                                      //
//		  	Wyb¢r numeru wzoru tàa ekranu (od 0 do 11)	//
//									//
//			okno_wzorow_tla_i_barw()	        	//
//			wstep_rutynowy()				//
//			za_dlugi_lancuch()				//
//			usun_spacje()					//
//			nie_liczba_naturalna()		        	//
//			liczba_poza_zakresem()		        	//
//			wyczysc_raport_bledu()		        	//
//			wyczysc_informacje()		        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void nr_wzoru_tla_ekranu(void)
{       opcja = 3;
	okno_wzorow_tla_i_barw();
	zle = 0;			/* znaczy: jest dobrze */
	if(nr_wz_tla<10) j = 1; else j = 2;
		/* j - tu: dàugoòÜ akceptowanego (default) àa‰cucha "nr_wz_tla"...  */
		/*... jeszcze przed wejòciem do moduàu bo zaloæeniem jest, æe po ...*/
		/*... wykresie robimy nast©pny wykres nie wychodz•c z programu.     */
	gotoxy(22,7); textcolor(8);
	cprintf("Numer wzoru tàa ekranu (0ˆ11) [%d] ", nr_wz_tla);

	do
	{	wstep_rutynowy();
		if(i == 0)
		{	zle = 0;
			nr_wzoru_tla = nr_wz_tla;
			dl_lancucha = 0;
		}
		else
		{   if(sygnal)
				za_dlugi_lancuch();
			else
			{	dl_lancucha = strlen(Z);
				usun_spacje();
				for(i=0; i<dl_lancucha; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ nie_liczba_naturalna(); break;
					} else zle = 0;
				}
			}
			if(zle == 0 && i != 0)			/* jak do tej pory jest dobrze */
			{	z = atoi(Z);
				if( (z<0 || z>11) && dl_lancucha>0 )
				{	liczba_poza_zakresem();
				} else
				{	zle = 0;		/* mimo wszystko jest dobrze */
					nr_wzoru_tla = z;
				}
			}
			gotoxy(55+j, 7); printf("         ");
		}
		if(zle == 0)					/* ostatecznie jest dobrze */
		{	nr_wz_tla = nr_wzoru_tla;
			gotoxy(55+j, 7);
			textcolor(9); textbackground(kolor_tla_wyboru_parametrow);
			cprintf("%d", nr_wzoru_tla);
			wyczysc_raport_bledu();
		} else
		{	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
			gotoxy(55+j, 7);
		}
	} while(zle);

	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
	wyczysc_informacje();
	opcja++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybory_parametrow()						//
//                                                                      //
//		  	Wybor numeru koloru tla ekranu (od 0 do 15)     //
//									//
//			okno_wzorow_tla_i_barw()	        	//
//			wstep_rutynowy()				//
//			za_dlugi_lancuch()				//
//			usun_spacje()					//
//			nie_liczba_naturalna()		        	//
//			liczba_poza_zakresem()		        	//
//			wyczysc_raport_bledu()		        	//
//			wyczysc_informacje()		        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void nr_koloru_tla_ekranu(void)
{       opcja = 4;			/* !!!! to jest chyba zb©dne */
	okno_wzorow_tla_i_barw();
	zle = 0;			/* znaczy: jest dobrze */
	if(nr_kol_tla<10) j = 1; else j = 2;
		/* j - tu: dàugoòÜ akceptowanego (default) àa‰cucha "nr_kol_tla"... */
		/*... jeszcze przed wejòciem do moduàu bo zaàoæeniem jest, ze po ...*/
		/*... wykresie robimy nast©pny wykres nie wychodz•c z programu.     */
	gotoxy(21,7); textcolor(8);
	cprintf("Numer koloru tàa ekranu (0ˆ15) [%d] ", nr_kol_tla);

	do
	{	wstep_rutynowy();
		if(i == 0)
		{	zle = 0;
			nr_koloru_tla = nr_kol_tla;
			dl_lancucha = 0;
		}
		else
		{   if(sygnal)
				za_dlugi_lancuch();
			else
			{	dl_lancucha = strlen(Z);
				usun_spacje();
				for(i=0; i<dl_lancucha; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ nie_liczba_naturalna(); break;
					} else zle = 0;
				}
			}
			if(zle == 0 && i != 0)			/* jak do tej pory jest dobrze */
			{	z = atoi(Z);
				if( (z<0 || z>15) && dl_lancucha>0 )
				{	liczba_poza_zakresem();
				} else
				{	zle = 0;		/* mimo wszystko jest dobrze */
					nr_koloru_tla = z;
				}
			}
			gotoxy(55+j, 7); printf("         ");
		}
		if(zle == 0)					/* ostatecznie jest dobrze */
		{	nr_kol_tla = nr_koloru_tla;
			gotoxy(55+j, 7);
			textcolor(9); textbackground(kolor_tla_wyboru_parametrow);
			cprintf("%d", nr_koloru_tla);
			wyczysc_raport_bledu();
		} else
		{	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
			gotoxy(55+j, 7);
		}
	} while(zle);

	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
	wyczysc_informacje();
	opcja++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybory_parametrow()						//
//                                                                      //
//	     Wyb¢r numeru koloru osi ukàadu wsp¢àrz©dnych (od 0 do 15)	//
//									//
//			okno_wzorow_tla_i_barw()	        	//
//			wstep_rutynowy()				//
//			kolor_ten_sam()			        	//
//			za_dlugi_lancuch()				//
//			usun_spacje()					//
//			nie_liczba_naturalna()		        	//
//			liczba_poza_zakresem()		        	//
//			wyczysc_raport_bledu()		        	//
//			wyczysc_informacje()		        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void nr_koloru_osi_ukladu_wspolrz(void)
{       opcja = 5;			/* !!!! to jest chyba zb©dne */
	okno_wzorow_tla_i_barw();
	zle = 0;			/* znaczy: jest dobrze */
	if(nr_kol_osi<10) j = 1; else j = 2;
		/* j - tu: dàugoòÜ akceptowanego (default) àa‰cucha "nr_kol_osi"... */
		/*... jeszcze przed wejòciem do moduàu bo zaàoæeniem jest, æe po ...*/
		/*... wykresie robimy nast©pny wykres nie wychodz•c z programu.     */
	gotoxy(14,7); textcolor(8);
	cprintf("Numer koloru osi ukàadu wsp¢àrz©dnych (0ˆ15) [%d] ", nr_kol_osi);

	do
	{	wstep_rutynowy();
		if(i == 0)
		{	if(nr_kol_osi == nr_koloru_tla)
				kolor_ten_sam();
			else
			{	zle = 0;
				nr_koloru_osi = nr_kol_osi;
				dl_lancucha = 0;
			}
		}
		else
		{   if(sygnal)
				za_dlugi_lancuch();
			else
			{	dl_lancucha = strlen(Z);
				usun_spacje();
				for(i=0; i<dl_lancucha; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ nie_liczba_naturalna(); break;
					} else zle = 0;
				}
			}
			if(zle == 0 && i != 0)			/* jak do tej pory jest dobrze */
			{	z = atoi(Z);
				if( (z<0 || z>15) && dl_lancucha>0 )
				{	liczba_poza_zakresem();
				} else
					if(z==nr_koloru_tla)
					{   kolor_ten_sam();
					} else
					{	zle = 0;	/* mimo wszystko jest dobrze */
						nr_koloru_osi = z;
					}
			}
			gotoxy(62+j, 7); printf("         ");
		}
		if(zle == 0)					/* ostatecznie jest dobrze */
		{	nr_kol_osi = nr_koloru_osi;
			gotoxy(62+j, 7);
			textcolor(9); textbackground(kolor_tla_wyboru_parametrow);
			cprintf("%d", nr_koloru_osi);
			wyczysc_raport_bledu();
		} else
		{	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
			gotoxy(62+j, 7);
		}
	} while(zle);

	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
	wyczysc_informacje();
	opcja++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybory_parametrow()						//
//                                                                      //
//		      Wyb¢r numeru koloru wykresu funkcji (od 0 do 15)	//
//									//
//			okno_wzorow_tla_i_barw()	        	//
//			wstep_rutynowy()				//
//			kolor_ten_sam()			        	//
//			za_dlugi_lancuch()				//
//			usun_spacje()					//
//			nie_liczba_naturalna()		        	//
//			liczba_poza_zakresem()		        	//
//			wyczysc_raport_bledu()		        	//
//			wyczysc_informacje()		        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void nr_koloru_wykresu_funkcji(void)
{       opcja = 6;			/* !!!! to jest chyba zb©dne */
	okno_wzorow_tla_i_barw();
	zle = 0;			/* znaczy: jest dobrze */
	if(nr_kol_wykresu<10) j = 1; else j = 2;
		/*j - tu: dàugoòÜ akceptowanego (default) àa‰cucha "nr_kol_wykresu"..*/
		/*... jeszcze przed wejòciem do moduàu bo zaàoæeniem jest, æe po ...*/
		/*... wykresie robimy nast©pny wykres nie wychodz•c z programu.     */
	gotoxy(18, 7); textcolor(8);
	cprintf("Numer koloru wykresu funkcji (0ˆ15) [%d] ", nr_kol_wykresu);

	do
	{	wstep_rutynowy();
		if(i == 0)
		{	if(nr_kol_wykresu == nr_koloru_tla)
				kolor_ten_sam();
			else
			{	zle = 0;
				nr_koloru_wykresu = nr_kol_wykresu;
				dl_lancucha = 0;
			}
		}
		else
		{   if(sygnal)
				za_dlugi_lancuch();
			else
			{	dl_lancucha = strlen(Z);
				usun_spacje();
				for(i=0; i<dl_lancucha; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ nie_liczba_naturalna(); break;
					} else zle = 0;
				}
			}
			if(zle == 0 && i != 0)	/* jak do tej pory jest dobrze */
			{	z = atoi(Z);
				if( (z<0 || z>15) && dl_lancucha>0 )
				{	liczba_poza_zakresem();
				} else
					if(z==nr_koloru_tla)
					{   kolor_ten_sam();
					} else
					{	zle = 0;	/* mimo wszystko jest dobrze */
						nr_koloru_wykresu = z;
					}
			}
			gotoxy(57+j, 7); printf("         ");
		}
		if(zle == 0)					/* ostatecznie jest dobrze */
		{	nr_kol_wykresu = nr_koloru_wykresu;
			gotoxy(57+j, 7);
			textcolor(9); textbackground(kolor_tla_wyboru_parametrow);
			cprintf("%d", nr_koloru_wykresu);
			wyczysc_raport_bledu();
		} else
		{	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
			gotoxy(57+j, 7);
		}
	} while(zle);

	for(i=dl_lancucha; i>0; i--) Z[i-1] = Z[i];
	wyczysc_informacje();
	opcja++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_wielomianu()				        	//
//	wpisz_lancuch_i_analizuj_go()					//
//	dlugosc_jednostki_osi_OX()					//
//	dlugosc_jednostki_osi_OY()					//
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
//		 Sprawdzanie kolejnych znak¢w i wpisywanie ich àa‰cucha	//
//									//
//			wstepna_analiza_znakow();	        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wstep_rutynowy(void)
{       if(!(opcja == 0 && sygnal)) i = 0;

	proba_poprawienia = proba_porzucenia = wezwanie_pomocy = sygnal = 0;
	textcolor(11);

	while((znak = getch()) != 13)
	{   wstepna_analiza_znakow();
		if(proba_poprawienia)
		   printf("\x07");
		else
			if(!proba_porzucenia && !sygnal && !wezwanie_pomocy)
				cprintf("%c", znak);
		if(sygnal) break;
	}

	Z[i] = '\0';
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wstep_rutynowy()						//
//                                                                      //
//		  	Sprawdzanie znaku wprowadzonego z klawiatury	//
//									//
//			pomoc()						//
//			brak_mozliwosci_poprawiania()           	//
//			czy_porzucic_program()		        	//
//			wyczysc_informacje()		        	//
//                      tlo_wykresu_funkcji()                           //
//			grafika_wstepu()				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wstepna_analiza_znakow(void)
{       int m;

	if(proba_poprawienia)
	{	proba_poprawienia = 0;
		textbackground(11); gotoxy(2, 25);
		cprintf("                                                        "
				"                      ");
		textcolor(11);
		if(opcja > 0)
			textbackground(kolor_tla_wyboru_parametrow);
		else
			if(funkcja_dowolna)
				textbackground(1);
			else
				textbackground(7);
		gotoxy(pozycja_kursora_x, pozycja_kursora_y);
	}
	else
		if(proba_porzucenia)
			proba_porzucenia = 0;
		else
			if(wezwanie_pomocy)
				wezwanie_pomocy = 0;
	if(znak == 0)
	{	if(getch() == 59)
		{   wezwanie_pomocy = 1;
			pozycja_kursora_x = wherex();
			pozycja_kursora_y = wherey();
			gettext(lewa-7, gora-2, prawa+8, dol+5, buff);
			if(opcja == 0)
			{	if(funkcja_dowolna)	strona = 4;
				else strona = 3;
			}
			else strona = 5;
			pomoc();
			textcolor(11);
			if(opcja > 0)
				textbackground(kolor_tla_wyboru_parametrow);
			else
				if(funkcja_dowolna)
					textbackground(1);
				else
					textbackground(7);
			gotoxy(pozycja_kursora_x, pozycja_kursora_y);
		}
		else
		{	proba_poprawienia = 1;
			pozycja_kursora_x = wherex();
			pozycja_kursora_y = wherey();
			brak_mozliwosci_poprawiania();
		}
	} else
		if(znak<32 || znak>126)
		{   if(znak == 8 && i > 0)
			{	printf("\b  \b");
				if(sygnal)
					sygnal = 0;
			}
			else		 /* przyciòni©to TAB lub ESC */
			{   if(znak == 27)
				{   proba_porzucenia = 1;
					pozycja_kursora_x = wherex();
					pozycja_kursora_y = wherey();
					gettext(lewa, gora, prawa, dol, buff);
					czy_porzucic_program();
					wyczysc_informacje();
					textcolor(11);
					if(opcja > 0)
						textbackground(kolor_tla_wyboru_parametrow);
					else
						if(funkcja_dowolna)
							textbackground(1);
						else
							textbackground(7);
					gotoxy(pozycja_kursora_x, pozycja_kursora_y);
				}
				else
				{	proba_poprawienia = 1;
					pozycja_kursora_x = wherex();
					pozycja_kursora_y = wherey();
					brak_mozliwosci_poprawiania();
				}
				i++;
			}
			i--;
		} else
			{	m = i;
				Z[m++] = znak;
				if(opcja > 0)
				{	if(m == 1 && (znak == '?' || znak == '/') )
					{	zle = 1;
						dl_lancucha = 1;
						// Pytanie: Czy zmieniaÜ parametry rysunku, czy zostawiÜ wartoòci opcjonalne?
						// Na ekranie pozostaje okno zapytania o zapis ale juæ nieaktywne - nie przejmuj si© nim.
						gotoxy(2,25); textcolor(4); textbackground(10);
						cprintf(" [Enter] - wykres funkcji;  "
							"[Inny dowolny klawisz] - wyb¢r parametr¢w wykresu ");
						znak = getch();
						if(znak == 13) tlo_wykresu_funkcji();
						else grafika_wstepu();
					}
					if(m == 9)
					{	printf("\b \b\x07");
						sygnal = 1;
						m--;
						dl_lancucha = 8;
					} else sygnal = 0;
				} else
					if(funkcja_dowolna)
					{  	if(Z[m-1] > 47 && Z[m-1] < 58) /* aktualne jest m-1..*/
						{	jest_cyfra++; /*..ze wzgl©du na wczeòniejsze m++.*/
							if(jest_cyfra > 6)
							{	sygnal = 1;
								m--;
							}
						} else
							if(Z[m] != 32)
								jest_cyfra = 0;
						if(m == 70)
						{	sygnal = 1;
							m--;
						}
					 } else
						if(m == 15)
						{	sygnal = 1;
							m--;
							dl_lancucha = 14;
						} else sygnal = 0; /* to else jest chyba zbyteczne */
				i = m;
			}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wstepna_analiza_znakow()					//
//                                                                      //
//  Raport o niemoæliwoòci uæywania klawiszy mog•cych byÜ korekcyjnymi	//
//					( opr¢cz 'Esc', 'F1' i '<--')	//
//									//
//////////////////////////////////////////////////////////////////////////
void brak_mozliwosci_poprawiania(void)
{       textcolor(11); textbackground(10); gotoxy(2, 25);
	cprintf("     Nie ma moæliwoòci poprawiania opr¢cz usuwania ostatniego znaku [<--]     ");
	gotoxy(pozycja_kursora_x, pozycja_kursora_y);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dlugosc_jednostki_osi_OX()					//
//	dlugosc_jednostki_osi_OY()					//
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
//				  Usuwa spacje z àa‰cucha znakowego	//
//									//
//////////////////////////////////////////////////////////////////////////
void usun_spacje(void)
{	for(i=0; i<dl_lancucha; i++)
	{	if(Z[i]==32)
		{	for(k=i; k<dl_lancucha; k++) Z[k] = Z[k+1];
			dl_lancucha--;
			i--;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dlugosc_jednostki_osi_OX()					//
//	dlugosc_jednostki_osi_OY()					//
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
//	    Raportuje o przekroczeniu limitu iloòci znak¢w w àa‰cuchu   //
//									//
//////////////////////////////////////////////////////////////////////////
void za_dlugi_lancuch(void)
{	zle = 1;
	gotoxy(18, 10); textcolor(4);
	cprintf(" Tak duæa iloòÜ znak¢w jest nie do przyj©cia");
	gotoxy(35, 11); textcolor(9); cprintf("Popraw dane");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dlugosc_jednostki_osi_OX()					//
//	dlugosc_jednostki_osi_OY()					//
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
//	 Raportuje o wprowadzeniu àa‰cucha, kt¢rego nie da si© zamieniÜ	//
//	 na liczb© naturaln•				        	//
//									//
//////////////////////////////////////////////////////////////////////////
void nie_liczba_naturalna(void)
{	zle = 1;
	gotoxy(18, 10); textcolor(4);
	cprintf("WielkoòÜ wprowadzona to nie liczba naturalna");
	gotoxy(35, 11); textcolor(9); cprintf("Popraw dane");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dlugosc_jednostki_osi_OX()				        //
//	dlugosc_jednostki_osi_OY()					//
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
//	   Raportuje o przekroczeniu limitu wielkoòci liczby naturalnej	//
//	   w zaleænoòci od wybieranej opcji				//
//									//
//////////////////////////////////////////////////////////////////////////
void liczba_poza_zakresem(void)
{	zle = 1;
	gotoxy(18, 10); textcolor(4);
	if(opcja==1) cprintf("     Liczba musi byÜ z zakresu [10;300]     ");
	else if(opcja==2) cprintf("     Liczba musi byÜ z zakresu [5;220]      ");
	 else if(opcja==3) cprintf("      Liczba musi byÜ z zakresu [0;11]      ");
	  else cprintf("      Liczba musi byÜ z zakresu [0;15]      ");
	gotoxy(35, 11); textcolor(9); cprintf("Popraw dane");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
// Raportuje o wyborze koloru osi liczbowych albo koloru wykresu funkcji//
// b©dacego jednoczeònie kolorem tàa ekranu				//
//									//
//////////////////////////////////////////////////////////////////////////
void kolor_ten_sam(void)
{	zle = 1;
	gotoxy(18, 10); textcolor(4);
	if(opcja==5)
		cprintf("Kolor osi liczbowych jest ten sam co kolor tàa");
	else
		cprintf("Kolor wykresu funkcji jest ten sam co kolor tàa");
	gotoxy(35, 11); textcolor(9); cprintf("Popraw dane");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dlugosc_jednostki_osi_OX()					//
//	dlugosc_jednostki_osi_OY()					//
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
//	      Wyczyszcza informacje o bà©dach z okna wyboru parametr¢w	//
//									//
//////////////////////////////////////////////////////////////////////////
void wyczysc_raport_bledu(void)
{	textbackground(kolor_tla_wyboru_parametrow);
	gotoxy(18, 10);
	cprintf("                                               ");
	gotoxy(35, 11); cprintf("           ");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_postaci_funkcji()					//
//	wybieranie_wielomianu()						//
//	wybieranie_funkcji_dowolnej()					//
//	tablica_operatorow_i_funkcji()					//
//	wpisz_lancuch_i_analizuj_go()					//
//	wybory_parametrow()						//
//	dlugosc_jednostki_osi_OX()					//
//	dlugosc_jednostki_osi_OY()					//
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//	wstepna_analiza_znakow()					//
//                                                                      //
//			  Wyczyszcza informacje o bà©dach z okna opcji	//
//									//
//////////////////////////////////////////////////////////////////////////
void wyczysc_informacje(void)
{	if(opcja >0) textbackground(kolor_tla_ekranu_opcji);
	else
		if(funkcja_dowolna)
			textbackground(1);
		else textbackground(7);
	gotoxy(2, 25);
	cprintf("                                       "
			"                                       ");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	nr_wzoru_tla_ekranu()						//
//	nr_koloru_tla_ekranu()						//
//	nr_koloru_osi_ukladu_wspolrz()					//
//	nr_koloru_wykresu_funkcji()					//
//                                                                      //
//   Okno informacyjne wyszczeg¢lniaj•ce albo numery wzor¢w tàa ekranu	//
//   albo kolory i ich numery						//
//									//
//////////////////////////////////////////////////////////////////////////
void okno_wzorow_tla_i_barw(void)
{	if(opcja==3) { textcolor(3); textbackground(4); } else
		if(opcja==4) { textcolor(4); textbackground(1); } else
			if(opcja==5) { textcolor(14); textbackground(5); }
				else { textcolor(15); textbackground(6); }	  /* opcja = 6 */

	gotoxy(5, 15);
	cprintf("⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ"
			"ƒƒƒƒƒƒƒƒƒƒø");
	for(i=0; i<7; i++)
	{	gotoxy(5, 16+i);
		cprintf("≥                                                        "
				"              ≥");
	}
	if(opcja==3) gotoxy(5, 16+i); else gotoxy(5, 15+i);
	cprintf("¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ"
			"ƒƒƒƒƒƒƒƒƒƒŸ");
	i = 15;
	if(opcja == 3)
	{	textcolor(9); gotoxy(29, ++i); cprintf("Tablica wzor¢w tàa ekranu");
		textcolor(2);
		gotoxy(10, ++i); cprintf("0  jednolity, opcjonalny kolor   "
								 " 6  grube, rozmyte linie \\\\\\");
		gotoxy(10, ++i); cprintf("1  jednolity kolor               "
								 " 7  kratka zwykàa");
		gotoxy(10, ++i); cprintf("2  grube linie -----             "
								 " 8  szeroka kratka poprzeczna");
		gotoxy(10, ++i); cprintf("3  w•zkie linie ///              "
								 " 9  drobna kratka poprzeczna");
		gotoxy(10, ++i); cprintf("4  grube linie ///               "
								 "10  drobnoziarnisty");
		gotoxy(10, ++i); cprintf("5  grube linie \\\\\\               "
								 "11  gruboziarnisty");
	} else
	{   if(opcja==4) textcolor(6); else
			if(opcja==5) textcolor(12); else textcolor(10);
		gotoxy(34, ++i); cprintf("Lista barw");
		if(opcja==4) textcolor(5); else
			if(opcja==5) textcolor(7); else textcolor(12);
		gotoxy(25, ++i); cprintf("Naciònij [?] aby zobaczyÜ barwy");
		if(opcja==4) textcolor(3); else
			if(opcja==5) textcolor(1); else textcolor(13);
		gotoxy(8, ++i);	cprintf("0  czarny     4  czerwony    "
								" 8  ciemnoszary     12  jasnoczerwony");
		gotoxy(8, ++i);	cprintf("1  niebieski  5  fioletowy   "
								" 9  jasnoniebieski  13  jasnofioletowy");
		gotoxy(8, ++i);	cprintf("2  zielony    6  br•zowy     "
								"10  jasnozielony    14  z¢àty");
		gotoxy(8, ++i);	cprintf("3  cyjanowy   7  jasnoszary  "
								"11  jasnocyjanowy   15  biaày");
	}

	textbackground(kolor_tla_wyboru_parametrow);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_postaci_funkcji()					//
//	wybieranie_wielomianu()						//
//	wybieranie_funkcji_dowolnej()					//
//	tablica_operatorow_i_funkcji()					//
//	wybory_parametrow()						//
//	dlugosc_jednostki_osi_OY()					//
//	wstepna_analiza_znakow()					//
//                                                                      //
//			Okno porzucania programu w trybie tekstowym	//
//									//
//			zdania_sprzeczne_ze_soba(ilosc_skokow)          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void czy_porzucic_program(void)
{       int m, mm, mmm=1;
	char m_ch1, m_ch2;

	if(opcja == 0) textbackground(3); else textbackground(2);
	textcolor(1); gotoxy(lewa, gora);
	cprintf("…ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕª");
	for(m=1; m<6; m++)
	{	gotoxy(lewa, gora+m);
		cprintf("∫                                   ∫");
	}
	gotoxy(lewa, gora+m);
	cprintf("»ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕº");
	textcolor(14); gotoxy(lewa+9, gora+2); cprintf("PORZUCENIE PROGRAMU");
	textcolor(11); gotoxy(lewa+6, gora+4); cprintf("Tak                  Nie");

	do
	{   mm = fmod(ilosc_skokow, 2);
		textcolor(11); textbackground(10); gotoxy(2, 25);
		zdania_sprzeczne_ze_soba(ilosc_skokow);
		if(mm == 0)
		{	textcolor(11); textbackground(2);
			gotoxy(lewa+26, gora+4); cprintf(" Tak ");
			textbackground(4); gotoxy(lewa+6, gora+4);
			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* zdefiniowane w getch(): #define KEY_RIGHT 77 */
						if( m_ch2 == 77 ) { ilosc_skokow++; break; }
		// Ten zapis robi ostrzeæenie -->  if( (m_ch2 = getch()) == 77 ) { ilosc_skokow++; break; }
					}
					else
					{	if( m_ch1 == 13 ) { mmm = 0; break; }
						else
							if( m_ch1 == 9 ) { ilosc_skokow++;	break; }
					}
				textcolor(1); cprintf(" Nie \b\b\b"); delay(100);
				printf("\b\b");
				textcolor(9); cprintf(" Nie \b\b\b"); delay(100);
				printf("\b\b");
				if(m > 8) m = 0;
			}
		} else
		{	textcolor(11); textbackground(2);
			gotoxy(lewa+6, gora+4); cprintf(" Nie ");
			textbackground(4); gotoxy(lewa+26, gora+4);

			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* zdefiniowane w getch(): #define KEY_LEFT 75 */
						if( m_ch2 == 75 ) { ilosc_skokow++; break; }
		// Ten zapis robi ostrzeæenie -->  if( (m_ch2 = getch()) == 75 ) { ilosc_skokow++; break; }
					}
					else
					{	if( m_ch1 == 13 ) exit(1);
						else
							if( m_ch1 == 9 ) { ilosc_skokow++; break; }
					}
				textcolor(1); cprintf(" Tak \b\b\b"); delay(100);
				printf("\b\b");
				textcolor(9); cprintf(" Tak \b\b\b"); delay(100);
				printf("\b\b");
				if(m > 8) m = 0;
			}
		}
	if(ilosc_skokow == 21) ilosc_skokow = 0;
	} while(mmm);

	puttext(lewa, gora, prawa, dol, buff);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	czy_porzucic_program()						//
//                                                                      //
//		     Zestaw zda‰ dla sàowa 'Tak' i dla sàowa 'Nie' dla	//
//		     moduàu 'czy_porzucic_program();'			//
//									//
//////////////////////////////////////////////////////////////////////////
void zdania_sprzeczne_ze_soba(int ilosc_skokow)
{       switch(ilosc_skokow)
	{	case 0 : cprintf("           Nie czas na æarty!  Po co miaàbyò porzucaÜ ten program?            "); break;
		case 1 : cprintf(" Zajmij si© wreszcie czymò innym i nie marnuj czasu przy tym gàupim programie."); break;
		case 2 : cprintf("  Badaj moæliwoòci tego programu i rozwijaj swoje umiej©tnoòci w matematyce!  "); break;
		case 3 : cprintf("Czy naprawd© zrobiàes wszystko co na dziò zaplanowaàeò. Upewnij si© co do tego"); break;
		case 4 : cprintf(" Ja program, jestem Twoim przyjacielem wi©c zosta‰ ze mn• i swoim komputerem. "); break;
		case 5 : cprintf(" Czy pozmywaàeò naczynia po jedzeniu. Jeæeli nie to przyciònij teraz [ENTER]. "); break;
		case 6 : cprintf("      Po co to robiÜ skoro nic ciekawszego niæ ten program byÜ nie moæe.      "); break;
		case 7 : cprintf("   Czyæbyò nie wiedziaà æe s• wi©ksze przyjemnoòci niæ patrzenie w komputer.  "); break;
		case 8 : cprintf("Tylko ja na tym ówiecie nigdy nie mam do Ciebie pretensji wi©c zosta‰my razem."); break;
		case 9 : cprintf("   Wyà•cz komputer i sprawd´ czy ciocia Zosia nie przyjechaàa z prezentami.   "); break;
		case 10: cprintf("Tylko ja na Ciebie nigdy nie krzycz© wi©c dlaczego ode mnie uciekasz. Program."); break;
		case 11: cprintf("        Lepiej b©dzie jak zabierzesz si© za odrabianie zada‰ domowych.        "); break;
		case 12: cprintf("  Porzucaj•c mnie skazaàbyò si© na reszt© dnia na pastw© mamy, taty i szkoly. "); break;
		case 13: cprintf("  Jak mamusia woàa to trzeba jej sàuchaÜ. Wyjd´ z programu i wyà•cz komputer. "); break;
		case 14: cprintf("        Nie b•d´ niewolnikiem cudzych upodoba‰ i myòli.  To Tw¢j wyb¢r!       "); break;
		case 15: cprintf("         Czyæbyò zapomniaà o swoich podstawowych obowi•zkach domowych.        "); break;
		case 16: cprintf("   Czuàbym si© zawiedziony gdybyò teraz mnie porzucià.  To ja, Tw¢j program.  "); break;
		case 17: cprintf("      Jest szansa przyciòni©cia klawisza [ENTER] - zr¢b to natychmiast!       "); break;
		case 18: cprintf(" Chyba nie zrobisz mi tego.  To ja, Tw¢j przyjaciel, Tw¢j komputerowy program."); break;
		case 19: cprintf("      Wyjd´ wreszcie z programu bo jak tego nie zrobisz to zobaczysz !!!      "); break;
		case 20: cprintf("      Something is rotten in Poland (çle si© dzieje w pa‰stwie polskim).      "); break;
		default: cprintf("                                                                      ");
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wprowadzenie()                                                 	//
//	grafika_wstepu()						//
//	menu()								//
//                                                                      //
//			Okno porzucania programu w trybie graficznym	//
//									//
//////////////////////////////////////////////////////////////////////////
void czy_porzucic_program_gr(void)
{       int m, mm, mmm=1;
	char m_ch1, m_ch2;
	int ilosc_skokow = 0;
	int pole_porzucenia_programu[] = {lewa_gr, gora_gr, prawa_gr, gora_gr, prawa_gr, dol_gr, lewa_gr, dol_gr, lewa_gr, gora_gr};

	setfillstyle(9, 2);
	fillpoly(5, pole_porzucenia_programu);
	rectangle(lewa_gr+3, gora_gr+3, prawa_gr-3, dol_gr-3);
	setcolor(14);
	moveto(lewa_gr+28, gora_gr+30);
	settextstyle(2, HORIZ_DIR, 7);
	outtext("PORZUCENIE PROGRAMU");
	setcolor(11);			  /* w tym miejscu jest to zbyteczne */
	moveto(lewa_gr+47, gora_gr+75);
	settextstyle(1, HORIZ_DIR, 3);
	outtext("Nie         Tak");

	do
	{   mm = fmod(ilosc_skokow, 2);
		if(mm == 0)
		{	setcolor(11); moveto(lewa_gr+190, gora_gr+75);
			settextstyle(1, HORIZ_DIR, 3); outtext("Tak");
			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* zdefiniowane w getch(): #define KEY_RIGHT 77 */
						if( m_ch2 == 77 ) { ilosc_skokow++; break; }
		// Ten zapis robi ostrzeæenie -->  if( (m_ch2 = getch()) == 77 ) { ilosc_skokow++; break; }
					}
					else
					{	if( m_ch1 == 13 ) { mmm = 0; break; }
						else
							if( m_ch1 == 9 ) { ilosc_skokow++;	break; }
					}
					setcolor(14); moveto(lewa_gr+47, gora_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("Nie");
					delay(100);
					setcolor(13); moveto(lewa_gr+47, gora_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("Nie");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		{	setcolor(11); moveto(lewa_gr+47, gora_gr+75);
			settextstyle(1, HORIZ_DIR, 3); outtext("Nie");
			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* zdefiniowane w getch(): #define KEY_LEFT 75 */
						if( m_ch2 == 75 ) { ilosc_skokow++; break; }
		// Ten zapis robi ostrzeæenie -->  if( (m_ch2 = getch()) == 75 ) { ilosc_skokow++; break; }
					}
					else
					{	if( m_ch1 == 13 ) exit(1);
						else
							if( m_ch1 == 9 ) { ilosc_skokow++; break; }
					}
					setcolor(14); moveto(lewa_gr+190, gora_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("Tak");
					delay(100);
					setcolor(13); moveto(lewa_gr+190, gora_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("Tak");
					delay(100);
					if(m > 8) m = 0;
			}
		}
	if(ilosc_skokow == 21) ilosc_skokow = 0;
	} while(mmm);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybieranie_postaci_funkcji()					//
//	wybieranie_wielomianu()						//
//	wybieranie_funkcji_dowolnej()					//
//	tablica_operatorow_i_funkcji()					//
//	wybory_parametrow()						//
//	dlugosc_jednostki_osi_OY()					//
//	wstepna_analiza_znakow()					//
//                                                                      //
//			Okno 'pomocy' dla trybu tekstowego		//
//									//
//////////////////////////////////////////////////////////////////////////
void pomoc(void)
{       int m;
	char znak_dodatkowy;

	gotoxy(15, 6); textcolor(8);
	if(strona == 3) textbackground(0); else
		if(strona == 4 || strona == 5) textbackground(2); else
			textbackground(7);
	cprintf("⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ POMOC ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø");
	for(m=0; m<12; m++)
	{	gotoxy(15, 7+m);
	cprintf("≥                                                  ≥");
	}
	gotoxy(15, 7+m);
	cprintf("¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ");

	if(strona == 2) goto petla_2; else
		if(strona == 3) goto petla_3; else
			if(strona == 4) goto petla_4; else
				if(strona == 5) goto petla_5; else
					goto petla_1;
	petla_1:
	strona = 1;
	gotoxy(16, 7); cprintf(" Ten tekst jest niedost©pny w obrazie graficznym! ");
	gotoxy(16, 8); cprintf(" Aby usun•Ü ten tekst przyciònij klawisz [ESC].   ");
	gotoxy(16, 9); cprintf("                                                  ");
	gotoxy(16,10); cprintf(" Program dziaàa na dowolnym PC i wymaga 200kb wol-");
	gotoxy(16,11); cprintf(" nej pami©ci.                                     ");
	gotoxy(16,12); cprintf(" Ten program jest przeznaczony dla wszystkich     ");
	gotoxy(16,13); cprintf(" dzieci bez jakiegokolwiek wyj•tku a jego wersja  ");
	gotoxy(16,14); cprintf(" w dowolnym j©zyku w kaædej chwili moæe byÜ àatwo ");
	gotoxy(16,15); cprintf(" dost©pna bez ogranicze‰ i zupeànie bezpàatnie.   ");
	gotoxy(16,16); cprintf("                                                  ");
	gotoxy(16,17); cprintf(" Jeæeli znajdziesz bà•d lub masz pytania, zadzwo‰:");
	gotoxy(16,18); cprintf("          (znajdziesz mnie w Internecie)          ");
	gotoxy(39,19); cprintf("ƒƒƒƒƒƒƒƒƒƒƒƒ [Page Down] \b\b\b\b\b\b\b");
	znak = getch();
	goto rozdzielnia;

	petla_2:
	strona = 2;
	gotoxy(16, 7); cprintf("              "); textcolor(5);
	 cprintf("Wyb¢r postaci funkcji"); textcolor(8); cprintf("               ");
	gotoxy(16, 8); cprintf("Moæesz wybraÜ tylko jeden wykres funkcji w jednym ");
	gotoxy(16, 9); cprintf("ukàadzie wsp¢àrz©dnych.                           ");
	gotoxy(16,10); cprintf("W obu przypadkach (Wielomianu i Wyraæeniu dowolnej");
	gotoxy(16,11); cprintf("postaci) dozwolony jest zapis jak na tablicy szko-");
	gotoxy(16,12); cprintf("lnej - z odst©pami, bez niepotrzebnych znak¢w mno-");
	gotoxy(16,13); cprintf("æenia i nawias¢w, dowolnymi wielkoòciami liter.   ");
	gotoxy(16,14); cprintf("'pi'jest zamienione na 'À', 'e' na podstaw© ln(). ");
	gotoxy(16,15); cprintf("Przykàad wielomianu:                              ");
	gotoxy(16,16); cprintf("  -12.03x^5 + 2xx - 50.33x + 1.1                  ");
	gotoxy(16,17); cprintf("Przykàad dowolnego wyraæenia:                     ");
	gotoxy(16,18); cprintf("  3.1ln(3x) - xsin(2x-cos(pix)) + pow(e-1.2,x) - x");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	znak = getch();
	goto rozdzielnia;

	petla_3:
	strona = 3;
	gotoxy(16, 7); cprintf("                    "); textcolor(6);
	 cprintf("Wielomian"); textcolor(8); cprintf("                    ");
	gotoxy(16, 8); cprintf("Dopuszczalna wielkoòÜ liczb jest z zakresu:       ");
	gotoxy(16, 9); cprintf("      (0.0000001 ; 1000000)                       ");
	gotoxy(16,10); cprintf("Tylko klawiszem [<--] moæesz poprawiÜ liczb©.     ");
	gotoxy(16,11); cprintf("Nie moæesz pisaÜ wi©cej niæ 15 znak¢w w liczbie.  ");
	gotoxy(16,12); cprintf("Wtedy moæesz albo usuwaÜ ostatnie jej cyfry [<--] ");
	gotoxy(16,13); cprintf("albo zaakceptowaÜ liczb© [ENTER].                 ");
	gotoxy(16,14); cprintf("Nienapisanie liczby jako wsp¢àczynnika pot©gi x   ");
	gotoxy(16,15); cprintf("jest traktowanie jej jak 0 (zero) a wi©c wtedy    ");
	gotoxy(16,16); cprintf("zeruje si© skàadnik wielomianu.                   ");
	gotoxy(16,17); cprintf("UWAGA: Uæycie wysokich pot©g x powoduje przekàama-");
	gotoxy(16,18); cprintf("    nia na wykresie dla x>25 i x<-25 rz©du paru %.");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	znak = getch();
	goto rozdzielnia;

	petla_4:
	strona = 4;
	gotoxy(16, 7); cprintf("             "); textcolor(1);
	 cprintf("Dowolna postaÜ wyraæenia"); textcolor(8); cprintf("             ");
	gotoxy(16, 8); cprintf("Pisz ostroænie sugeruj•c si© tablic• funkcji.     ");
	gotoxy(16, 9); cprintf("Skàadnia funkcji matematycznych musi byÜ utrzymana");
	gotoxy(16,10); cprintf("à•cznie z nazw• tej funkcji. Poprawa dàugiego za- ");
	gotoxy(16,11); cprintf("pisu moæe byÜ trudnym zadaniem ale b©dziesz mieÜ  ");
	gotoxy(16,12); cprintf("podgl•d wyraæenia, kt¢rego program nie przyjmie.  ");
	gotoxy(16,13); cprintf("Nie pisz wi©cej niæ 70 znak¢w w wyraæeniu, pami©- ");
	gotoxy(16,14); cprintf("taj, æe zakres wsp¢àrz©dnych jest ograniczony.    ");
	gotoxy(16,15); cprintf("Nie martw si© dziedzin• funkcji - statystyczna    ");
	gotoxy(16,16); cprintf("analiza wykresu funkcji w zakresie widzianym na   ");
	gotoxy(16,17); cprintf("ekranie wykresu b©dzie dost©pna po wykonaniu rysu-");
	gotoxy(16,18); cprintf("nku. Taktuj liczby ostroænie: 4.9988 to zwykle 5. ");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	znak = getch();
	goto rozdzielnia;

	petla_5:
	strona = 5;
	gotoxy(16, 7); cprintf("                       "); textcolor(4);
	 cprintf("Opcje"); textcolor(8); cprintf("                      ");
	gotoxy(16, 8); cprintf("Zdaj sobie spraw© z ograniczonej moæliwoòci ekranu");
	gotoxy(16, 9); cprintf("i wiedz o paruprocentowych bà©dach dla x>25 i     ");
	gotoxy(16,10); cprintf("x<-25 w przypadku duæych lub maàych (np.0.0000001)");
	gotoxy(16,11); cprintf("liczb mog•cych wyst•piÜ jako poòrednie liczby w   ");
	gotoxy(16,12); cprintf("rachunkach.                                       ");
	gotoxy(16,13); cprintf("Zar¢wno przed jak i po wykonaniu rysunku moæesz   ");
	gotoxy(16,14); cprintf("zmieniÜ opcje dla wykonywanych wykres¢w.          ");
	gotoxy(16,15); cprintf("Zawsze moæesz mieÜ podgl•d na barwy [?], porzuciÜ ");
	gotoxy(16,16); cprintf("program [ESC], lub przeczytaÜ ten skromny tekst.  ");
	gotoxy(16,17); cprintf("Wi©cej dowiesz si© z samego programu.             ");
	gotoxy(16,18); cprintf("                   Leszek Buczek - czerwiec, 1998.");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	znak = getch();
	goto rozdzielnia;

	petla_6:
	strona = 6;
	gotoxy(16, 7); cprintf("                  "); textcolor(10);
	 cprintf("Coò o programie"); textcolor(8); cprintf("                 ");
	gotoxy(16, 8); cprintf("Jest to pierwsza wersja programu o nazwie 'WYKRES'");
	gotoxy(16, 9); cprintf("W nast©pnej wersji ma si© pojawiÜ:                ");
	gotoxy(16,10); cprintf("1.Poprawa funkcjonalnoòci 'pow()' dla podstawy w  ");
	gotoxy(16,11); cprintf("  liczbach ujemnych,                              ");
	gotoxy(16,12); cprintf("2.MoæliwoòÜ wyboru wi©cej niæ jednej funkcji w tym");
	gotoxy(16,13); cprintf("  samym ukàadzie wsp¢àrz©dnych,                   ");
	gotoxy(16,14); cprintf("3.MoæliwoòÜ lu´nego traktowania skàadni funkcji:  ");
	gotoxy(16,15); cprintf("  a) 'kosinus' lub 'cosinus' przejdzie w 'cos',   ");
	gotoxy(16,16); cprintf("  b) brak nawiasu dla funkcji oznaczaÜ ma pierwsz•");
	gotoxy(16,17); cprintf("     liczb©, znak lub nast. funkcj© jako argument.");
	gotoxy(16,18); cprintf("Dla wykresu figury przestrzennej jest program'XYZ'");
	gotoxy(39,19); cprintf("ƒƒƒƒƒƒƒƒƒƒƒƒƒƒ [Page Up] \b\b\b\b\b");
	znak = getch();

	rozdzielnia:
	if(znak == 0)
	{	if( ( znak_dodatkowy = getch() ) == 81 )	/* strona nast©pna */
		{   if(strona == 1) goto petla_2; else
				if(strona == 2) goto petla_3; else
					if(strona == 3) goto petla_4; else
						if(strona == 4) goto petla_5; else
							if(strona == 5) goto petla_6; else
							{	znak = getch();
								goto rozdzielnia;
							}
		} else
			if( znak_dodatkowy == 73 )		/* strona poprzednia */
			{	if(strona == 2) goto petla_1; else
					if(strona == 3) goto petla_2; else
						if(strona == 4) goto petla_3; else
							if(strona == 5) goto petla_4; else
								if(strona == 6) goto petla_5; else
								{	znak = getch();
									goto rozdzielnia;
								}
			} else
				{	znak = getch();
					goto rozdzielnia;
				}
	} else
		if(znak != 27)
		{	znak = getch();
			goto rozdzielnia;
		} else
			puttext(lewa-7, gora-2, prawa+8, dol+5, buff);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wprowadzenie()							//
//	grafika_wstepu()						//
//	tlo_wykresu_funkcji()						//
//                                                                      //
//			Okno 'pomocy' dla trybu graficznego     	//
//									//
//////////////////////////////////////////////////////////////////////////
void pomoc_gr(void)
{	int pole_pomocy_gr[] = { lewa_gr-30, gora_gr-30, prawa_gr+30, gora_gr-30,
	 prawa_gr+30, dol_gr+30, lewa_gr-30, dol_gr+30, lewa_gr-30, gora_gr-30 };

	setfillstyle(11, 5);
	fillpoly(5, pole_pomocy_gr);
	rectangle(lewa_gr-27, gora_gr-27, prawa_gr+27, dol_gr+27);
	setcolor(13);
	moveto(lewa_gr+110, gora_gr-30);
	settextstyle(8, HORIZ_DIR, 1);
	outtext("POMOC");
	setcolor(9);
	settextstyle(2, HORIZ_DIR, 5);
	moveto(lewa_gr-10, gora_gr);
	outtext("Aby kontynuowac dzialanie programu");
	moveto(lewa_gr-10, gora_gr+15);
	outtext("wystarczy przycisnac dowolny klawisz.");
	moveto(lewa_gr-10, gora_gr+30);
	outtext("Aby porzucic program - przycisnij [Esc].");
	moveto(lewa_gr-10, gora_gr+45);
	outtext("Jezeli masz klopoty z programem,");
	moveto(lewa_gr-10, gora_gr+60);
	outtext("powiadom mnie:");
	setcolor(12);
	settextstyle(7, HORIZ_DIR, 1);
	moveto(lewa_gr, gora_gr+75);
	outtext("Leszek Buczek");
	moveto(lewa_gr, gora_gr+95);
	outtext("2709 Pheasant Hollow Dr.");
	moveto(lewa_gr, gora_gr+115);
	outtext("Plainsboro, NJ 08536");
	settextstyle(2, HORIZ_DIR, 5);
	moveto(lewa_gr, gora_gr+140);
	outtext("tel.: (609)750-0098");
	setcolor(13);
	settextstyle(0, HORIZ_DIR, 1);
	moveto(lewa_gr+280, gora_gr+157);
	outtext("Esc");

	do
	{   znak = getch();
		if(znak == 0) getch();
	} while(znak != 27);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wybory_parametrow()						//
//                                                                      //
//			Ekran graficzny przygotowany pod wykres funkcji	//
//									//
//			wykres_funkcji()		        	//
//			pomoc_gr()					//
//			menu()						//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void tlo_wykresu_funkcji(void)
{	int driver = VGA, mode = VGAHI, errorcode;
	int kwadrat_maksymalny[] = {0, 0, XMAX-1, 0, XMAX-1, YMAX-5, 0, YMAX-5, 0, 0};

/*	driver = DETECT;*/
	initgraph(&driver, &mode, "c:\\TURBOC3\\bgi");  /*  "d:\\tc\\bgi");  */

	errorcode = graphresult();
	if(errorcode != grOk)
	{	printf("\nBà•d grafiki (moduà 'tlo_wykresu_funkcji'): %s\n", grapherrormsg(errorcode));
		printf("Przyciònij dowolny klawisz aby wejòÜ do edytora : ");
		getch();
		exit(1);
	}

	setfillstyle(nr_wzoru_tla, nr_koloru_tla);
	fillpoly(5, kwadrat_maksymalny);
	setcolor(nr_koloru_osi);
	line(10, YMAX/2, XMAX-10, YMAX/2);
	line(XMAX-18, YMAX/2-3, XMAX-10, YMAX/2);
	line(XMAX-18, YMAX/2+3, XMAX-10, YMAX/2);
	line(XMAX/2, YMAX-10, XMAX/2, 10);
	line(XMAX/2-3, 18, XMAX/2, 10);
	line(XMAX/2+3, 18, XMAX/2, 10);

	i = 1;
	while( (XMAX/2+i*dl_jedn_na_osi_OX) <= (XMAX-20) )
	{	line(XMAX/2+i*dl_jedn_na_osi_OX, YMAX/2+2, XMAX/2+i*dl_jedn_na_osi_OX, YMAX/2-2);
		i++;
	}
	i = 1;
	while( (XMAX/2-i*dl_jedn_na_osi_OX) >= 20 )
	{	line(XMAX/2-i*dl_jedn_na_osi_OX, YMAX/2+2, XMAX/2-i*dl_jedn_na_osi_OX, YMAX/2-2);
		i++;
	}
	i = 1;
	while( (YMAX/2-i*dl_jedn_na_osi_OY) >= 20 )
	{	line(XMAX/2-2, YMAX/2-i*dl_jedn_na_osi_OY, XMAX/2+2, YMAX/2-i*dl_jedn_na_osi_OY);
		i++;
	}
	i = 1;
	while( (YMAX/2+i*dl_jedn_na_osi_OY) <= (YMAX-20) )
	{	line(XMAX/2-2, YMAX/2+i*dl_jedn_na_osi_OY, XMAX/2+2, YMAX/2+i*dl_jedn_na_osi_OY);
		i++;
	}

	setcolor(0);
	settextstyle(2, HORIZ_DIR, 4);
	moveto(XMAX/2-8,YMAX/2-2); outtext("o");
	moveto(XMAX/2+dl_jedn_na_osi_OX-2, YMAX/2+2); outtext("1");

	if(dl_jedn_na_osi_OX <= 30)
	{	moveto(XMAX/2+dl_jedn_na_osi_OX*10-5, YMAX/2+2); outtext("10");
		moveto(XMAX/2-dl_jedn_na_osi_OX*10-11, YMAX/2+2); outtext("-10");
		if(dl_jedn_na_osi_OX <= 15)
		{	moveto(XMAX/2+dl_jedn_na_osi_OX*20-5, YMAX/2+2); outtext("20");
			moveto(XMAX/2-dl_jedn_na_osi_OX*20-11, YMAX/2+2); outtext("-20");
			if(dl_jedn_na_osi_OX == 10)
			{	moveto(XMAX/2+dl_jedn_na_osi_OX*30-5, YMAX/2+2); outtext("30");
				moveto(XMAX/2-dl_jedn_na_osi_OX*30-11, YMAX/2+2); outtext("-30");
			}
		}
	}
	if(zmniejszenie_jednostki_OY == 10)
	{	if(dl_jedn_na_osi_OY <= 220)
		{	moveto(XMAX/2-14, YMAX/2-dl_jedn_na_osi_OY-6); outtext("10");
			if(dl_jedn_na_osi_OY <= 22)
			{	moveto(XMAX/2-20, YMAX/2-dl_jedn_na_osi_OY*10-6); outtext("100");
				moveto(XMAX/2-26, YMAX/2+dl_jedn_na_osi_OY*10-6); outtext("-100");
				if(dl_jedn_na_osi_OY <= 11)
				{	moveto(XMAX/2-20, YMAX/2-dl_jedn_na_osi_OY*20-6); outtext("200");
					moveto(XMAX/2-26, YMAX/2+dl_jedn_na_osi_OY*20-6); outtext("-200");
					if(dl_jedn_na_osi_OY <= 7)
					{	moveto(XMAX/2-20, YMAX/2-dl_jedn_na_osi_OY*30-6); outtext("300");
						moveto(XMAX/2-26, YMAX/2+dl_jedn_na_osi_OY*30-6); outtext("-300");
						if(dl_jedn_na_osi_OY == 5)
						{	moveto(XMAX/2-20, YMAX/2-dl_jedn_na_osi_OY*40-6); outtext("400");
							moveto(XMAX/2-26, YMAX/2+dl_jedn_na_osi_OY*40-6); outtext("-400");
						}
					}
				}
			}
		}
	} else
	{	if(dl_jedn_na_osi_OY <= 220)
		{	moveto(XMAX/2-6, YMAX/2-dl_jedn_na_osi_OY-6); outtext("1");
			if(dl_jedn_na_osi_OY <= 22)
			{	moveto(XMAX/2-14, YMAX/2-dl_jedn_na_osi_OY*10-6); outtext("10");
				moveto(XMAX/2-20, YMAX/2+dl_jedn_na_osi_OY*10-6); outtext("-10");
				if(dl_jedn_na_osi_OY <= 11)
				{	moveto(XMAX/2-14, YMAX/2-dl_jedn_na_osi_OY*20-6); outtext("20");
					moveto(XMAX/2-20, YMAX/2+dl_jedn_na_osi_OY*20-6); outtext("-20");
					if(dl_jedn_na_osi_OY <= 7)
					{	moveto(XMAX/2-14, YMAX/2-dl_jedn_na_osi_OY*30-6); outtext("30");
						moveto(XMAX/2-20, YMAX/2+dl_jedn_na_osi_OY*30-6); outtext("-30");
						if(dl_jedn_na_osi_OY == 5)
						{	moveto(XMAX/2-14, YMAX/2-dl_jedn_na_osi_OY*40-6); outtext("40");
							moveto(XMAX/2-20, YMAX/2+dl_jedn_na_osi_OY*40-6); outtext("-40");
						}
					}
				}
			}
		}
	}
	setcolor(6);
	settextstyle(2, HORIZ_DIR, 5);
	moveto(XMAX-10, YMAX/2+1); outtext("X");
	moveto(XMAX/2-10, 2); outtext("Y");

	wykres_funkcji();

	// poniæszy kod dotyczy sytuacji po zrobieniu wykresu
	do
	{	znak = getch();
		if(znak == 0)
		{ // wezwanie_pomocy = 0;
			if(getch() == 59)
			{ // wezwanie_pomocy = 1;
			rozmiar = imagesize(lewa_gr-30, gora_gr-30, prawa_gr+30, dol_gr+30);
			if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
			{	closegraph();
				printf("\nBà•d (5): W pami©ci nie ma miejsca dla przechowania obrazu");
				printf("\nJego rozmiar = %u bajt¢w jest za duæy", rozmiar);
				printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(lewa_gr-30, gora_gr-30, prawa_gr+30, dol_gr+30, ptr_do_alokacji_pamieci);
			pomoc_gr();
			putimage(lewa_gr-30, gora_gr-30, ptr_do_alokacji_pamieci, COPY_PUT);
			farfree(ptr_do_alokacji_pamieci);
			} else break;
		} else
		{	rozmiar = imagesize(lewa_gr, gora_gr, prawa_gr, dol_gr);
			if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
			{	closegraph();
				printf("\nBà•d (6): W pami©ci nie ma miejsca dla przechowania obrazu menu\n");
				printf("\nJego rozmiar = %u bajt¢w jest za duæy", rozmiar);
				printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(lewa_gr-160, gora_gr+200, prawa_gr-220, dol_gr+160, ptr_do_alokacji_pamieci);
			menu();
		}
	} while(1);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	tlo_wykresu_funkcji()						//
//                                                                      //
//	 Wykreòlanie przebiegu funkcji z wczeòniej zadanymi parametrami	//
//									//
//			funkcja_dowolnej_postaci();	        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void wykres_funkcji(void)
{       float granica_rozsadku;
	int m;
	int xx, yy, yy_poprzedni;			/* pozycje na ekranie */
	int punkt_poprzedni, punkt_poprzedni_poprzedni; /* czy w og¢le s• te punkty */
	float y_poprzedni, y_poprzedni_poprzedni; /* rzeczywiste wartoòci poprzednie punkt¢w */
	float skladnik;
	float wartosc_piksela_OX;
	float dl_jedn_na_osi_OY_float; /* wprowadzono aby uniknaÜ zaokr•glenia */
	float test;
	int jest_punkt = 0;	  /* dla detekcji jakiegokolwiek punktu na ekranie */
	int dziedzina_poprzednia;

	/* zeruj iloòÜ miejsc zerowych, ekstrem¢w i liczb zwi•zanych z dziedzin• funkcji */
	l_d = l_m_z = l_e_max = l_e_min = 0;

	if(wielomian)
	{ if(n > 7)
	  {	if(dl_jedn_na_osi_OX < 20) granica_rozsadku = 1e+18;
		else if(dl_jedn_na_osi_OX < 35) granica_rozsadku = 1e+16;
			else if(dl_jedn_na_osi_OX < 50) granica_rozsadku = 1e+14;
				else if(dl_jedn_na_osi_OX < 150) granica_rozsadku = 1e+12;
					else granica_rozsadku = 1e+10;
	  } else
		if(n > 5)
		{	if(dl_jedn_na_osi_OX < 20) granica_rozsadku = 1e+16;
			else if(dl_jedn_na_osi_OX < 35) granica_rozsadku = 1e+14;
				else if(dl_jedn_na_osi_OX < 50) granica_rozsadku = 1e+12;
					else if(dl_jedn_na_osi_OX < 150) granica_rozsadku = 1e+11;
						else granica_rozsadku = 1e+10;
		} else
		  if(n > 3)
		  {	if(dl_jedn_na_osi_OX < 20) granica_rozsadku = 1e+14;
			  else if(dl_jedn_na_osi_OX < 35) granica_rozsadku = 1e+12;
				  else if(dl_jedn_na_osi_OX < 50) granica_rozsadku = 1e+11;
					  else if(dl_jedn_na_osi_OX < 150) granica_rozsadku = 1e+10;
						  else granica_rozsadku = 1e+9;
		  } else
			if(dl_jedn_na_osi_OX < 20) granica_rozsadku = 1e+13;
			  else if(dl_jedn_na_osi_OX < 35) granica_rozsadku = 1e+12;
				  else if(dl_jedn_na_osi_OX < 50) granica_rozsadku = 1e+11;
					  else if(dl_jedn_na_osi_OX < 150) granica_rozsadku = 1e+10;
						  else granica_rozsadku = 1e+9;

	} else		/* dla funkcji dowolnej */
		granica_rozsadku = 1e+18;

	wartosc_piksela_OX = (float)1 / dl_jedn_na_osi_OX;
	dl_jedn_na_osi_OY_float = (float)dl_jedn_na_osi_OY / zmniejszenie_jednostki_OY;

	setcolor(nr_koloru_wykresu);
	jest_problem_z_dziedzina = 0;
	m = 0;
	punkt_poprzedni = punkt_poprzedni_poprzedni = 0;

	do
	{	x = (-310 + m) * wartosc_piksela_OX;
		xx = 10 + m;
		porzuc = 0;					 /* zaàoæenie optymistyczne */
		if(wielomian)
		{	y = skladnik = 0;
			for(l=1; l<n+2; l++)
			{   if(n-l+1 == 0) skladnik = w[l];	 /* aby unikn•Ü "pow(0,0)" */
				else skladnik = w[l] * pow(x, n-l+1);
				y = y + skladnik;
			}
		} else                /* dla funkcji dowolnej */
		  { if(m == 1 && dziedzina)
				d_p[l_d++] = 1234567;	/* wyimaginowana liczba inicjuj•ca */
			if(m>0)
				if(dziedzina) dziedzina_poprzednia = 1;
				else dziedzina_poprzednia = 0;
			if(!jest_funkcja) dziedzina = 1;
			funkcja_dowolnej_postaci();
		  }

/*cz.1*/if(porzuc)
		{   if(m>0)
			{	if(dziedzina_poprzednia && !dziedzina)
					d_k[l_d++] = x-wartosc_piksela_OX;
				else if(!dziedzina_poprzednia && dziedzina)
					d_p[l_d++] = x;
			}
			if(dziedzina) dziedzina_poprzednia = 1;	else dziedzina_poprzednia = 0;
			punkt_poprzedni = punkt_poprzedni_poprzedni = 0; m++; continue;
		}
/*cz.2*/else if(y < -granica_rozsadku || y > granica_rozsadku) /* ignoruj ten punkt */
			 {	if(m>0)
				{	if(dziedzina_poprzednia && !dziedzina)
						d_k[l_d++] = x-wartosc_piksela_OX;
					else if(!dziedzina_poprzednia && dziedzina)
						d_p[l_d++] = x;
				}
				if(dziedzina) dziedzina_poprzednia = 1; else dziedzina_poprzednia = 0;
				porzuc = 1; punkt_poprzedni = punkt_poprzedni_poprzedni = 0;
				dziedzina = 1;
				m++; continue;
			 }
		/* "test" to "yy" typu float */
		test = -(y * dl_jedn_na_osi_OY_float) + YMAX/2;
		/* Jest szansa rysowania tylko gdy byà "punkt poprzedni" */
		if(punkt_poprzedni)
		{	/*sprawd´ czy punkt wykracza poza ekran ale jeszcze istnieje*/
			if( (test < 10) || (test > 470) )
			{	if(test < 10)
				/* teraz punkt jest nad ekranem, niekoniecznie daleko od niego */
				{	if(yy_poprzedni > 10 && yy_poprzedni <= 470)/*przedtem..*/
					 if(punkt_poprzedni_poprzedni)/*..punkt byà na ekranie..*/
/* funkcja rosn•ca */                     if(y_poprzedni > y_poprzedni_poprzedni)/*..lub pod nim*/
					  { line(xx-1, yy_poprzedni, xx, 10); jest_punkt = 1; }
					  else
					  { d_k[l_d++] = x-wartosc_piksela_OX;
						dziedzina = 0;
						punkt_poprzedni = punkt_poprzedni_poprzedni = 0;
					  }
					yy_poprzedni = 10;
				}
				/* teraz punkt jest pod ekranem, niekoniecznie daleko od niego */
				else
				{	if(yy_poprzedni >= 10 && yy_poprzedni < 470)/*przedtem..*/
					 if(punkt_poprzedni_poprzedni)/*..punkt byà na ekranie..*/
/* funkcja malej•ca*/                     if(y_poprzedni < y_poprzedni_poprzedni)/*..lub nad nim*/
					  { line(xx-1, yy_poprzedni, xx, 470); jest_punkt = 1; }
					  else
					  {	d_k[l_d++] = x-wartosc_piksela_OX;
						dziedzina = 0;
						punkt_poprzedni = punkt_poprzedni_poprzedni = 0;
					  }
					yy_poprzedni = 470;
				}
			} else
			{	yy = (int)test;
			/* poprzednio punkt gdzieò byà - niekoniecznie na ekranie...*/
			/* ...ale teraz jest na ekranie	*/
				if(yy >= 10 && yy <= 470)  /* teraz punkt jest na ekranie */
				{	line(xx-1, yy_poprzedni, xx, yy);
					jest_punkt = 1;
					yy_poprzedni = yy;
				}
			}
			if(punkt_poprzedni_poprzedni && l_e_max <= 12 && l_e_min <= 12)
			{ /* poniæej dodaàem znak r¢wnoòci bo dokàadnoòÜ nie jest dobra */
				if( (y_poprzedni_poprzedni <= y_poprzedni) && (y < y_poprzedni) )
				{	l_e_max++;              /* jest maximum funkcji */
					e_max[l_e_max] = y_poprzedni;
					e_max_x[l_e_max] = x - wartosc_piksela_OX;
				} else /* poniæej dodaàem znak r¢wnoòci bo dokàadnoòÜ nie jest dobra */
					if(y_poprzedni_poprzedni >= y_poprzedni && y > y_poprzedni)
					{	l_e_min++;	     /* jest minimum funkcji */
						e_min[l_e_min] = y_poprzedni;
						e_min_x[l_e_min] = x - wartosc_piksela_OX;
					}
			}
			if( (wielomian || (dziedzina && funkcja_dowolna)) && (l_m_z <= 12) &&
			 ((y_poprzedni>0 && y<=0) || (y_poprzedni<0 && y>=0)) )
			{	l_m_z++;        /* jest miejsce zerowe funkcji */
				m_z[l_m_z] = x;	// - wartosc_piksela_OX;
			}
			if(wielomian || (dziedzina && funkcja_dowolna))
			{	punkt_poprzedni_poprzedni = 1;
				y_poprzedni_poprzedni = y_poprzedni;
				y_poprzedni = y;
			}
			m++;
			continue;
		} else
		/* Jeszcze do tej pory nie byào æadnego punktu lub jest to sytuacja po "porzuc" */
		{	if( (l_m_z <= 12) && (y==0) )
			{	l_m_z++;        /* jest miejsce zerowe funkcji */
				m_z[l_m_z] = x;	// - wartosc_piksela_OX;
			}
			punkt_poprzedni = 1;
			yy = (int)test;
			if(yy > 470) yy = 470;
			else if(yy < 10) yy = 10;
			yy_poprzedni = yy;
			punkt_poprzedni_poprzedni = 0;	/* to ma byÜ wiadome */
			// y_poprzedni_poprzedni  - nie istnieje !
			y_poprzedni = y;
			m++;
			// continue;
		}
		if(!wielomian && dziedzina)
			if(m>0 && !dziedzina_poprzednia)
				d_p[l_d++] = x;  //-wartosc_piksela_OX;
	} while(m < 620);

	if(l_d>0 && dziedzina) d_k[l_d] = 7654321; /*wyimaginowana liczba ko‰cz•ca*/
	settextstyle(2, HORIZ_DIR, 6);
	if(!jest_punkt)
	{	if(nr_koloru_tla == 1) setcolor(10); else setcolor(1);
		moveto(24, 450); outtext("Ani jeden punkt wykresu nie pojawià si© "
					 "w widzianym obszarze. ");
	} else if(jest_problem_z_dziedzina)
		   {	if(nr_koloru_tla == 12) setcolor(1); else setcolor(12);
				moveto(20, 450); outtext("Pewien przedziaà wykresu funkcji "
							 "wymaga pàaszczyzny zespolonej.");
		   }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	wykres_funkcji()						//
//                                                                      //
//		     Przebieg oblicze‰ w przypadku wczeòniej wybranej	//
//		     'funkcji dowolnej postaci'				//
//									//
//			dzialania_w_nawiasie_wewn_test();               //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void funkcja_dowolnej_postaci(void)
{		/* Tu nie musz• byÜ funkcje matematyczne ale mog• */
/*******************	PI / 2 == 1.570796310901;   **********************/
//	Tu musi byÜ juæ znana wartoòÜ liczbowa "x" !!!
/*************************************************************************/
	strcpy(C,CF);			/* zapami©taj oryginalny àa‰cuch */
	d_l_C = d_l = d_l_CF;
	dzialania_w_nawiasie_wewn_test();
}

    /*------------------------------------------------------------------*
     *	Jest to funkcja przystosowana do testu z kt¢rego zrezygnowaàem	*
     *		 A[i] zamieniono na C[i], d_l na d_l_C.			*
     *	Jednoczeònie prowadzi ona do oblicze‰ wyraæenia z funkcjami	*
     *	matematycznymi - C, d_l i d_l_C s• teraz z funkcjami.		*
     *------------------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	funkcja_dowolnej_postaci()					//
//                                                                      //
//  Przebieg oblicze‰ wyraæenia w nawiasie lub gdy juæ nie ma nawias¢w	//
//									//
//			oblicz_wartosc_funkcji_matem()          	//
//			usun_tylko_nawiasy()		        	//
//			dzialania_w_nawiasie_wewn()             	//
//			wprowadz_liczbe_do_lancucha()           	//
//			znaleziono_blad()				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void dzialania_w_nawiasie_wewn_test(void)  /* nawias¢w moæe w og¢le nie byÜ */
{	int m;

	jest_przecinek = 0;

	do				   /* aæ do zapisu beznawiasowego */
	{
		nr_nawiasu_otwartego = 0;   poczatek_operacji = 0;
		nr_nawiasu_zamknietego = 0; koniec_operacji = 0;
		if(jest_przecinek == 2)
			jest_przecinek = 0;
		k = 0;

		for(i=0; i<d_l_C; i++)
		{	if(k) break;	/* k!=0 znaczy: byày nawiasy i coò w nich byào */
			dzialanie = 0;	/* to chyba trzeba wrzuciÜ przed "for" */
			if(C[i] == '(')
			{	nr_nawiasu_otwartego++;
				poczatek_operacji = i+1;
			} else
				if(C[i] == ')')
				{	nr_nawiasu_zamknietego++;
					koniec_operacji = i-1;
				/* poszukiwanie przecinka */
				for(m=poczatek_operacji; m<=koniec_operacji; m++)
					if(C[m] == ',')
						if(jest_przecinek == 1)
						{	jest_przecinek = 2;	/* we´ argument po przecinku: mod( ,*) lub pow( ,*) */
							poczatek_operacji = m+1;
							break;	/* chc© aby mi wychodziào z najbardziej wewn©trznej p©tli FOR */
						} else
						{	jest_przecinek = 1;	/* we´ argument przed przecinkiem: mod(*, ) lub pow(*, ) */
							koniec_operacji = m-1;
							j = poczatek_operacji;
							break;  /* chc© aby mi wychodziào z najbardziej wewn©trznej petli FOR, 2 linie niæej! */
						}
					for(m=poczatek_operacji; m<=koniec_operacji; m++)
					{	if(C[m] == '+' || C[m] == '-' || C[m] == '*' ||
						   C[m] == '/')	dzialanie = 1;
						if(m>poczatek_operacji && dzialanie) break;
						if(m==poczatek_operacji && C[m] == '-') dzialanie = 0;
					}
					if(!dzialanie)
				{   if( (C[poczatek_operacji-2] > 96 &&
					 C[poczatek_operacji-2] < 123 &&
					 C[poczatek_operacji-2] != 120 ) ||
					 C[poczatek_operacji-1] == ',' )
					{   operacje_na_funkcji = 1;
						k = 0;
						for(i=poczatek_operacji; i<=koniec_operacji; i++)
							D[k++] = C[i];
						D[k++] = '\0';
						d_l_D = k;  /*to jest chyba nigdzie nie uæywane*/
						if(!jest_przecinek && !porzuc)
							oblicz_wartosc_funkcji_matem();
						else
						{	if(jest_przecinek == 1) strcpy(D1,D);
							else if(jest_przecinek == 2 && !porzuc)
						oblicz_wartosc_funkcji_matem();
						operacje_na_funkcji = 0;
							}
					} else
						if(jest_przecinek != 1)
							{   operacje_na_funkcji = 0;
								usun_tylko_nawiasy();
							}
						break; /* WYCHODZI Z P®TLI "FOR" A ZARAZEM Z P®TLI "WHILE"*/
					}
					if(porzuc) break;
					k = 0;
					if(nr_nawiasu_otwartego != 0)
					{	for(i=poczatek_operacji; i<=koniec_operacji; i++)
							D[k++] = C[i];
						D[k++] = '\0';
						d_l_D = k;	  /* to jest chyba nigdzie nie uæywane */
						strcpy(A, D);
						dzialania_w_nawiasie_wewn();
						if(porzuc) break;
						wprowadz_liczbe_do_lancucha();
					} else
						{   blad = 1;
							znaleziono_blad();
						}
				}
		} /* koniec p©tli "for" */
	} while( (nr_nawiasu_otwartego != 0 || i != d_l_C) && !porzuc );

	/* tu nie ma juæ æadnych nawias¢w */
	if(!porzuc)
	{	for(m=0; m<d_l_C; m++)
		{	if(C[m] == '+' || C[m] == '-' || C[m] == '*' || C[m] == '/')
				dzialanie = 1;
			if(m>0 && dzialanie) break;
			if(m==0 && C[m] == '-') dzialanie = 0;
		}
		strcpy(A, C);
		if(dzialanie)
			dzialania_w_nawiasie_wewn();
		if(!dzialanie)
		{	if(strcmp(&A[0],"x") == 0) y = x;
			else
				if(strcmp(&A[0],"-x") == 0) y = -x;
				else
				{	ptrA = A;
					y = atof(ptrA);
				}
		}
	}
}

    /*----------------------------------------------------------*
     *	Ten moduà dla funkcji matematycznych wchodzi w miejsce	*
     *	"usun_tylko_nawiasy" dla operacji bez funkcji.		*
     *----------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dzialania_w_nawiasie_wewn_test()				//
//                                                                      //
//		 Obliczenie wartoòci pojedynczej funkcji matematycznej	//
//				    ( szwankuje pow(ujemna, dowolna) )	//
//									//
//			czy_brak_obliczen()		        	//
//                      znaleziono_blad()				//
//			wprowadz_liczbe_do_lancucha()           	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void oblicz_wartosc_funkcji_matem(void)
{   int m, mm;		  /* w tym wypadku jest to dàugoòÜ nazwy funkcji matematycznej */
	int b_o = 0;	  /* "brak_obliczen" przej©te od "czy_brak_obliczen()" */

  if(jest_przecinek)		/* mod(y1,y) lub pow(y1,y) */
  {	poczatek_operacji = j;	/* mod(D1,D) lub pow(D1,D) */
	if(strcmp(&D1[0],"x") == 0) y1 = x;
	else if(strcmp(&D1[0],"-x") == 0) y1 = -x;
		 else { ptrD1 = D1; y1 = atof(ptrD1); }
	if(strcmp(&D[0],"x") == 0) y = x;
	else if(strcmp(&D[0],"-x") == 0) y = -x;
		else { ptrD = D; y = atof(ptrD); }
	if( jest_mod && (C[poczatek_operacji-2] == 'd' &&
		C[poczatek_operacji-3] == 'o' && C[poczatek_operacji-4] == 'm') )
	{	mm = 3;
		// w tym miejscu moæe byÜ problem z dziedzin• funkcji
		y = fmod(y1,y);
		dziedzina = 1;
	} else
	if( jest_pow && (C[poczatek_operacji-2] == 'w' &&
		C[poczatek_operacji-3] == 'o' && C[poczatek_operacji-4] == 'p') )
	{	mm = 3;
		if(y1 == 0 && y == 0) { b_o = 1; dziedzina = 0; }
		else if(y1 < 0) { b_o = 1; jest_problem_z_dziedzina = 1; }// dziedzina = 1; }
			 else { b_o = czy_brak_obliczen(); dziedzina = 1; }
		if(b_o)
			porzuc = 1;	//wynik pot©gowania jest zbyt wysoki (ograniczenie programowe)
		else { y = pow(y1,y); dziedzina = 1; }
	} else
	{ // Powinna byÜ jakaò funkcja a okazaào si© æe jej nie ma
		blad = 2;
		znaleziono_blad();
	}
  } else
  {	if(strcmp(&D[0],"x") == 0)
		y = x;
	else
	{	ptrD = D;
		y = atof(ptrD);
	}
	if( jest_ln && (C[poczatek_operacji-2] == 'n' &&
		C[poczatek_operacji-3] == 'l') )
	{	mm = 2;
		if(y <= 0)
		{	porzuc = 1; dziedzina = 0; } // Logarytm naturalny liczby <= 0
		else { y = log(y); dziedzina = 1; }
	} else
	if( jest_lg && (C[poczatek_operacji-2] == 'g' &&
		C[poczatek_operacji-3] == 'l') )
	{	mm = 2;
		if(y <= 0)
		{	porzuc = 1; dziedzina = 0; } // Logarytm dziesi©tny liczby <= 0
		else { y = log10(y); dziedzina = 1; }
	} else
	if( jest_cos && (C[poczatek_operacji-2] == 's' &&
		C[poczatek_operacji-3] == 'o' && C[poczatek_operacji-4] == 'c') )
	{	mm = 3;
		y = cos(y);
		dziedzina = 1;
	} else
	if( jest_acos && (C[poczatek_operacji-2] == 's' &&
		C[poczatek_operacji-3] == 'o' && C[poczatek_operacji-4] == 'c' &&
		C[poczatek_operacji-5] == 'a') )
	{	mm = 4;
		if(y < -1 || y > 1)
		{	porzuc = 1; dziedzina = 0; } // Arcus cosinus liczby < -1 lub > 1
		else { y = acos(y); dziedzina = 1; }
	} else
	if( jest_cosh && (C[poczatek_operacji-2] == 'h' &&
		C[poczatek_operacji-3] == 's' && C[poczatek_operacji-4] == 'o' &&
		C[poczatek_operacji-5] == 'c') )
	{	mm = 4;
		dziedzina = 1;
		if(y < -35 || y > 35)
			porzuc = 1; // Cosinus hiperboliczny liczby < -35 lub > 35 (ograniczenie programowe)
		else y = cosh(y);
	} else
	if( jest_sin && (C[poczatek_operacji-2] == 'n' &&
		C[poczatek_operacji-3] == 'i' && C[poczatek_operacji-4] == 's') )
	{	mm = 3;
		y = sin(y);
		dziedzina = 1;
	} else
	if( jest_asin && (C[poczatek_operacji-2] == 'n' &&
		C[poczatek_operacji-3] == 'i' && C[poczatek_operacji-4] == 's' &&
		C[poczatek_operacji-5] == 'a') )
	{	mm = 4;
		if(y < -1 || y > 1)
		{	porzuc = 1; dziedzina = 0; } // Arcus sinus liczby < -1 lub > 1
		else { y = asin(y); dziedzina = 1; }
	} else
	if( jest_sinh && (C[poczatek_operacji-2] == 'h' &&
		C[poczatek_operacji-3] == 'n' && C[poczatek_operacji-4] == 'i' &&
		C[poczatek_operacji-5] == 's') )
	{	mm = 4;
		dziedzina = 1;
		if(y < -35 || y > 35)
			porzuc = 1; // Sinus hiperboliczny liczby < -35 lub > 35 (ograniczenie programowe)
		else y = sinh(y);
	} else
	if( jest_tan && (C[poczatek_operacji-2] == 'n' &&
		C[poczatek_operacji-3] == 'a' && C[poczatek_operacji-4] == 't') )
	{	mm = 3;
		y = tan(y);
		dziedzina = 1;
	} else
	if( jest_atan && (C[poczatek_operacji-2] == 'n' &&
		C[poczatek_operacji-3] == 'a' && C[poczatek_operacji-4] == 't' &&
		C[poczatek_operacji-5] == 'a') )
	{	mm = 4;
		y = atan(y);
		dziedzina = 1;
	} else
	if( jest_tanh && (C[poczatek_operacji-2] == 'h' &&
		C[poczatek_operacji-3] == 'n' && C[poczatek_operacji-4] == 'a' &&
		C[poczatek_operacji-5] == 't') )
	{	mm = 4;
		/* tu nie ma ogranicze‰ z tym, æe dla
		 *	 	x<=-10		tanh(x)=-1
		 *		x>= 10		tanh(x)= 1
		 */
		y = tanh(y);
		dziedzina = 1;
	} else
	if( jest_abs && (C[poczatek_operacji-2] == 's' &&
		C[poczatek_operacji-3] == 'b' && C[poczatek_operacji-4] == 'a') )
	{	mm = 3;
		y = fabs(y);
		dziedzina = 1;
	} else
	if( jest_exp && (C[poczatek_operacji-2] == 'p' &&
		C[poczatek_operacji-3] == 'x' && C[poczatek_operacji-4] == 'e') )
	{	mm = 3;
		dziedzina = 1;
		if(y > 34)
			porzuc = 1; // Wykàadnik liczby "e" > 34 (ograniczenie programowe)
		else y = exp(y);
	} else
	if( jest_sq && (C[poczatek_operacji-2] == 'q' &&
		C[poczatek_operacji-3] == 's') )
	{	mm = 2;
		if(y < 0)
		{	porzuc = 1; dziedzina = 0; } // Pierwiastek kwadratowy liczby < 0.0
		else { y = sqrt(y); dziedzina = 1; }
	} else
	  { // Powinna byÜ jakaò funkcja a okazaào si©, æe jej nie ma
		blad = 2;
		znaleziono_blad();
	  }
  }
  if(!porzuc)
  {	wprowadz_liczbe_do_lancucha();
	for(i=0; i<mm; i++)	 /* zlikwiduj nazw© funkcji przed jej nawiasami */
	{	for(m=poczatek_operacji-1-mm; m<=d_l_C; m++)
			C[m] = C[m+1];
		d_l_C--;
	}
  }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	oblicz_wartosc_funkcji_matem()					//
//                                                                      //
//		   Przesiew wielkoòci za duæych dla obliczenia pow()	//
//			 (UWAGA: usuni©to warunki dla podstawy ujemnej)	//
//									//
//////////////////////////////////////////////////////////////////////////
int czy_brak_obliczen(void)
{	int brak_obliczen = 0;
	if(y1>=1000000000) brak_obliczen=1;	else
	 if(y1>=100000000) { if(y<-1 || y>=2) brak_obliczen=1; } else
	  if(y1>=1000000) { if(y<-1.2 || y>=2.5) brak_obliczen=1; } else
	   if(y1>=100000) { if(y<-1.5 || y>=3) brak_obliczen=1; } else
		if(y1>=10000) { if(y<-1.8 || y>=3.5) brak_obliczen=1; } else
		 if(y1>=1000) { if(y<-2.1 || y>=5) brak_obliczen=1; } else
		  if(y1>=100) { if(y<-3 || y>=7) brak_obliczen=1; } else
		   if(y1>=10) { if(y<-4.5 || y>=15) brak_obliczen=1; } else
			if(y1>=1) { if(y<-9 || y>=20) brak_obliczen=1; } else
			 if(y1>=0.1) { if(y<-15 || y>=10) brak_obliczen=1; } else
			  if(y1>=0.01) { if(y<-7 || y>=5) brak_obliczen=1; } else
			   if(y1>=0.001) { if(y<-5 || y>=3) brak_obliczen=1; } else
				if(y1>=0.0001) { if(y<-3.7 || y>=2.2) brak_obliczen=1; } else
				 if(y1>=0.00001) { if(y<-2.9 || y>=1.8) brak_obliczen=1; } else
				  if(y1>=0.000001) { if(y<-2.5 || y>=1.5) brak_obliczen=1; } else
				   if(y1>=0.0000001) { if(y<-2.1 || y>=1.2) brak_obliczen=1; } else
					if(y1<0.0000001) brak_obliczen=1;
	return brak_obliczen;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dzialania_w_nawiasie_wewn_test()				//
//	oblicz_wartosc_funkcji_matem()					//
//                                                                      //
//   Otrzymana wartoòÜ liczbowa zostaje zamieniona na wartoòÜ znakow•	//
//   i wstawiona do àa‰cucha						//
//									//
//////////////////////////////////////////////////////////////////////////
void wprowadz_liczbe_do_lancucha(void)
{	int m, mm;
	char *ptr_y;
	int dec, sign, ndig = 20; /* ndig -> dàugoòÜ liczby bez kropki i znaku */
				  /* dec -> pozycja kropki (zawsze do wstawienia!) */
				/* sign -> znak liczby. Do wstawienia tylko gdy "sign = 1"...*/
				/*...(liczba ujemna) i b©dzie to "-" zaraz na pocz•tku ale...*/
				/*..."-" nie wstawiaj gdy wyjdzie 0.0000000		     */

	/* 1. wprowad´ liczb© do àa‰cucha:	*/
	/*    a. zamie‰ otrzyman• liczb© na àa‰cuch */
	ptr_y = ecvt(y, ndig, &dec, &sign);
	ptr_y[ndig] = '\0';  // ptr_y - wartoòÜ przed obci©ciem

	mm = 0;
	if(dec > 0)
	{	for(i=ndig; i>=dec; i--) ptr_y[i+1] = ptr_y[i];
		ptr_y[++i] ='.';
		ndig++;
		if(ndig - i > 8)
			for(m=ndig; m>i+8; m--) ptr_y[m-1] = ptr_y[m];
		// ptr_y - po obci©ciu
	} else
	{   i = 0;
		while(i < -dec)
		{	for(m=ndig; m>=0; m--) ptr_y[m+1] = ptr_y[m];
			ptr_y[0] = '0';
			i++;
			ndig++;
		}
		for(m=ndig; m>=0; m--) ptr_y[m+2] = ptr_y[m];
		ptr_y[0] = '0';
		ptr_y[1] = '.';
		for(m=ndig+2; m>9; m--) ptr_y[m-1] = ptr_y[m];
		// ptr_y(po obci©ciu - liczba < 1)
	}
	if(sign)
		if(dec > -7)
		{	d_l = strlen(ptr_y);
			for(m=d_l; m>=0; m--) ptr_y[m+1] = ptr_y[m];
			ptr_y[0] = '-';
		}

	/*    b. znajd´ dàugoòÜ tego juæ - nie liczby lecz - àa‰cucha */
	d_l = strlen(ptr_y);

	/*    c. zlikwiduj zawartoòÜ podàa‰cucha poddanego */
	/*       wczeòniejszej operacji w àa‰cuchu "C" */
	for(i=0; i<=(koniec_operacji-poczatek_operacji); i++)
	{	for(m=poczatek_operacji; m<=d_l_C; m++)
			C[m] = C[m+1];
		d_l_C--;
	}

	/*    d. wstaw wynikowy àa‰cuch "ptr_y" do àa‰cucha "C" */
	mm = 0;
	for(i=poczatek_operacji; i<poczatek_operacji+d_l; i++)
	{	for(m=d_l_C; m>=poczatek_operacji+mm; m--)
			C[m+1] = C[m];
		d_l_C++;
		C[i] = ptr_y[mm++];
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dzialania_w_nawiasie_wewn_test()				//
//                                                                      //
//   W nawiasach jest tylko liczba lub 'x' wi©c usuni©te zostaj• tylko	//
//   nawiasy								//
//									//
//////////////////////////////////////////////////////////////////////////
void usun_tylko_nawiasy(void)
{       int m;

	for(m=poczatek_operacji-1; m<=d_l_C; m++) C[m] = C[m+1];
	d_l_C--;		/* "koniec_operacji" przesunie si© o 1 miejsce do przodu */
	for(m=koniec_operacji; m<=d_l_C; m++) C[m] = C[m+1];
	d_l_C--;
	// tu àa‰cuch "C" jest po usuni©ciu nawias¢w
	nr_nawiasu_otwartego--;
	nr_nawiasu_zamknietego--;
}

   /********************************************************************
    *------------------------------------------------------------------*
    *		      	    Proces obliczeniowy			       *
    *------------------------------------------------------------------*
    ********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dzialania_w_nawiasie_wewn_test()				//
//                                                                      //
//	 Obliczenia pomi©dzy liczbami wsr¢d kt¢rych moæe byÜ symbol 'x'	//
//    (tu nie ma nawias¢w a wi©c i funkcji; dziaàaniami s• +, -, * i /)	//
//									//
//			wynik_prostego_dzialania (aa, bb)       	//
//			znaleziono_blad()				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void dzialania_w_nawiasie_wewn(void)
{       d_l = strlen(A);
	wskaznik=0;

	while(d_l)	    /* aæ dàugoòÜ àa‰cucha zmniejszy si© do zera */
	{   if(wskaznik >2)
		{	aa = wynik_prostego_dzialania (aa, bb);
			wskaznik=1;
		} else
		{	zmniejsz_d_l = 0;
			wskaznik++;
			ptrA = A;
			if(atof(ptrA) == 0 && A[0] == 'x')   /* jeæeli jest to "x"... */
			{	jest_x = 1;
				zmniejsz_d_l++;
				if(wskaznik == 1) aa = x; else if(wskaznik == 3) bb = x;
				for(k=0; k<d_l; k++) A[k] = A[k+1];
/*******************************************************************/
			} else
				if(atof(ptrA) == 0 && A[0] == '-' && A[1] == 'x' && wskaznik == 1)
				{	jest_x = 1;
					if(wskaznik == 1) aa = -x; else if(wskaznik == 3) bb = -x;
					for(i=0; i<2; i++)
					{	zmniejsz_d_l++;
						for(k=0; k<d_l; k++) A[k] = A[k+1];
					}
/*******************************************************************/
			} else
				if(atof(ptrA) == 0 && wskaznik != 2 )
				{	if(wskaznik == 1) aa = 0; else bb = 0;
					do
					{   for(k=0; k<d_l; k++) A[k] = A[k+1];
						zmniejsz_d_l++;
					    // Tu miaà usuwaÜ 0 lub 0.00 lub -0.00 itp
					} while( A[0] == 46 || A[0] == 48 );
				} else
					if(atof(ptrA) != 0 && wskaznik != 2) /*...a jeæeli jest to liczba...*/
					{	a = atof(ptrA);
						if(wskaznik == 1) aa = a; else bb = a;
						do
						{   for(k=0; k<d_l; k++) A[k] = A[k+1];
							zmniejsz_d_l++;
						} while( A[0] == 46 || (A[0] >= 48 && A[0] <= 57) );
					} else	/*...a ostatecznie jest to znak dziaàania... */
						if(wskaznik == 2)
						{ if(A[0] == '+') dodawanie = 1; else
						   if(A[0] == '-') odejmowanie = 1; else
							if(A[0] == '*') mnozenie = 1; else
							 if(A[0] == '/') dzielenie = 1; else
							  { blad = 3;
								znaleziono_blad();
							  }
						  zmniejsz_d_l++;
						  for(k=0; k<d_l; k++) A[k] = A[k+1];
						}
		d_l = d_l - zmniejsz_d_l;
		}
	}	/* koniec gà¢wnej p©tli "while" */

	wynik_prostego_dzialania (aa, bb);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dzialania_w_nawiasie_wewn()					//
//                                                                      //
//   Obliczenia pomi©dzy liczbami wsr¢d kt¢rych moæe byÜ symbol 'x'	//
//   (tu nie ma nawias¢w a wi©c i funkcji; dziaàaniami s• +, -, * i /)	//
//									//
//			znaleziono_blad()				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
float wynik_prostego_dzialania(float aa, float bb)
{	if(dodawanie) yy = aa + bb; else
	 if(odejmowanie) yy = aa - bb; else
	  if(mnozenie) yy = aa * bb; else
	   if(dzielenie)
	   {    if(bb == 0)
			{	porzuc = 1; dziedzina = 0; }
			else
				yy = aa / bb;
		} else
		{   blad = 4;
			znaleziono_blad();
		}

	y = yy;
	dodawanie = odejmowanie = mnozenie = dzielenie = 0;

	return y;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	tlo_wykresu_funkcji()						//
//                                                                      //
//		Menu dla 4-ch wielkosci:  1. Analiza funkcji		//
//					  2. Zmiana opcji		//
//					  3. Inny wykres		//
//					  4. Porzucenie programu	//
//				(to stan po zrobieniu wykresu funkcji)	//
//									//
//			analiza_funkcji()				//
//			wybory_parametrow()		        	//
//			wybieranie_postaci_funkcji()            	//
//			czy_porzucic_program_gr()	        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void menu(void)
{       int m, mm, mmm=1;
	char m_ch1, m_ch2;
	int ilosc_skokow = 0;
	int pole_menu[] = { lewa_gr-160, gora_gr+200, prawa_gr-220, gora_gr+200,
			    prawa_gr-220, dol_gr+160, lewa_gr-160, dol_gr+160,
			    lewa_gr-160, gora_gr+200 };

	setfillstyle(6, 7);	/* moæna 7 zamieniÜ na 8 - b©dzie delikatniejszy */
	fillpoly(5, pole_menu);
	setcolor(14);
	moveto(lewa_gr-140, gora_gr+210);
	settextstyle(2, HORIZ_DIR, 6);
	outtext("Analiza funkcji");
	moveto(lewa_gr-140, gora_gr+230);
	outtext("Zmiana opcji");
	moveto(lewa_gr-140, gora_gr+250);
	outtext("Inny wykres");
	moveto(lewa_gr-140, gora_gr+270);
	outtext("Porzucenie programu");

	do
	{   mm = fmod(ilosc_skokow+20, 4);
		if(mm == 0)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )  /* zdefiniowane w getch(): #define KEY_DOWN  80  */
					{	if( (m_ch2 = getch()) == 80 ) { ilosc_skokow++; break; }
						else                  /* zdefiniowane w getch(): #define KEY_UP  72  */
							if( m_ch2 == 72 ) { ilosc_skokow--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { ilosc_skokow++; break; }
					}
					setcolor(13); moveto(lewa_gr-140, gora_gr+210);
					outtext("Analiza funkcji");
					delay(100);
					setcolor(14); moveto(lewa_gr-140, gora_gr+210);
					outtext("Analiza funkcji");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		if(mm == 1)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{	if( (m_ch2 = getch()) == 80 ) { ilosc_skokow++; break; }
						else                      /* 72 strzaàka w g¢r© */
							if( m_ch2 == 72 ) { ilosc_skokow--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { ilosc_skokow++; break; }
					}
					setcolor(13); moveto(lewa_gr-140, gora_gr+230);
					outtext("Zmiana opcji");
					delay(100);
					setcolor(14); moveto(lewa_gr-140, gora_gr+230);
					outtext("Zmiana opcji");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		if(mm == 2)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{	if( (m_ch2 = getch()) == 80 ) { ilosc_skokow++; break; }
						else                      /* 72 strzaàka w g¢r© */
							if( m_ch2 == 72 ) { ilosc_skokow--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { ilosc_skokow++; break; }
					}
					setcolor(13); moveto(lewa_gr-140, gora_gr+250);
					outtext("Inny wykres");
					delay(100);
					setcolor(14); moveto(lewa_gr-140, gora_gr+250);
					outtext("Inny wykres");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		if(mm == 3)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{	if( (m_ch2 = getch()) == 80 ) { ilosc_skokow++; break; }
						else                      /* 72 strzaàka w g¢r© */
							if( m_ch2 == 72 ) { ilosc_skokow--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { ilosc_skokow++; break; }
					}
					setcolor(13); moveto(lewa_gr-140, gora_gr+270);
					outtext("Porzucenie programu");
					delay(100);
					setcolor(14); moveto(lewa_gr-140, gora_gr+270);
					outtext("Porzucenie programu");
					delay(100);
					if(m > 8) m = 0;
			}
		}
	if(ilosc_skokow == 40) ilosc_skokow = 20;
	else
		if(ilosc_skokow == 0) ilosc_skokow = 20;
	} while(mmm);

	if(mm == 0)
	{	putimage(lewa_gr-160, gora_gr+200, ptr_do_alokacji_pamieci, COPY_PUT);
		farfree(ptr_do_alokacji_pamieci);
		proba_porzucenia = 1;	// zapewne zb©dne
		rozmiar = imagesize(lewa_gr-30, gora_gr-60, prawa_gr+30, dol_gr+60);
		if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
		{	closegraph();
			printf("\nBà•d (7): W pami©ci nie ma miejsca dla przechowania obrazu");
			printf("\nJego rozmiar = %u bajt¢w jest za duæy", rozmiar);
			printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
			getch();
			exit(1);
		}
		getimage(lewa_gr-30, gora_gr-60, prawa_gr+30, dol_gr+60, ptr_do_alokacji_pamieci);
		analiza_funkcji();

		putimage(lewa_gr-30, gora_gr-60, ptr_do_alokacji_pamieci, COPY_PUT);
		farfree(ptr_do_alokacji_pamieci);
	} else
	if(mm == 1)
	{       putimage(lewa_gr-160, gora_gr+200, ptr_do_alokacji_pamieci, COPY_PUT);
		farfree(ptr_do_alokacji_pamieci);
		closegraph(); opcja = 1; wybory_parametrow();
	} else
	if(mm == 2)
	{	putimage(lewa_gr-160, gora_gr+200, ptr_do_alokacji_pamieci, COPY_PUT);
		farfree(ptr_do_alokacji_pamieci);
		closegraph(); opcja = 0; wybieranie_postaci_funkcji();
	} else
	if(mm == 3)
	{	putimage(lewa_gr-160, gora_gr+200, ptr_do_alokacji_pamieci, COPY_PUT);
		farfree(ptr_do_alokacji_pamieci);
		proba_porzucenia = 1;
		rozmiar = imagesize(lewa_gr, gora_gr, prawa_gr, dol_gr);
		if( (ptr_do_alokacji_pamieci = farmalloc(rozmiar) ) == NULL)
		{	closegraph();
			printf("\nBà•d (8): W pami©ci nie ma miejsca dla przechowania obrazu");
			printf("\nJego rozmiar = %u bajt¢w jest za duæy", rozmiar);
			printf("\nWolnej pami©ci jest tylko %u bajt¢w\n", coreleft() );
			getch();
			exit(1);
		}
		getimage(lewa_gr, gora_gr, prawa_gr, dol_gr, ptr_do_alokacji_pamieci);
		czy_porzucic_program_gr();
		putimage(lewa_gr, gora_gr, ptr_do_alokacji_pamieci, COPY_PUT);
		farfree(ptr_do_alokacji_pamieci);
	} else
	if(mm == 4)
	{	putimage(lewa_gr-160, gora_gr+200, ptr_do_alokacji_pamieci, COPY_PUT);
		farfree(ptr_do_alokacji_pamieci);
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	menu()								//
//                                                                      //
//	  Analiza wykresu funkcji w trzech obrazach:	        	//
//	    1. Dziedzina funkcji,					//
//	    2. Miejsca zerowe funkcji,					//
//	    3. Ekstrema funkcji (wyszczeg¢lnione s• najpierw maksima).	//
//									//
//			okno_analizy_funkcji()		        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void analiza_funkcji(void)
{	int m, mm, mmm=1;
	char m_ch1, m_ch2;
	int ilosc_skokow = 0;

	do
	{   mm = fmod(ilosc_skokow, 3);
		if(mm == 0)
		{   okno_analizy_funkcji();
			setcolor(9);
			moveto(lewa_gr+73, gora_gr-42);
			settextstyle(7, HORIZ_DIR, 1);
			outtext("Dziedzina funkcji");
			if(wielomian)
			{	gotoxy(23,9); printf("X = ");
				printf("(-Æ;+Ø)");
			}
			else
			{	if(l_d)
				{	gotoxy(23,9); printf("X = ");
					if(d_p[0]==1234567) printf("(?;");
					else printf("(%.2f;", d_p[0]);
					for(m=1; m<=l_d; m++)
					{   if( !fmod(m,4) ) gotoxy(25,9+m/4);
						if( m > 27 )
						{	gotoxy(35,16); printf("...i wi©cej."); break; }
						else
						{	if( fmod(m,2) )
							{	if(d_k[m] == 7654321) printf("?)");
								else printf("%.2f)", d_k[m]);
							}
							else
							if(l_d!=m) printf(" v (%.2f;", d_p[m]);
						}
					}
					gotoxy(22,17); printf("Uwaga: '(' moæe okazaÜ si© byÜ '['");
					gotoxy(22,18); printf("a ')' ']'. Pytajnik oznacza æe wykres");
					gotoxy(22,19); printf("zaczyna si© lub ko‰czy liczb• juæ");
					gotoxy(22,20); printf("naleæ•c• do dziedziny funkcji.");
				} else
				{	gotoxy(24,10); printf("Nie odkryàem punkt¢w wykresu");
					gotoxy(24,11); printf("naleæ•cych do dziedziny funkcji");
					gotoxy(24,12); printf("w zakresie osi rz©dnych widzianych");
					gotoxy(24,13); printf("na ekranie monitora.");
				}
			}
			setcolor(2);
			moveto(lewa_gr+180, gora_gr+185);
			settextstyle(0, HORIZ_DIR, 1);
			outtext("Page Down / Esc");
			if( (m_ch1 = getch()) == 0 )    /* 81 - PgDn */
			{	if( (m_ch2 = getch()) == 81 ) ilosc_skokow++; }
			else
				if(m_ch1 == 27)	mmm = 0;
		} else
		if(mm == 1)
		{   okno_analizy_funkcji();
			setcolor(14);
			moveto(lewa_gr+53, gora_gr-42);
			settextstyle(7, HORIZ_DIR, 1);
			outtext("Miejsca zerowe funkcji"); // to tylko przykàad - b©dzie tablica
			if(l_m_z == 0)
			{	gotoxy(23, 9); printf("W zakresie widzianym na ekranie");
				gotoxy(23,10); printf(" nie wykryàem miejsc zerowych.");
			} else
				for(m=1; m<=l_m_z; m++)
				{   if(m > 11)
					{	gotoxy(35,20);
						printf("... i wi©cej.");
						break;
					} else
					{	gotoxy(28, 8+m);
						if(m>9) printf("y = 0   dla   X%d= %7.2f", m, m_z[m]);
						else printf("y = 0   dla   X%d = %7.2f", m, m_z[m]);
					}
				}
			setcolor(2);
			moveto(lewa_gr+100, gora_gr+185);
			settextstyle(0, HORIZ_DIR, 1);
			outtext("Page Down / Page Up / Esc");
			if( (m_ch1 = getch()) == 0 )    /* 81 - PgDn */
			{	if( (m_ch2 = getch()) == 81 ) ilosc_skokow++;
				else               			/* 73 PgUp */
					if( m_ch2 == 73 ) ilosc_skokow--;
			}
			else
				if(m_ch1 == 27)	mmm = 0;
		} else
		if(mm == 2)
		{   okno_analizy_funkcji();
			setcolor(15);
			moveto(lewa_gr+77, gora_gr-42);
			settextstyle(7, HORIZ_DIR, 1);
			outtext("Ekstrema funkcji");
			if(l_e_max == 0 && l_e_min == 0)
			{	gotoxy(23, 9); printf("W zakresie widzianym na ekranie");
				gotoxy(23,10); printf("nie wykryàem miejsc ekstremalnych.");
			} else
			{	if(l_e_max)
					for(m=1; m<=l_e_max; m++)
					{   if(m > 11)
						{	gotoxy(35,20);
							printf("... i wi©cej");
							break;
						}
						else
						{	gotoxy(23, 8+m);
							printf("Max:   y = %7.2f  dla  X = %7.2f", e_max[m], e_max_x[m]);
						}
					}
				if(l_e_min)
					for(m=1; m<=l_e_min; m++)
					{   if(m > 11 || l_e_max+m > 11)
						{	gotoxy(35,20);
							printf("... i wi©cej");
							break;
						}
						else
						{	gotoxy(24, 8+l_e_max+m);
							printf("Min:  y = %7.2f  dla  X = %7.2f", e_min[m], e_min_x[m]);
						}
					}
			}
			setcolor(2);
			moveto(lewa_gr+196, gora_gr+185);
			settextstyle(0, HORIZ_DIR, 1);
			outtext("Page Up / Esc");
			if( (m_ch1 = getch()) == 0 )
			{	if( (m_ch2 = getch()) == 73 ) ilosc_skokow--; }
			else
				if(m_ch1 == 27)	mmm = 0;
		}
	} while(mmm);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	analiza_funkcji()						//
//                                                                      //
//		Okno jednolite dla wszystkich trzech opracowa‰:		//
//			1. Dziedziny funkcji,				//
//			2. Miejsc zerowych funkcji,			//
//			3. Ekstrem funkcji.				//
//									//
//////////////////////////////////////////////////////////////////////////
void okno_analizy_funkcji(void)
{	int pole_analizy_funkcji[] = { lewa_gr-30, gora_gr-60, prawa_gr+30,
			gora_gr-60, prawa_gr+30, dol_gr+60, lewa_gr-30, dol_gr+60,
			lewa_gr-30, gora_gr-60 };

	setfillstyle(8, 8);
	fillpoly(5, pole_analizy_funkcji);
	rectangle(lewa_gr-27, gora_gr-57, prawa_gr+27, dol_gr+57);
	setcolor(11);
	moveto(lewa_gr+82, gora_gr-50);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("ANALIZA FUNKCJI");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	dzialania_w_nawiasie_wewn_test()		        	//
//	oblicz_wartosc_funkcji_matem()					//
//	dzialania_w_nawiasie_wewn()					//
//	wynik_prostego_dzialania (float aa, float bb)			//
//                                                                      //
//	Awaryjne wyjòcie z sytuacji gdy pojawi si© nieprzewidziany bà•d	//
//				(moæliwe æe przy przesyàaniu danych)	//
//	Praktycznie nie powinno mieÜ miejsca sygnalizowanie tego raportu//
//	Bà•d pojawi si© w jednym z 4-ch przypadk¢w:			//
//		1. problem z nawiasami,					//
//		2. brak spodziewanej funkcji lub nie znalezienie jej,   //
//		3. brak spodziewanego dziaàania pomi©dzy liczbami,	//
//		4. problem z symbolami dziaàania.			//
//									//
//			wybieranie_postaci_funkcji();           	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void znaleziono_blad(void)
{       int pole_bledu[] = { lewa_gr-40, gora_gr, prawa_gr+40, gora_gr,
	 prawa_gr+40, dol_gr, lewa_gr-40, dol_gr, lewa_gr-40, gora_gr };

	if(nr_koloru_tla == 4) setfillstyle(1, 0); else	setfillstyle(1, 4);
	fillpoly(5, pole_bledu);
	rectangle(lewa_gr-37, gora_gr+3, prawa_gr+37, dol_gr-3);
	setcolor(14);
	moveto(lewa_gr+25, gora_gr);
	settextstyle(8, HORIZ_DIR, 1);
	outtext("NIESPODZIEWANY BLAD");
	setcolor(11);
	moveto(lewa_gr-25, gora_gr+30);
	settextstyle(2, HORIZ_DIR, 5);
	if(blad == 1)
	{   moveto(lewa_gr-25, gora_gr+30);
		outtext("Mam klopot z nawiasami. Ich liczba lub pozy-");
		moveto(lewa_gr-25, gora_gr+45);
		outtext("cja nie zgadza sie z wymaganiami obliczen.");
	} else
	if(blad == 2)
	{   moveto(lewa_gr, gora_gr+30);
		outtext("Spodziewalem sie funkcji ale jej nie");
		moveto(lewa_gr, gora_gr+45);
		outtext("znalazlem.");
	} else
	if(blad == 3)
	{   moveto(lewa_gr, gora_gr+30);
		outtext("Spodziewalem sie dzialania ale go nie");
		moveto(lewa_gr, gora_gr+45);
		outtext("znalazlem.");
	} else
	if(blad == 4)
	{   moveto(lewa_gr-10, gora_gr+30);
		outtext("Spotkalem sie z niezrozumialym dzialaniem");
		moveto(lewa_gr-10, gora_gr+45);
		outtext("pomiedzy liczbami.");
	}
	setcolor(9);
	moveto(lewa_gr-32, gora_gr+65);
	outtext("Jest to moja wina albo blad transmisji danych.");
	moveto(lewa_gr+115, gora_gr+80);
	outtext("Przepraszam. Tw¢j program.");
	setcolor(13);
	moveto(lewa_gr-25, gora_gr+100);
	outtext("Prosze, napisz wyrazenie jeszcze raz.");
	setcolor(2);
	moveto(lewa_gr+197, gora_gr+128);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("Dowolny klawisz");

	znak = getch();
	if(znak == 0) getch();
	closegraph(); opcja = 0; wybieranie_postaci_funkcji();
}
