<?php 
function fees_epayment_preview_form($form, &$form_state, $applicantid ,$serviceid, $referenceno ,$factorytypeid ){ 
	 drupal_add_css(drupal_get_path('module', 'grips_epayments').'/css/grips_epayments.css');
	 drupal_add_js(drupal_get_path('module', 'grips_epayments').'/js/grips_epayments.js');
	 global $user, $base_root;
		$application_id 		= encryption_decryption_fun('decrypt', $applicantid);
		$service_id 			= encryption_decryption_fun('decrypt', $serviceid);
		$reference_no 			= encryption_decryption_fun('decrypt', $referenceno);
	 	$factorytype_id 		= encryption_decryption_fun('decrypt', $factorytypeid);
	 	$get_fa_cafa            = get_fa_cafa($application_id);
	 	$factory_name           = $get_fa_cafa['factory_name'];
		$service_fees           = $get_fa_cafa['service_fees'];
		$service_fees           = $get_fa_cafa['service_fees'];
		$payment_amount			= $get_fa_cafa['payment_amount'];
		$payble_amount			= $get_fa_cafa['payment_amount']-$service_fees;
		$previous_excess_paid	= $get_fa_cafa['previous_excess_paid'];
	 	$occupier_list 		    = get_current_occupier($application_id,$service_id,$factorytype_id,$reference_no);
	//print_r($occupier_list);die();
	 $form['fees_preview'] = array(
        	'#type' 		=> 'fieldset',
       		'#title' 		=> t('Fees Payment Preview'),
        	'#collapsible' 	=> TRUE, // Added
        	'#collapsed' 	=> FALSE // Added
    );
	 $form['fees_preview']['factory_name'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(i). Name of the factory'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> $factory_name,
		'#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly', ),
      
    );
	$form['fees_preview']['factory_occupier_name'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(ii). Name of Occupier'),
        '#type'				=> 'textfield',
        '#default_value' 	=> $occupier_list['name_occupier'].' '.$occupier_list['occupier_name_middle'].' '.$occupier_list['occupier_name_last'].' ('.$occupier_list['type_occupier'].')',
        '#required' 		=> TRUE,
		'#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly' ),
		
    );
	$form['fees_preview']['factory_occupier_email'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(ii). Email Address'),
        '#type'				=> 'textfield',
        '#default_value' 	=> $occupier_list['occupier_email_id'],
        '#required' 		=> TRUE,
		'#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly' ),
		
    );
	$form['fees_preview']['factory_occupier_mobile'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(ii). Mobile Number'),
        '#type'				=> 'textfield',
         '#default_value' 	=> $occupier_list['occupier_mobile'],
        '#required' 		=> TRUE,
		'#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly' ),
		
    );
	if($service_id == 2)
	      $service_acts = 'Registration and grant of License';
	$form['fees_preview']['factory_service_name'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(iii). Service Name:'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($service_acts)?$service_acts:'',
		'#attributes' 		=> array('class' => array('form-control') ,'readonly' => 'readonly'),
    );
	$form['fees_preview']['factory_reg_fees'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(iv). Registration Fees:'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($service_fees)?$service_fees:'0',
		'#attributes' 		=> array('class' => array('form-control') ,'readonly' => 'readonly'),
    );
	
	$form['fees_preview']['factory_license_fees'] = array(
      '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(v). License Fees:'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($payble_amount)?$payble_amount:'0',
		'#attributes' 		=> array('class' => array('form-control') ,'readonly' => 'readonly'),
    );
	$form['fees_preview']['factory_previous_payment_fees'] = array(
      '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(vi). Adjusted Fees:'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($previous_excess_paid)?$previous_excess_paid:'0',
		'#attributes' 		=> array('class' => array('form-control') ,'readonly' => 'readonly'),
    );
	$form['fees_preview']['factory_total_fees'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(vii). Total Payble fees:'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($payment_amount)?$payment_amount:'0',
		'#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly' ),
    );
	$form['fees_preview']['payment_mode'] = array(
					 '#prefix' 			=> '<div class="col-md-6 col-xs-6">',
        			'#suffix' 			=> '</div>',
					  '#type' => 'radios',
					  '#title' => t('(viii)Payment Mode'),
					  '#required' => true,				  
					
					  '#options' => array('1'=>t('Online Payment'),'2'=>t('Counter Payment'),'5'=>t('Debit Card Payment')),
					  
					);	
	$form['#action'] = url('epayments');
	 $form['submit'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#attributes' 		=> array('class' => array('btn btn-success')),
        '#type' 			=> 'submit',
        '#value' 			=> 'PROCEED FOR PAYMENT'
    );
	
					   
	return $form;

}

function _reload_payment_options($form, &$form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#payment_mode_div', drupal_render($form['epayments']['payment_mode']));
	return array('#type' => 'ajax', '#commands' => $commands);	
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

function fees_epayment_preview_form_submit($form, &$form_state){
	$form_state['redirect'] = url('epayments');
}