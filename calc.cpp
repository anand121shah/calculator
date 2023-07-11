#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QLineEdit>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Calculator");

    // Create the calculator's display
    QLineEdit *display = new QLineEdit(&window);
    display->setReadOnly(true);

    // Create the grid layout for the buttons
    QGridLayout *gridLayout = new QGridLayout;
    window.setLayout(gridLayout);

    // Create the buttons and connect them to slots
    QStringList buttons = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    QSignalMapper *signalMapper = new QSignalMapper(&window);

    int row = 0;
    int col = 0;

    foreach (QString text, buttons) {
        QPushButton *button = new QPushButton(text, &window);
        gridLayout->addWidget(button, row, col);

        signalMapper->setMapping(button, text);
        QObject::connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));

        col++;
        if (col == 4) {
            col = 0;
            row++;
        }
    }

    // Connect the signal mapper to the display
    QObject::connect(signalMapper, SIGNAL(mapped(const QString &)), display, SLOT(insert(const QString &)));

    // Add the display to the grid layout
    gridLayout->addWidget(display, row, 0, 1, 4);

    window.show();

    return app.exec();
}
