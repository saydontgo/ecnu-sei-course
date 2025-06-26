import app from '@system.app';
import router from '@system.router';

var cmdno = {init:0,close:1,read:2,deng:3,read_button:4}
export default {
    data: {
        mydata: {
            Lux: 0,
            LED: 'OFF',
            Button:-1
        },
    },
    onInit(){
        app.e53sc1service({
            cmd:cmdno.init,
            success(res){
            },
            fail(res){

            },
            complete(res){

            },
        })
        this.interval = setInterval(()=>this.query_button_Data(),100)
    },
    open(){
        console.log("open")
        let that = this
        app.e53sc1service({
            cmd:cmdno.deng,
            data:'ON',
            success(res){
                that.mydata = JSON.parse(res.e53_sc1)
            },
            fail(res){

            },
            complete(res){

            },
        })
    },
    close(){
        console.log("close")
        let that = this
        app.e53sc1service({
            cmd:cmdno.deng,
            data:'OFF',
            success(res){
                that.mydata = JSON.parse(res.e53_sc1)
            },
            fail(res){

            },
            complete(res){
                // console.log("complete")
            },
        })
    },
    start(){
        router.replace({
            uri: 'pages/Boy_and_Light/Boy_and_light'
        });
    },
    exit(){
        app.terminate()
    },
}