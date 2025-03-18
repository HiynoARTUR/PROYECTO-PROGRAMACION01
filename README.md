# PROYECTO PROGRAMACION

> Descripcion del Proyecto
Este proyecto consiste en el desarrollo de un monedero virtual programado en C++, diseñado para ayudar a estudiantes a mejorar la administración de sus finanzas personales.
A través de una plataforma intuitiva, los usuarios podrán registrar ingresos y gastos, visualizar su situación financiera y recibir recomendaciones para mejorar su gestión del dinero.
Este software está basado en la Programación Orientada a Objetos (POO), permitiendo una estructura modular, escalable y de fácil mantenimiento.

##INSTALACION

Requisitos Previos 

>Compilador de C++
>Entorno de desarrollo (VS Code)
>Sistema operativo Windows, Linux o MacOS

1. Clonar Repositorio
> gh repo clone HiynoARTUR/PROYECTO-PROGRAMACION01

2. Acceder Proyecto
> cd Cartera Digital

>Diferencias entre Programación Estructurada y Orientada a Objetos

# Diferencias entre POO y Estructurada
Organización de Datos y Comportamientos:

>POO: Utiliza clases y objetos para encapsular datos y comportamientos. Cada clase puede tener atributos (datos) y métodos (funciones) que operan sobre esos datos. Esto permite una mejor organización y reutilización del código.
Estructurada: Utiliza estructuras y funciones independientes. Los datos y las funciones que operan sobre esos datos están separados, lo que puede llevar a un código menos modular y más difícil de mantener.
Encapsulamiento:

>POO: Permite el encapsulamiento, donde los datos de un objeto están protegidos y solo pueden ser accedidos a través de métodos públicos. Esto ayuda a mantener la integridad de los datos.
Estructurada: No tiene un mecanismo de encapsulamiento. Las variables son accesibles desde cualquier parte del código, lo que puede llevar a errores si se modifican accidentalmente.
Herencia y Polimorfismo:

>POO: Permite la herencia, donde una clase puede heredar atributos y métodos de otra clase. También permite el polimorfismo, donde se pueden usar métodos de diferentes clases a través de una interfaz común.
Estructurada: No tiene soporte para herencia o polimorfismo. Cada función debe ser escrita para cada tipo de usuario, lo que puede llevar a duplicación de código.
Manejo de Recursos:

>POO: Los destructores permiten liberar recursos de manera controlada cuando un objeto ya no es necesario.
Estructurada: No hay un mecanismo de destructor, lo que puede llevar a fugas de memoria si no se manejan correctamente los recursos.

Comentarios del Codigo
>Al iniciar el programa, se presenta un menú principal que permite al usuario seleccionar acciones como crear un nuevo usuario, iniciar sesión, 
eliminar un usuario, mostrar un diccionario financiero o recibir un consejo financiero. Cada tipo de usuario tiene su propia lógica para ingresar 
datos y calcular ingresos y gastos, lo que se refleja en métodos virtuales que son implementados en las clases derivadas.
El sistema también incluye funciones para encriptar contraseñas, validar fechas y proporcionar recomendaciones financieras basadas en la situación 
económica del usuario. Esto no solo mejora la seguridad, sino que también ayuda a los usuarios a gestionar mejor sus finanzas.
En resumen, el código proporciona una interfaz interactiva y funcional para la gestión de usuarios, combinando la lógica de negocio con la presentación de datos de manera clara y estructurada.
