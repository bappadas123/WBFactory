<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function apply_renewal_licence($form, &$form_state) {
	$link_arr 		 	= explode('/', $_GET['q']);
	$service_name 		= $link_arr[2]	;
	global 	$user;
	$uid 				= $user->uid;
	$form 				= array();
	if($service_name == "renewal"){
		$service 		= "Apply for Renewal of Factories";
		$service_id 	= 3;
	}

	
	$form['dicision_renewal'] 	= array(
		'#type'		=> 'markup',
		'#prefix'	=> '<div class="box box-info">
							<div class="box-header with-border"><h3 class="box-title">'.$service.'</h3></div>
								<div class = "box-body">',
	);
	$form['dicision_renewal']['service_id'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $service_id,
	);
	$form['dicision_renewal']['nature_of_work'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-xs-4">',
		'#suffix' 			=> '</div>',
		'#title'			=> 'Nature of work',
		'#type' 			=> 'select',
		'#required'			=> TRUE,
		'#attributes' 		=> array('class'=>array('form-control')),
		'#options' 			=> nature_work_section85(),
		'#description'		=> '<b><font color=#FF0000>If not exist select other</font></b>',
		'#default_value'	=> !empty($service_parent) ? $service_parent :'',
		'#ajax'				=> array(
								'event'		=> 'change',
								'effect' 	=> 'fade',			
								'callback'	=> 'get_nature_work',
								'progress'	=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
								),
							)
	);
	$radios_options = array('Y'=>"Yes",'N'=>"No");	
	$form['dicision_renewal']['is_power']= array(
		'#prefix'	=> '<div class="col-xs-4">',
		'#suffix'	=>'</div>',
		'#type'		=> 'radios',
		'#title'	=>	t('Power is requried?'),
		'#options'	=> $radios_options,	
		'#ajax'		=> array(
						'event'		=> 'change',
						'effect' 	=> 'fade',			
						'callback'	=> 'get_nature_work',
						'progress'	=>	array(
						'type'		=> 'throbber',
						'message'	=> t('loading'),
								)
							),
		'#default_value' => $is_plan_exists,
		'#required'		 => TRUE,
	);
	 $nature_of_work_value = isset($form_state['values']['nature_of_work'])? $form_state['values']['nature_of_work'] : $service_parent;
	 $is_power_value = isset($form_state['values']['is_power'])? $form_state['values']['is_power'] : $service_parent;	
	 if($is_power_value == "Y" && $nature_of_work_value == "other"){
		 $description = "Number of worker will be 10 or more than 10 of any license period";
	 }if($is_power_value == "N" && $nature_of_work_value == "other"){
		 $description = "Number of worker will be 19 or more than 19 of any license period";
	 }if($is_power_value == "N" && $nature_of_work_value !== "other"){
		 $description = "Number of worker will be 10 or less than 10 of any license period";
	 }if($is_power_value == "Y" && $nature_of_work_value !== "other"){
		 $description = "Number of worker will be 9 or less than 9 of any license period";
	 }
	 $form['dicision_renewal']['no_worker'] 	= array(
		'#prefix' 			=> '<div id ="no_worker_id"><div class="col-xs-4">',
		'#suffix' 			=> '</div></div></div>',
		'#attributes' 		=> array('class'=>array('form-control')),
		'#title'			=> t('Number of worker'),
		'#default_value'	=> !empty($plan_approval_number) ? $plan_approval_number	:'',
		'#description'		=> '<b><font color=#FF0000>'.$description.'</font></b>',
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		);
	
	$service_list = array('0'=>"---Select----",'2'=>"Registration and grant of license",'3'=>"Renewal of Factories");	
	$form['dicision_renewal']['is_service_no'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-xs-4">',
		'#suffix' 			=> '</div></div><div class="row">',
		'#title'			=> 'Select Service',
		'#type' 			=> 'select',
		'#required'			=> TRUE,
		'#attributes' 		=> array('class'=>array('form-control')),
		'#options' 			=> $service_list,
		'#default_value'	=> !empty($service_list) ? $service_list :'',
		'#ajax'				=> array(
								'event'		=> 'change',
								'effect' 	=> 'fade',			
								'callback'	=> 'get_service_ajax',
								'progress'	=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
								),
							)
	);
	


	$form['dicision_renewal']['is_plan_no']= array(
		'#prefix'	 	=> '<div id="is_plan_no_div">',
		'#suffix'    	=>'</div>',
		);	 
	$form['dicision_renewal']['is_plan_apprpoval_no']= array(
		'#prefix'	 => '<div id="plan_apprpoval_no_div">',
		'#suffix'    =>'</div>',
		);
	 $form['dicision_renewal']['plan_approval_date'] 	= array(
		 '#prefix' 			=> '<div id="plan_approval_date_div">',
		 '#suffix' 			=> '</div>',
		 );
	$form['dicision_renewal']['plan_submit'] = array (
	  	'#prefix' 			=> '<div id="submit_plan_div">',
		'#suffix' 			=> '</div>',
		 );

	 $form['dicision_renewal']['markup_note'] 	= array(
		 '#prefix' 			=> '<div id="markup_note_div">',
		 '#suffix' 			=> '</div>',
		 	);
	$form['dicision_renewal']['is_reg_no']= array(
		'#prefix'	 	=> '<div id="is_reg_no_div">',
		'#suffix'    	=> '</div>',
		);
			
	$form['dicision_renewal']['registration_no'] 	= array(
		 '#prefix' 			=> '<div id="registration_no_div">',
		 '#suffix' 			=> '</div>',
		 );
	$form['dicision_renewal']['registration_date'] 	= array(
		 '#prefix' 			=> '<div id="registration_date_div">',
		 '#suffix' 			=> '</div>',
		 );
	$form['dicision_renewal']['licence_no'] 	= array(
		 '#prefix' 			=> '<div id="licence_no_div">',
		 '#suffix' 			=> '</div>',
		 );
	$form['dicision_renewal']['licence_date'] 	= array(
		 '#prefix' 			=> '<div id="licence_date_div">',
		 '#suffix' 			=> '</div>',
		 );
	$form['dicision_renewal']['submit'] = array (
	  	'#prefix' 			=> '<div id="submit_div">',
		'#suffix' 			=> '</div></div></div></div>',
		 );
	$is_service = isset($form_state['values']['is_service_no'])? $form_state['values']['is_service_no'] : $service_list;
	if($is_service == 3){
	$options_licence = array('R'=>"Registration No.",'L'=>"Licence No.");	
	$form['dicision_renewal']['is_reg_no']= array(
		'#prefix'	 	=> '<div class="col-xs-4" id="is_reg_no_div">',
		'#suffix'    	=> '</div></div></div></div>',
		'#type'		 	=> 'radios',
		'#title'		=>	t('Do you have :'),
		'#options'   	=> $options_licence,	
		'#ajax'			=> array(
						'event' 		=> 'change',
						'effect' 		=> 'fade',			
						'callback'		=> 'get_licence_register_ajax',
						'progress'		=>	array(
						'type'			=> 'throbber',
						'message'		=> t('loading'),
								)
							 ),
		'#default_value' 	=> $is_licence_registion,
		'#required'		=> TRUE,
		 );
	
	$is_reg_licence_no = isset($form_state['values']['is_reg_no'])? $form_state['values']['is_reg_no'] : $is_licence_registion;

	if($is_reg_licence_no == 'R'){
	$form['dicision_renewal']['registration_no'] 	= array(
		'#prefix' 			=> '<div id="registration_no_div"><div class="col-xs-4">',
		'#suffix' 			=> '</div></div></div></div></div>',
		'#attributes' 		=> array('class'=>array('form-control')),
		'#title'			=>	t('Enter Factory registration number'),
		'#default_value'	=> '',
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		);
	$form['dicision_renewal']['registration_date'] 	= array(
		 '#prefix' 			=> '<div id="registration_date_div"><div class="col-xs-4">',
		 '#suffix' 			=> '</div></div></div></div></div>',
		 '#title'			=>	t('Enter Date of Registration'),
		 '#default_value'	=> '',
		 '#type' 			=> 'textfield',
		 '#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Regigistration.'),);

	}
	if($is_reg_licence_no == 'L'){
			$form['dicision_renewal']['licence_no'] 	= array(
			'#prefix' 			=> '<div id="licence_no_div"><div class="col-xs-4">',
			'#suffix' 			=> '</div></div></div></div></div>',
			'#attributes' 		=> array('class'=>array('form-control')),
			'#title'			=>	t('Enter  Licence number'),
			'#default_value'	=> '',
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			);
		$form['dicision_renewal']['licence_date'] 	= array(
			 '#prefix' 			=> '<div id="licence_date_div"><div class="col-xs-4">',
			 '#suffix' 			=> '</div></div></div></div></div>',
			 '#title'			=>	t('valid upto Licence date'),
			 '#default_value'	=> '',
			 '#type' 			=> 'textfield',
			 '#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Regigistration.'),);
	
		
		}
		$form['dicision_renewal']['submit'] = array (
	  	'#prefix' 		=> '<div id="submit_div"><div class="col-xs-12">',
		'#suffix' 		=> '</div></div></div></div></div>',
	  	'#attributes' 	=> array('class' => array('btn btn-info pull-left')),
	  	'#type' 		=> 'submit',
	  	'#value'		=> 'Apply'
		);
	}
	if($is_service == 2){
	$radios_options_plan = array('4'=>"Yes",'5'=>"No");	
	$form['dicision_renewal']['is_plan_no']= array(
		'#prefix'	 	=> '<div class="col-xs-4" id="is_plan_no_div">',
		'#suffix'    	=> '</div></div></div></div>',
		'#type'		 	=> 'radios',
		'#title'		=>	t('Do you have plan approval no'),
		'#options'   	=> $radios_options_plan,	
		'#ajax'			=> array(
						'event' 		=> 'change',
						'effect' 		=> 'fade',			
						'callback'		=> 'get_plan_approve',
						'progress'		=>	array(
						'type'			=> 'throbber',
						'message'		=> t('loading'),
								)
							 ),
		'#default_value' 	=> $is_plan_exists,
		'#required'		=> TRUE,
		 );
	$is_plan_no_value = isset($form_state['values']['is_plan_no'])? $form_state['values']['is_plan_no'] : $is_plan_exists;
	 if($is_plan_no_value == 4){
	   $form['dicision_renewal']['is_plan_apprpoval_no']= array(
			'#prefix'		=> '<div id="plan_apprpoval_no_div"><div class="col-xs-4">',
			'#suffix'		=>'</div></div>',
			'#attributes'	=> array('class'=>array('form-control')),
			'#title'		=>	t('Plan approval no'),
			'#type'			=> 'textfield',
			'#default_value'=> $is_plan_exten,
			'#required'		=> TRUE,
			);
			
		 $form['dicision_renewal']['plan_approval_date'] 	= array(
		 '#prefix' 			=> '<div id="plan_approval_date_div"><div class="col-xs-4">',
		 '#suffix' 			=> '</div></div>',
		 '#title'			=>	t('Date of approval of plan'),
		 '#default_value'	=> !empty($plan_approval_date) ? $plan_approval_date	:'',
		 '#type' 			=> 'textfield',
		 '#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of approval of plan.'),
		 '#required' 		=> TRUE,
		 	);
	
	//$max_decission_service 		= get_max_decission_service($uid);
		$form['dicision_renewal']['plan_submit'] = array (
	  	'#prefix' 		=> '<div id="submit_plan_div"><div class="col-xs-4">',
		'#suffix' 		=> '</div></div></div></div></div>',
	  	'#attributes' 	=> array('class' => array('btn btn-info pull-left')),
	  	'#type' 		=> 'submit',
	  	'#value'		=> 'Apply'
		);
	}elseif($is_plan_no_value == 5){
	$form['dicision_renewal']['is_plan_apprpoval_no']= array(
		'#prefix'	 => '<div id="plan_apprpoval_no_div">',
		'#suffix'    =>'</div>',
		);
	 $form['dicision_renewal']['plan_approval_date'] 	= array(
		 '#prefix' 			=> '<div id="plan_approval_date_div">',
		 '#suffix' 			=> '</div>',
		 );
	$link_apply =l('click here', 'applicant/decission', array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
	 $form['dicision_renewal']['markup_note'] 	= array(
		 '#prefix' 			=> '<div id="markup_note_div"><div class="col-xs-4">',
		 '#suffix' 			=> '</div></div></div></div></div>',
		 '#type'				=> 'markup',
		 '#markup'			=> '<b><font color =red>You are eligible for service of approval of plan</font></b>  '.$link_apply
		);
	  
   	}else{
	$form['dicision_renewal']['markup_div_end'] 	= array(
		'#prefix' 			=> '',
		'#suffix' 			=> '</div></div></div></div></div></div></div></div></div>',
		'#type'				=> 'markup',
		);
		}
	}
	
	
	
	$form['dicision_renewal']['markup_div_end'] 	= array(
		 '#prefix' 		=> '',
		 '#suffix' 		=> '</div></div>',
		 '#type'		=> 'markup',
		 );
	
	return $form;
}
function get_service_ajax($form, $form_state){
	$commands = array();
	
	$commands[] = ajax_command_replace('#is_plan_no_div', drupal_render( $form['dicision_renewal']['is_plan_no']));
	//$commands[] = ajax_command_replace('#plan_apprpoval_no_div', drupal_render( $form['dicision_renewal']['is_plan_apprpoval_no']));
	//$commands[] = ajax_command_replace('#plan_approval_date_div', drupal_render( $form['dicision_renewal']['plan_approval_date']));
	//$commands[] = ajax_command_replace('#markup_note_div', drupal_render( $form['dicision_renewal']['markup_note']));

	$commands[] = ajax_command_replace('#is_reg_no_div', drupal_render($form['dicision_renewal']['is_reg_no']));
	return array('#type' => 'ajax', '#commands' => $commands);
	
	
	}
function get_licence_register_ajax($form, $form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#registration_no_div', drupal_render( $form['dicision_renewal']['registration_no']));
	$commands[] = ajax_command_replace('#registration_date_div', drupal_render( $form['dicision_renewal']['registration_date']));
	$commands[] = ajax_command_replace('#licence_no_div', drupal_render( $form['dicision_renewal']['licence_no']));
	$commands[] = ajax_command_replace('#licence_date_div', drupal_render( $form['dicision_renewal']['licence_date']));
	$commands[] = ajax_command_replace('#submit_div', drupal_render( $form['dicision_renewal']['submit']));
	return array('#type' => 'ajax', '#commands' => $commands);
	
	}
function get_plan_approve($form, $form_state){

	$commands = array();
	$commands[] = ajax_command_replace('#plan_apprpoval_no_div', drupal_render( $form['dicision_renewal']['is_plan_apprpoval_no']));
	$commands[] = ajax_command_replace('#plan_approval_date_div', drupal_render( $form['dicision_renewal']['plan_approval_date']));
	$commands[] = ajax_command_replace('#markup_note_div', drupal_render( $form['dicision_renewal']['markup_note']));
	$commands[] = ajax_command_replace('#submit_plan_div', drupal_render($form['dicision_renewal']['plan_submit']));
	return array('#type' => 'ajax', '#commands' => $commands);
}
function get_nature_work($form, $form_state){
	
	
	$commands = array();
	$commands[] = ajax_command_replace('#no_worker_id', drupal_render( $form['dicision_renewal']['no_worker']));
	return array('#type' => 'ajax', '#commands' => $commands);
}
function apply_renewal_licence_submit($form, &$form_state){
	global $base_root,$base_path,$user;
  	$uid 	= $user->uid;
	$i		= 1;
   	$val   	= $form_state['values']; 
	//print_r($val);die;
	
	if($val['plan_submit']=='Apply'){
		
	$nature_of_work  		= $val['nature_of_work'];
    $is_power	    		= $val['is_power'];
    $no_worker	    		= $val['no_worker'];
    $is_plan_no	   		 	= $val['is_plan_no'];
    $is_plan_apprpoval_no	= $val['is_plan_apprpoval_no'];
    $plan_approval_date	    = $val['plan_approval_date'];
    $service_list	    	= $val['is_service_no'];
   
	if($is_power == "Y" && $nature_of_work == "other"){
		
	   if($no_worker<10){
		 	$i=0;
			$factory_type_id_value 	= 	1;
		    drupal_set_message('Number of worker will be 10 or more than 10 of any license period.','error'); 
	   }
	   if($no_worker>=10){
		 	$i						=	1;
		    $factory_type_id_value 	= 	1;
	   }
		 
  }
	if($is_power == "N" && $nature_of_work == "other"){ 
		 if($no_worker<=19){
		    $i=0;
		    drupal_set_message('Number of worker will be 19 or more than 19 of any license period.','error'); 
	   }if($no_worker>=19){
		 	$i=1;
		    $factory_type_id_value = 2;
	   }
	   
		
	 }
	if($is_power == "N" && $nature_of_work !== "other"){
		  if($no_worker>9){
			   $i=0;
		   drupal_set_message('Number of worker will be 9 or less than 10 of any license period','error'); 
	   }if($no_worker<9){
		 	$i=1;
		    $factory_type_id_value =3;
	   }
		
	 }
	if($is_power == "Y" && $nature_of_work !== "other"){//echo $is_power.$nature_of_work;die('section85');
		 if($no_worker>9){
			  $i=0;
		   drupal_set_message('Number of worker will be 9 or less than 10 of any license period','error'); 
	   }if($no_worker<9){
		 	$i=1;
		    $factory_type_id_value =3;
	   }
	 }
	
	if($i==1){
		if($service_list == 2){
			 if($is_plan_no==4){
				$approval_det 	= get_application_plan_approval_no($is_plan_apprpoval_no, $plan_approval_date);
				//print_r($approval_det);die();
				//die( $no_worker.'ser'.$service_list.'plan no'.$is_plan_no);
				$applicant_uid 	= $approval_det['created_by'];
				$loggedin_uid 	= $uid;
				$application_id = $approval_det['id'];
				$ref_no 		= $approval_det['reference_number'];
			
		     	if(!empty($application_id)){
					if($approval_det['is_backlog'] == 1){
						drupal_goto('applicant/caf-reg/registrtatoin-license/'.encryption_decryption_fun('encrypt',$service_list).'/'.encryption_decryption_fun('encrypt',$factory_type_id_value).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$is_plan_apprpoval_no).'/'.encryption_decryption_fun('encrypt',$plan_approval_date).'/'.encryption_decryption_fun('encrypt','backlogplanapproval_no')) ;
				 	}else{
						if($applicant_uid == $loggedin_uid){
						drupal_goto('apply-eservice-registration/'.encryption_decryption_fun('encrypt',$service_list).'/'.encryption_decryption_fun('encrypt',$factory_type_id_value).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$ref_no)) ;
						}else{
							drupal_set_message('This approval number does not belong to you','error'); 
							}
						}
					}else{
						$application_id =0;
						drupal_goto('applicant/caf-reg/registrtatoin-license/'.encryption_decryption_fun('encrypt',$service_list).'/'.encryption_decryption_fun('encrypt',$factory_type_id_value).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$is_plan_apprpoval_no).'/'.encryption_decryption_fun('encrypt',$plan_approval_date).'/'.encryption_decryption_fun('encrypt','backlogplanapproval_no')) ;
					}
				}
			/*if($is_plan_exists == 5){
			$application_id =  get_fact_reg_identification_no($identification_number, $identification_date);
			if(!empty($application_id)){
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.encryption_decryption_fun('encrypt',$decission_service_id_vlue).'/'.encryption_decryption_fun('encrypt',$factory_type_id_vlue).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$registration_number).'/'.encryption_decryption_fun('encrypt','registration_number')) ;
		}else{
			$application_id =0;
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.encryption_decryption_fun('encrypt',$decission_service_id_vlue).'/'.encryption_decryption_fun('encrypt',$factory_type_id_vlue).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$registration_number).'/'.encryption_decryption_fun('encrypt','backlog_registrationno')) ;
		}
	}*/
			}
	 	}
	}
	
	if($val['submit'] == 'Apply'){
		$nature_of_work = $val['nature_of_work'];
		$is_power	    = $val['is_power'];
		$no_worker	    = $val['no_worker'];
		$service_no	    = $val['is_service_no'];
		$service_id		= $val['service_id'];
		
		if($is_power == "Y" && $nature_of_work == "other"){
		
	   if($no_worker<10){
		 	$i=0;
			$factory_type_id_value 	= 	1;
		    drupal_set_message('Number of worker will be 10 or more than 10 of any license period.','error'); 
	   }
	   if($no_worker>=10){
		 	$i						=	1;
		    $factory_type_id_value 	= 	1;
	   }
		 
  }
		if($is_power == "N" && $nature_of_work == "other"){ 
		 if($no_worker<=19){
		    $i=0;
		    drupal_set_message('Number of worker will be 19 or more than 19 of any license period.','error'); 
	   }if($no_worker>=19){
		 	$i=1;
		    $factory_type_id_value = 2;
	   }
	   
		
	 }
		if($is_power == "N" && $nature_of_work !== "other"){
		  if($no_worker>9){
			   $i=0;
		   drupal_set_message('Number of worker will be 9 or less than 10 of any license period','error'); 
	   }if($no_worker<9){
		 	$i=1;
		    $factory_type_id_value =3;
	   }
		
	 }
		if($is_power == "Y" && $nature_of_work !== "other"){//echo $is_power.$nature_of_work;die('section85');
		 if($no_worker>9){
			  $i=0;
		   drupal_set_message('Number of worker will be 9 or less than 10 of any license period','error'); 
	   }if($no_worker<9){
		 	$i=1;
		    $factory_type_id_value =3;
	   }
	 }
	 
		if(!empty($val['registration_no'])){
			$number  		= $val['registration_no'];
			$date	    	= $val['registration_date'];
			$type			= 'reg_no';
			}
		elseif(!empty($val['licence_no'])){
			$number  		= $val['licence_no'];
			$date	    	= $val['licence_date'];
			$type			= 'lic_no';
			}
		
   		//die('ser'.$service_no);
   		$checked = check_licence_registration($number,$date);
		
	   if(!empty($checked)){
		   drupal_goto('applicant/caf-renew/apply-eservice-renewal/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id_value).'/'.encryption_decryption_fun('encrypt',$checked['id']).'/'.encryption_decryption_fun('encrypt',$checked['registration_date']).'/'.encryption_decryption_fun('encrypt',$flagmapp));
		   
		   }else{
			  $application_id =0;
			   drupal_goto('applicant/caf-online-renew/apply-online-renewal-service/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id_value).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$number).'/'.encryption_decryption_fun('encrypt',$date).'/'.encryption_decryption_fun('encrypt',$type));
			   }
			}
		}


function check_licence_registration($number,$date){
	
	$fetch_number	= db_select('fa_cafa ', 'cafa');
	$fetch_number	->fields('cafa', array('id','factory_registrstion_no','registration_date'));
	$fetch_number	->condition('cafa.factory_registrstion_no ',trim($number));
    $get_registration_number = $fetch_number->execute()->fetchAssoc();
	$get_licence_number = 1;
	if($get_registration_number == NULL){
		$fetch_number	= db_select('fa_cafa ', 'cafa');
		$fetch_number	->fields('cafa', array('id','factory_license_no','license_date'));
		$fetch_number	->condition('cafa.factory_license_no ',trim($number));
		$get_licence_number = $fetch_number->execute()->fetchAssoc(); 
		$number = $get_licence_number;
	}elseif($get_licence_number==NULL){
		$number = 0;
	}else{
		$number = $get_registration_number;
	}
		return $number;
}