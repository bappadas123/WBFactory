jQuery(document).ready(function(){	
	jQuery("#verified-epaments-data-form").submit();
	jQuery("#verified-epaments-data-form-2").submit();
	jQuery("#epaments-process").submit();
	jQuery("#repairer-epayments-process").submit();
	jQuery("#epayments-process-form3a").submit();
	history.pushState(null, null, document.URL);
	window.addEventListener('popstate', function () {
		history.pushState(null, null, document.URL);
	});
});