<template>
  <div class="tasks-container">
    <h2 class="page-title">
      📋 Tasks Management
      <span v-if="user"> — Welcome, {{ user.username }}!</span>
    </h2>

    <div class="task-input-container">
      <input
        v-model="newTaskTitle"
        placeholder="Enter task title"
        class="task-input-field"
        @keyup.enter="addTask"
      />
      <input
        v-model="newTaskDescription"
        placeholder="Enter description"
        class="task-input-field"
        @keyup.enter="addTask"
      />
      <select v-model="newTaskStatus" class="status-select">
        <option value="todo">📝 Todo</option>
        <option value="in_progress">⚡ In Progress</option>
        <option value="done">✅ Done</option>
      </select>
      <button class="btn btn-primary" @click="addTask" :disabled="!newTaskTitle.trim()">
        <span class="btn-icon">➕</span> Add Task
      </button>
    </div>

    <div class="tasks-stats">
      <span class="stat-badge todo">Todo: {{ todoCount }}</span>
      <span class="stat-badge progress">In Progress: {{ inProgressCount }}</span>
      <span class="stat-badge done">Done: {{ doneCount }}</span>
      <span class="stat-badge total">Total: {{ tasks.length }}</span>
    </div>

    <div v-if="tasks.length === 0" class="empty-state">
      <div class="empty-icon">📭</div>
      <h3>No tasks yet</h3>
      <p>Add your first task using the form above</p>
    </div>

    <ul class="task-list" v-else>
      <li
        v-for="task in tasks"
        :key="task.id"
        class="task-card"
        :class="statusClass(task.status)"
      >
        <div class="task-content">
          <div class="task-header">
            <div class="task-status-indicator" :class="task.status"></div>
            <strong class="task-title">{{ task.title }}</strong>
            <span class="task-id">#{{ task.id }}</span>
          </div>

          <p class="task-description">{{ task.description || "No description" }}</p>

          <div class="task-footer">
            <div class="task-status-control">
              <label class="status-label">Status:</label>
              <select
                v-model="task.status"
                @change="changeStatus(task)"
                class="status-select small"
              >
                <option value="todo">📝 Todo</option>
                <option value="in_progress">⚡ In Progress</option>
                <option value="done">✅ Done</option>
              </select>
            </div>

            <div class="task-actions">
              <button
                class="btn-icon btn-edit"
                @click="editTask(task)"
                title="Edit task"
              >
                ✏️
              </button>
              <button
                class="btn-icon btn-delete"
                @click="deleteTask(task)"
                title="Delete task"
              >
                🗑️
              </button>
            </div>
          </div>
        </div>
      </li>
    </ul>

    <div v-if="error" class="error-notification">
      ⚠️ {{ error }}
      <button class="close-error" @click="error = null">×</button>
    </div>

    <div v-if="successMessage" class="success-notification">
      ✅ {{ successMessage }}
    </div>
  </div>
</template>

<script>
import api from "../api";

export default {
  data() {
    return {
      tasks: [],
      newTaskTitle: "",
      newTaskDescription: "",
      newTaskStatus: "todo",
      error: null,
      successMessage: null,
      user: null
    };
  },
  async mounted() {
    await this.fetchUser();
    await this.fetchTasks();
  },
  computed: {
    todoCount() {
      return this.tasks.filter(t => t.status === 'todo').length;
    },
    inProgressCount() {
      return this.tasks.filter(t => t.status === 'in_progress').length;
    },
    doneCount() {
      return this.tasks.filter(t => t.status === 'done').length;
    }
  },
  methods: {
    async fetchUser() {
      try {
        const r = await api.get("/me");
        this.user = r.data;
      } catch (e) {
        this.showError("Failed to load user info");
      }
    },
    async fetchTasks() {
      try {
        const r = await api.get("/tasks");
        this.tasks = r.data;
        this.showSuccess("Tasks loaded successfully");
      } catch (e) {
        this.showError("Failed to load tasks");
      }
    },
    async addTask() {
      if (!this.newTaskTitle.trim()) return;

      try {
        const r = await api.post("/tasks", {
          title: this.newTaskTitle,
          description: this.newTaskDescription,
          status: this.newTaskStatus
        });

        this.tasks.push(r.data);
        this.newTaskTitle = "";
        this.newTaskDescription = "";
        this.newTaskStatus = "todo";

        this.showSuccess("Task added successfully");
      } catch (e) {
        this.showError("Failed to add task");
      }
    },
    async deleteTask(task) {
      if (!confirm(`Are you sure you want to delete "${task.title}"?`)) return;

      try {
        await api.delete(`/tasks/${task.id}`);
        this.tasks = this.tasks.filter(t => t.id !== task.id);
        this.showSuccess("Task deleted successfully");
      } catch (e) {
        this.showError("Failed to delete task");
      }
    },
    async changeStatus(task) {
      try {
        await api.patch(`/tasks/${task.id}`, { status: task.status });
        this.showSuccess(`Task status updated to "${task.status}"`);
      } catch (e) {
        this.showError("Failed to update status");
      }
    },
    async editTask(task) {
      const newTitle = prompt("Enter new title", task.title);
      if (newTitle === null) return;

      const newDescription = prompt("Enter new description", task.description);

      try {
        const r = await api.put(`/tasks/${task.id}`, {
          title: newTitle,
          description: newDescription,
          status: task.status
        });

        const idx = this.tasks.findIndex(t => t.id === task.id);
        this.tasks[idx] = r.data;
        this.showSuccess("Task updated successfully");
      } catch (e) {
        this.showError("Failed to update task");
      }
    },
    statusClass(status) {
      return `status-${status}`;
    },
    showError(message) {
      this.error = message;
      this.successMessage = null;
      setTimeout(() => this.error = null, 5000);
    },
    showSuccess(message) {
      this.successMessage = message;
      this.error = null;
      setTimeout(() => this.successMessage = null, 3000);
    },
    logout() {
      localStorage.removeItem("token");
      window.location.reload();
    }
  }
};
</script>

<style scoped>
.tasks-container {
  max-width: 800px;
  margin: 0 auto;
  padding: 2rem;
  min-height: 100vh;
  background: #0f172a;
  color: #e2e8f0;
}

.page-title {
  text-align: center;
  margin-bottom: 2rem;
  color: #60a5fa;
  font-size: 2rem;
  border-bottom: 2px solid #1e293b;
  padding-bottom: 0.5rem;
}

.task-input-container {
  background: #1e293b;
  padding: 1.5rem;
  border-radius: 12px;
  margin-bottom: 2rem;
  display: flex;
  flex-wrap: wrap;
  gap: 1rem;
  align-items: center;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.3);
}

.task-input-field {
  flex: 1;
  min-width: 200px;
  padding: 0.75rem 1rem;
  background: #334155;
  border: 2px solid #475569;
  border-radius: 8px;
  color: #f1f5f9;
  font-size: 1rem;
  transition: all 0.3s;
}

.task-input-field:focus {
  outline: none;
  border-color: #60a5fa;
  box-shadow: 0 0 0 3px rgba(96, 165, 250, 0.2);
}

.task-input-field::placeholder {
  color: #94a3b8;
}

.status-select {
  padding: 0.75rem 1rem;
  background: #334155;
  border: 2px solid #475569;
  border-radius: 8px;
  color: #f1f5f9;
  font-size: 1rem;
  cursor: pointer;
}

.status-select.small {
  padding: 0.4rem 0.75rem;
  font-size: 0.9rem;
}

.btn {
  padding: 0.75rem 1.5rem;
  border: none;
  border-radius: 8px;
  font-size: 1rem;
  font-weight: 600;
  cursor: pointer;
  transition: all 0.3s;
  display: inline-flex;
  align-items: center;
  justify-content: center;
  gap: 0.5rem;
}

.btn:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}

.btn-primary {
  background: linear-gradient(135deg, #3b82f6, #1d4ed8);
  color: white;
}

.btn-primary:hover:not(:disabled) {
  background: linear-gradient(135deg, #2563eb, #1e40af);
  transform: translateY(-2px);
  box-shadow: 0 6px 12px rgba(37, 99, 235, 0.3);
}

.btn-icon {
  background: none;
  border: none;
  font-size: 1.2rem;
  cursor: pointer;
  padding: 0.5rem;
  border-radius: 6px;
  transition: all 0.2s;
}

.btn-edit {
  color: #60a5fa;
}

.btn-edit:hover {
  background: rgba(96, 165, 250, 0.2);
  transform: scale(1.1);
}

.btn-delete {
  color: #f87171;
}

.btn-delete:hover {
  background: rgba(248, 113, 113, 0.2);
  transform: scale(1.1);
}

.tasks-stats {
  display: flex;
  flex-wrap: wrap;
  gap: 1rem;
  margin-bottom: 2rem;
  justify-content: center;
}

.stat-badge {
  padding: 0.5rem 1rem;
  border-radius: 20px;
  font-weight: 600;
  font-size: 0.9rem;
}

.stat-badge.todo {
  background: rgba(59, 130, 246, 0.2);
  color: #60a5fa;
  border: 1px solid #3b82f6;
}

.stat-badge.progress {
  background: rgba(245, 158, 11, 0.2);
  color: #fbbf24;
  border: 1px solid #f59e0b;
}

.stat-badge.done {
  background: rgba(34, 197, 94, 0.2);
  color: #4ade80;
  border: 1px solid #22c55e;
}

.stat-badge.total {
  background: rgba(148, 163, 184, 0.2);
  color: #cbd5e1;
  border: 1px solid #94a3b8;
}

.task-list {
  list-style: none;
  padding: 0;
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.task-card {
  background: #1e293b;
  border-radius: 12px;
  padding: 1.5rem;
  transition: all 0.3s;
  border-left: 4px solid;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
}

.task-card:hover {
  transform: translateY(-2px);
  box-shadow: 0 6px 12px rgba(0, 0, 0, 0.3);
  background: #273449;
}

.status-todo {
  border-left-color: #3b82f6;
}

.status-in_progress {
  border-left-color: #f59e0b;
}

.status-done {
  border-left-color: #22c55e;
}

.task-content {
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.task-header {
  display: flex;
  align-items: center;
  gap: 1rem;
  flex-wrap: wrap;
}

.task-status-indicator {
  width: 12px;
  height: 12px;
  border-radius: 50%;
}

.task-status-indicator.todo {
  background: #3b82f6;
  box-shadow: 0 0 8px #3b82f6;
}

.task-status-indicator.in_progress {
  background: #f59e0b;
  box-shadow: 0 0 8px #f59e0b;
}

.task-status-indicator.done {
  background: #22c55e;
  box-shadow: 0 0 8px #22c55e;
}

.task-title {
  font-size: 1.3rem;
  color: #f1f5f9;
  flex: 1;
}

.task-id {
  color: #94a3b8;
  font-size: 0.9rem;
  background: #334155;
  padding: 0.2rem 0.5rem;
  border-radius: 4px;
}

.task-description {
  color: #cbd5e1;
  line-height: 1.5;
  margin: 0;
  padding: 0.75rem;
  background: #334155;
  border-radius: 8px;
  border-left: 3px solid #475569;
}

.task-footer {
  display: flex;
  justify-content: space-between;
  align-items: center;
  flex-wrap: wrap;
  gap: 1rem;
}

.task-status-control {
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.status-label {
  color: #94a3b8;
  font-weight: 500;
}

.task-actions {
  display: flex;
  gap: 0.5rem;
}

.empty-state {
  text-align: center;
  padding: 4rem 2rem;
  background: #1e293b;
  border-radius: 12px;
  border: 2px dashed #475569;
}

.empty-icon {
  font-size: 4rem;
  margin-bottom: 1rem;
  opacity: 0.5;
}

.empty-state h3 {
  color: #cbd5e1;
  margin-bottom: 0.5rem;
}

.empty-state p {
  color: #94a3b8;
}

.error-notification {
  position: fixed;
  bottom: 2rem;
  right: 2rem;
  background: #7f1d1d;
  color: #fecaca;
  padding: 1rem 1.5rem;
  border-radius: 8px;
  display: flex;
  align-items: center;
  gap: 1rem;
  animation: slideIn 0.3s ease;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.5);
  z-index: 1000;
}

.success-notification {
  position: fixed;
  bottom: 2rem;
  right: 2rem;
  background: #14532d;
  color: #bbf7d0;
  padding: 1rem 1.5rem;
  border-radius: 8px;
  animation: slideIn 0.3s ease;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.5);
  z-index: 1000;
}

.close-error {
  background: none;
  border: none;
  color: #fecaca;
  font-size: 1.5rem;
  cursor: pointer;
  padding: 0;
  width: 24px;
  height: 24px;
  display: flex;
  align-items: center;
  justify-content: center;
}

@keyframes slideIn {
  from {
    transform: translateX(100%);
    opacity: 0;
  }
  to {
    transform: translateX(0);
    opacity: 1;
  }
}

@media (max-width: 768px) {
  .tasks-container {
    padding: 1rem;
  }

  .task-input-container {
    flex-direction: column;
    align-items: stretch;
  }

  .task-input-field {
    min-width: auto;
  }

  .task-footer {
    flex-direction: column;
    align-items: stretch;
  }

  .task-actions {
    justify-content: flex-end;
  }

  .error-notification,
  .success-notification {
    left: 1rem;
    right: 1rem;
    bottom: 1rem;
  }
}

.task-list::-webkit-scrollbar {
  width: 8px;
}

.task-list::-webkit-scrollbar-track {
  background: #1e293b;
  border-radius: 4px;
}

.task-list::-webkit-scrollbar-thumb {
  background: #475569;
  border-radius: 4px;
}

.task-list::-webkit-scrollbar-thumb:hover {
  background: #64748b;
}
</style>