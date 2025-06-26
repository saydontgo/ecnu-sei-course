import router from '@system.router';
export default {
    data: {
        title: ""
    },
    onInit() {
        this.title = "Caught by Lion and Game Over";
    },
    toback(){
        router.replace({
            uri: 'pages/index/index'
        });
    },
}
