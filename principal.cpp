#include "principal.h"
#include "ui_principal.h"
#include <QInputDialog>
#include <QString>


Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);

}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_actionCrear_nuevo_proyecto_triggered()
{
    bool ok;
holi:
    QString text = QInputDialog::getText(this, "Proyecto 2","Ingrese el nombre del nuevo proyecto: ", QLineEdit::Normal,"", &ok);
    if ( ok && !text.isEmpty() ) {
        // el usuario ingresó ok e ingreso algo
        DIR* dir = opendir(text.toLatin1());
        if (dir)
        {
            /* El proyecto ya existe */

            //sacar messagebox
            QMessageBox msgBox;
            msgBox.setText("El proyecto ya existe, ingrese otro nombre.");
            msgBox.exec();
            closedir(dir);
            goto holi;
        }
        else
        {
            /* El directorio no existe y se crea. */
            system("mkdir " + text.toLatin1());
            nombreProyecto = text;
            //pidiendo el nombre de la clase principal
            QString texto = QInputDialog::getText(this, "Proyecto 2","Ingrese el nombre de la clase principal: ", QLineEdit::Normal,"", &ok);
            if ( ok && !texto.isEmpty() ) {

                //crear archivo principal
                QFile file( nombreProyecto.toLatin1() + "/" + texto.toLatin1() + ".obj" );
                if ( file.open(QIODevice::ReadWrite) )
                {
                    QTextStream stream( &file );
                    stream << "para_todos clase " + texto.toLatin1() + " $$ \n " +
                              "def para_todos "+ texto.toLatin1() +  " ninguno() $$ \n $$ \n $$" << endl;
                    listaClases.append("para_todos clase " + texto + " $$ \n " +
                                       "def para_todos "+ texto +  " ninguno() $$ \n $$ \n $$");
                    this->posicionClases++;
                    this->nombreClaseActual = texto;
                    file.close();
                }


//                //agregando el nombre del archivo al listView
//                QStandardItem* items = new QStandardItem(texto);
//                QStandardItemModel* modeloLista = new QStandardItemModel();
//                modeloLista->appendRow(items);
//                items->setEditable(false);
//                this->ui->listView->setModel(modeloLista);


                //agregando a listWidget
                this->ui->listWidget->addItem(texto);
                this->ui->listWidget->setCurrentRow(this->listaClases.size()-1);

                //creando el archivo de lista de clases
                QFile archivoClases( nombreProyecto.toLatin1() + "/clases.cl" );
                if ( archivoClases.open(QIODevice::ReadWrite) )
                {
                    QTextStream stream( &archivoClases );
                    stream << texto.toLatin1() + ".obj"<< endl;
                    archivoClases.close();
                }

                //agregando a la lista de nombre de clases
                listaNombreClases.append(texto + ".obj");

                //desplegando el texto de la nueva clase al textBox
                this->ui->plainTextEdit->insertPlainText("para_todos clase " + texto.toLatin1() + " $$ \n " +
                                                         "def para_todos "+ texto.toLatin1() +  " ninguno() $$ \n $$ \n $$" );


            }else
            {
                QMessageBox msgBox;
                msgBox.setText("No ingreso nada, la clase principal se llamará Principal\".");
                msgBox.exec();
                //crear archivo principal


                //creando el archivo principal.obj por default
                QFile file( nombreProyecto.toLatin1() + "/Principal.obj" );
                if ( file.open(QIODevice::ReadWrite) )
                {
                    QTextStream stream( &file );
                    stream << "para_todos clase Principal $$ \n def para_todos Principal ninguno ()$$ \n $$ \n $$" << endl;
                    file.close();
                    listaClases.append("para_todos clase Principal $$ \n def para_todos Principal ninguno ()$$ \n $$ \n $$");
                    this->posicionClases++;
                    this->nombreClaseActual = "Principal";

                }

//                //agregando el archivo al listView
//                QStandardItem* items = new QStandardItem("Principal");
//                QStandardItemModel* modeloLista = new QStandardItemModel();
//                modeloLista->appendRow(items);
//                items->setEditable(false);
//                this->ui->listView->setModel(modeloLista);

                //agregando a listWidget
                this->ui->listWidget->addItem("Principal");

                this->ui->listWidget->setCurrentRow(this->listaClases.size()-1);

                //creando el archivo de la lista de clases
                QFile archivoClases( nombreProyecto.toLatin1() + "/clases.cl" );
                if ( archivoClases.open(QIODevice::ReadWrite) )
                {
                    QTextStream stream( &archivoClases );
                    stream << "Principal.obj" << endl;
                    archivoClases.close();
                }
                //agregando a la lista de clases
                listaNombreClases.append("Principal.obj");

                //desplegando el texto de la clase en el plainText
                this->ui->plainTextEdit->insertPlainText("para_todos clase Principal $$ \n def para_todos Principal ninguno ()$$ \n $$ \n $$");


            }

        }

    } else {
        // no se ingreso nada o se presionó cancelar

    }
}



void Principal::on_actionNuevo_archivo_triggered()
{
    if (this->nombreProyecto.isNull())
    {
        QMessageBox msg;
        msg.setText("No tiene ningún proyecto abierto, cree un nuevo proyecto para abrir un archivo.");
        msg.exec();
        return;
    }


pedirNombre:
    bool ok;
    QString texto = QInputDialog::getText(this, "Proyecto 2","Ingrese el nombre de la nueva clase: ", QLineEdit::Normal,"", &ok);
    if ( ok && !texto.isEmpty() ) {

    //verificando que la clase no exista
        QFile archivo(this->nombreProyecto.toLatin1() + "/" +texto.toLatin1() + ".obj");

        if(archivo.exists())
        {
            //si la clase ya existe no se crea y regresa a pedir el nombre de la clase
            //desplegando messagebox
            QMessageBox msgBox;
            msgBox.setText("La clase ya existe!! Ingrese otro nombre.");
            msgBox.exec();
            //ir a etiqueta
            goto pedirNombre;
        }
        else
        {
          //si la clase no existe se crea el archivo
            if ( archivo.open(QIODevice::ReadWrite) )
            {
                QTextStream stream( &archivo );
                stream << "para_todos clase " + texto.toLatin1() + " $$ \n " +
                          "def para_todos "+ texto.toLatin1() +  " ninguno() $$ \n $$ \n $$" << endl;
                //agregandolo a la lista de String de clases
                listaClases.append("para_todos clase " + texto.toLatin1() + " $$ \n " +
                                   "def para_todos "+ texto.toLatin1() +  " ninguno() $$ \n $$ \n $$");

                this->nombreClaseActual = texto;
                archivo.close();
            }

            //agregando el nombre del archivo al listWidget
            this->ui->listWidget->addItem(texto);

            //seleccionando la fila de un archivo

            this->ui->listWidget->setCurrentRow(this->listaClases.size()-1);

            //agregando a la lista de clases
            listaNombreClases.append(texto + ".obj");

            //agregando al archivo de lista de clases
            QFile archivoClases( nombreProyecto.toLatin1() + "/clases.cl" );
            if ( archivoClases.open(QIODevice::Append) )
            {
                QTextStream stream( &archivoClases );
                stream << texto.toLatin1() + ".obj" << endl;
                archivoClases.close();
            }

            //guardando lo que estaba antes en variable
            listaClases.replace(posicionClases,this->ui->plainTextEdit->toPlainText());

            this->posicionClases = this->listaClases.size()-1;


            //blanqueando el plainText
            this->ui->plainTextEdit->setPlainText("");

            //desplegando en plainTextbox
            this->ui->plainTextEdit->insertPlainText("para_todos clase " + texto.toLatin1() + " $$ \n " +
                                                     "def para_todos "+ texto.toLatin1() +  " ninguno() $$ \n $$ \n $$");



        }


    }



}

void Principal::on_listWidget_doubleClicked(const QModelIndex &index)
{


    //guardar en variable actual
    this->listaClases.replace(posicionClases,this->ui->plainTextEdit->toPlainText().toLatin1());

    //despelegar cuando se seleccione la clase
    this->ui->plainTextEdit->setPlainText(this->listaClases.at(this->ui->listWidget->currentRow()));

    //seteando la posicion de la clase
    this->posicionClases = this->ui->listWidget->currentRow();

}

void Principal::on_actionGuardar_triggered()
{

    //guardando en valor actual por si fue cambiado en listaClases
    this->listaClases.replace(posicionClases,this->ui->plainTextEdit->toPlainText().toLatin1());

    //ciclo que reccorre la lista de nombre de clases y guarda el texto en los archivos
    for (int contador = 0;contador<listaNombreClases.size();contador++)
    {
        //nombre archivo
        QFile archivo(this->nombreProyecto.toLatin1() + "/" + listaNombreClases.at(contador).toLatin1());
        if ( archivo.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &archivo );
            stream << listaClases.at(contador).toLatin1();
            archivo.close();

        }
    }
}

void Principal::on_actionAbrir_proyecto_triggered()
{
    //abrir el .cl, leer cada uno de los archivos y subirlos a memoria
    //desplegar en el listwidget

    //obteniendo el path del proyecto
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    this->nombreProyecto = dir;

    QMessageBox msgbox;

    //leyendo archivo de clases
    QFile archivo(nombreProyecto.toLatin1() + "/clases.cl");
        if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&archivo);
        //leyendo linea por linea
        while (!in.atEnd()) {
            QString line = in.readLine();
            //insertando en listWidget
            if (line.toLatin1() == "")
            {
                goto salir;
            }
            this->ui->listWidget->addItem(line);
            QString textoClase="";
            //archivo de clase
            QFile clase(nombreProyecto.toLatin1() + "/" + line.toLatin1());
            if (!clase.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream in2(&clase);
            //leyendo el archivo de la clase
            textoClase = in2.readAll();
            //agregando a la lista de contenido de clases
            this->listaClases.append(textoClase);
            this->listaNombreClases.append(line);

        }
        salir:
        //seleccionando la clase principal en listWidget
        this->ui->listWidget->setCurrentRow(0);

        //desplegando en plainText el texto de la clase principal
        this->ui->plainTextEdit->setPlainText(this->listaClases.at(0));



        //seteando la posicion de las clases
        this->posicionClases = 0;



}

void Principal::on_actionAbrir_archivo_triggered()
{
    /*verificar si hay un proyecto abierto, si está abierto entonces se hace lo que esta en el otro comentario
    sino no lo abre porque tiene que tener un proyecto abierto*/

    /*1. Abrir el archivo
      2. agregar el nombre del nuevo archivo al archivo de lista nombre clases y a la variable
      3. abrir el archivo, leerlo y crear un nuevo archivo en el folder del proyecto
      4. ponerlo en la lista de contenido de clases que es listaClases
      5. desplegarlo en el plainText*/

    QString nuevoArchivo = QFileDialog::getOpenFileName(this, tr("Open Directory"),
                                                     "/home");
    QMessageBox msg1;


    //verificando que haya un proyecto abierto
    if(this->nombreProyecto.isNull())
    {
        //pedir que se tenga un proyecto abierto
        QMessageBox msg;
        msg.setText("No tiene ningún proyecto abierto, cree un nuevo proyecto para abrir un archivo.");
        msg.exec();

    }
    else
    {
        //abrir archivo
        QFile archivo(nuevoArchivo);
        if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in2(&archivo);
        //leyendo el archivo
        QString textoClase = in2.readAll();

        //obteniendo el nombre de la clase
        QString nombreClase = nuevoArchivo.split("/").at(nuevoArchivo.split("/").size()-1);

        msg1.setText(nombreClase);
        msg1.exec();

        this->listaNombreClases.append(nombreClase);


        //agregando al archivo lista nombre clases
        QFile archivoClases( nombreProyecto.toLatin1() + "/clases.cl" );
        if ( archivoClases.open(QIODevice::Append) )
        {
            QTextStream stream( &archivoClases );
            stream << nombreClase.toLatin1()  << endl;
            archivoClases.close();
        }


        //agregando a la lista de contenido de clases
        this->listaClases.append(textoClase);

        //crear nuevo archivo en el folder del proyecto
        QFile nuevaClase(nombreProyecto.toLatin1() + "/" + nombreClase);
        if ( nuevaClase.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &nuevaClase );
            stream << textoClase << endl;
            nuevaClase.close();
        }



        //agregando el nombre del archivo al listWidget
        this->ui->listWidget->addItem(nombreClase);

        //seleccionando la fila de un archivo
        this->ui->listWidget->setCurrentRow(this->listaClases.size()-1);


        //guardando lo que estaba antes en variable
        listaClases.replace(posicionClases,this->ui->plainTextEdit->toPlainText());

        this->posicionClases = this->listaClases.size()-1;


        //blanqueando el plainText
        this->ui->plainTextEdit->setPlainText("");

        //desplegando en plainTextbox
        this->ui->plainTextEdit->insertPlainText(textoClase);



    }


}
