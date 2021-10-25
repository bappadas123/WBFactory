// JavaScript Document

/////Amendment/////
jQuery(document).ready(function () {
    jQuery('#checkBtn').click(function() {
      checked = jQuery("input[type=checkbox]:checked").length;
      if(!checked) {
        alert("You must check at least one checkbox.");
        return false;
      }
    });
    
	$('body').on('focus',".calender_ajax", function(){
        $(this).datepicker({format: 'yyyy-mm-dd',autoclose: true,maxDate : 0});
    });
	
});


jQuery(document).ready(function(){
	jQuery('#list_check_all').click(function () {
		var ids = jQuery('.list_check_data').map(function() {
			
			return jQuery(this).attr('id');
		}).get().join();
		jQuery("#list_check_data").val(ids);//
	});
});
jQuery(function () {
	jQuery("#list_check_all").click(function () {
		jQuery('.list_check_data').prop('checked', this.checked);
	});
	jQuery(".list_check_data").click(function () { 
		if (jQuery(".list_check_data").length == jQuery(".list_check_data:checked").length) { 
			jQuery("#list_check_all").prop("checked", "checked");
		} else {
			jQuery("#list_check_all").removeAttr("checked");
		}
	});
});
jQuery(document).ready(function() {
    jQuery(".list_check_data").click(function() {
        var caf_fieldIdt = jQuery("#list_check_data").val();
        if (jQuery(this).is(':checked')) {
            var factory_fieldId = jQuery(this).attr('id');
           // alert('MMM'+factory_fieldId);
            if (caf_fieldIdt == '') {
                var caf_fieldIdt = factory_fieldId;
                //alert('IIIFFF'+caf_fieldIdt);  
            } else {
                var caf_fieldIdt = caf_fieldIdt + ',' + factory_fieldId;
                //alert('EEELLLL'+caf_fieldIdt);  
            }
            jQuery("#list_check_data").val(caf_fieldIdt);
        }

        var caf_verify = jQuery("#list_check_data").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#list_check_data").val('');
            var fact_caf_field_name_arr = caf_verify.split(',');
            for (var i = 0; i < fact_caf_field_name_arr.length; i++) {
                if (fact_caf_field_name_arr[i] != fieldId && fact_caf_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_caf_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#list_check_data").val(fieldIdt);
                    var t = jQuery("#list_check_data").val();
                    if (t == ',') {
                        jQuery("#list_check_data").val(null);
                    }
                }
            }
        }
    });
});

















	
jQuery(document).ready(function(){
	jQuery('#amend_select_all').click(function () {
		var ids = jQuery('.amendment_year_check').map(function() {
			
			return jQuery(this).attr('id');
		}).get().join();
		jQuery("#amendment_year_check").val(ids);//
	});
});
jQuery(function () {
	jQuery("#amend_select_all").click(function () {
		jQuery('.amendment_year_check').prop('checked', this.checked);
	});
	jQuery(".amendment_year_check").click(function () { 
		if (jQuery(".amendment_year_check").length == jQuery(".amendment_year_check:checked").length) { 
			jQuery("#amend_select_all").prop("checked", "checked");
		} else {
			jQuery("#amend_select_all").removeAttr("checked");
		}
	});
});
jQuery(document).ready(function() {
    jQuery(".amendment_year_check").click(function() {
        var caf_fieldIdt = jQuery("#amendment_year_check").val();
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
            jQuery("#amendment_year_check").val(caf_fieldIdt);
        }

        var caf_verify = jQuery("#amendment_year_check").val();
        if (!jQuery(this).is(':checked')) {
            var fieldIdt = '';
            var fieldId = jQuery(this).attr('id');
            jQuery("#amendment_year_check").val('');
            var fact_caf_field_name_arr = caf_verify.split(',');
            for (var i = 0; i < fact_caf_field_name_arr.length; i++) {
                if (fact_caf_field_name_arr[i] != fieldId && fact_caf_field_name_arr[i] != '') {

                    //alert(fact_inspec_field_name_arr[i]+'--->'+fieldId);
                    var fieldIdt = fieldIdt + ',' + fact_caf_field_name_arr[i];
                    fieldIdt = fieldIdt.replace(',,', '');
                    jQuery("#amendment_year_check").val(fieldIdt);
                    var t = jQuery("#amendment_year_check").val();
                    if (t == ',') {
                        jQuery("#amendment_year_check").val(null);
                    }
                }
            }
        }
    });
});


jQuery(document).ready(function() {
    // add multiple select / deselect functionality
    jQuery("#selectall_inspector").click(function() {
        jQuery('.inspector_verify_check').prop('checked', this.checked);
    });
  
    jQuery(".inspector_verify_check").click(function() {
        if (jQuery(".inspector_verify_check").length == jQuery(".inspector_verify_check:checked").length) {
            jQuery("#selectall_inspector").prop("checked", "checked");
        } else {
            jQuery("#selectall_inspector").removeAttr("checked");
        }
    });
});

jQuery(document).ready(function() {
    jQuery('#selectall_inspector').click(function() {
        var ids = $('.inspector_verify_check').map(function() {
            return $(this).attr('id');
        }).get().join();
        jQuery("#inspector_verify").val(ids); //
    });
});


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










///////////////////////////////Other Funtions/////////////////////////////
function myFunction() {
 	document.getElementById("demo").style.color = "green";
  	var myWindow = window.open("", "MsgWindow", "toolbar=yes,scrollbars=yes,resizable=yes, top=500,left=500,width=400,height=300");
 	 myWindow.document.write("<p>This is 'MsgWindow'. I am 200px wide and 100px tall!</p>");
}

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
	var newUrl = d.getAttribute("data-id");
	var objectEl = document.getElementById('doc');
	objectEl.outerHTML = objectEl.outerHTML.replace(/data="(.+?)"/, 'data="' + newUrl + '"');
	
}



