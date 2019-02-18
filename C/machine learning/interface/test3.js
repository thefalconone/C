//-----------------exe----------------

var execFile = require("child_process").execFile;

const child = execFile("test.exe", [], (error, stdout, stderr) => {
	if (error) {
		console.error("stderr", stderr);
		throw error;
	}
	console.log("stdout", stdout);
});

//----------------http----------------

var http = require("http");

var instructionsNouveauVisiteur = function(req, res) {
	res.writeHead(200, {"Content-Type": "text/html"});
	res.render(stdout);
	res.end()
}

var server = http.createServer(instructionsNouveauVisiteur);

server.listen(8080);