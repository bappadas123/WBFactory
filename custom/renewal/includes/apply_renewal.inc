<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function apply_renewal($form, &$form_state) {
	global $base_root,$base_path,$user;
	 $form['header']            = array(
        '#markup' => t('<div class="content"><h1><font color = "red">PLEASE DONOT SUBMIT ANY DATA FROM THIS PAGE. THIS IS UNDER TESTING</font></h1>')
    ); 
	
   $form['renewal_information']['license_no'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(i).License Number'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> $factory_name,
		'#attributes' 		=> array('class' => array( 'form-control')),
      
    );
	
	$form['renewal_information']['valid_upto'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(ii).Valid upto Date'),
        '#type'				=> 'textfield',
        '#default_value' 	=> $factory_pan,
        '#required' 		=> TRUE,
		'#attributes' 		=> array( 'class' => array('form-control datepicker_cls')),
		
    );
	
	$form['renewal_information']['submit'] = array (
		'#prefix' 		=> '<div class="row"><div class="col-md-12">',
		'#suffix'		=> '</div></div><br>',
		'#type' 		=> 'submit',
		'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		'#value' 		=> 'Submit',
	
	);
	
	return $form;
	}





function apply_renewal_submit($form, &$form_state){
	global $user;
    $userid 			= $user->uid;
    $val    			= $form_state['values'];
	$license_no 		= $val['license_no'];
	$valid_upto 		= $val['valid_upto'];
	$service_id			= 3;
	$caf_data 			= fun_fetch_cafa($license_no,$valid_upto,$service_id);
	if(empty($caf_data)){
		$tm_fact_data = fun_fetch_fact_tm($license_no,$valid_upto);
		
		if(!empty($tm_fact_data)){
			
		drupal_goto('applicant/renewal-license/'.encryption_decryption_fun('encrypt',$license_no).'/'.encryption_decryption_fun('encrypt',$valid_upto).'/'.encryption_decryption_fun('encrypt',$service_id));	
		}else{
			 drupal_set_message('This is an invalid Licesne Number','Error');
		}
	}else{
		drupal_goto('applicant-dashboard');	
	}
		
	//print_r($tm_fact_data);die();
	
			
	
	
	
	
	//DONE//
}

?>