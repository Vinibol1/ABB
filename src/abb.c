#include "abb.h"
#include "abb_estructura_privada.h"

#define Nodo_raiz 'N'
#define Nodo_izq 'I'
#define Nodo_der 'D'

abb_t *abb_crear(int (*comparador)(void *, void *))
{
	if (!comparador)
		return NULL;

	abb_t *abb = calloc(1, sizeof(abb_t));
	abb->comparador = comparador;
	return abb;
}

bool asignar_nodo_abb(abb_t *abb, char nodo, void *elemento)
{
	if (!abb || !nodo || !elemento)
		return false;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->elemento = elemento;
	switch (nodo) {
	case Nodo_raiz:
		abb->raiz = nuevo_nodo;
		break;
	case Nodo_izq:
		abb->raiz->izq = nuevo_nodo;
		break;
	case Nodo_der:
		abb->raiz->der = nuevo_nodo;
		break;
	}
	return true;
}

size_t abb_cantidad(abb_t *abb)
{
	return abb->nodos;
}

bool abb_insertar(abb_t *abb, void *elemento)
{
	if (!abb || !elemento)
		return false;
	abb->nodos += 1;
	if (abb->raiz == NULL)
		return asignar_nodo_abb(abb, 'N', elemento);

	abb_t abb_temp = *abb;
	if (abb->comparador(elemento, abb->raiz->elemento) > 0) {
		if (!abb->raiz->der)
			return asignar_nodo_abb(abb, 'D', elemento);

		abb_temp.raiz = abb->raiz->der;
		if (!abb_insertar(&abb_temp, elemento))
			return false;

	} else if (abb->comparador(elemento, abb->raiz->elemento) < 0) {
		if (!abb->raiz->izq)
			return asignar_nodo_abb(abb, 'I', elemento);

		abb_temp.raiz = abb->raiz->izq;
		if (!abb_insertar(&abb_temp, elemento))
			return false;
	}
	return true;
}

size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !f || !abb->raiz)
		return 0;
	abb_t abb_temp = *abb;
	size_t contador = 0;
	if (abb->raiz) {
		if (!f(abb->raiz->elemento, ctx)) {
			contador += 1;
			return contador;
		}
		contador += 1;
	}
	if (abb->raiz->izq) {
		abb_temp.raiz = abb->raiz->izq;
		contador += abb_iterar_preorden(&abb_temp, f, ctx);
	}
	if (abb->raiz->der) {
		abb_temp.raiz = abb->raiz->der;
		contador += abb_iterar_preorden(&abb_temp, f, ctx);
	}
	return contador;
}

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !f || !abb->raiz)
		return 0;
	abb_t abb_temp = *abb;
	size_t contador = 0;

	if (abb->raiz->izq) {
		abb_temp.raiz = abb->raiz->izq;
		contador += abb_iterar_inorden(&abb_temp, f, ctx);
	}
	if (abb->raiz) {
		if (!f(abb->raiz->elemento, ctx)) {
			contador += 1;
			return contador;
		}
		contador += 1;
	}
	if (abb->raiz->der) {
		abb_temp.raiz = abb->raiz->der;
		contador += abb_iterar_inorden(&abb_temp, f, ctx);
	}
	return contador;
}

size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !f || !abb->raiz)
		return 0;
	abb_t abb_temp = *abb;
	size_t contador = 0;
	if (abb->raiz->izq) {
		abb_temp.raiz = abb->raiz->izq;
		contador += abb_iterar_postorden(&abb_temp, f, ctx);
	}
	if (abb->raiz->der) {
		abb_temp.raiz = abb->raiz->der;
		contador += abb_iterar_postorden(&abb_temp, f, ctx);
	}
	if (abb->raiz) {
		if (!f(abb->raiz->elemento, ctx)) {
			contador += 1;
			return contador;
		}
		contador += 1;
	}
	return contador;
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (!abb->raiz || !abb || !elemento)
		return NULL;
	abb_t abb_temp = *abb;
	int comparador = abb->comparador(elemento, abb->raiz->elemento);
	if (comparador == 0)
		return abb->raiz->elemento;

	if (abb->raiz->izq && comparador < 0) {
		abb_temp.raiz = abb->raiz->izq;
		return abb_obtener(&abb_temp, elemento);
	}
	if (abb->raiz->der && comparador > 0) {
		abb_temp.raiz = abb->raiz->der;
		return abb_obtener(&abb_temp, elemento);
	}
	return NULL;
}

void liberar_nodos(abb_t *abb)
{
	abb_t abb_temp = *abb;
	if (abb->raiz->izq) {
		abb_temp.raiz = abb->raiz->izq;
		liberar_nodos(&abb_temp);
	}
	if (abb->raiz->der) {
		abb_temp.raiz = abb->raiz->der;
		liberar_nodos(&abb_temp);
	}
	if (abb->raiz) {
		free(abb->raiz);
		return;
	}
}

void abb_destruir(abb_t *abb)
{
	if (!abb)
		return;
	if (abb->nodos > 1)
		liberar_nodos(abb);
	else if (abb->nodos == 1)
		free(abb->raiz);
	free(abb);
}