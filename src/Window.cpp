#include <QApplication>
#include <QString>

#include "..\include\Window.h"
#include "..\include\serializing.h"
#include "..\include\sorting.h"

Window::Window(QWidget *parent) {
    setFixedSize(650, 650);

    allowDoubles = new QCheckBox("Разрешить действительные числа", this);
    allowDoubles->setGeometry(10, 10, 500, 30);

    inputFilenameHint = new QLabel("Введите имя файла ввода:", this);
    inputFilenameHint->setGeometry(10, 50, 500, 30);
    inputFilenameField = new QTextEdit(this);
    inputFilenameField->setGeometry(10, 90, 500, 30);
    outputFilenameHint = new QLabel("Введите имя файла вывода:", this);
    outputFilenameHint->setGeometry(10, 130, 500, 30);
    outputFilenameField = new QTextEdit(this);
    outputFilenameField->setGeometry(10, 170, 500, 30);

    streamFilenameButton = new QPushButton("Сортировка", this);
    streamFilenameButton->setGeometry(530, 90, 100, 30);

    inputHint = new QLabel("ИЛИ введите последовательность вручную:", this);
    inputHint->setGeometry(10, 210, 500, 30);
    inputField = new QTextEdit(this);
    inputField->setGeometry(10, 250, 300, 300);
    outputField = new QTextEdit(this);
    outputField->setGeometry(330, 250, 300, 300);
    outputField->setReadOnly(true);

    streamButton = new QPushButton("Сортировка", this);
    streamButton->setGeometry(10, 560, 100, 30);

    resultMessage = new QLabel("", this);
    resultMessage->setGeometry(10, 600, 500, 30);

    setWindowTitle("Лабораторная 4");

    connect(streamFilenameButton, SIGNAL (clicked()), this, SLOT (fileButtonClicked()));
    connect(streamButton, SIGNAL (clicked()), this, SLOT (sequenceButtonClicked()));
}

void Window::fileButtonClicked() {
    std::string inputFilename = inputFilenameField->toPlainText().toStdString();
    std::string outputFilename = outputFilenameField->toPlainText().toStdString();
    try {
        if (allowDoubles->isChecked()) {
            sortFileStream<double>(inputFilename, outputFilename, str2doubleDeserializer, \
                                   double2strSerializer);
        } else {
            sortFileStream<int>(inputFilename, outputFilename, str2intDeserializer, int2strSerializer);
        }
        resultMessage->setText("Сортировка выполнена успешно");
    } catch (ErrorCode error) {
        if (error == STREAM_NOT_OPEN) {
            resultMessage->setText("Не удалось открыть файлы");
        } else if (error == READING_ERROR) {
            resultMessage->setText("Ошибка чтения файла");
        } else if (error == WRITING_ERROR) {
            resultMessage->setText("Ошибка записи в файл");
        } else {
            resultMessage->setText("Ошибка");
        }
    }
}

void Window::sequenceButtonClicked() {
    std::string output;
    if (allowDoubles->isChecked()) {
        SequenceReadOnlyStream<double>* inputStream = ReadInputField<double>();
        output = sortSeqStream<double>(inputStream);
        delete inputStream;
    } else {
        SequenceReadOnlyStream<int>* inputStream = ReadInputField<int>();
        output = sortSeqStream<int>(inputStream);
        delete inputStream;
    }
    outputField->setText(QString::fromStdString(output));
    resultMessage->setText("Сортировка выполнена успешно");
}
