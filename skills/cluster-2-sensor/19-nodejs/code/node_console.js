// Require the serialport node module
var serialport = require('serialport');
//var SerialPort = serialport.SerialPort;  // Open the port
var port = new serialport("COM4", {
    baudRate: 115200
});// Read the port data
port.on("open", function () {
    console.log('open');
});
port.on('data', function(data) {
    console.log(data.toString());
});
