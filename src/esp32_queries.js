

const TEST_MODE = true;

window.onload = function() {

var testServer = "https://jsonplaceholder.typicode.com/todos/1";
var espAddress = "http://192.168.1.15";

const REFRESH_RATE = 1000; // in ms

var currents = [10, 20.5, 30, 5.3, 11, 8];
var armDistance = 0;

// bar graph
var chart = new CanvasJS.Chart("chartContainer", {
	animationEnabled: true,
	
	title:{
		text:"Current Draw per Motor"
	},
	axisX:{
		title: "Motor",
		interval: 1
	},
	axisY2:{
		interlacedColor: "rgba(1,77,101,.2)",
		gridColor: "rgba(1,77,101,.1)",
		title: "Current[A]"
	},
	data: [{
		type: "bar",
		name: "Motor",
		axisYType: "secondary",
		color: "#014D65",
		dataPoints: [
			{ y: currents[0], label: "0" },
			{ y: currents[1], label: "1" },
			{ y: currents[2], label: "2" },
			{ y: currents[3], label: "3" },
			{ y: currents[4], label: "4" },
			{ y: currents[5], label: "5" }
		]
	}]
});

var opts = {
  angle: 0.15, /// The span of the gauge arc
  lineWidth: 0.44, // The line thickness
  pointer: {
    length: 0.9, // Relative to gauge radius
    strokeWidth: 0.035 // The thickness
  },
  colorStart: '#6FADCF',   // Colors
  colorStop: '#8FC0DA',    // just experiment with them
  strokeColor: '#E0E0E0'   // to see which ones work best for you
};
var target = document.getElementById('armDistanceGauge'); // your canvas element
var gauge = new Gauge(target).setOptions(opts); // create sexy gauge!
gauge.maxValue = 3000; // set max gauge value
gauge.setMinValue(0);  // set min value
gauge.set(1250); // set actual value
gauge.setTextField(document.getElementById("preview-textfield"));

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

// continuously make HTTP GET requests to the esp32 and display info in browser
async function runQueries()
{
	var server;
	if (TEST_MODE)
	{
		server = testServer;
	}
	else
	{
		server = espAddress;
	}

	while(true)
	{
		
		fetch(server)
  		.then(function(response) {
    		return response.json();
 	 	})
  		.then(function(myJson) {
   	 		var obj = JSON.parse(myJson);
   	 		currents[0] = parseInt(obj.Motor1, 10);
    		currents[1] = parseInt(obj.Motor2, 10);
    		currents[2] = parseInt(obj.Motor3, 10);

    		currents[3] = parseInt(obj.Motor4, 10);
    		currents[4] = parseInt(obj.Motor5, 10);
    		currents[5] = parseInt(obj.Motor6, 10);

    		armDistance = parseInt(obj.ArmDistance, 10);
    		gauge.set(armDistance); // set actual value
			gauge.setTextField(document.getElementById("preview-textfield"));
  		});

  		// update chart every second
		chart.render();
		var j = 0;
		for (; j < currents.length; j++)
		{
			chart.options.data[0].dataPoints[j].y = currents[j];  // Update data points
		}
		await sleep(REFRESH_RATE);
	}
}

// run the script
runQueries();
}

// button clicked (to restart motors)
function restartMotors() {
    var server;
	if (TEST_MODE)
	{
		server = testServer;
	}
	else
	{
		server = espAddress;
	}

	fetch(server+"/restart")
  		.then(function(response) {
    		return response.json();
 	 })
}
