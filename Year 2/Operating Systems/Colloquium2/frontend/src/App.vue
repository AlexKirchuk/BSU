<template>
  <div>
    <nav v-if="isAuth" class="nav">
      <span>🧑 Logged in</span>
      <button @click="logout">Logout</button>
    </nav>

    <router-view />
  </div>
</template>

<script>
export default {
  computed: {
    isAuth() {
      return !!localStorage.getItem("token");
    }
  },
  methods: {
    logout() {
      localStorage.removeItem("token");
      this.$router.push("/login");
    }
  }
};
</script>

<style scoped>
.nav {
  display: flex;
  justify-content: space-between;
  padding: 1rem;
  background: #0f172a;
  color: #e2e8f0;
}
button {
  background: #ef4444;
  color: white;
  border: none;
  padding: 0.4rem 0.8rem;
  border-radius: 6px;
  cursor: pointer;
}
</style>