//Definicion de la clase marco

class Marco{
private:
    int IdMarco;
    int CamposV;
    int CamposO;
    int IdProc;
    char EstadoProc;
    bool SO; //Variable para indicar si esta ocupado por el Sistema Operativo

public:
    //Constructores
    Marco();
    Marco(int, bool);

    //Destructor
    ~Marco();

    //Metodos para el manejo de atributos
    int RegresarIdMarco();
    void CambiarIdMarco(int);
    int RegresarCamposV();
    void CambiarCamposV(int);
    int RegresarCamposO();
    void CambiarCamposO(int);
    int RegresarIdProc();
    void CambiarIdProc(int);
    char RegresarEstadoProc();
    void CambiarEstadoProc(char);
    bool RegresarSO();
    void CambiarSO(bool);
};

// Declaración del método constructor por omisión
Marco::Marco() {
    //Constructor vacío
}

// Declaración del método constructor con parámetros
Marco::Marco(int Id, bool So) {
    IdMarco = Id;
    CamposV = 5;
    CamposO = 0;
    IdProc = 0;
    EstadoProc = 'X'; //La x servira como caracter de excepsion
    SO = So;
}

// Declaración del método destructor
Marco::~Marco() {
    //Destructor vacío
}

//Método para regresar el valor del atributo IdMarco
int Marco::RegresarIdMarco() {
    return IdMarco;
}

//Método para cambiar el valor del atributo IdMarco
void Marco::CambiarIdMarco(int id){
    IdMarco = id;
}

//Método para regresar el valor del atributo CamposV
int Marco::RegresarCamposV() {
    return CamposV;
}

//Método para cambiar el valor del atributo CamposV
void Marco::CambiarCamposV(int campos) {
    CamposV = campos;
}

//Método para regresar el valor del atributo CamposO
int Marco::RegresarCamposO() {
    return CamposO;
}

//Método para cambiar el valor del atributo CamposO
void Marco::CambiarCamposO(int campos) {
    CamposO = campos;
}

//Método para regresar el valor del atributo IdProc
int Marco::RegresarIdProc() {
    return IdProc;
}

//Método para cambiar el valor del atributo
void Marco::CambiarIdProc(int id) {
    IdProc = id;
}

//Método para regresar el valor del atributo EstadoProc
char Marco::RegresarEstadoProc() {
    return EstadoProc;
}

//Método para cambiar el valor del atributo
void Marco::CambiarEstadoProc(char estado) {
    EstadoProc = estado;
}

//Método para regresar el valor del atributo
bool Marco::RegresarSO() {
    return SO;
}

//Método para cambiar el valor del atributo
void Marco::CambiarSO(bool so) {
    SO = so;
}
