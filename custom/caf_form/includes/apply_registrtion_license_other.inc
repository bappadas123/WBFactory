<?php 
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function apply_registrtion_license_other($form, &$form_state){
	$link_arr 		 	= explode('/', $_GET['q']);
	$service_name 		= $link_arr[2]	;
	global 	$user;
	$uid 				= $user->uid;
	$form 				= array();
	if($service_name == "registration"){
		$service 		= "Apply for Registration and grant of license";
		$service_id 	= 2;
	}
		
	$form['dicission_reg_making'] 	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="box box-info"><div class="box-header with-border">
              				<h3 class="box-title">'.$service.'</h3>
			    			</div><div class = "box-body">',
  					
		);
	$form['dicission_reg_making']['service_list'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> $service_id,
		);

	$form['dicission_reg_making']['nature_of_work'] = array(
	 		'#prefix' 			=> '<div class="row"><div class="col-xs-4">',
		   '#suffix' 			=> '</div>',
		   '#title'				=> 'Nature of work',
		   '#type' 				=> 'select',
		   '#required'			=> TRUE,
		   '#attributes' 		=> array('class'=>array('form-control')),
		   '#options' 			=> nature_work_section85(),
		   '#description'		=> '<b><font color=#FF0000>If not exist select other</font></b>',
		   '#default_value'		=> !empty($service_parent) ? $service_parent :'',
		   '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'get_nature_work',
											'progress'		=>	array(
											'type'			=>'throbber',
											'message'		=>t('loading'),
											),
				)
		);
		
	$radios_options = array('1'=>"Yes",'2'=>"No");	
	$form['dicission_reg_making']['is_power']= array(
			 '#prefix'	 		=> '<div class="col-xs-4">',
			 '#suffix'    		=>'</div>',
			 '#type'		 	=> 'radios',
			 '#title'			=>	t('Power is requried?'),
			 '#options'   		=> $radios_options,	
			 '#ajax'			=> array(
										 'event' 		=> 'change',
										 'effect' 		=> 'fade',			
										 'callback'		=> 'get_nature_work',
										 'progress'		=>	array(
										 'type'			=> 'throbber',
										 'message'		=> t('loading'),
									 )
							 ),
			 '#default_value' 	=> $is_plan_exists,
			 
			 '#required'		=> TRUE,
   
			   
	 );
	 
	 $nature_of_work_value = isset($form_state['values']['nature_of_work'])? $form_state['values']['nature_of_work'] : $service_parent;
	 $is_power_value = isset($form_state['values']['is_power'])? $form_state['values']['is_power'] : $service_parent;	
	 if($is_power_value == "1" && $nature_of_work_value == "other"){
		 $description = "Number of worker will be 10 or more than 10 of any license period";
	 }if($is_power_value == "2" && $nature_of_work_value == "other"){
		 $description = "Number of worker will be 19 or more than 19 of any license period";
	 }if($is_power_value == "2" && $nature_of_work_value !== "other"){
		 $description = "Number of worker will be 10 or less than 10 of any license period";
	 }if($is_power_value == "1" && $nature_of_work_value !== "other"){
		 $description = "Number of worker will be 9 or less than 9 of any license period";
	 }
	 $form['dicission_reg_making']['no_worker'] 	= array(
			 '#prefix' 			=> '<div id ="no_worker_id"><div class="col-xs-4">',
			 '#suffix' 			=> '</div></div></div>',
			 '#attributes' 		=> array('class'=>array('form-control')),
			 '#title'			=>	t('Number of worker'),
			 '#default_value'	=> !empty($plan_approval_number) ? $plan_approval_number	:'',
			 '#description'		=>	'<b><font color=#FF0000>'.$description.'</font></b>',
			 '#type' 			=> 'textfield',
			 '#required' 		=> TRUE,
		);
		
	
	$form['dicission_reg_making']['is_plan_no']= array(
			 '#prefix'	 		=> '<div class="row"><div class="col-xs-4">',
			 '#suffix'    		=>'</div>',
			 '#type'		 	=> 'radios',
			 '#title'			=>	t('Do you have plan approval no'),
			 '#options'   		=> $radios_options,	
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
	 $form['dicission_reg_making']['is_plan_apprpoval_no']= array(
							 '#prefix'	 => '<div id="plan_apprpoval_no_div">',
							 '#suffix'    =>'</div>',
										     
		 );
	 $form['dicission_reg_making']['plan_approval_date'] 	= array(
		 '#prefix' 			=> '<div id="plan_approval_date_div">',
		 '#suffix' 			=> '</div>',
		 
		 	);
	$form['dicission_reg_making']['submit'] = array (
	  '#prefix' 			=> '<div id="submit_div">',
		 '#suffix' 			=> '</div>',
		);
	 $form['dicission_reg_making']['markup_note'] 	= array(
		 '#prefix' 			=> '<div id="markup_note_div">',
		 '#suffix' 			=> '</div>',
		 
		 	);
   $is_plan_no_value = isset($form_state['values']['is_plan_no'])? $form_state['values']['is_plan_no'] : $service_parent;
   if($is_plan_no_value == 1){
	   $form['dicission_reg_making']['is_plan_apprpoval_no']= array(
							 '#prefix'	 => '<div id="plan_apprpoval_no_div"><div class="col-xs-4">',
							 '#suffix'    =>'</div></div>',
							'#attributes' 	=> array('class'=>array('form-control')),
							 '#title'			=>	t('Plan approval no'),
							 '#type'	 => 'textfield',
							 
							
							 '#default_value' => $is_plan_exten,
							 
							 '#required'		=> TRUE,
				     
		 );
		 $form['dicission_reg_making']['plan_approval_date'] 	= array(
		 '#prefix' 			=> '<div id="plan_approval_date_div"><div class="col-xs-4">',
		 '#suffix' 			=> '</div></div>',
		 '#title'			=>	t('Date of approval of plan'),
		 '#default_value'	=> !empty($plan_approval_date) ? $plan_approval_date	:'',
		 '#type' 			=> 'textfield',
		 '#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of approval of plan.'),
		 '#required' 		=> TRUE,
		 	);
	
	//$max_decission_service 		= get_max_decission_service($uid);
	$form['dicission_reg_making']['submit'] = array (
	  '#prefix' 			=> '<div id="submit_div"><div class="col-xs-4">',
		 '#suffix' 			=> '</div></div></div></div></div>',
	  '#attributes' 	=> array('class' => array('btn btn-info pull-right')),
	  '#type' 			=> 'submit',
	  '#value'			=> 'Apply'
	);
   }elseif($is_plan_no_value == 2){
		    $form['dicission_reg_making']['is_plan_apprpoval_no']= array(
							 '#prefix'	 => '<div id="plan_apprpoval_no_div">',
							 '#suffix'    =>'</div>',
										     
		 );
	 $form['dicission_reg_making']['plan_approval_date'] 	= array(
		 '#prefix' 			=> '<div id="plan_approval_date_div">',
		 '#suffix' 			=> '</div>',
		 
		 	);
			$link_apply =l('click here', 'applicant/decission', array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
	 $form['dicission_reg_making']['markup_note'] 	= array(
		 '#prefix' 			=> '<div id="markup_note_div"><div class="col-xs-4">',
		 '#suffix' 			=> '</div></div></div></div></div>',
		 '#type'				=> 'markup',
		  '#markup'			=> '<b><font color =red>You are eligible for service of approval of plan</font></b>  '.$link_apply
				
  
			);
	  
   }else{
	    $form['dicission_reg_making']['markup_div_end'] 	= array(
		 '#prefix' 			=> '',
		 '#suffix' 			=> '</div></div></div>',
		 '#type'				=> 'markup',
		 
				
  
			);
	   
   }
	
	
	return $form;
}

function get_plan_approve($form, $form_state){
	
	
	$commands = array();
	$commands[] = ajax_command_replace('#plan_apprpoval_no_div', drupal_render( $form['dicission_reg_making']['is_plan_apprpoval_no']));
	$commands[] = ajax_command_replace('#plan_approval_date_div', drupal_render( $form['dicission_reg_making']['plan_approval_date']));
	$commands[] = ajax_command_replace('#markup_note_div', drupal_render( $form['dicission_reg_making']['markup_note']));
	$commands[] = ajax_command_replace('#submit_div', drupal_render( $form['dicission_reg_making']['submit']));
	return array('#type' => 'ajax', '#commands' => $commands);
}
function get_nature_work($form, $form_state){
	
	
	$commands = array();
	$commands[] = ajax_command_replace('#no_worker_id', drupal_render( $form['dicission_reg_making']['no_worker']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}

function apply_registrtion_license_other_submit($form, &$form_state){

	global $base_root,$base_path,$user;
  	$uid 	= $user->uid;
   	$i		= 1;
   	$val   	= $form_state['values']; 
   //print_r($val);die();
   $nature_of_work  		= $val['nature_of_work'];
   $is_power	    		= $val['is_power'];
   $no_worker	    		= $val['no_worker'];
   $is_plan_no	   		 	= $val['is_plan_no'];
   $is_plan_apprpoval_no	= $val['is_plan_apprpoval_no'];
   $plan_approval_date	    = $val['plan_approval_date'];
   $service_list	    	= $val['service_list'];
   if($is_power == "1" && $nature_of_work == "other"){
	   if($no_worker<10){
		 	$i=0;
			$factory_type_id_value 	= 	1;
		    drupal_set_message('Number of worker will be 10 or more than 10 of any license period.','errorr'); 
	   }if($no_worker>=10){
		 	$i						=	1;
		    $factory_type_id_value 	= 	1;
	   }
		 
  }if($is_power == "2" && $nature_of_work == "other"){ 
		 if($no_worker<=19){
		    $i=0;
		    drupal_set_message('Number of worker will be 19 or more than 19 of any license period.','error'); 
	   }if($no_worker>=19){
		 	$i=1;
		    $factory_type_id_value = 2;
	   }
	   
		
	 }if($is_power == "2" && $nature_of_work !== "other"){
		  if($no_worker>9){
			   $i=0;
		   drupal_set_message('Number of worker will be 9 or less than 10 of any license period','error'); 
	   }if($no_worker<9){
		 	$i=1;
		    $factory_type_id_value =3;
	   }
		
	 }if($is_power == "1" && $nature_of_work !== "other"){//echo $is_power.$nature_of_work;die('section85');
		 if($no_worker>9){
			  $i=0;
		   drupal_set_message('Number of worker will be 9 or less than 10 of any license period','error'); 
	   }if($no_worker<9){
		 	$i=1;
		    $factory_type_id_value =3;
	   }
	 }
	
	 if($i==1){
		if($service_list ==2){ 
			 if($is_plan_no==1){
				$approval_det = get_application_plan_approval_no($is_plan_apprpoval_no, $plan_approval_date);
			//print_r($approval_det);die();
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
		/*if($is_plan_exists == 2){
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
	
   //die();
  
   
	   
}

?>