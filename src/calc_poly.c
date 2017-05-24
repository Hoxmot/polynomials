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

Stack stos;

long wiersz, kolumna;

struct ErrorInt {
	
	bool err;
	int n;
	
};
	
struct ErrorLong {
	
	bool err;
	long n;
	
};

struct ErrorUInt {
	
	bool err;
	unsigned n;
	
};

struct ErrorCoeff {
	
	bool err;
	poly_coeff_t n;
	
};

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


int main(){
	bool err;
	int in;
	wiersz = 1;
	kolumna = 1;
	in = getchar();
	while(in != EOF){
		err = false;
		/** @brief Wczytywanie współczynnika.
		 * Jest później przekazywany do PolyFromCoeff();
		 * */
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
		//Koniec F2
		/** @brief Przeprowadza 'ADD' lub 'AT x'.
		 * Sprawdza najpierw pierwszą lietrę, jeżeli jest A, to znaczy, że komenda to 'ADD' lub 'AT x"
		 * Następnie sprawdza drugą literę, wtedy ma pewnośc co do komendy
		 * Później do końca sprawdza, czy format jest podany poprawnie
		 * */
		//F3
		else if(i == 'A'){
			i = getchar();
			kolumna++;
			/** @brief Sprzwdzanie poprawności ADD.
			 * */
			//F3.1
			if(i == 'D'){
				//TODO
			}
			//Koniec F3.1
			/** @brief Sprawdzanie poprawności AT x.
			 * */
			// F3.2
			else if(i == 'T'){
				i = getchar();
				kolumna++;
				if(i != ' '){
					err = true;
					fprintf(stderr, "ERROR %ld WRONG COMMAND\N", wiersz);
					while(i != '\0' && i != EOF){
							i = getchar();
						}
					wiersz++;
					kolumna = 0;
				}
				else {
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
			//Koniec F3.2
			/** @brief Komunikat o błędzie.
			 * jako, że nie jest ot komenda 'ADD' ani 'AT x', to program wyrzuca komunikat o błędzie
			 * */
			 //F3.3
			else {
				err = true;
				fprintf(stderr, "ERROR %ld WRONG COMMAND\N", wiersz);
				while(i != '\0' && i != EOF){
						i = getchar();
					}
				wiersz++;
				kolumna = 0;
			}
			//Koniec F3.3
		}
		//Koniec F3
	}
}
