#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbrir_triggered();

    void on_actionPreorden_triggered();

    void on_actionBuscar_triggered();

    void on_actionEliminar_triggered();

    void on_actionAbrirArchivoTexto_triggered();

private:
    Ui::MainWindow *ui;
    QProcess *proceso;
};
#endif // MAINWINDOW_H
