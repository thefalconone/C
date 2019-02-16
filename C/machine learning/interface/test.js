//cd Documents\Charles\Informatique\C\machine learning\interface

var monmodule = require("./module");

var http = require("http");
var url = require("url");
var querystring = require("querystring");

var instructionsNouveauVisiteur = function(req, res) {
	var page = url.parse(req.url).pathname;
	var params = querystring.parse(url.parse(req.url).query);

	if(page == "/"){
		res.writeHead(200, {"Content-Type": "text/html"});

		if ('prenom' in params && 'nom' in params)
			res.write('Vous vous appelez ' + params['prenom'] + ' ' + params['nom']);

		monmodule.afficher();
	}
	else
		res.writeHead(404);

	res.end()
}

var server = http.createServer(instructionsNouveauVisiteur);

server.listen(8080);
