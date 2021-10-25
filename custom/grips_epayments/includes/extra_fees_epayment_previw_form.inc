<?php 
function extra_fees_epayment_previw_form($form, &$form_state, $boiler_enroll_no = NULL,$boiler_req_id=NULL, $type = NULL,$message_id=''){ 
	
	 drupal_add_css(drupal_get_path('module', 'grips_epayments').'/css/grips_epayments.css');
	 drupal_add_js(drupal_get_path('module', 'grips_epayments').'/js/grips_epayments.js');
	 global $user, $base_root;
	 
	 $uid = $user->uid;
	  $form['proceed_button'] = array(
	                            '#prefix' => '<div>',  
							    '#suffix' => '</div><br>',
								'#type' => 'markup',
								'#markup' => l(t('Back to Dashboard'),'applicant-details'),
								
	);
	
	$query88 = db_select('boiler_details','bd')->fields('bd',array('makers_number'))->condition('boiler_enroll_no',base64_decode($boiler_enroll_no))->execute();
	
	$record = $query88->fetchObject();
	$makers_number = $record->makers_number;
	
	 /* Fees Calculation start */
	 
	 $fees_array=db_query("select mef.extra_fees_amount from message_extra_fees mef, message_count mc where mc.boiler_enroll_no=".base64_decode($boiler_enroll_no)." and boiler_req_id=".$boiler_req_id." and type=".$type." and mc.message_id=".$message_id." and mef.message_id=mc.message_id");
	 
	 $data = $fees_array->fetchAssoc(); 
	 
	
	 $payableFees = $data['extra_fees_amount'];
	
	 //$user_id = $data['user_id'];
	 $user_array1 =	db_query("select firstname,middlename,lastname,phone from b_user_additional_reg_details where uid= ".$uid."");
	 $data1 = $user_array1->fetchAssoc();
	 
	 $user_array2 =	db_query("select mail from users where uid= ".$uid."");
	 $data2 = $user_array2->fetchAssoc();
	
	 $firstname = $data1['firstname'];
	 $middlename = $data1['middlename'];
	 $lastname = $data1['lastname'];
	 $phone = $data1['phone'];
	 $mail = $data2['mail'];
	 
	 
	 
	 
	
	  
	$form['epayments']['begin']	=	array(
									'#prefix'=> '',
									'#suffix'=>'<div class="panel panel-primary"><div class="panel-heading">Payment Details of Boiler/Economizer Registration</div><div class="panel-body">',
								);
	 
	$form['epayments']['maker_no'] = array(
						'#prefix'=> '<fieldset><div class="row"><div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Maker Number'),
						'#type' 		=> 'textfield',
						'#value' 		=> $makers_number,	
						'#attributes' => array('readonly' => 'readonly','class' => array('form-control', 'reg_field')),
	  );
	  
	  $form['epayments']['boiler_enroll_no'] = array(						
						'#type' 		=> 'hidden',
						'#value' 		=> base64_decode($boiler_enroll_no),						
						);
	 $form['epayments']['boiler_req_id'] = array(						
						'#type' 		=> 'hidden',
						'#value' 		=> $boiler_req_id,						
						);
	 $form['epayments']['extra_type'] = array(						
						'#type' 		=> 'hidden',
						'#value' 		=> 'extra_fees',						
						);
	
	
	 $form['epayments']['applicant_name'] = array(
	 					'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Applicant Name'),
						'#type' 		=> 'textfield',
						'#value' 		=> ucwords($firstname.' '.$middlename.' '.$lastname),
						'#attributes' => array('readonly' => 'readonly','class' => array('form-control', 'reg_field')),
						);
						
	$form['epayments']['phone'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Phone'),
						'#type' 		=> 'textfield',
						'#value' 		=> $phone,
						'#attributes' => array('readonly' => 'readonly','class' => array('form-control', 'reg_field')),
						'#element_validate'=> array('TEXTBOX_NUMERIC_VALIDATE')
						);	
	
	$form['epayments']['email'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('E mail'),
						'#type' 		=> 'textfield',
						'#value' 		=> $mail,
						'#attributes' => array('readonly' => 'readonly','class' => array('form-control', 'reg_field')),
						'#element_validate'=> array('TEXTBOX_EMAIL_VALIDATE')
						);

	
	
	$form['epayments']['total_fees'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Total Fees to be Submitted in INR:'),
						'#type' 		=> 'textfield',
						'#value' 		=> $payableFees,
						'#attributes' => array('readonly' => 'readonly','class' => array('form-control', 'reg_field')),
						'#element_validate'=> array('TEXTBOX_NUMERIC_VALIDATE')
						);
						
						
	$form['epayments']['payment_mode'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div></div></fieldset>',
					  '#type' => 'radios',
					  '#title' => t('Payment Mode'),
					  '#required' => true,				  
					  //'#attributes' => array('readonly'=>true),
					  '#options' => array('1'=>t('Online Payment'),'2'=>t('Counter Payment'),'5'=>t('Debit Card Payment')),
					  '#default_value' => !empty($form_state['values']['payment_mode']) ? $form_state['values']['payment_mode'] : '1',
					);
						
	
	$form['epayments']['type'] = array(
						
						'#type' 		=> 'hidden',
						'#value' 		=> $type,
						
						);		
	$form['epayments']['message_id'] = array(
						
						'#type' 		=> 'hidden',
						'#value' 		=> $message_id,
						
						);							
					
	$form['#action'] = url('epayments');
	
	$form['epayments']['submit'] = array (
					   '#type' => 'submit',
					   '#prefix'=> '<center>',
					   '#suffix'=>'</center>',
					   // '#executes_submit_callback' => FALSE,
					   '#value' => 'Proceed To Pay',
					   '#attributes' => array('formtarget'=>'_blank','id' => '#paymentSubmit','class' => array('btn btn-primary')),
  					);
	$form['epayments']['end']	=	array(
								'#prefix'=> '',
								'#suffix'=>'</div></div>',
								);	   
					   
	return $form;

}

function fees_epayment_previw_form_validate($form, &$form_state){ 
$val	=	$form_state['values']; 
		foreach($form as $element){
			if(is_array($element)){
				if(isset($element['#type']) and ($element['#type'] == 'textfield')){
					chkbadchar($element['#value'], $element['#title'], $element['#name']);
				}
			}
		}
		$mob= "/^[6789][0-9]{9}$/";

		if(strlen(trim($val['phone']))>0){
			if(!preg_match($mob, $val['phone'])){ 
			  if (strlen(trim($val['phone'])) < 10){
				 form_set_error('phone', t('Mobile number is less than 10 digit.'));
			  }else{
				form_set_error('phone', t('Mobile number should be valid.'));
			  }
			}
		 }else if(strlen(trim($val['phone']))>0){
			form_set_error('phone', t('Mobile number can not be left blank.'));
		 }
		 if(isset($val['email']) && $val['email'] != ''){
			 $validateEmail	=	db_query("select mail from users where mail=:mailval", array(':mailval'=> $val['email']));
			 if( $validateEmail->rowCount() > 0 ){
				form_error($form['email'], t( 'Email already exists.'));
				$form_state['rebuild'] = TRUE;
			}
		}
}

function extra_fees_epayment_previw_form_submit($form, &$form_state){
	$form_state['redirect'] = url('epayments');
}