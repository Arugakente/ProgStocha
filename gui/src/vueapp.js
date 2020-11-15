import Vue from 'vue'
import VueToast from 'vue-toast-notification'
import Vuelidate from 'vuelidate'

import App from './App.vue'

Vue.use(VueToast, {
    position: 'bottom-right',
    duration: 5000
});

Vue.use(Vuelidate)

new Vue({
    render: h => h(App)
}).$mount('#vueapp')
