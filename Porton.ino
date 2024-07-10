/*  Introducción:
       
    Se trata de controlar un portón de garaje, en mi caso lleva un motor monofásico de corriente alterna con condensador, de 250V.
    
    A través de un mando a distancia se activará un relé que permanecerá activado tanto tiempo como lo estemos apretando desde el mando.
    Entonces este relé se comportará como un pulsador a distancia. Esta entrada es el pin D2 de un Arduino UNO/Nano y en el programa
    se llama "pulsador". Durante la creación de este programa he usado un pulsador, pero la conexión final será un relé del mando receptor.

    Tiene dos salidas "ledA" (pin A0) y "ledB" (pin A1), son las salidas que activarán dos relés, pero durante la programación
    de las secuencias he utilizado dos leds. Los relés son los que controlarán el motor monofásico de corriente alterna, que lo hará girar
    en un sentido o en el otro (dependiendo si se activa ledA o ledB) durante un tiempo determinado. Aquí el tiempo es de 10 segundos
    pero en la vida real ha de ser muchos más segundos.

    Funcionamiento del programa:

    La premisa es que sólo se puede encender uno de los dos leds, nunca ambos.

    Tenemos un pulsador como entrada y dos leds como salidas. Al arrancar el Arduino permanecerá los dos leds apagados.
    Si doy un pulso en el pulsador, se encederá "ledA" durante 10 segundos; transcurrido ese tiempo se apagará este led,
    y "ledB" permanecerá apagado (como ya estaba).
    Si durante esos 10 segundos le doy al pulsador entonces se apagará "ledA", y "ledB" continuará estando apagado (como ya estaba).
    Si vuelvo a pulsar ahora se encenderá "ledB" y permanecerá encendido durante 10 segundos, "ledA" continuará apagado (como ya estaba).
    Si durante esos 10 segundos le doy al pulsador entonces se apagará "ledB", y "ledA" continuará estando apagado.

    En la vida real esto es el portón del garaje que se abre o se cierra.
    Pulsamos y se abre dándo un tiempo de 10 segundos para que esto ocurra.
    Volvemos a pulsar y el portón se cierra, dando 10 segundos para que esto ocurra.
    Si durante la apertura o el cierre de la puerta el coche todavía no ha salido o entrado (durante esos 10 segundos) y pulsamos el pulsador
    lo que ocurre es que anulamos la acción, y el portón se para.

    He visto portones que sólo abren o cierra y eso a mi modo de ver es que el programador de esos aparatos no se ha esmerado mucho.
    Por motivos de seguridad siempre ha de haber la opción de parar el portón, tanto al abrir como al cerrar.
*/

#include <Bounce2.h>// Puedes descargarla desde el gestor de bibliotecas o bien desde aquí: https://github.com/adafruit/Adafruit_Debounce

// Definir los pines
#define pulsador 2  // Pulsador/relé del mando a distancia. Activador de la secuencia. Es el pin D2 del Arduino UNO/Nano.
#define ledA A0     // Control de dos relés que visualizamos con dos led.
#define ledB A1     // Cuando A0 se enciende significa que se abre la puerta y cuando A1 se enciende significa que se cierra. Nunca se activan ambos a la vez.
                    // En realidad A0 y A1 actuarán sobre dos relés que controlarán el motor de corriente alterna que hace mover el portón hacia ambos lados.

// Crear una instancia de Bounce para el antirrebote del pulsador.
Bounce debouncer = Bounce(); 

// Variables para manejar el estado de los leds y el temporizador.
bool timerActive = false;
unsigned long startTime;
const unsigned long duracion = 10000; // 10 segundos de activación para el motor. En realidad son muchos más segundos, lo tengo a 10 segundos para las pruebas con leds.
int mode = 0; // 0: ledB, 1: ledA

void setup() {
  // Se declara primero el estado de ambos leds como apagados y luego como salidas para evitar que al arrancar el Arduino
  // tenga "1s lógicos" momentáneos en los pines de salida. Las patillas que usan protocolos seriales tiene esta tendencia,
  // y aunque aquí no ocurre, evitamos a toda costa que esto suceda.
  
  // Iniciar con los leds apagados.
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, LOW);
  
  // Configurar los pines como entradas o salidas.
  pinMode(ledA,           OUTPUT);
  pinMode(ledB,           OUTPUT);
  pinMode(pulsador, INPUT_PULLUP);

  // Configurar el antirrebote.
  debouncer.attach(pulsador);
  debouncer.interval(500); // Intervalo de antirrebote en ms. Hay que pulsar medio segundo o un poco más para activar la secuencia.
}

void loop() {
  // Actualizar el estado del antirrebote.
  debouncer.update();

  // Si el botón es pulsado:
  if (debouncer.fell()) {
    if (timerActive) {
      // Si el temporizador está activo, apagar ambos leds y detener el temporizador.
      digitalWrite(ledA, LOW);
      digitalWrite(ledB, LOW);
      timerActive = false;
    } else {
      // Si el temporizador no está activo, iniciar el temporizador y encender el led correspondiente.
      startTime = millis();
      timerActive = true;
      if (mode == 0) {
        digitalWrite(ledB, HIGH);
        digitalWrite(ledA, LOW);
        mode = 1; // Cambiar al modo ledA para la próxima pulsación.
      } else {
        digitalWrite(ledA, HIGH);
        digitalWrite(ledB, LOW);
        mode = 0; // Cambiar al modo ledB para la próxima pulsación.
      }
    }
  }

  // Si el temporizador está activo, verificar el tiempo transcurrido.
  if (timerActive) {
    if (millis() - startTime >= duracion) {
      // Si han pasado 10 segundos, apagar los leds y detener el temporizador
      digitalWrite(ledA, LOW);
      digitalWrite(ledB, LOW);
      timerActive = false;
    }
  }
}
