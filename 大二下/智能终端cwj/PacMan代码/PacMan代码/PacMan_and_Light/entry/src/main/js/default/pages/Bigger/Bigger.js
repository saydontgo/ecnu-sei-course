import router from '@system.router';
export default {
    data: {
        title: ""
    },
    onInit() {
        this.title = "You Win and Get Stronger";
    },
    toback(){
        router.replace({
            uri: 'pages/index/index'
        });
    },
}
