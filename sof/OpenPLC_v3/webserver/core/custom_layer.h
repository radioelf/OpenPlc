//-----------------------------------------------------------------------------
// ADVERTENCIA: LA EDICION DE ESTE ARCHIVO PUEDE ROMPER EL TIEMPO DE EJECUCION DE OPENPLC! SI NO
// SABES LO QUE ESTÁS HACIENDO. EDITAR BAJO SU PROPIO RIESGO.
// PS: Siempre puedes restaurar la funcionalidad original si rompes algo.
// haciendo clic en el boton "Restaurar codigo original".
//-----------------------------------------------------------------------------
// Estos son los vectores de E/S ignorados. Si quieres anular 
// una entrada o salida particular de OpenPLC, debes ponerlas en el vector
// de ignorados. Por ejemplo, si desea reemplazar %IX0.5, %IX0.6 and %IW3
// tus vectores deben ser:
//     int ignored_bool_inputs[] = {5, 6}; //%IX0.5 y %IX0.6 ignorado
//     int ignored_int_inputs[] = {3}; //%IW3 ignorado
//
// Todas las E/S en los vectores ignorados serán omitidas por la capa de hardware OpenPLC
//-----------------------------------------------------------------------------
int ignored_bool_inputs[] = {-1};
int ignored_bool_outputs[] = {-1};
int ignored_int_inputs[] = {-1};
int ignored_int_outputs[] = {-1};

//-----------------------------------------------------------------------------
// Esta funcion es llamada por la rutina principal de OpenPLC cuando se esta inicializando.
// Los procedimientos de inicializacion de hardware para su capa personalizada deben estar aqui.
//-----------------------------------------------------------------------------
void initCustomLayer()
{
}

//-----------------------------------------------------------------------------
// Esta funcion es llamada por OpenPLC en un bucle. Aqui la entrada interna de
// los buffers deben actualizarse con los valores que se deseen. Asegurate 
// de usar semaforos (mutex) bufferLock para proteger el acceso a los buffers
// en un entorno de subprocesos.
//-----------------------------------------------------------------------------
void updateCustomIn()
{
	// Codigo de ejemplo: sobrescribir %IW3 con un valor fijo
    // Si desea que %IW3 lea constantemente un valor fijo (por ejemplo, 53)
    // se debe agregar %IW3 a los vectores ignorados arriba, y luego simplemente 
    // inserte esta linea de codigo en esta funcion:
    //     if (int_input[3] != NULL) *int_input[3] = 53;
}

//-----------------------------------------------------------------------------
// Esta funcion es llamada por OpenPLC en un bucle. Aqui la salida interna de
// los buffers deben actualizarse con los valores que se deseen. Asegurate
// de usar semaforos (mutex) bufferLock para proteger el acceso a los buffers
// en un entorno de subprocesos.
//-----------------------------------------------------------------------------
void updateCustomOut()
{
	// Codigo de ejemplo - Enviando valor %QW5 sobre I2C
    // Si se desea que la salida %QW5 envie a traves de I2C en lugar de la
    // usarse como una salida tradicional, todo lo que tienes que hacer es,
    // primero agrega %QW5 a los vectores ignorados, y luego define  la funcion
    // send_over_i2c(). Finalmente puedes llamar a send_over_i2c() y
    // envía tu valor a %QW5 a traves de I2C, ejemplo:
    //     if (int_output[5] != NULL) send_over_i2c(*int_output[5]);
    //
	// ATENCION: si sus pines I2C son utilizados por OpenPLC como I/O, usted
    // tambien debe agregar esas I/O a los vectores ignorados, de lo contrario
    // OpenPLC intentara controlar sus pines I2C y el bus I2C no funcionara.
}
