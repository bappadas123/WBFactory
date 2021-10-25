<?php
function form20_preview($form, &$form_state,$formid ,$referenceid, $factorytypeid, $serviceid){ 

	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;

	  //PREVIOUS TAB FILL REDIRECTION
	  $get_previous_tab_data = db_query("SELECT count(*) FROM {fa_form20_patient_details} where notice_poisoning_id = '$form_id'")->fetchObject()->count;
	 
	if($form_id == 0 && $reference_id == 0 && $factory_id == 0){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form20/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	} else if($get_previous_tab_data == 0) {
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Patient Details Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form20/patient-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	}
	//PREVIOUS TAB FILL REDIRECTION

	$get_all_data 		= get_notice_poisoning_data($form_id,$reference_id,$factory_typeid,$service_id); 
	$get_patient_data   = get_notice_poisoning_patient_data($form_id);

	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address         = get_notice_full_address('fa_form20_notice_poisoning','sub-table',$get_all_data[0]->factory_id,$getdata_factory_address);

	$getdata_occpier_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$occpier_address         = get_notice_full_address('fa_form20_notice_poisoning','sub-table',$get_all_data[0]->factory_id,$getdata_occpier_address);

 	$output .='<div class="row"><div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12">
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
				
	$output .= '</table></div></div>';
	
	$form = array();
	
	$form['application_documents'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Application Preview'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
		'#markup' 			=> t($output),
	);
	$form['formid_hidden'] 		= array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $formid
	);	
	$form['referenceid_hidden'] = array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $referenceid
	);	
	  	$form['factorytypeid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $factorytypeid
		);
			
		$form['serviceid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $serviceid
		);
	$form['application_documents']['output'] = array(
		'#markup' 			=> t($output),
	);
	$form['application_documents']['finalAgree'] 	= array(
		 '#prefix' 		=> '<div class="col-md-12 col-xs-12">',	
		 '#suffix' 		=> '</div></div>',
		 '#type' 		=> 'checkbox',
		 '#title' 		=> ' I hereby declare that the particulars given above are true the best of my knowledge and belief.',
		 '#attributes'	=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
		 '#required' 	=> TRUE,
	);
	$form['application_documents_end']['submit'] = array (
		'#type' 			=> 'submit',
		'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		'#value' 		=> 'Save'										  
    );
	$form['application_documents_end']['back_link'] = array(
		'#markup' => l(t('Back'), 'applicant/form20/patient-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array(
			'html' => TRUE,
			'attributes' => array(
				'class' => array('btn btn-outline-dark pull-left')
			)
		))
	);	
		
	return $form;
 }
 
 	function form20_preview_submit($form, &$form_state){
		
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid 						= $user->uid;
		$val   						= $form_state['values'];

		$formid 	      = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid      = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid        = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
			
		$queryapp 		 =	db_update('fa_form20_notice_poisoning');
		$queryapp		 ->	fields(array('notice_status'=> 'In'));
		$queryapp		 ->	condition('id',$formid,'=');
		$queryapp		 ->	condition('reference_number',$referenceid,'=');
		$queryapp		 ->	condition('factory_typeid',$factorytypeid,'=');
		$queryapp		 ->	condition('service_id',$serviceid,'=');
		$queryapp		 ->	execute();
			
			drupal_goto('applicant/form20-upload/'.$val['formid_hidden'].'/'.$val['referenceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['serviceid_hidden']);

		$form_state['rebuild'] = true;
	} 