<?php
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
  function form18_witness_details($form, &$form_state,$formid ,$referenceid, $factorytypeid, $serviceid){
	  
	  global $base_root,$base_path,$user;
	  $uid 						= $user->uid;
	  $form = array();
	  
	  $form_id 	 	= encryption_decryption_fun('decrypt', $formid);
	  $reference_id = encryption_decryption_fun('decrypt', $referenceid);
	  $factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid);//echo $form_id.''.$reference_id.''.$factory_typeid.''.$service_id;

	  //PREVIOUS TAB FILL REDIRECTION
	  $get_previous_tab_data = db_query("SELECT count(*) FROM {fa_form18_injured_person_details} where accident_case_id = '$form_id'")->fetchObject()->count;
	 
	if($form_id == 0 && $reference_id == 0 && $factory_id == 0){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form18/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	} else if($get_previous_tab_data == 0) {
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Injured Person Details Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form18/injured-person-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	}
	//PREVIOUS TAB FILL REDIRECTION

		$get_all_data = get_accident_witness_data($form_id);
	  
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

	 // Enter Witness Details //
	 
	 $form['notice_accident_witness'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Details of Witness'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE, // Added
     );
	$form['notice_accident_witness']['witness_name'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('Name of the Witness'),
		'#type' 			=> 'textfield',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_name,
	);
	$form['notice_accident_witness']['witness_address'] = array(
		'#prefix' 			=> '<div class="col-md-12 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div></div>',
		'#title' 			=> t("Witness's Address"),
		'#type' 			=> 'textarea',
		//'#required' 		=> TRUE,
		//'#value' 			=> $get_all_data[0]->patient_address,
	);

	$form['notice_accident_witness']['add_witness'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
		'#suffix' 			=> '</div></div>',
		'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
		'#type' 			=> 'submit',
		'#value' 			=> t("+ Add Witness's details"),
	);	
		
	$form['notice_accident_witness']['view_witness'] = array(
		'#prefix'			=> '<div class="row"><div id="view_witness_details_id"><div class="col-md-12">',
		'#suffix' 		    => '</div></div></div>',
		'#type' 			=> 'markup',
		'#markup' 			=> view_witness_details($form_id,$reference_id,$factorytype_id,$service_id),
	);				
	
		// Enter Witness Details //
		if(!empty($get_all_data))
		{
			$form['notice_accident_witness_end']['submit'] = array (
				'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save'
			);
		}
		$form['notice_accident_witness_end']['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/form18/injured-person-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array(
				'html' => TRUE,
				'attributes' => array(
					'class' => array('btn btn-outline-dark pull-left')
				)
			))
		);		

	  return $form;
  }
	
 function form18_witness_details_submit($form, &$form_state){
		
		//echo '<pre>'; print_r($form_state); die();
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid 						= $user->uid;
		$val   						= $form_state['values'];
		
		//print_r($val);die;
		$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid  = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid    = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	
	if($val['op'] == "+ Add Witness's details")
	{
		$witness_details = array(
			'accident_case_id' 	=> $formid,
			'witness_name' 		=> $val['witness_name'],
			'witness_address'   => $val['witness_address'],
		);
		
		//print_r($witness_details);die;
		$witness_id = db_insert('fa_form18_witness_details')->fields($witness_details)->execute();
	}
	if($val['op'] == 'Save')
	{
		drupal_goto('applicant/form18/preview/'.$val['formid_hidden'].'/'.$val['referenceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['serviceid_hidden']);
	} 
		$form_state['rebuild'] = true;
	} 
	
function view_witness_details($form_id,$reference_id,$factorytype_id,$service_id){ //echo 'A-'.$form_id.' B-'.$reference_id.' C-'.$factory_id; die;
	$get_all_data 			= array();
	$type					= '';
	$details				= '';

	$get_all_data 			= get_accident_witness_data($form_id);
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	$chunks 		= array_chunk($get_all_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Witness Name'),
						array('data'=> 'Address'),
						array('data'=> 'Action'),	
					);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $witness_details){ 
			$Wcounter++;

			$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/form18/del-witness-details/'.encryption_decryption_fun('encrypt', $witness_details->id).'/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$service_id),array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));

			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$witness_details->witness_name ,'class' => array('')),
								array('data' =>$witness_details->witness_address,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								);
				} 
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_witness_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => 'All Witness List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
}

function del_witness_details($id,$form_id,$reference_id,$factorytype_id,$service_id){ //echo 'A-'.$id.' B-'.$form_id.' C-'.$reference_id.' D-'.$factorytype_id.' E-'.$service_id; die;
	
	//drupal_add_library('system', 'drupal.ajax');
	
	 $final_id = trim(encryption_decryption_fun('decrypt', $id));
	 $formid 	  = encryption_decryption_fun('decrypt', $form_id);
	 $referenceid  = encryption_decryption_fun('decrypt', $reference_id);
	 $factorytypeid 	  = encryption_decryption_fun('decrypt', $factorytype_id);
	 $serviceid 	  = encryption_decryption_fun('decrypt', $service_id);
	
		if ($final_id != 0) {
			$query = db_delete('fa_form18_witness_details');
			$query->condition('id', $final_id,'=');
			$query->condition('accident_case_id', $formid,'=');
			$query->execute();
		}
		
		drupal_goto('applicant/form18/witness-details/'.$form_id.'/'.$reference_id.'/'.$factorytype_id.'/'.$service_id);//.'#view_patients_details_id'

		 	/*$commands = array();
			$commands[] = ajax_command_replace('#view_witness_details_id', "<div id ='view_witness_details_id'><div class='col-md-12 col-xs-12'>".view_witness_details($formid,$referenceid,$factorytypeid,$serviceid).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);*/
}