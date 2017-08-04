/** @file
   Implementacja stosu

   @author Kamil Bladoszewski <kb392558@students.mimuw.edu.pl>
   @copyright Uniwersytet Warszawski
   @date 2017-05-27
*/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "poly.h"

typedef struct Error {
	
	bool czyBlad;
	Poly odp;
	
} Error;

struct Elem;

typedef struct Elem {
	
	struct Elem *next;
	Poly var;
	
	} Elem;

typedef struct Stack {
	
	Elem *first;
	
	} Stack;
	
extern Stack stos;

bool elemEmpty(Elem *e){
	if(e == NULL)
		return true;
	else if(&e->var == NULL)
		return true;
	else return false;
}

bool isEmpty(){
	if(stos.first == NULL)
		return true;
	Elem *e;
	e = stos.first;
	if(&e->var == NULL)
		return true;
	else return false;
}

bool isEmpty2(){
	if(isEmpty())
		return true;
	else {
		Elem *e;
		e = stos.first;
		if(e->next == NULL)
			return true;
		else {
			Elem *e2;
			e2 = e->next;
			if(&e2->var == NULL)
				return true;
			else return false;
		}
	}
}

Error get(){
	if(isEmpty()){
		Error err;
		err.czyBlad = true;
		//err.odp = NULL;
		return err;
	}
	else {
		Error res;
		Elem *e;
		e = stos.first;
		res.odp = e->var;
		res.czyBlad = false;
		return res;
	}
}

Error get2(){
	if(isEmpty()){
		Error err;
		err.czyBlad = true;
		//err.odp = NULL;
		return err;
	}
	else {
		Elem *e;
		e = stos.first;
		if(e->next == NULL){
			Error err;
			err.czyBlad = true;
			//err.odp = NULL;
			return err;
		}
		else {
			Elem *e2;
			e2 = e->next;
			if(&e2->var == NULL){
				Error err;
			err.czyBlad = true;
			//err.odp = NULL;
			return err;
			}
			else {
				Error res;
				res.czyBlad = false;
				res.odp = e2->var;
				return res;
			}
		}
	}
}
	
Error pop(){
	Elem *e, *n;
	if(isEmpty()){
		Error err;
		err.czyBlad = true;
		//err.odp = NULL;
		return err;
	}
	e = stos.first;
	n = e->next;
	stos.first = n;
	Error res;
	res.czyBlad = false;
	res.odp = e->var;
	free(e);
	return res;
}

void add(Poly p){
	Elem *e, *f;
	if(isEmpty()){
		e = malloc(sizeof(struct Elem));
		e->var = p;
		e->next = NULL;
		stos.first = e;
	}
	else {
		e = malloc(sizeof(struct Elem));
		e->var = p;
		f = stos.first;
		e->next = f;
		stos.first = e;
	}
}

#endif /* __STACK_H__ */
