# Control de porton de garaje

**Introducción:**
       
Se trata de controlar un portón de garaje, en mi caso lleva un motor monofásico de corriente alterna con condensador, de 250V.
    
A través de un mando a distancia se activará un relé que permanecerá activado tanto tiempo como lo estemos apretando desde el mando.
Entonces este relé se comportará como un pulsador a distancia. Esta entrada es el pin D2 de un Arduino UNO/Nano y en el programa
se llama "pulsador". Durante la creación de este programa he usado un pulsador, pero la conexión final será un relé del mando receptor.

Tiene dos salidas "ledA" (pin A0) y "ledB" (pin A1), son las salidas que activarán dos relés, pero durante la programación
de las secuencias he utilizado dos leds. Los relés son los que controlarán el motor monofásico de corriente alterna, que lo hará girar
en un sentido o en el otro (dependiendo si se activa ledA o ledB) durante un tiempo determinado. Aquí el tiempo es de 10 segundos
pero en la vida real ha de ser muchos más segundos.

**Funcionamiento del programa:**

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


