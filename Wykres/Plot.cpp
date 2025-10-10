/*****************************************************************
 *     PLOT.cpp     -  graph of a function, basic version
 *
 *     Remains to do:
 *     stage1: 1. Create an array of possible function names, e.g. "Kosine"
 *                would be converted to "cos".
 *     stage2: 1. Extension of the analysis up to three functions drawn
 *                on a single coordinate  system, including only one
 *                "free-form function".
 *     stage3: 1. Changing parameters for the same function graphs,
 *             2. Analysis of several functions at the same time,
 *             3. Activation of the [ESC] key and the "help" for the rest of the program,
 *             4. Improvment functionality of 'any key' for the rest of the program,
 *             5. Final phase of the analysis:
 *                - final approval of the program's features,
 *                - testing the program,
 *                - implementation of the program.
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
#include<ctype.h> 	/*  for isdigit(), tolower()	*/

#define XMAX      640
#define YMAX      480
#define left       22	/* non-graphic text positions - "EXIT THE PROGRAM" */
#define top         8
#define right      58
#define bottom     14
#define left_gr   180	/* graphic text positions - "EXIT THE PROGRAM" */
#define top_gr    140
#define right_gr  460
#define bottom_gr 280

int i, j, k, l;	/* counters; m, mm,... are counters, local variables...*/
int option = 0;	/* ... n is reserved for a degree of a polynomial */
int backgr_color_for_option = 11;
int backgr_color_for_parameter_sel = 7;
int bad, z;
char character_entered;
char *ptr_character_entered;
char Z[100];    /* 100 because of array A[] */
int string_length;
int trying_to_correct = 0;
int trying_to_exit = 0;
int calling_for_help = 0;
int cursor_position_x, cursor_position_y;
int beep_attention = 0;

/* The first assignments are necessary if you omit the selection of function graph parameters is omitted
   The second - when the parameters are selected */
int unit_length_on_the_OX_axis = 50; int unit_length_on_the_OX = 50;
int unit_length_on_the_OY_axis = 50; int unit_length_on_the_OY = 50;
int unit_OY_length_reduction = 1;
int backgr_pattern_number = 1; int backgr_patt_number = 1;  /* background pattern number */
int backgr_color_number = 7; int backgr_col_number = 7;
int axes_color_number = 12; int axes_col_number = 12;
int function_plot_color_number = 10; int function_plot_col_number = 10;

/* polynomial */
char W[11][15];	    /* array of polynomial coefficients */
char *ptr_W[11];
float w[11];
int n;		    /* polynomial degree */
int number_of_decimal_points;

int hop_count = 0;  /* hops counter from "Yes" to "No" and vice versa...*/
		    /*... for a module "whether_to_exit_the_program" renewed after 20  */
int buff[52][14];   /* buffer for the window being replaced by "whether_to_exit_ ... */
		    /*... the_program" and "help_non_gr". This buffer is slightly oversized just in case */
int page_number;    /* page number of "help_non_gr" */
float x, y, y1;     /* actual values */
int polynomial_chosen = 0;
/*-------------------------------------------------------------------------*/
/* Below: variables and their types for "free-form function" */
int free_form_function_chosen = 0;
int it_is_a_digit = 0;
char A[100];
char *ptrA;
int d_l_A;
int d_l;
char B[100];	/*  exact copy of the A array - in order to possibly A correction  */
char C[150];	/*  actual array of characters as a subject of calculations  */
int d_l_C;
float a;
int x_found = 0;
int decrease_d_l;

int indicator;
float aa, bb;
float yy;
int addition = 0, subtraction = 0, multiplication = 0, division = 0;
int is_there_any_operator_indic;

int number_of_bracket_open;     /* the next number of the open parenthesis */
int number_of_bracket_closed;   /* the next number of the closed parenthesis */
int operation_begins;
int operation_ends;
int parenthesis_position;
char D[100];    /* D is the string in the innermost parentheses, or the entire string */
int d_l_D;
char *ptrD;
char D1[65];	/* the second argument for mod( , ) lub pow( , ) */
char *ptrD1;	/* 	           -- " --			 */

char E[78];	/*  place of bugs report  */
char *ptrE;

char CF[150];
int d_l_CF;
int it_is_a_function;	/* if there is a letter <>'x', then it MUST be a function;
			  "e" and "pi" have already been detected;
			  pos_ and p_ both mean 'position';
			  _1 - first time; _2 - second time the same function */
int it_is_ln  , pos_ln_1  , pos_ln_2  , p_ln_1  , p_ln_2  ;
int it_is_lg  , pos_lg_1  , pos_lg_2  , p_lg_1  , p_lg_2  ;
int it_is_cos , pos_cos_1 , pos_cos_2 , p_cos_1 , p_cos_2 ;
int it_is_sin , pos_sin_1 , pos_sin_2 , p_sin_1 , p_sin_2 ;
int it_is_tan , pos_tan_1 , pos_tan_2 , p_tan_1 , p_tan_2 ;
int it_is_cosh, pos_cosh_1, pos_cosh_2, p_cosh_1, p_cosh_2;
int it_is_sinh, pos_sinh_1, pos_sinh_2, p_sinh_1, p_sinh_2;
int it_is_tanh, pos_tanh_1, pos_tanh_2, p_tanh_1, p_tanh_2;
int it_is_acos, pos_acos_1, pos_acos_2, p_acos_1, p_acos_2;
int it_is_asin, pos_asin_1, pos_asin_2, p_asin_1, p_asin_2;
int it_is_atan, pos_atan_1, pos_atan_2, p_atan_1, p_atan_2;
int it_is_abs , pos_abs_1 , pos_abs_2 , p_abs_1 , p_abs_2 ;
int it_is_mod , pos_mod_1 , pos_mod_2 , p_mod_1 , p_mod_2 ;
int it_is_pow , pos_pow_1 , pos_pow_2 , p_pow_1 , p_pow_2 ;
int it_is_exp , pos_exp_1 , pos_exp_2 , p_exp_1 , p_exp_2 ;
int it_is_sq  , pos_sq_1  , pos_sq_2  , p_sq_1  , p_sq_2  ;
int p; /* common indicator for all functions for the test for their 'empty' - 'no empty' status */
int operations_on_function = 0;  /*operations on a function indicator */
int actual_number_of_commas, predicted_number_of_commas;
int it_is_comma = 0;             /* 'comma' indicator */
/*-------------------------------------------------------------------------*/
int terminate;
int problem_with_domain = 0;     /* 0 means 'no problem' - for exponentiation */
unsigned image_size;
void far *ptr_to_memory_allocation;
int error_detector = 0; 	 /* for a function "error_found()" */

/* arrayed variables for function analysis */
float d_p[30];		/* domain of a function - beginning of the notation in parentheses */
float d_k[30];		/* domain of a function - end of the notation in parentheses */
int l_d = 0;
int function_domain;
float m_z[15];		/* 0's of a function */
int l_m_z = 0;
float e_max[15];	/* function extrema - maximum */
float e_max_x[15];
int l_e_max = 0;
float e_min[15];	/* function extrema - minimum */
float e_min_x[15];
int l_e_min = 0;

void introduction(void);
void function_type_selection(void);
void the_largest_window(void);
void polynomial_choosing(void);
void remove_spaces_and_analyze(void);
void correct_notation_of_the_number(void);
void check_number_size(void);
void free_form_function_choosing(void);
void question_about_notation(void);
void operators_and_math_func_table(void);
void introduction_graphics(void);
void parameters_selection(void);
void OX_axis_unit_length(void);
void OY_axis_unit_length(void);
void background_pattern_number(void);       /* for the entire screen */
void bgr_patterns_and_colors_window(void);  /* help window of background patterns and available colors */
void background_color_number(void);         /* for the entire screen */
void coor_system_axes_color_number(void);   /* coordinate system axes color number */
void function_graph_color_number(void);
void routine_introduction(void);
void preliminary_analysis_of_chars(void);
void no_possibility_of_correction(void);
void function_graph_background(void);
void graph_of_the_function(void);

/* error report */
void this_is_not_a_real_number(void);
void string_is_too_long(void);
void remove_spaces(void);
void this_is_not_a_natural_number(void);
void out_of_range_number(void);
void the_same_color_is_not_allowed(void);
void clear_error_report(void);
void clear_info(void);
void error_found(void);	      /* error report (one of 4) appearing on the graphic
				 screen - previously not detected or simply data
				 transmission error */
/* exit the program and help */
void whether_to_exit_the_program(void);
void contradictory_sentences(int hop_count);
void whether_to_exit_the_program_gr(void);
void help_non_gr(void);
void help_gr(void);

/*-------------------------------------------------------------------------*/
/* Below: functions and their types for an "free-form function" */
void read_the_string_and_analyze_it(void);  /* ... until it succeeds */
void correct_algebraic_expression(void);
void is_there_any_argument(void);
void inner_parenth_operations_test(void);
void inner_parenth_operations(void);
void remove_only_parentheses(void);
void insert_number_into_the_string(void);
float result_of_a_simple_operation(float aa, float bb);

void free_form_function(void);
void math_function_calculation(void);
int is_it_a_lack_of_calculations(void);
/*-------------------------------------------------------------------------*/
void function_menu(void);
void function_analysis(void);
void window_of_function_analysis(void);

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//      Initialization function					        //
//									//
//			introduction();					//
//	  		function_type_selection();                      //
//			introduction_graphics();			//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void main(void)
{   introduction();
	function_type_selection();
	introduction_graphics();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	main() 	 <-- Functions that call this module			//
//                                                                      //
//			Graphical image of the program introduction     //
//								        //
//			whether_to_exit_the_program_gr() <-- Functions  //
//                                            called from this module   //
//			help_gr()  					//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void introduction(void)
{	int driver = VGA, mode = VGAHI, errorcode;
	int maximum_square[] = {0, 0, XMAX-1, 0, XMAX-1, YMAX-5, 0, YMAX-5, 0, 0};
	unsigned image_size;
	void far *ptr_to_memory_allocation;

	initgraph(&driver, &mode, "c:\\TURBOC3\\bgi");   /*  d:\\tc\\bgi"  */

	errorcode = graphresult();
	if(errorcode != grOk)
	{	printf("\nGraphics error (module 'introduction'): %s\n", grapherrormsg(errorcode));
		printf("Press any key to enter the editor : ");
		getch();
		exit(1);
	}

	setfillstyle(1, 8);
	fillpoly(5, maximum_square);
	setcolor(9);

	setcolor(3);
	moveto(194,20);     // moveto(260,20);
	settextstyle(1, HORIZ_DIR, 1);
	outtext("Leszek Buczek (June 1998)");
	moveto(218,45);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("presents a program called");

	setcolor(9);
	moveto(125,60);
	settextstyle(1, HORIZ_DIR, 5);
	outtext("PLOT OF FUNCTION");

	i = 50;
	setcolor(10);
	settextstyle(2, HORIZ_DIR, 6);
	moveto(i+15,120);
	outtext("It is your program! You can copy it from your co-");
	moveto(i,140);
	outtext("lleague and use it for math lessons as well as for");
	moveto(i,160);
	outtext("your own learning purposes. When using it, always");
	moveto(i,180);
	outtext("ask yourself why it is like that, not the other way");
	moveto(i,200);
	outtext("and look for a compliance with your own solutions.");

	setcolor(9);
	moveto(i+15,225);
	outtext("Never believe implicitly what you see. The program");
	moveto(i,245);
	outtext("itself has errors of approximations, but apart from");
	moveto(i,265);
	outtext("that, in the sciences, try to have a critical attitude");
	moveto(i,285);
	outtext("towards what you see, feel, and experience in general.");

	setcolor(14);
	moveto(i+15,310);
	outtext("Remember that 'looking' does not mean 'seeing'. You can");
	moveto(i,330);
	outtext("only see what you can imagine. When you find the conne-");
	moveto(i,350);
	outtext("ctions between the lines of the graph and what you");
	moveto(i,370);
	outtext("observe, you will reach the highest cognitive stage of");
	moveto(i,390);
	outtext("mathematics, and I will be delighted that I have");
	// setcolor(9);
	moveto(i,410);    // (i+250,410);
	outtext("achieved my goal giving you this program.");

	setcolor(7);
	moveto(150,440);
	outtext("PRESS ANY KEY TO ENTER THE PROGRAM");

	do
	{	trying_to_exit = 0;
		calling_for_help = 0;
		character_entered = getch();
		if(character_entered == 27)
		{	trying_to_exit = 1;
			image_size = imagesize(left_gr, top_gr, right_gr, bottom_gr);
			if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
			{	closegraph();
				printf("\nError (1): There is no space in the memory to store the image");
				printf("\nIts size = %u bytes is too large", image_size);
				printf("\nFree memory is only %u bytes\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(left_gr, top_gr, right_gr, bottom_gr, ptr_to_memory_allocation);
			whether_to_exit_the_program_gr();
			putimage(left_gr, top_gr, ptr_to_memory_allocation, COPY_PUT);
			farfree(ptr_to_memory_allocation);
		} else
		if(character_entered == 0)
		{	if(getch() == 59)
			{	calling_for_help = 1;
			image_size = imagesize(left_gr-30, top_gr-30, right_gr+30, bottom_gr+30);
			if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
			{	closegraph();
				printf("\nError (2): There is no space in the memory to store the image");
				printf("\nIts size = %u bytes is too large ", image_size);
				printf("\nFree memory is only %u bytes\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(left_gr-30, top_gr-30, right_gr+30, bottom_gr+30, ptr_to_memory_allocation);
			help_gr();
			putimage(left_gr-30, top_gr-30, ptr_to_memory_allocation, COPY_PUT);
			farfree(ptr_to_memory_allocation);
			} else getch();
		}
	} while( trying_to_exit || calling_for_help);

	closegraph();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	main()  							//
//	function_menu() 						//
//	error_found() 					        	//
//                                                                      //
//			Choosing a form of an algebraic expression	//
//									//
//			the_largest_window() 				//
//			whether_to_exit_the_program() 			//
//			clear_info() 			                //
//			help_non_gr() 					//
//			polynomial_choosing() 		                //
//			free_form_function_choosing() 	                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void function_type_selection(void)
{	textbackground(2); clrscr();
	textcolor(14); /* textbackground(10);  */
	the_largest_window();
	textcolor(9); gotoxy(24, 3);
	cprintf("Choose a form of the function");
	textcolor(5); gotoxy(8, 6);
	cprintf("1.  Polynomial of the form ax^n + ... + bx^2 + cx + d");
	gotoxy(8, 8);
	cprintf("2.  Freeform of an expression f(x)");
	textcolor(11); gotoxy(2, 25);
	cprintf("                                Your choice:              "
			"                   "); textcolor(1); gotoxy(47, 25);
	character_entered = getch();
	while( character_entered != '1' && character_entered != '2' )
	{	if(character_entered == 27)
		{	gettext(left, top, right, bottom, buff);
			whether_to_exit_the_program();
			clear_info();
			textcolor(11); textbackground(10); gotoxy(2, 25);
			cprintf("                                Your choice:         "
					"                        "); textcolor(1); gotoxy(47, 25);
			character_entered = getch();
			continue;
		}
		if(character_entered == 0)
		{	if(getch() == 59)
			{	gettext(left-7, top-2, right+8, bottom+5, buff);
				page_number = 2;
				help_non_gr();
				textcolor(11); textbackground(10); gotoxy(2, 25);
				cprintf("                                Your choice:"
						"                                 ");
				textcolor(1); gotoxy(47, 25);
				character_entered = getch();
				continue;
			} else getch();
		}
		textcolor(14); textbackground(4); gotoxy(2, 25);
		cprintf("               WRONG !  You have a choice of either \"1\" or \"2\"                ");
		delay(1000);
		textcolor(11); textbackground(10); gotoxy(2, 25);
		cprintf("                Choose one of the two options (either 1 or 2)                 ");
		textcolor(1); gotoxy(64, 25);
		character_entered = getch();
	}
	cprintf("%c", character_entered); delay(500);
	if(character_entered == '1') polynomial_choosing(); else free_form_function_choosing();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_type_selection() 					//
//                                                                      //
//			Defining a polynomial				//
//									//
//			the_largest_window() 				//
//			whether_to_exit_the_program() 			//
//			clear_info() 			                //
//			help_non_gr() 					//
//			routine_introduction() 				//
//			remove_spaces_and_analyze() 		        //
//			correct_notation_of_the_number() 	        //
//			check_number_size() 		                //
//                      function_graph_background()                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void polynomial_choosing(void)
{   polynomial_chosen = 1; free_form_function_chosen = 0;

	clrscr();
	textcolor(14); textbackground(7);
	the_largest_window();
	textcolor(9); gotoxy(36, 3);
	cprintf("Polynomial");
	textcolor(5); gotoxy(28, 4);
	cprintf("ax^n + ... + bx^2 + cx + d");
	textcolor(6); gotoxy(20, 6);
	cprintf("Enter a degree of the polynomial (1ö9): ");
	textcolor(1);
	character_entered = getch();
	while( character_entered < '1' || character_entered > '9' )
	{	if(character_entered == 27)
		{	cursor_position_x = wherex();
			cursor_position_y = wherey();
			gettext(left, top, right, bottom, buff);
			whether_to_exit_the_program();
			clear_info();
			textbackground(backgr_color_for_parameter_sel);
			gotoxy(cursor_position_x, cursor_position_y);
			character_entered = getch();
			continue;
		}
		if(character_entered == 0)
		{	if(getch() == 59)
			{	cursor_position_x = wherex();
				cursor_position_y = wherey();
				gettext(left-7, top-2, right+8, bottom+5, buff);
				page_number = 3;
				help_non_gr();
				textcolor(1); textbackground(7);
				gotoxy(cursor_position_x, cursor_position_y);
				character_entered = getch();
				continue;
			} else getch();
		}
		if(character_entered > 32 && character_entered < 127) cprintf("%c", character_entered);
		textcolor(14); textbackground(4); gotoxy(2, 25);
		cprintf("      WRONG !  You have a choice of digits 1, 2, 3, 4, 5, 6, 7, 8 and 9       ");
		delay(1000);
		textcolor(11); textbackground(10); gotoxy(2, 25);
		cprintf("                  Choose one of nine options (from 1 to 9)                    ");
		textcolor(1); textbackground(7); gotoxy(60, 6); printf(" \b");
		character_entered = getch();
	}
	cprintf("%c", character_entered);
	textcolor(11); textbackground(10); gotoxy(2, 25);
	cprintf("                                       "
			"                                       ");
	textcolor(4); textbackground(7); gotoxy(12, 8);
	cprintf("y(x) = "); *ptr_character_entered = character_entered; n = atoi(ptr_character_entered);
	for(l=0; l<n-1; l++)
	{	if(l == 5) gotoxy(19, 9);
		cprintf("a(%d)x^%d + ", l+1, n-l);
	}
	if(l == 5) gotoxy(19, 9);
	cprintf("a(%d)x + a(%d)", l+1, l+2);
	textcolor(5); gotoxy(10, 11);
	cprintf("Enter coefficients of a polynomial %d-th degree :", n);
	j = 0;

	for(l=1; l<n+2; l++)
	{   bad = 0;
		j++;
		textcolor(6); textbackground(7);
		if(l>5) gotoxy(45, 1+l+j); else gotoxy(20, 11+l+j);
		cprintf("a(%d) = ", l);
		textcolor(9);

		do
		{	routine_introduction();
			for(k=0; k<=i; k++)
				W[l][k] = Z[k];
			if(i == 0)
			{   bad = 0;
				W[l][i] = '0';	   /* covering '\0' by '0' */
				W[l][++i] = '\0';
			}
			else
			if(beep_attention)
			{	if(character_entered != 13)     /* && character_entered != 27) ?? I guess it already is superfluous*/
				{   bad = 1;
					printf("\x07");
					W[l][i] = '\0';
					textcolor(14); textbackground(4); gotoxy(2, 25);
					cprintf("      Too many characters. "
							"[ENTER] - accept, [<--] - delete the digits.       ");
					delay(1000);
					textcolor(11); textbackground(10); gotoxy(2, 25);
					cprintf("        A number can be up to 14 characters long. "
							"Spaces are allowed.         ");
					textcolor(9); textbackground(7);
					if(l>5)
						if(l==10) gotoxy(67, 1+l+j); else gotoxy(66, 1+l+j);
					else gotoxy(41, 11+l+j);
				}
			} else
				bad = 0;
		} while(bad);
		if(i!=0)		/* 'i' never will be == 0 but...(?) */
		{	if(l>5)
				if(l==10) gotoxy(53, 1+l+j); else gotoxy(52, 1+l+j);
			else gotoxy(27, 11+l+j);
			printf("               ");
		}
		if(W[l][0] != '0' && i != 1)
		{	remove_spaces_and_analyze();
			correct_notation_of_the_number();      /* e.g. +.4500 -> 0.45 ; -000.0 -> 0 */
		}
		if(bad) continue;
		ptr_W[l] = W[l];	/* This is a number, but its magnitude has to examined */
		w[l] = atof(ptr_W[l]);
		check_number_size();
		if(bad) continue;
		if(l>5)			/* the number is accepted here */
			if(l==10) gotoxy(53, 1+l+j); else gotoxy(52, 1+l+j);
		else gotoxy(27, 11+l+j);
		textcolor(1);
		cprintf("%s", W[l]);
				/* printf("k = %d", k);    I HAVE NOT A CLUE WHY HERE k=101 (NOT k=100)... */
		if(k < 100 )    /* ...FOR TRUNCATED NUMBERS */
		{	textbackground(10); gotoxy(2, 25);
			cprintf("                                                      "
					"                        ");
		}
	}

	do
	{       gotoxy(2,25); textcolor(4); textbackground(10);
		cprintf("     [Enter] - plot the function;      "
			"[p] - selection of plot parameters     ");
		character_entered = getch();
		if(character_entered == 13) function_graph_background();
		/* If you choose not to change the parameters of the graph of the function,
		   the following variables included in the graph modules have optional values:
		   unit_length_on_the_OX_axis = 50
		   unit_length_on_the_OY_axis = 50
		   unit_OY_length_reduction = 1  // that means: ignore the scale; 10 - shrink unit 10 times
		   backgr_pattern_number = 1          // blue
		   backgr_color_number = 7            // light grey
		   axes_color_number = 12             // bright red
		   function_plot_color_number = 10    // light green
		*/
		if(character_entered == 'p') break;   // will exit the 'do' loop and go out of the entire module

		trying_to_exit = calling_for_help = 0;
		if(character_entered == 27)
		{	trying_to_exit = 1;
			gettext(left, top, right, bottom, buff);
			whether_to_exit_the_program();
			continue;
		}
		if(character_entered == 0)
			if(getch() == 59)
			{   calling_for_help = 1;
				gettext(left-7, top-2, right+8, bottom+5, buff);
				page_number = 3;
				help_non_gr();
			}
	} while( trying_to_exit || calling_for_help );
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	polynomial_choosing()						//
//                                                                      //
//		   Removing spaces and testing if this is a real number	//
//									//
//			this_is_not_a_real_number() 		        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void remove_spaces_and_analyze(void)
{   int m, mm;
	int it_is_a_digit = 0;

	number_of_decimal_points = 0;
	string_length = i;
			/*	printf("d_l = %d", string_length);*/
	for(k=0; k<string_length; k++)
	{		/*	printf("k = %d, W = %s, ", k, W[l]);*/
		if(W[l][k]==32)
		{	for(mm=k; mm<string_length; mm++) W[l][mm] = W[l][mm+1];
			string_length--;
			k--;
		}
	}
			/*	k = string_length;*/	/* it is superfluous because the "k" is no longer used */
	if(W[l][0] == '-' || W[l][0] == '+')
		m = 1;
	else
		m = 0;
	for(mm=m; mm<string_length; mm++)
		if(W[l][mm] >= '0' && W[l][mm] <= '9') { it_is_a_digit = 1; break; }
	if(!it_is_a_digit) this_is_not_a_real_number();
	else
		for(mm=m; mm<string_length; mm++)
		{	if(W[l][mm]=='.')
				number_of_decimal_points++;
			if( ( ( W[l][mm] < '0' || W[l][mm] > '9') && W[l][mm] != '.')
				|| number_of_decimal_points > 1)
			{	this_is_not_a_real_number();
				if(bad) break;
			}
		}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	remove_spaces_and_analyze() 					//
//                                                                      //
//			Real number error report	        	//
//									//
//////////////////////////////////////////////////////////////////////////
void this_is_not_a_real_number(void)
{	textcolor(14); textbackground(4); gotoxy(2, 25);
	cprintf("         WRONG !   It must be a real number "
			"in decimal notation here.         ");
	delay(1000);
	textcolor(11); textbackground(10); gotoxy(2, 25);
	cprintf("     Examples:  3,  4.55,  .61,  0.61,  -.61,  -0.61,  "
			"-123.45,  +123.45      ");
	for(k=string_length; k>0; k--) W[l][k-1] = W[l][k]; /* Erase the number just.. */
	bad = 1; l--; j--; /*..in case. "k" is renewed as 0 anyway */
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	polynomial_choosing() 					        //
//                                                                      //
//			Improving the number format			//
//									//
//////////////////////////////////////////////////////////////////////////
void correct_notation_of_the_number(void)   /* np. +.4500 -> 0.45 ; -000.0 -> 0 */
{   int it_is_a_significant_digit = 0;
	int delete_only_the_dot = 0;        /* indicator */
	int m;

	for(k=0; k<string_length; k++)
	{	if( W[l][k] >= '1' && W[l][k] <= '9' ) it_is_a_significant_digit = 1;
		if(it_is_a_significant_digit || W[l][k] == '.') break;
		else
			if(W[l][k] != '-')
			{	for(m=k; m<string_length; m++) W[l][m] = W[l][m+1];
				string_length--;
				k--;
			}
	}

	if(!it_is_a_significant_digit && W[l][k] == '.')
	{	for(m=string_length; m>=k; m--) W[l][m+1] = W[l][m];
		W[l][m+1] = '0';
		string_length++;
	}

	if(it_is_a_significant_digit && number_of_decimal_points) delete_only_the_dot = 1;
	it_is_a_significant_digit = 0;
	for(k=string_length-1; k>=0; k--)
	{	if(W[l][k] >= '1' && W[l][k] <= '9') break; /*it_is_a_significant_digit = 1*/
		else
		{   if(delete_only_the_dot && W[l][k] == '.') delete_only_the_dot = 2;
			if(delete_only_the_dot)
			{	W[l][string_length-1] = W[l][string_length];
				string_length--;
			}
			if(delete_only_the_dot == 2) break;
		}
	}
	if(string_length == 0) { W[l][0] = '0'; string_length = 1; }
	k = string_length;     /* renewal of the string length */
	W[l][k] = '\0';        /* just to be sure */
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	polynomial_choosing() 					        //
//                                                                      //
//                      Discarding a number that is too big, too small,	//
//                      or truncating decimal digits                    //
//									//
//////////////////////////////////////////////////////////////////////////
void check_number_size(void)
{   int m, mm = 0;

	if( w[l] >= 1000000 || w[l] <= -1000000 )
	{	if( w[l] >= 1000000 )
		{	textcolor(14); textbackground(4); gotoxy(2, 25);
			cprintf("     I did not accept!  The acceptable upper limit"
					" of a number is 999999.     ");
			delay(1000);
			textcolor(11); textbackground(10); gotoxy(2, 25);
			cprintf("               Even MILLION (1000000) is too big"
					" number for me.               ");
		} else
			{	textcolor(14); textbackground(4); gotoxy(2, 25);
				cprintf("    I did not accept!  The acceptable lower limit "
						"of a number is -999999.     ");
				delay(1000);
				textcolor(11); textbackground(10); gotoxy(2, 25);
				cprintf("  The number MINUS MILLION (-1000000) and below"
						" are too small numbers to me.  ");
			}
		for(k=string_length; k>0; k--) W[l][k-1] = W[l][k]; /* erase the number.. */
		bad = 1; l--; j--;     /*..just in case. "k" is renewed as 0 anyway */
	} else
		if(number_of_decimal_points)
		{	for(k=0; k<string_length; k++)
				if(W[l][k] == '.')
					for(m=k+1; m<string_length; m++)
					{	mm++;
						if(mm > 6)
						{   for(m=string_length; m>k+7; m--)
								W[l][m-1] = W[l][m];
							string_length = k+mm;
							k = 100;
							textcolor(11); textbackground(10); gotoxy(2, 25);
							cprintf("Attention:I have limited the number by "
									"cutting it to 6 digits after the period");
							textbackground(backgr_color_for_parameter_sel);
							break;
						}
					}
		}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_type_selection() 				        //
//	operators_and_math_func_table() 				//
//                                                                      //
//			Selecting a free-form function			//
//									//
//			the_largest_window() 				//
//			whether_to_exit_the_program() 			//
//			clear_info() 			                //
//			help_non_gr() 					//
//			operators_and_math_func_table() 	        //
//			read_the_string_and_analyze_it() 	        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void free_form_function_choosing(void)
{   char choice;
	clrscr();
	textcolor(14); textbackground(1);
	the_largest_window();
	gotoxy(24, 3);
	cprintf("Selecting a free-form function f(x)");

	textcolor(5); textbackground(7); gotoxy(5, 13);
	cprintf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ"
			"ÍÍÍÍÍÍÍÍÍÍ»");
	for(i=0; i<9; i++)
	{	gotoxy(5, i+14);
		cprintf("º                                                        "
				"              º");
	}
	gotoxy(5, i+14);
	cprintf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ"
			"ÍÍÍÍÍÍÍÍÍÍ¼");
	textcolor(1); gotoxy(23, 14);
	cprintf("Available operations (here: à and á)");
	textcolor(0); gotoxy(10, 16); cprintf("Operators                 :  ");
	textcolor(4); cprintf("  +     -     *     /");
	textcolor(0); gotoxy(10, 17); cprintf("Logarithmic functions     :  ");
	textcolor(4); cprintf("ln(à)        lg(à)");
	textcolor(0); gotoxy(10, 18); cprintf("Trigonometric functions   :  ");
	textcolor(4); cprintf("cos(à)       sin(à)       tan(à)");
		gotoxy(39, 19); cprintf("acos(à)      asin(à)      atan(à)");
	textcolor(0); gotoxy(10, 20); cprintf("Hyperbolic functions      :  ");
	textcolor(4); cprintf("cosh(à)      sinh(à)      tanh(à)");
	textcolor(0); gotoxy(10, 21); cprintf("Other mathemat. functions :  ");
	textcolor(4); cprintf("abs(à)       mod(à,á)     sq(à)");
		gotoxy(39, 22); cprintf("pow(à,á)     exp(à)");

	textcolor(3); textbackground(1); gotoxy(3, 5);
	cprintf("Do you like to have detailed information about the operators? (Y/N) [N] ");
	choice = getch();
	while(1)
	{	if(choice == 27)
		{	cursor_position_x = wherex();
			cursor_position_y = wherey();
			gettext(left, top, right, bottom, buff);
			whether_to_exit_the_program();
			clear_info();
			textbackground(backgr_color_for_parameter_sel);
			gotoxy(cursor_position_x, cursor_position_y);
			choice = getch();
			continue;
		} else
			if(choice == 0)
			{	if(getch() == 59)
				{	cursor_position_x = wherex();
					cursor_position_y = wherey();
					gettext(left-7, top-2, right+8, bottom+5, buff);
					page_number = 4;
					help_non_gr();
					gotoxy(cursor_position_x, cursor_position_y);
					choice = getch();
					continue;
				} else
				{	getch();
					break;
				}
			} break;
	}
	if(choice == 'y' || choice == 'Y') operators_and_math_func_table();
	textcolor(2); textbackground(1); cprintf("N");
	textcolor(9); gotoxy(3, 7); cprintf("f(x) = ");
	read_the_string_and_analyze_it();

	// You will be asked questions about possible changes to the plot
	//   parameters if you like to have changes.
	/* If you choose not to change the parameters of the graph of your function,
	   the following variables included in the graph modules have optional values:
	   unit_length_on_the_OX_axis = 50
	   unit_length_on_the_OY_axis = 50
	   unit_OY_length_reduction = 1  // that is mean: ignore the scale; 10 - shrink unit 10 times
	   backgr_pattern_number = 1               // blue
	   backgr_color_number = 7              // light grey
	   axes_color_number = 12             // light red
	   function_plot_color_number = 10         // light green
	*/
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	free_form_function_choosing()					//
//                                                                      //
//			Table of Operators and Functions		//
//									//
//			the_largest_window() 				//
//			whether_to_exit_the_program() 			//
//			clear_info() 			                //
//			help_non_gr() 					//
//			free_form_function_choosing() 	                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void operators_and_math_func_table(void)
{	clrscr();
	textcolor(1); textbackground(3);
	the_largest_window();
	textcolor(14); gotoxy(14, 3);
	cprintf("Mathematical Operators and Functions to use on à and á");
	textcolor(4); gotoxy(6, 6);
	cprintf("Operators                           Trigonometric functions");
	textcolor(5); gotoxy(8, 7);
	cprintf("+  "); textcolor(8); cprintf("addition                         ");
	textcolor(5); cprintf("cos(à)   "); textcolor(8); cprintf("cosine à");
	textcolor(5); gotoxy(8, 8);
	cprintf("-  "); textcolor(8); cprintf("subtraction                      ");
	textcolor(5); cprintf("sin(à)   "); textcolor(8); cprintf("sine à");
	textcolor(5); gotoxy(8, 9);
	cprintf("*  "); textcolor(8); cprintf("multiplication                   ");
	textcolor(5); cprintf("tan(à)   "); textcolor(8); cprintf("tangent à");
	textcolor(5); gotoxy(8, 10);
	cprintf("/  "); textcolor(8); cprintf("division                         ");
	textcolor(5); cprintf("acos(à)  "); textcolor(8); cprintf("arcus cosine à");
	textcolor(5); gotoxy(44, 11);
	cprintf("asin(à)  "); textcolor(8); cprintf("arcus sine à");
	textcolor(4); gotoxy(6, 12);
	cprintf("Logarithmic functions                 ");
	textcolor(5); cprintf("atan(à)  "); textcolor(8); cprintf("arcus tangent à");
	textcolor(5); gotoxy(8, 13);
	cprintf("ln(à)  "); textcolor(8); cprintf("natural logarithm à");
	textcolor(5); gotoxy(8, 14);
	cprintf("lg(à)  "); textcolor(8); cprintf("decimal logarithm à        ");
	textcolor(4); cprintf("Other mathematical functions");
	textcolor(5); gotoxy(44, 15);
	cprintf("abs(à)    "); textcolor(8); cprintf("absolute value à");
	textcolor(4); gotoxy(6, 16);
	cprintf("Hyperbolic functions                  ");
	textcolor(5); cprintf("mod(à,á)  "); textcolor(8); cprintf("division remainder à/á");
	textcolor(5); gotoxy(8, 17);
	cprintf("cosh(à)  "); textcolor(8); cprintf("hyperbolic cosine à        ");
	textcolor(5); cprintf("pow(à,á)  "); textcolor(8); cprintf("à to the power of á");
	textcolor(5); gotoxy(8, 18);
	cprintf("sinh(à)  "); textcolor(8); cprintf("hyperbolic sine à          ");
	textcolor(5); cprintf("exp(à)    "); textcolor(8); cprintf("e to the power of à");
	textcolor(5); gotoxy(8, 19);
	cprintf("tanh(à)  "); textcolor(8); cprintf("hyperbolic tangent à       ");
	textcolor(5); cprintf("sq(à)     "); textcolor(8); cprintf("square root à");
	textcolor(11); gotoxy(12, 22);
	cprintf("Detailed information can be found in the school textbooks");
	while(1)
	{	textcolor(1); textbackground(2); gotoxy(2, 25);
		cprintf("                   Press any key to type an expression "
				"f(x)                   \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		character_entered = getch();
		if(character_entered == 27)
		{	gettext(left, top, right, bottom, buff);
			whether_to_exit_the_program();
			clear_info();
		} else
			if(character_entered == 0)
			{	if(getch() == 59)
				{	gettext(left-7, top-2, right+8, bottom+5, buff);
					page_number = 4;
					clear_info();
					help_non_gr();
				} else
				{	getch();
					break;
				}
			} else
				break;
	}
	free_form_function_choosing();
}

  /********************************************************************
   *------------------------------------------------------------------*
   *			Process before calculations		      *
   *------------------------------------------------------------------*
   ********************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	free_form_function_choosing()					//
//	correct_algebraic_expression()					//
//                                                                      //
//			Typing characters into a string and parsing them//
//			( the longest module )				//
//									//
//			routine_introduction() 				//
//			correct_algebraic_expression() 			//
//			is_there_any_argument() 			//
//			clear_info() 			                //
//			question_about_notation() 			//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void read_the_string_and_analyze_it(void)
{	int m;
	int d_l_fiction;
	char F[150];

free_form_function_chosen = 1; polynomial_chosen = 0;
it_is_a_function = 0;	  /* if there is a letter<>'x' then it MUST be a function */
it_is_ln   = 0; pos_ln_1   = -1; pos_ln_2   = -1; p_ln_1   = -1; p_ln_2   = -1;
it_is_lg   = 0; pos_lg_1   = -1; pos_lg_2   = -1; p_lg_1   = -1; p_lg_2   = -1;
it_is_cos  = 0; pos_cos_1  = -1; pos_cos_2  = -1; p_cos_1  = -1; p_cos_2  = -1;
it_is_sin  = 0; pos_sin_1  = -1; pos_sin_2  = -1; p_sin_1  = -1; p_sin_2  = -1;
it_is_tan  = 0; pos_tan_1  = -1; pos_tan_2  = -1; p_tan_1  = -1; p_tan_2  = -1;
it_is_cosh = 0; pos_cosh_1 = -1; pos_cosh_2 = -1; p_cosh_1 = -1; p_cosh_2 = -1;
it_is_sinh = 0; pos_sinh_1 = -1; pos_sinh_2 = -1; p_sinh_1 = -1; p_sinh_2 = -1;
it_is_tanh = 0; pos_tanh_1 = -1; pos_tanh_2 = -1; p_tanh_1 = -1; p_tanh_2 = -1;
it_is_acos = 0; pos_acos_1 = -1; pos_acos_2 = -1; p_acos_1 = -1; p_acos_2 = -1;
it_is_asin = 0; pos_asin_1 = -1; pos_asin_2 = -1; p_asin_1 = -1; p_asin_2 = -1;
it_is_atan = 0; pos_atan_1 = -1; pos_atan_2 = -1; p_atan_1 = -1; p_atan_2 = -1;
it_is_abs  = 0; pos_abs_1  = -1; pos_abs_2  = -1; p_abs_1  = -1; p_abs_2  = -1;
it_is_mod  = 0; pos_mod_1  = -1; pos_mod_2  = -1; p_mod_1  = -1; p_mod_2  = -1;
it_is_pow  = 0; pos_pow_1  = -1; pos_pow_2  = -1; p_pow_1  = -1; p_pow_2  = -1;
it_is_exp  = 0; pos_exp_1  = -1; pos_exp_2  = -1; p_exp_1  = -1; p_exp_2  = -1;
it_is_sq   = 0; pos_sq_1   = -1; pos_sq_2   = -1; p_sq_1   = -1; p_sq_2   = -1;

	textcolor(7); gotoxy(10, 7);
	do
	{   routine_introduction();
		for(k=0; k<=i; k++)
			A[k] = Z[k];
		if(i == 0)
		{	bad = 1;
			textcolor(14); textbackground(4); gotoxy(2, 25);
			cprintf("                     Enter any algebraic"
				" expression here.                     ");
			delay(1000);
			textcolor(11); textbackground(10); gotoxy(2, 25);
			cprintf("           Example: 4abs(sin(2.5"
					"pi/cos(x2tanh(3.2x))))-pow(e,-x/pi)           ");
			textcolor(7); textbackground(1);
			gotoxy(10, 7);
		}
		else
		if(beep_attention)
		{	if(character_entered != 13) /* && character_entered != 27) ??  I guess it already is superfluous */
			{   bad = 1;
				printf("\x07");
				if(it_is_a_digit > 6)
				{	cursor_position_x = wherex();
					cursor_position_y = wherey();
					textcolor(14); textbackground(4); gotoxy(2, 25);
					cprintf("                         Too many "
							"digits in a number.                         ");
					delay(1000);
					textcolor(11); textbackground(10); gotoxy(2, 25);
					cprintf("Number cannot have more than 6 digits "
							"in both the integer and fractional parts");
					textcolor(7); textbackground(1);
					gotoxy(cursor_position_x, cursor_position_y);
				} else
				{	A[i] = '\0';
					textcolor(14); textbackground(4); gotoxy(2, 25);
					cprintf("                       I cannot handle "
							"more characters.                       ");
					delay(1000);
					textcolor(11); textbackground(10); gotoxy(2, 25);
					cprintf("  You can only enter up to 70 chars. "
							"[ENTER] - accept, [<--] - remove digits. ");
					textcolor(7); textbackground(1);
					gotoxy(79, 7);
				}
			}
		} else
			bad = 0;
	} while(bad);

	d_l = d_l_A = strlen(A);
	strcpy(B,A);

	/*--------------------------------------------------------------*
	 *      Remove all encountered spaces				*
	 *--------------------------------------------------------------*/
	decrease_d_l = 0;
	for(i=0; i<d_l; i++)
	if( A[i] == 32 )
	{   decrease_d_l++;
		for(k=i; k<d_l; k++) A[k] = A[k+1];
		i--;
	}
	d_l = d_l - decrease_d_l;

	/*----------------------------------------------------------------------*
	 *	Replace uppercase letters with lowercase letters - if necessary	*
	 *----------------------------------------------------------------------*/
	for(i=0; i<d_l; i++) A[i] = tolower(A[i]);

	/*--------------------------------------------------------------*
	 *	Check for unacceptable characters	        	*
	 *--------------------------------------------------------------*/
	for(i=0; i<d_l; i++)
		if( (A[i]>32 && A[i]<40) || (A[i]>57 && A[i]<97) || (A[i]==102) ||
			(A[i]==106) || (A[i]==107) || (A[i]==114) || (A[i]==117) ||
			(A[i]==118) || (A[i]>120) )
			{   ptrE = E;
				ptrE="     An unacceptable mark has been found.  "
					 "Correct the expression typing.     ";
				correct_algebraic_expression();
			}

	/*--------------------------------------------------------------*
	 *	Check for the presence of "pi" and "e"			*
	 *--------------------------------------------------------------*/
	/* "pi" will be replaced by: 3.141593 for the calculation process */
	/* "ã" for the better expression view */
	for(i=0; i<d_l; i++)
		if(A[i] == 'p' && A[i+1] == 'i')
		{	for(j=0; j<6; j++)
			{	for(k=d_l; k>i+2; k--) A[k] = A[k-1];
				d_l = d_l++;
			}
			A[i] = '3'; A[i+1] = '.'; A[i+2] = '1'; A[i+3] = '4';
			A[i+4] = '1'; A[i+5] = '5'; A[i+6] = '9'; A[i+7] = '3';
			if(i+8 < d_l)	/* first, look to see if there is a number after "pi"... */
				if( A[i+8] == '.' || (A[i+8] >47 && A[i+8] <58) )
				{	for(k=d_l; k>i+8; k--) A[k] = A[k-1];
					A[i+8] = '*';
					d_l++;
				}
			if(i > 0)	/*...and then, if there is no number before "pi" */
				if( A[i-1] == '.' || (A[i-1] >47 && A[i-1] <58) )
				{	for(k=d_l; k>i; k--) A[k] = A[k-1];
					A[i] = '*';
					d_l++;
				}
			i = i + 7;
		}
	/* "e" will be replaced by: 2.718282 for the calculation process,
	       also "e" will be shown in an expression view.
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
			if(i+8 < d_l)	/* first, look to see if there is a number after "e"... */
				if( A[i+8] == '.' || (A[i+8] >47 && A[i+8] <58) )
				{	for(k=d_l; k>i+8; k--) A[k] = A[k-1];
					A[i+8] = '*';
					d_l++;
				}
			if(i > 0)	/*...and then, if there is no number before "e" */
				if( A[i-1] == '.' || (A[i-1] >47 && A[i-1] <58) )
				{	for(k=d_l; k>i; k--) A[k] = A[k-1];
					A[i] = '*';
					d_l++;
				}
			i = i + 7;
		}

	/*-----------------------------------------------------------------*
	 *	Check the positions of the simplest operators (+, -, *, /) *
	 *-----------------------------------------------------------------*/
	if( A[0] == '*' || A[0] == '/' || A[d_l-1] == '+' || A[d_l-1] == '-' ||
		A[d_l-1] == '*' || A[d_l-1] == '/')
		{   ptrE = E;
			ptrE="         The operation requires two numbers. "
				 "Correct the expression.          ";
			correct_algebraic_expression();
		}
	for(i=0; i<d_l-1; i++)
	if( (A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/') &&
	  (A[i+1] == '+' || A[i+1] == '-' || A[i+1] == '*' || A[i+1] == '/') )
		{   ptrE = E;
			ptrE="       Error in writing operators (+, -, *, /). "
				 "Correct the expression.       ";
			correct_algebraic_expression();
		}
	if(A[0] == '+')		/* remove '+' at the beginning of the string */
	{	for(i=0; i<d_l; i++) A[i] = A[i+1];
		d_l--;
	}

	/*--------------------------------------------------------------*
	 *	Check the position of the parentheses and their number	*
	 *--------------------------------------------------------------*/
	number_of_bracket_open = 0;
	number_of_bracket_closed = 0;
	for(i=0; i<d_l; i++)
	{   if( A[i] == '(' )
			number_of_bracket_open++;
		else
			if(A[i] == ')' && (number_of_bracket_open > number_of_bracket_closed))
				number_of_bracket_closed++;
	}
	if(number_of_bracket_open != number_of_bracket_closed)
	{   ptrE = E;
		ptrE="             Error in placing parentheses. "
			 "Correct the expression.            ";
		correct_algebraic_expression();
	}

	/****************************************************************
	 *	Entering new characters into the string			*
	 ****************************************************************
	 *--------------------------------------------------------------------*
	 *  a)  Enter an additional multiplication sign before the numbers... *
	 *--------------------------------------------------------------------*/
	for(i=1; i<d_l; i++)	      /*  If there is a sign before the digit  */
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
	 *  b)	...after the numbers...					*
	 *--------------------------------------------------------------*/
	for(i=1; i<d_l; i++)	   /*  If there is a digit before a non-digit character  */
		if( (A[i]<48 || A[i]>57) && A[i]!='+' && A[i]!='-' &&
			 A[i]!='*' && A[i]!='/' && A[i]!='.' && A[i]!=')' && A[i]!=',' )
			if( A[i-1]==46 || (A[i-1]>47 && A[i-1]<58) )
			{   for(k=d_l; k>i; k--) A[k] = A[k-1];
				A[i] = '*';
				d_l++;
				i++;
			}

	/*--------------------------------------------------------------*
	 *  c)	...between "x" and other characters			*
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
	 *  d)	...and between the parentheses: ) and (			*
	 *--------------------------------------------------------------*/
	for(i=0; i<d_l; i++)
	{	if( A[i] == ')' && A[i+1] == '(' )
		{	for(k=d_l; k>i+1; k--) A[k] = A[k-1];
			A[i+1] = '*';
			d_l++;
			i++;
		}
	}

	/*----------------------------------------------------------------------*
	 *  e)  Enter additional parentheses (for multiplication and division)	*
	 *----------------------------------------------------------------------*/
	for(i=1; i<d_l; i++)
	{	number_of_bracket_open = 0;
		number_of_bracket_closed = 0;
		if( A[i]=='*' || A[i]=='/' )
		{	k = i;	/* stage 1: There is an opportunity to place "(". Search for the place */
			do
			{	do
				{	k--;
					if( A[k]==')' ) number_of_bracket_closed++;
					if( A[k]=='(' ) number_of_bracket_open++;
					if(!number_of_bracket_closed && number_of_bracket_open)
						break;
					if( number_of_bracket_closed == number_of_bracket_open )
					{	number_of_bracket_open = 0;
						number_of_bracket_closed = 0;
					}
				} while( !((A[k]=='+' || A[k]=='-') && A[k-1]!='(') && k!=0 && A[k]!=',' );

				if(!number_of_bracket_closed && number_of_bracket_open) break;
				} while( ( number_of_bracket_closed>number_of_bracket_open )
					&& k!=0 && A[k]!=',');

			if( !(!number_of_bracket_closed && number_of_bracket_open) &&
				k!=0 && A[k]!=',' && A[k-1]!='(' && A[k-1]!=',' )
			{	/* The program is looking for where to put "(" because it has to put "(" somewhere */
/*	If any test gives an error, remember that a variable called
	"parentheses_difference_number" can be located in this place
*/				parenthesis_position = k+1;
				for(k=d_l; k>parenthesis_position; k--) A[k] = A[k-1];
				A[parenthesis_position] = '(';
				d_l++;
				i++;
				k = i;  /* stage 2: If there was "(", look for a place to insert ")"... */
				number_of_bracket_open = 0;  /*...to location where * or / was found */
				number_of_bracket_closed = 0;
				it_is_a_function = 0;
				do
				{	do
					{	k++;
						if( A[k]==')' ) number_of_bracket_closed++;
						if( A[k]=='(' ) number_of_bracket_open++;
						if( A[k]>96 && A[k]<123 && A[k]!='x' ) it_is_a_function=1;
						if( (A[k]=='*' || A[k]=='/') &&
							number_of_bracket_closed >= number_of_bracket_open )
						{	number_of_bracket_open = 0;
							number_of_bracket_closed = 0;
						}
					} while(A[k]!='+' && A[k]!='-' && k!=d_l &&
						A[k]!=',' && A[k]!=')' );
				} while( (number_of_bracket_closed<number_of_bracket_open ||
						  ((number_of_bracket_closed==number_of_bracket_open) &&
						   (A[k]!='+' && A[k]!='-'))) &&
					k!=d_l && (A[k]!=',' || it_is_a_function) );
				parenthesis_position = k;
				for(k=d_l; k>parenthesis_position; k--) A[k] = A[k-1];
				A[parenthesis_position] = ')';
				d_l++;
				i=i+2;
			}
		}
	}

	/************************************************************************
	 *	Recognize functions and analyze them in terms of their syntax	*
	 *									*
	 *	The functions that can be used are as follows:			*
	 * ln(),	lg(),	cos(),	sin(),	tan(),	acos(),	asin(),	atan(),	*
	 * cosh(),	sinh(),	tanh(),	abs(),	mod(),	pow(),	exp(),	sq().	*
	 *	Any function can only be used twice.		        	*
	 ************************************************************************
	 *------------------------------------------------------------------*
	 *	  Determining the presence of mathematical functions and    *
	 *	 analyzing their external syntax (inside the parentheses)   *
	 *------------------------------------------------------------------*/
	for(i=0; i<d_l; i++)
	{ if( (i==0 && A[i]>96 && A[i]<123 && A[i]!='x') || /* letter for i==0 */
		  (i!=0 && A[i]>96 && A[i]<123 && A[i]!='x' &&  /* letter for i!=0 */
		   (A[i-1]<97 || A[i-1]>122) ) ) 	   /*..and the previous one is not a letter */
	 { it_is_a_function = 0;				   /* we assume it does not exist */
	   if(A[i] == 'l')
	   { if(A[i+1]=='n' && A[i+2]=='(')
		 { if(pos_ln_1 == -1)
		   { it_is_a_function = it_is_ln = 1; pos_ln_1 = i; p = p_ln_1 = i+3;
			 is_there_any_argument();
		   }
		   else
		   { if(pos_ln_2 == -1)
			 { it_is_a_function = 1; pos_ln_2 = i; p = p_ln_2 = i+3;
			   is_there_any_argument();
			 }
			 else
			 { ptrE = E;
			   ptrE=" The \"ln()\" function can only be used twice.  "
					"Include this in the expression. ";
			   correct_algebraic_expression();
			 }
		   }
		 }
		 else if(A[i+1]=='g' && A[i+2]=='(')
			  { if(pos_lg_1 == -1)
				{ it_is_a_function = it_is_lg = 1; pos_lg_1 = i; p = p_lg_1 = i+3;
				  is_there_any_argument();
				}
				else
				{ if(pos_lg_2 == -1)
				  { it_is_a_function = 1; pos_lg_2 = i; p = p_lg_2 = i+3;
					is_there_any_argument();
				  }
				  else
				  { ptrE = E;
					ptrE=" The \"lg()\" function can only be used twice.  "
						 "Include this in the expression. ";
					correct_algebraic_expression();
				  }
				}
			  }
	   } else
		 if(A[i] == 'c')
		 { if(A[i+1]=='o' && A[i+2]=='s')
			if(A[i+3]=='(')
			{ if(pos_cos_1 == -1)
			  { it_is_a_function = it_is_cos = 1; pos_cos_1 = i; p = p_cos_1 = i+4;
				is_there_any_argument();
			  }
			  else
			  { if(pos_cos_2 == -1)
				{ it_is_a_function = 1; pos_cos_2 = i; p = p_cos_2 = i+4;
				  is_there_any_argument();
				}
				else
				{ ptrE = E;
				  ptrE=" The \"cos()\" function can only be used twice. "
					   "Include this in the expression. ";
				  correct_algebraic_expression();
				}
			  }
			}
			else if(A[i+3]=='h' && A[i+4]=='(')
				 { if(pos_cosh_1 == -1)
				   { it_is_a_function = it_is_cosh = 1; pos_cosh_1 = i;
					 p = p_cosh_1 = i+5; is_there_any_argument();
				   }
				   else
				   { if(pos_cosh_2 == -1)
					 { it_is_a_function = 1; pos_cosh_2 = i; p = p_cosh_2 = i+5;
					   is_there_any_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" The \"cosh()\" function can only be used twice. "
							"Include this in the expression.";
					   correct_algebraic_expression();
					 }
				   }
				 }
		 } else
		   if(A[i] == 's')
		   { if(A[i+1]=='i' && A[i+2]=='n')
			 { if(A[i+3]=='(')
			   { if(pos_sin_1 == -1)
				 { it_is_a_function = it_is_sin = 1; pos_sin_1 = i;
				   p = p_sin_1 = i+4; is_there_any_argument();
				 }
				 else
				 { if(pos_sin_2 == -1)
				   { it_is_a_function = 1; pos_sin_2 = i; p = p_sin_2 = i+4;
					 is_there_any_argument();
				   }
				   else
				   { ptrE = E;
					 ptrE=" The \"sin()\" function can only be used twice. "
						  "Include this in the expression. ";
					 correct_algebraic_expression();
				   }
				 }
			   }
			   else if(A[i+3]=='h' && A[i+4]=='(')
					{ if(pos_sinh_1 == -1)
					  { it_is_a_function = it_is_sinh = 1; pos_sinh_1 = i;
						p = p_sinh_1 = i+5; is_there_any_argument();
					  }
					  else
					  { if(pos_sinh_2 == -1)
						{ it_is_a_function = 1; pos_sinh_2 = i;
						  p = p_sinh_2 = i+5; is_there_any_argument();
						}
						else
						{ ptrE = E;
						  ptrE=" The \"sinh()\" function can only be used twice. "
							   "Include this in the expression.";
						  correct_algebraic_expression();
						}
					  }
					}
			 } else if(A[i+1]=='q' && A[i+2]=='(')
					{ if(pos_sq_1 == -1)
					  { it_is_a_function = it_is_sq = 1; pos_sq_1 = i;
						p = p_sq_1 = i+3; is_there_any_argument();
					  }
					  else
					  { if(pos_sq_2 == -1)
						{ it_is_a_function = 1; pos_sq_2 = i; p = p_sq_2 = i+3;
						  is_there_any_argument();
						}
						else
						{ ptrE = E;
						  ptrE=" The \"sq()\" function can only be used twice.  "
							   "Include this in the expression. ";
						  correct_algebraic_expression();
						}
					  }
					}
		   } else
			 if(A[i] == 't')
			 { if(A[i+1]=='a' && A[i+2]=='n')
				if(A[i+3]=='(')
				{ if(pos_tan_1 == -1)
				  { it_is_a_function = it_is_tan = 1; pos_tan_1 = i;
					p = p_tan_1 = i+4; is_there_any_argument();
				  }
				  else
				  { if(pos_tan_2 == -1)
					{ it_is_a_function = 1; pos_tan_2 = i; p = p_tan_2 = i+4;
					  is_there_any_argument();
					}
					else
					{ ptrE = E;
					  ptrE=" The \"tan()\" function can only be used twice. "
						   "Include this in the expression. ";
					  correct_algebraic_expression();
					}
				  }
				}
				else if(A[i+3]=='h' && A[i+4]=='(')
					 { if(pos_tanh_1 == -1)
					   { it_is_a_function = it_is_tanh = 1; pos_tanh_1 = i;
						 p = p_tanh_1 = i+5; is_there_any_argument();
					   }
					   else
					   { if(pos_tanh_2 == -1)
						 { it_is_a_function = 1; pos_tanh_2 = i;
						   p = p_tanh_2 = i+5; is_there_any_argument();
						 }
						 else
						 { ptrE = E;
						   ptrE=" The \"tanh()\" function can only be used twice. "
								"Include this in the expression.";
						   correct_algebraic_expression();
						}
					   }
					 }
			 } else
			   if(A[i] == 'a')
			   { if(A[i+4] == '(')
				 { if(A[i+1]=='c' && A[i+2]=='o' && A[i+3]=='s')
				   { if(pos_acos_1 == -1)
					 { it_is_a_function = it_is_acos = 1; pos_acos_1 = i;
					   p = p_acos_1 = i+5; is_there_any_argument();
					 }
					 else
					 { if(pos_acos_2 == -1)
					   { it_is_a_function = 1; pos_acos_2 = i; p = p_acos_2 = i+5;
						 is_there_any_argument();
					   }
					   else
					   { ptrE = E;
						 ptrE=" The \"acos()\" function can only be used twice. "
							  "Include this in the expression.";
						 correct_algebraic_expression();
					   }
					 }
				   }
				   else if(A[i+1]=='s' && A[i+2]=='i' && A[i+3]=='n')
						{ if(pos_asin_1 == -1)
						  { it_is_a_function = it_is_asin = 1; pos_asin_1 = i;
							p = p_asin_1 = i+5; is_there_any_argument();
						  }
						  else
						  { if(pos_asin_2 == -1)
							{ it_is_a_function = 1; pos_asin_2 = i;
							  p = p_asin_2 = i+5; is_there_any_argument();
							}
							else
							{ ptrE = E;
							  ptrE=" The \"asin()\" function can only be used twice. "
								   "Include this in the expression.";
							  correct_algebraic_expression();
							}
						  }
						}
						else if(A[i+1]=='t' && A[i+2]=='a' && A[i+3]=='n')
							 { if(pos_atan_1 == -1)
							   { it_is_a_function = it_is_atan = 1; pos_atan_1 = i;
								 p = p_atan_1 = i+5; is_there_any_argument();
							   }
							   else
							   { if(pos_atan_2 == -1)
								 { it_is_a_function = 1; pos_atan_2 = i;
								   p = p_atan_2 = i+5; is_there_any_argument();
								 }
								 else
								 { ptrE = E;
								   ptrE=" The \"atan()\" function can "
										"only be used twice. "
										"Include this in the expression.";
								   correct_algebraic_expression();
								 }
							   }
							 }
				 } else if(A[i+1]=='b' && A[i+2]=='s' && A[i+3]=='(')
						{ if(pos_abs_1 == -1)
						  { it_is_a_function = it_is_abs = 1; pos_abs_1 = i;
							p = p_abs_1 = i+4; is_there_any_argument();
						  }
						  else
						  { if(pos_abs_2 == -1)
							{ it_is_a_function = 1; pos_abs_2 = i;
							  p = p_abs_2 = i+4; is_there_any_argument();
							}
							else
							{ ptrE = E;
							  ptrE=" The \"abs()\" function can only be used twice. "
								   "Include this in the expression. ";
							  correct_algebraic_expression();
							}
						  }
						}
			   } else
				 if(A[i] == 'm' && A[i+1]=='o' && A[i+2]=='d' && A[i+3]=='(')
				 { if(pos_mod_1 == -1)
				   { it_is_a_function = it_is_mod = 1; pos_mod_1 = i;
					 p = p_mod_1 = i+4; is_there_any_argument();
				   }
				   else
				   { if(pos_mod_2 == -1)
					 { it_is_a_function = 1; pos_mod_2 = i; p = p_mod_2 = i+4;
					   is_there_any_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" The \"mod()\" function can only be used twice. "
							"Include this in the expression. ";
					   correct_algebraic_expression();
					 }
				   }
				 }
				 else
				 if(A[i] == 'p' && A[i+1]=='o' && A[i+2]=='w' && A[i+3]=='(')
				 { if(pos_pow_1 == -1)
				   { it_is_a_function = it_is_pow = 1; pos_pow_1 = i;
					 p = p_pow_1 = i+4; is_there_any_argument();
				   }
				   else
				   { if(pos_pow_2 == -1)
					 { it_is_a_function = 1; pos_pow_2 = i; p = p_pow_2 = i+4;
					   is_there_any_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" The \"pow()\" function can only be used twice. "
							"Include this in the expression. ";
					   correct_algebraic_expression();
					 }
				   }
				 }
				 else
				 if(A[i] == 'e' && A[i+1]=='x' && A[i+2]=='p' && A[i+3]=='(')
				 { if(pos_exp_1 == -1)
				   { it_is_a_function = it_is_exp = 1; pos_exp_1 = i;
					 p = p_exp_1 = i+4; is_there_any_argument();
				   }
				   else
				   { if(pos_exp_2 == -1)
					 { it_is_a_function = 1; pos_exp_2 = i; p = p_exp_2 = i+4;
					   is_there_any_argument();
					 }
					 else
					 { ptrE = E;
					   ptrE=" The \"exp()\" function can only be used twice. "
							"Include this in the expression. ";
					   correct_algebraic_expression();
					 }
				   }
				 }
	  if(it_is_a_function == 0)
	  { ptrE = E;
		ptrE="A function is expected but its notation is incorrect. "
			 "Type correct expression.";
		correct_algebraic_expression();
	  }
	 }
	}

	/*------------------------------------------------------------------*
	 *	Internal syntax analysis for commas.	                    *
	 *------------------------------------------------------------------*/
	actual_number_of_commas = 0;
	for(i=0; i<d_l; i++)
	{	if(A[i] == ',')
		{	actual_number_of_commas++;
			//	ptrC = "+";	/* result of the previous approach - changing A[] to C[]...*/
			//	C[i] = *ptrC;   /*...to check a string without math functions */
		}
	}
	predicted_number_of_commas = 0;
	if(it_is_a_function)
		if(it_is_mod || it_is_pow)
		{	if(pos_mod_1 != -1) predicted_number_of_commas++;
			if(pos_mod_2 != -1) predicted_number_of_commas++;
			if(pos_pow_1 != -1) predicted_number_of_commas++;
			if(pos_pow_2 != -1) predicted_number_of_commas++;
		}
	if(actual_number_of_commas != predicted_number_of_commas)
	{	ptrE = E;
		ptrE="  Something is wrong with the commas. "
			 "Remember \".\" replaces \",\" in a number.  ";
		correct_algebraic_expression();
	} else
	{   gotoxy(10, 8); printf("                                        "
				  "                              ");
	////////////// inserting "ã" instead of 3.141593 ///////////////
	//    The first line below is artificially entered to close the
	//    string because I noticed that the program does not do this
	////////////////////////////////////////////////////////////////
	A[d_l] = '\0';

	d_l_fiction = d_l;
	strcpy(F,A);
	for(i=0; i<d_l-7; i++)			 /* maybe i<d_l-8 */
		if(F[i] == '3')
		 if(F[i+1] == '.')
		  if(F[i+2] == '1')
		   if(F[i+3] == '4')
			if(F[i+4] == '1')
			 if(F[i+5] == '5')
			  if(F[i+6] == '9')
			   if(F[i+7] == '3')
			   {	F[i] = 'ã';
					for(j=0; j<7; j++)
					{	for(k=i+1; k< d_l_fiction; k++)
							F[k] = F[k+1];
						d_l_fiction--;
					}
			   }
	for(i=0; i<d_l-7; i++)			 /* maybe i<d_l-8 */
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
					{	for(k=i+1; k< d_l_fiction; k++)
							F[k] = F[k+1];
						d_l_fiction--;
					}
			   }
		gotoxy(10, 9); textcolor(7); cprintf("I have changed your entry to:");
		gotoxy(10,10); printf("                                        "
							  "                              ");
		gotoxy(10,11); printf("                                        "
							  "                              ");
		textcolor(9); gotoxy(3,10); cprintf("f(x) = ");
			/* print string F[] */
		gotoxy(10,10); textcolor(11);
		if(d_l_fiction<=70) cprintf("%s", F);
		else
		{	for(i=70; i>0; i--)
				if(F[i] == '+' || F[i] == '/' || F[i] == '*') break;
			for(m=0; m<=i; m++)	cprintf("%c", F[m]);
			gotoxy(10,11); for(m=i+1; m<d_l_fiction; m++) cprintf("%c", F[m]);
		}  /* switching to operational string A[] */
		if( A[0] == '-' && (A[1] < 48 || A[1] > 57) ) /* put 0 before '-' at the beginning of the string */
		{	for(i=d_l; i>=0; i--) A[i+1] = A[i];
			A[0] = '0';
			d_l++;
		}

		strcpy(CF,A);	/* remember the original string */
		d_l_CF = d_l;

		clear_info();
		question_about_notation();
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	read_the_string_and_analyze_it()				//
//                                                                      //
//    Analysis of internal syntax in terms of the presence of arguments	//
//									//
//			correct_algebraic_expression() 			//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void is_there_any_argument(void)
{   while(A[p]=='(')
	{	p++;
	}
	if( ( A[p]<43 || A[p]==44 || A[p]==47 || (A[p]>57 && A[p]<97) || A[p]>122 )
	 || ( (A[p]=='+' || A[p]=='-') && (A[p+1]<46 || A[p+1]==47 ||
		  (A[p+1]>57 && A[p+1]<97) || A[p+1]>122) ) )
		{	ptrE = E;
			ptrE=" Every function requires an argument. "
				 "Check the table and correct any errors. ";
			correct_algebraic_expression();
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
					ptrE="  The \"mod()\" and \"pow()\" functions must have "
						 "two arguments. Correct errors.  ";
					correct_algebraic_expression();
				}
		  }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	read_the_string_and_analyze_it()				//
//	is_there_any_argument()						//
//	question_about_notation()					//
//                                                                      //
// Detecting an error and calling the string entry procedure again	//
//							                //
//			read_the_string_and_analyze_it() 	        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void correct_algebraic_expression(void)
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
	// I delete the entire string and renew "d_l" just in case.
	d_l = strlen(A);
	for(m=d_l; m>0; m--) A[m-1] = A[m];
	d_l = 0;

	read_the_string_and_analyze_it();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	read_the_string_and_analyze_it()				//
//                                                                      //
//	   Asking for the user's consent whether the string processed	//
//	   by the program is accepted by the user			//
//									//
//                      function_graph_background()                     //
//                      introduction_graphics() 			//
//			correct_algebraic_expression() 			//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void question_about_notation(void)
{   int m,/* mm,*/ mmm=1;
	char m_ch1, m_ch2;

	gettext(left, top+6, right, bottom+6, buff);
	textbackground(2);
	textcolor(8); gotoxy(left, top+6);
	cprintf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	for(m=1; m<6; m++)
	{	gotoxy(left, top+6+m);
		cprintf("º                                   º");
	}
	gotoxy(left, top+6+m);
	cprintf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	textcolor(10); gotoxy(left+3, top+8); cprintf("Do you agree with my notation?");
	_setcursortype(_NOCURSOR);
	textcolor(11); gotoxy(left+6, top+10); cprintf("Yes                  No ");
	do
	{	gotoxy(left+6, top+10);
		for(m=0; m<10; m++)
		{   if( kbhit() )
				if( (m_ch1 = getch()) == 0 )
				{       m_ch2 = getch();  /* defined in getch(): #define KEY_RIGHT 77 */
					if( m_ch2 == 77 ) { hop_count++; break; }
		// It produces a 'warning' --> 	if( (m_ch2 = getch()) == 77 ) { hop_count++; break; }
				}
				else
				{	if( m_ch1 == 13 )
		// It is not here: _setcursortype(_NORMALCURSOR); I am wondering why it is not needed
					// Question: Should I change plot parameters or leave optional values?
					// The query window remains on the screen but is no longer active - do not worry about it.
					{       gotoxy(2,25); textcolor(4); textbackground(10);
						cprintf(" [Enter] - function graph; "
							"[Any other key] - selection of the graph parameters");
						character_entered = getch();
						if(character_entered == 13) function_graph_background();
						else introduction_graphics();
					}
					else
						if( m_ch1 == 9 ) { hop_count++;	break; }
				}
			textcolor(9); cprintf("Yes\b\b\b"); delay(100);
			textcolor(11); cprintf("Yes\b\b\b"); delay(100);
			if(m > 8) m = 0;
		}
		if(!mmm) break;
		gotoxy(left+27, top+10);
		for(m=0; m<10; m++)
		{   if( kbhit() )
				if( (m_ch1 = getch()) == 0 )
				{       m_ch2 = getch(); /* defined in getch(): #define KEY_LEFT 75 */
					if( m_ch2 == 75 ) { hop_count++; break; }
		// It produces a 'warning' -->  if( (m_ch2 = getch()) == 75 ) { hop_count++; break; }
				}
				else
				{	if( m_ch1 == 13 )
					{   puttext(left, top+6, right, bottom+6, buff);
						_setcursortype(_NORMALCURSOR);
						ptrE = E;
						ptrE="Type the expression again, but in a "
							 "different way so I will know what you mean";
						correct_algebraic_expression();
					}
					else
						if( m_ch1 == 9 ) { hop_count++; break; }
				}
			textcolor(9); cprintf("No \b\b\b"); delay(100);
			textcolor(11); cprintf("No \b\b\b"); delay(100);
			if(m > 8) m = 0;
		}
	if(hop_count == 21) hop_count = 0;
	} while(1); // do it until it comes out of the middle of the loop
	textbackground(1);
//	_setcursortype(_NORMALCURSOR);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	main()								//
//	question_about_notation()					//
//	parameters_selection()						//
//	preliminary_analysis_of_chars()					//
//                                                                      //
//	   A static, informative graphic image that can be reused	//
//	   with the "option" as a dynamic image	                	//
//									//
//                      whether_to_exit_the_program_gr()		//
//			help_gr()					//
//			parameters_selection()			        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void introduction_graphics(void)
{	int driver = VGA, mode = VGAHI, errorcode;
	int maximum_square[] = {0, 0, XMAX-1, 0, XMAX-1, YMAX-5, 0, YMAX-5, 0, 0};
	unsigned image_size;
	void far *ptr_to_memory_allocation;

	initgraph(&driver, &mode, "c:\\TURBOC3\\bgi");  /*  "d:\\tc\\bgi");  */

	errorcode = graphresult();
	if(errorcode != grOk)
	{	printf("\nGraphics error (module 'introduction_graphics'): %s\n", grapherrormsg(errorcode));
		printf("Press any key to enter the editor : ");
		getch();
		exit(1);
	}

	setfillstyle(10, 9);
	fillpoly(5, maximum_square);
	setcolor(9);
	moveto(146,15);
	settextstyle(1, HORIZ_DIR, 5);
	outtext("FUNCTION GRAPH");

	setcolor(2);
	settextstyle(2, HORIZ_DIR, 6);
	if(option==0)
	{   j = 0;
		moveto(14,75);
		outtext("You will select parameters by answering the "
				"following questions:");
	} else
	{   j = 10;
		moveto(185,75);
		outtext("Currently selected parameter");
	}

	setcolor(3);
	i = 100;
	moveto(i-65+j,i+j);
	settextstyle(2, HORIZ_DIR, 5);
	outtext("Unit length on the OX axis in screen points (from 10 to 300) [default]");
	moveto(i-65+j,i+20+j);
	outtext("Unit length on the OY axis in screen points (from 5 to 220) [default]");
	moveto(i-65+j,i+40+j);
	outtext("Background pattern number from the pattern list (from 0 to 11) [default]");
	moveto(i-65+j,i+60+j);
	outtext("Background color number from the color palette below (from 0 to 15) [default]");
	moveto(i-65+j,i+80+j);
	outtext("Coordinate system axes color number (from 0 to 15) [default]");
	moveto(i-65+j,i+100+j);
	outtext("Function plot color number (from 0 to 15) [default]");
	if(option==0)
	{	setcolor(2);
		moveto(43,230);
		settextstyle(2, HORIZ_DIR, 6);
		outtext("This image can always be previewed by using the  '?'  sign");
	}
	setcolor(14);
	settextstyle(2, HORIZ_DIR, 6);
	if(option==0)
	{	moveto(150,260);
		outtext("PRESS ANY KEY TO ENTER THE PROGRAM");
	} else
	{	moveto(145,247);
		outtext("PRESS ANY KEY TO SELECT THE OPTIONS");
	}
	setcolor(7);
	moveto(88,420);
	settextstyle(4, HORIZ_DIR, 5);
	outtext("Leszek Buczek's programs");
	setcolor(3);
	moveto(250,290);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("PALETTE OF COLOURS");

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
	if(option>0)
	{	setcolor(10);
		for(i=1; i<option; i++)
		{	circle(27, 97+i*20, 3);
			setfillstyle(1, 10);
			floodfill(27, 97+i*20, 10);
		}
		circle(27, 97+i*20, 3);
	} else option = 1;

	do
	{	trying_to_exit = 0;
		calling_for_help = 0;
		character_entered = getch();
		if(character_entered == 27)
		{	trying_to_exit = 1;
			image_size = imagesize(left_gr, top_gr, right_gr, bottom_gr);
			if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
			{	closegraph();
				printf("\nError (3): There is no space in the memory to store the image");
				printf("\nIts size = %u bytes is too large", image_size);
				printf("\nFree memory is only %u bytes\n", coreleft() );
				exit(1);
			}
			getimage(left_gr, top_gr, right_gr, bottom_gr, ptr_to_memory_allocation);
			whether_to_exit_the_program_gr();
			putimage(left_gr, top_gr, ptr_to_memory_allocation, COPY_PUT);
			farfree(ptr_to_memory_allocation);
		} else
		if(character_entered == 0)
		{	if(getch() == 59)
			{	calling_for_help = 1;
			image_size = imagesize(left_gr-30, top_gr-30, right_gr+30, bottom_gr+30);
			if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
			{	closegraph();
				printf("\nError (4): There is no space in the memory to store the image");
				printf("\nIts size = %u bytes is too large", image_size);
				printf("\nFree memory is only %u bytes\n", coreleft() );
				exit(1);
			}
			getimage(left_gr-30, top_gr-30, right_gr+30, bottom_gr+30, ptr_to_memory_allocation);
			help_gr();
			putimage(left_gr-30, top_gr-30, ptr_to_memory_allocation, COPY_PUT);
			farfree(ptr_to_memory_allocation);
			} else getch();
		}
	} while( trying_to_exit || calling_for_help);

	closegraph();
	parameters_selection();
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	introduction_graphics()						//
//	parameters_selection()						//
//	function_menu()							//
//                                                                      //
//	           A module that serves as a "switchboard" between the  //
//                 selection of "options"                       	//
//								        //
//			the_largest_window()				//
//			OX_axis_unit_length()		                //
//			OY_axis_unit_length()		                //
//			background_pattern_number()			//
//			background_color_number()			//
//			coor_system_axes_color_number()	                //
//			function_graph_color_number()	                //
//			introduction_graphics()				//
//			whether_to_exit_the_program()			//
//			clear_info()			                //
//			function_graph_background()		        //
//			parameters_selection()			        //
//			help_non_gr()					//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void parameters_selection(void)
{	clrscr();
	textcolor(1); textbackground(backgr_color_for_option);
	the_largest_window();
	cprintf("                                        "
			"                                       ");
	textcolor(5); textbackground(backgr_color_for_parameter_sel);
	gotoxy(8, 3);
	cprintf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ"
			"ÍÍÍÍ»");
	for(i=0; i<9; i++)
	{	gotoxy(8, i+4);
		cprintf("º                                                        "
				"        º");
	}
	gotoxy(8, i+4);
	cprintf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ"
			"ÍÍÍÍ¼");
	textcolor(14); gotoxy(30, 5); cprintf("SETTING THE PARAMETERS");

	if(option==1) OX_axis_unit_length(); else
	  if(option==2) OY_axis_unit_length(); else
		if(option==3) background_pattern_number(); else
		  if(option==4) background_color_number(); else
			if(option==5) coor_system_axes_color_number(); else
			  if(option==6) function_graph_color_number();

	/*  draw the graph of the function  */

	if(option > 3 && option < 8)
	{	textbackground(backgr_color_for_option);
		for(i=0; i<9; i++)
		{   gotoxy(5, 15+i);
			cprintf("                                                      "
					"                  ");
		}
	}

	gotoxy(20, 18); textcolor(8); textbackground(backgr_color_for_option);
	if(option==7)
	{   textcolor(15);
		cprintf(" Press any key to see the function graph ");
	}
	else
	{   cprintf("Press any key to select the next parameter");
		gotoxy(34, 19); cprintf("Preview [?] ");
	}
	while(1) /* work to eternity or ...to call a function, others... */
	{	character_entered = getch();		/*... options or drawing mathematical functions */
		if(option < 7 && (character_entered == '?' || character_entered == '/'))
		{	introduction_graphics();
			continue;
		}
		if(character_entered == 27)
		{	cursor_position_x = wherex();
			cursor_position_y = wherey();
			gettext(left, top, right, bottom, buff);
			whether_to_exit_the_program();
			clear_info();
			textbackground(backgr_color_for_option);
			gotoxy(cursor_position_x, cursor_position_y);
			continue;
		}
		else
		if(character_entered != 0)
		{	if(option == 7)
				function_graph_background();
			else
				parameters_selection();
		} else
			if(getch() == 59)
			{   cursor_position_x = wherex();
				cursor_position_y = wherey();
				gettext(left-7, top-2, right+8, bottom+5, buff);
				page_number = 5;
				help_non_gr();
				clear_info();
				textcolor(11); textbackground(backgr_color_for_parameter_sel);
				gotoxy(cursor_position_x, cursor_position_y);
				continue;
			} else
			{	if(option == 7)
					function_graph_background();
				else
					parameters_selection();
			}
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_type_selection()					//
//	polynomial_choosing()						//
//	free_form_function_choosing()					//
//	operators_and_math_func_table()					//
//	parameters_selection()						//
//                                                                      //
//	                Drawing of an empty window covering the entire  //
//                      screen (except the last line)	                //
//									//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void the_largest_window(void)
{	cprintf("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"
			"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
	for(i=0; i<22; i++)
		cprintf("³                                                        "
				"                      ³");
	cprintf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"
			"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	parameters_selection()						//
//                                                                      //
//	   Selection of the unit length on the OX axis at screen points //
//								        //
//			routine_introduction()				//
//			string_is_too_long()				//
//			remove_spaces()					//
//			this_is_not_a_natural_number()			//
//			out_of_range_number()		          	//
//			clear_error_report()		        	//
//			clear_info()		        	        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void OX_axis_unit_length(void)
{   option = 1;
	bad = 0;		       /* means: it is good */
	if(unit_length_on_the_OX<100) j = 2; else j = 3;
		/* j - here: default length of the accepted string "unit_length_on_the_OX"... */
		/*... before entering the module because the assumption is that after ...*/
		/*... a plot we create another plot without leaving the program.     */
		/* Additional note:
		   So far, only one graph in a coordinate system is possible;
		   two or three graphs in one coordinate system have not been
		   done yet and therefore they are impossible to do now. */
	gotoxy(19,7); textcolor(8);
	cprintf("Unit length on the OX axis in screen points");
	gotoxy(32, 8); cprintf("(10ö300) [%d] ", unit_length_on_the_OX);

	do
	{	routine_introduction();
		if(i == 0)
		{	bad = 0;
			unit_length_on_the_OX_axis = unit_length_on_the_OX;
			string_length = 0;				/* I guess this is unnecessary */
		}
		else
		{   if(beep_attention)
				string_is_too_long();
			else
			{	string_length = strlen(Z);
				remove_spaces();
				for(i=0; i<string_length; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ this_is_not_a_natural_number(); break;
					} else bad = 0;
				}
			}
			if(bad == 0 && i != 0)			/* so far so good */
			{	z = atoi(Z);
				if( (z<10 || z>300) && string_length>0 )
				{   out_of_range_number();
				} else
				{	bad = 0;		/* it is good after all */
					unit_length_on_the_OX_axis = z;
				}
			}
			gotoxy(44+j, 8); printf("         ");
		}
		if(bad == 0)					/* finally it is good */
		{	unit_length_on_the_OX = unit_length_on_the_OX_axis;
			gotoxy(44+j, 8);
			textcolor(9); textbackground(backgr_color_for_parameter_sel);
			cprintf("%d", unit_length_on_the_OX_axis);
			clear_error_report();
		} else
		{	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
			gotoxy(44+j, 8);
		}
	} while(bad);
	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
	clear_info();
	option++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	parameters_selection()						//
//                                                                      //
//	   Selection of the unit length on the OY axis at screen points //
//									//
//			routine_introduction()				//
//			string_is_too_long()				//
//			remove_spaces()					//
//			this_is_not_a_natural_number()		       	//
//			out_of_range_number()		        	//
//			clear_error_report()		        	//
//			clear_info()		                	//
//			whether_to_exit_the_program()	               	//
//			help_non_gr()					//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void OY_axis_unit_length(void)
{   option = 2;
	bad = 0;			/* means: it is good */
	if(unit_length_on_the_OY<10) j = 1; else if(unit_length_on_the_OY<100) j = 2; else j = 3;
		/* j - here: default length of the accepted string "unit_length_on_the_OY"... */
		/*... before entering the module because the assumption is that after ...*/
		/*... a plot we create another plot without leaving the program.     */
	gotoxy(19,7); textcolor(8);
	cprintf("Unit length on the OY axis in screen points");
	gotoxy(33, 8); cprintf("(5ö220) [%d] ", unit_length_on_the_OY);

	do
	{	routine_introduction();
		if(i == 0)
		{	bad = 0;
			unit_length_on_the_OY_axis = unit_length_on_the_OY;
			string_length = 0;
		}
		else
		{   if(beep_attention)
				string_is_too_long();
			else
			{	string_length = strlen(Z);
				remove_spaces();
				for(i=0; i<string_length; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ this_is_not_a_natural_number(); break;
					} else bad = 0;
				}
			}
			if(bad == 0 && i != 0)			/* so far so good */
			{	z = atoi(Z);
				if( (z<5 || z>220) && string_length>0 )
				{	out_of_range_number();
				} else
				{	bad = 0;		/* it is good after all */
					unit_length_on_the_OY_axis = z;
				}
			}
			gotoxy(44+j, 8); printf("         ");
		}
		if(bad == 0)					/* finally it is good */
		{	unit_length_on_the_OY = unit_length_on_the_OY_axis;
			gotoxy(44+j, 8);
			textcolor(9); textbackground(backgr_color_for_parameter_sel);
			cprintf("%d", unit_length_on_the_OY_axis);
			clear_error_report();
		} else
		{	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
			gotoxy(44+j, 8);
		}
	} while(bad);
	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
	clear_info();

	gotoxy(21, 10); textcolor(8); textbackground(backgr_color_for_parameter_sel);
	cprintf("Reduce the length of the unit ten times");
	gotoxy(21, 11);
	cprintf("( Y(es) / N(o - any other key) ) [");
	if(unit_OY_length_reduction == 1) cprintf("N] ? ");
	else cprintf("Y] ? ");

	while(1)
	{	character_entered = getch();
		if(character_entered == 27)
		{	cursor_position_x = wherex();
			cursor_position_y = wherey();
			gettext(left, top, right, bottom, buff);
			whether_to_exit_the_program();
			clear_info();
			textbackground(backgr_color_for_parameter_sel);
			gotoxy(cursor_position_x, cursor_position_y);
			continue;
		} else
			if(character_entered == 0)
			{	if(getch() == 59)
				{	cursor_position_x = wherex();
					cursor_position_y = wherey();
					gettext(left-7, top-2, right+8, bottom+5, buff);
					page_number = 5;
					help_non_gr();
					gotoxy(cursor_position_x, cursor_position_y);
					continue;
				} else
				{	getch();
					break;
				}
			} break;
	}
	textcolor(9); textbackground(backgr_color_for_parameter_sel);
	if(character_entered == 'y' || character_entered == 'Y')
	{   cprintf("Yes");
		unit_OY_length_reduction = 10;
	} else
		if(character_entered == 'n' || character_entered == 'N')
		{	cprintf("No ");
			unit_OY_length_reduction = 1;
		} else	/* ignore any other character and assume "default" */
			if(unit_OY_length_reduction == 1) cprintf("No ");
			else cprintf("Yes");
	option++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	parameters_selection()						//
//                                                                      //
//	   Selecting a screen background pattern number (from 0 to 11)	//
//									//
//			bgr_patterns_and_colors_window()	       	//
//			routine_introduction()				//
//			string_is_too_long()				//
//			remove_spaces()					//
//			this_is_not_a_natural_number()		       	//
//			out_of_range_number()		        	//
//			clear_error_report()		        	//
//			clear_info()		                	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void background_pattern_number(void)
{   option = 3;
	bgr_patterns_and_colors_window();
	bad = 0;			/* means: it is good */
	if(backgr_patt_number<10) j = 1; else j = 2;
		/* j - here: default length of the accepted string "backgr_patt_number"...  */
		/*... before entering the module because the assumption is that after...*/
		/*... a plot we create another plot without leaving the program.     */
	gotoxy(17,7); textcolor(8);
	cprintf("Screen background pattern number (0ö11) [%d] ", backgr_patt_number);

	do
	{	routine_introduction();
		if(i == 0)
		{	bad = 0;
			backgr_pattern_number = backgr_patt_number;
			string_length = 0;
		}
		else
		{   if(beep_attention)
				string_is_too_long();
			else
			{	string_length = strlen(Z);
				remove_spaces();
				for(i=0; i<string_length; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ this_is_not_a_natural_number(); break;
					} else bad = 0;
				}
			}
			if(bad == 0 && i != 0)			/* so far so good */
			{	z = atoi(Z);
				if( (z<0 || z>11) && string_length>0 )
				{	out_of_range_number();
				} else
				{	bad = 0;		/* it is good after all */
					backgr_pattern_number = z;
				}
			}
			gotoxy(60+j, 7); printf("         ");
		}
		if(bad == 0)					/* finally it is good */
		{	backgr_patt_number = backgr_pattern_number;
			gotoxy(60+j, 7);
			textcolor(9); textbackground(backgr_color_for_parameter_sel);
			cprintf("%d", backgr_pattern_number);
			clear_error_report();
		} else
		{	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
			gotoxy(60+j, 7);
		}
	} while(bad);
	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
	clear_info();
	option++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	parameters_selection()						//
//                                                                      //
//	  Selecting a screen background color number (from 0 to 15)     //
//									//
//			bgr_patterns_and_colors_window()	       	//
//			routine_introduction()				//
//			string_is_too_long()				//
//			remove_spaces()					//
//			this_is_not_a_natural_number()		       	//
//			out_of_range_number()		        	//
//			clear_error_report()		        	//
//			clear_info()		                	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void background_color_number(void)
{   option = 4;				/* !! this is probably unnecessary */
	bgr_patterns_and_colors_window();
	bad = 0;			/* means: it is good */
	if(backgr_col_number<10) j = 1; else j = 2;
		/* j - here: default length of the accepted string "backgr_col_number"... */
		/*... before entering the module because the assumption is that after ...*/
		/*... a plot we create another plot without leaving the program.     */
	gotoxy(19,7); textcolor(8);
	cprintf("Screen background color number (0ö15) [%d] ", backgr_col_number);

	do
	{	routine_introduction();
		if(i == 0)
		{	bad = 0;
			backgr_color_number = backgr_col_number;
			string_length = 0;
		}
		else
		{   if(beep_attention)
				string_is_too_long();
			else
			{	string_length = strlen(Z);
				remove_spaces();
				for(i=0; i<string_length; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ this_is_not_a_natural_number(); break;
					} else bad = 0;
				}
			}
			if(bad == 0 && i != 0)			/* so far so good */
			{	z = atoi(Z);
				if( (z<0 || z>15) && string_length>0 )
				{	out_of_range_number();
				} else
				{	bad = 0;		/* it is good after all */
					backgr_color_number = z;
				}
			}
			gotoxy(60+j, 7); printf("         ");
		}
		if(bad == 0)					/* finally it is good */
		{	backgr_col_number = backgr_color_number;
			gotoxy(60+j, 7);
			textcolor(9); textbackground(backgr_color_for_parameter_sel);
			cprintf("%d", backgr_color_number);
			clear_error_report();
		} else
		{	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
			gotoxy(60+j, 7);
		}
	} while(bad);
	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
	clear_info();
	option++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	parameters_selection()						//
//                                                                      //
//	            Selecting the color number of the coordinate system //
//                  axes (from 0 to 15)                         	//
//									//
//			bgr_patterns_and_colors_window()	       	//
//			routine_introduction()				//
//			the_same_color_is_not_allowed()		       	//
//			string_is_too_long()				//
//			remove_spaces()					//
//			this_is_not_a_natural_number()		       	//
//			out_of_range_number()		        	//
//			clear_error_report()		        	//
//			clear_info()		                	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void coor_system_axes_color_number(void)
{   option = 5;				/* !! this is probably unnecessary */
	bgr_patterns_and_colors_window();
	bad = 0;			/* means: it is good */
	if(axes_col_number<10) j = 1; else j = 2;
		/* j - here: default length of the accepted string "axes_col_number"... */
		/*... before entering the module because the assumption is that after ...*/
		/*... a plot we create another plot without leaving the program.     */
	gotoxy(16,7); textcolor(8);
	cprintf("Coordinate system axes color number (0ö15) [%d] ", axes_col_number);

	do
	{	routine_introduction();
		if(i == 0)
		{	if(axes_col_number == backgr_color_number)
				the_same_color_is_not_allowed();
			else
			{	bad = 0;
				axes_color_number = axes_col_number;
				string_length = 0;
			}
		}
		else
		{   if(beep_attention)
				string_is_too_long();
			else
			{	string_length = strlen(Z);
				remove_spaces();
				for(i=0; i<string_length; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ this_is_not_a_natural_number(); break;
					} else bad = 0;
				}
			}
			if(bad == 0 && i != 0)			/* so far so good */
			{	z = atoi(Z);
				if( (z<0 || z>15) && string_length>0 )
				{	out_of_range_number();
				} else
					if(z==backgr_color_number)
					{   the_same_color_is_not_allowed();
					} else
					{	bad = 0;	/* it is good after all */
						axes_color_number = z;
					}
			}
			gotoxy(62+j, 7); printf("         ");
		}
		if(bad == 0)					/* finally it is good */
		{	axes_col_number = axes_color_number;
			gotoxy(62+j, 7);
			textcolor(9); textbackground(backgr_color_for_parameter_sel);
			cprintf("%d", axes_color_number);
			clear_error_report();
		} else
		{	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
			gotoxy(62+j, 7);
		}
	} while(bad);
	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
	clear_info();
	option++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	parameters_selection()						//
//                                                                      //
//	Selecting the color number of the function graph (from 0 to 15)	//
//									//
//			bgr_patterns_and_colors_window()	       	//
//			routine_introduction()				//
//			the_same_color_is_not_allowed()		       	//
//			string_is_too_long()				//
//			remove_spaces()					//
//			this_is_not_a_natural_number()		       	//
//			out_of_range_number()		        	//
//			clear_error_report()		        	//
//			clear_info()		                	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void function_graph_color_number(void)
{   option = 6;				/* !! this is probably unnecessary */
	bgr_patterns_and_colors_window();
	bad = 0;			/* means: it is good */
	if(function_plot_col_number<10) j = 1; else j = 2;
		/*j - here: default length of the accepted string "function_plot_col_number"..*/
		/*... before entering the module because the assumption is that after ...*/
		/*... a plot we create another plot without leaving the program.     */
	gotoxy(13, 7); textcolor(8);
	cprintf("The color number of the function graph (0ö15) [%d] ", function_plot_col_number);

	do
	{	routine_introduction();
		if(i == 0)
		{	if(function_plot_col_number == backgr_color_number)
				the_same_color_is_not_allowed();
			else
			{	bad = 0;
				function_plot_color_number = function_plot_col_number;
				string_length = 0;
			}
		}
		else
		{   if(beep_attention)
				string_is_too_long();
			else
			{	string_length = strlen(Z);
				remove_spaces();
				for(i=0; i<string_length; i++)
				{	if(Z[i]<'0' || Z[i]>'9')
					{ this_is_not_a_natural_number(); break;
					} else bad = 0;
				}
			}
			if(bad == 0 && i != 0)	                /* so far so good */
			{	z = atoi(Z);
				if( (z<0 || z>15) && string_length>0 )
				{	out_of_range_number();
				} else
					if(z==backgr_color_number)
					{   the_same_color_is_not_allowed();
					} else
					{	bad = 0;	/* it is good after all */
						function_plot_color_number = z;
					}
			}
			gotoxy(62+j, 7); printf("         ");
		}
		if(bad == 0)					/* finally it is good */
		{	function_plot_col_number = function_plot_color_number;
			gotoxy(62+j, 7);
			textcolor(9); textbackground(backgr_color_for_parameter_sel);
			cprintf("%d", function_plot_color_number);
			clear_error_report();
		} else
		{	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
			gotoxy(62+j, 7);
		}
	} while(bad);
	for(i=string_length; i>0; i--) Z[i-1] = Z[i];
	clear_info();
	option++;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	polynomial_choosing()				        	//
//	read_the_string_and_analyze_it()				//
//	OX_axis_unit_length()				        	//
//	OY_axis_unit_length()				        	//
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//	       Checking subsequent characters and entering their string	//
//									//
//			preliminary_analysis_of_chars();	       	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void routine_introduction(void)
{   if(!(option == 0 && beep_attention)) i = 0;
	trying_to_correct = trying_to_exit = calling_for_help = beep_attention = 0;
	textcolor(11);
	while((character_entered = getch()) != 13)
	{   preliminary_analysis_of_chars();
		if(trying_to_correct)
		   printf("\x07");
		else
			if(!trying_to_exit && !beep_attention && !calling_for_help)
				cprintf("%c", character_entered);
		if(beep_attention) break;
	}
	Z[i] = '\0';
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	routine_introduction()						//
//                                                                      //
//		 Checking the character entered from the keyboard	//
//									//
//			help_non_gr()					//
//			no_possibility_of_correction()           	//
//			whether_to_exit_the_program()		       	//
//			clear_info()		                	//
//                      function_graph_background()                     //
//			introduction_graphics()				//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void preliminary_analysis_of_chars(void)
{   int m;

	if(trying_to_correct)
	{	trying_to_correct = 0;
		textbackground(11); gotoxy(2, 25);
		cprintf("                                                        "
				"                      ");
		textcolor(11);
		if(option > 0)
			textbackground(backgr_color_for_parameter_sel);
		else
			if(free_form_function_chosen)
				textbackground(1);
			else
				textbackground(7);
		gotoxy(cursor_position_x, cursor_position_y);
	}
	else
		if(trying_to_exit)
			trying_to_exit = 0;
		else
			if(calling_for_help)
				calling_for_help = 0;
	if(character_entered == 0)
	{	if(getch() == 59)
		{   calling_for_help = 1;
			cursor_position_x = wherex();
			cursor_position_y = wherey();
			gettext(left-7, top-2, right+8, bottom+5, buff);
			if(option == 0)
			{	if(free_form_function_chosen)	page_number = 4;
				else page_number = 3;
			}
			else page_number = 5;
			help_non_gr();
			textcolor(11);
			if(option > 0)
				textbackground(backgr_color_for_parameter_sel);
			else
				if(free_form_function_chosen)
					textbackground(1);
				else
					textbackground(7);
			gotoxy(cursor_position_x, cursor_position_y);
		}
		else
		{	trying_to_correct = 1;
			cursor_position_x = wherex();
			cursor_position_y = wherey();
			no_possibility_of_correction();
		}
	} else
		if(character_entered<32 || character_entered>126)
		{   if(character_entered == 8 && i > 0)
			{	printf("\b  \b");
				if(beep_attention)
					beep_attention = 0;
			}
			else		 /* either TAB or ESC was pressed */
			{   if(character_entered == 27)
				{   trying_to_exit = 1;
					cursor_position_x = wherex();
					cursor_position_y = wherey();
					gettext(left, top, right, bottom, buff);
					whether_to_exit_the_program();
					clear_info();
					textcolor(11);
					if(option > 0)
						textbackground(backgr_color_for_parameter_sel);
					else
						if(free_form_function_chosen)
							textbackground(1);
						else
							textbackground(7);
					gotoxy(cursor_position_x, cursor_position_y);
				}
				else
				{	trying_to_correct = 1;
					cursor_position_x = wherex();
					cursor_position_y = wherey();
					no_possibility_of_correction();
				}
				i++;
			}
			i--;
		} else
			{	m = i;
				Z[m++] = character_entered;
				if(option > 0)
				{	if(m == 1 && (character_entered == '?' || character_entered == '/') )
					{	bad = 1;
						string_length = 1;
						// Question: Should I change plot parameters or leave optional values?
						// The query window remains on the screen but is no longer active - do not worry about it.
						gotoxy(2,25); textcolor(4); textbackground(10);
						cprintf(" [Enter] - function graph; "
							"[Any other key] - selection of the graph parameters");
						character_entered = getch();
						if(character_entered == 13) function_graph_background();
						else introduction_graphics();
					}
					if(m == 9)
					{	printf("\b \b\x07");
						beep_attention = 1;
						m--;
						string_length = 8;
					} else beep_attention = 0;
				} else
					if(free_form_function_chosen)
					{  	if(Z[m-1] > 47 && Z[m-1] < 58) /* m-1 is current..*/
						{	it_is_a_digit++; /*..due to the earlier m++.*/
							if(it_is_a_digit > 6)
							{	beep_attention = 1;
								m--;
							}
						} else
							if(Z[m] != 32)
								it_is_a_digit = 0;
						if(m == 70)
						{	beep_attention = 1;
							m--;
						}
					 } else
						if(m == 15)
						{	beep_attention = 1;
							m--;
							string_length = 14;
						} else beep_attention = 0; /* this 'else' is probably redundant */
				i = m;
			}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	preliminary_analysis_of_chars()					//
//                                                                      //
// Report on the impossibility of using keys that may be correction keys//
//				    ( apart from 'Esc', 'F1' i '<--' )	//
//									//
//////////////////////////////////////////////////////////////////////////
void no_possibility_of_correction(void)
{   textcolor(11); textbackground(10); gotoxy(2, 25);
	cprintf("    There is no correction option except removing the last character [<--]    ");
	gotoxy(cursor_position_x, cursor_position_y);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	OX_axis_unit_length()				        	//
//	OY_axis_unit_length()				        	//
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//				  Removes spaces from the string	//
//									//
//////////////////////////////////////////////////////////////////////////
void remove_spaces(void)
{	for(i=0; i<string_length; i++)
	{	if(Z[i]==32)
		{	for(k=i; k<string_length; k++) Z[k] = Z[k+1];
			string_length--;
			i--;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	OX_axis_unit_length()				        	//
//	OY_axis_unit_length()				        	//
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//	       Reports when the limit on the number of characters in    //
//             the string has been exceeded                             //
//									//
//////////////////////////////////////////////////////////////////////////
void string_is_too_long(void)
{	bad = 1;
	gotoxy(15, 10); textcolor(4);
	cprintf(" Such a large number of characters is unacceptable");
	gotoxy(33, 11); textcolor(9); cprintf("Correct the data");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	OX_axis_unit_length()				        	//
//	OY_axis_unit_length()				        	//
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//	     Reports about the entered string that cannot be converted	//
//	     to a natural number				       	//
//									//
//////////////////////////////////////////////////////////////////////////
void this_is_not_a_natural_number(void)
{	bad = 1;
	gotoxy(20, 10); textcolor(4);
	cprintf("The entered value is not a natural number");
	gotoxy(33, 11); textcolor(9); cprintf("Correct the data");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	OX_axis_unit_length()				                //
//	OY_axis_unit_length()				        	//
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//	  Reports when the natural number size limit has been exceeded,	//
//	  depending on the selected option				//
//									//
//////////////////////////////////////////////////////////////////////////
void out_of_range_number(void)
{	bad = 1;
	gotoxy(18, 10); textcolor(4);
	if(option==1) cprintf("    The number must be in a range [10;300]  ");
	else if(option==2) cprintf("    The number must be in a range [5;220]   ");
	 else if(option==3) cprintf("     The number must be in a range [0;11]   ");
	  else cprintf("     The number must be in a range [0;15]   ");
	gotoxy(33, 11); textcolor(9); cprintf("Correct the data");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//           Reports on the selection of either the color number of the //
//           axes or the color of the function graph, which is also the //
//           background color of the screen				//
//									//
//////////////////////////////////////////////////////////////////////////
void the_same_color_is_not_allowed(void)
{	bad = 1;
	gotoxy(12, 10); textcolor(4);
	if(option==5)
		cprintf("The color of the axes is the same as the background color");
	else
		cprintf("The color of the graph is the same as the background color");
	gotoxy(33, 11); textcolor(9); cprintf("Correct the data");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	OX_axis_unit_length()				        	//
//	OY_axis_unit_length()				        	//
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//	   Clears error information from the parameter selection window	//
//									//
//////////////////////////////////////////////////////////////////////////
void clear_error_report(void)
{	textbackground(backgr_color_for_parameter_sel);
	gotoxy(12, 10);
	cprintf("                                                          ");
	gotoxy(33, 11); cprintf("                ");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_type_selection()					//
//	polynomial_choosing()						//
//	free_form_function_choosing()					//
//	operators_and_math_func_table()					//
//	read_the_string_and_analyze_it()				//
//	parameters_selection()						//
//	OX_axis_unit_length()				        	//
//	OY_axis_unit_length()				        	//
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//	preliminary_analysis_of_chars()					//
//                                                                      //
//		   Clears error information from the options window	//
//									//
//////////////////////////////////////////////////////////////////////////
void clear_info(void)
{	if(option >0) textbackground(backgr_color_for_option);
	else
		if(free_form_function_chosen)
			textbackground(1);
		else textbackground(7);
	gotoxy(2, 25);
	cprintf("                                       "
			"                                       ");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	background_pattern_number()					//
//	background_color_number()					//
//	coor_system_axes_color_number()					//
//	function_graph_color_number()					//
//                                                                      //
//   An information window detailing either screen background pattern	//
//   numbers or colors and their numbers				//
//									//
//////////////////////////////////////////////////////////////////////////
void bgr_patterns_and_colors_window(void)
{	if(option==3) { textcolor(3); textbackground(4); } else
		if(option==4) { textcolor(4); textbackground(1); } else
			if(option==5) { textcolor(14); textbackground(5); }
				else { textcolor(15); textbackground(6); }    /* option = 6 */

	gotoxy(5, 15);
	cprintf("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"
			"ÄÄÄÄÄÄÄÄÄÄ¿");
	for(i=0; i<7; i++)
	{	gotoxy(5, 16+i);
		cprintf("³                                                        "
				"              ³");
	}
	if(option==3) gotoxy(5, 16+i); else gotoxy(5, 15+i);
	cprintf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"
			"ÄÄÄÄÄÄÄÄÄÄÙ");
	i = 15;
	if(option == 3)
	{	textcolor(9); gotoxy(25, ++i); cprintf("Screen background patterns table");
		textcolor(2);
		gotoxy(10, ++i); cprintf("0  solid, optional color           "
								 " 6  light backslashes \\\\\\ ");
		gotoxy(10, ++i); cprintf("1  solid color                     "
								 " 7  thin cross hatching");
		gotoxy(10, ++i); cprintf("2  thick horizontal lines -----    "
								 " 8  thick cross hatching");
		gotoxy(10, ++i); cprintf("3  thin diagonal lines ///         "
								 " 9  interleaving lines");
		gotoxy(10, ++i); cprintf("4  thick diagonal lines ///        "
								 "10  widely spaced dots");
		gotoxy(10, ++i); cprintf("5  thick diagonal backslashes \\\\\\  "
								 "11  closely spaced dots");
	} else
	{   if(option==4) textcolor(6); else
			if(option==5) textcolor(12); else textcolor(10);
		gotoxy(36, ++i); cprintf("Color list");
		if(option==4) textcolor(5); else
			if(option==5) textcolor(7); else textcolor(12);
		gotoxy(27, ++i); cprintf("Press [?] to see the colors");
		if(option==4) textcolor(3); else
			if(option==5) textcolor(1); else textcolor(13);
		gotoxy(8, ++i);	cprintf("0  black      4  red         "
								" 8  darkgray        12  lightred");
		gotoxy(8, ++i);	cprintf("1  blue       5  magenta     "
								" 9  lightblue       13  lightmagenta");
		gotoxy(8, ++i);	cprintf("2  green      6  brown       "
								"10  lightgreen      14  yellow");
		gotoxy(8, ++i);	cprintf("3  cyan       7  lightgray   "
								"11  lightcyan       15  white");
	}

	textbackground(backgr_color_for_parameter_sel);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_type_selection()					//
//	polynomial_choosing()						//
//	free_form_function_choosing()					//
//	operators_and_math_func_table()					//
//	parameters_selection()						//
//	OY_axis_unit_length()				        	//
//	preliminary_analysis_of_chars()					//
//                                                                      //
//			Program abandonment window in text mode 	//
//									//
//			contradictory_sentences(hop_count)              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void whether_to_exit_the_program(void)
{   int m, mm, mmm=1;
	char m_ch1, m_ch2;

	if(option == 0) textbackground(3); else textbackground(2);
	textcolor(1); gotoxy(left, top);
	cprintf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	for(m=1; m<6; m++)
	{	gotoxy(left, top+m);
		cprintf("º                                   º");
	}
	gotoxy(left, top+m);
	cprintf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	textcolor(14); gotoxy(left+11, top+2); cprintf("EXIT THE PROGRAM");
	textcolor(11); gotoxy(left+6, top+4); cprintf("Yes                  No ");

	do
	{   mm = fmod(hop_count, 2);
		textcolor(11); textbackground(10); gotoxy(2, 25);
		contradictory_sentences(hop_count);
		if(mm == 0)
		{	textcolor(11); textbackground(2);
			gotoxy(left+26, top+4); cprintf(" Yes ");
			textbackground(4); gotoxy(left+6, top+4);
			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* defined in getch(): #define KEY_RIGHT 77 */
						if( m_ch2 == 77 ) { hop_count++; break; }
		// It produces a 'warning' -->  if( (m_ch2 = getch()) == 77 ) { hop_count++; break; }
					}
					else
					{	if( m_ch1 == 13 ) { mmm = 0; break; }
						else
							if( m_ch1 == 9 ) { hop_count++;	break; }
					}
				textcolor(1); cprintf(" No  \b\b\b"); delay(100);
				printf("\b\b");
				textcolor(9); cprintf(" No  \b\b\b"); delay(100);
				printf("\b\b");
				if(m > 8) m = 0;
			}
		} else
		{	textcolor(11); textbackground(2);
			gotoxy(left+6, top+4); cprintf(" No  ");
			textbackground(4); gotoxy(left+26, top+4);

			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* defined in getch(): #define KEY_LEFT 75 */
						if( m_ch2 == 75 ) { hop_count++; break; }
		// It produces a 'warning' -->  if( (m_ch2 = getch()) == 75 ) { hop_count++; break; }
					}
					else
					{	if( m_ch1 == 13 ) exit(1);
						else
							if( m_ch1 == 9 ) { hop_count++; break; }
					}
				textcolor(1); cprintf(" Yes \b\b\b"); delay(100);
				printf("\b\b");
				textcolor(9); cprintf(" Yes \b\b\b"); delay(100);
				printf("\b\b");
				if(m > 8) m = 0;
			}
		}
	if(hop_count == 21) hop_count = 0;
	} while(mmm);
	puttext(left, top, right, bottom, buff);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	whether_to_exit_the_program()					//
//                                                                      //
//	    A set of sentences for the word 'Yes' and for the word 'No'	//
//	    for the module 'whether_to_exit_the_program();'		//
//									//
//////////////////////////////////////////////////////////////////////////
void contradictory_sentences(int hop_count)
{   switch(hop_count)
	{	case 0 : cprintf("         This is no time for jokes! Why would you leave this program?         "); break;
		case 1 : cprintf("    Do something else and stop wasting your time with this crazy program.     "); break;
		case 2 : cprintf("   Explore the possibilities of this program and develop your math skills!    "); break;
		case 3 : cprintf("  Have you really done everything you planned for today? Make sure of this.   "); break;
		case 4 : cprintf(" It is me, your program, I am your friend, so stay with me and your computer. "); break;
		case 5 : cprintf("       Did you wash the dishes after eating? If not, press [ENTER] now.       "); break;
		case 6 : cprintf("   Why do that if there can be nothing more interesting than this program.    "); break;
		case 7 : cprintf("Do not you know that there are greater pleasures than looking at the computer."); break;
		case 8 : cprintf("I am the only one in this world that never holds a grudge against you, so stay"); break;
		case 9 : cprintf(" Turn off the computer and check if your aunt has not came with gifts for you."); break;
		case 10: cprintf(" Only I never shout at you, so why are you running away from me? Your program."); break;
		case 11: cprintf("             It would be better if you start doing your homework.             "); break;
		case 12: cprintf("If you left me, you would condemn yourself to the mercy of mom, dad and school"); break;
		case 13: cprintf("      When mommy calls, you have to listen to her. Exit the program now.      "); break;
		case 14: cprintf("Don't be a slave to other people's preferences and thoughts. It's your choice!"); break;
		case 15: cprintf("             Have you forgotten about your basic household duties?            "); break;
		case 16: cprintf("   I would feel disappointed if you abandoned me now. It's me, your program.  "); break;
		case 17: cprintf("       There is a chance to press the [ENTER] key - do it immediately!        "); break;
		case 18: cprintf("    I don't think you will do that to me. It's me, your computer program.     "); break;
		case 19: cprintf("  Exit the program now, because if you don't do it, you'll see what happens!  "); break;
		case 20: cprintf("       Something is rotten in Poland - do programming, ignore politics.       "); break;
		default: cprintf("                                                                              ");
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	introduction()                                                 	//
//	introduction_graphics()						//
//	function_menu()							//
//                                                                      //
//			'Exit the program' window in graphical mode	//
//									//
//////////////////////////////////////////////////////////////////////////
void whether_to_exit_the_program_gr(void)
{   int m, mm, mmm=1;
	char m_ch1, m_ch2;
	int hop_count = 0;
	int exit_the_program_box[] = {left_gr, top_gr, right_gr, top_gr, right_gr, bottom_gr, left_gr, bottom_gr, left_gr, top_gr};

	setfillstyle(9, 2);
	fillpoly(5, exit_the_program_box);
	rectangle(left_gr+3, top_gr+3, right_gr-3, bottom_gr-3);
	setcolor(14);
	moveto(left_gr+28, top_gr+30);
	settextstyle(2, HORIZ_DIR, 7);
	outtext("  EXIT THE PROGRAM");
	setcolor(11);			  /* it is superfluous at this point */
	moveto(left_gr+47, top_gr+75);
	settextstyle(1, HORIZ_DIR, 3);
	outtext("No          Yes");
	do
	{   mm = fmod(hop_count, 2);
		if(mm == 0)
		{	setcolor(11); moveto(left_gr+195, top_gr+75);
			settextstyle(1, HORIZ_DIR, 3); outtext("Yes");
			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* defined in getch(): #define KEY_RIGHT 77 */
						if( m_ch2 == 77 ) { hop_count++; break; }
	// It produces a 'warning' -->  if( (m_ch2 = getch()) == 77 ) { hop_count++; break; }
					}
					else
					{	if( m_ch1 == 13 ) { mmm = 0; break; }
						else
							if( m_ch1 == 9 ) { hop_count++;	break; }
					}
					setcolor(14); moveto(left_gr+47, top_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("No ");
					delay(100);
					setcolor(13); moveto(left_gr+47, top_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("No ");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		{	setcolor(11); moveto(left_gr+47, top_gr+75);
			settextstyle(1, HORIZ_DIR, 3); outtext("No ");
			for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{       m_ch2 = getch(); /* defined in getch(): #define KEY_LEFT 75 */
						if( m_ch2 == 75 ) { hop_count++; break; }
		// It produces a 'warning' -->  if( (m_ch2 = getch()) == 75 ) { hop_count++; break; }
					}
					else
					{	if( m_ch1 == 13 ) exit(1);
						else
							if( m_ch1 == 9 ) { hop_count++; break; }
					}
					setcolor(14); moveto(left_gr+195, top_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("Yes");
					delay(100);
					setcolor(13); moveto(left_gr+195, top_gr+75);
					settextstyle(1, HORIZ_DIR, 3); outtext("Yes");
					delay(100);
					if(m > 8) m = 0;
			}
		}
	if(hop_count == 21) hop_count = 0;
	} while(mmm);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_type_selection()					//
//	polynomial_choosing()						//
//	free_form_function_choosing()					//
//	operators_and_math_func_table()					//
//	parameters_selection()						//
//	OY_axis_unit_length()				        	//
//	preliminary_analysis_of_chars()					//
//                                                                      //
//			'Help' window for the text mode	        	//
//									//
//////////////////////////////////////////////////////////////////////////
void help_non_gr(void)
{   int m;
	char another_character;

	gotoxy(15, 6); textcolor(8);
	if(page_number == 3) textbackground(0); else
		if(page_number == 4 || page_number == 5) textbackground(2); else
			textbackground(7);
	cprintf("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ HELP ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
	for(m=0; m<12; m++)
	{	gotoxy(15, 7+m);
	cprintf("³                                                  ³");
	}
	gotoxy(15, 7+m);
	cprintf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");

	if(page_number == 2) goto page_no_2; else
		if(page_number == 3) goto page_no_3; else
			if(page_number == 4) goto page_no_4; else
				if(page_number == 5) goto page_no_5; else
					goto page_no_1;
	page_no_1:
	page_number = 1;
	gotoxy(16, 7); cprintf(" This text is not available in the graphic image! ");
	gotoxy(16, 8); cprintf(" To exit this window, press the [ESC] key.        ");
	gotoxy(16, 9); cprintf("                                                  ");
	gotoxy(16,10); cprintf(" The program runs on any PC and requires 200kb of ");
	gotoxy(16,11); cprintf(" free memory.                                     ");
	gotoxy(16,12); cprintf(" This program is intended for all children        ");
	gotoxy(16,13); cprintf(" without any exception and its version in any     ");
	gotoxy(16,14); cprintf(" language can be easily accessed at any time      ");
	gotoxy(16,15); cprintf(" without restrictions and completely free of      ");
	gotoxy(16,16); cprintf(" charge.                                          ");
	gotoxy(16,17); cprintf(" If you find an error or have questions, you can  ");
	gotoxy(16,18); cprintf(" find me on Internet.                             ");
	gotoxy(39,19); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄ [Page Down] \b\b\b\b\b\b\b");
	character_entered = getch();
	goto switchboard;

	page_no_2:
	page_number = 2;
	gotoxy(16, 7); cprintf("          "); textcolor(5);
	 cprintf("Choosing a form of a function"); textcolor(8); cprintf("           ");
	gotoxy(16, 8); cprintf(" You can only select one function graph in one    ");
	gotoxy(16, 9); cprintf(" coordinate system. In both cases (Polynomial and ");
	gotoxy(16,10); cprintf(" free-form expression) it is allowed to write as  ");
	gotoxy(16,11); cprintf(" on a school board - with spaces, without unnece- ");
	gotoxy(16,12); cprintf(" ssary multiplication signs and brackets, and in  ");
	gotoxy(16,13); cprintf(" any letter case.                                 ");
	gotoxy(16,14); cprintf(" 'pi' is changed to 'ã', 'e' to base of ln().     ");
	gotoxy(16,15); cprintf(" Polynomial example:                              ");
	gotoxy(16,16); cprintf("  -12.03x^5 + 2xx - 50.33x + 1.1                  ");
	gotoxy(16,17); cprintf("  Example of free-form expression:                ");
	gotoxy(16,18); cprintf("  3.1ln(3x) - xsin(2x-cos(pix)) + pow(e-1.2,x) - x");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	character_entered = getch();
	goto switchboard;

	page_no_3:
	page_number = 3;
	gotoxy(16, 7); cprintf("                    "); textcolor(6);
	 cprintf("Polynomial"); textcolor(8); cprintf("                   ");
	gotoxy(16, 8); cprintf(" The allowed number size is in the range:         ");
	gotoxy(16, 9); cprintf("      (0.0000001 ; 1000000)                       ");
	gotoxy(16,10); cprintf(" By pressing the [<-] key you can correct a number");
	gotoxy(16,11); cprintf(" You cannot write more than 15 chars in a number. ");
	gotoxy(16,12); cprintf(" Then you can either delete the last digits with  ");
	gotoxy(16,13); cprintf(" [<--] or accept the number [ENTER].              ");
	gotoxy(16,14); cprintf(" Not writing a number as a power factor of x is   ");
	gotoxy(16,15); cprintf(" treated as 0 (zero), so the polynomial summand   ");
	gotoxy(16,16); cprintf(" is zero.                                         ");
	gotoxy(16,17); cprintf(" NOTE: Using high powers of x causes distortions  ");
	gotoxy(16,18); cprintf(" in the graph for x>25 and x<-25 of a few percent.");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	character_entered = getch();
	goto switchboard;

	page_no_4:
	page_number = 4;
	gotoxy(16, 7); cprintf("        "); textcolor(1);
	 cprintf("Free-form of algebraic expression"); textcolor(8); cprintf("         ");
	gotoxy(16, 8); cprintf("Write carefully based on the function table.      ");
	gotoxy(16, 9); cprintf("The syntax of math functions must be kept, inclu- ");
	gotoxy(16,10); cprintf("ding the name of the function. Correcting a long  ");
	gotoxy(16,11); cprintf("entry can be a difficult task, but you will have  ");
	gotoxy(16,12); cprintf("a preview of the not accepted expression.         ");
	gotoxy(16,13); cprintf("Do not write more than 70 characters in the expre-");
	gotoxy(16,14); cprintf("ssion; remember that the graph range is limited.  ");
	gotoxy(16,15); cprintf("Don't worry about the domain of a function - ana- ");
	gotoxy(16,16); cprintf("lysis of a function graph in the range seen on the");
	gotoxy(16,17); cprintf("graph screen will be available after drawing.     ");
	gotoxy(16,18); cprintf("Treat the numbers carefully: 4.9988 is usually 5. ");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	character_entered = getch();
	goto switchboard;

	page_no_5:
	page_number = 5;
	gotoxy(16, 7); cprintf("                      "); textcolor(4);
	 cprintf("Options"); textcolor(8); cprintf("                     ");
	gotoxy(16, 8); cprintf(" Be aware of the limited display capabilities and ");
	gotoxy(16, 9); cprintf(" errors of a few percentage points for x>25 and   ");
	gotoxy(16,10); cprintf(" x<-25 in the case of large or small numbers      ");
	gotoxy(16,11); cprintf(" (e.g. 0.0000001) that may appear as intermediate ");
	gotoxy(16,12); cprintf(" numbers in calculations.                         ");
	gotoxy(16,13); cprintf(" Both before and after making a drawing, you can  ");
	gotoxy(16,14); cprintf(" change options for the graphs you create.        ");
	gotoxy(16,15); cprintf(" You can always preview the colors [?], exit the  ");
	gotoxy(16,16); cprintf(" program [ESC], or read this modest text.         ");
	gotoxy(16,17); cprintf(" You will learn more from the program itself.     ");
	gotoxy(16,18); cprintf("                      Leszek Buczek - June, 1998. ");
	gotoxy(39,19); cprintf(" [Page Up] / [Page Down] \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	character_entered = getch();
	goto switchboard;

	page_no_6:
	page_number = 6;
	gotoxy(16, 7); cprintf("            "); textcolor(10);
	 cprintf("Something about the program"); textcolor(8); cprintf("           ");
	gotoxy(16, 8); cprintf(" This is the first version of the program 'PLOT'. ");
	gotoxy(16, 9); cprintf(" It is expected to appear in the next version:    ");
	gotoxy(16,10); cprintf("1. Improved 'pow()' functionality for a negative  ");
	gotoxy(16,11); cprintf("   base number,                                   ");
	gotoxy(16,12); cprintf("2. Possibility to select more than one function   ");
	gotoxy(16,13); cprintf("   in the same coordinate system,                 ");
	gotoxy(16,14); cprintf("3. Ability to treat function syntax freely:       ");
	gotoxy(16,15); cprintf("   a) 'kosinus' or 'cosinus' becomes 'cos',       ");
	gotoxy(16,16); cprintf("   b) lack of a parenthesis for a function means a");
	gotoxy(16,17); cprintf("      number, char. or next function as argument. ");
	gotoxy(16,18); cprintf("For the 3D plot of a function is the 'XYZ' program");
	gotoxy(39,19); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [Page Up] \b\b\b\b\b");
	character_entered = getch();

	switchboard:
	if(character_entered == 0)
	{	if( ( another_character = getch() ) == 81 )	/* next page */
		{   if(page_number == 1) goto page_no_2; else
				if(page_number == 2) goto page_no_3; else
					if(page_number == 3) goto page_no_4; else
						if(page_number == 4) goto page_no_5; else
							if(page_number == 5) goto page_no_6; else
							{	character_entered = getch();
								goto switchboard;
							}
		} else
			if( another_character == 73 )		/* previous page */
			{	if(page_number == 2) goto page_no_1; else
					if(page_number == 3) goto page_no_2; else
						if(page_number == 4) goto page_no_3; else
							if(page_number == 5) goto page_no_4; else
								if(page_number == 6) goto page_no_5; else
								{	character_entered = getch();
									goto switchboard;
								}
			} else
				{	character_entered = getch();
					goto switchboard;
				}
	} else
		if(character_entered != 27)
		{	character_entered = getch();
			goto switchboard;
		} else
			puttext(left-7, top-2, right+8, bottom+5, buff);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	introduction()							//
//	introduction_graphics()						//
//	function_graph_background()					//
//                                                                      //
//			'Help' window for graphical mode        	//
//									//
//////////////////////////////////////////////////////////////////////////
void help_gr(void)
{	int help_field_gr_box[] = { left_gr-30, top_gr-30, right_gr+30, top_gr-30,
	 right_gr+30, bottom_gr+30, left_gr-30, bottom_gr+30, left_gr-30, top_gr-30 };

	setfillstyle(11, 5);
	fillpoly(5, help_field_gr_box);
	rectangle(left_gr-27, top_gr-27, right_gr+27, bottom_gr+27);
	setcolor(13);
	moveto(left_gr+110, top_gr-30);
	settextstyle(8, HORIZ_DIR, 1);
	outtext("HELP");
	setcolor(9);
	settextstyle(2, HORIZ_DIR, 5);
	moveto(left_gr-10, top_gr);
	outtext("To continue running the program,");
	moveto(left_gr-10, top_gr+15);
	outtext("just press any key.");
	moveto(left_gr-10, top_gr+30);
	outtext("To exit the program - press [Esc].");
	moveto(left_gr-10, top_gr+45);
	outtext("If you have problems with the program,");
	moveto(left_gr-10, top_gr+60);
	outtext("let me know:");
	setcolor(12);
	settextstyle(7, HORIZ_DIR, 1);
	moveto(left_gr, top_gr+75);
	outtext("Leszek Buczek");
	moveto(left_gr, top_gr+95);
	outtext("2709 Pheasant Hollow Dr.");
	moveto(left_gr, top_gr+115);
	outtext("Plainsboro, NJ 08536");
	settextstyle(2, HORIZ_DIR, 5);
	moveto(left_gr, top_gr+140);
	outtext("tel.: (609)750-0098");
	setcolor(13);
	settextstyle(0, HORIZ_DIR, 1);
	moveto(left_gr+280, top_gr+157);
	outtext("Esc");
	do
	{   character_entered = getch();
		if(character_entered == 0) getch();
	} while(character_entered != 27);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	parameters_selection()						//
//                                                                      //
//			Graphic screen prepared for a function plot	//
//									//
//			graph_of_the_function()		        	//
//			help_gr()					//
//			function_menu()					//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void function_graph_background(void)
{	int driver = VGA, mode = VGAHI, errorcode;
	int maximum_square[] = {0, 0, XMAX-1, 0, XMAX-1, YMAX-5, 0, YMAX-5, 0, 0};

/*	driver = DETECT;*/
	initgraph(&driver, &mode, "c:\\TURBOC3\\bgi");  /*  "d:\\tc\\bgi");  */

	errorcode = graphresult();
	if(errorcode != grOk)
	{	printf("\nGraphics error (module 'function_graph_background'): %s\n", grapherrormsg(errorcode));
		printf("Press any key to enter the editor : ");
		getch();
		exit(1);
	}

	setfillstyle(backgr_pattern_number, backgr_color_number);
	fillpoly(5, maximum_square);
	setcolor(axes_color_number);
	line(10, YMAX/2, XMAX-10, YMAX/2);
	line(XMAX-18, YMAX/2-3, XMAX-10, YMAX/2);
	line(XMAX-18, YMAX/2+3, XMAX-10, YMAX/2);
	line(XMAX/2, YMAX-10, XMAX/2, 10);
	line(XMAX/2-3, 18, XMAX/2, 10);
	line(XMAX/2+3, 18, XMAX/2, 10);

	i = 1;
	while( (XMAX/2+i*unit_length_on_the_OX_axis) <= (XMAX-20) )
	{	line(XMAX/2+i*unit_length_on_the_OX_axis, YMAX/2+2, XMAX/2+i*unit_length_on_the_OX_axis, YMAX/2-2);
		i++;
	}
	i = 1;
	while( (XMAX/2-i*unit_length_on_the_OX_axis) >= 20 )
	{	line(XMAX/2-i*unit_length_on_the_OX_axis, YMAX/2+2, XMAX/2-i*unit_length_on_the_OX_axis, YMAX/2-2);
		i++;
	}
	i = 1;
	while( (YMAX/2-i*unit_length_on_the_OY_axis) >= 20 )
	{	line(XMAX/2-2, YMAX/2-i*unit_length_on_the_OY_axis, XMAX/2+2, YMAX/2-i*unit_length_on_the_OY_axis);
		i++;
	}
	i = 1;
	while( (YMAX/2+i*unit_length_on_the_OY_axis) <= (YMAX-20) )
	{	line(XMAX/2-2, YMAX/2+i*unit_length_on_the_OY_axis, XMAX/2+2, YMAX/2+i*unit_length_on_the_OY_axis);
		i++;
	}

	setcolor(0);
	settextstyle(2, HORIZ_DIR, 4);
	moveto(XMAX/2-8,YMAX/2-2); outtext("o");
	moveto(XMAX/2+unit_length_on_the_OX_axis-2, YMAX/2+2); outtext("1");

	if(unit_length_on_the_OX_axis <= 30)
	{	moveto(XMAX/2+unit_length_on_the_OX_axis*10-5, YMAX/2+2); outtext("10");
		moveto(XMAX/2-unit_length_on_the_OX_axis*10-11, YMAX/2+2); outtext("-10");
		if(unit_length_on_the_OX_axis <= 15)
		{	moveto(XMAX/2+unit_length_on_the_OX_axis*20-5, YMAX/2+2); outtext("20");
			moveto(XMAX/2-unit_length_on_the_OX_axis*20-11, YMAX/2+2); outtext("-20");
			if(unit_length_on_the_OX_axis == 10)
			{	moveto(XMAX/2+unit_length_on_the_OX_axis*30-5, YMAX/2+2); outtext("30");
				moveto(XMAX/2-unit_length_on_the_OX_axis*30-11, YMAX/2+2); outtext("-30");
			}
		}
	}
	if(unit_OY_length_reduction == 10)
	{	if(unit_length_on_the_OY_axis <= 220)
		{	moveto(XMAX/2-14, YMAX/2-unit_length_on_the_OY_axis-6); outtext("10");
			if(unit_length_on_the_OY_axis <= 22)
			{	moveto(XMAX/2-20, YMAX/2-unit_length_on_the_OY_axis*10-6); outtext("100");
				moveto(XMAX/2-26, YMAX/2+unit_length_on_the_OY_axis*10-6); outtext("-100");
				if(unit_length_on_the_OY_axis <= 11)
				{	moveto(XMAX/2-20, YMAX/2-unit_length_on_the_OY_axis*20-6); outtext("200");
					moveto(XMAX/2-26, YMAX/2+unit_length_on_the_OY_axis*20-6); outtext("-200");
					if(unit_length_on_the_OY_axis <= 7)
					{	moveto(XMAX/2-20, YMAX/2-unit_length_on_the_OY_axis*30-6); outtext("300");
						moveto(XMAX/2-26, YMAX/2+unit_length_on_the_OY_axis*30-6); outtext("-300");
						if(unit_length_on_the_OY_axis == 5)
						{	moveto(XMAX/2-20, YMAX/2-unit_length_on_the_OY_axis*40-6); outtext("400");
							moveto(XMAX/2-26, YMAX/2+unit_length_on_the_OY_axis*40-6); outtext("-400");
						}
					}
				}
			}
		}
	} else
	{	if(unit_length_on_the_OY_axis <= 220)
		{	moveto(XMAX/2-6, YMAX/2-unit_length_on_the_OY_axis-6); outtext("1");
			if(unit_length_on_the_OY_axis <= 22)
			{	moveto(XMAX/2-14, YMAX/2-unit_length_on_the_OY_axis*10-6); outtext("10");
				moveto(XMAX/2-20, YMAX/2+unit_length_on_the_OY_axis*10-6); outtext("-10");
				if(unit_length_on_the_OY_axis <= 11)
				{	moveto(XMAX/2-14, YMAX/2-unit_length_on_the_OY_axis*20-6); outtext("20");
					moveto(XMAX/2-20, YMAX/2+unit_length_on_the_OY_axis*20-6); outtext("-20");
					if(unit_length_on_the_OY_axis <= 7)
					{	moveto(XMAX/2-14, YMAX/2-unit_length_on_the_OY_axis*30-6); outtext("30");
						moveto(XMAX/2-20, YMAX/2+unit_length_on_the_OY_axis*30-6); outtext("-30");
						if(unit_length_on_the_OY_axis == 5)
						{	moveto(XMAX/2-14, YMAX/2-unit_length_on_the_OY_axis*40-6); outtext("40");
							moveto(XMAX/2-20, YMAX/2+unit_length_on_the_OY_axis*40-6); outtext("-40");
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

	graph_of_the_function();

	// the code below applies to the situation after making a plot
	do
	{	character_entered = getch();
		if(character_entered == 0)
		{ // calling_for_help = 0;
			if(getch() == 59)
			{ // calling_for_help = 1;
			image_size = imagesize(left_gr-30, top_gr-30, right_gr+30, bottom_gr+30);
			if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
			{	closegraph();
				printf("\nError (5): There is no space in the memory to store the image");
				printf("\nIts size = %u bytes is too large", image_size);
				printf("\nFree memory is only %u bytes\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(left_gr-30, top_gr-30, right_gr+30, bottom_gr+30, ptr_to_memory_allocation);
			help_gr();
			putimage(left_gr-30, top_gr-30, ptr_to_memory_allocation, COPY_PUT);
			farfree(ptr_to_memory_allocation);
			} else break;
		} else
		{	image_size = imagesize(left_gr, top_gr, right_gr, bottom_gr);
			if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
			{	closegraph();
				printf("\nError (6): There is no space in the memory to store the menu image\n");
				printf("\nIts size = %u bytes is too large", image_size);
				printf("\nFree memory is only %u bytes\n", coreleft() );
				getch();
				exit(1);
			}
			getimage(left_gr-160, top_gr+200, right_gr-220, bottom_gr+160, ptr_to_memory_allocation);
			function_menu();
		}
	} while(1);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_graph_background()					//
//                                                                      //
//	      Plotting the function with previously set parameters   	//
//									//
//			free_form_function();	                	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void graph_of_the_function(void)
{       float limit_of_reason;
	int m;
	int xx, yy, yy_previous;	     /* positions on the screen */
	int point_previous, point_before_previous; /* whether these points exist at all? */
	float y_previous, y_before_previous; /* actual previous points values */
	float summand;
	float OX_pixel_value;
	float unit_length_on_the_OY_axis_flo; /* introduced it to avoid rounding */
	float test;
	int point_flag = 0;	  /* for detecting any point on the screen */
	int previous_function_domain;

	/* put zero to the number of zeros, extrema and numbers related to the function domain */
	l_d = l_m_z = l_e_max = l_e_min = 0;

	if(polynomial_chosen)
	{ if(n > 7)
	  {	if(unit_length_on_the_OX_axis < 20) limit_of_reason = 1e+18;
		else if(unit_length_on_the_OX_axis < 35) limit_of_reason = 1e+16;
			else if(unit_length_on_the_OX_axis < 50) limit_of_reason = 1e+14;
				else if(unit_length_on_the_OX_axis < 150) limit_of_reason = 1e+12;
					else limit_of_reason = 1e+10;
	  } else
		if(n > 5)
		{	if(unit_length_on_the_OX_axis < 20) limit_of_reason = 1e+16;
			else if(unit_length_on_the_OX_axis < 35) limit_of_reason = 1e+14;
				else if(unit_length_on_the_OX_axis < 50) limit_of_reason = 1e+12;
					else if(unit_length_on_the_OX_axis < 150) limit_of_reason = 1e+11;
						else limit_of_reason = 1e+10;
		} else
		  if(n > 3)
		  {	if(unit_length_on_the_OX_axis < 20) limit_of_reason = 1e+14;
			  else if(unit_length_on_the_OX_axis < 35) limit_of_reason = 1e+12;
				  else if(unit_length_on_the_OX_axis < 50) limit_of_reason = 1e+11;
					  else if(unit_length_on_the_OX_axis < 150) limit_of_reason = 1e+10;
						  else limit_of_reason = 1e+9;
		  } else
			if(unit_length_on_the_OX_axis < 20) limit_of_reason = 1e+13;
			  else if(unit_length_on_the_OX_axis < 35) limit_of_reason = 1e+12;
				  else if(unit_length_on_the_OX_axis < 50) limit_of_reason = 1e+11;
					  else if(unit_length_on_the_OX_axis < 150) limit_of_reason = 1e+10;
						  else limit_of_reason = 1e+9;

	} else		/* for free-form function */
		limit_of_reason = 1e+18;

	OX_pixel_value = (float)1 / unit_length_on_the_OX_axis;
	unit_length_on_the_OY_axis_flo = (float)unit_length_on_the_OY_axis / unit_OY_length_reduction;

	setcolor(function_plot_color_number);
	problem_with_domain = 0;
	m = 0;

	point_previous = point_before_previous = 0;
	do
	{	x = (-310 + m) * OX_pixel_value;
		xx = 10 + m;
		terminate = 0;					 /* optimistic assumption */
		if(polynomial_chosen)
		{	y = summand = 0;
			for(l=1; l<n+2; l++)
			{   if(n-l+1 == 0) summand = w[l];	 /* to avoid "pow(0,0)" */
				else summand = w[l] * pow(x, n-l+1);
				y = y + summand;
			}
		} else                /* for free-form function */
		  { if(m == 1 && function_domain)
				d_p[l_d++] = 1234567;	/* imaginary initial number */
			if(m>0)
				if(function_domain) previous_function_domain = 1;
				else previous_function_domain = 0;
			if(!it_is_a_function) function_domain = 1;
			free_form_function();
		  }

/*pt.1*/if(terminate)
		{   if(m>0)
			{	if(previous_function_domain && !function_domain)
					d_k[l_d++] = x-OX_pixel_value;
				else if(!previous_function_domain && function_domain)
					d_p[l_d++] = x;
			}
			if(function_domain) previous_function_domain = 1;	else previous_function_domain = 0;
			point_previous = point_before_previous = 0; m++; continue;
		}
/*pt.2*/else if(y < -limit_of_reason || y > limit_of_reason) /* ignore that point */
			 {	if(m>0)
				{	if(previous_function_domain && !function_domain)
						d_k[l_d++] = x-OX_pixel_value;
					else if(!previous_function_domain && function_domain)
						d_p[l_d++] = x;
				}
				if(function_domain) previous_function_domain = 1; else previous_function_domain = 0;
				terminate = 1; point_previous = point_before_previous = 0;
				function_domain = 1;
				m++; continue;
			 }
		/* "test" - it is "yy" type float */
		test = -(y * unit_length_on_the_OY_axis_flo) + YMAX/2;
		/* There is a chance to draw, but only when there was a "previous point" */
		if(point_previous)
		{	/* check if the point extends beyond the screen but still exists */
			if( (test < 10) || (test > 470) )
			{	if(test < 10)
				/* now the point is above the screen, not necessarily far from it */
				{	if(yy_previous > 10 && yy_previous <= 470)/*before..*/
					 if(point_before_previous)/*..the point was on the screen..*/
/* increasing function */                  if(y_previous > y_before_previous)/*..or under it*/
					  { line(xx-1, yy_previous, xx, 10); point_flag = 1; }
					  else
					  { d_k[l_d++] = x-OX_pixel_value;
						function_domain = 0;
						point_previous = point_before_previous = 0;
					  }
					yy_previous = 10;
				}
				/* now the point is below the screen, not necessarily far from it */
				else
				{	if(yy_previous >= 10 && yy_previous < 470)/*before..*/
					 if(point_before_previous)/*..the point was on the screen..*/
/* decreasing function */                  if(y_previous < y_before_previous)/*..or above it*/
					  { line(xx-1, yy_previous, xx, 470); point_flag = 1; }
					  else
					  {	d_k[l_d++] = x-OX_pixel_value;
						function_domain = 0;
						point_previous = point_before_previous = 0;
					  }
					yy_previous = 470;
				}
			} else
			{	yy = (int)test;
			/* previously the point was somewhere - not necessarily on the screen...*/
			/* ...but now it is on the screen */
				if(yy >= 10 && yy <= 470)  /* the point is on the screen now */
				{	line(xx-1, yy_previous, xx, yy);
					point_flag = 1;
					yy_previous = yy;
				}
			}
			if(point_before_previous && l_e_max <= 12 && l_e_min <= 12)
			{ /* I added an equal sign below because the accuracy is not good */
				if( (y_before_previous <= y_previous) && (y < y_previous) )
				{	l_e_max++;              /* it is a maximum of the function */
					e_max[l_e_max] = y_previous;
					e_max_x[l_e_max] = x - OX_pixel_value;
				} else /* I added an equal sign below because the accuracy is not good */
					if(y_before_previous >= y_previous && y > y_previous)
					{	l_e_min++;	     /* it is a minimum of the functions */
						e_min[l_e_min] = y_previous;
						e_min_x[l_e_min] = x - OX_pixel_value;
					}
			}
			if( (polynomial_chosen || (function_domain && free_form_function_chosen)) && (l_m_z <= 12) &&
			 ((y_previous>0 && y<=0) || (y_previous<0 && y>=0)) )
			{	l_m_z++;        /* is the zero of the function */
				m_z[l_m_z] = x;	// - OX_pixel_value;
			}
			if(polynomial_chosen || (function_domain && free_form_function_chosen))
			{	point_before_previous = 1;
				y_before_previous = y_previous;
				y_previous = y;
			}
			m++;
			continue;
		} else
		/* So far there has been no point or it is a situation after "terminate" */
		{	if( (l_m_z <= 12) && (y==0) )
			{	l_m_z++;        /* is the zero of the function */
				m_z[l_m_z] = x;	// - OX_pixel_value;
			}
			point_previous = 1;
			yy = (int)test;
			if(yy > 470) yy = 470;
			else if(yy < 10) yy = 10;
			yy_previous = yy;
			point_before_previous = 0;	/* this is to be known */
			// y_before_previous  - does not exist here!
			y_previous = y;
			m++;
			// continue;
		}
		if(!polynomial_chosen && function_domain)
			if(m>0 && !previous_function_domain)
				d_p[l_d++] = x;  // -OX_pixel_value;
	} while(m < 620);
	if(l_d>0 && function_domain) d_k[l_d] = 7654321; /* imaginary ending number */
	settextstyle(2, HORIZ_DIR, 6);
	if(!point_flag)
	{	if(backgr_color_number == 1) setcolor(10); else setcolor(1);
		moveto(65, 450); outtext("Not a single graph point appeared "
					 "in the visible area. ");
	} else if(problem_with_domain)
		   {	if(backgr_color_number == 12) setcolor(1); else setcolor(12);
				moveto(60, 450); outtext("A certain interval of the graph "
							 "requires a complex plane.");
		   }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	graph_of_the_function()						//
//                                                                      //
//		     Calculation flow for the previously selected	//
//		     'free-form function'				//
//									//
//			inner_parenth_operations_test();                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void free_form_function(void)
{		/* There don't have to be mathematical functions here, but they can be here */
/*******************	PI / 2 == 1.570796310901;   **********************/
//	The numerical value of "x" must already be known here !!!
/*************************************************************************/
	strcpy(C,CF);			/* remember the original string */
	d_l_C = d_l = d_l_CF;
	inner_parenth_operations_test();
}

    /*------------------------------------------------------------------*
     *	This is a function adapted to the test that I gave up	        *
     *		 A[i] was replaced by C[i], d_l by d_l_C.		*
     *	At the same time, it leads to the calculation of expressions	*
     *	with mathematical functions -	                        	*
     *  - C, d_l and d_l_C strings are now with functions.              *
     *------------------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	free_form_function()				        	//
//                                                                      //
//  Calculation flow for an expression inside parentheses or    	//
//  when there are no parentheses at all                                //
//									//
//			math_function_calculation()              	//
//			remove_only_parentheses()		       	//
//			inner_parenth_operations()              	//
//			insert_number_into_the_string()           	//
//			error_found()			        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void inner_parenth_operations_test(void)  /* there may be no parentheses at all */
{	int m;
	it_is_comma = 0;

	do				  /* up to the bracketless entry */
	{
		number_of_bracket_open = 0;   operation_begins = 0;
		number_of_bracket_closed = 0; operation_ends = 0;
		if(it_is_comma == 2)
			it_is_comma = 0;
		k = 0;

		for(i=0; i<d_l_C; i++)
		{	if(k) break;	/* k!=0 means: there were parentheses and there was something inside them */
			is_there_any_operator_indic = 0;	/* I guess this should be put before "for" */
			if(C[i] == '(')
			{	number_of_bracket_open++;
				operation_begins = i+1;
			} else
				if(C[i] == ')')
				{	number_of_bracket_closed++;
					operation_ends = i-1;
				/* looking for a comma */
				for(m=operation_begins; m<=operation_ends; m++)
					if(C[m] == ',')
						if(it_is_comma == 1)
						{	it_is_comma = 2;	/* take the argument after the comma: either mod( ,*) or pow( ,*) */
							operation_begins = m+1;
							break;	/* I want it to come out of the innermost loop 'for' */
						} else
						{	it_is_comma = 1;	/* take the argument before the comma: either mod(*, ) or pow(*, ) */
							operation_ends = m-1;
							j = operation_begins;
							break;  /* I want it to come out of the innermost loop 'for', 2 lines below! */
						}
					for(m=operation_begins; m<=operation_ends; m++)
					{	if(C[m] == '+' || C[m] == '-' || C[m] == '*' ||
						   C[m] == '/')	is_there_any_operator_indic = 1;
						if(m>operation_begins && is_there_any_operator_indic) break;
						if(m==operation_begins && C[m] == '-') is_there_any_operator_indic = 0;
					}
					if(!is_there_any_operator_indic)
				{   if( (C[operation_begins-2] > 96 &&
					 C[operation_begins-2] < 123 &&
					 C[operation_begins-2] != 120 ) ||
					 C[operation_begins-1] == ',' )
					{   operations_on_function = 1;
						k = 0;
						for(i=operation_begins; i<=operation_ends; i++)
							D[k++] = C[i];
						D[k++] = '\0';
						d_l_D = k;  /* I don't think it's used anywhere */
						if(!it_is_comma && !terminate)
							math_function_calculation();
						else
						{	if(it_is_comma == 1) strcpy(D1,D);
							else if(it_is_comma == 2 && !terminate)
						math_function_calculation();
						operations_on_function = 0;
							}
					} else
						if(it_is_comma != 1)
							{   operations_on_function = 0;
								remove_only_parentheses();
							}
						break; /* IT LEAVES THE "FOR" LOOP AND ALSO THE "WHILE" LOOP*/
					}
					if(terminate) break;
					k = 0;
					if(number_of_bracket_open != 0)
					{	for(i=operation_begins; i<=operation_ends; i++)
							D[k++] = C[i];
						D[k++] = '\0';
						d_l_D = k;	  /* I don't think it's used anywhere */
						strcpy(A, D);
						inner_parenth_operations();
						if(terminate) break;
						insert_number_into_the_string();
					} else
						{   error_detector = 1;
							error_found();
						}
				}
		} /* end of "for" loop */
	} while( (number_of_bracket_open != 0 || i != d_l_C) && !terminate );

	/* there are no more parentheses here */
	if(!terminate)
	{	for(m=0; m<d_l_C; m++)
		{	if(C[m] == '+' || C[m] == '-' || C[m] == '*' || C[m] == '/')
				is_there_any_operator_indic = 1;
			if(m>0 && is_there_any_operator_indic) break;
			if(m==0 && C[m] == '-') is_there_any_operator_indic = 0;
		}
		strcpy(A, C);
		if(is_there_any_operator_indic)
			inner_parenth_operations();
		if(!is_there_any_operator_indic)
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

    /*--------------------------------------------------------------*
     *	This module for math functions replaces	                    *
     *	"remove_only_parentheses" for operations without functions. *
     *--------------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	inner_parenth_operations_test()			        	//
//                                                                      //
//	       Calculating the value of a single mathematical function	//
//				      ( pow(negative, any) is failing )	//
//									//
//			is_it_a_lack_of_calculations()		       	//
//                      error_found()			        	//
//			insert_number_into_the_string()           	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void math_function_calculation(void)
{   int m, mm;		  /* in this case it is the length of the name of the mathematical function */
	int b_o = 0;	  /* variable "lack_of_calculations" taken from "is_it_a_lack_of_calculations()" */

  if(it_is_comma)		/* mod(y1,y) or pow(y1,y) */
  {	operation_begins = j;	/* mod(D1,D) or pow(D1,D) */
	if(strcmp(&D1[0],"x") == 0) y1 = x;
	else if(strcmp(&D1[0],"-x") == 0) y1 = -x;
		 else { ptrD1 = D1; y1 = atof(ptrD1); }
	if(strcmp(&D[0],"x") == 0) y = x;
	else if(strcmp(&D[0],"-x") == 0) y = -x;
		else { ptrD = D; y = atof(ptrD); }
	if( it_is_mod && (C[operation_begins-2] == 'd' &&
		C[operation_begins-3] == 'o' && C[operation_begins-4] == 'm') )
	{	mm = 3;
		// there may be a problem with the domain of the function here
		y = fmod(y1,y);
		function_domain = 1;
	} else
	if( it_is_pow && (C[operation_begins-2] == 'w' &&
		C[operation_begins-3] == 'o' && C[operation_begins-4] == 'p') )
	{	mm = 3;
		if(y1 == 0 && y == 0) { b_o = 1; function_domain = 0; }
		else if(y1 < 0) { b_o = 1; problem_with_domain = 1; }// function_domain = 1; }
			 else { b_o = is_it_a_lack_of_calculations(); function_domain = 1; }
		if(b_o)
			terminate = 1;	// exponentiation result is too high (this program limitation)
		else { y = pow(y1,y); function_domain = 1; }
	} else
	{ // There should be some function here, but it turns out there is not
		error_detector = 2;
		error_found();
	}
  } else
  {	if(strcmp(&D[0],"x") == 0)
		y = x;
	else
	{	ptrD = D;
		y = atof(ptrD);
	}
	if( it_is_ln && (C[operation_begins-2] == 'n' &&
		C[operation_begins-3] == 'l') )
	{	mm = 2;
		if(y <= 0)
		{	terminate = 1; function_domain = 0; } // The natural logarithm of a number <= 0
		else { y = log(y); function_domain = 1; }
	} else
	if( it_is_lg && (C[operation_begins-2] == 'g' &&
		C[operation_begins-3] == 'l') )
	{	mm = 2;
		if(y <= 0)
		{	terminate = 1; function_domain = 0; } // The decimal logarithm of a number <= 0
		else { y = log10(y); function_domain = 1; }
	} else
	if( it_is_cos && (C[operation_begins-2] == 's' &&
		C[operation_begins-3] == 'o' && C[operation_begins-4] == 'c') )
	{	mm = 3;
		y = cos(y);
		function_domain = 1;
	} else
	if( it_is_acos && (C[operation_begins-2] == 's' &&
		C[operation_begins-3] == 'o' && C[operation_begins-4] == 'c' &&
		C[operation_begins-5] == 'a') )
	{	mm = 4;
		if(y < -1 || y > 1)
		{	terminate = 1; function_domain = 0; } // Arcus cosine of numbers either < -1 or > 1
		else { y = acos(y); function_domain = 1; }
	} else
	if( it_is_cosh && (C[operation_begins-2] == 'h' &&
		C[operation_begins-3] == 's' && C[operation_begins-4] == 'o' &&
		C[operation_begins-5] == 'c') )
	{	mm = 4;
		function_domain = 1;
		if(y < -35 || y > 35)
			terminate = 1; // Hyperbolic cosine of a number either < -35 or > 35 (this program limitation)
		else y = cosh(y);
	} else
	if( it_is_sin && (C[operation_begins-2] == 'n' &&
		C[operation_begins-3] == 'i' && C[operation_begins-4] == 's') )
	{	mm = 3;
		y = sin(y);
		function_domain = 1;
	} else
	if( it_is_asin && (C[operation_begins-2] == 'n' &&
		C[operation_begins-3] == 'i' && C[operation_begins-4] == 's' &&
		C[operation_begins-5] == 'a') )
	{	mm = 4;
		if(y < -1 || y > 1)
		{	terminate = 1; function_domain = 0; } // Arcus sine of a number either < -1 or > 1
		else { y = asin(y); function_domain = 1; }
	} else
	if( it_is_sinh && (C[operation_begins-2] == 'h' &&
		C[operation_begins-3] == 'n' && C[operation_begins-4] == 'i' &&
		C[operation_begins-5] == 's') )
	{	mm = 4;
		function_domain = 1;
		if(y < -35 || y > 35)
			terminate = 1; // Hyperbolic sine of a number either < -35 or > 35 (this program limitation)
		else y = sinh(y);
	} else
	if( it_is_tan && (C[operation_begins-2] == 'n' &&
		C[operation_begins-3] == 'a' && C[operation_begins-4] == 't') )
	{	mm = 3;
		y = tan(y);
		function_domain = 1;
	} else
	if( it_is_atan && (C[operation_begins-2] == 'n' &&
		C[operation_begins-3] == 'a' && C[operation_begins-4] == 't' &&
		C[operation_begins-5] == 'a') )
	{	mm = 4;
		y = atan(y);
		function_domain = 1;
	} else
	if( it_is_tanh && (C[operation_begins-2] == 'h' &&
		C[operation_begins-3] == 'n' && C[operation_begins-4] == 'a' &&
		C[operation_begins-5] == 't') )
	{	mm = 4;
		/* there are no limits here except for
		 *	 	x<=-10		tanh(x)=-1
		 *		x>= 10		tanh(x)= 1
		 */
		y = tanh(y);
		function_domain = 1;
	} else
	if( it_is_abs && (C[operation_begins-2] == 's' &&
		C[operation_begins-3] == 'b' && C[operation_begins-4] == 'a') )
	{	mm = 3;
		y = fabs(y);
		function_domain = 1;
	} else
	if( it_is_exp && (C[operation_begins-2] == 'p' &&
		C[operation_begins-3] == 'x' && C[operation_begins-4] == 'e') )
	{	mm = 3;
		function_domain = 1;
		if(y > 34)
			terminate = 1; // Exponent of "e" > 34 (this program limitation)
		else y = exp(y);
	} else
	if( it_is_sq && (C[operation_begins-2] == 'q' &&
		C[operation_begins-3] == 's') )
	{	mm = 2;
		if(y < 0)
		{	terminate = 1; function_domain = 0; } // Square root of a number < 0.0
		else { y = sqrt(y); function_domain = 1; }
	} else
	  { // There should be some function, but it turns out there is not
		error_detector = 2;
		error_found();
	  }
  }
  if(!terminate)
  {	insert_number_into_the_string();
	for(i=0; i<mm; i++)	 /* remove the function name before its parentheses */
	{	for(m=operation_begins-1-mm; m<=d_l_C; m++)
			C[m] = C[m+1];
		d_l_C--;
	}
  }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	math_function_calculation()					//
//                                                                      //
//		   Screening for sizes too large for pow() calculation	//
//			 (NOTE: Conditions for negative basis removed)	//
//									//
//////////////////////////////////////////////////////////////////////////
int is_it_a_lack_of_calculations(void)
{	int lack_of_calculations = 0;
	if(y1>=1000000000) lack_of_calculations=1;	else
	 if(y1>=100000000) { if(y<-1 || y>=2) lack_of_calculations=1; } else
	  if(y1>=1000000) { if(y<-1.2 || y>=2.5) lack_of_calculations=1; } else
	   if(y1>=100000) { if(y<-1.5 || y>=3) lack_of_calculations=1; } else
		if(y1>=10000) { if(y<-1.8 || y>=3.5) lack_of_calculations=1; } else
		 if(y1>=1000) { if(y<-2.1 || y>=5) lack_of_calculations=1; } else
		  if(y1>=100) { if(y<-3 || y>=7) lack_of_calculations=1; } else
		   if(y1>=10) { if(y<-4.5 || y>=15) lack_of_calculations=1; } else
			if(y1>=1) { if(y<-9 || y>=20) lack_of_calculations=1; } else
			 if(y1>=0.1) { if(y<-15 || y>=10) lack_of_calculations=1; } else
			  if(y1>=0.01) { if(y<-7 || y>=5) lack_of_calculations=1; } else
			   if(y1>=0.001) { if(y<-5 || y>=3) lack_of_calculations=1; } else
				if(y1>=0.0001) { if(y<-3.7 || y>=2.2) lack_of_calculations=1; } else
				 if(y1>=0.00001) { if(y<-2.9 || y>=1.8) lack_of_calculations=1; } else
				  if(y1>=0.000001) { if(y<-2.5 || y>=1.5) lack_of_calculations=1; } else
				   if(y1>=0.0000001) { if(y<-2.1 || y>=1.2) lack_of_calculations=1; } else
					if(y1<0.0000001) lack_of_calculations=1;
	return lack_of_calculations;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	inner_parenth_operations_test()			        	//
//	math_function_calculation()					//
//                                                                      //
//   Calculated numeric value is converted to a character value 	//
//   and inserted into the string					//
//									//
//////////////////////////////////////////////////////////////////////////
void insert_number_into_the_string(void)
{	int m, mm;
	char *ptr_y;
	int dec, sign, ndig = 20; /* ndig -> length of the number without dot and sign */
				  /* dec -> dot position (always to be inserted!) */
				  /* sign -> number sign. To be inserted only when "sign = 1"...*/
				  /*...(negative number) and it will be "-" right at the beginning but...*/
				  /*..."-" do not insert when it comes out 0.0000000 */

	/* 1. Enter the number into a string:	*/
	/*    a. Convert the number into a string */
	ptr_y = ecvt(y, ndig, &dec, &sign);
	ptr_y[ndig] = '\0';  // ptr_y - value before truncation

	mm = 0;
	if(dec > 0)
	{	for(i=ndig; i>=dec; i--) ptr_y[i+1] = ptr_y[i];
		ptr_y[++i] ='.';
		ndig++;
		if(ndig - i > 8)
			for(m=ndig; m>i+8; m--) ptr_y[m-1] = ptr_y[m];
		// ptr_y - after truncation
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
		// ptr_y(after truncation - number < 1)
	}
	if(sign)
		if(dec > -7)
		{	d_l = strlen(ptr_y);
			for(m=d_l; m>=0; m--) ptr_y[m+1] = ptr_y[m];
			ptr_y[0] = '-';
		}

	/*    b. Find the length of this - not a number but - a string */
	d_l = strlen(ptr_y);

	/*    c. Eliminate the contents of the substring previously */
	/*       operated on in the string "C" */
	for(i=0; i<=(operation_ends-operation_begins); i++)
	{	for(m=operation_begins; m<=d_l_C; m++)
			C[m] = C[m+1];
		d_l_C--;
	}

	/*    d. Insert the resulting string "ptr_y" into the string "C" */
	mm = 0;
	for(i=operation_begins; i<operation_begins+d_l; i++)
	{	for(m=d_l_C; m>=operation_begins+mm; m--)
			C[m+1] = C[m];
		d_l_C++;
		C[i] = ptr_y[mm++];
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	inner_parenth_operations_test()			        	//
//                                                                      //
//   There is only a number or 'x' in the parentheses, so only the	//
//   parentheses will be removed					//
//									//
//////////////////////////////////////////////////////////////////////////
void remove_only_parentheses(void)
{   int m;

	for(m=operation_begins-1; m<=d_l_C; m++) C[m] = C[m+1];
	d_l_C--;	/* "operation_ends" will move 1 place forward */
	for(m=operation_ends; m<=d_l_C; m++) C[m] = C[m+1];
	d_l_C--;
	// the string "C" is after removing the parentheses here
	number_of_bracket_open--;
	number_of_bracket_closed--;
}

   /********************************************************************
    *------------------------------------------------------------------*
    *		      	    Computational process		       *
    *------------------------------------------------------------------*
    ********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	inner_parenth_operations_test()			        	//
//                                                                      //
//	 Calculations between numbers that may include the symbol 'x'.	//
//       There are no parentheses here and therefore no functions.      //
//       Operators are +, -, * and /                            	//
//									//
//			result_of_a_simple_operation(aa, bb)       	//
//			error_found()			        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void inner_parenth_operations(void)
{   d_l = strlen(A);
	indicator=0;

	while(d_l)	    /* until the string length decreases to zero */
	{   if(indicator >2)
		{	aa = result_of_a_simple_operation(aa, bb);
			indicator=1;
		} else
		{	decrease_d_l = 0;
			indicator++;
			ptrA = A;
			if(atof(ptrA) == 0 && A[0] == 'x')   /* if it is "x"... */
			{	x_found = 1;
				decrease_d_l++;
				if(indicator == 1) aa = x; else if(indicator == 3) bb = x;
				for(k=0; k<d_l; k++) A[k] = A[k+1];
/*******************************************************************/
			} else
				if(atof(ptrA) == 0 && A[0] == '-' && A[1] == 'x' && indicator == 1)
				{	x_found = 1;
					if(indicator == 1) aa = -x; else if(indicator == 3) bb = -x;
					for(i=0; i<2; i++)
					{	decrease_d_l++;
						for(k=0; k<d_l; k++) A[k] = A[k+1];
					}
/*******************************************************************/
			} else
				if(atof(ptrA) == 0 && indicator != 2 )
				{	if(indicator == 1) aa = 0; else bb = 0;
					do
					{   for(k=0; k<d_l; k++) A[k] = A[k+1];
						decrease_d_l++;
					    // Here it should be remove 0 or 0.00 or -0.00 etc
					} while( A[0] == 46 || A[0] == 48 );
				} else
					if(atof(ptrA) != 0 && indicator != 2) /*...if it is a number...*/
					{	a = atof(ptrA);
						if(indicator == 1) aa = a; else bb = a;
						do
						{   for(k=0; k<d_l; k++) A[k] = A[k+1];
							decrease_d_l++;
						} while( A[0] == 46 || (A[0] >= 48 && A[0] <= 57) );
					} else	/*...finally it is an operator... */
						if(indicator == 2)
						{ if(A[0] == '+') addition = 1; else
						   if(A[0] == '-') subtraction = 1; else
							if(A[0] == '*') multiplication = 1; else
							 if(A[0] == '/') division = 1; else
							  { error_detector = 3;
								error_found();
							  }
						  decrease_d_l++;
						  for(k=0; k<d_l; k++) A[k] = A[k+1];
						}
		d_l = d_l - decrease_d_l;
		}
	}	/* end of main "while" loop */

	result_of_a_simple_operation(aa, bb);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	inner_parenth_operations()					//
//                                                                      //
//   Calculations between numbers that may include the symbol 'x'.	//
//   There are no parentheses here and therefore no functions.  	//
//   Operators are +, -, * and /                                        //
//									//
//			error_found()			        	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
float result_of_a_simple_operation(float aa, float bb)
{	if(addition) yy = aa + bb; else
	 if(subtraction) yy = aa - bb; else
	  if(multiplication) yy = aa * bb; else
	   if(division)
	   {    if(bb == 0)
			{	terminate = 1; function_domain = 0; }
			else
				yy = aa / bb;
		} else
		{   error_detector = 4;
			error_found();
		}

	y = yy;
	addition = subtraction = multiplication = division = 0;

	return y;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_graph_background()					//
//                                                                      //
//		Menu for 4 cases:  1. Function analysis	        	//
//				   2. Changing options	        	//
//				   3. Another graph	        	//
//				   4. Exit the program          	//
//			(this is the state after plotting the function)	//
//									//
//			function_analysis()				//
//			parameters_selection()		        	//
//			function_type_selection()               	//
//			whether_to_exit_the_program_gr()	       	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void function_menu(void)
{   int m, mm, mmm=1;
	char m_ch1, m_ch2;
	int hop_count = 0;
	int menu_box[] = { left_gr-160, top_gr+200, right_gr-220, top_gr+200,
			    right_gr-220, bottom_gr+160, left_gr-160, bottom_gr+160,
			    left_gr-160, top_gr+200 };

	setfillstyle(6, 7);	/* you can replace 7 with 8 - it will be more delicate */
	fillpoly(5, menu_box);
	setcolor(14);
	moveto(left_gr-140, top_gr+210);
	settextstyle(2, HORIZ_DIR, 6);
	outtext("Function analysis");
	moveto(left_gr-140, top_gr+230);
	outtext("Changing options");
	moveto(left_gr-140, top_gr+250);
	outtext("Another graph");
	moveto(left_gr-140, top_gr+270);
	outtext("Exit the program");
	do
	{   mm = fmod(hop_count+20, 4);
		if(mm == 0)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )  /* defined in getch(): #define KEY_DOWN  80  */
					{	if( (m_ch2 = getch()) == 80 ) { hop_count++; break; }
						else                  /* defined in getch(): #define KEY_UP  72  */
							if( m_ch2 == 72 ) { hop_count--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { hop_count++; break; }
					}
					setcolor(13); moveto(left_gr-140, top_gr+210);
					outtext("Function analysis");
					delay(100);
					setcolor(14); moveto(left_gr-140, top_gr+210);
					outtext("Function analysis");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		if(mm == 1)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{	if( (m_ch2 = getch()) == 80 ) { hop_count++; break; }
						else                      /* 72 arrow up */
							if( m_ch2 == 72 ) { hop_count--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { hop_count++; break; }
					}
					setcolor(13); moveto(left_gr-140, top_gr+230);
					outtext("Changing options");
					delay(100);
					setcolor(14); moveto(left_gr-140, top_gr+230);
					outtext("Changing options");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		if(mm == 2)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{	if( (m_ch2 = getch()) == 80 ) { hop_count++; break; }
						else                      /* 72 arrow up */
							if( m_ch2 == 72 ) { hop_count--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { hop_count++; break; }
					}
					setcolor(13); moveto(left_gr-140, top_gr+250);
					outtext("Another graph");
					delay(100);
					setcolor(14); moveto(left_gr-140, top_gr+250);
					outtext("Another graph");
					delay(100);
					if(m > 8) m = 0;
			}
		} else
		if(mm == 3)
		{	for(m=0; m<10; m++)
			{   if( kbhit() )
					if( (m_ch1 = getch()) == 0 )
					{	if( (m_ch2 = getch()) == 80 ) { hop_count++; break; }
						else                      /* 72 arrow up */
							if( m_ch2 == 72 ) { hop_count--; break; }
					}
					else
					{   if( m_ch1 == 27 ) { mmm = 0; mm = 4; break; }
						else
							if( m_ch1 == 13 ) { mmm = 0; break; }
							else
								if( m_ch1 == 9 ) { hop_count++; break; }
					}
					setcolor(13); moveto(left_gr-140, top_gr+270);
					outtext("Exit the program");
					delay(100);
					setcolor(14); moveto(left_gr-140, top_gr+270);
					outtext("Exit the program");
					delay(100);
					if(m > 8) m = 0;
			}
		}
	if(hop_count == 40) hop_count = 20;
	else
		if(hop_count == 0) hop_count = 20;
	} while(mmm);

	if(mm == 0)
	{	putimage(left_gr-160, top_gr+200, ptr_to_memory_allocation, COPY_PUT);
		farfree(ptr_to_memory_allocation);
		trying_to_exit = 1;	// probably unnecessary
		image_size = imagesize(left_gr-30, top_gr-60, right_gr+30, bottom_gr+60);
		if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
		{	closegraph();
			printf("\nError (7): There is no space in the memory to store the image");
			printf("\nIts size = %u bytes is too large", image_size);
			printf("\nFree memory is only %u bytes\n", coreleft() );
			getch();
			exit(1);
		}
		getimage(left_gr-30, top_gr-60, right_gr+30, bottom_gr+60, ptr_to_memory_allocation);
		function_analysis();

		putimage(left_gr-30, top_gr-60, ptr_to_memory_allocation, COPY_PUT);
		farfree(ptr_to_memory_allocation);
	} else
	if(mm == 1)
	{       putimage(left_gr-160, top_gr+200, ptr_to_memory_allocation, COPY_PUT);
		farfree(ptr_to_memory_allocation);
		closegraph(); option = 1; parameters_selection();
	} else
	if(mm == 2)
	{	putimage(left_gr-160, top_gr+200, ptr_to_memory_allocation, COPY_PUT);
		farfree(ptr_to_memory_allocation);
		closegraph(); option = 0; function_type_selection();
	} else
	if(mm == 3)
	{	putimage(left_gr-160, top_gr+200, ptr_to_memory_allocation, COPY_PUT);
		farfree(ptr_to_memory_allocation);
		trying_to_exit = 1;
		image_size = imagesize(left_gr, top_gr, right_gr, bottom_gr);
		if( (ptr_to_memory_allocation = farmalloc(image_size) ) == NULL)
		{	closegraph();
			printf("\nError (8): There is no space in the memory to store the image");
			printf("\nIts size = %u bytes is too large", image_size);
			printf("\nFree memory is only %u bytes\n", coreleft() );
			getch();
			exit(1);
		}
		getimage(left_gr, top_gr, right_gr, bottom_gr, ptr_to_memory_allocation);
		whether_to_exit_the_program_gr();
		putimage(left_gr, top_gr, ptr_to_memory_allocation, COPY_PUT);
		farfree(ptr_to_memory_allocation);
	} else
	if(mm == 4)
	{	putimage(left_gr-160, top_gr+200, ptr_to_memory_allocation, COPY_PUT);
		farfree(ptr_to_memory_allocation);
	}
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_menu()							//
//                                                                      //
//	  Graph analysis in three windows:	                	//
//	    1. Domain of the function,					//
//	    2. Zeros of the function,					//
//	    3. Extrema of the function (the maxima are listed first).	//
//									//
//			window_of_function_analysis()		       	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void function_analysis(void)
{	int m, mm, mmm=1;
	char m_ch1, m_ch2;
	int hop_count = 0;

	do
	{   mm = fmod(hop_count, 3);
		if(mm == 0)
		{   window_of_function_analysis();
			setcolor(9);
			moveto(left_gr+52, top_gr-42);
			settextstyle(7, HORIZ_DIR, 1);
			outtext("Domain of the function");
			if(polynomial_chosen)
			{	gotoxy(23,9); printf("X î ");
				printf("(-®;+¯)");
			}
			else
			{	if(l_d)
				{	gotoxy(23,9); printf("X î ");
					if(d_p[0]==1234567) printf("(?;");
					else printf("(%.2f;", d_p[0]);
					for(m=1; m<=l_d; m++)
					{   if( !fmod(m,4) ) gotoxy(25,9+m/4);
						if( m > 27 )
						{	gotoxy(35,16); printf("...and more"); break; }
						else
						{	if( fmod(m,2) )
							{	if(d_k[m] == 7654321) printf("?)");
								else printf("%.2f)", d_k[m]);
							}
							else
							if(l_d!=m) printf(" v (%.2f;", d_p[m]);
						}
					}
					gotoxy(22,17); printf("Note: '(' may turn out to be '[' and");
					gotoxy(22,18); printf("')' ']'. A '?' means that the graph");
					gotoxy(22,19); printf("begins or ends with a number that");
					gotoxy(22,20); printf("already belongs to the function domain.");
				} else
				{	gotoxy(24,10); printf("I did not detect any graph points");
					gotoxy(24,11); printf("belonging to the domain of the");
					gotoxy(24,12); printf("function within the range of the");
					gotoxy(24,13); printf("ordinate axes seen on the screen.");
				}
			}
			setcolor(2);
			moveto(left_gr+180, top_gr+185);
			settextstyle(0, HORIZ_DIR, 1);
			outtext("Page Down / Esc");
			if( (m_ch1 = getch()) == 0 )    /* 81 - PgDn */
			{	if( (m_ch2 = getch()) == 81 ) hop_count++; }
			else
				if(m_ch1 == 27)	mmm = 0;
		} else
		if(mm == 1)
		{   window_of_function_analysis();
			setcolor(14);
			moveto(left_gr+58, top_gr-42);
			settextstyle(7, HORIZ_DIR, 1);
			outtext("Zeros of the function"); // this is just an example - there will be a table
			if(l_m_z == 0)
			{	gotoxy(23, 9); printf("I did not detect any zeros in");
				gotoxy(23,10); printf(" the range seen on the screen.");
			} else
				for(m=1; m<=l_m_z; m++)
				{   if(m > 11)
					{	gotoxy(35,20);
						printf("... and more");
						break;
					} else
					{	gotoxy(28, 8+m);
						if(m>9) printf("y = 0   for   X%d= %7.2f", m, m_z[m]);
						else printf("y = 0   for   X%d = %7.2f", m, m_z[m]);
					}
				}
			setcolor(2);
			moveto(left_gr+100, top_gr+185);
			settextstyle(0, HORIZ_DIR, 1);
			outtext("Page Down / Page Up / Esc");
			if( (m_ch1 = getch()) == 0 )    /* 81 - PgDn */
			{	if( (m_ch2 = getch()) == 81 ) hop_count++;
				else               	/* 73 PgUp */
					if( m_ch2 == 73 ) hop_count--;
			}
			else
				if(m_ch1 == 27)	mmm = 0;
		} else
		if(mm == 2)
		{   window_of_function_analysis();
			setcolor(15);
			moveto(left_gr+50, top_gr-42);
			settextstyle(7, HORIZ_DIR, 1);
			outtext("Extrema of the function");
			if(l_e_max == 0 && l_e_min == 0)
			{	gotoxy(23, 9); printf("I did not detect any extrema ");
				gotoxy(23,10); printf("in the range seen on the screen.");
			} else
			{	if(l_e_max)
					for(m=1; m<=l_e_max; m++)
					{   if(m > 11)
						{	gotoxy(35,20);
							printf("... and more");
							break;
						}
						else
						{	gotoxy(23, 8+m);
							printf("Max:   y = %7.2f  for  X = %7.2f", e_max[m], e_max_x[m]);
						}
					}
				if(l_e_min)
					for(m=1; m<=l_e_min; m++)
					{   if(m > 11 || l_e_max+m > 11)
						{	gotoxy(35,20);
							printf("... and more");
							break;
						}
						else
						{	gotoxy(24, 8+l_e_max+m);
							printf("Min:  y = %7.2f  for  X = %7.2f", e_min[m], e_min_x[m]);
						}
					}
			}
			setcolor(2);
			moveto(left_gr+196, top_gr+185);
			settextstyle(0, HORIZ_DIR, 1);
			outtext("Page Up / Esc");
			if( (m_ch1 = getch()) == 0 )
			{	if( (m_ch2 = getch()) == 73 ) hop_count--; }
			else
				if(m_ch1 == 27)	mmm = 0;
		}
	} while(mmm);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	function_analysis()						//
//                                                                      //
//		The same window for all three cases:	        	//
//			1. Domain of the function,			//
//			2. Zeros of the function,			//
//			3. Extrema of the function.			//
//									//
//////////////////////////////////////////////////////////////////////////
void window_of_function_analysis(void)
{	int function_analysis_box[] = { left_gr-30, top_gr-60, right_gr+30,
			top_gr-60, right_gr+30, bottom_gr+60, left_gr-30, bottom_gr+60,
			left_gr-30, top_gr-60 };

	setfillstyle(8, 8);
	fillpoly(5, function_analysis_box);
	rectangle(left_gr-27, top_gr-57, right_gr+27, bottom_gr+57);
	setcolor(11);
	moveto(left_gr+75, top_gr-50);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("FUNCTION ANALYSIS");
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//	inner_parenth_operations_test()		                	//
//	math_function_calculation()					//
//	inner_parenth_operations()					//
//	result_of_a_simple_operation(float aa, float bb)		//
//                                                                      //
//	Emergency solution when an unexpected error occurs      	//
//				(possibly when transmitting data).	//
//	In practice, such a report should not appear.                   //
//	The error will appear in one of the 4 cases:			//
//		1. problem with parentheses,				//
//		2. missing of expected function or not found any of     //
//                 function,                                            //
//		3. lack of expected operator between numbers,   	//
//		4. problem with operator symbols.			//
//									//
//			function_type_selection();              	//
//                                                                      //
//////////////////////////////////////////////////////////////////////////
void error_found(void)
{   int error_box[] = { left_gr-40, top_gr, right_gr+40, top_gr,
	 right_gr+40, bottom_gr, left_gr-40, bottom_gr, left_gr-40, top_gr };

	if(backgr_color_number == 4) setfillstyle(1, 0); else	setfillstyle(1, 4);
	fillpoly(5, error_box);
	rectangle(left_gr-37, top_gr+3, right_gr+37, bottom_gr-3);
	setcolor(14);
	moveto(left_gr+40, top_gr);
	settextstyle(8, HORIZ_DIR, 1);
	outtext("UNEXPECTED ERROR");
	setcolor(11);
	moveto(left_gr-25, top_gr+30);
	settextstyle(2, HORIZ_DIR, 5);
	if(error_detector == 1)
	{   moveto(left_gr-25, top_gr+30);
		outtext("I'm having trouble with parentheses. Their");
		moveto(left_gr-25, top_gr+45);
		outtext("number or position is not correct.");
	} else
	if(error_detector == 2)
	{   moveto(left_gr, top_gr+30);
		outtext("I expected a function, but I did not");
		moveto(left_gr, top_gr+45);
		outtext("find it.");
	} else
	if(error_detector == 3)
	{   moveto(left_gr, top_gr+30);
		outtext("I expected an operator, but I did not");
		moveto(left_gr, top_gr+45);
		outtext("find it.");
	} else
	if(error_detector == 4)
	{   moveto(left_gr-10, top_gr+30);
		outtext("I encountered incomprehensible operator");
		moveto(left_gr-10, top_gr+45);
		outtext("between numbers.");
	}
	setcolor(9);
	moveto(left_gr-25, top_gr+65);
	outtext("It is my fault or a data transmission error.");
	moveto(left_gr+115, top_gr+80);
	outtext("I am sorry. Your program.");
	setcolor(13);
	moveto(left_gr-25, top_gr+100);
	outtext("Please, write the expression again.");
	setcolor(2);
	moveto(left_gr+197, top_gr+128);
	settextstyle(0, HORIZ_DIR, 1);
	outtext("Press any key");

	character_entered = getch();
	if(character_entered == 0) getch();
	closegraph(); option = 0; function_type_selection();
}
