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
    int RegresaIdMarco();
    void CambiarIdMarco(int);
    int RegresaCamposV();
    void CambiarCamposV(int);
    int RegresaCamposO();
    void CambiarCamposO(int);
    int RegresaIdProc();
    void CambiarIdProc(int);
    char RegresaEstadoProc();
    void CambiarEstadoProc(char);
    bool RegresaSO();
    void CambiarSO(bool);
};

// Declaraci�n del m�todo constructor por omisi�n
Marco::Marco() {
    //Constructor vac�o
}

// Declaraci�n del m�todo constructor con par�metros
Marco::Marco(int Id, bool So) {
    IdMarco = Id;
    CamposV = 5;
    CamposO = 0;
    IdProc = 0;
    EstadoProc = 'X'; //La x servira como caracter de excepsion
    SO = So;
}

// Declaraci�n del m�todo destructor
Marco::~Marco() {
    //Destructor vac�o
}

//M�todo para regresar el valor del atributo IdMarco
int Marco::RegresaIdMarco() {
    return IdMarco;
}

//M�todo para cambiar el valor del atributo IdMarco
void Marco::CambiarIdMarco(int id){
    IdMarco = id;
}

//M�todo para regresar el valor del atributo CamposV
int Marco::RegresaCamposV() {
    return CamposV;
}

//M�todo para cambiar el valor del atributo CamposV
void Marco::CambiarCamposV(int campos) {
    CamposV = campos;
}

//M�todo para regresar el valor del atributo CamposO
int Marco::RegresaCamposO() {
    return CamposO;
}

//M�todo para cambiar el valor del atributo CamposO
void Marco::CambiarCamposO(int campos) {
    CamposO = campos;
}

//M�todo para regresar el valor del atributo IdProc
int Marco::RegresaIdProc() {
    return IdProc;
}

//M�todo para cambiar el valor del atributo
void Marco::CambiarIdProc(int id) {
    IdProc = id;
}

//M�todo para regresar el valor del atributo EstadoProc
char Marco::RegresaEstadoProc() {
    return EstadoProc;
}

//M�todo para cambiar el valor del atributo
void Marco::CambiarEstadoProc(char estado) {
    EstadoProc = estado;
}

//M�todo para regresar el valor del atributo
bool Marco::RegresaSO() {
    return SO;
}

//M�todo para cambiar el valor del atributo
void Marco::CambiarSO(bool so) {
    SO = so;
}
