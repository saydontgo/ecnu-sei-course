import app from '@system.app';
export default {
    data: {
        title: 'Hello World'
    },
    exit(e){
        app.terminate()
    }
}
