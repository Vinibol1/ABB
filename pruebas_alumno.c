#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

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
	printf("%i\n", *num);
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
		     "abb postorden itero corractamente: 1 == %zu", num_aux);
	pa2m_afirmar(
		*num_aux2 == 3,
		"abb postorden itero y aplico función corractamente: 3 == %zu",
		*num_aux2);

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

int main()
{
	pa2m_nuevo_grupo("abb crear");
	abb_crear_prueba();
	pa2m_nuevo_grupo("abb insertar");
	abb_insertar_prueba();
	pa2m_nuevo_grupo("abb preorder");
	abb_iterar_preorder_prueba();
	abb_iterar_preorder_prueba_un_elem();
	pa2m_nuevo_grupo("abb postorder");
	abb_iterar_postorder_prueba_un_elem();
	abb_iterar_postorder_prueba();
	pa2m_nuevo_grupo("abb inorder");
	abb_iterar_inorder_prueba();
	abb_iterar_inorder_prueba_un_elem();
	pa2m_nuevo_grupo("abb obtener");
	abb_obtener_prueba();

	return pa2m_mostrar_reporte();
}
