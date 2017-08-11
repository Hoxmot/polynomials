/** @file
   Interfejs klasy wielomianów

   @author Jakub Pawlewicz <pan@mimuw.edu.pl>, Kamil Bladoszewski <kb392558@students.mimuw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-04-24, 2017-05-14
*/

#include "poly.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

/** Typ współczynników wielomianu */
typedef long poly_coeff_t;

/** Typ wykładników wielomianu */
typedef int poly_exp_t;

void monoPrint(Mono *m);

/** @brief Funkcja drukująca wielomian na standardowe wyjście.
 * Stworzona specjalnie na potrzeby debugowania
 * @param[in] p : wielomian do druku
 * */
void polyPrint(Poly *p){
	if(PolyIsZero(p)){
		printf("0");
	}
	else if(PolyIsCoeff(p)){
		printf("%ld", p->val);
	}
	else {
		monoPrint(p->first);
	}
}

/** @brief Funkcja drukująca jednomian na standardowe wyjście.
 * Stworzona specjalnie na potrzeby debugowania
 * @param[in] i : jednomian do druku
 * */
void monoPrint(Mono *m){
	Poly p = m->p;
	poly_exp_t ex = m->exp;
	printf("(");
	polyPrint(&p);
	printf(",%d)", ex);
	if(m->next != NULL){
		printf("+");
		monoPrint(m->next);
	}
}

/**
 * @brief Tworzy wielomian, który jest współczynnikiem.
 * @param[in] c : wartość współczynnika
 * @return wielomian
 */
 Poly PolyFromCoeff(poly_coeff_t c){

    Poly a;
    a.first = NULL;
    a.val = c;
    return a;

}

/**
 * @brief Tworzy wielomian tożsamościowo równy zeru.
 * @return wielomian
 */
Poly PolyZero(){

    Poly a;
    a.first = NULL;
    a.val = 0;
    return a;

}

/**
 * @brief Tworzy jednomian `p * x^e`.
 * Przejmuje na własność zawartość struktury wskazywanej przez @p p.
 * @param[in] p : wielomian - współczynnik jednomianu
 * @param[in] e : wykładnik
 * @return jednomian `p * x^e`
 */
Mono MonoFromPoly(const Poly *p, poly_exp_t e){

    return (Mono) {.p = *p, .exp = e, .next = NULL};

}

/**
 * @brief Sprawdza, czy wielomian jest współczynnikiem.
 * @param[in] p : wielomian
 * @return Czy wielomian jest współczynnikiem?
 */
bool PolyIsCoeff(const Poly *p)
{
    if(p->first == NULL) ///< Jeśli nie posiada listy jednomianów, to jest współczynnikiem.
		return true;
	else return false; ///< Nie jest WPP.
}

/**
 * @brief Sprawdza, czy wielomian jest tożsamościowo równy zeru.
 * @param[in] p : wielomian
 * @return Czy wielomian jest równy zero?
 */
bool PolyIsZero(const Poly *p){

    if(p->first == NULL){
		if(p->val == 0)
			return true;
		else return false;
	}
	//TODO
	/*
	else {
		Mono *m;
		m = p->first;
		while(m != NULL){
			if(PolyIsZero(&m->p) == true){
				if(m->next == NULL)
					return true;
				else {
					m = m->next;
				}
			}
			else return false;
		}
	}
	*/
	return false;

}

void MonoDestroy(Mono *m);

/**
 * @brief Usuwa wielomian z pamięci.
 * @param[in] p : wielomian
 */
void PolyDestroy(Poly *p){

	if(p->first != NULL){
		MonoDestroy(p->first);
		free(p->first);
	}
	p->val = 0;
	p->first = NULL;

}

/**
 * @brief Usuwa jednomian z pamięci.
 * @param[in] m : jednomian
 */
void MonoDestroy(Mono *m){

	PolyDestroy(&m->p);
		m->exp = 0;
	if(m->next != NULL){
		MonoDestroy(m->next);
		free(m->next);
	}
	m->next = NULL;

}

Mono MonoClone(const Mono *m);

/**
 * @brief Robi pełną, głęboką kopię wielomianu.
 * @param[in] p : wielomian
 * @return skopiowany wielomian
 */
Poly PolyClone(const Poly *p){
	Poly p2;
	p2.val = p->val;
	if(p->first != NULL){
		p2.first = malloc(sizeof(struct Mono));
		*p2.first = MonoClone(p->first);
	}
	else p2.first = NULL;
	return p2;
}

/**
 * @brief Robi pełną, głęboką kopię jednomianu.
 * @param[in] m : jednomian
 * @return skopiowany jednomian
 */
Mono MonoClone(const Mono *m){
    Mono m2;
    m2.exp = m->exp;
    m2.p = PolyClone(&m->p);
    
    if(m->next != NULL){
    	m2.next = malloc(sizeof(struct  Mono));
		*m2.next = MonoClone(m->next);
    }
    else m2.next = NULL;
    return m2;
}

/** 
 * @brief Dodaje współczynnik do wielomiany
 * @param[in] p : wielomian
 * @param[in] x : współczynnik
 * @return wielomian z dodanym współczynnikiem
 * */
Poly PolyAddCoeff(const Poly *p, poly_coeff_t x){

	if(PolyIsCoeff(p)){
		return PolyFromCoeff(p->val + x);
	}

	Poly w;
	Mono *m, *curr, *prev;
	m = p->first;
	w.val = 0;
	w.first = malloc(sizeof(struct Mono));
	curr = w.first;
	prev = NULL;
	curr->exp = 0;
	curr-> next = NULL;
	while(m != NULL){
		if(m->exp == 0){
			curr->exp = m->exp;
			curr->next = NULL;
			curr->p = PolyAddCoeff(&m->p, x);
		 	if(PolyIsZero(&curr->p)){
		 		MonoDestroy(curr);
		 		free(curr);
		 		if(prev != NULL)
		 			prev->next = NULL;
		 		else 
		 			w.first = NULL;
		 	}
			return w;
		}
		else {
			curr->p = PolyClone(&m->p);
			curr->exp = m->exp;
		}
		m = m->next;
		prev = curr;
		curr = NULL;
		curr = malloc(sizeof(struct Mono));
		curr->exp = 0;
		curr->next = NULL;
		prev->next = curr;
	}
	curr->p = PolyFromCoeff(x);
	return w;

}

Poly PolyNeg(const Poly *p);

/**
 * @brief Dodaje dwa wielomiany.
 * @param[in] p : wielomian
 * @param[in] q : wielomian
 * @return `p + q`
 */
Poly PolyAdd(const Poly *p, const Poly *q){
	if(PolyIsZero(p))
		return PolyClone(q);

	if(PolyIsZero(q))
		return PolyClone(p);
	
	if(PolyIsCoeff(p)){
		return PolyAddCoeff(q, p->val);
	}
	
	if(PolyIsCoeff(q)){
		return PolyAddCoeff(p, q->val);
	}
	
	Poly w;
	Mono *curr, *prev, *pm, *qm;
	prev = NULL;
	curr = malloc(sizeof(struct Mono));
	curr->next = NULL;
	curr->exp = 0;
	w.first = curr;
	w.val = 0;
	pm = p->first;
	qm = q->first;
	while(pm != NULL && qm != NULL){
		if(pm->exp == qm->exp){
			curr->exp = pm->exp;
			curr->p = PolyAdd(&pm->p, &qm->p);
			pm = pm->next;
			qm = qm->next;
			if(PolyIsZero(&curr->p)){
				MonoDestroy(curr);
				continue;
			}
		}
		else if(pm->exp > qm->exp){
			curr->exp = pm->exp;
			curr->p = PolyClone(&pm->p);
			pm = pm->next;
		}
		else { //*pm->exp < *qm->exp
			curr->exp = qm->exp;
			curr->p = PolyClone(&qm->p);
			qm = qm->next;
		}

		prev = curr;
		curr = malloc(sizeof(struct Mono));
		curr->exp = 0;
		curr->next = NULL;
		prev->next = curr;
	}
	if(prev == NULL && pm == NULL && qm == NULL){
		free(curr);
		w.first = NULL;
	}
	else if(pm == NULL && qm != NULL){
		*curr = MonoClone(qm);
	}
	else if(qm == NULL && pm != NULL){
		*curr = MonoClone(pm);
	}
	else{
		free(curr);
		prev->next = NULL;
	}

	return w;
}

/** 
* @brief Porównuje dwa jednomiany
* @param[in] p : wskaźnik na pierwszy jednomian
* @param[in] q : wskaźnik na drugi jednomian
* @return liczba dodatnia (p > q), ujemna (p < q) lub zero (p = q)
*/
int cmp_mono(const void *p, const void *q){
    Mono *m1 = (Mono*) p;
    Mono *m2 = (Mono*) q;
    return m1->exp - m2->exp;
}

/**
 * @brief Sumuje listę jednomianów i tworzy z nich wielomian.
 * Przejmuje na własność zawartość tablicy @p monos.
 * @param[in] count : liczba jednomianów
 * @param[in] monos : tablica jednomianów
 * @return wielomian będący sumą jednomianów
 */
Poly PolyAddMonos(unsigned count, const Mono monos[]){
	//quick_sort(&monos, 0, count - 1);
	/*for(int i = 0; i < count; i++){
		Mono *tmp;
		tmp = &monos[i];
		assert(tmp != NULL);
	}*/
	qsort(monos, count, sizeof(struct Mono), &cmp_mono);
	Poly w, tmp;
	Mono *curr, *prev;
	w.first = NULL;
	w.val = 0;
	/*
	w.first = malloc(sizeof(struct Mono));
	w.val = 0;
	*w.first = monos[count - 1];
	curr = w.first;
	*/
	prev = NULL;
	Mono *m;
	for(int i = count - 1; i >= 0; --i){
		if(w.first != NULL){
			m = malloc(sizeof(struct Mono));
			*m = monos[i];
			if(curr->exp == m->exp){
				tmp = PolyAdd(&curr->p, &m->p);
				MonoDestroy(m);
				free(m);
				PolyDestroy(&curr->p);
				curr->p = tmp;
				if(PolyIsZero(&curr->p)){
					MonoDestroy(curr);
					free(curr);
					if(prev != NULL)
						curr = prev;
					else {
						w.first = NULL;
						curr = w.first;
						/*
						w.first = malloc(sizeof(struct Mono));
						curr = w.first;
						curr->exp = 0;
						curr->next = NULL;
						*/
					}
				}
			}
			else {
				curr->next = m;
				prev = curr;
				curr = curr->next;
			}
		}
		else {
			w.first = malloc(sizeof(struct Mono));
			w.first->next = NULL;
			w.first->exp = 0;
			*w.first = monos[i];
			curr = w.first;
		}
	}
	return w;
}

/** 
 * @brief Mnoży wielomian przez współczynnik
 * @param[in] p : wielomian
 * @param[in] x : współczynnik
 * @return x*p
 * */
Poly PolyMulCoeff(const Poly *p, poly_coeff_t x){
	if(PolyIsCoeff(p)){
		return PolyFromCoeff(p->val * x);
	}

	if(x == 1)
		return PolyClone(p);

	/*
	if(x == (-1))
		return PolyNeg(p);
	*/
	
	Poly w;	
	Mono *pm, *m, *prev;
	m = malloc(sizeof(struct Mono));
	m->exp = 0;
	m->next = NULL;
	pm = p->first;
	w.first = m;
	while(pm != NULL){
		m->p = PolyMulCoeff(&(pm->p), x);
		m->exp = pm->exp;
		pm = pm->next;
		if(pm != NULL){
			prev = m;
			m = malloc(sizeof(struct Mono));
			m->exp = 0;
			m->next = NULL;
			prev->next = m;
		}
	}
	return w;
}

/**
 * @brief Mnoży dwa wielomiany.
 * @param[in] p : wielomian
 * @param[in] q : wielomian
 * @return `p * q`
 */
Poly PolyMul(const Poly *p, const Poly *q){
	if(PolyIsZero(p) || PolyIsZero(q))
		return PolyZero();

	if(PolyIsCoeff(p))
		return PolyMulCoeff(q, p->val);

	if(PolyIsCoeff(q))
		return PolyMulCoeff(p, q->val);

	unsigned a = 0;
	unsigned b = 0;
	Mono *pm, *qm;
	pm = p->first;
	while(pm != NULL){
		a++;
		pm = pm->next;
	}
	qm = q->first;
	while(qm != NULL){
		b++;
		qm = qm->next;
	}
	unsigned len;
	len = a * b;
	Mono *monos;
	monos = calloc(len, sizeof(struct Mono));
	pm = p->first;
	unsigned curr = 0;
	while(pm != NULL){
		qm = q->first;
		while(qm != NULL){
			monos[curr].next = NULL;
			monos[curr].exp = pm->exp * qm->exp;
			monos[curr].p = PolyMul(&pm->p, &qm->p);
			if(PolyIsZero(&monos[curr].p)){
				monos[curr].next = NULL;
				monos[curr].exp = 0;
				PolyDestroy(&monos[curr].p);
			}
			else {
				curr++;
			}
			qm = qm->next;
		}
		pm = pm->next;
	}
	Poly w = PolyAddMonos(curr, monos);
	free(monos);
	return w;
}

/**
 * @brief Zwraca przeciwny wielomian.
 * @param[in] p : wielomian
 * @return `-p`
 */
Poly PolyNeg(const Poly *p){
	//Poly minus = PolyFromCoeff(-1);
	return PolyMulCoeff(p, -1);
	/*
	if(PolyIsZero(p) == true)
		return PolyClone(p);
	Poly *w;
	w = malloc(sizeof(struct Poly));
	if(PolyIsCoeff(p) == true){
		*w = PolyClone(p);
		w->val *= (-1);
		return *w;
	}
	Mono *curr, *pm, *prev;
	curr = malloc(sizeof(struct Mono));
	w->first = curr;
	while(pm != NULL){
		curr->exp = pm->exp;
		*curr->p = PolyNeg(pm->p);
		pm = pm->next;
		if(pm != NULL){
			prev = curr;
			curr = malloc(sizeof(struct Mono));
			prev->next = curr;
		}
	}
	return *w;
	*/
}

/**
 * @brief Odejmuje wielomian od wielomianu.
 * @param[in] p : wielomian
 * @param[in] q : wielomian
 * @return `p - q`
 */
Poly PolySub(const Poly *p, const Poly *q){
	Poly tmp, res;
	tmp = PolyNeg(q);
	res = PolyAdd(p, &tmp);
	PolyDestroy(&tmp);
	return res;
}


/** 
 * @brief Zwraca większy wykładnik
 * @param[in] a : pierwszy wykładnik
 * @param[in] b: drugi wykładnik
 * @return większy wykładnik
 * */
poly_exp_t max(poly_exp_t a, poly_exp_t b){
	return a >= b ? a : b;
}

/**
 * @brief Zwraca stopień wielomianu ze względu na zadaną zmienną (-1 dla wielomianu tożsamościowo równego zeru).
 * Zmienne indeksowane są od 0.
 * Zmienna o indeksie 0 oznacza zmienną główną tego wielomianu.
 * Większe indeksy oznaczają zmienne wielomianów znajdujących się
 * we współczynnikach.
 * @param[in] p : wielomian
 * @param[in] var_idx : indeks zmiennej
 * @return stopień wielomianu @p p z względu na zmienną o indeksie @p var_idx
 */
poly_exp_t PolyDegBy(const Poly *p, unsigned var_idx){
	if(PolyIsZero(p) == true)
		return (-1);
	if(PolyIsCoeff(p) == true){
		if(var_idx > 0)
			return (-1);
		else //var_idx == 0
			return 0;
	}
	Mono *m;
	poly_exp_t mx;
	mx = (-1);
	m = p->first;
	if(var_idx == 0){
		return m->exp;
	}
	if(var_idx > 0){
		while(m != NULL){
			mx = max(mx, PolyDegBy(&m->p, var_idx - 1));
			m = m->next;
		}
	}
	return mx;
}

/**
 * @brief Zwraca stopień wielomianu (-1 dla wielomianu tożsamościowo równego zeru).
 * @param[in] p : wielomian
 * @return stopień wielomianu @p p
 */
poly_exp_t PolyDeg(const Poly *p){
	if(PolyIsZero(p) == true)
		return (-1);
	if(PolyIsCoeff(p) == true)
		return 0;
	Mono *m;
	poly_exp_t mx, tmp;
	mx = (-1);
	m = p->first;
	while(m != NULL){
		tmp = PolyDeg(&m->p);
		if(tmp != (-1)){
			tmp += m->exp;
		}
		m = m->next;
		mx = max(mx, tmp);
	}
	return mx;
}

/**
 * @brief Sprawdza równość dwóch wielomianów.
 * @param[in] p : wielomian
 * @param[in] q : wielomian
 * @return `p = q`
 */
bool PolyIsEq(const Poly *p, const Poly *q){
	if(PolyIsZero(p) == true){
		if(PolyIsZero(q) == true)
			return true;
		else return false;
	}
	if(PolyIsZero(q) == true)
		return false;
	if(PolyIsCoeff(p) == true){
		if(PolyIsCoeff(q) == true){
			if(q->val == p->val)
				return true;
			else return false;
		}
		else return false;
	}
	if(PolyIsCoeff(q) == true)
		return false;
	
	Mono *pm, *qm;
	pm = p->first;
	qm = p->first;
	while(pm != NULL && qm != NULL){
		if(PolyIsZero(&pm->p) == true)
			pm = pm->next;
		else if(PolyIsZero(&qm->p) == true)
			qm = qm->next;
		else if(pm->exp != qm->exp)
			return false;
		else { //pm->exp == qm->exp
			if(PolyIsEq(&pm->p, &qm->p) != true)
				return false;
			pm = pm->next;
			qm = qm->next;
		}
	}
	if(pm == NULL && qm != NULL)
		return false;
	if(qm == NULL && pm != NULL)
		return false;
	return true;
}

/** 
 * @brief Podnosi współczynnik do danej potęgi
 * @param[in] x : współczynnik
 * @param[in] a : wykładnik
 * @return x^a
 * */
poly_coeff_t coeff_pow(poly_coeff_t x, poly_exp_t a){
	if(x == 0)
		return 0;
	if(a == 0)
		return 1;
	poly_coeff_t result = 1;
    while (a)
    {
        if (a & 1)
            result *= x;
        a >>= 1;
        x *= x;
    }

    return result;
}


/**
 * @brief Wylicza wartość wielomianu w punkcie @p x.
 * Wstawia pod pierwszą zmienną wielomianu wartość @p x.
 * W wyniku może powstać wielomian, jeśli współczynniki są wielomianem
 * i zmniejszane są indeksy zmiennych w takim wielomianie o jeden.
 * Formalnie dla wielomianu @f$p(x_0, x_1, x_2, \ldots)@f$ wynikiem jest
 * wielomian @f$p(x, x_0, x_1, \ldots)@f$.
 * @param[in] p
 * @param[in] x
 * @return @f$p(x, x_0, x_1, \ldots)@f$
 */
Poly PolyAt(const Poly *p, poly_coeff_t x){
	if(PolyIsZero(p) == true)
		return PolyZero();
	if(PolyIsCoeff(p) == true)
		return PolyClone(p);
	if(x == 0)
		return PolyZero();
	Poly w, w1;
	Mono *pm;
	pm = p->first;
	//printf("%ld <-> %ld\n", coeff_pow(x, pm->exp), pm->exp);
	w = PolyMulCoeff(&pm->p, coeff_pow(x, pm->exp));
	pm = pm->next;
	while(pm != NULL){
		Poly tmp;
		tmp = PolyMulCoeff(&pm->p, coeff_pow(x, pm->exp));
		w1 = PolyAdd(&w, &tmp);
		PolyDestroy(&w);
		PolyDestroy(&tmp);
		w = w1;
		pm = pm->next;
	}
	return w;
}
