<?php 
function repairer_extra_fees_epayment_preview_form($form, &$form_state, $repairer_enroll_no = NULL, $repairer_renewal_request_id = NULL,$fees_type=NULL){
	 drupal_add_css(drupal_get_path('module', 'grips_epayments').'/css/grips_epayments.css');
	 drupal_add_js(drupal_get_path('module', 'grips_epayments').'/js/grips_epayments.js');
	 global $user, $base_root;
	 $form = array();
	 $form['proceed_button'] = array(
	                            '#prefix' => '<div>',  
							    '#suffix' => '</div><br>',
								'#type' => 'markup',
								'#markup' => l(t('Back to Dashboard'),'repairer-dashboard'),
								
	);

	$query88 = db_select('repairer_details','rd')
				->fields('rd',array('repairer_name','repairer_enroll_no','id'))
				->condition('repairer_enroll_no',$repairer_enroll_no)
				->execute();
	
	$record88 = $query88->fetchObject();
	
	$repairer_name = $record88->repairer_name;
	$repairer_enroll_no = $record88->repairer_enroll_no;
	$repairer_id = $record88->id;
	
	$query89 = db_select('repairer_renewal_fees_details','rrfd')
				->fields('rrfd',array('renewal_type','class','total_fees','extra_fees_amount'))
				->condition('uid',$user->uid)
				->condition('repairer_renewal_request_id',$repairer_renewal_request_id)
				->execute();
	
	$record89 = $query89->fetchObject();
	$renewal_type = $record89->renewal_type;
	$class = $record89->class;
	
	switch($class){
		case 1 : $class_val = 'Special Class'; break;
		case 2 : $class_val = 'Special Class'; break;
		case 3 : $class_val = 'Special Class'; break;
		case 1 : $class_val = 'Special Class'; break;	
	}
	$total_fees = $record89->extra_fees_amount;
	
	$user_array1 = db_select('b_user_additional_reg_details','rard')
				->fields('rard',array('firstname','middlename','lastname','phone'))
				->condition('uid',$user->uid)
				->execute(); 
	 $data1 = $user_array1->fetchAssoc();
	 
	 
	 $user_array2 = db_select('users','u')
				->fields('u',array('mail'))
				->condition('uid',$user->uid)
				->execute(); 
	 $data2 = $user_array2->fetchAssoc();
	
	 $firstname = $data1['firstname'];
	 $middlename = $data1['middlename'];
	 $lastname = $data1['lastname'];
	 $phone = $data1['phone'];
	 $mail = $data2['mail'];
	  
	$form['epayments']['begin']	=	array(
									'#prefix'=> '',
									'#suffix'=>'<div class="panel panel-primary"><div class="panel-heading">Payment Details of Erector / Repairer</div><div class="panel-body"',
								);
	 
	$form['epayments']['repairer_name'] = array(
						'#prefix'=> '<fieldset><div class="row"><div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Repairer Name'),
						'#type' 		=> 'textfield',
						'#value' 		=> $repairer_name,	
						'#attributes' 	=> array('readonly'=>true)
	  );
	  
	  $form['epayments']['repairer_renewal_request_id'] = array(						
						'#type' 		=> 'hidden',
						'#value' 		=> $repairer_renewal_request_id,						
						);
	$form['epayments']['fees_type'] = array(						
						'#type' 		=> 'hidden',
						'#value' 		=> $fees_type,						
						);
	
	 $form['epayments']['applicant_name'] = array(
	 					'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Applicant Name'),
						'#type' 		=> 'textfield',
						'#value' 		=> ucwords($firstname.' '.$middlename.' '.$lastname),
						'#attributes' 	=> array('readonly'=>true)
						);
						
	$form['epayments']['phone'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Phone'),
						'#type' 		=> 'textfield',
						'#value' 		=> $phone,
						'#attributes' 	=> array('readonly'=>true),
						'#element_validate'=> array('TEXTBOX_NUMERIC_VALIDATE')
						);	
	
	$form['epayments']['email'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('E mail'),
						'#type' 		=> 'textfield',
						'#value' 		=> $mail,
						'#attributes' 	=> array('readonly'=>true),
						'#element_validate'=> array('TEXTBOX_EMAIL_VALIDATE')
						);
	
	$form['epayments']['total_fees'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix' => '</label></div>',
						'#title' 		=> t('Total Fees'),
						'#type' 		=> 'textfield',
						'#value' 		=> $total_fees,
						'#attributes' 	=> array('readonly'=>true),
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
						
	
	$form['epayments']['repairer_enroll_no'] = array(						
						'#type' 		=> 'hidden',
						'#value' 		=> $repairer_enroll_no,
						
						);	
											
	$form['epayments']['repairer_id'] = array(
						
						'#type' 		=> 'hidden',
						'#value' 		=> $repairer_id,
						
						);							
	$form['#action'] = url('repairer_epayments/'.$repairer_renewal_request_id.'/'.$repairer_id.'/'.$fees_type);				
	//$form['#action'] = url('repairer_epayments/'.$repairer_renewal_request_id.'/'.$repairer_id);
	$form['submit'] = array (
					   '#type' => 'submit',
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

/*function repairer_fees_epayment_preview_form_validate($form, &$form_state){ 
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

function repairer_fees_epayment_preview_form_submit($form,&$form_state){
	$repairer_renewal_request_id = $form_state['values']['repairer_renewal_request_id'];
	$repairer_id =  $form_state['values']['repairer_id'];
	$form_state['redirect'] = url('repairer_epayments/'.$repairer_renewal_request_id.'/'.$repairer_id);
}*/