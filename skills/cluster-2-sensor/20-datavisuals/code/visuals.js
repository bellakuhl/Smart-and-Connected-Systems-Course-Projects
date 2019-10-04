var fs = require("fs");
var text = fs.readFileSync("smoke.txt");
var textByLine = text.split("\n")

http.createServer(function (req, res) {
  //Open a file on the server and return its content:
  fs.readFile('demofile1.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data);
    return res.end();
  });
}).listen(8080);

// General Code
function getData(Time, ID, Smoke, Temp) {
var labels = read("smoke.txt").split("\n");
for (var i = 1; i < labels.length; ++i) {
    labels[i] = labels[i].trim();
   }
for (var i = 0; i < labels.length; ++i) {
    var value = labels[i].split("  ");
    var sex = labels[0];
    var name = value[1];
    if (sex == "F") {
      females.enqueue(new Dancer(name, sex));
    } else {
        males.enqueue(new Dancer(name, sex)); }
    }
 }
