#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <dirent.h>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();



private slots:
    void on_actionCrear_nuevo_proyecto_triggered();

    void on_actionNuevo_archivo_triggered();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_actionGuardar_triggered();

    void on_actionAbrir_proyecto_triggered();

    void on_actionAbrir_archivo_triggered();

private:
    Ui::Principal *ui;
    QString nombreProyecto;
    QList<QString> listaClases; //contiene el contendio de las clases
    QList<QString> listaNombreClases; //contiene el nombre de todas las clases
    QString nombreClaseActual;
    int posicionClases=0;
};

#endif // PRINCIPAL_H
