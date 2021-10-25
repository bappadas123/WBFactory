// JavaScript Document
(function ($) {
	Drupal.behaviors.project_store = {
		attach: function(context) {
		  $("#same_factory_addr").click(function(){
			  if($(this).is(':checked')){
				  //alert($("#state_name").val());
				 $("#pincode_autocomplete_off").val($("#pincode_autocomplete").val()); 
				 $("#state_name_off").val($("#state_name").val()); 
			  }else{
				 $("#pincode_autocomplete_off").val('');
				 $("#state_name_off").val(''); 
			  }
		  });
		  jQuery( ".datepicker_cls" ).datepicker({
      			changeMonth: true,
      			changeYear: true,
	  		 	format: 'yyyy-mm-dd',
   		 });
		 
	  }
	}
	
	
	
})(jQuery);


jQuery(document).ready(function() {
    jQuery( ".datepicker" ).datepicker({
      changeMonth: true,
      changeYear: true,
	   format: 'yyyy-mm-dd', 
    });
	

	

	
	/*jQuery('#factory_id').selectmenu({
        focus: function(ev, ui) {
            jQuery('#test_id').html(ui.item.value + ' was hovered');
        }
    });*/
	
	
	/*$("#factory_id > option").each(function() {
    alert(this.text + ' ---' + this.value);
	
	   // var $target = jQuery(e.target); 
	 
	// alert($target.attr("id")+'labani');
	 
});*/

jQuery("#factory_id").hover(function (e)
{

$("#factory_id option").each(function() {
   // alert(this.text + ' ' + this.value);
});

});
	
/*	jQuery("#factory_id").hover(function (e)
{
     var $target = jQuery(e.target); 
	 
	 //alert($target.attr("id")+'labani');
	 
     if($target.each(fu)){
         alert($target.attr("id")+'labani');//Will alert id if it has id attribute
         alert($target.text());//Will alert the text of the option
         alert($target.val());//Will alert the value of the option
     }
});
*/

  } );
  
   jQuery("#active_year").live("click", function(){
	var status								=   parseInt(1);
	var edit_base_url 						=   jQuery("input[type='hidden'][name='base_url']").val();
	var amenablity_date 					= 	jQuery('.amenablity_date').val(); 
	var many_year 							= 	jQuery('.many_year').val();
	var serviceid_hidden 					=   jQuery("input[type='hidden'][name='serviceid']").val();
	var factorytypeid_hidden 				=   jQuery("input[type='hidden'][name='factorytypeid']").val();
	var application_reference_no_hidden 	=   jQuery("input[type='hidden'][name='application_reference_no']").val();
	var applicationid_hidden 				=   jQuery("input[type='hidden'][name='applicationid']").val();
	var data 								=  'amenablity_date='+amenablity_date+'&many_year='+many_year+'&serviceid_hidden='+serviceid_hidden+'&factorytypeid_hidden='+factorytypeid_hidden+'&application_reference_no_hidden='+application_reference_no_hidden+'&applicationid_hidden='+applicationid_hidden;
	var data1 								=  'amenablity_date='+amenablity_date+'&many_year='+many_year+'&serviceid_hidden='+serviceid_hidden+'&factorytypeid_hidden='+factorytypeid_hidden+'&application_reference_no_hidden='+application_reference_no_hidden+'&applicationid_hidden='+applicationid_hidden;
		
	jQuery.ajax({
			type	:'POST',
			url		: edit_base_url+'applicant/create-validate-year',   
			data	: data,	
			dataType: 'json',
		async: true, 
		success	: function(data){
					//if(data!=''){
						//jQuery("#year_error_div").html("<font color='red'><strong>"+data+"</strong></font>").show();
						status = parseInt(2);
						//jQuery("#year_error_div").html("<font color='red'><strong>"+status+"</strong></font>").show();
			//	}
				if(status ==2){//alert('hii');
					test();
				}
		}
			
			
			//complete : function (data) {test();}
	 });
	  
	
   });
  


function test(){
  var edit_base_url 						=  jQuery("input[type='hidden'][name='base_url']").val();
	var amenablity_date 					= 	jQuery('.amenablity_date').val(); 
	var many_year 							= 	jQuery('.many_year').val();
	var serviceid_hidden 					=   jQuery("input[type='hidden'][name='serviceid']").val();
	var factorytypeid_hidden 				=   jQuery("input[type='hidden'][name='factorytypeid']").val();
	var application_reference_no_hidden 	=   jQuery("input[type='hidden'][name='application_reference_no']").val();
	var applicationid_hidden 				=   jQuery("input[type='hidden'][name='applicationid']").val();
	var data 								=  'amenablity_date='+amenablity_date+'&many_year='+many_year+'&serviceid_hidden='+serviceid_hidden+'&factorytypeid_hidden='+factorytypeid_hidden+'&application_reference_no_hidden='+application_reference_no_hidden+'&applicationid_hidden='+applicationid_hidden;
	
  return jQuery.ajax({
			type	:'POST',
			url		: edit_base_url+'applicant/fetch',   
			data	: data,	
			dataType: 'json',
				async: true,
		 	success	: function(data){
				
				var selectedDeviceModel = jQuery('#service_year_id');
       	         jQuery.each(data, function(index, item) {
					if(item == ''){
						item = 'select';
					}
                    selectedDeviceModel.append(
                        jQuery('<option/>', {
							
                            value: item,
                            text: item
                        })
                    );
                });	jQuery("#active_year").attr("disabled", "disabled");
				alert('hi');
				//jQuery("#loading").hide();
			}
	 });
}

<!--------------- Inspector Verify Data ---------------------------------->
jQuery(document).ready(function(){
  jQuery(".inspector_verify_check").click(function(){                        
            var inspector_fieldIdt = jQuery("#inspector_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#inspector_verify").val(inspector_fieldIdt);
            }    
			    
            var inspector_verify = jQuery("#inspector_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt             = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#inspector_verify").val('');
                var fact_inspec_field_name_arr         = inspector_verify.split(',');
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#inspector_verify").val(fieldIdt);
                        var t             = jQuery("#inspector_verify").val();
                        if(t==','){
                            jQuery("#inspector_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });
	
<!--------------- Inspector Verify Document ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".inspector_doc_verify_check").click(function(){  //alert('hill');                      
            var inspector_fieldIdt = jQuery("#inspector_doc_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#inspector_doc_verify").val(inspector_fieldIdt);
            }    
			    
            var inspector_doc_verify = jQuery("#inspector_doc_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt            = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#inspector_doc_verify").val('');
                var fact_inspec_field_name_arr         = inspector_doc_verify.split(',');
				//alert('GGG'+fact_inspec_field_name_arr);
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#inspector_doc_verify").val(fieldIdt);
                        var t             = jQuery("#inspector_doc_verify").val();
                        if(t==','){
                            jQuery("#inspector_doc_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });	
	
<!--------------- Deputychief Verify Data ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".deputychief_verify_check").click(function(){                        
            var inspector_fieldIdt = jQuery("#deputychief_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#deputychief_verify").val(inspector_fieldIdt);
            }    
			    
            var deputychief_verify = jQuery("#deputychief_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt             = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#deputychief_verify").val('');
                var fact_inspec_field_name_arr         = deputychief_verify.split(',');
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#deputychief_verify").val(fieldIdt);
                        var t             = jQuery("#deputychief_verify").val();
                        if(t==','){
                            jQuery("#deputychief_verify").val(null);
                        }
                    }
                 }
            }                
        });
    }); 
	
<!--------------- Deputychief Verify Document ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".deputychief_doc_verify_check").click(function(){  //alert('hill');                      
            var inspector_fieldIdt = jQuery("#deputychief_doc_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#deputychief_doc_verify").val(inspector_fieldIdt);
            }    
			    
            var deputychief_doc_verify = jQuery("#deputychief_doc_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt            = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#deputychief_doc_verify").val('');
                var fact_inspec_field_name_arr         = deputychief_doc_verify.split(',');
				//alert('GGG'+fact_inspec_field_name_arr);
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#deputychief_doc_verify").val(fieldIdt);
                        var t             = jQuery("#deputychief_doc_verify").val();
                        if(t==','){
                            jQuery("#deputychief_doc_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });	 

<!--------------- Inspector Chemical Verify Data ---------------------------------->
jQuery(document).ready(function(){
  jQuery(".inspectorchemical_verify_check").click(function(){                        
            var inspector_fieldIdt = jQuery("#inspectorchemical_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#inspectorchemical_verify").val(inspector_fieldIdt);
            }    
			    
            var inspectorchemical_verify = jQuery("#inspectorchemical_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt             = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#inspectorchemical_verify").val('');
                var fact_inspec_field_name_arr         = inspectorchemical_verify.split(',');
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#inspectorchemical_verify").val(fieldIdt);
                        var t             = jQuery("#inspectorchemical_verify").val();
                        if(t==','){
                            jQuery("#inspectorchemical_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });
	
<!--------------- Inspector Chemical Verify Document ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".inspectorchemical_doc_verify_check").click(function(){  //alert('hill');                      
            var inspector_fieldIdt = jQuery("#inspectorchemical_doc_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#inspectorchemical_doc_verify").val(inspector_fieldIdt);
            }    
			    
            var inspectorchemical_doc_verify = jQuery("#inspectorchemical_doc_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt            = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#inspectorchemical_doc_verify").val('');
                var fact_inspec_field_name_arr         = inspectorchemical_doc_verify.split(',');
				//alert('GGG'+fact_inspec_field_name_arr);
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#inspectorchemical_doc_verify").val(fieldIdt);
                        var t             = jQuery("#inspectorchemical_doc_verify").val();
                        if(t==','){
                            jQuery("#inspectorchemical_doc_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });	
	
<!--------------- Deputychief Chemical Verify Data ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".deputychiefchemical_verify_check").click(function(){                        
            var inspector_fieldIdt = jQuery("#deputychiefchemical_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#deputychiefchemical_verify").val(inspector_fieldIdt);
            }    
			    
            var deputychiefchemical_verify = jQuery("#deputychiefchemical_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt             = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#deputychiefchemical_verify").val('');
                var fact_inspec_field_name_arr         = deputychiefchemical_verify.split(',');
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#deputychiefchemical_verify").val(fieldIdt);
                        var t             = jQuery("#deputychiefchemical_verify").val();
                        if(t==','){
                            jQuery("#deputychiefchemical_verify").val(null);
                        }
                    }
                 }
            }                
        });
    }); 
	
<!--------------- Deputychief Chemical Verify Document ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".deputychiefchemical_doc_verify_check").click(function(){  //alert('hill');                      
            var inspector_fieldIdt = jQuery("#deputychiefchemical_doc_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#deputychiefchemical_doc_verify").val(inspector_fieldIdt);
            }    
			    
            var deputychiefchemical_doc_verify = jQuery("#deputychiefchemical_doc_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt            = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#deputychiefchemical_doc_verify").val('');
                var fact_inspec_field_name_arr         = deputychiefchemical_doc_verify.split(',');
				//alert('GGG'+fact_inspec_field_name_arr);
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#deputychiefchemical_doc_verify").val(fieldIdt);
                        var t             = jQuery("#deputychiefchemical_doc_verify").val();
                        if(t==','){
                            jQuery("#deputychiefchemical_doc_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });	 

<!--------------- Jointchief Verify Data ---------------------------------->
jQuery(document).ready(function(){
  jQuery(".jointchief_verify_check").click(function(){                        
            var inspector_fieldIdt = jQuery("#jointchief_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#jointchief_verify").val(inspector_fieldIdt);
            }    
			    
            var jointchief_verify = jQuery("#jointchief_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt             = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#jointchief_verify").val('');
                var fact_inspec_field_name_arr         = jointchief_verify.split(',');
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#jointchief_verify").val(fieldIdt);
                        var t             = jQuery("#jointchief_verify").val();
                        if(t==','){
                            jQuery("#jointchief_verify").val(null);
                        }
                    }
                 }
            }                
        });
    }); 
	
<!--------------- Jointchief Verify Document ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".jointchief_doc_verify_check").click(function(){  //alert('hill');                      
            var inspector_fieldIdt = jQuery("#jointchief_doc_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#jointchief_doc_verify").val(inspector_fieldIdt);
            }    
			    
            var jointchief_doc_verify = jQuery("#jointchief_doc_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt            = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#jointchief_doc_verify").val('');
                var fact_inspec_field_name_arr         = jointchief_doc_verify.split(',');
				//alert('GGG'+fact_inspec_field_name_arr);
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#jointchief_doc_verify").val(fieldIdt);
                        var t             = jQuery("#jointchief_doc_verify").val();
                        if(t==','){
                            jQuery("#jointchief_doc_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });	 

<!--------------- Chief Verify Data ---------------------------------->
jQuery(document).ready(function(){
  jQuery(".chief_verify_check").click(function(){                        
            var inspector_fieldIdt = jQuery("#chief_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#chief_verify").val(inspector_fieldIdt);
            }    
			    
            var chief_verify = jQuery("#chief_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt             = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#chief_verify").val('');
                var fact_inspec_field_name_arr         = chief_verify.split(',');
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#chief_verify").val(fieldIdt);
                        var t             = jQuery("#chief_verify").val();
                        if(t==','){
                            jQuery("#chief_verify").val(null);
                        }
                    }
                 }
            }                
        });
    }); 
	
<!--------------- Chief Verify Document ---------------------------------->

jQuery(document).ready(function(){
  jQuery(".chief_doc_verify_check").click(function(){  //alert('hill');                      
            var inspector_fieldIdt = jQuery("#chief_doc_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                if(inspector_fieldIdt == ''){
                    var inspector_fieldIdt     = factory_fieldId;
					//alert('IIIFFF'+inspector_fieldIdt);  
                }else {
                    var inspector_fieldIdt = inspector_fieldIdt+','+factory_fieldId;  
					//alert('EEELLLL'+inspector_fieldIdt);  
                }
                jQuery("#chief_doc_verify").val(inspector_fieldIdt);
            }    
			    
            var chief_doc_verify = jQuery("#chief_doc_verify").val();
            if (!jQuery(this).is(':checked')) {    
                var fieldIdt            = '';            
                var fieldId             = jQuery(this).attr('id');            
                jQuery("#chief_doc_verify").val('');
                var fact_inspec_field_name_arr         = chief_doc_verify.split(',');
				//alert('GGG'+fact_inspec_field_name_arr);
                for(var i=0;i<fact_inspec_field_name_arr.length;i++){                    
                    if(fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i]!=''){
						//alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                        var fieldIdt     = fieldIdt+','+fact_inspec_field_name_arr[i];
                        fieldIdt         = fieldIdt.replace(',,', '');
                        jQuery("#chief_doc_verify").val(fieldIdt);
                        var t             = jQuery("#chief_doc_verify").val();
                        if(t==','){
                            jQuery("#chief_doc_verify").val(null);
                        }
                    }
                 }
            }                
        });
    });
	
jQuery(document).ready(function(){	
	var sampleDate = jQuery('.daterange').datepicker({
		
    beforeShowDay: function (date) {
		var startDate1 = new Date(jQuery("#start").val().replace('-',',').replace('-',','));
		var endDate1 = new Date(jQuery("#end").val().replace('-',',').replace('-',','));
		
		//alert('--------'+startDate1+'---------'+endDate1);
		
		if (date.valueOf() < endDate1.valueOf() && date.valueOf() > startDate1.valueOf()) {
			return (date.valueOf() < endDate1.valueOf() && date.valueOf() > startDate1.valueOf());
			}else {
				return false;
			}
		},
    autoclose: true
	});
});

jQuery(document).ready(function(){	
	var sampleDate = jQuery('.hprange').datepicker({
		
    beforeShowDay: function (date) {
		var startDate2 = new Date(jQuery("#hpstart").val().replace('-',',').replace('-',','));
		var endDate2 = new Date(jQuery("#hpend").val().replace('-',',').replace('-',','));
		//alert('--------'+startDate2+'---------'+date.valueOf());
		if (date.valueOf() < endDate2.valueOf() && date.valueOf() > startDate2.valueOf()) {
			return (date.valueOf() < endDate2.valueOf() && date.valueOf() > startDate2.valueOf());
			}else {
				return false;
			}
		},
    autoclose: true
	});
});


/*jQuery(document).ready(function(){alert('hill'); 
  jQuery(".plan_section").click(function(){  alert('hill');                      
            var inspector_fieldIdt = jQuery("#inspector_doc_verify").val();                
            if (jQuery(this).is(':checked')) {                
                var factory_fieldId = jQuery(this).attr('id');
				//alert('MMM'+factory_fieldId);
                jQuery("#inspector_doc_verify").val(inspector_fieldIdt);
            }    
        });
    });*/	
	
	
jQuery(document).ready(function(){
    jQuery(".plan_section").keyup(function(){ alert('dfdf');
        jQuery(".plan_section").css("background-color", "pink");
    });
});
