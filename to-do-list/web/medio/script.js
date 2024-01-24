let tasks = [];

function addTask() {
    const taskInput = document.getElementById('taskInput');
    const taskText = taskInput.value.trim();

    if (taskText !== '') {
        tasks.push({ text: taskText, completed: false });
        taskInput.value = '';
        displayTasks();
    }
}

function removeTask(index) {
    tasks.splice(index, 1);
    displayTasks();
}

function toggleTask(index) {
    tasks[index].completed = !tasks[index].completed;
    displayTasks();
}

function showPendingTasks() {
    const pendingTasks = tasks.filter(task => !task.completed);
    alert("Tarefas Pendentes:\n" + pendingTasks.map(task => task.text).join("\n"));
}

function saveTasksToFile() {
    const content = JSON.stringify(tasks);
    const blob = new Blob([content], { type: 'application/json' });
    const a = document.createElement('a');
    a.href = URL.createObjectURL(blob);
    a.download = 'tasks.json';
    a.click();
}

function displayTasks() {
    const taskList = document.getElementById('taskList');
    taskList.innerHTML = '';

    tasks.forEach((task, index) => {
        const li = document.createElement('li');
        li.innerHTML = `
            <span class="${task.completed ? 'completed' : ''}">${task.text}</span>
            <button onclick="removeTask(${index})">Remover</button>
            <input type="checkbox" onchange="toggleTask(${index})" ${task.completed ? 'checked' : ''}>
        `;
        taskList.appendChild(li);
    });
}

// Carregar tarefas salvas anteriormente, se existirem
document.addEventListener('DOMContentLoaded', () => {
    if (localStorage.getItem('tasks')) {
        tasks = JSON.parse(localStorage.getItem('tasks'));
        displayTasks();
    }
});

// Salvar tarefas no armazenamento local ao fechar a página
window.addEventListener('beforeunload', () => {
    localStorage.setItem('tasks', JSON.stringify(tasks));
});
