//灯状态 0是关闭 1是开启
//that.title = JSON.stringify(res)
//that.statu = res.led_status
//that.statu = res['led_status']
var led = {open:1,close:0,change:2}
import app from '@system.app';
export default {
    data: {
        title: 'BearPi-HM Micro',
        statu:'0'
    },
    exit(e){
        app.terminate()
    },
    open(e){
        let that = this
        app.ledcontrol({
            code:led.open,
            success(res){
                that.statu = res.led_status
            },
            fail(res,code){

            },
            complete(){

            }
        })
    },
    close(e){
        let that = this
        app.ledcontrol({
            code:led.close,
            success(res){
                that.statu = res.led_status
            },
            fail(res,code){

            },
            complete(){

            }
        })
    },
    change(e){
        let that = this
        app.ledcontrol({
            code:led.change,
            success(res){
                that.statu = res.led_status
            },
            fail(res,code){

            },
            complete(){

            }
        })
    }
}
