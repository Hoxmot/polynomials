#include <stdio.h>
#include "poly.h"

void monoPrint1(Mono m);

/** @brief Funkcja drukująca wielomian na standardowe wyjście.
 * @param[in] p : wielomian do druku
 * */
void polyPrint1(Poly p){
	if(PolyIsZero(&p)){
		printf("0");
	}
	else if(PolyIsCoeff(&p)){
		printf("%ld", p.coeff);
	}
	else {
		unsigned len = p.size;
		for(unsigned k = 0; k < len; k++){
			monoPrint1(p.arr[k]);
			if(k + 1 < len)
				printf("+");
		}
	}
}

/** @brief Funkcja drukująca jednomian na standardowe wyjście.
 * @param[in] i : jednomian do druku
 * */
void monoPrint1(Mono m){
	Poly p = m.p;
	poly_exp_t ex = m.exp;
	printf("(");
	polyPrint1(p);
	printf(",%d)", ex);
}
