#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

class Window: public QWidget {
    Q_OBJECT
public:
    Window(QWidget *parent = nullptr);
private slots:
    void fileButtonClicked();
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
};

#endif // WINDOW_H
