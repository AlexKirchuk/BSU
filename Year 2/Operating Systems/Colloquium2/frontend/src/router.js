import { createRouter, createWebHistory } from "vue-router";
import Login from "./components/Login.vue";
import Register from "./components/Register.vue";
import Tasks from "./components/Tasks.vue";

const router = createRouter({
  history: createWebHistory(),
  routes: [
    {
      path: "/login",
      name: "Login",
      component: Login
    },
    {
      path: "/register",
      name: "Register",
      component: Register
    },
    {
      path: "/tasks",
      name: "Tasks",
      component: Tasks,
      meta: { requiresAuth: true }
    },
    {
      path: "/",
      redirect: "/tasks"
    }
  ]
});

/* 🔐 Guard */
router.beforeEach((to, from, next) => {
  const token = localStorage.getItem("token");

  if (to.meta.requiresAuth && !token) {
    next("/login");
  } else if ((to.path === "/login" || to.path === "/register") && token) {
    next("/tasks");
  } else {
    next();
  }
});

export default router;