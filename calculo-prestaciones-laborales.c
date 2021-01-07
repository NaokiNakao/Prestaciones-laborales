/*
Este programa realiza el cálculo de las prestaciones laborales

Creado por: Naoki Nakao
Fecha: 7 de octubre, 2020
Mat/ID: 1014-2124
1750-ICC-101
*/

#include <stdio.h>
#include <stdlib.h>

//prototipos de función

void pedir_datos_tiempo();
void tiempo_total();
void datos_salario();
void datos_vac_preaviso();

void preaviso();
void cesantia();
float vacaciones(float);
float navidad(float);
float calc_total(float, float, float, float, float);
void mostrar_resultado();

//directivas de procesador(macros)

#define A_TILDE 160
#define I_TILDE 161
#define U_TILDE 163
#define GN 164

//variables globales

int agnos, meses, dias, agnos_antes_1992, meses_antes_1992, dias_antes_1992, agnos_total, meses_total, dias_total, dias_vac; //almacenan los datos de tiempo
float salario_actual, salario_ult_12_meses, salario_acum_agno, salario_diario_actual, salario_diario_prom;//almacenan datos relacionados al salario
char p;//almacena un caracter
float pago_preaviso = 0, pago_cesantia_antes_1992, pago_cesantia, pago_vacaciones, pago_navidad, pago_total;//almacenan los valores relacionados con el pago final

int main()
{
    printf("C%clculo de prestaciones laborales\n", A_TILDE);

    pedir_datos_tiempo();//pidiendo los datos de tiempo del trabajador
    tiempo_total();//calculando el tiempo total
    datos_salario();//pidiendo los datos del salario y calculando los promedios
    datos_vac_preaviso();//pide la cantidad de dias de vaciones que se tomaron y si hubo preaviso o no

    if (p == 'N' || p == 'n')
    {
        preaviso();//calcula la cantidad que se debe pagar en caso de que no se haya preavisado
    }

    cesantia();//calculando la cesantía
    pago_vacaciones = vacaciones(dias_vac);//calculando el pago correspondiente por vacaciones
    pago_navidad = navidad(salario_acum_agno);//calculando el pago correspondiente por navidad
    pago_total = calc_total(pago_preaviso, pago_cesantia_antes_1992, pago_cesantia, pago_vacaciones, pago_navidad);//calculando el total

    mostrar_resultado();//mostrando los resultados de las prestaciones

    return 0;
}

/*
    Función: pedir_datos_tiempo
    Argumentos: ---
    Objetivo: pedir y almacenar los datos de tiempo
    Retorno: ---
*/
void pedir_datos_tiempo()
{
    do {//pidiendo los datos de tiempo antes del año 1992

        printf("Cantidad de a%cos, meses y d%cas trabajados antes de 1992: ", GN, I_TILDE);
        scanf("%d %d %d", &agnos_antes_1992, &meses_antes_1992, &dias_antes_1992);

        if (agnos_antes_1992 < 0 || meses_antes_1992 < 0 || dias_antes_1992 < 0)
        {
            printf("\nDatos no v%clidos\n", A_TILDE);
        }

    } while (agnos_antes_1992 < 0 || meses_antes_1992 < 0 || dias_antes_1992 < 0);

    do {//pidiendo los datos de tiempo después del año 1992

        printf("Cantidad de a%cos, meses y d%cas trabajados a partir de 1992: ", GN, I_TILDE);
        scanf("%d %d %d", &agnos, &meses, &dias);

        if (agnos < 0 || meses < 0 || dias < 0)
        {
            printf("\nDatos no v%clidos\n", A_TILDE);
        }

    } while (agnos < 0 || meses < 0 || dias < 0);

    return;
}

/*
    Función: tiempo_total
    Argumentos: ---
    Objetivo: calcular el total de días, meses y años que ha estado el trbajador
    Retorno: ---
*/
void tiempo_total()
{
    agnos_total = agnos + agnos_antes_1992;
    meses_total = meses + meses_antes_1992;
    dias_total = dias + dias_antes_1992;

    if (dias_total >= 30)
    {
        dias_total %= 30;
        meses_total++;
    }

    if (meses_total >= 12)
    {
        meses_total %= 12;
        agnos_total++;
    }

    return;
}

/*
    Función: datos_salario
    Argumentos: ---
    Objetivo: almacenar los datos del salario, calcular los promedios
    Retorno: ---
*/
void datos_salario()
{
    float factor = 23.83;

    do {//pididendo la suma de los salarios de los últimos 12 meses

        printf("Suma de los %cltimos doce salarios: ", U_TILDE);
        scanf("%f", &salario_ult_12_meses);

        if (salario_ult_12_meses < 0)
        {
            printf("Datos incorrectos.");
        }

    } while (salario_ult_12_meses < 0);

    do {//pidiendo el salario actual

        printf("Salario actual: ");
        scanf("%f", &salario_actual);

        if (salario_actual < 0)
        {
            printf("Datos incorrectos.");
        }

    } while (salario_actual < 0);

    do {//pidiendo el salario acumulado en el año presente

        printf("Salario acumulado a%co en curso: ", GN);
        scanf("%f", &salario_acum_agno);

        if (salario_acum_agno < 0)
        {
            printf("Datos incorrectos");
        }

    } while (salario_acum_agno < 0);

    salario_diario_prom = (salario_ult_12_meses / 12) / factor;//calculando el salario promedio
    salario_diario_actual = salario_actual / factor;//calculando el salario diario actual

    return;
}

/*
    Función: datos_vac_preaviso
    Argumentos: ---
    Objetivo: pedir la cantidad de dias de vaciones que se tomaron y si hubo preaviso o no
    Retorno: ---
*/
void datos_vac_preaviso()
{
    do {//pidiendo la cantidad de días de vaciones tomados

        printf("Cantidad de d%cas de vacaciones tomados: ", I_TILDE);
        scanf("%d", &dias_vac);

        if (dias_vac < 0)
        {
            printf("Datos incorrectos");
        }

    } while (dias_vac < 0);

    do {
        printf("Fue preavisado el trabajador? Si(1) o No(0): ");
        scanf(" %c", &p);

        if (p != 'N' && p != 'n' && p != 'S' && p != 's')
        {
            printf("\nDatos incorrectos");
        }
    } while (p != 'N' && p != 'n' && p != 'S' && p != 's');

    return;
}

/*
    Función: preaviso
    Argumentos: ---
    Objetivo: calcula la cantidad que se debe pagar en caso de que no se haya preavisado
    Retorno: ---
*/
void preaviso()
{
    if (agnos_total > 1)
    {
        pago_preaviso = salario_diario_prom * 28;
    }
    else if (meses_total > 6 && agnos_total <= 1)
    {
        pago_preaviso = salario_diario_prom * 14;
    }
    else if (meses_total >= 3 && meses_total <= 6)
    {
        pago_preaviso = salario_diario_prom * 7;
    }

    return;
}

/*
    Función: cesantia
    Argumentos: ---
    Objetivo: Calcular el pago por la cesantía antes y después de 1992
    Retorno: ---
*/
void cesantia()
{
    //calculando la cesantia antes de 1992
    pago_cesantia_antes_1992 = agnos_antes_1992 * 15 * salario_diario_prom;//calculando la cesantía correspondiente antes del 1992

    //calculando la cesantia a partir de 1992
    if (agnos > 5)
    {
        pago_cesantia = salario_diario_prom * 23 * agnos;
    }
    else if (agnos > 1 && agnos <= 5)
    {
        pago_cesantia = salario_diario_prom * 21 * agnos;
    }
    else if (meses > 6 && agnos <= 1)
    {
        pago_cesantia = salario_diario_prom * 13;
    }
    else if (meses >= 3 && meses <= 6)
    {
        pago_cesantia = salario_diario_prom * 6;
    }

    return;
}

/*
    Función: vacaciones
    Argumentos: (float) v
    Objetivos: calcular el pago por vaciones
    Retorno: (float) cantidad resultante al calcular los días de vaciones tomados
*/
float vacaciones(float v)
{
    float total;

    if (agnos_total > 1 && agnos_total < 5)
    {
        total = (14 - dias_vac) * salario_diario_actual;
    }
    else if (agnos > 5)
    {
        total = (18 - dias_vac) * salario_diario_actual;
    }

    return total;
}

/*
    Función: navidad
    Argumentos: (float) n
    Objetivo: calcular la cantidad de dinero que corresponde por el pago de navidad
    Retorno: (float) pago por navidad dependiendo de lo que haya acumulado es año
*/
float navidad(float n)
{
    float total = n / 12;

    return total;
}

/*
    Función: calc_total
    Argumentos: (foat) pre, (float) ces_ant_1992, (float) ces, (float) vac, (float) nav
    Objetivo: calcular el valor total de las prestaciones
    Retorno: valor total
*/
float calc_total(float pre, float ces_ant_1992, float ces, float vac, float nav)
{
    float total = pre + ces_ant_1992 + ces + vac + nav;
    return total;
}

/*
    Función: mostrar_resultado
    Argumentos: ---
    Objetivo: mostrar la cantidad total
    Retorno: ---
*/
void mostrar_resultado()
{
    printf("\n\nResultado del c%clculo de prestaciones: ", A_TILDE);
    printf("\nSalario diario promedio: %f", salario_diario_prom);
    printf("\nSalario diario actual: %f", salario_diario_actual);
    printf("\nTiempo laborado: %d a%cos, %d meses y %d d%cas", agnos_total, GN, meses_total, dias_total, I_TILDE);
    printf("\nPreaviso: %f", pago_preaviso);
    printf("\nCesant%ca (Antes 1992): %f", I_TILDE, pago_cesantia_antes_1992);
    printf("\nCesant%ca: %f", I_TILDE, pago_cesantia);
    printf("\nSalario de vacaiones: %f", pago_vacaciones);
    printf("\nSalario de navidad: %f", pago_navidad);
    printf("\nTotal de prestaciones: %f", pago_total);

    return;
}





















