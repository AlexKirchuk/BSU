<template>
  <div class="login-container">
    <div class="login-card">
      <div class="login-header">
        <div class="login-icon">
          <svg width="40" height="40" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path d="M12 12C14.7614 12 17 9.76142 17 7C17 4.23858 14.7614 2 12 2C9.23858 2 7 4.23858 7 7C7 9.76142 9.23858 12 12 12Z"
                  stroke="currentColor" stroke-width="2"/>
            <path d="M20 21V19C20 16.7909 18.2091 15 16 15H8C5.79086 15 4 16.7909 4 19V21"
                  stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
          </svg>
        </div>
        <h1 class="login-title">Welcome Back</h1>
        <p class="login-subtitle">Sign in to continue to your account</p>
      </div>

      <form @submit.prevent="login" class="login-form">
        <div class="form-group">
          <label for="username" class="form-label">
            <svg class="input-icon" width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path d="M12 12C14.7614 12 17 9.76142 17 7C17 4.23858 14.7614 2 12 2C9.23858 2 7 4.23858 7 7C7 9.76142 9.23858 12 12 12Z"
                    stroke="currentColor" stroke-width="1.5"/>
              <path d="M20 21V19C20 16.7909 18.2091 15 16 15H8C5.79086 15 4 16.7909 4 19V21"
                    stroke="currentColor" stroke-width="1.5" stroke-linecap="round"/>
            </svg>
            Username
          </label>
          <div class="input-wrapper">
            <input
              v-model="username"
              id="username"
              type="text"
              placeholder="Enter your username"
              class="form-input"
              required
              autocomplete="username"
            />
          </div>
        </div>

        <div class="form-group">
          <label for="password" class="form-label">
            <svg class="input-icon" width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <rect x="3" y="11" width="18" height="11" rx="2" stroke="currentColor" stroke-width="1.5"/>
              <path d="M7 11V7C7 4.23858 9.23858 2 12 2C14.7614 2 17 4.23858 17 7V11"
                    stroke="currentColor" stroke-width="1.5" stroke-linecap="round"/>
              <circle cx="12" cy="15" r="1" fill="currentColor"/>
            </svg>
            Password
          </label>
          <div class="input-wrapper">
            <input
              v-model="password"
              id="password"
              :type="showPassword ? 'text' : 'password'"
              placeholder="Enter your password"
              class="form-input"
              required
              autocomplete="current-password"
            />
            <button
              type="button"
              class="password-toggle"
              @click="showPassword = !showPassword"
            >
              {{ showPassword ? '👁️' : '👁️‍🗨️' }}
            </button>
          </div>
        </div>

        <div class="form-options">
          <label class="checkbox-container">
            <input type="checkbox" v-model="rememberMe" />
            <span class="checkmark"></span>
            Remember me
          </label>
          <a href="#" class="forgot-password" @click.prevent="forgotPassword">
            Forgot password?
          </a>
        </div>

        <button
          type="submit"
          class="login-button"
          :disabled="isLoading"
          :class="{ 'loading': isLoading }"
        >
          <span v-if="!isLoading">
            <svg class="button-icon" width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path d="M10 16L14 12L10 8" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
            </svg>
            Sign In
          </span>
          <span v-else class="loading-spinner"></span>
        </button>

        <div class="register-link">
          <p>Don't have an account?</p>
          <button @click="goToRegister" class="register-button">
            Create Account
          </button>
        </div>
      </form>

      <transition name="fade">
        <div v-if="error" class="error-notification">
          <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <circle cx="12" cy="12" r="10" stroke="currentColor" stroke-width="2"/>
            <path d="M12 8V12" stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
            <circle cx="12" cy="16" r="1" fill="currentColor"/>
          </svg>
          <span>{{ error }}</span>
          <button @click="error = null" class="close-error">×</button>
        </div>
      </transition>
    </div>

    <div class="bg-blur-1"></div>
    <div class="bg-blur-2"></div>
  </div>
</template>

<script>
import api from "../api";

export default {
  emits: ["login-success"],
  data() {
    return {
      username: "",
      password: "",
      rememberMe: false,
      showPassword: false,
      isLoading: false,
      error: null
    };
  },
  methods: {
    async login() {
      if (!this.username.trim() || !this.password.trim()) {
        this.error = "Please fill in all fields";
        return;
      }

      this.isLoading = true;
      this.error = null;

      try {
        const formData = new URLSearchParams();
        formData.append("username", this.username);
        formData.append("password", this.password);

        const response = await api.post("/login", formData, {
          headers: { "Content-Type": "application/x-www-form-urlencoded" }
        });

        localStorage.setItem("token", response.data.access_token);

        if (this.rememberMe) {
          localStorage.setItem("rememberMe", "true");
          localStorage.setItem("username", this.username);
        } else {
          localStorage.removeItem("rememberMe");
          localStorage.removeItem("username");
        }

        this.error = null;

        setTimeout(() => {
          window.location.reload();
        }, 500);

      } catch (e) {
        this.isLoading = false;

        if (e.response && e.response.data && e.response.data.detail) {
          this.error = e.response.data.detail;
        } else if (e.code === 'ECONNABORTED') {
          this.error = "Connection timeout. Please try again.";
        } else if (!navigator.onLine) {
          this.error = "No internet connection";
        } else {
          this.error = "Login failed. Please check your credentials.";
        }
      }
    },
    goToRegister() {
      this.$router.push({ name: "Register" });
    },
    forgotPassword() {
      alert("Password reset functionality would be implemented here");
    }
  },
  mounted() {
    if (localStorage.getItem("rememberMe") === "true") {
      this.rememberMe = true;
      const savedUsername = localStorage.getItem("username");
      if (savedUsername) {
        this.username = savedUsername;
      }
    }
  }
};
</script>

<style scoped>
.login-container {
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 16px;
  background: linear-gradient(135deg, #0f172a 0%, #1e293b 100%);
  position: relative;
  overflow: hidden;
}

.bg-blur-1, .bg-blur-2 {
  position: absolute;
  border-radius: 50%;
  filter: blur(60px);
  opacity: 0.15;
  z-index: 0;
}

.bg-blur-1 {
  width: 300px;
  height: 300px;
  background: linear-gradient(45deg, #3b82f6, #8b5cf6);
  top: -150px;
  right: -80px;
}

.bg-blur-2 {
  width: 250px;
  height: 250px;
  background: linear-gradient(45deg, #10b981, #06b6d4);
  bottom: -120px;
  left: -80px;
}

.login-card {
  width: 100%;
  max-width: 400px;
  background: rgba(30, 41, 59, 0.95);
  backdrop-filter: blur(8px);
  border-radius: 16px;
  padding: 28px 24px;
  box-shadow: 0 16px 48px rgba(0, 0, 0, 0.25);
  border: 1px solid rgba(255, 255, 255, 0.08);
  position: relative;
  z-index: 1;
  animation: slideUp 0.6s ease;
}

.login-header {
  text-align: center;
  margin-bottom: 24px;
}

.login-icon {
  color: #60a5fa;
  margin-bottom: 16px;
}

.login-title {
  font-size: 24px;
  font-weight: 700;
  margin: 0 0 6px 0;
  background: linear-gradient(90deg, #60a5fa, #38bdf8);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  background-clip: text;
}

.login-subtitle {
  color: #94a3b8;
  font-size: 14px;
  margin: 0;
}

.login-form {
  display: flex;
  flex-direction: column;
  gap: 18px;
}

.form-group {
  position: relative;
}

.form-label {
  display: flex;
  align-items: center;
  gap: 6px;
  color: #cbd5e1;
  font-size: 13px;
  font-weight: 500;
  margin-bottom: 6px;
}

.input-icon {
  color: #60a5fa;
}

.input-wrapper {
  position: relative;
  width: 100%;
}

.form-input {
  width: 100%;
  padding: 10px 36px 10px 12px;
  background: #1e293b;
  border: 1.5px solid #334155;
  border-radius: 8px;
  color: #f1f5f9;
  font-size: 13px;
  transition: all 0.3s;
  box-sizing: border-box;
  min-height: 40px;
  line-height: 1.2;
}

.form-input:focus {
  outline: none;
  border-color: #60a5fa;
  box-shadow: 0 0 0 2px rgba(96, 165, 250, 0.15);
}

.form-input::placeholder {
  color: #64748b;
  font-size: 13px;
}

.password-toggle {
  position: absolute;
  right: 10px;
  top: 50%;
  transform: translateY(-50%);
  background: none;
  border: none;
  color: #94a3b8;
  cursor: pointer;
  font-size: 16px;
  padding: 0;
  width: 24px;
  height: 24px;
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 2;
}

.password-toggle:hover {
  color: #60a5fa;
}

.form-options {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: -4px;
}

.checkbox-container {
  display: flex;
  align-items: center;
  cursor: pointer;
  color: #cbd5e1;
  font-size: 13px;
  gap: 6px;
}

.checkbox-container input {
  display: none;
}

.checkmark {
  width: 16px;
  height: 16px;
  border: 1.5px solid #475569;
  border-radius: 3px;
  display: inline-block;
  position: relative;
  transition: all 0.3s;
}

.checkbox-container input:checked + .checkmark {
  background-color: #60a5fa;
  border-color: #60a5fa;
}

.checkbox-container input:checked + .checkmark::after {
  content: "✓";
  position: absolute;
  color: white;
  font-size: 10px;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}

.forgot-password {
  color: #60a5fa;
  text-decoration: none;
  font-size: 13px;
  transition: color 0.3s;
}

.forgot-password:hover {
  color: #38bdf8;
  text-decoration: underline;
}

.login-button {
  background: linear-gradient(135deg, #3b82f6, #2563eb);
  color: white;
  border: none;
  border-radius: 10px;
  padding: 14px;
  font-size: 14px;
  font-weight: 600;
  cursor: pointer;
  transition: all 0.3s;
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 8px;
  margin-top: 8px;
}

.login-button:hover:not(:disabled) {
  background: linear-gradient(135deg, #2563eb, #1d4ed8);
  transform: translateY(-1px);
  box-shadow: 0 6px 20px rgba(37, 99, 235, 0.25);
}

.login-button:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}

.login-button.loading {
  background: #475569;
}

.button-icon {
  transition: transform 0.3s;
}

.login-button:hover .button-icon {
  transform: translateX(3px);
}

.loading-spinner {
  width: 18px;
  height: 18px;
  border: 2px solid rgba(255, 255, 255, 0.3);
  border-top-color: white;
  border-radius: 50%;
  animation: spin 0.8s linear infinite;
}

.register-link {
  text-align: center;
  margin-top: 16px;
  padding-top: 16px;
  border-top: 1px solid #334155;
}

.register-link p {
  color: #94a3b8;
  margin-bottom: 12px;
  font-size: 13px;
}

.register-button {
  background: transparent;
  color: #60a5fa;
  border: 1.5px solid #60a5fa;
  border-radius: 8px;
  padding: 10px 24px;
  font-size: 13px;
  font-weight: 600;
  cursor: pointer;
  transition: all 0.3s;
  width: 100%;
}

.register-button:hover {
  background: rgba(96, 165, 250, 0.08);
  transform: translateY(-1px);
}

.error-notification {
  background: rgba(239, 68, 68, 0.1);
  border: 1px solid rgba(239, 68, 68, 0.3);
  color: #fca5a5;
  padding: 12px;
  border-radius: 10px;
  margin-top: 20px;
  display: flex;
  align-items: center;
  gap: 10px;
  font-size: 13px;
  animation: slideIn 0.3s ease;
}

.error-notification svg {
  flex-shrink: 0;
}

.close-error {
  margin-left: auto;
  background: none;
  border: none;
  color: #fca5a5;
  font-size: 20px;
  cursor: pointer;
  padding: 0;
  width: 24px;
  height: 24px;
  display: flex;
  align-items: center;
  justify-content: center;
}

@keyframes slideUp {
  from {
    opacity: 0;
    transform: translateY(30px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

@keyframes slideIn {
  from {
    opacity: 0;
    transform: translateY(-10px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

@keyframes spin {
  to { transform: rotate(360deg); }
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.3s;
}
.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}

@media (max-width: 480px) {
  .login-card {
    padding: 24px 20px;
    margin: 16px;
    max-width: 100%;
  }

  .login-title {
    font-size: 22px;
  }

  .login-subtitle {
    font-size: 13px;
  }

  .login-form {
    gap: 16px;
  }

  .form-input {
    padding: 9px 32px 9px 10px;
    font-size: 13px;
    min-height: 38px;
  }

  .form-options {
    flex-direction: column;
    align-items: flex-start;
    gap: 10px;
  }

  .login-button {
    padding: 12px;
    font-size: 13px;
  }

  .register-button {
    padding: 9px 20px;
    font-size: 12px;
  }
}

@media (max-width: 360px) {
  .login-card {
    padding: 20px 16px;
  }

  .login-title {
    font-size: 20px;
  }

  .form-label {
    font-size: 12px;
  }
}
</style>