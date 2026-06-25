#include <QApplication>

#include "..\include\Window.h"

Window::Window(QWidget *parent) {
    setFixedSize(650, 600);

    inputFilenameHint = new QLabel("Введите имя файла ввода:", this);
    inputFilenameHint->setGeometry(10, 10, 500, 30);
    inputFilenameField = new QTextEdit(this);
    inputFilenameField->setGeometry(10, 50, 500, 30);
    outputFilenameHint = new QLabel("Введите имя файла вывода:", this);
    outputFilenameHint->setGeometry(10, 90, 500, 30);
    outputFilenameField = new QTextEdit(this);
    outputFilenameField->setGeometry(10, 130, 500, 30);

    streamFilenameButton = new QPushButton("Сортировка", this);
    streamFilenameButton->setGeometry(530, 50, 100, 30);

    inputHint = new QLabel("ИЛИ введите последовательность вручную:", this);
    inputHint->setGeometry(10, 170, 500, 30);
    inputField = new QTextEdit(this);
    inputField->setGeometry(10, 210, 300, 300);
    outputField = new QTextEdit(this);
    outputField->setGeometry(330, 210, 300, 300);
    outputField->setReadOnly(true);

    streamButton = new QPushButton("Сортировка", this);
    streamButton->setGeometry(10, 530, 100, 30);

    resultMessage = new QLabel("", this);
    resultMessage->setGeometry(10, 570, 500, 30);

    setWindowTitle("Лабораторная 4");
}
