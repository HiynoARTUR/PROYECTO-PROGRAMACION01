#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

// Función plantilla para leer un valor de tipo T desde la entrada estándar
template <typename T>
T leerValor(const string &mensaje) {
    T valor;
    cout << mensaje;
    while (!(cin >> valor)) { // Verifica si la entrada es válida
        cin.clear(); // Limpia el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada no válida
        cout << "Entrada no válida. " << mensaje; // Mensaje de error
    }
    return valor; // Retorna el valor leído
}

// Función para encriptar una cadena de texto
string encriptar(const string &s) {
    string resultado = s;
    for (size_t i = 0; i < s.size(); i++) {
        resultado[i] = s[i] + 1; // Incrementa cada carácter
    }
    return resultado; // Retorna la cadena encriptada
}

// Clase para representar una fecha
class Fecha {
private:
    int dia, mes, anio; // Atributos de la fecha
    // Método privado para verificar si un año es bisiesto
    bool esBisiesto(int a) {
        return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
    }
    // Método privado para obtener el número de días en un mes
    int diasEnMes(int m, int a) {
        if(m == 2) return esBisiesto(a) ? 29 : 28; // Febrero
        if(m == 4 || m == 6 || m == 9 || m == 11) return 30; // Meses con 30 días
        return 31; // Meses con 31 días
    }
public:
    // Constructor que inicializa la fecha
    Fecha(int d, int m, int a) {
        if(m >= 1 && m <= 12 && d >= 1 && d <= diasEnMes(m, a)) {
            dia = d; mes = m; anio = a; // Asigna valores válidos
        } else {
            cout << "Fecha inválida. Se asignará 01/01/2000 por defecto.\n";
            dia = 1; mes = 1; anio = 2000; // Asigna fecha por defecto
        }
    }
    // Método para convertir la fecha a una cadena
    string toString() const {
        return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
    }
};

// Clase base para representar un usuario
class Usuario {
protected:
    string nombre; // Nombre del usuario
    string contraseña; // Contraseña encriptada
    int edad; // Edad del usuario
    Fecha fechaCreacion; // Fecha de creación de la cuenta
    double ingresos; // Ingresos del usuario
    double gastosPrimarios; // Gastos primarios
    double gastosSecundarios; // Gastos secundarios
    double gastosTerciarios; // Gastos terciarios
    double ahorro; // Ahorro del usuario
    double inversion; // Inversión del usuario
    double deudas; // Deudas del usuario
    string estadoFamiliar; // Estado familiar del usuario
    string moneda; // Moneda del usuario
public:
    // Constructor que inicializa los atributos del usuario
    Usuario(string nom, string pass, int ed, Fecha fecha, string mon)
      : nombre(nom), contraseña(encriptar(pass)), edad(ed), fechaCreacion(fecha),
        ingresos(0), gastosPrimarios(0), gastosSecundarios(0), gastosTerciarios(0),
        ahorro(0), inversion(0), deudas(0), estadoFamiliar(""), moneda(mon) {}
    
    // Métodos virtuales que deben ser implementados por las clases derivadas
    virtual void ingresarDatos() = 0; // Método para ingresar datos
    virtual void mostrarInformacion() const {
        cout << "Nombre: " << nombre << "\nEdad: " << edad 
             << "\nFecha de creacion: " << fechaCreacion.toString() 
             << "\nMoneda: " << moneda 
             << "\nDeudas: $" << fixed << setprecision(2) << deudas << "\n";
    }
    virtual void mostrarTabla() const = 0; // Método para mostrar tabla de gastos e ingresos
    virtual void mostrarRecomendaciones() const = 0; // Método para mostrar recomendaciones
    // Método para autenticar al usuario
    bool autenticar(const string &pass) const {
        return encriptar(pass) == contraseña; // Compara la contraseña encriptada
    }
    string getNombre() const { return nombre; } // Método para obtener el nombre
    virtual ~Usuario() {} // Destructor virtual
};

// Clase para representar un usuario estudiante
class UsuarioEstudiante : public Usuario {
private:
    bool recibeMesada; // Indica si recibe mesada
    double mesada; // Monto de la mesada
    string frecuenciaMesada; // Frecuencia de la mesada
    bool tieneTrabajo; // Indica si tiene trabajo
    double ingresoTrabajo; // Ingreso del trabajo
    bool gastaEnPasaje; // Indica si gasta en pasaje
    bool tieneMovilidad; // Indica si tiene movilidad propia
    bool loLlevan; // Indica si lo llevan sus padres
    bool viveSolo; // Indica si vive solo
    double alquiler; // Monto de alquiler
    double gastoComida; // Gasto en comida
    double gastosSecundariosEst; // Gastos secundarios del estudiante
    double gastosTerciariosEst; // Gastos terciarios del estudiante
public:
    // Constructor que inicializa los atributos del usuario estudiante
    UsuarioEstudiante(string nom, string pass, int ed, Fecha fecha, string mon)
      : Usuario(nom, pass, ed, fecha, mon),
        recibeMesada(false), mesada(0), frecuenciaMesada(""),
        tieneTrabajo(false), ingresoTrabajo(0),
        gastaEnPasaje(false), tieneMovilidad(false), loLlevan(false), viveSolo(false),
        alquiler(0), gastoComida(0), gastosSecundariosEst(0), gastosTerciariosEst(0) {}
    
    // Método para ingresar datos específicos del estudiante
    void ingresarDatos() override {
        cout << "\n\033[1;36m---- Informacion de Estudiante ----\033[0m\n";
        char resp;
        cout << "¿Recibe mesada? (s/n): ";
        cin >> resp;
        recibeMesada = (resp=='s' || resp=='S'); // Lee si recibe mesada
        if(recibeMesada) {
            cout << "Ingrese el monto de la mesada: ";
            cin >> mesada; // Lee el monto de la mesada
            cout << "Ingrese la frecuencia (diario/semanal/mensual): ";
            cin >> frecuenciaMesada; // Lee la frecuencia de la mesada
            ingresos += mesada; // Suma la mesada a los ingresos
        }
        cout << "¿Tiene trabajo? (s/n): ";
        cin >> resp;
        tieneTrabajo = (resp=='s' || resp=='S'); // Lee si tiene trabajo
        if(tieneTrabajo) {
            cout << "Ingrese su ingreso mensual por trabajo: ";
            cin >> ingresoTrabajo; // Lee el ingreso del trabajo
            ingresos += ingresoTrabajo; // Suma el ingreso del trabajo a los ingresos
        }
        cout << "¿Gasta en pasaje? (s/n): ";
        cin >> resp;
        gastaEnPasaje = (resp=='s' || resp=='S'); // Lee si gasta en pasaje
        if(gastaEnPasaje) {
            double gastoPasaje;
            cout << "Ingrese gasto mensual en pasaje: ";
            cin >> gastoPasaje; // Lee el gasto en pasaje
            gastosPrimarios += gastoPasaje; // Suma el gasto en pasaje a los gastos primarios
        }
        cout << "¿Tiene movilidad propia? (s/n): ";
        cin >> resp;
        tieneMovilidad = (resp=='s' || resp=='S'); // Lee si tiene movilidad propia
        cout << "¿Lo llevan sus padres? (s/n): ";
        cin >> resp;
        loLlevan = (resp=='s' || resp=='S'); // Lee si lo llevan sus padres
        cout << "¿Vive solo? (s/n): ";
        cin >> resp;
        viveSolo = (resp=='s' || resp=='S'); // Lee si vive solo
        if(viveSolo) {
            cout << "Ingrese el monto mensual de alquiler: ";
            cin >> alquiler; // Lee el monto de alquiler
            gastosPrimarios += alquiler; // Suma el alquiler a los gastos primarios
            cout << "¿Compra sus propias comidas? (s/n): ";
            cin >> resp;
            if(resp=='s' || resp=='S'){
                cout << "Ingrese gasto mensual aproximado en comidas: ";
                cin >> gastoComida; // Lee el gasto en comida
                gastosPrimarios += gastoComida; // Suma el gasto en comida a los gastos primarios
            }
        } else {
            cout << "¿Recibe dinero de sus padres? (s/n): ";
            cin >> resp;
            if(!(resp=='s' || resp=='S')){
                cout << "Mensaje: ¡Nunca te rindas y sigue contra las adversidades!\n"; // Mensaje motivacional
            }
        }
        cout << "Ingrese gastos secundarios mensuales (ropa, útiles, etc.): ";
        cin >> gastosSecundariosEst; // Lee los gastos secundarios
        gastosSecundarios += gastosSecundariosEst; // Suma los gastos secundarios
        cout << "Ingrese gastos terciarios mensuales (gastos no necesarios): ";
        cin >> gastosTerciariosEst; // Lee los gastos terciarios
        gastosTerciarios += gastosTerciariosEst; // Suma los gastos terciarios
        cout << "Ingrese su dinero ahorrado: ";
        cin >> ahorro; // Lee el ahorro
        cout << "Ingrese su dinero invertido: ";
        cin >> inversion; // Lee la inversión
        cout << "Ingrese sus deudas pendientes: ";
        cin >> deudas; // Lee las deudas
        if(viveSolo)
            estadoFamiliar = "solo"; // Establece el estado familiar
        else
            estadoFamiliar = "con familia"; // Establece el estado familiar
    }
    
    // Método para mostrar información del estudiante
    void mostrarInformacion() const override {
        cout << "\n\033[1;36m---- Información de Estudiante ----\033[0m\n";
        Usuario::mostrarInformacion(); // Llama al método de la clase base
        cout << "Ingresos totales: $" << fixed << setprecision(2) << ingresos << "\n";
        cout << "Gastos primarios: $" << gastosPrimarios << "\n";
        cout << "Gastos secundarios: $" << gastosSecundarios << "\n";
        cout << "Gastos terciarios: $" << gastosTerciarios << "\n";
        cout << "Ahorro: $" << ahorro << "\n";
        cout << "Inversión: $" << inversion << "\n";
        cout << "Estado familiar: " << estadoFamiliar << "\n";
    }
    
    // Método para mostrar tabla de gastos e ingresos
    void mostrarTabla() const override {
        cout << "\n\033[1;36m---- Tabla de Gastos e Ingresos (Estudiante) ----\033[0m\n";
        double neto = ingresos - (gastosPrimarios + gastosSecundarios + gastosTerciarios); // Calcula ingreso neto
        cout << "Ingreso Neto: $" << neto << "\n";
        double porcentajeGastos = (ingresos > 0 ? ((gastosPrimarios + gastosSecundarios + gastosTerciarios) / ingresos) * 100 : 0);
        double porcentajeAhorro = (ingresos > 0 ? (ahorro / ingresos) * 100 : 0);
        double porcentajeTerceros = (ingresos > 0 ? (gastosTerciarios / ingresos) * 100 : 0);
        double porcentajeInversion = (ingresos > 0 ? (inversion / ingresos) * 100 : 0);
        cout << fixed << setprecision(2);
        cout << "Porcentaje de Gastos Totales: " << porcentajeGastos << "%\n";
        cout << "Porcentaje de Ahorro: " << porcentajeAhorro << "%\n";
        cout << "Porcentaje de Gastos Terciarios: " << porcentajeTerceros << "%\n";
        cout << "Porcentaje de Inversión: " << porcentajeInversion << "%\n";
        // Mensajes de evaluación de finanzas
        if(fabs(porcentajeGastos - 50) <= 2 && fabs(porcentajeAhorro - 20) <= 2 &&
           fabs(porcentajeTerceros - 10) <= 2 && fabs(porcentajeInversion - 10) <= 2)
            cout << "\033[32mTodo está en orden. ¡Buen trabajo!\033[0m\n";
        else if(fabs(porcentajeGastos - 50) <= 5 || fabs(porcentajeAhorro - 20) <= 5 ||
                fabs(porcentajeTerceros - 10) <= 5 || fabs(porcentajeInversion - 10) <= 5)
            cout << "\033[33mRevisa tus gastos, podrías reducir un poco.\033[0m\n";
        else
            cout << "\033[31mAlerta: Revisa urgentemente tus finanzas para evitar deudas.\033[0m\n";
    }
    
    // Método para mostrar recomendaciones financieras
    void mostrarRecomendaciones() const override {
        cout << "\n\033[1;36m---- Recomendaciones para Estudiante ----\033[0m\n";
        if(ingresos > 0) {
            if((ahorro / ingresos) * 100 < 20)
                cout << "- Aumenta tu ahorro para alcanzar al menos el 20% de tus ingresos.\n";
            if((inversion / ingresos) * 100 < 10)
                cout << "- Evalúa invertir más para diversificar tus ingresos.\n";
            if(deudas > (ingresos * 0.5))
                cout << "- Tus deudas son elevadas en comparación con tus ingresos.\n";
        } else {
            cout << "- No se han registrado ingresos suficientes para dar recomendaciones.\n";
        }
    }
};

// Clase para representar un usuario docente
class UsuarioDocente : public Usuario {
private:
    string materia; // Materia que imparte
    string viveCon; // Indica si vive solo o con familia
    double salario; // Salario del docente
    double gastosFamiliares; // Gastos familiares
public:
    // Constructor que inicializa los atributos del usuario docente
    UsuarioDocente(string nom, string pass, int ed, Fecha fecha, string mon)
      : Usuario(nom, pass, ed, fecha, mon), materia(""), viveCon(""), salario(0), gastosFamiliares(0) {}
    
    // Método para ingresar datos específicos del docente
    void ingresarDatos() override {
        cout << "\n\033[1;35m---- Información de Docente ----\033[0m\n";
        cout << "Ingrese su edad: ";
        cin >> edad; // Lee la edad
        cout << "Ingrese la materia que imparte: ";
        cin >> materia; // Lee la materia
        cout << "¿Vive solo o con familia? (solo/familia): ";
        cin >> viveCon; // Lee el estado de vivienda
        cout << "Ingrese su salario mensual: ";
        cin >> salario; // Lee el salario
        ingresos = salario; // Asigna el salario a los ingresos
        if(viveCon == "solo") {
            double alquiler, comida;
            cout << "Ingrese el monto de alquiler mensual: ";
            cin >> alquiler; // Lee el alquiler
            cout << "Ingrese gasto mensual en comida: ";
            cin >> comida; // Lee el gasto en comida
            gastosPrimarios = alquiler + comida; // Suma alquiler y comida a los gastos primarios
        } else {
            cout << "Ingrese gastos familiares mensuales aproximados: ";
            cin >> gastosFamiliares; // Lee los gastos familiares
            gastosPrimarios = gastosFamiliares; // Asigna gastos familiares a los gastos primarios
        }
        cout << "Ingrese gastos secundarios mensuales: ";
        cin >> gastosSecundarios; // Lee los gastos secundarios
        cout << "Ingrese gastos terciarios mensuales: ";
        cin >> gastosTerciarios; // Lee los gastos terciarios
        cout << "Ingrese dinero ahorrado: ";
        cin >> ahorro; // Lee el ahorro
        cout << "Ingrese dinero invertido: ";
        cin >> inversion; // Lee la inversión
        cout << "Ingrese sus deudas pendientes: ";
        cin >> deudas; // Lee las deudas
        estadoFamiliar = viveCon; // Establece el estado familiar
    }
    
    // Método para mostrar información del docente
    void mostrarInformacion() const override {
        cout << "\n\033[1;35m---- Información de Docente ----\033[0m\n";
        Usuario::mostrarInformacion(); // Llama al método de la clase base
        cout << "Materia: " << materia << "\nSalario: $" << salario << "\n";
        cout << "Gastos primarios: $" << gastosPrimarios << "\nGastos secundarios: $" << gastosSecundarios 
             << "\nGastos terciarios: $" << gastosTerciarios << "\n";
        cout << "Ahorro: $" << ahorro << "\nInversión: $" << inversion << "\nEstado: " << estadoFamiliar << "\n";
    }
    
    // Método para mostrar tabla de gastos e ingresos
    void mostrarTabla() const override {
        cout << "\n\033[1;35m---- Tabla de Gastos e Ingresos (Docente) ----\033[0m\n";
        double neto = ingresos - (gastosPrimarios + gastosSecundarios + gastosTerciarios); // Calcula ingreso neto
        cout << "Ingreso Neto: $" << neto << "\n";
        double porcentajeGastos = (ingresos > 0 ? ((gastosPrimarios + gastosSecundarios + gastosTerciarios) / ingresos) * 100 : 0);
        double porcentajeAhorro = (ingresos > 0 ? (ahorro / ingresos) * 100 : 0);
        double porcentajeTerceros = (ingresos > 0 ? (gastosTerciarios / ingresos) * 100 : 0);
        double porcentajeInversion = (ingresos > 0 ? (inversion / ingresos) * 100 : 0);
        cout << fixed << setprecision(2);
        cout << "Porcentaje de Gastos Totales: " << porcentajeGastos << "%\n";
        cout << "Porcentaje de Ahorro: " << porcentajeAhorro << "%\n";
        cout << "Porcentaje de Gastos Terciarios: " << porcentajeTerceros << "%\n";
        cout << "Porcentaje de Inversión: " << porcentajeInversion << "%\n";
    }
    
    // Método para mostrar recomendaciones financieras
    void mostrarRecomendaciones() const override {
        cout << "\n\033[1;35m---- Recomendaciones para Docente ----\033[0m\n";
        if(ingresos > 0) {
            if((ahorro / ingresos) * 100 < 15)
                cout << "- Intenta incrementar tu ahorro, idealmente supera el 15% de tus ingresos.\n";
            if(deudas > (ingresos * 0.4))
                cout << "- Tus deudas superan el 40% de tus ingresos, revisa opciones para consolidarlas.\n";
        } else {
            cout << "- No se han registrado ingresos suficientes para dar recomendaciones.\n";
        }
    }
};

// Clase para representar un usuario padre/tutor
class UsuarioPadreTutor : public Usuario {
private:
    string viveCon; // Indica si vive solo o con familia
    double salario; // Salario del padre/tutor
    double gastosFamiliares; // Gastos familiares
public:
    // Constructor que inicializa los atributos del usuario padre/tutor
    UsuarioPadreTutor(string nom, string pass, int ed, Fecha fecha, string mon)
      : Usuario(nom, pass, ed, fecha, mon), viveCon(""), salario(0), gastosFamiliares(0) {}
    
    // Método para ingresar datos específicos del padre/tutor
    void ingresarDatos() override {
        cout << "\n\033[1;33m---- Información de Padre/Tutor ----\033[0m\n";
        cout << "Ingrese su edad: ";
        cin >> edad; // Lee la edad
        cout << "¿Vive solo o con familia? (solo/familia): ";
        cin >> viveCon; // Lee el estado de vivienda
        cout << "Ingrese su salario mensual: ";
        cin >> salario; // Lee el salario
        ingresos = salario; // Asigna el salario a los ingresos
        if(viveCon == "solo") {
            double alquiler, comida;
            cout << "Ingrese el monto de alquiler mensual: ";
            cin >> alquiler; // Lee el alquiler
            cout << "Ingrese gasto mensual en comida: ";
            cin >> comida; // Lee el gasto en comida
            gastosPrimarios = alquiler + comida; // Suma alquiler y comida a los gastos primarios
        } else {
            cout << "Ingrese gastos familiares mensuales aproximados: ";
            cin >> gastosFamiliares; // Lee los gastos familiares
            gastosPrimarios = gastosFamiliares; // Asigna gastos familiares a los gastos primarios
        }
        cout << "Ingrese gastos secundarios mensuales: ";
        cin >> gastosSecundarios; // Lee los gastos secundarios
        cout << "Ingrese gastos terciarios mensuales: ";
        cin >> gastosTerciarios; // Lee los gastos terciarios
        cout << "Ingrese dinero ahorrado: ";
        cin >> ahorro; // Lee el ahorro
        cout << "Ingrese dinero invertido: ";
        cin >> inversion; // Lee la inversión
        cout << "Ingrese sus deudas pendientes: ";
        cin >> deudas; // Lee las deudas
        estadoFamiliar = viveCon; // Establece el estado familiar
    }
    
    // Método para mostrar información del padre/tutor
    void mostrarInformacion() const override {
        cout << "\n\033[1;33m---- Información de Padre/Tutor ----\033[0m\n";
        Usuario::mostrarInformacion(); // Llama al método de la clase base
        cout << "Salario: $" << ingresos << "\nGastos primarios: $" << gastosPrimarios 
             << "\nGastos secundarios: $" << gastosSecundarios << "\nGastos terciarios: $" << gastosTerciarios << "\n";
        cout << "Ahorro: $" << ahorro << "\nInversión: $" << inversion << "\nEstado: " << estadoFamiliar << "\n";
    }
    
    // Método para mostrar tabla de gastos e ingresos
    void mostrarTabla() const override {
        cout << "\n\033[1;33m---- Tabla de Gastos e Ingresos (Padre/Tutor) ----\033[0m\n";
        double neto = ingresos - (gastosPrimarios + gastosSecundarios + gastosTerciarios); // Calcula ingreso neto
        cout << "Ingreso Neto: $" << neto << "\n";
        double porcentajeGastos = (ingresos > 0 ? ((gastosPrimarios + gastosSecundarios + gastosTerciarios) / ingresos) * 100 : 0);
        double porcentajeAhorro = (ingresos > 0 ? (ahorro / ingresos) * 100 : 0);
        double porcentajeTerceros = (ingresos > 0 ? (gastosTerciarios / ingresos) * 100 : 0);
        double porcentajeInversion = (ingresos > 0 ? (inversion / ingresos) * 100 : 0);
        cout << fixed << setprecision(2);
        cout << "Porcentaje de Gastos Totales: " << porcentajeGastos << "%\n";
        cout << "Porcentaje de Ahorro: " << porcentajeAhorro << "%\n";
        cout << "Porcentaje de Gastos Terciarios: " << porcentajeTerceros << "%\n";
        cout << "Porcentaje de Inversión: " << porcentajeInversion << "%\n";
    }
    
    // Método para mostrar recomendaciones financieras
    void mostrarRecomendaciones() const override {
        cout << "\n\033[1;33m---- Recomendaciones para Padre/Tutor ----\033[0m\n";
        if(ingresos > 0) {
            if((ahorro / ingresos) * 100 < 10)
                cout << "- Es recomendable aumentar el ahorro, apunta a al menos el 10% de tus ingresos.\n";
            if(deudas > (ingresos * 0.5))
                cout << "- Tus deudas son altas. Considera estrategias para reducirlas o refinanciarlas.\n";
        } else {
            cout << "- No se han registrado ingresos suficientes para dar recomendaciones.\n";
        }
    }
};

// Clase para representar un usuario emprendedor
class UsuarioEmprendedor : public Usuario {
private:
    string negocio; // Nombre del negocio
public:
    // Constructor que inicializa los atributos del usuario emprendedor
    UsuarioEmprendedor(string nom, string pass, int ed, Fecha fecha, string mon)
      : Usuario(nom, pass, ed, fecha, mon), negocio("") {}
    
    // Método para ingresar datos específicos del emprendedor
    void ingresarDatos() override {
        cout << "\n\033[1;32m---- Información de Emprendedor ----\033[0m\n";
        cout << "Ingrese su edad: ";
        cin >> edad; // Lee la edad
        cout << "Ingrese el nombre de su negocio: ";
        cin >> negocio; // Lee el nombre del negocio
        cout << "Ingrese su ingreso mensual (ventas/provisión): ";
        cin >> ingresos; // Lee los ingresos
        cout << "Ingrese gastos primarios mensuales: ";
        cin >> gastosPrimarios; // Lee los gastos primarios
        cout << "Ingrese gastos secundarios mensuales: ";
        cin >> gastosSecundarios; // Lee los gastos secundarios
        cout << "Ingrese gastos terciarios mensuales: ";
        cin >> gastosTerciarios; // Lee los gastos terciarios
        cout << "Ingrese dinero ahorrado: ";
        cin >> ahorro; // Lee el ahorro
        cout << "Ingrese dinero invertido: ";
        cin >> inversion; // Lee la inversión
        cout << "Ingrese sus deudas pendientes: ";
        cin >> deudas; // Lee las deudas
        estadoFamiliar = "solo"; // Establece el estado familiar
    }
    
    // Método para mostrar información del emprendedor
    void mostrarInformacion() const override {
        cout << "\n\033[1;32m---- Información de Emprendedor ----\033[0m\n";
        Usuario::mostrarInformacion(); // Llama al método de la clase base
        cout << "Negocio: " << negocio << "\nIngresos: $" << ingresos << "\n";
        cout << "Gastos primarios: $" << gastosPrimarios << "\nGastos secundarios: $" << gastosSecundarios 
             << "\nGastos terciarios: $" << gastosTerciarios << "\n";
        cout << "Ahorro: $" << ahorro << "\nInversión: $" << inversion << "\n";
    }
    
    // Método para mostrar tabla de gastos e ingresos
    void mostrarTabla() const override {
        cout << "\n\033[1;32m---- Tabla de Gastos e Ingresos (Emprendedor) ----\033[0m\n";
        double neto = ingresos - (gastosPrimarios + gastosSecundarios + gastosTerciarios); // Calcula ingreso neto
        cout << "Ingreso Neto: $" << neto << "\n";
        double porcentajeGastos = (ingresos > 0 ? ((gastosPrimarios + gastosSecundarios + gastosTerciarios) / ingresos) * 100 : 0);
        double porcentajeAhorro = (ingresos > 0 ? (ahorro / ingresos) * 100 : 0);
        double porcentajeTerceros = (ingresos > 0 ? (gastosTerciarios / ingresos) * 100 : 0);
        double porcentajeInversion = (ingresos > 0 ? (inversion / ingresos) * 100 : 0);
        cout << fixed << setprecision(2);
        cout << "Porcentaje de Gastos Totales: " << porcentajeGastos << "%\n";
        cout << "Porcentaje de Ahorro: " << porcentajeAhorro << "%\n";
        cout << "Porcentaje de Gastos Terciarios: " << porcentajeTerceros << "%\n";
        cout << "Porcentaje de Inversión: " << porcentajeInversion << "%\n";
        // Mensajes de evaluación de finanzas
        if(fabs(porcentajeGastos - 70) <= 2 && fabs(porcentajeAhorro - 20) <= 2 && fabs(porcentajeTerceros - 10) <= 2)
            cout << "\033[32mFinanzas en orden. ¡Sigue así!\033[0m\n";
        else if(fabs(porcentajeGastos - 70) <= 5 || fabs(porcentajeAhorro - 20) <= 5 || fabs(porcentajeTerceros - 10) <= 5)
            cout << "\033[33mRevisa tus gastos, podrías ajustar un poco.\033[0m\n";
        else
            cout << "\033[31mAlerta: Revisa urgentemente tus finanzas.\033[0m\n";
    }
    
    // Método para mostrar recomendaciones financieras
    void mostrarRecomendaciones() const override {
        cout << "\n\033[1;32m---- Recomendaciones para Emprendedor ----\033[0m\n";
        if(ingresos > 0) {
            if((ahorro / ingresos) * 100 < 25)
                cout << "- Aumenta tu ahorro para lograr al menos un 25% de tus ingresos.\n";
            if(deudas > (ingresos * 0.3))
                cout << "- Considera refinanciar tus deudas para reducir el porcentaje de endeudamiento.\n";
        } else {
            cout << "- No se han registrado ingresos suficientes para dar recomendaciones.\n";
        }
    }
};

// Función para mostrar un diccionario financiero
void mostrarDiccionario() {
    cout << "\nDiccionario Financiero:\n";
    cout << "Ahorro: Parte de los ingresos guardada para el futuro.\n";
    cout << "Inversión: Dinero destinado a generar más ingresos.\n";
    cout << "Presupuesto: Plan financiero que organiza ingresos y gastos.\n";
    cout << "Gasto hormiga: Pequeñas compras diarias que afectan el ahorro.\n";
    cout << "Activos: Bienes o inversiones que generan ingresos.\n";
    cout << "Pasivos: Deudas u obligaciones financieras.\n";
    cout << "Interés compuesto: Beneficio generado sobre intereses previos.\n";
    cout << "Liquidez: Facilidad de convertir un activo en dinero en efectivo.\n";
    cout << "Deuda buena: Préstamo utilizado para generar ingresos.\n";
    cout << "Deuda mala: Préstamo utilizado para gastos innecesarios.\n";
    cout << "Diversificación: Estrategia para reducir riesgos financieros.\n";
    cout << "Inflación: Aumento sostenido de los precios en el tiempo.\n";
    cout << "Tasa de interés: Costo del dinero prestado o rendimiento de inversión.\n";
    cout << "Fondo de emergencia: Dinero reservado para imprevistos.\n";
    cout << "Endeudamiento responsable: Uso de crédito con planificación.\n";
    cout << "Capitalización: Acumulación de intereses sobre una inversión.\n";
    cout << "Amortización: Pago gradual de una deuda a lo largo del tiempo.\n";
    cout << "Rentabilidad: Beneficio obtenido en relación con la inversión realizada.\n";
    cout << "Tasa de cambio: Valor de una moneda con respecto a otra.\n";
    cout << "Patrimonio: Conjunto de bienes y deudas de una persona.\n";
    cout << "Flujo de caja: Movimiento de ingresos y egresos en un período.\n";
}

// Función para mostrar un tip financiero aleatorio
void mostrarTipFinanciero() {
    vector<string> tips = {
        "\nAhorre al menos el 20% de sus ingresos.",
        "Evite gastos innecesarios.",
        "Lleve un registro de sus ingresos y egresos.",
        "Utilice un presupuesto mensual.",
        "Invierta en educación financiera.",
        "Elimine deudas lo antes posible.",
        "No gaste más de lo que gana.",
        "Evite compras impulsivas.",
        "Tenga un fondo de emergencia.",
        "Revise su estado financiero regularmente.",
        "Compare precios antes de comprar.",
        "Evite suscribirse a servicios innecesarios.",
        "Reduzca gastos hormiga.",
        "Establezca metas de ahorro.",
        "Use la regla 50/30/20 para su presupuesto.",
        "Pague sus tarjetas de crédito a tiempo.",
        "Evite los préstamos innecesarios.",
        "Planifique sus compras con antelación.",
        "Mantenga un control de sus gastos diarios.",
        "No invierta en algo que no entiende.",
        "Considere múltiples fuentes de ingresos.",
        "Automatice sus ahorros.",
        "Evite gastos por comisiones bancarias innecesarias.",
        "Revise sus suscripciones y cancele las que no use.",
        "Priorice gastos esenciales sobre entretenimiento.",
        "Aproveche descuentos y ofertas sin caer en compras impulsivas.",
        "Revise su historial crediticio periódicamente.",
        "Utilice métodos de pago con recompensas o cashback.",
        "Diversifique sus inversiones para reducir riesgos.",
        "Cree un plan financiero a largo plazo.\n"
    };
    srand(time(0)); // Inicializa la semilla para la generación de números aleatorios
    cout << "\nTip financiero del día: \n" << tips[rand() % tips.size()] << "\n"; // Muestra un tip aleatorio
}

// Función para confirmar la eliminación de un usuario
bool confirmarEliminacion() {
    string confirm;
    cout << "\n¿Está seguro de eliminar el usuario? (si/no): ";
    cin >> confirm;
    if(confirm != "si") return false; // Si la respuesta no es "si", cancela
    cout << "Confirmación final, ¿desea eliminarlo? (si/no): ";
    cin >> confirm;
    return (confirm == "si"); // Retorna verdadero si la respuesta es "si"
}

// Función para confirmar la contraseña
bool confirmarContraseña(const string& original) {
    string pass1, pass2;
    cout << "\nIngrese nuevamente la contraseña: ";
    cin >> pass1; // Lee la primera entrada de contraseña
    cout << "Ingrese nuevamente la contraseña: ";
    cin >> pass2; // Lee la segunda entrada de contraseña
    return (pass1 == original && pass2 == original); // Retorna verdadero si ambas contraseñas coinciden
}

// Clase para gestionar el sistema de usuarios
class SistemaUsuarios {
private:
    vector<Usuario*> usuarios; // Vector que almacena punteros a usuarios
public:
    // Método para agregar un nuevo usuario al sistema
    void agregarUsuario(Usuario* usuario) {
        usuarios.push_back(usuario); // Agrega el usuario al vector
        cout << "\nUsuario creado exitosamente.\n"; // Mensaje de éxito
    }
    
    // Método para autenticar un usuario
    Usuario* autenticarUsuario(const string& nombre, const string& contraseña) {
        for(auto usuario : usuarios) {
            if(usuario->getNombre() == nombre && usuario->autenticar(contraseña))
                return usuario; // Retorna el usuario autenticado
        }
        return nullptr; // Retorna nullptr si no se encuentra el usuario
    }
    
    // Método para eliminar un usuario
    void eliminarUsuario() {
        string nombre, contraseña;
        cout << "\nIngrese el nombre del usuario a eliminar: ";
        cin >> nombre; // Lee el nombre del usuario
        cout << "Ingrese la contraseña: ";
        cin >> contraseña; // Lee la contraseña
        for(size_t i = 0; i < usuarios.size(); i++) {
            if(usuarios[i]->getNombre() == nombre && usuarios[i]->autenticar(contraseña)) {
                if(!confirmarEliminacion()) {
                    cout << "Eliminación cancelada.\n"; // Mensaje de cancelación
                    return;
                }
                if(!confirmarContraseña(contraseña)) {
                    cout << "Contraseña incorrecta. Cancelando eliminación.\n";
                    return;
                }
                delete usuarios[i];
                usuarios.erase(usuarios.begin() + i);
                cout << "Usuario eliminado correctamente.\n";
                return;
            }
        }
        cout << "Usuario no encontrado o contraseña incorrecta.\n";
    }
    ~SistemaUsuarios() {
        for(auto usuario : usuarios) {
            delete usuario;
        }
    }
};

void mostrarMenuPrincipal() {
    cout << "\n\033[1;34m****************************************\033[0m\n";
    cout << "\033[1;34m*          MENÚ PRINCIPAL              *\033[0m\n";
    cout << "\033[1;34m****************************************\033[0m\n";
    cout << "\033[1;32m* 1. Crear Usuario                     *\033[0m\n";
    cout << "\033[1;33m* 2. Iniciar Sesión                    *\033[0m\n";
    cout << "\033[1;35m* 3. Eliminar Usuario                  *\033[0m\n";
    cout << "\033[1;36m* 4. Mostrar Diccionario Financiero    *\033[0m\n";
    cout << "\033[1;31m* 5. Mostrar Tip Financiero            *\033[0m\n";
    cout << "\033[1;37m* 6. Salir                             *\033[0m\n";
    cout << "\033[1;34m****************************************\033[0m\n";
    cout << "\nSeleccione una opción: ";
}

int main() {
    SistemaUsuarios sistema;
    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        cout << "\n\n";
        if(opcion == 1) {
            int tipo;
            cout << "\nSeleccione el tipo de usuario:\n";
            cout << "1. Estudiante\n";
            cout << "2. Docente\n";
            cout << "3. Padre/Tutor\n";
            cout << "4. Emprendedor\n";
            cout << "Opción: ";
            cin >> tipo;
            string nombre, contraseña, mon;
            int edad, d, m, a;
            cout << "\nIngrese su nombre: ";
            cin >> nombre;
            cout << "Cree una contraseña: ";
            cin >> contraseña;
            cout << "Ingrese su moneda (ej: USD, EUR, MXN): ";
            cin >> mon;
            cout << "Ingrese su edad: ";
            cin >> edad;
            cout << "Ingrese la fecha de creación (día mes año): ";
            cin >> d >> m >> a;
            Fecha fecha(d, m, a);
            Usuario* nuevo = nullptr;
            if(tipo == 1) {
                nuevo = new UsuarioEstudiante(nombre, contraseña, edad, fecha, mon);
            } else if(tipo == 2) {
                nuevo = new UsuarioDocente(nombre, contraseña, edad, fecha, mon);
            } else if(tipo == 3) {
                nuevo = new UsuarioPadreTutor(nombre, contraseña, edad, fecha, mon);
            } else if(tipo == 4) {
                nuevo = new UsuarioEmprendedor(nombre, contraseña, edad, fecha, mon);
            } else {
                cout << "Tipo no válido.\n";
                continue;
            }
            nuevo->ingresarDatos();
            sistema.agregarUsuario(nuevo);
        } else if(opcion == 2) {
            string nombre, contraseña;
            cout << "\nIngrese su nombre: ";
            cin >> nombre;
            cout << "Ingrese su contraseña: ";
            cin >> contraseña;
            Usuario* usuario = sistema.autenticarUsuario(nombre, contraseña);
            if(usuario) {
                cout << "Inicio de sesión exitoso.\n";
                usuario->mostrarInformacion();
                usuario->mostrarTabla();
                usuario->mostrarRecomendaciones();
            } else {
                cout << "Usuario o contraseña incorrectos.\n";
            }
        } else if(opcion == 3) {
            sistema.eliminarUsuario();
        } else if(opcion == 4) {
            mostrarDiccionario();
        } else if(opcion == 5) {
            mostrarTipFinanciero();
        }
        cout << "\n\n";
    } while(opcion != 6);
    cout << "\nSaliendo del programa. ¡Hasta luego!\n";
    return 0;
}