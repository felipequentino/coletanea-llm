const form = document.getElementById('userForm');
const userList = document.getElementById('userList');

// Função para renderizar a lista de usuários
function renderUser(user) {
    const li = document.createElement('li');
    li.innerHTML = `<strong>${user.nome}</strong> - Idade: ${user.idade} <button onclick="deleteUser(${user.id})">Excluir</button>`;
    userList.appendChild(li);
}

// Função para buscar os usuários do banco de dados e renderizá-los na página
async function getUsers() {
    const response = await fetch('/users');
    const users = await response.json();
    userList.innerHTML = '';
    users.forEach(user => {
        renderUser(user);
    });
}

// Função para adicionar um novo usuário
async function addUser(event) {
    event.preventDefault();
    const nome = document.getElementById('nome').value;
    const idade = document.getElementById('idade').value;
    await fetch('/users', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ nome, idade })
    });
    form.reset();
    getUsers();
}

// Função para excluir um usuário
async function deleteUser(id) {
    await fetch(`/users/${id}`, { method: 'DELETE' });
    getUsers();
}

form.addEventListener('submit', addUser);
getUsers();
