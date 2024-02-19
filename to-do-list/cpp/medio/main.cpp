#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class ToDoList : public QWidget {
    Q_OBJECT
public:
    explicit ToDoList(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("To-Do List");

        // Layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        QHBoxLayout *buttonLayout = new QHBoxLayout;

        // Widgets
        taskInput = new QLineEdit;
        addButton = new QPushButton("Adicionar");
        removeButton = new QPushButton("Remover");
        completeButton = new QPushButton("Concluir");
        saveButton = new QPushButton("Salvar");
        taskList = new QListWidget;

        // Connect buttons
        connect(addButton, SIGNAL(clicked()), this, SLOT(addTask()));
        connect(removeButton, SIGNAL(clicked()), this, SLOT(removeTask()));
        connect(completeButton, SIGNAL(clicked()), this, SLOT(markCompleted()));
        connect(saveButton, SIGNAL(clicked()), this, SLOT(saveTasks()));

        // Add widgets to layout
        layout->addWidget(taskInput);
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(removeButton);
        buttonLayout->addWidget(completeButton);
        buttonLayout->addWidget(saveButton);
        layout->addLayout(buttonLayout);
        layout->addWidget(taskList);

        // Load tasks from file
        loadTasks();
    }

public slots:
    void addTask() {
        QString task = taskInput->text();
        if (!task.isEmpty()) {
            taskList->addItem(task);
            taskInput->clear();
        }
    }

    void removeTask() {
        qDeleteAll(taskList->selectedItems());
    }

    void markCompleted() {
        QListWidgetItem *item = taskList->currentItem();
        if (item) {
            QFont font = item->font();
            font.setStrikeOut(true);
            item->setFont(font);
        }
    }

    void saveTasks() {
        ofstream outFile("tasks.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < taskList->count(); ++i) {
                outFile << taskList->item(i)->text().toStdString() << endl;
            }
            outFile.close();
            QMessageBox::information(this, "Salvar", "Tarefas salvas com sucesso!");
        } else {
            QMessageBox::critical(this, "Erro", "Não foi possível salvar as tarefas.");
        }
    }

private:
    QLineEdit *taskInput;
    QListWidget *taskList;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *completeButton;
    QPushButton *saveButton;

    void loadTasks() {
        ifstream inFile("tasks.txt");
        if (inFile.is_open()) {
            string task;
            while (getline(inFile, task)) {
                taskList->addItem(QString::fromStdString(task));
            }
            inFile.close();
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ToDoList window;
    window.resize(400, 300);
    window.show();

    return app.exec();
}

#include "main.moc"
