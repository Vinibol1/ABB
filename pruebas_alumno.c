#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"
#include <string.h>

int comparador(void *numero, void *numero2)
{
	int *num = numero;
	int *num2 = numero2;
	if (*num == *num2)
		return 0;
	else if (*num > *num2)
		return 1;
	return -1;
}

bool funcion_iterar(void *elem, void *ctx)
{
	int *num = elem;
	printf("%i", *num);
	(*num)++;
	return true;
}

bool funcion_false(void *elem, void *ctx)
{
	return false;
}

bool funcion_iterar2(void *elem, void *ctx)
{
	int *num = elem;
	printf("%i", *num);
	if (*num == 3) {
		return false;
	}

	(*num)++;
	return true;
}

void abb_crear_prueba()
{
	abb_t *abb = abb_crear(comparador);

	pa2m_afirmar(abb != NULL, "abb se creo correctamente");
	pa2m_afirmar(abb->comparador != NULL,
		     "abb comparador se asigno correctamentte");
	pa2m_afirmar(abb->raiz == NULL, "abb raiz es NULL");
	pa2m_afirmar(abb->nodos == 0, "abb nodos es 0");
	abb_destruir(abb);
}

void abb_insertar_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	int *num_aux = abb->raiz->elemento;
	int *num_aux2 = abb->raiz->der->elemento;
	int *num_aux3 = abb->raiz->der->der->elemento;
	int *num_aux4 = abb->raiz->izq->elemento;
	pa2m_afirmar(*num_aux == 2,
		     "abb raiz se inserto corractamente: 2 == %d", *num_aux);
	pa2m_afirmar(*num_aux2 == 3,
		     "abb derecha se inserto corractamente: 3 == %d",
		     *num_aux2);
	pa2m_afirmar(*num_aux3 == 4,
		     "abb derecha se inserto corractamente: 4 == %d",
		     *num_aux3);
	pa2m_afirmar(*num_aux4 == 1,
		     "abb izquierda se inserto corractamente: 1 == %d",
		     *num_aux4);
	abb_destruir(abb);
}

void abb_iterar_preorder_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);
	size_t num_aux = abb_iterar_preorden(abb, funcion_iterar, NULL);
	int *num_aux2 = abb->raiz->elemento;
	int *num_aux3 = abb->raiz->der->elemento;
	int *num_aux4 = abb->raiz->der->der->elemento;
	pa2m_afirmar(num_aux == 4, "abb preorden itero corractamente: 4 == %zu",
		     num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb preorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);
	pa2m_afirmar(
		*num_aux3 == 4,
		"abb preorden itero y aplico función corractamente: 4 == %zu",
		*num_aux3);
	pa2m_afirmar(
		*num_aux4 == 5,
		"abb preorden itero y aplico función corractamente: 5 == %zu",
		*num_aux4);
	abb_destruir(abb);
}

void abb_iterar_preorder_prueba_un_elem()
{
	abb_t *abb = abb_crear(comparador);
	size_t num_aux = abb_iterar_preorden(abb, funcion_iterar, NULL);
	pa2m_afirmar(num_aux == 0, "abb preorden vacio devuelve 0: 0 == %zu",
		     num_aux);
	int num = 2;
	abb_insertar(abb, &num);

	num_aux = abb_iterar_preorden(abb, funcion_iterar, NULL);
	int *num_aux2 = abb->raiz->elemento;

	pa2m_afirmar(num_aux == 1, "abb preorden itero corractamente: 1 == %zu",
		     num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb preorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);

	abb_destruir(abb);
}

void abb_iterar_pre_con_funcion_que_retorna_false_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 1;
	int num3 = 3;
	int num4 = 5;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	size_t num_aux = abb_iterar_preorden(abb, funcion_iterar2, NULL);
	int *num_aux2 = abb->raiz->elemento;
	int *num_aux3 = abb->raiz->der->elemento;
	pa2m_afirmar(num_aux == 3, "abb inorden itero corractamente: 3 == %zu",
		     num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);
	pa2m_afirmar(
		*num_aux3 == 3,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux3);

	size_t num_aux4 = abb_iterar_preorden(abb, funcion_false, NULL);
	pa2m_afirmar(num_aux4 == 1, "abb inorden itero corractamente: 1 == %zu",
		     num_aux4);

	abb_destruir(abb);
}

void abb_iterar_postorder_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);
	size_t num_aux = abb_iterar_postorden(abb, funcion_iterar, NULL);
	int *num_aux2 = abb->raiz->elemento;
	int *num_aux3 = abb->raiz->der->elemento;
	int *num_aux4 = abb->raiz->der->der->elemento;
	pa2m_afirmar(num_aux == 4,
		     "abb postorden itero corractamente: 4 == %zu", num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb postorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);
	pa2m_afirmar(
		*num_aux3 == 4,
		"abb postorden itero y aplico función corractamente: 4 == %zu",
		*num_aux3);
	pa2m_afirmar(
		*num_aux4 == 5,
		"abb postorden itero y aplico función corractamente: 5 == %zu",
		*num_aux4);
	abb_destruir(abb);
}

void abb_iterar_postorder_prueba_un_elem()
{
	abb_t *abb = abb_crear(comparador);
	size_t num_aux = abb_iterar_postorden(abb, funcion_iterar, NULL);
	pa2m_afirmar(num_aux == 0, "abb postorden vacio devuelve 0: 0 == %zu",
		     num_aux);
	int num = 2;
	abb_insertar(abb, &num);

	num_aux = abb_iterar_postorden(abb, funcion_iterar, NULL);
	int *num_aux2 = abb->raiz->elemento;

	pa2m_afirmar(num_aux == 1,
		     "\nabb postorden itero corractamente: 1 == %zu", num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb postorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);

	abb_destruir(abb);
}

void abb_iterar_post_con_con_funcion_que_retorna_false_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 1;
	int num3 = 3;
	int num4 = 5;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	size_t num_aux = abb_iterar_postorden(abb, funcion_iterar2, NULL);
	int *num_aux2 = abb->raiz->elemento;
	int *num_aux3 = abb->raiz->der->elemento;
	pa2m_afirmar(num_aux == 3, "abb inorden itero corractamente: 3 == %zu",
		     num_aux);
	pa2m_afirmar(
		*num_aux2 == 2,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);
	pa2m_afirmar(
		*num_aux3 == 3,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux3);

	size_t num_aux4 = abb_iterar_postorden(abb, funcion_false, NULL);
	pa2m_afirmar(num_aux4 == 1, "abb inorden itero corractamente: 1 == %zu",
		     num_aux4);

	abb_destruir(abb);
}

void abb_iterar_inorder_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	size_t num_aux = abb_iterar_inorden(abb, funcion_iterar, NULL);
	int *num_aux2 = abb->raiz->elemento;
	int *num_aux3 = abb->raiz->der->elemento;
	int *num_aux4 = abb->raiz->der->der->elemento;
	pa2m_afirmar(num_aux == 4, "abb inorden itero corractamente: 4 == %zu",
		     num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);
	pa2m_afirmar(
		*num_aux3 == 4,
		"abb inorden itero y aplico función corractamente: 4 == %zu",
		*num_aux3);
	pa2m_afirmar(
		*num_aux4 == 5,
		"abb inorden itero y aplico función corractamente: 5 == %zu",
		*num_aux4);
	abb_destruir(abb);
}

void abb_iterar_inorder_con_con_funcion_que_retorna_false_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 1;
	int num3 = 3;
	int num4 = 5;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	size_t num_aux = abb_iterar_inorden(abb, funcion_iterar2, NULL);
	int *num_aux2 = abb->raiz->elemento;
	int *num_aux3 = abb->raiz->der->elemento;
	pa2m_afirmar(num_aux == 3, "abb inorden itero corractamente: 2 == %zu",
		     num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);
	pa2m_afirmar(
		*num_aux3 == 3,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux3);

	size_t num_aux4 = abb_iterar_inorden(abb, funcion_false, NULL);
	pa2m_afirmar(num_aux4 == 1, "abb inorden itero corractamente: 1 == %zu",
		     num_aux4);

	abb_destruir(abb);
}

void abb_iterar_inorder_prueba_un_elem()
{
	abb_t *abb = abb_crear(comparador);
	size_t num_aux = abb_iterar_inorden(abb, funcion_iterar, NULL);
	pa2m_afirmar(num_aux == 0, "abb inorden vacio devuelve 0: 0 == %zu",
		     num_aux);

	int num = 2;
	abb_insertar(abb, &num);

	num_aux = abb_iterar_inorden(abb, funcion_iterar, NULL);
	int *num_aux2 = abb->raiz->elemento;

	pa2m_afirmar(num_aux == 1, "abb inorden itero corractamente: 1 == %zu",
		     num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb inorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);

	abb_destruir(abb);
}

void abb_obtener_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);
	int num5 = 7;
	int *num_aux2 = abb_obtener(abb, &num2);
	int *num_aux3 = abb_obtener(abb, &num3);
	int *num_aux4 = abb_obtener(abb, &num4);
	int *num_aux5 = abb_obtener(abb, &num5);

	pa2m_afirmar(*num_aux2 == 3,
		     "abb_obtener obtuvo correctamente: 3 == %zu", *num_aux2);
	pa2m_afirmar(*num_aux3 == 4,
		     "abb_obtener obtuvo correctamente: 4 == %zu", *num_aux3);
	pa2m_afirmar(*num_aux4 == 1,
		     "abb_obtener obtuvo correctamente: 1 == %zu", *num_aux4);
	pa2m_afirmar(num_aux5 == NULL,
		     "abb_obtener null obtuvo 0 correctamente: 0 == %zu",
		     num_aux5);
	abb_destruir(abb);
}

void abb_quitar_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 4;
	int num3 = 5;
	int num4 = 3;
	int num5 = 0;
	int num6 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);
	abb_insertar(abb, &num5);
	abb_insertar(abb, &num6);

	pa2m_afirmar(abb_cantidad(abb) == 6, "abb_cantidad devuelve 6");

	void *num_aux = NULL;
	pa2m_afirmar(abb_quitar(abb, &num, &num_aux) == true,
		     "abb_quitar devuelve true");
	int *numero_aux = num_aux;
	pa2m_afirmar(*numero_aux == 2,
		     "abb_quitar obtuvo correctamente: 2 == %zu", *numero_aux);
	int *numero = abb->raiz->elemento;
	pa2m_afirmar(
		*numero == 1,
		"abb_quitar dejo en posicion correcta el elemento del arbol: 1 == %zu",
		*numero);

	pa2m_afirmar(abb_cantidad(abb) == 5, "abb_cantidad devuelve 5");

	void *num_aux2 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num2, &num_aux2) == true,
		     "abb_quitar devuelve true");
	int *numero_aux2 = num_aux2;
	pa2m_afirmar(*numero_aux2 == 4,
		     "abb_quitar obtuvo correctamente: 4 == %zu", *numero_aux2);
	int *numero2 = abb->raiz->der->elemento;
	pa2m_afirmar(
		*numero2 == 3,
		"abb_quitar dejo en posicion correcta el elemento del arbol:3 == %zu",
		*numero2);

	void *num_aux3 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num3, &num_aux3) == true,
		     "abb_quitar devuelve true");
	int *numero_aux3 = num_aux3;
	pa2m_afirmar(*numero_aux3 == 5,
		     "abb_quitar obtuvo correctamente: 5 == %zu", *numero_aux3);
	pa2m_afirmar(abb->raiz->der->der == NULL,
		     "abb_quitar devuelve NULL en la posición quitada");

	void *num_aux4 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num4, &num_aux4) == true,
		     "abb_quitar devuelve true");
	int *numero_aux4 = num_aux4;
	pa2m_afirmar(*numero_aux4 == 3,
		     "abb_quitar obtuvo correctamente: 3 == %zu", *numero_aux4);
	pa2m_afirmar(abb->raiz->der == NULL,
		     "abb_quitar devuelve NULL en la posición quitada");

	void *num_aux6 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num6, &num_aux6) == true,
		     "abb_quitar devuelve true");
	int *numero_aux6 = num_aux6;
	pa2m_afirmar(*numero_aux6 == 1,
		     "abb_quitar obtuvo correctamente: 1 == %zu", *numero_aux6);
	int *numero3 = abb->raiz->elemento;
	pa2m_afirmar(*numero3 == 0,
		     "abb_quitar devuelve NULL en la posición quitada");

	void *num_aux5 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num5, &num_aux5) == true,
		     "abb_quitar devuelve true");
	int *numero_aux5 = num_aux5;
	pa2m_afirmar(*numero_aux5 == 0,
		     "abb_quitar obtuvo correctamente: 0 == %zu", *numero_aux5);
	pa2m_afirmar(abb->raiz == NULL,
		     "abb_quitar devuelve NULL en la posición quitada");

	pa2m_afirmar(abb_cantidad(abb) == 0, "abb_cantidad devuelve 0");

	abb_destruir(abb);
}

void abb_quitar_pruebas_de_funcionamiento_parametros_erroneos()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 4;
	int num3 = 5;
	int num4 = 3;
	int num5 = 0;
	int num6 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);
	abb_insertar(abb, &num5);

	pa2m_afirmar(abb_cantidad(abb) == 5, "abb_cantidad devuelve 5");

	void *num_aux = NULL;
	pa2m_afirmar(abb_quitar(abb, &num6, &num_aux) == false,
		     "abb_quitar devuelve false");
	int *numero_aux = num_aux;
	pa2m_afirmar(numero_aux == NULL, "abb_quitar obtuvo NULL");

	pa2m_afirmar(abb_cantidad(abb) == 5, "abb_cantidad devuelve 5");

	pa2m_afirmar(abb_quitar(abb, &num4, NULL) == true,
		     "abb_quitar devuelve false si se pasa NULL");

	abb_destruir(abb);
}

void abb_quitar_raices_prueba()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 4;
	int num3 = 5;
	int num4 = 7;
	int num5 = 6;
	int num6 = 8;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);
	abb_insertar(abb, &num5);
	abb_insertar(abb, &num6);

	pa2m_afirmar(abb_cantidad(abb) == 6, "abb_cantidad devuelve 6");

	void *num_aux = NULL;
	pa2m_afirmar(abb_quitar(abb, &num, &num_aux) == true,
		     "abb_quitar devuelve true");
	int *numero_aux = num_aux;
	pa2m_afirmar(*numero_aux == 2,
		     "abb_quitar obtuvo correctamente: 2 == %zu", *numero_aux);
	int *numero = abb->raiz->elemento;
	pa2m_afirmar(
		*numero == 4,
		"abb_quitar dejo en posicion correcta el elemento del arbol: 4 == %zu",
		*numero);

	pa2m_afirmar(abb_cantidad(abb) == 5, "abb_cantidad devuelve 5");

	void *num_aux2 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num2, &num_aux2) == true,
		     "abb_quitar devuelve true");
	int *numero_aux2 = num_aux2;
	pa2m_afirmar(*numero_aux2 == 4,
		     "abb_quitar obtuvo correctamente: 4 == %zu", *numero_aux2);
	int *numero2 = abb->raiz->elemento;
	pa2m_afirmar(
		*numero2 == 5,
		"abb_quitar dejo en posicion correcta el elemento del arbol:3 == %zu",
		*numero2);

	void *num_aux3 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num3, &num_aux3) == true,
		     "abb_quitar devuelve true");
	int *numero_aux3 = num_aux3;
	pa2m_afirmar(*numero_aux3 == 5,
		     "abb_quitar obtuvo correctamente: 5 == %zu", *numero_aux3);

	void *num_aux4 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num4, &num_aux4) == true,
		     "abb_quitar devuelve true");
	int *numero_aux4 = num_aux4;
	pa2m_afirmar(*numero_aux4 == 7,
		     "abb_quitar obtuvo correctamente: 7 == %zu", *numero_aux4);
	pa2m_afirmar(abb->raiz->izq == NULL,
		     "abb_quitar devuelve NULL en la posición quitada");

	void *num_aux6 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num5, &num_aux6) == true,
		     "abb_quitar devuelve true");
	int *numero_aux6 = num_aux6;
	pa2m_afirmar(*numero_aux6 == 6,
		     "abb_quitar obtuvo correctamente: 6 == %zu", *numero_aux6);
	int *numero3 = abb->raiz->elemento;
	pa2m_afirmar(*numero3 == 8, "abb_quitar devuelve 8 en la raiz");

	void *num_aux5 = NULL;
	pa2m_afirmar(abb_quitar(abb, &num6, &num_aux5) == true,
		     "abb_quitar devuelve true");
	int *numero_aux5 = num_aux5;
	pa2m_afirmar(*numero_aux5 == 8,
		     "abb_quitar obtuvo correctamente: 8 == %zu", *numero_aux5);
	pa2m_afirmar(abb->raiz == NULL,
		     "abb_quitar devuelve NULL en la posición quitada");

	pa2m_afirmar(abb_cantidad(abb) == 0, "abb_cantidad devuelve 0");

	abb_destruir(abb);
}

void abb_vectorizar_inorder_pruebas()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	int *vector_[4];
	abb_vectorizar_inorden(abb, (void **)&vector_, 4);

	pa2m_afirmar(*vector_[0] == 1,
		     "abb_obtener obtuvo correctamente: 1 == %zu", *vector_[0]);
	pa2m_afirmar(*vector_[1] == 2,
		     "abb_obtener obtuvo correctamente: 2 == %zu", *vector_[1]);
	pa2m_afirmar(*vector_[2] == 3,
		     "abb_obtener obtuvo correctamente: 3 == %zu", *vector_[2]);
	pa2m_afirmar(*vector_[3] == 4,
		     "abb_obtener obtuvo correctamente: 4 == %zu", *vector_[3]);
	abb_destruir(abb);
}

void abb_vectorizar_inorder_pruebas2()
{
	abb_t *abb = abb_crear(comparador);
	char *num = "asd";
	char *num2 = "dsa";
	char *num3 = "qwe";
	char *num4 = "zxc";
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	char **vector_[4];
	abb_vectorizar_inorden(abb, (void **)&vector_, 4);

	pa2m_afirmar(strcmp(**vector_, "asd") == 0,
		     "abb_obtener obtuvo correctamente: asd == %s ", **vector_);
	pa2m_afirmar(strcmp(*vector_[1], "dsa") == 0,
		     "abb_obtener obtuvo correctamente: dsa == %s ", **vector_);
	pa2m_afirmar(strcmp(*vector_[2], "qwe") == 0,
		     "abb_obtener obtuvo correctamente: qwe == %s ", **vector_);
	pa2m_afirmar(strcmp(*vector_[3], "zxc") == 0,
		     "abb_obtener obtuvo correctamente: zxc == %s ", **vector_);

	abb_destruir(abb);
}

void abb_vectorizar_preorder_pruebas()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	int *vector_[4];
	abb_vectorizar_preorden(abb, (void **)&vector_, 4);

	pa2m_afirmar(*vector_[0] == 2,
		     "abb_obtener obtuvo correctamente: 2 == %zu", *vector_[0]);
	pa2m_afirmar(*vector_[1] == 1,
		     "abb_obtener obtuvo correctamente: 1 == %zu", *vector_[1]);
	pa2m_afirmar(*vector_[2] == 3,
		     "abb_obtener obtuvo correctamente: 3 == %zu", *vector_[2]);
	pa2m_afirmar(*vector_[3] == 4,
		     "abb_obtener obtuvo correctamente: 4 == %zu", *vector_[3]);
	abb_destruir(abb);
}

void abb_vectorizar_preorder_mas_elementos_pruebas()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	int *vector_[2];
	abb_vectorizar_preorden(abb, (void **)&vector_, 2);

	pa2m_afirmar(*vector_[0] == 2,
		     "abb_obtener obtuvo correctamente: 2 == %zu", *vector_[0]);
	pa2m_afirmar(*vector_[1] == 1,
		     "abb_obtener obtuvo correctamente: 1 == %zu", *vector_[1]);
	abb_destruir(abb);
}

void abb_vectorizar_postorder_pruebas()
{
	abb_t *abb = abb_crear(comparador);
	int num = 2;
	int num2 = 3;
	int num3 = 4;
	int num4 = 1;
	abb_insertar(abb, &num);
	abb_insertar(abb, &num2);
	abb_insertar(abb, &num3);
	abb_insertar(abb, &num4);

	int *vector_[4];
	abb_vectorizar_postorden(abb, (void **)&vector_, 4);

	pa2m_afirmar(*vector_[0] == 1,
		     "abb_obtener obtuvo correctamente: 2 == %zu", *vector_[0]);
	pa2m_afirmar(*vector_[1] == 4,
		     "abb_obtener obtuvo correctamente: 1 == %zu", *vector_[1]);
	pa2m_afirmar(*vector_[2] == 3,
		     "abb_obtener obtuvo correctamente: 3 == %zu", *vector_[2]);
	pa2m_afirmar(*vector_[3] == 2,
		     "abb_obtener obtuvo correctamente: 4 == %zu", *vector_[3]);
	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo("abb crear");
	abb_crear_prueba();
	pa2m_nuevo_grupo("abb insertar");
	abb_insertar_prueba();
	pa2m_nuevo_grupo("abb preorder");
	abb_iterar_preorder_prueba();
	abb_iterar_preorder_prueba_un_elem();
	abb_iterar_pre_con_funcion_que_retorna_false_prueba();
	pa2m_nuevo_grupo("abb postorder");
	abb_iterar_postorder_prueba_un_elem();
	abb_iterar_postorder_prueba();
	abb_iterar_post_con_con_funcion_que_retorna_false_prueba();
	pa2m_nuevo_grupo("abb inorder");
	abb_iterar_inorder_prueba();
	abb_iterar_inorder_prueba_un_elem();
	abb_iterar_inorder_con_con_funcion_que_retorna_false_prueba();
	pa2m_nuevo_grupo("abb obtener");
	abb_obtener_prueba();
	pa2m_nuevo_grupo("abb quitar");
	abb_quitar_prueba();
	abb_quitar_pruebas_de_funcionamiento_parametros_erroneos();
	pa2m_nuevo_grupo("abb quitar raices");
	abb_quitar_raices_prueba();
	pa2m_nuevo_grupo("abb vectorizar inorden");
	abb_vectorizar_inorder_pruebas();
	abb_vectorizar_inorder_pruebas2();
	pa2m_nuevo_grupo("abb vectorizar preorden");
	abb_vectorizar_preorder_pruebas();
	abb_vectorizar_preorder_mas_elementos_pruebas();

	return pa2m_mostrar_reporte();
}
