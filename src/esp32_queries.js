
window.onload = function() {

var testServer = "https://jsonplaceholder.typicode.com/todos/1";
var espAddress = "http://192.168.1.15";

const TEST_MODE = true;
const REFRESH_RATE = 1000; // in ms

var currents = [10, 20.5, 30, 5.3, 11, 8];

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
