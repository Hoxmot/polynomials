/** @file
   Kalkulator

   @author Kamil Bladoszewski <kb392558@students.mimuw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-27
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "poly.h"
#include "stack.h"
#include "struktury.h"

Stack stos; ///< globalny stos

long wiersz; ///< globalna zmienna trzymająca numer wiersza
long kolumna; ///< globalna zmienna trzymająca numer kolumny



/** @brief Wczytywanie współczynnika.
 * Jest później przekazywany do PolyFromCoeff();
 * Używany tylko do wczytywania współczynnika, który nie jest częścią większego wielomianu
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
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
	}
	poly_coeff_t liczba;
	poly_coeff_t l10;
	if(!ujemna)
		liczba = i - '0';
	else liczba = 0 - (i - '0');
	for(i = getchar(); '0' <= i && i <= '9'; i = getchar()){
		kolumna++;
		l10 = liczba * 10;
		if(l10 / 10 != liczba){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
		if(!ujemna)
			liczba = l10 + (i - '0');
		else liczba = l10 - (i - '0');
		if((liczba < l10 && !ujemna) || (liczba > l10 && ujemna)){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
	}
	kolumna++;
	if(i != '\n' && i != EOF){
		odp.err = true;
	 	fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
	 	while(i != '\n' && i != EOF){
			i = getchar();
		}
		return odp;
	}
	else {
		odp.n = liczba;
		return odp;
	}
}

/** @brief Funkcja dla komendy PolyAt(), która czyta wartość, którą należy podstawić.
 * Od punkcji coeff różni się zwracanymi komunikatami.
 * @param[in] i : spacja po AT
 * @return typ przechowujący informację o błędzie i ewentualną wartość
 * */
ErrorLong readAt(int i){
	ErrorLong odp;
	odp.err = false;
	long liczba, l10;
	i = getchar();
	kolumna++;
	if(('0' <= i && i <= '9') || i == '-'){
		bool ujemna = false;
		if(i == '-'){
			ujemna = true;
			i = getchar();
			kolumna++;
	 		if('0' <= i && i <= '9');
			else {
				odp.err = true;
				fprintf(stderr, "ERROR %ld WRONG VALUE\n", wiersz);
				while(i != '\n' && i != EOF){
					i = getchar();
				}
				return odp;
			}
		}
		if(!ujemna)
			liczba = i - '0';
		else liczba = 0 - (i - '0');
		for(i = getchar(); '0' <= i && i <= '9'; i = getchar()){
			kolumna++;
			l10 = liczba * 10;
			if(l10 / 10 != liczba){
				odp.err = true;
	  			fprintf(stderr, "ERROR %ld WRONG VALUE\n", wiersz);
				while(i != '\n' && i != EOF){
					i = getchar();
				}
				return odp;
			}
			if(!ujemna)
				liczba = l10 + (i - '0');
			else liczba = l10 - (i - '0');
			if((liczba < l10 && !ujemna) || (liczba > l10 && ujemna)){
				odp.err = true;
				fprintf(stderr, "ERROR %ld WRONG VALUE\n", wiersz);
				while(i != '\n' && i != EOF){
	 				i = getchar();
				}
				return odp;
			}
		}
		kolumna++;
		if(i != '\n' && i != EOF){
			odp.err = true;
		 	fprintf(stderr, "ERROR %ld WRONG VALUE\n", wiersz);
			while(i != '\n' && i != EOF){
					i = getchar();
			}
			return odp;
		}
		else {
			odp.n = liczba;
			return odp;
		}
	}
	else {
		odp.err = true;
		fprintf(stderr, "ERROR %ld WRONG VALUE\n", wiersz);
		while(i != '\n' && i != EOF){
			i = getchar();
		}
		return odp;
	}
}

/** @brief Funkcja wczytująca index dla PolyDegBy().
 * Wczytuje liczbę unsigned int
 * @param[in] i : spacja tuż po DEG_BY
 * @return index
 * */
ErrorUInt getIdx(int i){
	ErrorUInt eui;
	unsigned liczba, l10;
	i = getchar();
	kolumna++;
	if('0' <= i && i <= '9'){
		liczba = i - '0';
		for(i = getchar(); '0' <= i && i <= '9'; i = getchar()){
			kolumna++;
			l10 = liczba * 10;
			if(l10 / 10 != liczba){
				eui.err = true;
				fprintf(stderr, "ERROR %ld WRONG VARIABLE\n", wiersz);
				while(i != '\n' && i != EOF){
					i = getchar();
				}
				return eui;
			}
			else {
				liczba = l10 + (i - '0');
				if(liczba < l10){
					eui.err = true;
					fprintf(stderr, "ERROR %ld WRONG VARIABLE\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
					return eui;
				}
			}
		}
		kolumna++;
		if(i != '\n' && i != EOF){
			eui.err = true;
			fprintf(stderr, "ERROR %ld WRONG VARIABLE\n", wiersz);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return eui;
		}
		else {
			eui.n = liczba;
			return eui;
		}
	}
	else {
		eui.err = true;
		fprintf(stderr, "ERROR %ld WRONG VARIABLE\n", wiersz);
		while(i != '\n' && i != EOF){
			i = getchar();
		}
		return eui;
	}
}

/** @brief Wczytywanie współczynnika.
 * Jest później przekazywany do PolyFromCoeff();
 * Używane w trakcie korzystania z funkcji polyParse()
 * Od funkcji coeff() różni się znakami, które może przyjmować na koniec liczby
 * @param[in] i : obecnie wczytany znak; pierwszy znak współczynnika
 * @return współczynnik, który można przekazać do PolyFromCoeff();
 * */
ErrorCoeff parseCoeff(int i){
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
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
	}
	poly_coeff_t liczba;
	poly_coeff_t l10;
	if(!ujemna)
		liczba = i - '0';
	else liczba = 0 - (i -'0');
	for(i = getchar(); '0' <= i && i <= '9'; i = getchar()){
		kolumna++;
		l10 = liczba * 10;
		if(l10 / 10 != liczba){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
		if(!ujemna)
			liczba = l10 + (i - '0');
		else liczba = l10 - (i - '0');
		if((liczba < l10 && !ujemna) || (liczba > l10 && ujemna)){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
	}
	kolumna++;
	if(i != ','){
		odp.err = true;
	 	fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
	 	while(i != '\n' && i != EOF){
			i = getchar();
		}
		return odp;
	}
	else {
		odp.n = liczba;
		return odp;
	}
}

/** @brief Funkcja wczytująca wykładnik.
 * Wczytuje wykładnik, a następnie przekazuje monoParse();
 * @param[in] i : obecnie wczytany znak, pierwszy znak wykładnika
 * @return wykładnik
 * */
ErrorExp getExp(int i){
	ErrorExp odp;
	odp.err = false;
	odp.n = 0;
	poly_exp_t liczba = i - '0';
	poly_exp_t l10;
	for(i = getchar(); '0' <= i && i <= '9'; i = getchar()){
		kolumna++;
		l10 = liczba * 10;
		if(l10 / 10 != liczba){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
		liczba = l10 + (i - '0');
		if(liczba < l10){
			odp.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return odp;
		}
	}
	kolumna++;
	if(i != ')'){
		odp.err = true;
	 	fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
	 	while(i != '\n' && i != EOF){
			i = getchar();
		}
		return odp;
	}
	else {
		odp.n = 0;
		odp.n = liczba;
		return odp;
	}
}

ErrorPoly polyParse(int i, bool wew);

/** @brief Funkcja, która tworzy jednomian.
 * Jeśli pierwszym znakiem w monomianie jest '(', to znaczy, że współczynnikiem przy jednomianie jest wielomian
 * Jeśli pierwszym znakiem jest cyfra lub '-', to znaczy, że przy jednomianie jest współczynnik
 * @param[in] i : nawias otwierający jednomianu, który parsujemy
 * @return monomian
 * */
ErrorMono monoParse(int i){
	ErrorMono em;
	em.err = false;
	em.zero = false;
	i = getchar();
	kolumna++;
	if(i == '('){
		ErrorPoly ep;
		ep = polyParse(i, true);
		if(ep.err){
			em.err = true;
			return em;
		}
		else {
			i = getchar();
			kolumna++;
			if('0' <= i && i <= '9'){
				ErrorExp ee;
				ee = getExp(i);
				if(ee.err){
					em.err = true;
					return em;
				}
				else {
					if(PolyIsZero(&ep.p)){
						em.zero = true;
						return em;
					}
					else {
						em.monos = MonoFromPoly(&ep.p, ee.n);
						return em;
					}
				}
			}
			else {
				em.err = true;
				fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
				while(i != '\n' && i != EOF){
					i = getchar();
				}
				return em;
			}
		}
	}
	else if(('0' <= i && i <= '9') || i == '-'){
		ErrorCoeff ec;
		ec = parseCoeff(i);
		if(ec.err){
			em.err = true;
			return em;
		}
		else {
			Poly coe = PolyFromCoeff(ec.n);
			i = getchar();
			kolumna++;
			if('0' <= i && i <= '9'){
				ErrorExp ee;
				ee = getExp(i);
				if(ee.err){
					em.err = true;
					return em;
				}
				else {
					if(PolyIsZero(&coe)){
						em.zero = true;
						return em;
					}
					else {
						em.monos = MonoFromPoly(&coe, ee.n);
						return em;
					}
				}
			}
			else {
				em.err = true;
				fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
				while(i != '\n' && i != EOF){
					i = getchar();
				}
				return em;
			}
		}
	}
	else {
		em.err = true;
		fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
		while(i != '\n' && i != EOF){
			i = getchar();
		}
		return em;
	}
}

/** @brief Funkcja wczytująca wielomian niebędący współczynnikiem
 * Jeżeli jest to suma jednomianów, to sumuje je za pomocą PolyAddMonos()
 * Jeżeli jest to jeden jednomian, to zmiania go w wielomian za pomocą PolyAddMonos()
 * @param[in] i : pierwszy znak wielomianu, czyli '('
 * @param[in] wew : zmienna logiczna mówiąca, czy wielomian jest wewnątrz jakiegoś jednomianu. Jeśli tak, to po zamknięciu jego nawiasu jest przecinek. Jeśli nie, to koniec wiersz lub koniec pliku.
 * @return wielomian
 * */
ErrorPoly polyParse(int i, bool wew){
	ErrorPoly ep;
	ErrorMono em;
	bool z0 = true;
	ep.err = false;
	em = monoParse(i);
	if(em.err){
		ep.err = true;
		return ep;
	}
	else {
		if(!em.zero)
			z0 = false;
		i = getchar();
		kolumna++;
		if(i == '+'){
			MonoTab *mt, *mt2;
			mt = malloc(sizeof(struct MonoTab));
			mt->next = NULL;
			mt->size = 1;
			if(!z0)
				mt->m = em.monos;
			while(i == '+'){
				i = getchar();
				kolumna++;
				if(i == '('){
					em = monoParse(i);
					if(em.err){
						ep.err = true;
						return ep;
					}
					else if(!em.zero){
						if(z0){
							mt->m = em.monos;
							z0 = false;
						}
						else {
							mt2 = malloc(sizeof(struct MonoTab));
							mt2->next = mt;
							mt2->size = mt->size + 1;
							mt2->m = em.monos;
							mt = mt2;
							mt2 = NULL;
						}
						z0 = false;
					}
				}
				else {
					ep.err = true;
					fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
					return ep;
				}
				i = getchar();
				kolumna++;
			}
			if((!wew && (i == '\n' || i == EOF)) || (wew && i == ',')){
				if(z0){
					ep.p = PolyZero();
					return ep;
				}
				else {
					int len = mt->size;
					Mono mon[len];
					for(int k = 0; k < len; k++){
						mon[k] = mt->m;
						mt2 = mt;
						mt = mt->next;
						free(mt2);
					}
					ep.p = PolyAddMonos(len, mon);
					return ep;
				}
			}
			else {
				ep.err = true;
				fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
				while(i != '\n' && i != EOF){
					i = getchar();
				}
				return ep;
			}
		}
		else if((!wew && (i == '\n' || i == EOF)) || (wew && i == ',')){
			if(z0){
				ep.p = PolyZero();
				return ep;
			}
			else {
				Mono monos[1];
				monos[0] = em.monos;
				ep.p = PolyAddMonos(1, monos);
				return ep;
			}
		}
		else {
			ep.err = true;
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
			return ep;
		}
	}
}

void monoPrint(Mono m);

/** @brief Funkcja drukująca wielomian na standardowe wyjście.
 * @param[in] p : wielomian do druku
 * */
void polyPrint(Poly p){
	if(PolyIsZero(&p)){
		printf("0");
	}
	else if(PolyIsCoeff(&p)){
		printf("%ld", p.coeff);
	}
	else {
		unsigned len = p.size;
		for(unsigned k = 0; k < len; k++){
			monoPrint(p.arr[k]);
			if(k + 1 < len)
				printf("+");
		}
	}
}

/** @brief Funkcja drukująca jednomian na standardowe wyjście.
 * @param[in] i : jednomian do druku
 * */
void monoPrint(Mono m){
	Poly p = m.p;
	poly_exp_t ex = m.exp;
	printf("(");
	polyPrint(p);
	printf(",%d)", ex);
}

int main(){
	int i;
	wiersz = 1;
	kolumna = 1;
	i = getchar();
	while(i != EOF){
		if(('0' <= i && i <= '9') || i == '-'){
			ErrorCoeff res;
			res = coeff(i);
			if(!res.err){
				add(PolyFromCoeff(res.n));
			}
			//else został obsłużony przez coeff();
		}
		else if(i == '('){
			ErrorPoly ep;
			ep = polyParse(i, false);
			if(!ep.err){
				add(ep.p);
			}
			//else zostało obsłużone w polyParse
		}
		else if(('A' <= i && i <= 'Z') || ('a' <= i && i <= 'z')){
			ungetc(i, stdin);
			char input[10];
			scanf("%s", input);
			if(strcmp(input, "ADD") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e1, e2;
					e1 = pop();
					e2 = pop();
					if(e1.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else if(e2.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
						add(e1.odp);
					}
					else {
						Poly p1, p2;
						p1 = e1.odp;
						p2 = e2.odp;
						Poly res = PolyAdd(&p1, &p2);
						PolyDestroy(&p1);
						PolyDestroy(&p2);
						add(res);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "AT") == 0){
				i = getchar();
				kolumna++;
				if(i != ' '){
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
				else {
					ErrorLong el;
					el = readAt(i);
					if(!el.err){
						Error er;
						er = pop();
						if(er.czyBlad){
							fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
						}
						else {
							Poly res;
							res = PolyAt(&er.odp, el.n);
							PolyDestroy(&er.odp);
							add(res);
						}
					//else nic nie zwraca, bo błąd został już obsłużony w readAt();
					}
				}
			}
			else if (strcmp(input, "CLONE") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e;
					e = get();
					if(e.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						Poly p;
						p = e.odp;
						Poly res = PolyClone(&p);
						add(res);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "DEG") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e;
					e = get();
					if(e.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						Poly p;
						p = e.odp;
						poly_exp_t res = PolyDeg(&p);
						printf("%d\n", res);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "DEG_BY") == 0){
				i = getchar();
				if(i == ' '){
					ErrorUInt eui;
					eui = getIdx(i);
					if(!eui.err){
						poly_exp_t res;
						Error e;
						e = get();
						if(e.czyBlad){
							fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
						}
						else {
							res = PolyDegBy(&e.odp, eui.n);
							printf("%d\n", res);
						}
					}
					//else zostało obsłużone przez getIdx();
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "IS_COEFF") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e;
					e = get();
					if(e.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						bool x = PolyIsCoeff(&e.odp);
						printf("%d\n", x);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "IS_EQ") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e1, e2;
					e1 = get();
					e2 = get2();
					if(e1.czyBlad || e2.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						bool x;
						Poly p1, p2;
						p1 = e1.odp;
						p2 = e2.odp;
						x = PolyIsEq(&p1, &p2);
						printf("%d\n", x);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "IS_ZERO") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e;
					e = get();
					if(e.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						bool x = PolyIsZero(&e.odp);
						printf("%d\n", x);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "MUL") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e1, e2;
					e1 = pop();
					e2 = pop();
					if(e1.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else if(e2.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
						add(e1.odp);
					}
					else {
						Poly p1, p2;
						p1 = e1.odp;
						p2 = e2.odp;
						Poly res = PolyMul(&p1, &p2);
						PolyDestroy(&p1);
						PolyDestroy(&p2);
						add(res);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "NEG") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e1;
					e1 = pop();
					if(e1.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						Poly p;
						p = e1.odp;
						Poly res = PolyNeg(&p);
						PolyDestroy(&p);
						add(res);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "POP") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e;
					e = pop();
					if(e.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						Poly p = e.odp;
						PolyDestroy(&p);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "PRINT") == 0){
				i = getchar();
				kolumna++;
				if(i == '\n' || i == EOF){
					Error e;
					e = get();
					if(e.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else {
						polyPrint(e.odp);
						printf("\n");
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "SUB") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Error e1, e2;
					e1 = pop();
					e2 = pop();
					if(e1.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
					}
					else if(e2.czyBlad){
						fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", wiersz);
						add(e1.odp);
					}
					else {
						Poly p1, p2;
						p1 = e1.odp;
						p2 = e2.odp;
						Poly res = PolySub(&p1, &p2);
						PolyDestroy(&p1);
						PolyDestroy(&p2);
						add(res);
					}
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else if(strcmp(input, "ZERO") == 0){
				i = getchar();
				if(i == '\n' || i == EOF){
					Poly z = PolyZero();
					add(z);
				}
				else {
					fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
					while(i != '\n' && i != EOF){
						i = getchar();
					}
				}
			}
			else {
				fprintf(stderr, "ERROR %ld WRONG COMMAND\n", wiersz);
				while(i != '\n' && i != EOF){
					i = getchar();
				}
			}
		}
		else {
			fprintf(stderr, "ERROR %ld %ld\n", wiersz, kolumna);
			while(i != '\n' && i != EOF){
				i = getchar();
			}
		}
		i = getchar();
		wiersz++;
		kolumna = 1;
	}
	
	return 0;
}
