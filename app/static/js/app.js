const todosForm = document.getElementById('todo-form')
const todosList = document.getElementById('todo-list')
const taskInputElt = document.getElementById('task-input')

const getSavedTasks = () => {
    const todos = localStorage.getItem('todos-items') || '[]'
    return JSON.parse(todos)
}

const saveTask = (task) => {
    const todosItems = getSavedTasks()
    todosItems.push(task)
    localStorage.setItem('todos-items', JSON.stringify(todosItems))
}

const addTodo = (task) => {
    const taskElt = document.createElement('li')
    taskElt.textContent = task

    todosList.appendChild(taskElt)
}

const submitHandler = (e) => {
    e.preventDefault()
    
    const task = taskInputElt.value
    taskInputElt.value = ''

    addTodo(task)
    saveTask(task)
}

todosForm.addEventListener('submit', submitHandler)
window.addEventListener('load', () => {
    const todosItems = getSavedTasks()
    todosItems.forEach(task => addTodo(task))
})
