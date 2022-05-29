var express = require('express');
var router = express.Router();
var dgram = require('dgram');
var client = dgram.createSocket('udp4');
const { route } = require('express/lib/application');
var server = dgram.createSocket('udp4');
var temp,hum,d1;
var minutes,hour = 0;
//import dgram from 'node:dgram';
//import { Buffer } from 'node:buffer';



server.bind(3000);
var list={tem:'192.168.0.100',
led:'192.168.0.200',
irs:'192.168.0.300',
}

/* GET home page. */

router.get('/', function(req, res, next) {
  console.log("message re "+list['irs'])
  server.on('message',function(msg, rinfo){
  d1 = new Date();  
  var key = msg.slice(13, 16);
  list[key]=msg.slice(0,13)
  temp = msg.slice(16,18);
  hum = msg.slice(25,27);
  console.log("message recived is "+msg)
  hour = d1.getHours();
  minutes = d1.getMinutes();
  });

   
   res.render('index', {temp,hum,hour,minutes});
});

router.post('/ledstatus', function(req, res, next) {

console.log(req.body.led)
led=String(list['led'])
const message = Buffer.from(req.body.led);
const client = dgram.createSocket('udp4');
client.send(message, 1234, led, (err) => {
  client.close();
}
)

  res.redirect('/')
})

module.exports = router;