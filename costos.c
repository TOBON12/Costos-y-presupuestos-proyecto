#include <stdio.h>

#define MAX_MESES 12

// Declaración de las funciones
void estimar_pronostico(float intercepto, float pendiente, int meses_actuales, int meses_a_predecir, float* suma_pronostico);
float calcular_precio(float* costo_total_produccion);  
void generar_estado_financiero(float suma_pronostico, float precio, float costo_total_produccion);

void calcular_estadisticas(int meses, int meses_a_predecir) {
    int mes_indice[MAX_MESES];
    float ventas_mes[MAX_MESES];
    int mes_cuadrado[MAX_MESES];
    float ventas_cuadrado[MAX_MESES];
    float producto_mes_ventas[MAX_MESES];

    // Inicializar índices de meses
    for (int i = 0; i < meses; i++) {
        mes_indice[i] = i + 1;
    }

    // Solicitar valores de ventas (Y)
    for (int i = 0; i < meses; i++) {
        printf("Ingrese las ventas para el mes %d: ", mes_indice[i]);
        scanf("%f", &ventas_mes[i]);
    }

    // Calcular X^2, Y^2 y X * Y
    for (int i = 0; i < meses; i++) {
        mes_cuadrado[i] = mes_indice[i] * mes_indice[i];
        ventas_cuadrado[i] = ventas_mes[i] * ventas_mes[i];
        producto_mes_ventas[i] = mes_indice[i] * ventas_mes[i];
    }

    // Mostrar resultados
    printf("\n%-5s %-12s %-6s %-12s %-8s\n", "Mes", "Ventas", "X^2", "Y^2", "X * Y");
    for (int i = 0; i < meses; i++) {
        printf("%-5d %-12.2f %-6d %-12.2f %-8.2f\n", mes_indice[i], ventas_mes[i], mes_cuadrado[i], ventas_cuadrado[i], producto_mes_ventas[i]);
    }

    // Sumar valores
    int suma_mes_indice = 0, suma_mes_cuadrado = 0;
    float suma_ventas = 0, suma_ventas_cuadrado = 0, suma_producto_mes_ventas = 0;
    for (int i = 0; i < meses; i++) {
        suma_mes_indice += mes_indice[i];
        suma_ventas += ventas_mes[i];
        suma_mes_cuadrado += mes_cuadrado[i];
        suma_ventas_cuadrado += ventas_cuadrado[i];
        suma_producto_mes_ventas += producto_mes_ventas[i];
    }

    // Mostrar sumas totales
    printf("\nSumas:\n");
    printf("Suma de X: %d\n", suma_mes_indice);
    printf("Suma de Y: %.2f\n", suma_ventas);
    printf("Suma de X^2: %d\n", suma_mes_cuadrado);
    printf("Suma de Y^2: %.2f\n", suma_ventas_cuadrado);
    printf("Suma de X * Y: %.2f\n", suma_producto_mes_ventas);

    // Calcular pendiente y ordenada al origen
    float pendiente = (meses * suma_producto_mes_ventas - suma_mes_indice * suma_ventas) / (meses * suma_mes_cuadrado - suma_mes_indice * suma_mes_indice);
    float intercepto = (suma_ventas - pendiente * suma_mes_indice) / meses;

    // Mostrar valores de a y b
    printf("\nEl valor de la pendiente es: %.6f\n", pendiente);
    printf("El valor de la ordenada al origen es: %.6f\n", intercepto);
    
    // Llamar a la función para calcular pronóstico
    float suma_pronostico = 0.0;
    estimar_pronostico(intercepto, pendiente, meses, meses_a_predecir, &suma_pronostico);

    // Calcular precio de venta
    float costo_total_produccion = 0.0; 
    float precio = calcular_precio(&costo_total_produccion); 

    // Generar el estado financiero
    generar_estado_financiero(suma_pronostico, precio, costo_total_produccion);
}

void estimar_pronostico(float intercepto, float pendiente, int meses_actuales, int meses_a_predecir, float* suma_pronostico) {
    const char* nombres_meses[MAX_MESES] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    printf("\n%-12s %-4s %-12s\n", "Mes", "X", "Pronostico");

    *suma_pronostico = 0.0;
    for (int i = 0; i < meses_a_predecir; i++) {
        int mes_numero = meses_actuales + i + 1;
        float pronostico = intercepto + pendiente * mes_numero;
        printf("%-12s %-4d %-12.3f\n", nombres_meses[(mes_numero - 1) % MAX_MESES], mes_numero, pronostico);
        *suma_pronostico += pronostico;
    }

    printf("TOTAL                %.3f\n", *suma_pronostico);
}

float calcular_precio(float* costo_total_produccion) {
    float costo_materia_prima, costo_mano_obra, cif_variable, cif_fijo, margen_utilidad, precio;

    printf("\nPara calcular el precio de venta:\n");

    // Ingresar costos
    printf("Costo de Materia Prima por unidad: $");
    scanf("%f", &costo_materia_prima);

    printf("Costo de Mano de Obra por unidad: $");
    scanf("%f", &costo_mano_obra);

    printf("Costo de CIF Variables por unidad: $");
    scanf("%f", &cif_variable);

    printf("Costo total de CIF Fijos: $");
    scanf("%f", &cif_fijo);

    *costo_total_produccion = costo_materia_prima + costo_mano_obra + cif_variable + cif_fijo;

    printf("Ingrese el margen de utilidad (ejemplo: 0.20 para 20%%): ");
    scanf("%f", &margen_utilidad);

    precio = *costo_total_produccion / (1 - margen_utilidad);

    printf("\nCOSTO TOTAL\n");
    printf("Materia Prima\t\t$%.2f\n", costo_materia_prima);
    printf("Mano de Obra\t\t$%.2f\n", costo_mano_obra);
    printf("CIF Variables\t\t$%.2f\n", cif_variable);
    printf("CIF Fijos\t\t$%.2f\n", cif_fijo);
    printf("Total Produccion\t$%.2f\n", *costo_total_produccion);
    printf("\nPrecio de Venta\t\t$%.2f\n", precio);

    return precio;
}

void generar_estado_financiero(float suma_pronostico, float precio, float costo_total_produccion) {
    float ingresos = suma_pronostico * precio;
    float costo_ventas = suma_pronostico * costo_total_produccion; 
    float utilidad_bruta = ingresos - costo_ventas;

    float gastos_variable, gastos_fijo;
    printf("\nIngrese el gasto variable (ventas): $");
    scanf("%f", &gastos_variable);
    printf("Ingrese el gasto fijo: $");
    scanf("%f", &gastos_fijo);

    float gastos_operativos = gastos_variable + gastos_fijo;
    float utilidad_neta_operativa = utilidad_bruta - gastos_operativos;

    float porcentaje_financiero;
    printf("Porcentaje de gastos financieros (ejemplo: 0.05 para 5%%): ");
    scanf("%f", &porcentaje_financiero);
    float gasto_financiero = ingresos * porcentaje_financiero;

    float utilidad_final = utilidad_neta_operativa - gasto_financiero;

    printf("\n\tESTADO FINANCIERO\n\n");
    printf("INGRESOS\t\t$%.2f\n", ingresos);
    printf("COSTO DE VENTA\t\t$%.2f\n", costo_ventas);
    printf("UTILIDAD BRUTA\t\t$%.2f\n", utilidad_bruta);
    printf("GASTOS OPERATIVOS\n");
    printf("Variables\t\t$%.2f\n", gastos_variable);
    printf("Fijos\t\t\t$%.2f\n", gastos_fijo);
    printf("Utilidad Operativa\t$%.2f\n", utilidad_neta_operativa);
    printf("Gasto Financiero\t$%.2f\n", gasto_financiero);
    printf("Utilidad Final\t\t$%.2f\n", utilidad_final);
}

int main() {
    int opcion, meses, meses_a_predecir;
    char continuar;

    do {
        printf("\nSeleccione una opcion:\n");
        printf("1. Calcular estadisticas de ventas\n");
        printf("2. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese la cantidad de meses de datos disponibles: ");
                scanf("%d", &meses);
                printf("Ingrese la cantidad de meses a pronosticar: ");
                scanf("%d", &meses_a_predecir);
                calcular_estadisticas(meses, meses_a_predecir);
                break;
            case 2:
                printf("Saliendo del programa.\n");
                return 0;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }

        printf("¿Desea realizar otra operacion? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 0;
}
