#include <QApplication>
#include <QWidget>
#include <QString>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QStringList>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Task {
    QString title;
    QString description;
    QString dueDate;
    QString priority;
    QString category;
    bool completed;
    QString completionNote;
};

class ToDoList : public QWidget {
    Q_OBJECT

public:
    ToDoList(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("To-Do List");

        taskTitleEdit = new QLineEdit;
        taskDescriptionEdit = new QTextEdit;
        taskDueDateEdit = new QLineEdit;
        taskPriorityEdit = new QLineEdit;
        taskCategoryEdit = new QLineEdit;

        addButton = new QPushButton("Add Task");
        removeButton = new QPushButton("Remove Task");
        completeButton = new QPushButton("Complete Task");

        taskListWidget = new QListWidget;

        QVBoxLayout *layout = new QVBoxLayout;
        QHBoxLayout *inputLayout = new QHBoxLayout;
        QVBoxLayout *buttonLayout = new QVBoxLayout;

        QLabel *titleLabel = new QLabel("Title:");
        QLabel *descriptionLabel = new QLabel("Description:");
        QLabel *dueDateLabel = new QLabel("Due Date:");
        QLabel *priorityLabel = new QLabel("Priority:");
        QLabel *categoryLabel = new QLabel("Category:");

        inputLayout->addWidget(titleLabel);
        inputLayout->addWidget(taskTitleEdit);
        inputLayout->addWidget(descriptionLabel);
        inputLayout->addWidget(taskDescriptionEdit);
        inputLayout->addWidget(dueDateLabel);
        inputLayout->addWidget(taskDueDateEdit);
        inputLayout->addWidget(priorityLabel);
        inputLayout->addWidget(taskPriorityEdit);
        inputLayout->addWidget(categoryLabel);
        inputLayout->addWidget(taskCategoryEdit);

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(removeButton);
        buttonLayout->addWidget(completeButton);

        layout->addLayout(inputLayout);
        layout->addLayout(buttonLayout);
        layout->addWidget(taskListWidget);

        setLayout(layout);

        connect(addButton, SIGNAL(clicked()), this, SLOT(addTask()));
        connect(removeButton, SIGNAL(clicked()), this, SLOT(removeTask()));
        connect(completeButton, SIGNAL(clicked()), this, SLOT(completeTask()));

        loadTasks();
        displayTasks();
    }

public slots:
    void addTask() {
        Task newTask;
        newTask.title = taskTitleEdit->text();
        newTask.description = taskDescriptionEdit->toPlainText();
        newTask.dueDate = taskDueDateEdit->text();
        newTask.priority = taskPriorityEdit->text();
        newTask.category = taskCategoryEdit->text();
        newTask.completed = false;
        tasks.push_back(newTask);

        saveTasks();
        displayTasks();
    }

    void removeTask() {
        int index = taskListWidget->currentRow();
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            saveTasks();
            displayTasks();
        }
    }

    void completeTask() {
        int index = taskListWidget->currentRow();
        if (index >= 0 && index < tasks.size()) {
            QString completionNote = QInputDialog::getText(this, "Completion Note", "Enter completion note:");
            tasks[index].completed = true;
            tasks[index].completionNote = completionNote;
            saveTasks();
            displayTasks();
        }
    }

private:
    void loadTasks() {
        ifstream file("tasks.txt");
        if (!file.is_open()) {
            cerr << "Failed to open file!" << endl;
            return;
        }

        while (!file.eof()) {
            Task task;
            std::string temp;

            // Leitura dos dados como std::string
            std::getline(file, temp);
            task.title = QString::fromStdString(temp);

            std::getline(file, temp);
            task.description = QString::fromStdString(temp);

            std::getline(file, temp);
            task.dueDate = QString::fromStdString(temp);

            std::getline(file, temp);
            task.priority = QString::fromStdString(temp);

            std::getline(file, temp);
            task.category = QString::fromStdString(temp);

            file >> task.completed;
            file.ignore();

            std::getline(file, temp);
            task.completionNote = QString::fromStdString(temp);

            tasks.push_back(task);
        }

        file.close();
    }

    void saveTasks() {
        ofstream file("tasks.txt");
        if (!file.is_open()) {
            cerr << "Failed to open file!" << endl;
            return;
        }

        for (const Task &task : tasks) {
            file << task.title.toStdString() << endl;
            file << task.description.toStdString() << endl;
            file << task.dueDate.toStdString() << endl;
            file << task.priority.toStdString() << endl;
            file << task.category.toStdString() << endl;
            file << task.completed << endl;
            file << task.completionNote.toStdString() << endl;
        }

        file.close();
    }

    void displayTasks() {
        taskListWidget->clear();

        for (const Task &task : tasks) {
            QString taskText = task.title + " - Due: " + task.dueDate + " - Priority: " + task.priority + " - Category: " + task.category;
            if (task.completed) {
                taskText += " (Completed)";
            }
            QListWidgetItem *item = new QListWidgetItem(taskText);
            taskListWidget->addItem(item);
        }
    }

    QLineEdit *taskTitleEdit;
    QTextEdit *taskDescriptionEdit;
    QLineEdit *taskDueDateEdit;
    QLineEdit *taskPriorityEdit;
    QLineEdit *taskCategoryEdit;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *completeButton;

    QListWidget *taskListWidget;

    vector<Task> tasks;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ToDoList todoList;
    todoList.show();

    return app.exec();
}

#include "main.moc"
