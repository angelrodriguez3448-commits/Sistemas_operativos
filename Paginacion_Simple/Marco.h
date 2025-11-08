//Definicion de la clase marco

class Marco{
private:
    int IdMarco;
    int CamposV;
    int CamposO;
    int Pagina;
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
    int RegresaPagina();
    void CambiarPagina(int);
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
    Pagina = 0;
    IdProc = 0;
    EstadoProc = 'X'; //La x servira como caracter de excepsion
    SO = So;
}

// Declaraci�n del m�todo destructor
Marco::~Marco() {
    //Destructor vac�o
}

//Metodo para regresar el valor del atributo IdMarco
int Marco::RegresaIdMarco() {
    return IdMarco;
}

//Metodo para cambiar el valor del atributo IdMarco
void Marco::CambiarIdMarco(int id){
    IdMarco = id;
}

//Metodo para regresar el valor del atributo CamposV
int Marco::RegresaCamposV() {
    return CamposV;
}

//Metodo para cambiar el valor del atributo CamposV
void Marco::CambiarCamposV(int campos) {
    CamposV = campos;
}

//Metodo para regresar el valor del atributo CamposO
int Marco::RegresaCamposO() {
    return CamposO;
}

//Metodo para cambiar el valor del atributo CamposO
void Marco::CambiarCamposO(int campos) {
    CamposO = campos;
}

//Metodo para regresar el valor del atributo Pagina
int Marco::RegresaPagina() {
    return Pagina;
}

//Metodo para cambiar el valor del atributo Pagina
void Marco::CambiarPagina(int pag) {
    Pagina = pag;
}

//Metodo para regresar el valor del atributo IdProc
int Marco::RegresaIdProc() {
    return IdProc;
}

//Metodo para cambiar el valor del atributo
void Marco::CambiarIdProc(int id) {
    IdProc = id;
}

//Metodo para regresar el valor del atributo EstadoProc
char Marco::RegresaEstadoProc() {
    return EstadoProc;
}

//Metodo para cambiar el valor del atributo
void Marco::CambiarEstadoProc(char estado) {
    EstadoProc = estado;
}

//Metodo para regresar el valor del atributo
bool Marco::RegresaSO() {
    return SO;
}

//Metodo para cambiar el valor del atributo
void Marco::CambiarSO(bool so) {
    SO = so;
}
