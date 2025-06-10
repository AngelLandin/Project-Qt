#include "MainWindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      label_(new QLabel("Tarea inicial", this)),
      button_(new QPushButton("Agregar tarea", this)),
      lineEdit_(new QLineEdit(this)),
      textEdit_(new QTextEdit(this))
{
    // 1) Configurar la ventana principal
    setWindowTitle("Ejemplo Qt – Controles Básicos");

    // Estilo personalizado tipo moderno
    setStyleSheet(R"(
        QWidget {
            background-color: #1E1E2F;
            color: #FFFFFF;
            font-family: Segoe UI, sans-serif;
            font-size: 14px;
        }

        QLabel {
            font-weight: bold;
        }

        QLineEdit {
            background-color: #2A2A40;
            border: 1px solid #3E3E5E;
            border-radius: 5px;
            padding: 5px;
            color: #FFFFFF;
        }

        QTextEdit {
            background-color: #2A2A40;
            border: 1px solid #3E3E5E;
            border-radius: 5px;
            padding: 5px;
            color: #FFFFFF;
        }

        QPushButton {
            background-color: #3F8CFF;
            border: none;
            padding: 6px 12px;
            border-radius: 6px;
            color: white;
        }

        QPushButton:hover {
            background-color: #5EA0FF;
        }

        QMenuBar {
            background-color: #1E1E2F;
            color: white;
        }

        QMenuBar::item:selected {
            background: #3F8CFF;
        }

        QToolBar {
            background-color: #1E1E2F;
            border-bottom: 1px solid #3E3E5E;
        }

        QStatusBar {
            background-color: #1E1E2F;
            color: white;
        }
    )");


    resize(600, 400);

    // 2) Barra de menú con acción "Salir"
    QMenu *fileMenu = menuBar()->addMenu("&Archivo");
    QAction *exitAction = fileMenu->addAction("Salir");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    // 3) Barra de estado
    statusBar()->showMessage("Listo");

    // 4) Barra de herramientas que reutiliza la acción "Salir"
    QToolBar *toolbar = addToolBar("Principal");
    toolbar->addAction(exitAction);

    // 5) Conectar el botón al slot
    connect(button_, &QPushButton::clicked, this, &MainWindow::on_buttonClicked);

    // 6) Crear un widget central con layout
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

   // Layout vertical principal
    QVBoxLayout *vbox = new QVBoxLayout;

    QLabel *motivationalLabel = new QLabel(
    R"("Cuando algo es lo suficientemente importante, haces lo que sea necesario, incluso cuando las probabilidades no están a tu favor.")  
    — Elon Musk)", this);
    motivationalLabel->setWordWrap(true); // Que se adapte al ancho
    motivationalLabel->setAlignment(Qt::AlignCenter);
    motivationalLabel->setStyleSheet("font-size: 16px; font-style: italic; color: #9FD0FF; margin-bottom: 10px;");

    vbox->addWidget(motivationalLabel);  // Primero la frase
    vbox->addWidget(label_);             // Luego el label "Tarea inicial"


    // Layout horizontal para QLabel + QLineEdit + QPushButton
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel("Ingresar tarea:", this));  // ← Cambiado
    hbox->addWidget(lineEdit_);
    hbox->addWidget(button_);
    vbox->addLayout(hbox);

    // QLabel y QTextEdit para mostrar líneas
    vbox->addWidget(new QLabel("Listado de tareas pendientes:", this));  // ← Cambiado
    vbox->addWidget(textEdit_);

    central->setLayout(vbox);
}

MainWindow::~MainWindow()
{
    // Qt libera los hijos automáticamente
}

void MainWindow::on_buttonClicked()
{
    QString input = lineEdit_->text();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "El campo de texto está vacío.");
        return;
    }

    // Actualizar QLabel e insertar línea en QTextEdit
    label_->setText("Último ingreso: " + input);
    taskCount_++;
    textEdit_->append(QString::number(taskCount_) + ". " + input);

    lineEdit_->clear();
}
