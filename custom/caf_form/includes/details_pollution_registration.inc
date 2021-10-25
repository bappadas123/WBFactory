<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function details_pollution_registration($form, &$form_state, $serviceid, $factory_type_id,$applicationid,$linknumber,$flagmapp) {	
	global $base_root, $base_path, $user;
  
	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$flagmapp) ;
	 }else{
		 	$get_fa_cafa = get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$wbpcb_category_name 		= $get_fa_cafa['wbpcb_category_name'];
			$wbpcb_reference_no 		= $get_fa_cafa['wbpcb_reference_no'];
			$wbpcb_ref_date 			= $get_fa_cafa['wbpcb_ref_date'];
			$wbpcb_intimation_letter    = $get_fa_cafa['wbpcb_intimation_letter'];
		
		 }
	 
	  
	
	$service_id 	= encryption_decryption_fun('decrypt',$serviceid);
	$factory_typeid = encryption_decryption_fun('decrypt',$factory_type_id);
	//////////////////////////////occupier Type////////////////////////
	
	
	//////////////////////////////end occupier Type////////////////////////
	
	
	
    $form = array();
	$form['#attributes'] = array('enctype' => "multipart/form-data");
	$form['serviceid_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> $serviceid,
		);
	$form['factorytypeid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_type_id
			 
		);
	$form['reference_no_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number)
			 
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	

	$form['director_factory_statring_info'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('Tenure Factory'),
			'#collapsible' 	=> TRUE,
			'#collapsed'	=> FALSE, 
		);
			
		
	$form['director_factory_statring_info']['markup_start'] = array(
	     	 '#prefix' =>'<div class="row">'	
			);
		
	$form['director_factory_statring_info']['factory_pollution_type'] 	= array(
				'#prefix' 			=> '<div id ="pollution_type_id"><div class="col-md-6 col-xs-12">',
				'#suffix' 			=> '</div></div>',
				'#title' 			=> t('Categories of wbpcb'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class'=>array('form-control')),
				'#options' 			=>  get_category_wbpcb(),
				'#required'			 => TRUE,
				'#default_value'	=> $wbpcb_category_name,
					
				'#ajax'				=>  array(
												'effect' 		=> 'fade',			
												'callback'		=> 'get_pollution_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
											),
										),
			
			);	
		
		$form['director_factory_statring_info']['doc_file'] = array(
			   '#prefix' 		=> '<div id="edit-doc-file-ajax-wrapper">',
			   '#suffix' 		=> '</div>'	,
			   
	);
	  $form['director_factory_statring_info']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_no_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
	  $form['director_factory_statring_info']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_date_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
	 
	$value_pollution_type  =   isset($form_state['values']['factory_pollution_type']) ? $form_state['values']['factory_pollution_type'] : $wbpcb_category_name;
	if($value_pollution_type == 4){
		
	$form['director_factory_statring_info']['doc_file'] = array(
					'#type' 				 => 'managed_file',
					'#title'				 => 'Upload FORM V :-',
					'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					'#upload_location' 		 => 'public://upload/pollution_doc/',
					'#process' 				 => array('import_my_file_element_process'),
					'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
					'#prefix' 				 => '<div id="edit-doc-file-ajax-wrapper"><div class="col-md-6 col-xs-12">',
			  		'#suffix' 				 => '</div></div>',
					'#required' 			 => TRUE
			);
	 $form['director_factory_statring_info']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_no_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
	  $form['director_factory_statring_info']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_date_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
		}
	 if($value_pollution_type == '1' || $value_pollution_type == '2' || $value_pollution_type == '3'){
		$form['director_factory_statring_info']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_no_approval_id"><div class="col-md-6 col-xs-12">Reference number of approval of arrangments',
				'#suffix' 			=> '</div></div>',
				'#attributes' 		=> array('class'=>array('form-control')),
				'#type' 			=> 'textfield',
				'#required'			=> TRUE,
				'#description'		=> t('<font color="#FF0000">(N.B.:-If any,made fo disposal of trade waste and effluents. )</font>'),
			);	
		$form['director_factory_statring_info']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_date_approval_id"><div class="col-md-6 col-xs-12">',
				'#suffix' 			=> '</div></div>',
				'#title' 		=> t('Date of approval of arrangments'),
			
				'#attributes' 		=> array('class'=>array('datepicker_cls form-control')),
				'#type' 			=> 'textfield',
				'#required'			=> TRUE,
				'#description'		=> t('<font color="#FF0000">(N.B.:-If any,made fo disposal of trade waste and effluents. )</font>'),
			);
			$form['director_factory_statring_info']['doc_file'] = array(
			   '#prefix' 		=> '<div id="edit-doc-file-ajax-wrapper">',
			   '#suffix' 		=> '</div>'	
	  );
	 }	
			
	$form['director_factory_statring_info']['markup_start1'] = array(
	     	 '#suffix' =>'</div>'	
			);
		
	$form['back_link']	 = array(
					
				'#markup' 		=> l(t('Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('button ')))),
			);
					
		$form['submit'] = array (
		  '#prefix' => '</div></div><div align="right">',  
		  '#suffix' => '</div>',
		  '#type' => 'submit',
		  '#value' => 'Save & Continue'
	); 

            return $form; 
        
         }
		 


function get_pollution_ajax_load($form, $form_state){
	$commands 	= array();	
	//$form['director_factory_statring_info']['date_approval_arrangments']['#id'] 			= 'date_approval_id';
	//$form['director_factory_statring_info']['date_approval_arrangments']['#attributes'] 	= array('class'=>array('datepicker_cls form-control'),);
			
	$commands[] = ajax_command_replace('#reference_no_approval_id', drupal_render($form['director_factory_statring_info']['reference_no_approval_arrangments']));
	$commands[] = ajax_command_replace('#reference_date_approval_id', drupal_render($form['director_factory_statring_info']['date_approval_arrangments']));
$commands[] = ajax_command_replace('#edit-doc-file-ajax-wrapper', drupal_render($form['director_factory_statring_info']['doc_file']));	
		
	return array('#type' => 'ajax', '#commands' => $commands);	
}
function details_pollution_registration_submit($form, &$form_state){
	 global $user;
	 $val   					    		= $form_state['values'];
	 $uid 			    					= $user->uid;
	 $service_id							= encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	 $factory_type_id						= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	 $application_id 						= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	 $application_reference_no				= encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	 $reference_no_approval_arrangments		= $val['reference_no_approval_arrangments'];
	 $date_approval_arrangments				= $val['date_approval_arrangments'];
	   
	 $factory_pollution_type				= $val['factory_pollution_type'];
	 if($factory_pollution_type== 4){
		$docmunt_white_category 	= file_load($val['doc_file']);
		if($docmunt_white_category != "" ){
			$signed_form->status = FILE_STATUS_PERMANENT;
			file_save($docmunt_white_category);
			$fid			=	$signed_form->fid;
		}
  } 
  
  $addition_info = array(
			'wbpcb_intimation_letter' 	=> $fid,
			'wbpcb_reference_no' 		=> $reference_no_approval_arrangments,
			'wbpcb_ref_date' 			=> $date_approval_arrangments,
			'wbpcb_category_name'		=> $factory_pollution_type 
							
		);
		//print_r($addition_info);die();
	$queryabc 		= 	db_update('fa_cafa');
    $queryabc		->	fields($addition_info);
    $queryabc		->	condition('id', $application_id, '=');
    $queryabc		->	execute();
	
	
	
	 
	
}


?>