#ifndef WINDOW_H
#define WINDOW_H

#include <sstream>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

#include "ListSequence.h"
#include "SequenceReadOnlyStream.h"

#define BUF_ALLOCATE 30

class Window: public QWidget {
    Q_OBJECT
public:
    Window(QWidget *parent = nullptr);
private slots:
    void fileButtonClicked();
    void sequenceButtonClicked();
private:
    QCheckBox* allowDoubles;

    QLabel* inputFilenameHint;
    QTextEdit* inputFilenameField;
    QLabel* outputFilenameHint;
    QTextEdit* outputFilenameField;
    QPushButton* streamFilenameButton;

    QLabel* inputHint;
    QTextEdit* inputField;
    QTextEdit* outputField;
    QPushButton* streamButton;

    QLabel* resultMessage;

    template <class T> SequenceReadOnlyStream<T>* ReadInputField() {
        std::string input = inputField->toPlainText().toStdString() + " ";
        std::istringstream stringStream;
        stringStream.str(input);
        Sequence<T>* seq = new ListSequence<T>();
        T buf;
        stringStream >> buf;
        int pos = stringStream.tellg();
        while (pos != -1) {
            seq->Append(buf);
            stringStream >> buf;
            pos = stringStream.tellg();
        }
        SequenceReadOnlyStream<T>* inputStream = new SequenceReadOnlyStream<T>(seq);
        return inputStream;
    }
};

#endif // WINDOW_H
