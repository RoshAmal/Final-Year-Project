var express = require('express');
var router = express.Router();
var dgram = require('dgram');
var server = dgram.createSocket('udp4');
var temp,hum;

server.bind(3000);

/* GET home page. */
router.get('/', function(req, res, next) {

  server.on('message',function(msg, rinfo){
    temp = msg.slice(14, 18);
    hum = msg.slice(25,29)
     console.log("message recived is "+msg)
     console.log("message recived is "+rinfo)
   })
   

  
  res.render('index', {temp,hum});
});

module.exports = router;