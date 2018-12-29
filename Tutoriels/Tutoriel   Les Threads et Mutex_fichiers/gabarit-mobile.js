$(function() {
	
	var hauteurEntete = $('#gabarit_mobile').height();
	if (hauteurEntete > 80)
		$('#gabarit_mobile').addClass('longMenu');
	else
		$('#gabarit_mobile').removeClass('longMenu');
	
	var open = false;
	var clic = false;
	
	$('#gabarit_mobile span').on('touchstart', function() {
		
		if (clic)
			return false;
		
		clic = true;
		
		if (open) {
			open = false;
			gabaritMobile_fermerMenu();
			
		} else {				
			open = true;
			gabaritMobile_ouvrirMenu();	
		}
		
		setTimeout(function() {
			clic = false;
		}, 300);
	});
	
	/* $(window).resize(function() {
		if (open) {
			open = false;
			gabaritMobile_fermerMenu();
			$('#gabarit_menu_mobile').removeClass('show');
		}
	}); */

});

function gabaritMobile_ouvrirMenu() {
	$('#gabarit_mobile span').addClass('activeSpan');
	$('#gabarit_menu_mobile ul:not(.gabarit_sousmenu)').show();
	$('#gabarit_menu_mobile a').click(gabaritMobile_clicRubrique);
}

function gabaritMobile_fermerMenu() {
	$('#gabarit_mobile span').removeClass('activeSpan');
	$('#gabarit_menu_mobile > ul > li.active_menu').removeClass('active_menu');
	$('#gabarit_menu_mobile ul.gabarit_sousmenu').hide();
}

function gabaritMobile_clicRubrique() {	
	var elem = $(this);

	if (elem.attr('data-idrub') == 1 || elem.attr('data-niv') == 2)
		return true;
	
	$('#gabarit_menu_mobile ul.gabarit_sousmenu').hide();
	elem.parent().children('ul.gabarit_sousmenu').show();
	$('#gabarit_menu_mobile > ul > li.active_menu').removeClass('active_menu');
	elem.parent().addClass('active_menu');
	$('#gabarit_menu_mobile a').click(gabaritMobile_clicRubrique);

	return false;
}