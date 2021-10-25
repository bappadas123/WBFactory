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
				autoclose: true,
			});jQuery( ".datepicker_retify" ).datepicker({
				changeMonth: true,
				changeYear: true,
				format: 'dd-mm-yyyy',
                autoclose: true,
                endDate: '+0d'
			});
			jQuery( ".datepicker_min" ).datepicker({
				changeMonth: true,
				changeYear: true,
				format: 'yyyy-mm-dd',
				maxDate: "+5D"  
			});
			jQuery( ".datepicker" ).datepicker({
				changeMonth: true,
				changeYear: true,
				format: 'yyyy-mm-dd', 
			});
			jQuery(".range_dt").change(function(){
				var criteria_id = jQuery("#range_dates option:selected").html();
   				jQuery('.criteria_rate').val(criteria_id);
				var SelectedValue = jQuery('.testClass').val();
				//alert(SelectedValue);
	
			});
		
			/*jQuery('#textBox2').change(function () {
        		var SelectedValue = jQuery('.testClass').val();
				alert(SelectedValue);
			});*/
			
			
	
	//////////////////////////////////////Change in name of factory from//////////////////////////////
		//$(".date_change_x").click(function(){
			$(".range_dt").change(function(){
			
			//var selectedText = $("#textBox2").val();
			//var selectedText = $('input:textbox').val()
			//var selectedText = jQuery('input[name=hidden_value]').val();
			var selectedText = jQuery("#range_dates option:selected").html();
			//alert(selectedText.indexOf("st"));
			
			 if(selectedText.indexOf("st") != "-1" || selectedText.indexOf("nd") != "-1" || selectedText.indexOf("rd") != "-1" ||selectedText.indexOf("th") != "-1"){
				//alert('one');
				var res = selectedText.split(" TO ");				
				var start_date 	=  res[0];
				var s_date =  start_date.replace(/(st|nd|rd|th)/,'');
				var end_date 	= res[1];
				var e_date =  end_date.replace(/(st|nd|rd|th)/,'');
				
				var sdate = Date.parse(s_date);
				var edate = Date.parse(e_date);
				jQuery('.dd').datepicker({
				beforeShowDay: function (date) {
					if (date.valueOf() >= sdate && date.valueOf() <= edate ) { 
							return (date.valueOf() >= sdate && date.valueOf() <= edate );		
							}
						else {  
						return false;
							}
						},
						autoclose: true,
						format: 'yyyy-mm-dd',						
					});
				
				}
			
			else if(selectedText.length == 4){
					//alert('two');
					 var res = selectedText.split(" TO ");
					 var start_date 	= res[0];
 					 var end_date 	= res[0];	
					//alert(start_date);
					 var sdate = Date.parse(new Date(start_date, 0, 1));
				     var edate = Date.parse(new Date(end_date, 11, 31));
					 
					jQuery('.dd').datepicker({
					beforeShowDay: function (date) {
					if (date.valueOf() >= sdate && date.valueOf() <= edate ) { 
							return (date.valueOf() >= sdate && date.valueOf() <= edate );		
							}
						else {  
						return false;
							}
							
						},
						autoclose: true,
						format: 'yyyy-mm-dd',						
					});
					
					} 
					
				else if(selectedText.indexOf("st") == -1 || selectedText.indexOf("nd") == -1 || selectedText.indexOf("rd") == -1 ||selectedText.indexOf("th") == -1){ 		                        // alert('three');
						 var res = selectedText.split(" TO ");	
						 var start_date 	=  res[0];
						// var s_date =  start_date.replace(/(st|nd|rd|th)/,'');
						 var end_date 	= res[1];
						// var e_date =  end_date.replace(/(st|nd|rd|th)/,'');
						
						 var sdate = Date.parse(new Date(start_date, 0, 1));
						 var edate = Date.parse(new Date(end_date, 11, 31));
		
						 jQuery('.dd').datepicker({
						beforeShowDay: function (date) {
							if (date.valueOf() >= sdate && date.valueOf() <= edate ) { 
									return (date.valueOf() >= sdate && date.valueOf() <= edate );		
									}
								else {  
								return false;
									}
								},
								autoclose: true,
								format: 'yyyy-mm-dd',						
							});
						}	
			
			  });
			//////////////////////////////////////Change in name of factory from//////////////////////////////
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
				//alert('hi');
				//jQuery("#loading").hide();
			}
	 });
}

<!--------------- Inspector Verify Data In SELECT ALL ---------------------------------->

jQuery(function() {
    // add multiple select / deselect functionality
    jQuery("#selectall_inspector").click(function() {
        jQuery('.inspector_verify_check').prop('checked', this.checked);
    });
    // if all checkbox are selected, then check the select all checkbox
    // and viceversa
    jQuery(".inspector_verify_check").click(function() {
        if (jQuery(".inspector_verify_check").length == jQuery(".inspector_verify_check:checked").length) {
            jQuery("#selectall_inspector").prop("checked", "checked");
        } else {
            jQuery("#selectall_inspector").removeAttr("checked");
        }
    });
});

jQuery(document).ready(function() {
    $('#selectall_inspector').click(function() {
        var ids = $('.inspector_verify_check').map(function() {
            return $(this).attr('id');
        }).get().join();
        jQuery("#inspector_verify").val(ids); //
    });
});

<!--------------- Inspector Verify Data ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".inspector_verify_check").click(function() {
        var inspector_fieldIdt = jQuery("#inspector_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#inspector_verify").val(inspector_fieldIdt);
        }

        var inspector_verify = jQuery("#inspector_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#inspector_verify").val('');
            var fact_inspec_field_name_arr = inspector_verify.split(',');
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#inspector_verify").val(fieldIdt);
                    var t = jQuery("#inspector_verify").val();
                    if (t == ',') {
                        jQuery("#inspector_verify").val(null);
                    }
                }
            }
        }
    });
});

<!--------------- Inspector Verify Document ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".inspector_doc_verify_check").click(function() { //alert('hill');                      
        var inspector_fieldIdt = jQuery("#inspector_doc_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#inspector_doc_verify").val(inspector_fieldIdt);
        }

        var inspector_doc_verify = jQuery("#inspector_doc_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#inspector_doc_verify").val('');
            var fact_inspec_field_name_arr = inspector_doc_verify.split(',');
            //alert('GGG'+fact_inspec_field_name_arr);
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {
                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#inspector_doc_verify").val(fieldIdt);
                    var t = jQuery("#inspector_doc_verify").val();
                    if (t == ',') {
                        jQuery("#inspector_doc_verify").val(null);
                    }
                }
            }
        }
    });
});








<!--------------- Deputychief Verify Data In SELECT ALL ---------------------------------->

jQuery(function() {
    // add multiple select / deselect functionality
    jQuery("#selectall_deputychief").click(function() {
        jQuery('.deputychief_verify_check').prop('checked', this.checked);
    });
    // if all checkbox are selected, then check the select all checkbox
    // and viceversa
    jQuery(".deputychief_verify_check").click(function() {
        if (jQuery(".deputychief_verify_check").length == jQuery(".deputychief_verify_check:checked").length) {
            jQuery("#selectall_deputychief").prop("checked", "checked");
        } else {
            jQuery("#selectall_deputychief").removeAttr("checked");
        }
    });
});

jQuery(document).ready(function() {
    jQuery('#selectall_deputychief').click(function() {
        var ids = jQuery('.deputychief_verify_check').map(function() {
            return jQuery(this).attr('id');
        }).get().join();
        jQuery("#deputychief_verify").val(ids); //
    });
});

<!--------------- Deputychief Verify Data ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".deputychief_verify_check").click(function() {
        var inspector_fieldIdt = jQuery("#deputychief_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#deputychief_verify").val(inspector_fieldIdt);
        }

        var deputychief_verify = jQuery("#deputychief_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#deputychief_verify").val('');
            var fact_inspec_field_name_arr = deputychief_verify.split(',');
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#deputychief_verify").val(fieldIdt);
                    var t = jQuery("#deputychief_verify").val();
                    if (t == ',') {
                        jQuery("#deputychief_verify").val(null);
                    }
                }
            }
        }
    });
});







<!--------------- Deputychief Verify Document ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".deputychief_doc_verify_check").click(function() { //alert('hill');                      
        var inspector_fieldIdt = jQuery("#deputychief_doc_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#deputychief_doc_verify").val(inspector_fieldIdt);
        }

        var deputychief_doc_verify = jQuery("#deputychief_doc_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#deputychief_doc_verify").val('');
            var fact_inspec_field_name_arr = deputychief_doc_verify.split(',');
            //alert('GGG'+fact_inspec_field_name_arr);
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {
                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#deputychief_doc_verify").val(fieldIdt);
                    var t = jQuery("#deputychief_doc_verify").val();
                    if (t == ',') {
                        jQuery("#deputychief_doc_verify").val(null);
                    }
                }
            }
        }
    });
});



<!--------------- Inspector Chemical Verify Data In SELECT ALL ---------------------------------->

jQuery(function() {
    // add multiple select / deselect functionality
    jQuery("#selectall_inspectorchemical").click(function() {
        jQuery('.inspectorchemical_verify_check').prop('checked', this.checked);
    });
    // if all checkbox are selected, then check the select all checkbox
    // and viceversa
    jQuery(".inspectorchemical_verify_check").click(function() {
        if (jQuery(".inspectorchemical_verify_check").length == jQuery(".inspectorchemical_verify_check:checked").length) {
            jQuery("#selectall_inspectorchemical").prop("checked", "checked");
        } else {
            jQuery("#selectall_inspectorchemical").removeAttr("checked");
        }
    });
});

jQuery(document).ready(function() {
    $('#selectall_inspectorchemical').click(function() {
        var ids = $('.inspectorchemical_verify_check').map(function() {
            return $(this).attr('id');
        }).get().join();
        jQuery("#inspectorchemical_verify").val(ids); //
    });
});

<!--------------- Inspector Chemical Verify Data ---------------------------------->
jQuery(document).ready(function() {
    jQuery(".inspectorchemical_verify_check").click(function() {
        var inspector_fieldIdt = jQuery("#inspectorchemical_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#inspectorchemical_verify").val(inspector_fieldIdt);
        }

        var inspectorchemical_verify = jQuery("#inspectorchemical_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#inspectorchemical_verify").val('');
            var fact_inspec_field_name_arr = inspectorchemical_verify.split(',');
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#inspectorchemical_verify").val(fieldIdt);
                    var t = jQuery("#inspectorchemical_verify").val();
                    if (t == ',') {
                        jQuery("#inspectorchemical_verify").val(null);
                    }
                }
            }
        }
    });
});

<!--------------- Inspector Chemical Verify Document ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".inspectorchemical_doc_verify_check").click(function() { //alert('hill');                      
        var inspector_fieldIdt = jQuery("#inspectorchemical_doc_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#inspectorchemical_doc_verify").val(inspector_fieldIdt);
        }

        var inspectorchemical_doc_verify = jQuery("#inspectorchemical_doc_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#inspectorchemical_doc_verify").val('');
            var fact_inspec_field_name_arr = inspectorchemical_doc_verify.split(',');
            //alert('GGG'+fact_inspec_field_name_arr);
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {
                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#inspectorchemical_doc_verify").val(fieldIdt);
                    var t = jQuery("#inspectorchemical_doc_verify").val();
                    if (t == ',') {
                        jQuery("#inspectorchemical_doc_verify").val(null);
                    }
                }
            }
        }
    });
});

<!--------------- Deputychief Chemical Verify Data In SELECT ALL ---------------------------------->

jQuery(function() {
    // add multiple select / deselect functionality
    jQuery("#selectall_deputychiefchemical").click(function() {
        jQuery('.deputychiefchemical_verify_check').prop('checked', this.checked);
    });
    // if all checkbox are selected, then check the select all checkbox
    // and viceversa
    jQuery(".deputychiefchemical_verify_check").click(function() {
        if (jQuery(".deputychiefchemical_verify_check").length == jQuery(".deputychiefchemical_verify_check:checked").length) {
            jQuery("#selectall_deputychiefchemical").prop("checked", "checked");
        } else {
            jQuery("#selectall_deputychiefchemical").removeAttr("checked");
        }
    });
});

jQuery(document).ready(function() {
    $('#selectall_deputychiefchemical').click(function() {
        var ids = $('.deputychiefchemical_verify_check').map(function() {
            return $(this).attr('id');
        }).get().join();
        jQuery("#deputychiefchemical_verify").val(ids); //
    });
});

<!--------------- Deputychief Chemical Verify Data ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".deputychiefchemical_verify_check").click(function() {
        var inspector_fieldIdt = jQuery("#deputychiefchemical_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#deputychiefchemical_verify").val(inspector_fieldIdt);
        }

        var deputychiefchemical_verify = jQuery("#deputychiefchemical_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#deputychiefchemical_verify").val('');
            var fact_inspec_field_name_arr = deputychiefchemical_verify.split(',');
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#deputychiefchemical_verify").val(fieldIdt);
                    var t = jQuery("#deputychiefchemical_verify").val();
                    if (t == ',') {
                        jQuery("#deputychiefchemical_verify").val(null);
                    }
                }
            }
        }
    });
});

<!--------------- Deputychief Chemical Verify Document ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".deputychiefchemical_doc_verify_check").click(function() { //alert('hill');                      
        var inspector_fieldIdt = jQuery("#deputychiefchemical_doc_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#deputychiefchemical_doc_verify").val(inspector_fieldIdt);
        }

        var deputychiefchemical_doc_verify = jQuery("#deputychiefchemical_doc_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#deputychiefchemical_doc_verify").val('');
            var fact_inspec_field_name_arr = deputychiefchemical_doc_verify.split(',');
            //alert('GGG'+fact_inspec_field_name_arr);
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {
                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#deputychiefchemical_doc_verify").val(fieldIdt);
                    var t = jQuery("#deputychiefchemical_doc_verify").val();
                    if (t == ',') {
                        jQuery("#deputychiefchemical_doc_verify").val(null);
                    }
                }
            }
        }
    });
});



<!--------------- Jointchief Verify Data In SELECT ALL ---------------------------------->

jQuery(function() {
    // add multiple select / deselect functionality
    jQuery("#selectall_jointchief").click(function() {
        jQuery('.jointchief_verify_check').prop('checked', this.checked);
    });
    // if all checkbox are selected, then check the select all checkbox
    // and viceversa
    jQuery(".jointchief_verify_check").click(function() {
        if (jQuery(".jointchief_verify_check").length == jQuery(".jointchief_verify_check:checked").length) {
            jQuery("#selectall_jointchief").prop("checked", "checked");
        } else {
            jQuery("#selectall_jointchief").removeAttr("checked");
        }
    });
});

jQuery(document).ready(function() {
    $('#selectall_jointchief').click(function() {
        var ids = $('.jointchief_verify_check').map(function() {
            return $(this).attr('id');
        }).get().join();
        jQuery("#jointchief_verify").val(ids); //
    });
});

<!--------------- Jointchief Verify Data ---------------------------------->
jQuery(document).ready(function() {
    jQuery(".jointchief_verify_check").click(function() {
        var inspector_fieldIdt = jQuery("#jointchief_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#jointchief_verify").val(inspector_fieldIdt);
        }

        var jointchief_verify = jQuery("#jointchief_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#jointchief_verify").val('');
            var fact_inspec_field_name_arr = jointchief_verify.split(',');
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#jointchief_verify").val(fieldIdt);
                    var t = jQuery("#jointchief_verify").val();
                    if (t == ',') {
                        jQuery("#jointchief_verify").val(null);
                    }
                }
            }
        }
    });
});

<!--------------- Jointchief Verify Document ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".jointchief_doc_verify_check").click(function() { //alert('hill');                      
        var inspector_fieldIdt = jQuery("#jointchief_doc_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#jointchief_doc_verify").val(inspector_fieldIdt);
        }

        var jointchief_doc_verify = jQuery("#jointchief_doc_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#jointchief_doc_verify").val('');
            var fact_inspec_field_name_arr = jointchief_doc_verify.split(',');
            //alert('GGG'+fact_inspec_field_name_arr);
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {
                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#jointchief_doc_verify").val(fieldIdt);
                    var t = jQuery("#jointchief_doc_verify").val();
                    if (t == ',') {
                        jQuery("#jointchief_doc_verify").val(null);
                    }
                }
            }
        }
    });
});

<!--------------- Jointchief Chemical Verify Data In SELECT ALL ---------------------------------->

jQuery(function() {
    // add multiple select / deselect functionality
    jQuery("#selectall_jointchiefchemical").click(function() {
        jQuery('.jointchiefchemical_verify_check').prop('checked', this.checked);
    });
    // if all checkbox are selected, then check the select all checkbox
    // and viceversa
    jQuery(".jointchiefchemical_verify_check").click(function() {
        if (jQuery(".jointchiefchemical_verify_check").length == jQuery(".jointchiefchemical_verify_check:checked").length) {
            jQuery("#selectall_jointchiefchemical").prop("checked", "checked");
        } else {
            jQuery("#selectall_jointchiefchemical").removeAttr("checked");
        }
    });
});

jQuery(document).ready(function() {
    $('#selectall_jointchiefchemical').click(function() {
        var ids = $('.jointchiefchemical_verify_check').map(function() {
            return $(this).attr('id');
        }).get().join();
        jQuery("#jointchiefchemical_verify").val(ids); //
    });
});

<!--------------- Jointchief Chemical Verify Data ---------------------------------->
jQuery(document).ready(function() {
    jQuery(".jointchiefchemical_verify_check").click(function() {
        var inspector_fieldIdt = jQuery("#jointchiefchemical_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#jointchiefchemical_verify").val(inspector_fieldIdt);
        }

        var jointchiefchemical_verify = jQuery("#jointchiefchemical_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#jointchiefchemical_verify").val('');
            var fact_inspec_field_name_arr = jointchiefchemical_verify.split(',');
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#jointchiefchemical_verify").val(fieldIdt);
                    var t = jQuery("#jointchiefchemical_verify").val();
                    if (t == ',') {
                        jQuery("#jointchiefchemical_verify").val(null);
                    }
                }
            }
        }
    });
});

<!--------------- Jointchief Chemical Verify Document ---------------------------------->

jQuery(document).ready(function() {
    jQuery(".jointchiefchemical_doc_verify_check").click(function() { //alert('hill');                      
        var inspector_fieldIdt = jQuery("#jointchiefchemical_doc_verify").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (inspector_fieldIdt == '') {
                var inspector_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+inspector_fieldIdt);  
            } else {
                var inspector_fieldIdt = inspector_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+inspector_fieldIdt);  
            }
            jQuery("#jointchiefchemical_doc_verify").val(inspector_fieldIdt);
        }

        var jointchiefchemical_doc_verify = jQuery("#jointchiefchemical_doc_verify").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#jointchiefchemical_doc_verify").val('');
            var fact_inspec_field_name_arr = jointchiefchemical_doc_verify.split(',');
            //alert('GGG'+fact_inspec_field_name_arr);
            for (var i = 0; i < fact_inspec_field_name_arr.length; i++) {
                if (fact_inspec_field_name_arr[i] != fieldId && fact_inspec_field_name_arr[i] != '') {
                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_inspec_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#jointchiefchemical_doc_verify").val(fieldIdt);
                    var t = jQuery("#jointchiefchemical_doc_verify").val();
                    if (t == ',') {
                        jQuery("#jointchiefchemical_doc_verify").val(null);
                    }
                }
            }
        }
    });
});

jQuery(document).ready(function(){	
jQuery(".show2").click(function(e){
	alert('Enter date between calender period.');	
		var id 			= jQuery(this).attr('id');
		var start_date 	= jQuery("#start"+id).val();
		var end_date 	= jQuery("#end"+id).val();
		//alert(start_date);
		//alert(end_date);
		    startDate1 = new Date(start_date.replace('-',',').replace('-',','));
			endDate1 = new Date(end_date.replace('-',',').replace('-',','));
			jQuery('.daterange').datepicker({
    		beforeShowDay: function (date) {
			
			  if (date.valueOf() >= startDate1.valueOf() && date.valueOf() <= endDate1.valueOf() ) { 
				return (date.valueOf() >= startDate1.valueOf() && date.valueOf() <= endDate1.valueOf() );			
				}
				else {  
				return false;
				}
			},
			autoclose: true,
			format: 'yyyy-mm-dd',		
		});     
    });
});

jQuery(document).ready(function(){	
jQuery(".hp2").click(function(e){
	alert('Enter date between calender period.');	
		var id 			= jQuery(this).attr('id');
		var start_date 	= jQuery("#hpstart"+id).val();
		var end_date 	= jQuery("#hpend"+id).val();
		    startDate1 = new Date(start_date.replace('-',',').replace('-',','));
			endDate1 = new Date(end_date.replace('-',',').replace('-',','));
			
			jQuery('.hprange').datepicker({
		
    		beforeShowDay: function (date) {
			
			  if (date.valueOf() >= startDate1.valueOf() && date.valueOf() <= endDate1.valueOf() ) { 
				return (date.valueOf() >= startDate1.valueOf() && date.valueOf() <= endDate1.valueOf() );			
				}
				else {  
				return false;
				}
			},
			
			autoclose: true,
			format: 'yyyy-mm-dd',
			
		});
    });
});

jQuery(document).ready(function(){	
	jQuery(".dates").click(function(e){
		alert('Enter date between service period.');	
		var id 			= jQuery(this).attr('id');
		var start_date 	= jQuery("#id_fromdate").val();
		var end_date 	= jQuery("#id_todate").val();
		startDate = new Date(start_date.replace('-',',').replace('-',','));
			endDate = new Date(end_date.replace('-',',').replace('-',','));
			
			jQuery('.range').datepicker({
		
    		beforeShowDay: function (date) {
			
			  if (date.valueOf() >= startDate.valueOf() && date.valueOf() <= endDate.valueOf() ) { 
				return (date.valueOf() >= startDate.valueOf() && date.valueOf() <= endDate.valueOf() );		
				}
				else {  
				return false;
				}
			},
			
			autoclose: true,
			format: 'yyyy-mm-dd',
			
		});
    });
});

////////SELECT ALL REGISTRATION///////////////////
jQuery(document).ready(function(){
	jQuery('#select_all').click(function () { 
		var ids = jQuery('.inspector_verify_check').map(function() {
			return jQuery(this).attr('id');
		}).get().join();
		jQuery(".inspector_verify").val(ids);//
	});
});
jQuery(function () {
	jQuery("#select_all").click(function () {
		jQuery('.inspector_verify_check').prop('checked', this.checked);
	});
	jQuery(".inspector_verify_check").click(function () { 
		if (jQuery(".inspector_verify_check").length == jQuery(".inspector_verify_check:checked").length) { 
			jQuery("#select_all").prop("checked", "checked");
		} else {
			jQuery("#select_all").removeAttr("checked");
		}
	});
});


jQuery(document).ready(function(){
	jQuery('#select_all').click(function () { 
		var ids = jQuery('.deputychief_verify_check').map(function() {
			return jQuery(this).attr('id');
		}).get().join();
		jQuery(".deputychief_verify").val(ids);//
	});
});
jQuery(function () {
	jQuery("#select_all").click(function () {
		jQuery('.deputychief_verify_check').prop('checked', this.checked);
	});
	jQuery(".deputychief_verify_check").click(function () { 
		if (jQuery(".deputychief_verify_check").length == jQuery(".deputychief_verify_check:checked").length) { 
			jQuery("#select_all").prop("checked", "checked");
		} else {
			jQuery("#select_all").removeAttr("checked");
		}
	});
});


jQuery(document).ready(function(){
	jQuery('#select_all').click(function () { 
		var ids = jQuery('.jointchief_verify_check').map(function() {
			return jQuery(this).attr('id');
		}).get().join();
		jQuery(".jointchief_verify").val(ids);//
	});
});
jQuery(function () {
	jQuery("#select_all").click(function () {
		jQuery('.jointchief_verify_check').prop('checked', this.checked);
	});
	jQuery(".jointchief_verify_check").click(function () { 
		if (jQuery(".jointchief_verify_check").length == jQuery(".jointchief_verify_check:checked").length) { 
			jQuery("#select_all").prop("checked", "checked");
		} else {
			jQuery("#select_all").removeAttr("checked");
		}
	});
});

jQuery(document).ready(function(){
	jQuery('#select_all').click(function () { 
		var ids = jQuery('.chief_verify_check').map(function() {
			return jQuery(this).attr('id');
		}).get().join();
		jQuery(".chief_verify").val(ids);//
	});
});
jQuery(function () {
	jQuery("#select_all").click(function () {
		jQuery('.chief_verify_check').prop('checked', this.checked);
	});
	jQuery(".chief_verify_check").click(function () { 
		if (jQuery(".chief_verify_check").length == jQuery(".chief_verify_check:checked").length) { 
			jQuery("#select_all").prop("checked", "checked");
		} else {
			jQuery("#select_all").removeAttr("checked");
		}
	});
});

////////////////////////////End select all//////////////////////////////
jQuery(document).ready(function(){
	jQuery('.multidate').datepicker({
	  multidate: true,
		format: 'dd-mm-yyyy'
	});
});

jQuery(document).ready(function(){
	jQuery('.input-daterange input').each(function() {
    jQuery(this).datepicker('clearDates');
	});
  /*  jQuery(".range_dt").change(function(){
		
        var value = jQuery(this).children("option:selected").val();
        alert("You - " + value);
    });*/
});

jQuery(function () {
	jQuery(document).on('keyup','#number1',function( e ) {
		if (this.value.length == this.maxLength) { 
		  jQuery('#number2').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number2',function( e ) {	
		if (this.value.length == this.maxLength) {
		  jQuery('#number3').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number3',function( e ) {	
		if (this.value.length == 0) {
		  jQuery('#number2').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number2',function( e ) {	
		if (this.value.length == 0) {
		  jQuery('#number1').get(0).focus();
		}
	});
});

jQuery(function () {
	jQuery(document).on('keyup','#number4',function( e ) {	
		if (this.value.length == this.maxLength) {
		  $('#number5').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number5',function( e ) {	
		if (this.value.length == this.maxLength) {
		  $('#number6').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number6',function( e ) {	
		if (this.value.length == 0) {
		  $('#number5').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number5',function( e ) {	
		if (this.value.length == 0) {
		  $('#number4').get(0).focus();
		}
	});
});

jQuery(function () {
	jQuery(document).on('keyup','#number7',function( e ) {	
		if (this.value.length == this.maxLength) {
		  $('#number8').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number8',function( e ) {	
		if (this.value.length == this.maxLength) {
		  $('#number9').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number9',function( e ) {	
		if (this.value.length == 0) {
		  $('#number8').get(0).focus();
		}
	});
	jQuery(document).on('keyup','#number8',function( e ) {	
		if (this.value.length == 0) {
		  $('#number7').get(0).focus();
		}
	});
});
///////////////////////////////RENEWAL//////////////////////////////////

jQuery(document).ready(function(){
	jQuery('#select_all').click(function () { 
		var ids = jQuery('.caf_verify_check').map(function() {
			return jQuery(this).attr('id');
		}).get().join();
		jQuery(".caf_verify_check").val(ids);//
	});
});
jQuery(function () {
	jQuery("#select_all").click(function () {
		jQuery('.caf_verify_check').prop('checked', this.checked);
	});
	jQuery(".caf_verify_check").click(function () { 
		if (jQuery(".caf_verify_check").length == jQuery(".caf_verify_check:checked").length) { 
			jQuery("#select_all").prop("checked", "checked");
		} else {
			jQuery("#select_all").removeAttr("checked");
		}
	});
});
<!--------------- CAF Verify Data ---------------------------------->
jQuery(document).ready(function() {
    jQuery(".caf_verify_check").click(function() {
        var caf_fieldIdt = jQuery("#caf_verify_check").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
            //alert('MMM'+factory_fieldId);
            if (caf_fieldIdt == '') {
                var caf_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+caf_fieldIdt);  
            } else {
                var caf_fieldIdt = caf_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+caf_fieldIdt);  
            }
            jQuery("#caf_verify_check").val(caf_fieldIdt);
        }

        var caf_verify = jQuery("#caf_verify_check").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#caf_verify_check").val('');
            var fact_caf_field_name_arr = caf_verify.split(',');
            for (var i = 0; i < fact_caf_field_name_arr.length; i++) {
                if (fact_caf_field_name_arr[i] != fieldId && fact_caf_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_caf_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#caf_verify_check").val(fieldIdt);
                    var t = jQuery("#caf_verify_check").val();
                    if (t == ',') {
                        jQuery("#caf_verify_check").val(null);
                    }
                }
            }
        }
    });
});
//////////////////////////////TAMAL///////////
function popIt(url) {
	var leftPos = screen.width - 720;
	ref = window.open(url,"thePop","menubar=1,resizable=1,scrollbars=1,status=1,height=400,width=710,left="+leftPos+",top=0")
	ref.focus();
}

function killPopUp() {
	if(!ref.closed) {
	ref.close();
	}
}
function seeDoc(d){
	var newUrl =d.getAttribute("data-id");
	var objectEl = document.getElementById('doc');
	objectEl.outerHTML = objectEl.outerHTML.replace(/data="(.+?)"/, 'data="' + newUrl + '"');
	
}

//jQuery(document).ready(function(){
//	jQuery('.adhaar-card').on('keypress change blur', function () { 
//	 jQuery(this).val(function (index, value) { 
//		if(value.length > 15)
//		{
//			return alert('Number should be 12 digit');
//		}
//		return value.replace(/[^a-z0-9]+/gi, '').replace(/(.{4})/g, '$1 '); 
//	  }); 
//	}); 
//	 
//	jQuery('.adhaar-card').on('copy cut paste', function () { 
//	  setTimeout(function () { 
//		jQuery('.adhaar-card').trigger("change"); 
//	  }); 
//	});
//});


jQuery(document).ready(function(){
	jQuery('.adhaar-card').keyup(function () {
    var cctlength = jQuery(this).val().length; // get character length

    switch (cctlength) {
        case 4:
            var cctVal = jQuery(this).val();
            var cctNewVal = cctVal + '-';
            jQuery(this).val(cctNewVal);
            break;
        case 9:
            var cctVal = jQuery(this).val();
            var cctNewVal = cctVal + '-';
            jQuery(this).val(cctNewVal);
            break;
        case 14:
            var cctVal = jQuery(this).val();
            var cctNewVal = cctVal;
            jQuery(this).val(cctNewVal);
            break;
        default:
            break;
    }
	});
});

