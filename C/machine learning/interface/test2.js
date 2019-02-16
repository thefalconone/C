
var express = require('express');
var session = require('cookie-session'); // Charge le middleware de sessions
var bodyParser = require('body-parser'); // Charge le middleware de gestion des paramètres
var urlencodedParser = bodyParser.urlencoded({ extended: false });

var app = express();

app.use(session({secret: 'todotopsecret'}))

app.get('/', function(req, res) {
	res.setHeader('Content-Type', 'text/plain');
	res.send('Vous êtes à l\'accueil, que puis-je pour vous ?');
})
.get('/sous-sol', function(req, res) {
	res.setHeader('Content-Type', 'text/plain');
	res.send('Vous êtes dans la cave à vins, ces bouteilles sont à moi !');
})
.get('/etage/:etagenum/chambre', function(req, res) {
	res.render("chambre.ejs", {etage: req.params.etagenum});
});


app.use(function(req, res, next){
	res.setHeader('Content-Type', 'text/plain');
	res.status(404).send('Page introuvable !');
});

app.listen(8080);