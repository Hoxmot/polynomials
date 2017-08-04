/** @file
   Przydatne struktury, które ułatwiają pracę nad projektem

   @author Kamil Bladoszewski <kb392558@students.mimuw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-27
*/
/** @brief Struktura przechowywująca wartość typu int lub błąd.
 * */
 
#ifndef __STRUKTURY_H__
#define __STRUKTURY_H__
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "poly.h"
#include "stack.h"
 
typedef struct ErrorInt {
	
	bool err; ///< sprawdza czy jest błąd
	int n; ///< trzyma wartość
	
} ErrorInt;
	
/** @brief Struktura przechowywująca wartość typu long lub błąd.
 * */
typedef struct ErrorLong {
	
	bool err; ///< sprawdza czy jest błąd
	long n; ///< trzyma wartość
	
} ErrorLong;

/** @brief Struktura przetrzymująca wartość typu unsigned lub błąd.
 * */
typedef struct ErrorUInt {
	
	bool err; ///< sprawdza czy jest błąd
	unsigned n; ///< trzyma wartość
	
} ErrorUInt;

/** @brief Struktura przechowująca coeff lub błąd.
 * */
typedef struct ErrorCoeff {
	
	bool err; ///< sprawdza czy jest błąd
	poly_coeff_t n; ///< trzymana wartośc
	
} ErrorCoeff;

/** @brief Struktura przechowująca monomian lub błąd lub 0.
 * */
typedef struct ErrorMono {
	
	bool err; ///< sprawdza czy błąd
	bool zero; ///< sprawdza czy jest zerowy
	Mono monos; ///< trzyma monomian
	
} ErrorMono;

/** @brief Struktura przechowująca wielomian lub błąd.
 * */
typedef struct ErrorPoly {
	
	bool err; ///< sprawdza czy błąd
	Poly p; ///< trzyma wielomian
	
} ErrorPoly;

/** @brief Struktura przechowująca wykładnik lub błąd.
 * */
typedef struct ErrorExp {
	
	bool err; ///< sprawdza czy błąd
	poly_exp_t n; ///< trzyma wykładnik
	
} ErrorExp;

typedef struct MonoTab MonoTab;

/** @brief Struktura przechowująca jednomiany.
 * Będzie później służyć do zmiany ich w tablicę jednomianów, która zostanie przekazana PolyAddMonos
 * */
struct MonoTab {
	
	Mono m; ///< wartość
	MonoTab *next; ///< następny element
	int size; ///< liczba wielomianów

};

/** @brief Zwraca rozmiar, jaki powinna mieć tablica, aby zmieścić wszystkie monomiany zaczynając od tego.
 * */
int MonoSize(MonoTab *mt){
	return mt->size;
}

#endif /* __STRUKTURY_H__ */
