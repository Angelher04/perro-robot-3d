# perro-robot-3d
QuadPaws

Robot cuadrúpedo interactivo con sensores ultrasónicos

Autores

Michelle Mogica Guzmán

Santiago Alvarado Hernández

Sergio Hernández Gutiérrez

Ángel Alberto Hernández Pérez

Introducción
¿Qué es un robot cuadrúpedo?

Un robot cuadrúpedo es un robot que se desplaza utilizando cuatro patas, imitando la locomoción de animales como perros o gatos. Su principal objetivo es mantener estabilidad y movilidad en diversos terrenos donde las ruedas no son eficientes.

¿Por qué es interesante/útil construir uno?

Permite estudiar y aplicar cinemática y control de múltiples grados de libertad

Es una plataforma ideal para probar algoritmos de equilibrio y locomoción

Introduce el uso de servomotores, estructuras mecánicas ligeras y control distribuido

Tiene aplicaciones en exploración, asistencia y educación robótica

QuadPaws busca lograr interacción básica con personas mediante gestos: saludar y sentarse al detectar presencia.

Diseño mecánico

El diseño estructural del robot se desarrolló priorizando:

Bajo peso para facilitar el movimiento

Centro de masa estable

Rigidización mediante piezas en PLA

Facilidad de ensamble y mantenimiento



📌 El robot consiste en:

Cuerpo central donde se montan la electrónica y batería

4 patas con 3 grados de libertad cada una

Topes para limitar rangos no seguros del servo

3️⃣ Electrónica
Componentes principales
Componente	Cantidad	Función
Arduino Mega 2560	1	Control del sistema
Driver PCA9685	1	Control de servomotores por PWM
Servomotores MG996R	12	Articulaciones del robot
Sensores ultrasónicos HC-SR04	2	Detección de proximidad
Batería 6V o pack 4xAA	1	Alimentación de servos
Fuente USB o 9V regulada	1	Alimentación del microcontrolador



4️⃣ Sistema de control

QuadPaws funciona de manera autónoma con dos sensores:

Sensor 1 (frontal izquierdo): activa secuencia de saludo

Sensor 2 (frontal derecho): activa secuencia de sentado

Principales funciones del código

Conversión de grados a pulsos PWM para servos

Rutina de postura neutral (parado)

Secuencias animadas (saludo y sentado)

Lectura de distancia por ultrasonido

Retardo programado para evitar repetición continua

⚙️ Instrucciones de carga

Abrir Arduino IDE

Seleccionar tarjeta:
Tools → Board → Arduino Mega or Mega 2560

Seleccionar puerto correspondiente



🔌 Alimentación del robot

Recomendado: batería externa de 6–7.2V para servos

USB solamente para la placa Arduino

Unir GND común entre Arduino y PCA9685

🖐️ Interacción

Acercar un objeto/persona a < 30 cm

Sensor izquierdo → saludo

Sensor derecho → sentado

5️⃣ Resultados

📸 Fotografías del robot funcionando


📹 Video demostrativo

6️⃣ Problemas y mejoras
Dificultades encontradas

Ruido en servos y consumo de corriente elevado

Necesidad de calibrar posiciones de cada articulación

Ensamble inicial requería reajustes por holguras

Mejoras futuras

Sistema de equilibrio dinámico (IMU)

Movimientos más naturales y gaits avanzados

Control remoto vía Bluetooth o aplicación Web

Actualizar diseño mecánico para reducir peso y fricción
