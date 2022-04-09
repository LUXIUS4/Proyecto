#include "datosarchivo.h"

DatosArchivo::DatosArchivo(QString nombreArchivo, QString numPreorden)
{
    this->nomArchivo = nombreArchivo;
    this->numPreorden = numPreorden;
}
//get Nombre del Archivo
QString DatosArchivo::getNomArchivo(){
    return this->nomArchivo;
}
//set Nombre del Archivo
void DatosArchivo::setNomArchivo(QString nombreArchivo){
    this->nomArchivo = nombreArchivo;
}

//get numero en preOrden
QString DatosArchivo::getNumPreorden(){
    return this->numPreorden;
}
//set numeros en Preorden
void DatosArchivo::setNumPreorden(QString numPreorden){
    this->numPreorden = this->numPreorden+numPreorden;
}

