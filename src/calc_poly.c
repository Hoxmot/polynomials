/** @file
   Kalkulator

   @author Kamil Bladoszewski <kb392558@students.mimuw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-25
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "poly.h"
#include "stos.h"

Stack stos; ///< globalny stos

long wiersz; ///< globalna zmienna trzymająca numer wiersza
long kolumna; ///< globalna zmienna trzymająca numer kolumny

/** @brief Struktura przechowywująca wartość typu int lub błąd 
 * */
struct ErrorInt {
	
	bool err; ///< sprawdza czy jest błąd
	int n; ///< trzyma wartość
	
};
	
/** @brief Struktura przechowywująca wartość typu long lub błąd
 * */
struct ErrorLong {
	
	bool err; ///< sprawdza czy jest błąd
	long n; ///< trzyma wartość
	
};

/** @brief Struktura przetrzymująca wartość typu unsigned lub błąd
 * */
struct ErrorUInt {
	
	bool err; ///< sprawdza czy jest błąd
	unsigned n; ///< trzyma wartość
	
};

/** @brief Struktura przechowująca coeff lub błąd.
 * */
struct ErrorCoeff {
	
	bool err; ///< sprawdza czy jest błąd
	poly_coeff_t n; ///< trzymana wartośc
	
};

/** @brief Wczytywanie współczynnika.
 * Jest później przekazywany do PolyFromCoeff();
 * @param[in] i : obecnie wczytany znak
 * @return wartość do przekazania PolyFromCoeff() lub błąd
 * */
ErrorCoeff coeff(int i){
	ErrorCoeff odp;
	odp.err = false;
	odp.n = 0;
	bool ujemna = false;
	if(i == '-'){
		ujemna = true;
		i = getchar();
		kolumna++;
		if('0' <= i && i <= '9'){}
		else {
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\0' && i != EOF){
				i = getchar();
			}
			wiersz++;
			kolumna = 0;
			break;
		}
	}
	poly_coeff_t liczba = i - '0';
	poly_coeff_t l10;
	for(i = getchar(); '0' <= i && i <= '9'; i = getchar()){
		kolumna++;
		if(ujemna && liczba > 0)
			liczba *= -1;
		l10 = liczba * 10;
		if(l10 / 10 != liczba){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\0' && i != EOF){
				i = getchar();
			}
			wiersz++;
			kolumna = 0;
			break;
		}
		liczba = l10 + (i - '0');
		if(liczba < l10){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\0' && i != EOF){
				i = getchar();
			}
			wiersz++;
			kolumna = 0;
			break;
		}
	}
	odp.n = liczba;
	return odp;
}

ErrorLong readAt(int i){
	long liczba, l10;
					i = getchar();
					if(('0' <= i && i <= '9') || i == '-'){
						bool ujemna = false;
						if(i == '-'){
							ujemna = true;
							i = getchar();
							kolumna++;
							if('0' <= i && i <= '9'){}
							else {
								err = true;
								fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
								while(i != '\0' && i != EOF){
									i = getchar();
								}
								wiersz++;
								kolumna = 0;
								break;
							}
						}
						for(i = getchar(); '0' <= i && i <= '9'; i = getchar()){
							kolumna++;
							if(ujemna && liczba > 0)
								liczba *= -1;
							l10 = liczba * 10;
							if(l10 / 10 != liczba){
								err = true;
								fprintf(stderr, "ERROR %ld WRONG VALUE\n", wiersz);
								while(i != '\0' && i != EOF){
									i = getchar();
								}
								wiersz++;
								kolumna = 0;
								break;
							}
							liczba = l10 + (i - '0');
							if(liczba < l10){
								err = true;
								fprintf(stderr, "ERROR %ld WRONG VALUE\n", wiersz);
								while(i != '\0' && i != EOF){
									i = getchar();
								}
								wiersz++;
								kolumna = 0;
								break;
							}
						}
						//TODO
					}
					//TODO
				}
}


int main(){
	bool err;
	int in;
	wiersz = 1;
	kolumna = 1;
	in = getchar();
	while(in != EOF){
		//err = false;
		 //F1
		if(('0' <= i && i <= '9') || i == '-'){
			ErrorCoeff res;
			res = coeff(i);
			if(i != '\0' && i != EOF){
				res.err = true;
				fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
				while(i != '\0' && i != EOF){
						i = getchar();
				}
				wiersz++;
				kolumna = 0;
			}
			else if(!res.err){
				add(PolyFromCoeff(res.n);
				wiersz++;
				kolumna = 0;
			}
		}
		//Koniec F1
		/** @brief Parsowanie wielomianów.
		 * */
		//F2
		else if(i == '('){
			//TODO
		}
		else {
			ungetc(i, stdin);
			char input[10];
			scanf("%s", input);
			//TODO
		}
	}
}
