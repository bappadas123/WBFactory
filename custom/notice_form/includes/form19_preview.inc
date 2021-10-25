<?php
function form19_preview($form, &$form_state,$formid ,$referenceid, $factorytypeid, $serviceid){

	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
    $form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
    $service_id 	= encryption_decryption_fun('decrypt', $serviceid);//echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;
	 //PREVIOUS TAB FILL REDIRECTION
	 if($form_id == 0 && $reference_id == 0 && $factory_id == 0){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Occurrence Information tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form19/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	}
	 //PREVIOUS TAB FILL REDIRECTION

	$get_all_data 		= get_dangerous_occurence_details($form_id,$reference_id,$factory_typeid,$service_id);
	$get_occurence_data = get_occurence_data($form_id);

 	$output .='<div class="row"><div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12">
			  <table class="table table-bordered custom-table-view"> <tr>
   								<th width="40%">Parameters</th>
   								<th>Inputs</th>
								</tr>';

	$output .='<tr><td colspan="2" class="sub-title">A. Factory Information</td></tr>
				<tr><td>(i) Name of the factory</td><td>'.$get_all_data[0]->factory_name.'</td></tr>
				<tr><td>(ii) Nature of the Industry</td><td>'.$get_all_data[0]->industry_nature.'</td></tr>
				<tr><td>(iii) Registration No.</td><td>'.$get_all_data[0]->registration_number.'</td></tr>
				<tr><td>(iv) Registration Date</td><td>'.date('d-m-Y',strtotime($get_all_data[0]->registration_date)).'</td></tr>
				<tr><td>(v) Licence No.</td><td>'.$get_all_data[0]->licence_number.'</td></tr>
				<tr><td>(vi) Licence Date</td><td>'.date('d-m-Y',strtotime($get_all_data[0]->licence_date)).'</td></tr>
				<tr><td>(vii) Classification No.</td><td>'.$get_all_data[0]->classification_no.'</td></tr>
				<tr><td>(viii) Date and hour of dangerous occurrence</td><td>'.date('d-m-Y',strtotime($get_all_data[0]->date_occurrence)).' at '.$get_all_data[0]->time_occurrence.'</td></tr>
				<tr><td>(ix) Full account of dangerous occurrence</td><td>'.$get_all_data[0]->full_account.'</td></tr>
				<tr><td>(x) Branch or department where the dangerous occurrence occured</td><td>'.$get_all_data[0]->branch_name.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">B. Name of person who saw the dangerous occurrence and can give important evidence</td></tr>';
				
			$i = 0;
			while($i < count($get_occurence_data))
			{ $slno = $i+1;
	$output .='
				<tr><td>('.$slno.') Name of person</td><td>'.$get_occurence_data[$i]->persons_name.'</td></tr>';
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
		'#markup' => l(t('Back'), 'applicant/form19/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array(
			'html' => TRUE,
			'attributes' => array(
				'class' => array('btn btn-outline-dark pull-left')
			)
		))
	);	
	return $form;
 }
 
 function form19_preview_submit($form, &$form_state){
		
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid          = $user->uid;
		$val   		  = $form_state['values'];

		$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid  = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid    = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
			
		$queryapp 	  =	db_update('fa_form19_dangerous_occurrence');
		$queryapp	 ->	fields(array('notice_status'=> 'In'));
		$queryapp	 ->	condition('id',$formid,'=');
		$queryapp	 ->	condition('reference_number',$referenceid,'=');
		$queryapp	 ->	condition('factory_typeid',$factoryid,'=');
		$queryapp	 ->	condition('service_id',$serviceid,'=');
		$queryapp	 ->	execute();
			
		drupal_goto('applicant/form19-upload/'.$val['formid_hidden'].'/'.$val['referenceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['serviceid_hidden']);

		$form_state['rebuild'] = true;
	} 
		//drupal_goto('applicant/form19-upload/'.encryption_decryption_fun('encrypt',$dangerous_occurrence_ID).'/'.encryption_decryption_fun('encrypt',$referencenumber).'/'.encryption_decryption_fun('encrypt',$factoryid));
