#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <fstream>
#include <iostream>
#include <QInputDialog>
#include <cstdlib>
#include <QDesktopServices>
#include <QUrl>

/*
PROGRAMADORES:
- Fernando José Lux Gaitan
2590-20-361
- Elwin Waymer Elías de León
2590-17-11383
*/

using namespace std;
QString nomArch, numPreOrden;
struct Nodo{
    int dato;
    Nodo *izq, *der;
}*raiz;

Nodo* iniciar(Nodo* raiz){
    raiz=NULL;
    return raiz;
}

Nodo *nuevoNodo(int valor){//*
    Nodo *nuevo;//*
    nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

Nodo* insertar(Nodo *raiz, int dato){//*
    if(raiz==NULL){
        raiz = nuevoNodo(dato);
    }else if (dato <= raiz->dato){
        raiz->izq = insertar(raiz->izq, dato);
    }else{
        raiz->der = insertar(raiz->der, dato);
    }
    return raiz;
}

void preorden(Nodo *raiz){//*
    if(raiz==NULL){
        return ;
    }
    QString numeros = QString::number(raiz->dato);

    numPreOrden = numPreOrden+"   "+numeros;
    preorden(raiz->izq);
    preorden(raiz->der);

}

bool buscar(Nodo *raiz, int valor){//*
    //1. si el arbol/subarbol está vacio retornar false
    if(raiz == NULL){
        return false;
    //2. si el valor buscado es igual al valor que se encuentra
    //en la raiz, devolver true
    }else if( valor == raiz->dato){
        return true;
    }
    //3. de lo contrario si el valor es menor que el valor que
    //tiene la raiz, buscamos por la izquierda
    else if(valor < raiz->dato){
        return buscar(raiz->izq, valor);
    }
    //4. de lo contrario buscamos por la derecha
    else{
        return buscar(raiz->der, valor);
    }
    //cout<<raiz->dato<<" ";
}

void Reemplazar(Nodo** actual){
    Nodo *p = *actual, *a = (*actual)->izq;
    while(a->der != NULL){
        p = a;
        a = a->der;
    }
    (*actual)->dato = a->dato;
    if(p == (*actual))
        p->izq = a->izq;
    else
        p->der = a->izq;
    (*actual) = a;
}



void Eliminar(int n, Nodo**actual){
    if(*actual==NULL)
        cout<<"Elemento "<<n<<" NO EXISTE";
    else if(n < (*actual)->dato)
        Eliminar(n, &(*actual)->izq);
    else if(n > (*actual)->dato)
        Eliminar(n, &(*actual)->der);
    else{
        Nodo* sup = (*actual);
        if(sup->izq==NULL)
            (*actual) = sup->der;
        else if(sup->der == NULL)
            (*actual) = sup->izq;
        else{
            Reemplazar(&sup);
        }
        delete(sup);
    }
}




/*Nodo* unirABB(Nodo *izq, Nodo* der)
{
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    Nodo* centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}

void elimina(Nodo *&raiz, int x)
{
     if(raiz==NULL) return;

     if(x<raiz->dato)
         elimina(raiz->izq, x);
     else if(x>raiz->dato)
         elimina(raiz->der, x);

     else
     {
         Nodo* p = raiz;
         raiz = unirABB(raiz->izq, raiz->der);
         delete p;
     }
}*/




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Nodo *raiz=NULL;
    Nodo* iniciar(raiz);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbrir_triggered()
{

    std::ifstream lectura;
    QString fileName = QFileDialog::getOpenFileName(this,"Seleccione el Archivo",QDir::homePath());
    QFile file (fileName);


    if(!file.open(QFile::ReadOnly | QFile::Text)){
        if(!file.isOpen()){
            QMessageBox::information(NULL,"MENSAJE","EL USUARIO NO ESCOGIO NINGUN TIPO DE ARCHIVO");
        }else{
            QMessageBox::warning(NULL,"ERROR","Archivo no se puede Abrir");
        }
    }else{
        QMessageBox::information(NULL,"Ubicacion Del Archivo",fileName);
        nomArch = fileName;
        int conteo=0;
        std::string texto="", lin="", numtxt="";
        QTextStream in (&file);
        QString linea = in.readAll();
        lectura.open(fileName.toStdString());

        while(std::getline(lectura, texto)){
                 lin = lin+texto+"\n";
                 numtxt = texto;
                 int dato = (int)atof(numtxt.c_str());
                 if(numtxt.length()==0){

                 }else{
                     conteo++;
                     raiz = insertar(raiz, dato);
                 }
        }
        lectura.close();
        file.close();

        ui->plainTextEdit->setPlainText("ID  NOMBRE\n"+linea);
        QMessageBox::information(NULL,"FeedBack","Archivo abierto correctamente\nSe leyeron "+QString::number(conteo)+" datos correctamente");
    }
}


void MainWindow::on_actionPreorden_triggered()
{
    if(raiz==NULL){
       QMessageBox::information(NULL,"Informacion","Arbol Vacio");
    }else{
       preorden(raiz);
       QMessageBox::about(NULL,"NUMEROS EN PREORDEN",numPreOrden);
       numPreOrden = "";
    }

}


void MainWindow::on_actionBuscar_triggered()
{
    if(raiz==NULL){
        QMessageBox::information(NULL,"Informacion","Arbol Vacio");
    }else{
        int n = QInputDialog::getInt(NULL,"Busqueda por ID","Ingrese el numero a buscar:");
        bool busqueda = buscar(raiz,n);
        if(busqueda==true){
            std::ifstream lectura;
            lectura.open(nomArch.toStdString());
            std::string texto="", lin="", numtxt="";

            while(std::getline(lectura, texto)){
                     lin = lin+texto+"\n";
                     numtxt = texto;
                     int dato = (int)atof(numtxt.c_str());
                     int espacio = numtxt.find(",",0);
                     std::string nom = numtxt.erase(0,espacio);
                     std::string nombre = nom.erase(0,1);
                     if(dato==n){
                         QMessageBox::information(NULL,"Busqueda Exitosa","Se encontro el valor "+QString::number(dato)+" en el Arbol que corresponde al nombre de "+nombre.c_str());
                     }
                     numtxt="";
            }
            lectura.close();

        }else{
            QMessageBox::information(NULL,"INFORMACION","Valor no encontrado");
        }

    }

}


void MainWindow::on_actionEliminar_triggered()
{
    if(raiz==NULL){
        QMessageBox::information(NULL,"Informacion","Arbol Vacio");
    }else{
        int n = QInputDialog::getInt(NULL,"Busqueda","Ingrese el numero que desea eliminar del arbol y del archivo:");
        bool busqueda = buscar(raiz,n);
        if(busqueda==true){
            Eliminar(n,&raiz);
            std::ifstream lectura;
            std::ofstream escritura;
            lectura.open(nomArch.toStdString());
            std::string texto="", linea="", numtxt="";

            while(std::getline(lectura,linea)){
                     //lin = lin+texto+"\n";
                     numtxt = linea;
                     int dato = (int)atof(numtxt.c_str());

                     if(dato!=n){
                         texto = texto+linea+"\n";
                     }
                     numtxt="";
            }lectura.close();
            escritura.open(nomArch.toStdString(),std::ios_base::out);
            if(!escritura.is_open()){
                QMessageBox::warning(NULL,"ERROR","FALLO AL ABRIR EL ARCHIVO");
            }else{
                escritura<<texto;
                QString text = texto.c_str();
                ui->plainTextEdit->setPlainText("ID NOMBRE\n"+text);
            }escritura.close();
            QMessageBox::information(NULL,"INFORMACION","ARCHIVO Y ARBOL ACTUALIZADO CORRECTAMENTE");
        }else{
            QMessageBox::information(NULL,"INFORMACION","Valor no encontrado");
        }
    }

}


void MainWindow::on_actionAbrirArchivoTexto_triggered()
{
    if(nomArch==""){
        QMessageBox::information(NULL,"INFORMACION","AUN NO SE HA ABIERTO ALGUN ARCHIVO");
    }else{

        QDesktopServices::openUrl(QUrl("file:///"+nomArch,QUrl::TolerantMode));
    }

}

