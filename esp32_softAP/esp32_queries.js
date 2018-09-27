
// make test queries (HTTP GET test server);
var testServer = "https://httpbin.org";
var espAddress = "http://192.168.1.15";
var motorIDs = ["Motor1","Motor2","Motor3","Motor4","Motor5","Motor6"];
var motorShutdown = 1;

const TEST_MODE = false;

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

// continuously make HTTP GET requests to the esp32 and display info in browser
async function runQueries()
{
	while(true)
	{
		if (!TEST_MODE)
		{
			fetch(testServer).then(function(response) {
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
			});
		}

		await sleep(3000);

		if (TEST_MODE)
		{
				fetch(espAddress).then(function(response) {
					// placeholder
			});
		}
	}
}

// run the script
runQueries();

