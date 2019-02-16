function changeImage() {
            var image = document.getElementById('photo');
            if (image.src.match("Diapo/pause.png")) {
                image.src = "Diapo/play.png";
            }
            else {
                image.src = "Diapo/pause.png";
            }
        }


var main = function() {

	var paused = false

	$('.arrowR').click(function() {
		paused = true;
		$('#slideshow > div:first')
		.fadeOut(200)
		.next()
		.fadeIn(200)
		.end()
		.appendTo('#slideshow');
	});
		
	$('.arrowL').click(function() {
		paused = true;
		$('#slideshow > div:last')
		.fadeIn(200)
		.prependTo('#slideshow')
		.next()
		.fadeOut(200)
		.end();

		
	});

	$('.bouton').click(function() {
		paused = false;
	});
	
	setInterval(function() {
		if (paused === false) { 
			$('#slideshow > div:first')
			.fadeOut(200)
			.next()
			.fadeIn(200)
			.end()
			.appendTo('#slideshow');
		};
	},  2000);
   
	
};

$(document).ready(main);