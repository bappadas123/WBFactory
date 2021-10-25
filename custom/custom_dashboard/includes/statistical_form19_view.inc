<?php
function statistical_form19_view($form, &$form_state,$formid ,$referenceid, $factoryid){

	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'notice_form') . '/js/myfunction.js');
	
    $form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_id 	    = encryption_decryption_fun('decrypt', $factoryid);

	if(empty($formid) || $formid == ''){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the previous tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form19/default/'.$form_id.'/'.$factory_type_id.'/'.$applicationid) ;
	}

	$get_all_data 		= get_dangerous_occurence_details($form_id,$reference_id,$factory_id);
	$get_occurence_data = get_occurence_data($form_id);

 	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
			  <div class="col-lg-12 col-md-12 col-sm-12">
			  <table class="table table-bordered custom-table-view"> <tr>
   								<th width="40%">Parameters</th>
   								<th>Inputs</th>
								</tr>';

	$output .='<tr><td colspan="2" class="sub-title">A. Factory Information</td></tr>
				<tr><td>(i) Name of the factory</td><td>'.$get_all_data[0]->factory_name.'</td></tr>
				<tr><td>(ii) Nature of the Industry</td><td>'.$get_all_data[0]->industry_nature.'</td></tr>
				<tr><td>(iii) Registration No.</td><td>'.$get_all_data[0]->registration_number.'</td></tr>
				<tr><td>(iv) Registration Date</td><td>'.$get_all_data[0]->registration_date.'</td></tr>
				<tr><td>(v) Licence No.</td><td>'.$get_all_data[0]->licence_number.'</td></tr>
				<tr><td>(vi) Licence Date</td><td>'.$get_all_data[0]->licence_date.'</td></tr>
				<tr><td>(vii) Date and hour of dangerous occurence</td><td>'.$get_all_data[0]->date_occurrence.' at '.$get_all_data[0]->time_occurrence.'</td></tr>
				<tr><td>(viii) Full account of dangerous occurence</td><td>'.$get_all_data[0]->full_account.'</td></tr>
				<tr><td>(ix) Branch or department where the dangerous occurence occured</td><td>'.$get_all_data[0]->branch_name.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">B. Name of person who saw the dangerous occurence and can give important evidence</td></tr>';
				
			$i = 0;
			while($i < count($get_occurence_data))
			{ $slno = $i+1;
	$output .='
				<tr><td>('.$slno.') Name of person</td><td>'.$get_occurence_data[$i]->persons_name.'</td></tr>';
				$i++;			 
			}			
				
	$output .= '</table></div></div></div>';
	
 }
 