/*
 * Copyright (c) 2022 Nanjing Xiaoxiongpai Intelligent Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import router from '@system.router';
import app from '@system.app';

var cmdno = {init:0,close:1,read:2,deng:3,read_button:4}

export default {
    data: {
        mydata: {
            Lux: 0,
            LED: 'OFF',
            Button:-1
        },
        interval:0,
        // 吃豆人图片（包括不同方向、运动或静止状态）
        Pac_img:'/GameIMG/stop4.png',
        // 吃豆人图片大小
        wide: 75,
        high: 60,
        // 吃豆人坐标
        up_pos: 200,
        left_pos:-720,
        // 吃豆人状态（动/静）
        move:0,
        // 吃豆人移动方向
        dir:0,
        // 黄豆的坐标、图标
        light_uppos:250,
        light_leftpos:250,
        light_img1:'/GameIMG/light1.png'
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
    toback(){
        app.e53ia1service({
            cmd:cmdno.close,
            success(res){
            },
            fail(res){

            },
            complete(res){

            },
        })
        clearInterval(this.interval)
        router.replace({
            uri: 'pages/index/index'
        });
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
    queryData(){
        console.log("query")
        let that = this
        app.e53sc1service({
            cmd:cmdno.read,
            data:'',
            success(res){
                that.mydata = JSON.parse(res.e53_sc1)
            },
            fail(res){

            },
            complete(res){

            },
        })
    },
    up(){
        this.wide=60
        this.high=75
        this.Pac_img="/GameIMG/move1.png"
        this.dir=1
        if(this.up_pos>0){
           if(this.left_pos>-710&&this.left_pos<-550){
               if(this.up_pos!=170){
                   this.up_pos=this.up_pos-5;
               }
           }
           else if(this.left_pos>-410&&this.left_pos<-270){
                if(this.up_pos!=190){
                    this.up_pos=this.up_pos-5;
                }
            }
           else if(this.left_pos>-220&&this.left_pos<0){
               if(this.up_pos!=310){
                   this.up_pos=this.up_pos-5;
               }
           }
           else this.up_pos=this.up_pos-5;
        }

    },
    down(){
        this.wide=60
        this.high=75
        this.Pac_img="/GameIMG/move2.png"
        this.dir=2
        if(this.up_pos<280){
            if(this.left_pos>-710&&this.left_pos<-550){
                if(this.up_pos!=5){
                    this.up_pos=this.up_pos+5;
                }
            }
            else if(this.left_pos>-410&&this.left_pos<-270){
                if(this.up_pos!=30){
                    this.up_pos=this.up_pos+5;
                }
            }
            else if(this.left_pos>-220&&this.left_pos<0){
                if(this.up_pos!=80){
                    this.up_pos=this.up_pos+5;
                }
            }
            else this.up_pos=this.up_pos+5;
        }

    },
    left(){
        this.move=1
        this.wide=75
        this.high=60
        this.Pac_img="/GameIMG/move3.png"
        this.dir=3
        if(this.left_pos>-720){
            if(this.up_pos>10&&this.up_pos<170){
                if(this.left_pos<-405) {
                    if (this.left_pos == -550) this.move=0
                }
            }
           if(this.up_pos>30&&this.up_pos<190){
                if(this.left_pos<-220) {
                    if (this.left_pos == -260) this.move=0
                }
            }
            if(this.up_pos>80&&this.up_pos<310){
                if(this.left_pos<300){
                    if(this.left_pos==0) this.move=0
                }
            }
            if(this.move)  this.left_pos=this.left_pos-5;
        }

    },
    right(){
        this.move=1
        this.wide=75
        this.high=60
        this.Pac_img="/GameIMG/move4.png"
        this.dir=4
        if(this.up_pos<350){
            if(this.up_pos>10&&this.up_pos<170){
                if(this.left_pos<-640) {
                    if (this.left_pos == -710) this.move=0
                }
            }
            if(this.up_pos>30&&this.up_pos<190){
                if(this.left_pos<-350) {
                    if (this.left_pos == -410) this.move=0
                }
            }
            if(this.up_pos>80&&this.up_pos<310){
                if(this.left_pos<-160||this.left_pos>=0) {
                    if (this.left_pos == -230) this.move=0
                }
            }
            if(this.move) this.left_pos=this.left_pos+5;
        }

    },
    work(){
        // 处理移动
        if (this.mydata.Button==1) this.up();
        else if (this.mydata.Button==2) this.down();
        else if (this.mydata.Button==3) this.left();
        else if (this.mydata.Button==4) this.right();
        else this.Pac_img="/GameIMG/stop"+this.dir+".png"
        //判断游戏是否结束（即碰到狮子（输）/黄豆（赢））
        if((this.left_pos==-570||this.left_pos==-410)&&this.up_pos>=130&&this.up_pos<270
        ||(this.up_pos==130||this.up_pos==270)&&this.left_pos>=-570&&this.left_pos<=-410){
            router.replace({
                uri: "/pages/Caught/Caught"
            });
        }
        if((this.left_pos==-60||this.left_pos==65)&&this.up_pos>=10&&this.up_pos<=125
        ||(this.up_pos==10||this.up_pos==125)&&this.left_pos>=-60&&this.left_pos<=65){
            router.replace({
                uri: "/pages/Bigger/Bigger"
            });
        }
    },
    work_forever(){
        setInterval(function (){
            this.work()
        }.bind(this),125)
    },
    query_button_Data(){
        console.log("query1")
        let that = this
        app.e53sc1service({
            cmd:cmdno.read_button,
            data:'',
            success(res){
                that.mydata = JSON.parse(res.e53_sc1)
            },
            fail(res){

            },
            complete(res){

            },
        })
    }
}

// // console.log("up") left和up的pos同时满足障碍物横纵坐标，就不让走
// if(this.left_pos<-325) this.left_pos=this.left_pos+5;
// else {
//     if(this.up_pos>40) this.up_pos=this.up_pos-10;
//     else {
//         if(this.left_pos<10) this.left_pos=this.left_pos+5;
//     }
// }

