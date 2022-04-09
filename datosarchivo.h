#ifndef DATOSARCHIVO_H
#define DATOSARCHIVO_H
#include <QString>


class DatosArchivo
{
private:
    QString nomArchivo;
    QString numPreorden;
public:
    DatosArchivo(QString nomArchivo, QString numPreorden);
    QString getNomArchivo();
    void setNomArchivo(QString nombreArchivo);
    QString getNumPreorden();
    void setNumPreorden(QString numPreorden);
    QString setNumPreorden();
};

#endif // DATOSARCHIVO_H
