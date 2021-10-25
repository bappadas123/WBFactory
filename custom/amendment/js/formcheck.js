(function($) {
 
  Drupal.behaviors.other_details_part1 = {
  attach: function (context, settings) { 

/*jQuery(".numbersonly").on("keypress keyup blur",function (event) {
     jQuery(this).val(jQuery(this).val().replace(/[^0-9\.]/g,''));
	
			var keycode = (event.which) ? event.which : event.keyCode;
			
			 if ((keycode != 8) && (keycode < 48 || keycode > 57)) {
                return false;
            }
			
			
        });*/
		

	jQuery('.charField').on('keypress', (function(event) {
        var inputValue = event.charCode;
        if(!(inputValue >= 65 && inputValue <= 90) && !(inputValue >= 97 && inputValue <= 122) && (inputValue != 32 && inputValue != 38 && inputValue != 0)){
            event.preventDefault();
        }
    }));
	jQuery('.NoField').on('keypress', (function(event) {
        var inputValue = event.charCode;
        if(!(inputValue >= 48 && inputValue <= 57)){
            event.preventDefault();
        }
    })); 
	jQuery('.charNoField').on('keypress', (function(event) {
        var inputValue = event.charCode;
        if(!(inputValue >= 48 && inputValue <= 57) && !(inputValue >= 65 && inputValue <= 90) &&!(inputValue >= 97 && inputValue <= 122)){
            event.preventDefault();
        }
    }));
	jQuery('.NoField').on('keypress', (function(event) {
        var inputValue = event.charCode;
        if(!(inputValue >= 48 && inputValue <= 57)){
            event.preventDefault();
        }
    }));
	jQuery('.emailField').on('keypress', (function(event) {
        var inputValue = event.charCode;
        if(!(inputValue >= 48 && inputValue <= 57) && !(inputValue >= 65 && inputValue <= 90) && !(inputValue >= 97 && inputValue <= 122) && (inputValue != 45
		 && inputValue != 46 && inputValue != 64 && inputValue != 95)){
            event.preventDefault();
        }
    }));
	
 
}};
})(jQuery); 



//jQuery(document).ready(function(){ //alert('REST');
//	
//	$('#occupier_first_name_c_id').on('keypress', (function(event) { alert('TEST');
//        var inputValue = event.charCode;
//        if(!(inputValue >= 65 && inputValue <= 90) && !(inputValue >= 97 && inputValue <= 122) && (inputValue != 32 && inputValue != 38 && inputValue != 0)){
//            event.preventDefault();
//        }
//    }));
//	$('.charField').on('keypress', (function(event) { alert('TEST');
//        var inputValue = event.charCode;
//        if(!(inputValue >= 65 && inputValue <= 90) && !(inputValue >= 97 && inputValue <= 122) && (inputValue != 32 && inputValue != 38 && inputValue != 0)){
//            event.preventDefault();
//        }
//    }));
//	$('.charNoField').on('keypress', (function(event) {
//        var inputValue = event.charCode;
//        if(!(inputValue >= 48 && inputValue <= 57) && !(inputValue >= 65 && inputValue <= 90) &&!(inputValue >= 97 && inputValue <= 122)){
//            event.preventDefault();
//        }
//    }));
//
//	$('.NoField').on('keypress', (function(event) {
//        var inputValue = event.charCode;
//        if(!(inputValue >= 48 && inputValue <= 57)){
//            event.preventDefault();
//        }
//    }));
//	$('.emailField').on('keypress', (function(event) {
//        var inputValue = event.charCode;
//        if(!(inputValue >= 48 && inputValue <= 57) && !(inputValue >= 65 && inputValue <= 90) && !(inputValue >= 97 && inputValue <= 122) && (inputValue != 45
//		 && inputValue != 46 && inputValue != 64 && inputValue != 95)){
//            event.preventDefault();
//        }
//    }));
//
//});