jQuery(document).ready(function() { 




   jQuery('.datepicker_cls').live('focus',function(){
       
		 
		
		 alert('111');
		
		jQuery('#date_approval_id').datepicker(
         {
			dateFormat: "dd-mm-yy",
			changeMonth : true,
     		changeYear  : true,
            defaultDate: "+1w",
			
			beforeShow: function() {
            						
										
										
											
										jQuery(this).datepicker("option", "maxDate", 0); 
										
          						   }
            
         });
		 
	
	
	
  });
	
	
});