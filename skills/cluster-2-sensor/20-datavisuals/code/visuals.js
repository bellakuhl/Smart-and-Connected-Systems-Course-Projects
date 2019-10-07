
window.onload = function() {
        var dataPoints0 = [];
        function getDataPointsFromCSV(csv, field) { // get data from file
            var dataPoints0 = csvLines = points = [];
            csvLines = csv.split(/[\r?\n|\r|\n]+/);

            for (var i = 0; i < csvLines.length; i++)
                if (csvLines[i].length > 0) {
                    points = csvLines[i].split(",");
                    dataPoints0.push({
                        x: parseFloat(points[1]),
                        y: parseFloat(points[field])
                    });
                }
        }
        var chart = new CanvasJS.Chart("chartContainer", {
        	title: {
        		text: "Stock Data"
        	},
        	axisX: {
              	title: "Month (2018)",
        		valueFormatString: "#"
        	},
        	axisY2: {
        		title: "Closing",
        		prefix: "$"
            },
        	toolTip: {
        		shared: true
        	},
        	legend: {
        		cursor: "pointer",
        		verticalAlign: "top",
        		horizontalAlign: "center",
        		dockInsidePlotArea: true,
        		itemclick: toogleDataSeries
        	},
        	data: [{
        		type:"line",
        		axisYType: "secondary",
        		name: "AMZN",
        		showInLegend: true,
        		markerSize: 0,
        		yValueFormatString: "$###",
        		dataPoints: [
              for (int i = 0; i < 5; i++) {
                x: i
                for (int j = 0; j < dataPoints0.length; j++) {
                  y: dataPoints0[0][j];
                }
              }
        	{
        		type: "line",
        		axisYType: "secondary",
        		name: "GOOGL",
        		showInLegend: true,
        		markerSize: 0,
        		yValueFormatString: "$####",
        		dataPoints: [
              for (int i = 0; i < 5; i++) {
                x: i
                for (int j = 0; j < dataPoints0.length; j++) {
                  y: dataPoints0[1][j];
                }
              }
        		]
        	},
        	{
        		type: "line",
        		axisYType: "secondary",
        		name: "FB",
        		showInLegend: true,
        		markerSize: 0,
        		yValueFormatString: "$###",
        		dataPoints: [
              for (int i = 0; i < 5; i++) {
                x: i
                for (int j = 0; j < dataPoints0.length; j++) {
                  y: dataPoints0[2][j];
                }
              }
        		]
        	},
        	{
        		type: "line",
        		axisYType: "secondary",
        		name: "MSFT",
        		showInLegend: true,
        		markerSize: 0,
        		yValueFormatString: "$#",
        		dataPoints: [
              for (int i = 0; i < 5; i++) {
                x: i
                for (int j = 0; j < dataPoints0.length; j++) {
                  y: dataPoints0[3][j];
                }
              }
        		]
        	}]
        });
        chart.render();
}());



























/*var fs = require("fs");
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
    var Time = value[0];
    var ID = value[1];
    var Smoke = value[2];
    var Temp = value[3];
    if (sex == "F") {
      females.enqueue(new Dancer(name, sex));
    } else {
        males.enqueue(new Dancer(name, sex)); }
    }
 }
*/
