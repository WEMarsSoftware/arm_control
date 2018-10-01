
window.onload = function() {
// make test queries (HTTP GET test server);
var testServer = "https://httpbin.org";
var espAddress = "http://192.168.1.15";
var motorIDs = ["Motor1","Motor2","Motor3","Motor4","Motor5","Motor6"];
var motorShutdown = 1;

const TEST_MODE = false;

var currents = [10, 20.5, 30, 15.3, 11, 8];

// bar graph
var chart = new CanvasJS.Chart("chartContainer", {
	animationEnabled: true,
	
	title:{
		text:"Current Draw per Motor"
	},
	axisX:{
		interval: 1
	},
	axisY2:{
		interlacedColor: "rgba(1,77,101,.2)",
		gridColor: "rgba(1,77,101,.1)",
		title: "Current"
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
	while(true)
	{
		/*
		if (!TEST_MODE)
		{
			fetch(testServer).then(function(response) {
				// response should be full text response
				var i;
				for (i = 0; i < motorIDs.length; i++) { 
    				document.getElementById(motorIDs[i]).innerHTML = document.getElementById(motorIDs[i]).innerHTML.slice(0, -4);
    				document.getElementById(motorIDs[i]).innerHTML += "NEW#";

    				//TODO: parse response and properly check for motor shutoff event
    				if (motorShutdown != -1)
    				{
						document.getElementById(motorIDs[motorShutdown-1]).style.color = "red";
    				}
				}

				if (response.prototype.includes("shutoff"))
				{
					// do something useful
				}
			});
		}

		await sleep(3000);

		if (TEST_MODE)
		{
				fetch(espAddress).then(function(response) {
					// placeholder
			});
		}*/
		await sleep(1000);
		chart.render();
		chart.options.data[0].dataPoints[3].y += 5;  // Update an existing dataPoint
	}
}

// run the script
runQueries();
}
