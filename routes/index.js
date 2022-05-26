var express = require('express');
var router = express.Router();
var dgram = require('dgram');
var server = dgram.createSocket('udp4');
var temp,hum,d1;
var minutes,hour = 0;
server.bind(3000);

/* GET home page. */

router.get('/', function(req, res, next) {

  server.on('message',function(msg, rinfo){
  d1 = new Date();  
  temp = msg.slice(14, 16);
  hum = msg.slice(23,25);
  console.log("message recived is "+msg)
  hour = d1.getHours();
  minutes = d1.getMinutes();
  });

   var indication="Am"
   if (hour>12)
   indication="Pm"

   console.log("time"+hour)
   res.render('index', {temp,hum,hour,minutes});
});


module.exports = router;