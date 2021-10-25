<?php
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
  function form18_accident_details($form, &$form_state, $formid ,$referenceid, $factorytypeid, $serviceid){
	  
	  global $base_root,$base_path,$user;
	  $uid 						= $user->uid;
	  $form = array();
	  
	    $form_id 	 	= encryption_decryption_fun('decrypt', $formid);
	    $reference_id   = encryption_decryption_fun('decrypt', $referenceid);
	    $factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid);
//echo $form_id.''.$reference_id.''.$factory_typeid.''.$service_id;
	 //PREVIOUS TAB FILL REDIRECTION
	 if($form_id == 0 && $reference_id == 0 && $factory_id == 0){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form18/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	}
	 //PREVIOUS TAB FILL REDIRECTION

	  $get_all_data = get_notice_accident_data($form_id,$reference_id,$factory_typeid,$service_id);

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

		$form['notice_accident_details'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Details of Accident'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		); 	

		$form['notice_accident_details']['accident_place'] 	= array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('(xiv). Exact place where the accident took place'),
			'#type' 			=> 'textfield',
			'#default_value'    => !empty($get_all_data[0]->accident_place) ? $get_all_data[0]->accident_place : '',
			'#required' 		=> TRUE,
		);
		$form['notice_accident_details']['accident_date'] 	= array(
			'#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('(xv).Date of accident'),
			'#type' 			=> 'textfield',
			'#default_value'    => !empty($get_all_data[0]->accident_date) ? trim(implode('-', array_reverse(explode('-',$get_all_data[0]->accident_date)))) : '',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
		);
		$form['notice_accident_details']['accident_shift'] 	= array(
			'#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('(xvi). Shift of accident'),
			'#type' 			=> 'textfield',
			'#default_value'    => !empty($get_all_data[0]->accident_shift) ? $get_all_data[0]->accident_shift : '',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class'=>array('form-control')),
		);
		$form['notice_accident_details']['accident_time'] 	= array(
			'#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('(xvii).Time of accident'),
			'#type' 			=> 'textfield',
			'#default_value'    => !empty($get_all_data[0]->accident_time) ? $get_all_data[0]->accident_time : '',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class'=>array('form-control')),
		);
		
		$option = array( "Yes" => "Yes", "No" => "No");
		$form['notice_accident_details']['is_machinery_accident'] = array(
			'#prefix'		 	=> '<div class="col-md-3 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(xviii). Accident caused by machinery?'),
			'#options'			=> $option,
			'#type' 			=> 'radios',
			//'#required' 		=> TRUE,
			'#default_value' 	=> !empty($get_all_data[0]->is_machinery_accident) ? $get_all_data[0]->is_machinery_accident : '',
			'#ajax' 			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',
									'callback' 		=> 'get_ajax_load',
									'progress' 		=> array(
									'type' 			=> 'throbber',
									'message' 		=> t('loading')
								)
       			 )
		);
			
		$value_is_machinery_accident = (isset($form_state['values']['is_machinery_accident'])) ? $form_state['values']['is_machinery_accident'] : $get_all_data[0]->is_machinery_accident;
		
		if($value_is_machinery_accident == 'Yes')
		{
			$option_machine = array( "Yes" => "Yes", "No" => "No");
			$form['notice_accident_details']['is_moved_by_power'] = array(
				'#prefix'		 	=> '<div id="is_moved_by_power_id"><div class="col-md-4 col-xs-12">',
				'#suffix' 			=> '</div></div>',
				'#title' 			=> t('(a). It was moved by mechanical power at that time?'),
				'#options'			=> $option_machine,
				'#type' 			=> 'radios',
				'#default_value' 	=> !empty($get_all_data[0]->is_moved_by_power) ? $get_all_data[0]->is_moved_by_power : '',
			);
			$form['notice_accident_details']['machine_name'] 	= array(
				'#prefix' 			=> '<div id="machine_name_id"><div class="col-md-5 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div></div>',
				'#title'			=>	t('(b). Name of the machine and the part causing the accident'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($get_all_data[0]->machine_name) ? $get_all_data[0]->machine_name : '',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class'=>array('form-control')),
			);
			
		} else {
			$form['notice_accident_details']['is_moved_by_power'] 	= array(
				'#prefix' 			=> '<div id="is_moved_by_power_id">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_accident_details']['machine_name'] 	= array(
				'#prefix' 			=> '<div id="machine_name_id">',
				'#suffix' 			=> '</div>',
			);
		}

		$form['notice_accident_details']['accident_description'] 	= array(
			'#prefix' 			=> '<div class="col-md-12 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div></div>',
			'#title'			=>	t('(xix). State how the accident occured'),
			'#type' 			=> 'textarea',
			'#default_value'    => !empty($get_all_data[0]->accident_description) ? $get_all_data[0]->accident_description : '',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class'=>array('form-control'),'style'=>'width:980px;'),
		);

		$form['notice_accident_details_end']['submit'] = array (
			'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save'
		);
		
		$form['notice_accident_details_end']['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/form18/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);	
		
	  return $form;
  }

	function get_ajax_load($form, $form_state)
	{
		$commands[] = ajax_command_replace('#machine_name_id', drupal_render($form['notice_accident_details']['machine_name']));
		$commands[] = ajax_command_replace('#is_moved_by_power_id', drupal_render($form['notice_accident_details']['is_moved_by_power']));
		
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	} 
  
 	function form18_accident_details_submit($form, &$form_state){
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid          = $user->uid;
		$val          = $form_state['values'];
	//print_r($val); die;
		
		$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid  = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid    = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
		
		$notice_accident_case_details = array(	
		  'accident_place'         	  => $val['accident_place'],		
		  'accident_date'         	   => trim(implode('-', array_reverse(explode('-',$val['accident_date'])))),
		  'accident_shift'             => $val['accident_shift'],
		  'accident_time'       	   => $val['accident_time'],
		  'is_machinery_accident'      => $val['is_machinery_accident'],
		  'is_moved_by_power'          => $val['is_moved_by_power'],
		  'machine_name'          	   => $val['machine_name'],
		  'accident_description'       => $val['accident_description'],
		);			

		$query_occupier 	=	db_update('fa_form18_notice_accident');
		$query_occupier		->	fields($notice_accident_case_details);
		$query_occupier		->	condition('id',$formid,'=');
		$query_occupier		->	condition('reference_number',$referenceid,'=');
		$query_occupier		->	condition('factory_typeid',$factorytypeid,'=');
		$query_occupier		->	condition('service_id',$serviceid,'=');
		$query_occupier		->	execute();
		
		drupal_goto('applicant/form18/injured-person-details/'.$val['formid_hidden'].'/'.$val['referenceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['serviceid_hidden']);
		
		$form_state['rebuild'] = true;
	} 
 