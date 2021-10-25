<?php
function statistical_form20_view($form, &$form_state,$formid ,$referenceid, $factoryid){ 

	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'notice_form') . '/js/myfunction.js');
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_id 	    = encryption_decryption_fun('decrypt', $factoryid);

	$get_all_data 		= get_notice_poisoning_data($form_id,$reference_id,$factory_id); 
	$get_patient_data   = get_notice_poisoning_patient_data($form_id);

	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address         = get_notice_full_address('fa_form20_notice_poisoning','sub-table',$get_all_data[0]->factory_id,$getdata_factory_address);

	$getdata_occpier_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$occpier_address         = get_notice_full_address('fa_form20_notice_poisoning','sub-table',$get_all_data[0]->factory_id,$getdata_occpier_address);

 	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
			   <div class="col-lg-12 col-md-12 col-sm-12">
			   <table class="table table-bordered custom-table-view"> <tr>
   								<th width="40%">Parameters</th>
   								<th>Inputs</th>
								</tr>';

	$output .='<tr><td colspan="2" class="sub-title">A. Factory Information</td></tr>
				<tr><td>(i) Name of the factory</td><td>'.$get_all_data[0]->factory_name.'</td></tr>
				<tr><td>(ii) Address of the factory</td><td>'.$factory_address.'<br> '.$get_all_data[0]->addrline.'</td></tr>
				<tr><td>(iii) Nature of the Industry</td><td>'.$get_all_data[0]->industry_nature.'</td></tr>';
	
	$output .='<tr><td colspan="2" class="sub-title">B. Occupier Information</td></tr>
				<tr><td>(iv) Occupier Name</td><td>'.$get_all_data[0]->name_occupier.'</td></tr>
				<tr><td>(v) Address of Occupier</td><td>'.$occpier_address.'<br> '.$get_all_data[0]->addrline.'</td></tr>
				<tr><td colspan="2" class="sub-title">C. Patient Details Information</td></tr>';

			$i = 0;
			while($i < count($get_patient_data))
			{ 
	$output .='
				<tr><td>(i) Name and Works Number of Patient</td><td>'.$get_patient_data[$i]->patient_name.' ('.$get_patient_data[$i]->patient_works_no.')</td></tr>
				<tr><td>(ii) Address of Patient</td><td>'.$get_patient_data[$i]->patient_address.'</td></tr>
				<tr><td>(iii) Sex and Age</td><td>'.$get_patient_data[$i]->patient_gender.' ('.$get_patient_data[$i]->patient_age.' years)</td></tr>
				<tr><td>(iv) Precise occupation of Patient</td><td>'.$get_patient_data[$i]->patient_occupation.'</td></tr>
				<tr><td>(v) Nature of Poisoning or Disease</td><td>'.$get_patient_data[$i]->patient_disease.'</td></tr>
				<tr><td>(vii) Has the case been reported to the Certifying Surgeon</td><td>'.$get_patient_data[$i]->patient_reported.'</td></tr>
				<tr><td colspan="2" class="sub-title">&nbsp;</td></tr>';
				
				$i++;			 
			}			
				
	$output .= '</table></div></div></div>';
	
 }
