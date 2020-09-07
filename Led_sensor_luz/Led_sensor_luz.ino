/*
#       _\|/_   A ver..., ¿que tenemos por aqui?
#       (O-O)        
# ---oOO-(_)-OOo---------------------------------
 
 
##########################################################
# ****************************************************** #
# *           DOMOTICA PARA PRINCIPIANTES              * #
# *          Diodo Led como sensor de luz              * #
# *                                                    * #
# *         Autor:   Eulogio López Cayuela             * #
# *           https://github.com/inopya/               * #
# *                                                    * #
# *       Versión 1.0       Fecha: 16/03/2020          * #
# ****************************************************** #
##########################################################
*/

#define __VERSION__ "Diodo LED como sensor de luz"

/*
      ===== NOTAS DE LA VERSION ===== 
    Uso de un diodo led comun como sensor de luz:
    
    Un diodo led presenta una cierta capacitancia interna en la union PN.
    Al polarizarlo en inverso cargaremos dicho "condensador",
    y este se descargará más rapido cuanta mas luz reciba la union PN.
    Por tanto si tras polarizarlo en inverso medimos el tiempo que tarda en descargarse,
    podemos estimar la cantidad de luz que ha recibido.
    Un manera más sencilla sin tener que esperar a medir el tiempo de la descarga 
    de dicha capacitancia interna es el que empleamos aqui.
    
    1) Polarizamos en inverso,
    2) esperamos unos pocos milisegundos y medimos el valor de voltaje remanente.
    
    Si no hubiese indicido ninguna luz, tras unos pocos milisegundos la carga sería el voltaje al que fue sometido.
    
    En presencia de luz, cuanto menor sea el valor leido, mayor podemos asegurar que ha sido la cantidad de luz incidente
    
    Cada led 'medirá' luz en una longitud de onda próxima al tipo de luz que emite
    Los mejores resultados los obtendremos con leds rojos o verdes y cuerpo transparente.
    Pero podemos usar cualquier led del que disppongamos.

    El ANODO del led se conectará a tierra mediante una resistencia de entre 200 y 270 ohmios
    Dicha resitencia no es obligatoria dado que el diodo esta en inverso, pero quede ahí por si deseamos usar el led como
    emisor de luz y como sensor a un mismo tiempo conectando el ANODO a una salida digital.
    
    El CATODO se conecta a una entrada analogica de arduino.
    
    Podemos usar simultaneamente leds de distintos colores apra medir distintas longitudes de onda de la luz

    En el ejemplo se usa un led RGB de anodo comun para medir tres componentes de la luz a un mismo tiempo.
*/



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DEFINICION DE PINES
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

// ANODO del LED a tierra con una resistencia de 220-270 ohmios
#define PIN_LED_CATODO_ROJO     A0  
#define PIN_LED_CATODO_VERDE    A1   
#define PIN_LED_CATODO_AZUL     A2 
 
#define INTERVALO_MUESTRAS    1000      // Tiempo entre muestras de luz.
#define TIEMPO_CARGA            10      // Tiempo necesario para 'cargar' el led (entre 10 y 30 ms)
#define TIEMPO_SENSADO          20      // Tiempo para provocar una  cierta descarga de la capacidad
                                        // interna del led. Un menor voltaje medido representa
                                        // un mayor valor de luminosidad, debido a que la descarga 
                                        // es mas rapida cuanta mas luz incide en el led
                                        // Tiempos pu elevados provocarian la descarga completa 
                                        // de dicha capacidad interna del diodo y nos induciria a 
                                        // pensar que la lunimosidad es elevada. (entre 15 y 50 ms)

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DEFINICION DE VARIABLES GLOBALES
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

uint16_t valor_sensor_rojo=0;
uint16_t valor_sensor_verde=0;
uint16_t valor_sensor_azul=0;



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   ****************************************************************************************************** 
                                    FUNCION DE CONFIGURACION
   ****************************************************************************************************** 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void setup(void)
{
  Serial.begin(115200);                           // Iniciar puerto serie apra DEBUG
  Serial.println (F(__VERSION__));                // mostramos la version por consola, DEBUG
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   ****************************************************************************************************** 
                                  BUCLE PRINCIPAL DEL PROGRAMA
   ****************************************************************************************************** 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/


void loop(void)
{ 

  /* --------- lectura sensor ROJO --------- */
  pinMode(PIN_LED_CATODO_ROJO, OUTPUT);
  digitalWrite(PIN_LED_CATODO_ROJO, HIGH);
  delay(TIEMPO_CARGA);

  pinMode(PIN_LED_CATODO_ROJO, INPUT); 
  delay(TIEMPO_SENSADO);

  valor_sensor_rojo = analogRead(PIN_LED_CATODO_ROJO); 
  //El valor medido es inversamente proporcional a la cantidad de luz que incide en el led
  //ya que la capacidad interna del diodo se descarga mas rapidamente cuanta más luz recibe.
  //Usamos la funcion map para mostrar en un modo 'más lógico', es decir: mas luz, mayor valor 
  valor_sensor_rojo = map(valor_sensor_rojo, 0,1023,1023,0);

   
  /* --------- lectura sensor VERDE --------- */
  pinMode(PIN_LED_CATODO_VERDE, OUTPUT);
  digitalWrite(PIN_LED_CATODO_VERDE, HIGH);
  delay(TIEMPO_CARGA);

  pinMode(PIN_LED_CATODO_VERDE, INPUT); 
  delay(TIEMPO_SENSADO);

  valor_sensor_verde = analogRead(PIN_LED_CATODO_VERDE); 
  //El valor medido es inversamente proporcional a la cantidad de luz que incide en el led
  //ya que la capacidad interna del diodo se descarga mas rapidamente cuanta más luz recibe.
  //Usamos la funcion map para mostrar en un modo 'más lógico', es decir: mas luz, mayor valor  
  valor_sensor_verde = map(valor_sensor_verde, 0,1023,1023,0);
  
  /* --------- lectura sensor AZUL --------- */
  pinMode(PIN_LED_CATODO_AZUL, OUTPUT);
  digitalWrite(PIN_LED_CATODO_AZUL, HIGH);
  delay(TIEMPO_CARGA);

  pinMode(PIN_LED_CATODO_AZUL, INPUT); 
  delay(TIEMPO_SENSADO);

  valor_sensor_azul = analogRead(PIN_LED_CATODO_AZUL); 
  //El valor medido es inversamente proporcional a la cantidad de luz que incide en el led
  //ya que la capacidad interna del diodo se descarga mas rapidamente cuanta más luz recibe.
  //Usamos la funcion map para mostrar en un modo 'más lógico', es decir: mas luz, mayor valor  
  valor_sensor_azul = map(valor_sensor_azul, 0,1023,1023,0);


  /* --------- Mostar datos por el puerto serie --------- */
  
  Serial.print(F("Valor Rojo: "));
  Serial.println(valor_sensor_rojo);
  Serial.print(F("Valor Verde: "));
  Serial.println(valor_sensor_verde);
  Serial.print(F("Valor Azul: "));
  Serial.println(valor_sensor_azul);
  Serial.println(F("*****************\n"));
  
  delay(INTERVALO_MUESTRAS);
}


//*******************************************************
//                    FIN DE PROGRAMA
//*******************************************************
