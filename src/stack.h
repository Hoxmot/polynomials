/* Stos */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Error {
	
	bool czyBlad;
	Poly odp;
	
};

struct Elem {
	
	Elem next;
	Poly var;
	
	};

struct Stack {
	
	Elem first;
	
	};
	
extern Stack stos;

bool elemEmpty(Elem e){
	if(e == NULL)
		return true;
	else if(e.var == NULL)
		return true;
	else return false;
}

bool isEmpty(){
	if(stos == NULL)
		return true;
	else if(stos.first == NULL)
		return true;
	Elem e = stos.first
	if(e.var == NULL)
		return true;
	else return false;
}

Error get(){
	if(isEmpty()){
		Error err;
		err.czyBlad = true;
		err.odp = NULL;
		return err;
	}
	else {
		Error res;
		res.odp = stos.var;
		res.czyBlad = false;
		return res;
	}
}

Error get2(){
	if(isEmpty()){
		Error err;
		err.czyBlad = true;
		err.odp = NULL;
		return err;
	}
	else {
		Elem e = stos.first;
		if(e.next == NULL){
			Error err;
			err.czyBlad = true;
			err.odp = NULL;
			return err;
		}
		else {
			Elem e2 = e.next;
			if(e2.var == NULL){
				Error err;
			err.czyBlad = true;
			err.odp = NULL;
			return err;
			}
			else {
				Error res;
				res.czyBlad = false;
				res.odp = e2.var
				return res;
			}
		}
	}
}
	
Error pop(){
	Elem e, n;
	if(isEmpty()){
		Error err;
		err.czyBlad = true;
		err.odp = NULL;
		return err;
	}
	e = stos.first;
	n = e.next;
	stos.first = n;
	Error res;
	res.czyBlad = false;
	res.odp = e.var
	return res;
}

void add(Poly p){
	Elem e, f;
	if(isEmpty()){
		e.var = p;
		e.next = NULL;
		stos.first = e;
	}
	else {
		e.var = p;
		stos.first = f;
		e.next = f;
		stos.next = e;
	}
}
	
