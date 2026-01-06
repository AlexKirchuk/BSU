<template>
  <div class="register-container">
    <div class="register-card">
      <div class="register-header">
        <div class="register-icon">
          <svg width="40" height="40" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path d="M12 12C14.7614 12 17 9.76142 17 7C17 4.23858 14.7614 2 12 2C9.23858 2 7 4.23858 7 7C7 9.76142 9.23858 12 12 12Z"
                  stroke="currentColor" stroke-width="2"/>
            <path d="M20 21V19C20 16.7909 18.2091 15 16 15H8C5.79086 15 4 16.7909 4 19V21"
                  stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
            <path d="M12 12L12 18" stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
            <path d="M9 15L15 15" stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
          </svg>
        </div>
        <h1 class="register-title">Create Account</h1>
        <p class="register-subtitle">Join us and start managing your tasks</p>
      </div>

      <form @submit.prevent="register" class="register-form">
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
              placeholder="Choose a username"
              class="form-input"
              required
              autocomplete="username"
              :class="{ 'input-error': usernameError }"
            />
          </div>
          <div v-if="usernameError" class="input-hint error">
            {{ usernameError }}
          </div>
          <div v-else class="input-hint">
            At least 3 characters, letters and numbers only
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
              placeholder="Create a strong password"
              class="form-input"
              required
              autocomplete="new-password"
              :class="{ 'input-error': passwordError }"
              @input="validatePassword"
            />
            <button
              type="button"
              class="password-toggle"
              @click="showPassword = !showPassword"
            >
              {{ showPassword ? '👁️' : '👁️‍🗨️' }}
            </button>
          </div>

          <div class="password-strength">
            <div class="strength-bar" :class="passwordStrengthClass"></div>
            <div class="strength-label">
              <span v-if="password.length === 0">Password strength</span>
              <span v-else>{{ passwordStrengthText }}</span>
            </div>
          </div>

          <div class="password-requirements">
            <div class="requirement" :class="{ 'met': password.length >= 8 }">
              <span class="requirement-icon">{{ password.length >= 8 ? '✓' : '○' }}</span>
              At least 8 characters
            </div>
            <div class="requirement" :class="{ 'met': hasUppercase }">
              <span class="requirement-icon">{{ hasUppercase ? '✓' : '○' }}</span>
              One uppercase letter
            </div>
            <div class="requirement" :class="{ 'met': hasNumber }">
              <span class="requirement-icon">{{ hasNumber ? '✓' : '○' }}</span>
              One number
            </div>
            <div class="requirement" :class="{ 'met': hasSpecial }">
              <span class="requirement-icon">{{ hasSpecial ? '✓' : '○' }}</span>
              One special character
            </div>
          </div>
        </div>

        <div class="form-group">
          <label for="confirmPassword" class="form-label">
            <svg class="input-icon" width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path d="M22 11.0857V12.0057C21.9988 14.1621 21.3005 16.2604 20.0093 17.9875C18.7182 19.7147 16.9033 20.9782 14.8354 21.5896C12.7674 22.201 10.5573 22.1276 8.53447 21.3803C6.51168 20.633 4.78465 19.2518 3.61096 17.4428C2.43727 15.6338 1.87979 13.4938 2.02168 11.342C2.16356 9.19029 2.99721 7.14205 4.39828 5.5028C5.79935 3.86354 7.69279 2.72111 9.79619 2.24587C11.8996 1.77063 14.1003 1.98806 16.07 2.86572"
                    stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
              <path d="M22 4L12 14.01L9 11.01" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
            </svg>
            Confirm Password
          </label>
          <div class="input-wrapper">
            <input
              v-model="confirmPassword"
              id="confirmPassword"
              :type="showConfirmPassword ? 'text' : 'password'"
              placeholder="Re-enter your password"
              class="form-input"
              required
              autocomplete="new-password"
              :class="{ 'input-error': confirmPasswordError }"
            />
            <button
              type="button"
              class="password-toggle"
              @click="showConfirmPassword = !showConfirmPassword"
            >
              {{ showConfirmPassword ? '👁️' : '👁️‍🗨️' }}
            </button>
          </div>
          <div v-if="confirmPasswordError" class="input-hint error">
            {{ confirmPasswordError }}
          </div>
        </div>

        <div class="agreement">
          <label class="checkbox-container">
            <input type="checkbox" v-model="agreeTerms" />
            <span class="checkmark"></span>
            <span class="agreement-text">
              I agree to the
              <a href="#" class="terms-link" @click.prevent="showTerms">Terms of Service</a>
              and
              <a href="#" class="terms-link" @click.prevent="showPrivacy">Privacy Policy</a>
            </span>
          </label>
        </div>

        <button
          type="submit"
          class="register-button"
          :disabled="isLoading || !isFormValid"
          :class="{ 'loading': isLoading, 'disabled': !isFormValid }"
        >
          <span v-if="!isLoading">
            <svg class="button-icon" width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path d="M12 5V19" stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
              <path d="M5 12H19" stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
            </svg>
            Create Account
          </span>
          <span v-else class="loading-spinner"></span>
        </button>

        <div class="login-link">
          <p>Already have an account?</p>
          <router-link to="/login" class="login-button-link">
            <svg width="14" height="14" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path d="M10 8L6 12L10 16" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
              <path d="M6 12H18" stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
            </svg>
            Sign In
          </router-link>
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

      <transition name="fade">
        <div v-if="success" class="success-notification">
          <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <circle cx="12" cy="12" r="10" stroke="currentColor" stroke-width="2"/>
            <path d="M8 12L11 15L16 9" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
          </svg>
          <span>{{ success }}</span>
          <router-link to="/login" class="go-login">
            Go to Login →
          </router-link>
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
  data() {
    return {
      username: "",
      password: "",
      confirmPassword: "",
      agreeTerms: false,
      showPassword: false,
      showConfirmPassword: false,
      isLoading: false,
      error: null,
      success: null,
      usernameError: null,
      passwordError: null,
      confirmPasswordError: null
    };
  },
  computed: {
    isFormValid() {
      return this.username.length >= 3 &&
             this.password.length >= 8 &&
             this.password === this.confirmPassword &&
             this.agreeTerms &&
             !this.usernameError &&
             !this.passwordError &&
             !this.confirmPasswordError;
    },
    hasUppercase() {
      return /[A-Z]/.test(this.password);
    },
    hasNumber() {
      return /\d/.test(this.password);
    },
    hasSpecial() {
      return /[!@#$%^&*(),.?":{}|<>]/.test(this.password);
    },
    passwordStrength() {
      if (this.password.length === 0) return 0;
      let strength = 0;
      if (this.password.length >= 8) strength += 25;
      if (this.hasUppercase) strength += 25;
      if (this.hasNumber) strength += 25;
      if (this.hasSpecial) strength += 25;
      return strength;
    },
    passwordStrengthText() {
      const strength = this.passwordStrength;
      if (strength < 25) return "Very Weak";
      if (strength < 50) return "Weak";
      if (strength < 75) return "Good";
      return "Strong";
    },
    passwordStrengthClass() {
      const strength = this.passwordStrength;
      if (strength < 25) return "very-weak";
      if (strength < 50) return "weak";
      if (strength < 75) return "good";
      return "strong";
    }
  },
  watch: {
    username(newVal) {
      if (newVal.length === 0) {
        this.usernameError = null;
        return;
      }
      if (newVal.length < 3) {
        this.usernameError = "Username must be at least 3 characters";
      } else if (!/^[a-zA-Z0-9_]+$/.test(newVal)) {
        this.usernameError = "Only letters, numbers and underscores allowed";
      } else {
        this.usernameError = null;
      }
    },
    password(newVal) {
      if (newVal.length === 0) {
        this.passwordError = null;
        return;
      }
      if (newVal.length < 8) {
        this.passwordError = "Password must be at least 8 characters";
      } else if (!this.hasUppercase) {
        this.passwordError = "Password must contain at least one uppercase letter";
      } else if (!this.hasNumber) {
        this.passwordError = "Password must contain at least one number";
      } else if (!this.hasSpecial) {
        this.passwordError = "Password must contain at least one special character";
      } else {
        this.passwordError = null;
      }
    },
    confirmPassword(newVal) {
      if (newVal.length === 0) {
        this.confirmPasswordError = null;
        return;
      }
      if (newVal !== this.password) {
        this.confirmPasswordError = "Passwords do not match";
      } else {
        this.confirmPasswordError = null;
      }
    }
  },
  methods: {
    async register() {
      if (!this.isFormValid) return;

      this.isLoading = true;
      this.error = null;
      this.success = null;

      try {
        await api.post("/register", {
          username: this.username,
          password: this.password
        });

        this.success = "🎉 Account created successfully! You can now log in.";
        this.error = null;

        setTimeout(() => {
          this.username = "";
          this.password = "";
          this.confirmPassword = "";
          this.agreeTerms = false;
        }, 3000);

      } catch (e) {
        this.error = e.response?.data?.detail || "Registration failed. Please try again.";
        this.success = null;
      } finally {
        this.isLoading = false;
      }
    },
    showTerms() {
      alert("Terms of Service will be displayed here");
    },
    showPrivacy() {
      alert("Privacy Policy will be displayed here");
    },
    validatePassword() {
    }
  }
};
</script>

<style scoped>
.register-container {
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
  background: linear-gradient(45deg, #8b5cf6, #d946ef);
  top: -150px;
  left: -80px;
}

.bg-blur-2 {
  width: 250px;
  height: 250px;
  background: linear-gradient(45deg, #10b981, #06b6d4);
  bottom: -120px;
  right: -80px;
}

.register-card {
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

.register-header {
  text-align: center;
  margin-bottom: 24px;
}

.register-icon {
  color: #8b5cf6;
  margin-bottom: 16px;
}

.register-title {
  font-size: 24px;
  font-weight: 700;
  margin: 0 0 6px 0;
  background: linear-gradient(90deg, #8b5cf6, #d946ef);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  background-clip: text;
}

.register-subtitle {
  color: #94a3b8;
  font-size: 14px;
  margin: 0;
}

.register-form {
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
  color: #8b5cf6;
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
  border-color: #8b5cf6;
  box-shadow: 0 0 0 2px rgba(139, 92, 246, 0.15);
}

.form-input.input-error {
  border-color: #ef4444;
}

.form-input.input-error:focus {
  box-shadow: 0 0 0 2px rgba(239, 68, 68, 0.15);
}

.input-hint {
  font-size: 11px;
  color: #64748b;
  margin-top: 4px;
  margin-left: 2px;
  line-height: 1.2;
}

.input-hint.error {
  color: #ef4444;
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
  color: #8b5cf6;
}

.password-strength {
  margin-top: 8px;
}

.strength-bar {
  height: 4px;
  background: #334155;
  border-radius: 2px;
  overflow: hidden;
  position: relative;
}

.strength-bar::after {
  content: '';
  position: absolute;
  top: 0;
  left: 0;
  height: 100%;
  width: 0;
  border-radius: 2px;
  transition: width 0.3s ease, background 0.3s ease;
}

.strength-bar.very-weak::after {
  width: 25%;
  background: #ef4444;
}

.strength-bar.weak::after {
  width: 50%;
  background: #f59e0b;
}

.strength-bar.good::after {
  width: 75%;
  background: #60a5fa;
}

.strength-bar.strong::after {
  width: 100%;
  background: #10b981;
}

.strength-label {
  font-size: 11px;
  color: #94a3b8;
  text-align: right;
  margin-top: 3px;
}

.password-requirements {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 6px;
  margin-top: 8px;
}

.requirement {
  display: flex;
  align-items: flex-start;
  gap: 4px;
  font-size: 11px;
  color: #64748b;
  line-height: 1.1;
}

.requirement.met {
  color: #10b981;
}

.requirement-icon {
  font-size: 9px;
  width: 12px;
  height: 12px;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-shrink: 0;
  margin-top: 1px;
}

.agreement {
  margin: 8px 0;
}

.agreement-text {
  color: #cbd5e1;
  font-size: 12px;
  line-height: 1.4;
}

.terms-link {
  color: #8b5cf6;
  text-decoration: none;
  font-size: 12px;
  transition: color 0.3s;
}

.terms-link:hover {
  color: #a78bfa;
  text-decoration: underline;
}

.register-button {
  background: linear-gradient(135deg, #8b5cf6, #7c3aed);
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

.register-button:hover:not(:disabled):not(.disabled) {
  background: linear-gradient(135deg, #7c3aed, #6d28d9);
  transform: translateY(-1px);
  box-shadow: 0 6px 20px rgba(139, 92, 246, 0.25);
}

.register-button:disabled,
.register-button.disabled {
  opacity: 0.5;
  cursor: not-allowed;
  background: #475569;
}

.register-button.loading {
  background: #475569;
}

.button-icon {
  transition: transform 0.3s;
}

.register-button:hover .button-icon {
  transform: rotate(90deg);
}

.loading-spinner {
  width: 18px;
  height: 18px;
  border: 2px solid rgba(255, 255, 255, 0.3);
  border-top-color: white;
  border-radius: 50%;
  animation: spin 0.8s linear infinite;
}

.login-link {
  text-align: center;
  margin-top: 16px;
  padding-top: 16px;
  border-top: 1px solid #334155;
}

.login-link p {
  color: #94a3b8;
  margin-bottom: 12px;
  font-size: 13px;
}

.login-button-link {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 8px;
  color: #60a5fa;
  text-decoration: none;
  font-weight: 600;
  padding: 10px 16px;
  border: 1.5px solid #334155;
  border-radius: 8px;
  transition: all 0.3s;
  background: transparent;
  width: 100%;
  font-size: 13px;
  box-sizing: border-box;
}

.login-button-link:hover {
  background: rgba(96, 165, 250, 0.08);
  border-color: #60a5fa;
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

.success-notification {
  background: rgba(16, 185, 129, 0.1);
  border: 1px solid rgba(16, 185, 129, 0.3);
  color: #6ee7b7;
  padding: 12px;
  border-radius: 10px;
  margin-top: 20px;
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 10px;
  font-size: 13px;
  animation: slideIn 0.3s ease;
}

.success-notification svg {
  flex-shrink: 0;
}

.go-login {
  color: #6ee7b7;
  text-decoration: none;
  font-weight: 600;
  transition: color 0.3s;
}

.go-login:hover {
  color: #34d399;
  text-decoration: underline;
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
  .register-card {
    padding: 24px 20px;
    margin: 12px;
    max-width: 100%;
  }

  .register-title {
    font-size: 22px;
  }

  .register-subtitle {
    font-size: 13px;
  }

  .register-form {
    gap: 16px;
  }

  .form-input {
    padding: 9px 32px 9px 10px;
    font-size: 13px;
    min-height: 38px;
  }

  .password-requirements {
    grid-template-columns: 1fr;
    gap: 5px;
  }

  .requirement {
    font-size: 11px;
  }

  .agreement-text {
    font-size: 11px;
  }

  .register-button {
    padding: 12px;
    font-size: 13px;
  }

  .login-button-link {
    padding: 9px 14px;
    font-size: 12px;
  }
}

@media (max-width: 360px) {
  .register-card {
    padding: 20px 16px;
  }

  .register-title {
    font-size: 20px;
  }

  .form-label {
    font-size: 12px;
  }

  .input-hint,
  .strength-label,
  .requirement {
    font-size: 10px;
  }
}
</style>