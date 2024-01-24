function addTask() {
    var taskInput = document.getElementById("taskInput");
    var taskList = document.getElementById("taskList");

    if (taskInput.value.trim() !== "") {
        var taskItem = document.createElement("li");
        taskItem.textContent = taskInput.value;
        taskItem.onclick = function () {
            this.remove();
        };

        taskList.appendChild(taskItem);
        taskInput.value = "";
    }
}
