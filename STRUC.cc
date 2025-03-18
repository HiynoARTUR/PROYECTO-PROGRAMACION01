#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// Función plantilla para leer un valor del usuario con un mensaje personalizado
template <typename T>
T leerValor(const string &mensaje) {
    T valor;
    cout << mensaje;
    while (!(cin >> valor)) { // Verifica si la entrada es válida
        cin.clear(); // Limpia el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada no válida
        cout << "Entrada no válida. " << mensaje; // Solicita nuevamente la entrada
    }
    return valor; // Devuelve el valor leído
}

// Función para encriptar una contraseña (simplemente incrementa cada carácter)
string encriptar(const string &s) {
    string resultado = s;
    for (size_t i = 0; i < s.size(); i++) {
        resultado[i] = s[i] + 1; // Incrementa el valor ASCII de cada carácter
    }
    return resultado; // Devuelve la contraseña encriptada
}

// Estructura para representar una fecha
struct Fecha {
    int dia, mes, anio;

    // Constructor que inicializa la fecha y valida su corrección
    Fecha(int d, int m, int a) {
        if (m >= 1 && m <= 12 && d >= 1 && d <= diasEnMes(m, a)) {
            dia = d; mes = m; anio = a; // Asigna valores válidos
        } else {
            cout << "Fecha inválida. Se asignará 01/01/2000 por defecto.\n";
            dia = 1; mes = 1; anio = 2000; // Asigna fecha por defecto
        }
    }

    // Método para verificar si un año es bisiesto
    bool esBisiesto(int a) {
        return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
    }

    // Método para obtener el número de días en un mes dado
    int diasEnMes(int m, int a) {
        if (m == 2) return esBisiesto(a) ? 29 : 28; // Febrero
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30; // Meses con 30 días
        return 31; // Meses con 31 días
    }

    // Método para convertir la fecha a una cadena de texto
    string toString() const {
        return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
    }
};

// Estructura base para representar un usuario
struct Usuario {
    string nombre; // Nombre del usuario
    string contraseña; // Contraseña encriptada
    int edad; // Edad del usuario
    Fecha fechaCreacion; // Fecha de creación de la cuenta
    double ingresos; // Ingresos del usuario
    double gastosPrimarios; // Gastos primarios del usuario
    double gastosSecundarios; // Gastos secundarios del usuario
    double gastosTerciarios; // Gastos terciarios del usuario
    double ahorro; // Ahorro del usuario
    double inversion; // Inversión del usuario
    double deudas; // Deudas del usuario
    string estadoFamiliar; // Estado familiar del usuario
    string moneda; // Moneda utilizada por el usuario

    // Constructor que inicializa un usuario
    Usuario(string nom, string pass, int ed, Fecha fecha, string mon)
        : nombre(nom), contraseña(encriptar(pass)), edad(ed), fechaCreacion(fecha),
          ingresos(0), gastosPrimarios(0), gastosSecundarios(0), gastosTerciarios(0),
          ahorro(0), inversion(0), deudas(0), estadoFamiliar(""), moneda(mon) {}

    // Método virtual para ingresar datos específicos del usuario
    virtual void ingresarDatos() = 0;

    // Método virtual para mostrar información del usuario
    virtual void mostrarInformacion() const {
        cout << "Nombre: " << nombre << "\nEdad: " << edad 
             << "\nFecha de creación: " << fechaCreacion.toString() 
             << "\nMoneda: " << moneda 
             << "\nDeudas: $" << fixed << setprecision(2) << deudas << "\n";
    }

    // Método virtual para mostrar una tabla de gastos e ingresos
    virtual void mostrarTabla() const = 0;

    // Método virtual para mostrar recomendaciones financieras
    virtual void mostrarRecomendaciones() const = 0;

    // Método para autenticar al usuario comparando la contraseña ingresada
    bool autenticar(const string &pass) const {
        return encriptar(pass) == contraseña; // Compara la contraseña encriptada
    }

    // Destructor virtual
    virtual ~Usuario() {}
};

// Estructura para representar un usuario estudiante
struct UsuarioEstudiante : public Usuario {
    bool recibeMesada; // Indica si el estudiante recibe mesada
    double mesada; // Monto de la mesada
    string frecuenciaMesada; // Frecuencia de la mesada
    bool tieneTrabajo; // Indica si el estudiante tiene trabajo
    double ingresoTrabajo; // Ingreso mensual por trabajo
    bool gastaEnPasaje; // Indica si gasta en pasaje
    bool tieneMovilidad; // Indica si tiene movilidad propia
    bool loLlevan; // Indica si lo llevan sus padres
    bool viveSolo; // Indica si vive solo
    double alquiler; // Monto de alquiler mensual
    double gastoComida; // Gasto mensual en comida
    double gastosSecundariosEst; // Gastos secundarios del estudiante
    double gastosTerciariosEst; // Gastos terciarios del estudiante

    // Constructor que inicializa un usuario estudiante
    UsuarioEstudiante(string nom, string pass, int ed, Fecha fecha, string mon)
        : Usuario(nom, pass, ed, fecha, mon),
          recibeMesada(false), mesada(0), frecuenciaMesada(""),
          tieneTrabajo(false), ingresoTrabajo(0),
          gastaEnPasaje(false), tieneMovilidad(false), loLlevan(false), viveSolo(false),
          alquiler(0), gastoComida(0), gastosSecundariosEst(0), gastosTerciariosEst(0) {}

    // Método para ingresar datos específicos del estudiante
    void ingresarDatos() override {
        cout << "\n---- Información de Estudiante ----\n";
        char resp;
        cout << "¿Recibe mesada? (s/n): ";
        cin >> resp;
        recibeMesada = (resp == 's' || resp == 'S');
        if (recibeMesada) {
            cout << "Ingrese el monto de la mesada: ";
            cin >> mesada;
            cout << "Ingrese la frecuencia (diario/semanal/mensual): ";
            cin >> frecuenciaMesada;
            ingresos += mesada; // Suma la mesada a los ingresos
        }
        cout << "¿Tiene trabajo? (s/n): ";
        cin >> resp;
        tieneTrabajo = (resp == 's' || resp == 'S');
        if (tieneTrabajo) {
            cout << "Ingrese su ingreso mensual por trabajo: ";
            cin >> ingresoTrabajo;
            ingresos += ingresoTrabajo; // Suma el ingreso del trabajo a los ingresos
        }
        cout << "¿Gasta en pasaje? (s/n): ";
        cin >> resp;
        gastaEnPasaje = (resp == 's' || resp == 'S');
        if (gastaEnPasaje) {
            double gastoPasaje;
            cout << "Ingrese gasto mensual en pasaje: ";
            cin >> gastoPasaje;
            gastosPrimarios += gastoPasaje; // Suma el gasto de pasaje a los gastos primarios
        }
        cout << "¿Tiene movilidad propia? (s/n): ";
        cin >> resp;
        tieneMovilidad = (resp == 's' || resp == 'S');
        cout << "¿Lo llevan sus padres? (s/n): ";
        cin >> resp;
        loLlevan = (resp == 's' || resp == 'S');
        cout << "¿Vive solo? (s/n): ";
        cin >> resp;
        viveSolo = (resp == 's' || resp == 'S');
        if (viveSolo) {
            cout << "Ingrese el monto mensual de alquiler: ";
            cin >> alquiler;
            gastosPrimarios += alquiler; // Suma el alquiler a los gastos primarios
            cout << "¿Compra sus propias comidas? (s/n): ";
            cin >> resp;
            if (resp == 's' || resp == 'S') {
                cout << "Ingrese gasto mensual aproximado en comidas: ";
                cin >> gastoComida;
                gastosPrimarios += gastoComida; // Suma el gasto de comida a los gastos primarios
            }
        } else {
            cout << "¿Recibe dinero de sus padres? (s/n): ";
            cin >> resp;
            if (!(resp == 's' || resp == 'S')) {
                cout << "Mensaje: ¡Nunca te rindas y sigue contra las adversidades!\n";
            }
        }
        cout << "Ingrese gastos secundarios mensuales (ropa, útiles, etc.): ";
        cin >> gastosSecundariosEst;
        gastosSecundarios += gastosSecundariosEst; // Suma los gastos secundarios
        cout << "Ingrese gastos terciarios mensuales (gastos no necesarios): ";
        cin >> gastosTerciariosEst;
        gastosTerciarios += gastosTerciariosEst; // Suma los gastos terciarios
        cout << "Ingrese su dinero ahorrado: ";
        cin >> ahorro; // Lee el ahorro
        cout << "Ingrese su dinero invertido: ";
        cin >> inversion; // Lee la inversión
        cout << "Ingrese sus deudas pendientes: ";
        cin >> deudas; // Lee las deudas
        estadoFamiliar = viveSolo ? "solo" : "con familia"; // Establece el estado familiar
    }

    // Método para mostrar información del estudiante
    void mostrarInformacion() const override {
        cout << "\n---- Información de Estudiante ----\n";
        Usuario::mostrarInformacion(); // Llama al método base para mostrar información común
        cout << "Ingresos totales: $" << fixed << setprecision(2) << ingresos << "\n";
        cout << "Gastos primarios: $" << gastosPrimarios << "\n";
        cout << "Gastos secundarios: $" << gastosSecundarios << "\n";
        cout << "Gastos terciarios: $" << gastosTerciarios << "\n";
        cout << "Ahorro: $" << ahorro << "\n";
        cout << "Inversión: $" << inversion << "\n";
        cout << "Estado familiar: " << estadoFamiliar << "\n";
    }

    // Método para mostrar una tabla de gastos e ingresos del estudiante
    void mostrarTabla() const override {
        cout << "\n---- Tabla de Gastos e Ingresos (Estudiante) ----\n";
        double neto = ingresos - (gastosPrimarios + gastosSecundarios + gastosTerciarios);
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
        if (fabs(porcentajeGastos - 50) <= 2 && fabs(porcentajeAhorro - 20) <= 2 &&
            fabs(porcentajeTerceros - 10) <= 2 && fabs(porcentajeInversion - 10) <= 2)
            cout << "Todo está en orden. ¡Buen trabajo!\n";
        else if (fabs(porcentajeGastos - 50) <= 5 || fabs(porcentajeAhorro - 20) <= 5 ||
                 fabs(porcentajeTerceros - 10) <= 5 || fabs(porcentajeInversion - 10) <= 5)
            cout << "Revisa tus gastos, podrías reducir un poco.\n";
        else
            cout << "Alerta: Revisa urgentemente tus finanzas para evitar deudas.\n";
    }

    // Método para mostrar recomendaciones financieras para el estudiante
    void mostrarRecomendaciones() const override {
        cout << "\n---- Recomendaciones para Estudiante ----\n";
        if (ingresos > 0) {
            if ((ahorro / ingresos) * 100 < 20)
                cout << "- Aumenta tu ahorro para alcanzar al menos el 20% de tus ingresos.\n";
            if ((inversion / ingresos) * 100 < 10)
                cout << "- Evalúa invertir más para diversificar tus ingresos.\n";
            if (deudas > (ingresos * 0.5))
                cout << "- Tus deudas son elevadas en comparación con tus ingresos.\n";
        } else {
            cout << "- No se han registrado ingresos suficientes para dar recomendaciones.\n";
        }
    }
};

// Clase para manejar el sistema de usuarios
class SistemaUsuarios {
private:
    vector<Usuario*> usuarios; // Vector que almacena punteros a usuarios
public:
    // Método para agregar un nuevo usuario al sistema
    void agregarUsuario(Usuario* usuario) {
        usuarios.push_back(usuario);
        cout << "\nUsuario creado exitosamente.\n";
    }

    // Método para autenticar un usuario
    Usuario* autenticarUsuario(const string& nombre, const string& contraseña) {
        for (auto usuario : usuarios) {
            if (usuario->nombre == nombre && usuario->autenticar(contraseña))
                return usuario; // Devuelve el usuario autenticado
        }
        return nullptr; // Devuelve nullptr si no se encuentra el usuario
    }

    // Método para eliminar un usuario del sistema
    void eliminarUsuario() {
        string nombre, contraseña;
        cout << "\nIngrese el nombre del usuario a eliminar: ";
        cin >> nombre;
        cout << "Ingrese la contraseña: ";
        cin >> contraseña;
        for (size_t i = 0; i < usuarios.size(); i++) {
            if (usuarios[i]->nombre == nombre && usuarios[i]->autenticar(contraseña)) {
                // Confirmación de eliminación
                string confirm;
                cout << "\n¿Está seguro de eliminar el usuario? (si/no): ";
                cin >> confirm;
                if (confirm != "si") {
                    cout << "Eliminación cancelada.\n";
                    return;
                }
                delete usuarios[i]; // Libera la memoria del usuario
                usuarios.erase(usuarios.begin() + i); // Elimina el usuario del vector
                cout << "Usuario eliminado correctamente.\n";
                return;
            }
        }
        cout << "Usuario no encontrado o contraseña incorrecta.\n";
    }

    // Destructor para liberar la memoria de los usuarios
    ~SistemaUsuarios() {
        for (auto usuario : usuarios) {
            delete usuario; // Libera la memoria de cada usuario
        }
    }
};

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    cout << "\n****************************************\n";
    cout << "*          MENÚ PRINCIPAL              *\n";
    cout << "****************************************\n";
    cout << "* 1. Crear Usuario                     *\n";
    cout << "* 2. Iniciar Sesión                    *\n";
    cout << "* 3. Eliminar Usuario                  *\n";
    cout << "* 4. Mostrar Diccionario Financiero    *\n";
    cout << "* 5. Mostrar Tip Financiero            *\n";
    cout << "* 6. Salir                             *\n";
    cout << "****************************************\n";
    cout << "\nSeleccione una opción: ";
}

// Función principal
int main() {
    SistemaUsuarios sistema; // Crea una instancia del sistema de usuarios
    int opcion;
    do {
        mostrarMenuPrincipal(); // Muestra el menú principal
        cin >> opcion; // Lee la opción seleccionada
        cout << "\n\n";
        if (opcion == 1) { // Opción para crear un nuevo usuario
            int tipo;
            cout << "\nSeleccione el tipo de usuario:\n";
            cout << "1. Estudiante\n";
            cout << "2. Docente\n";
            cout << "3. Padre/Tutor\n";
            cout << "4. Emprendedor\n";
            cout << "Opción: ";
            cin >> tipo; // Lee el tipo de usuario
            string nombre, contraseña, mon;
            int edad, d, m, a;
            cout << "\nIngrese su nombre: ";
            cin >> nombre; // Lee el nombre del usuario
            cout << "Cree una contraseña: ";
            cin >> contraseña; // Lee la contraseña
            cout << "Ingrese su moneda (ej: USD, EUR, MXN): ";
            cin >> mon; // Lee la moneda
            cout << "Ingrese su edad: ";
            cin >> edad; // Lee la edad
            cout << "Ingrese la fecha de creación (día mes año): ";
            cin >> d >> m >> a; // Lee la fecha de creación
            Fecha fecha(d, m, a); // Crea una instancia de Fecha
            Usuario* nuevo = nullptr; // Puntero para el nuevo usuario
            if (tipo == 1) {
                nuevo = new UsuarioEstudiante(nombre, contraseña, edad, fecha, mon); // Crea un nuevo usuario estudiante
            } 
            // Aquí puedes agregar más tipos de usuario como UsuarioDocente, UsuarioPadreTutor, UsuarioEmprendedor, etc.
            else {
                cout << "Tipo no válido.\n";
                continue; // Continúa al siguiente ciclo si el tipo no es válido
            }
            nuevo->ingresarDatos(); // Llama al método para ingresar datos del usuario
            sistema.agregarUsuario(nuevo); // Agrega el nuevo usuario al sistema
        } else if (opcion == 2) { // Opción para iniciar sesión
            string nombre, contraseña;
            cout << "\nIngrese su nombre: ";
            cin >> nombre; // Lee el nombre del usuario
            cout << "Ingrese su contraseña: ";
            cin >> contraseña; // Lee la contraseña
            Usuario* usuario = sistema.autenticarUsuario(nombre, contraseña); // Intenta autenticar al usuario
            if (usuario) {
                cout << "Inicio de sesión exitoso.\n";
                usuario->mostrarInformacion(); // Muestra la información del usuario
                usuario->mostrarTabla(); // Muestra la tabla de gastos e ingresos
                usuario->mostrarRecomendaciones(); // Muestra recomendaciones financieras
            } else {
                cout << "Usuario o contraseña incorrectos.\n"; // Mensaje de error
            }
        } else if (opcion == 3) { // Opción para eliminar un usuario
            sistema.eliminarUsuario(); // Llama al método para eliminar un usuario
        } else if (opcion == 4) {
            // Aquí puedes implementar la función para mostrar el diccionario financiero.
        } else if (opcion == 5) {
            // Aquí puedes implementar la función para mostrar un tip financiero.
        }
        cout << "\n\n";
    } while (opcion != 6); // Continúa hasta que el usuario elija salir
    cout << "\nSaliendo del programa. ¡Hasta luego!\n"; // Mensaje de despedida
    return 0; // Fin del programa
}