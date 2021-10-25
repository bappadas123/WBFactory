<?php
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
  function form20_patient_details($form, &$form_state, $formid ,$referenceid, $factorytypeid, $serviceid){
	  
	  global $user;
	  $uid 						= $user->uid;
	  $form = array();
	  
	  $form_id 	 	= encryption_decryption_fun('decrypt', $formid);
	  $reference_id = encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id; die;

	  //PREVIOUS TAB FILL REDIRECTION
	  $get_previous_tab_data = db_query("SELECT count(*) FROM {fa_form20_notice_poisoning} where id = '$form_id' AND reference_number ='$reference_id' AND  factory_typeid ='$factory_typeid' AND name_occupier !=''")->fetchObject()->count;
	 
	if($form_id == 0 && $reference_id == 0 && $factory_id == 0){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form20/default/'.$formid.'/'.$referenceid.'/'.$factoryid) ;
	} else if($get_previous_tab_data == 0) {
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Occupier Address Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form20/occupier-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	}
	//PREVIOUS TAB FILL REDIRECTION

		$get_all_data = get_notice_poisoning_patient_data($form_id);
		//print_r($get_all_data); 
	  
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

	 // Enter Patient Details //
	 
	 $form['notice_poisioning_patient'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Details of Patient'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE, // Added
     );
	$form['notice_poisioning_patient']['patient_name'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('Name of the Patient'),
		'#type' 			=> 'textfield',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_name,
	);
	$form['notice_poisioning_patient']['patient_age'] = array(
		'#prefix' 			=> '<div class="col-md-1 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('Age'),
		'#type' 			=> 'textfield',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_age,
	);
	
	$option = array( "Male" => "Male", "Female" => "Female");
	$form['notice_poisioning_patient']['patient_gender'] = array(
		'#prefix'		 	=> '<div class="col-md-2 col-xs-12">',
		'#suffix' 			=> '</div>',
		'#title' 			=> t('Sex'),
		'#options'			=> $option,
		'#type' 			=> 'radios',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_gender,
	);
	$form['notice_poisioning_patient']['patient_occupation'] = array(
		'#prefix' 			=> '<div class="col-md-3 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('Precise Occupation of Patient'),
		'#type' 			=> 'textfield',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_occupation,
	);
	$form['notice_poisioning_patient']['patient_works_no'] = array(
		'#prefix' 			=> '<div class="col-md-2 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('Works No. of Patient'),
		'#type' 			=> 'textfield',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_works_no,
	);
	$form['notice_poisioning_patient']['patient_address'] = array(
		'#prefix' 			=> '<div class="col-md-12 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('Patient Address'),
		'#type' 			=> 'textarea',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_address,
	);
	$form['notice_poisioning_patient']['patient_disease'] = array(
		'#prefix' 			=> '<div class="col-md-7 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('Nature of Poisoning or Disease from which Patient is suffering'),
		'#type' 			=> 'textfield',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_disease,
	);
	$option_2 = array( "Yes" => "Yes", "No" => "No");
	$form['notice_poisioning_patient']['patient_reported'] = array(
		'#prefix' 			=> '<div class="col-md-5 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div></div>',
		'#title' 			=> t('Has the case been reported to certifying Surgeon ?'),
		//'#required' 		=> TRUE,
		'#options'			=> $option_2,
		'#type' 			=> 'radios',
		//'#value' 			=> $get_all_data[0]->patient_reported,
	);

	$form['notice_poisioning_patient']['add_patients'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
		'#suffix' 			=> '</div></div>',
		'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
		'#type' 			=> 'submit',
		'#value' 			=> t("+ Add Patient's details"),
	);	
		
	$form['notice_poisioning_patient']['view_patients'] = array(
		'#prefix'			=> '<div class="row"><div id="view_patients_details_id"><div class="col-md-12">',
		'#suffix' 		    => '</div></div></div>',
		'#type' 			=> 'markup',
		'#markup' 			=> view_patient_details($form_id,$reference_id,$factory_typeid,$service_id),
	);				
	
		// Enter Patient Details //
		if(!empty($get_all_data))
		{
			$form['notice_poisioning_patient_end']['submit'] = array (
				'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save'
			);
		}
	
	$form['notice_poisioning_patient_end']['back_link'] = array(
		'#markup' => l(t('Back'), 'applicant/form20/occupier-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array(
			'html' => TRUE,
			'attributes' => array(
				'class' => array('btn btn-outline-dark pull-left')
			)
		))
	);		

	  return $form;
  }
	
 	function form20_patient_details_submit($form, &$form_state){
		
		//echo '<pre>'; print_r($form_state); die();
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid 						= $user->uid;
		$val   						= $form_state['values'];
		
		//print_r($val);die;
		$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid  = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid        = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	
	if($val['op'] == "+ Add Patient's details")
	{
		$patient_details = array(
			'notice_poisoning_id' => $formid,
			'patient_name' 		  => $val['patient_name'],
			'patient_works_no'    => $val['patient_works_no'],
			'patient_age'         => $val['patient_age'],
			'patient_gender'      => $val['patient_gender'],
			'patient_address'     => $val['patient_address'],
			'patient_occupation'  => $val['patient_occupation'],
			'patient_disease'     => $val['patient_disease'],
			'patient_reported'	  => $val['patient_reported'],
			'created_date' 		  => date('Y-m-d H:i:s'),
		);
		$patient_id = db_insert('fa_form20_patient_details')->fields($patient_details)->execute();
	}
	if($val['op'] == 'Save')
	{
		drupal_goto('applicant/form20/preview/'.$val['formid_hidden'].'/'.$val['referenceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['serviceid_hidden']);
	} 
		$form_state['rebuild'] = true;
	} 
	
function view_patient_details($form_id,$reference_id,$factorytype_id,$service_id){ //echo 'A-'.$form_id.' B-'.$reference_id.' C-'.$factory_id; die;
	$get_all_data 			= array();
	$type					= '';
	$details				= '';

	$get_all_data 			= get_notice_poisoning_patient_data($form_id);
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	$chunks 		= array_chunk($get_all_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Patient Details'),
						array('data'=> 'Occupation Details'),
						array('data'=> 'Address'),
						array('data'=> 'Nature of Poisoning'),
						array('data'=> 'Action'),	
					);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $patient_details){ 
			$Wcounter++;

			$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/form20/del-patient-details/'.encryption_decryption_fun('encrypt', $patient_details->id).'/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$service_id),array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));

     $patient_details_view    = 'Name:-'.$patient_details->patient_name.'<br/>Sex:-'.$patient_details->patient_gender.'<br/>Age:-'.$patient_details->patient_age;
	 $occupation_details_view = 'Occupation:-'.$patient_details->patient_occupation.'<br/>Works No:-'.$patient_details->patient_works_no;
	 $case_reported           = ($patient_details->patient_reported == 'Yes') ? "<br/>(Case has been reported to certifying Surgeon)" : "<br/>(Case has not been reported to certifying Surgeon)" ;
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$patient_details_view ,'class' => array('')),
								array('data' =>$occupation_details_view,'class' => array('')),
								array('data' =>$patient_details->patient_address ,'class' => array('')),
								array('data' =>$patient_details->patient_disease.$case_reported,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								);
				} 
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_patients_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '(1). All Patients List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
}

function del_patient_details($id,$form_id,$reference_id,$factorytype_id,$service_id){ //echo 'A-'.$id.' B-'.$form_id.' C-'.$reference_id.' D-'.$factorytype_id.' E-'.$service_id; //die;
	
	//drupal_add_library('system', 'drupal.ajax');
	
	$final_id         = trim(encryption_decryption_fun('decrypt', $id));
	$formid 	      = encryption_decryption_fun('decrypt', $form_id);
	$referenceid      = encryption_decryption_fun('decrypt', $reference_id);
	$factorytypeid    = encryption_decryption_fun('decrypt', $factorytype_id);
	$serviceid 	      = encryption_decryption_fun('decrypt', $service_id);
	//echo 'A-'.$final_id.' B-'.$formid.' C-'.$referenceid.' D-'.$factorytypeid.' E-'.$serviceid; die;
		
		if ($final_id != 0) {
			$query = db_delete('fa_form20_patient_details');
			$query->condition('id', $final_id,'=');
			$query->condition('notice_poisoning_id', $formid,'=');

			$query->execute();
		}
		drupal_goto('applicant/form20/patient-details/'.$form_id.'/'.$reference_id.'/'.$factorytype_id.'/'.$service_id);
		//drupal_goto('applicant/form20/patient-details/'.encryption_decryption_fun('encrypt',$formid).'/'.encryption_decryption_fun('encrypt',$referenceid).'/'.encryption_decryption_fun('encrypt',$factoryid));//.'#view_patients_details_id'

		 	/*$commands = array();
			$commands[] = ajax_command_replace('#view_patients_details_id', "<div id ='view_patients_details_id'><div class='col-md-12 col-xs-12'>".view_patient_details($formid,$referenceid,$factoryid).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);*/
}