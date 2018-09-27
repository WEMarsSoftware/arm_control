
// make test queries (HTTP GET test server);
var responseText = "";
var testServer = "https://httpbin.org";

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function runQueries()
{
	while(true)
	{
		fetch(testServer).then(function(response) {
    		document.write(response.headers.get('Content-Type'));
		});

		await sleep(3000);
	}
}

runQueries();