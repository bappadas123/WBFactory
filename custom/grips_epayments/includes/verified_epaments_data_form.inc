<?php 
function verified_epaments_data_form($form, &$form_state){
	$form['epayments']['Dept_Cd'] = array(
						 '#title' 		=> t('Dept_Cd'),
						 '#type' 		=> 'hidden',
						 '#value' 		=> '086',				  
	  );
	  
	 $form['epayments']['Service_Cd'] = array(
						 '#title' 		=> t('Service_Cd'),
						 '#type' 		=> 'hidden',
						 '#value' 		=> '301',		  
	  );  
	 
	$form['epayments']['dept_ref_no'] = array(
						'#prefix'=> '<div class="panel panel-success"><div class="panel-heading">Verify Payments</div><div class="panel-body"><fieldset><div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						 '#title' 		=> t('Enter your department reference number.'),
						 '#type' 		=> 'textfield',
						 '#required'		=> TRUE,
						 '#attributes'	=> array('class'=>array('form-control')),					  
	  );
	  
	$form['epayments']['total_amount'] = array(
						'#prefix'=> '<div class="col-md-6 col-xs-12"><label class="input">',
						'#suffix'=>'</label></div>',
						'#title' 		=> t('Total Amount'),
						'#type' 		=> 'textfield',
						'#required'		=> TRUE,
						'#attributes'	=> array('class'=>array('form-control')),				
						);	
	
	$Dept_Ref_No = isset($form_state['values']['dept_ref_no']) && !empty($form_state['values']['dept_ref_no']) ? $form_state['values']['dept_ref_no'] : ''; 
	$total_amount = isset($form_state['values']['total_amount']) && !empty($form_state['values']['total_amount']) ? $form_state['values']['total_amount'] : '';	
	
	if(!empty($Dept_Ref_No) && !empty($total_amount)){
		drupal_add_js(drupal_get_path('module', 'grips_epayments') . '/js/grips_epayments.js');
		$xmlString = 'Dept_Ref_No='.$Dept_Ref_No.'|Dept_Cd=086|Service_Cd=301|Total_Amount='.$total_amount;
		
		$checkSum = md5($xmlString);
		$xmlString = $xmlString.'|checkSum='.$checkSum;
		$xmlString = encrypt($xmlString);		
								
		$form['xmlString'] = array(
							'#title' 		=> t('xmlString'),
							'#type' 		=> 'hidden',
							'#required'		=> TRUE,
							'#value'		=> $xmlString,	
							'#attributes' => array('id'=>'verify_grips_xmlstr')					
							);
		
		$form['#action'] = url('https://wbifms.gov.in/GRIPS/DeptVarifyPayment.do', array('external' => true));

		$form['submit_new'] = array (
					   '#type' => 'submit',
					   '#value' => 'Redirecting to Bank Site. Please do not press BACK button in browser or REFRESH the page.',
					   '#attributes'=> array('id' => 'paymentSubmit','class' => array('btn btn-primary')),
					   '#prefix' => '',
					   '#suffix' => '</fieldset></div></div>',
  					);
	}else{
		$form['submit'] = array (
					   '#type' => 'submit',					  
					   '#value' => 'Submit',
					   '#attributes' => array('id'=>'verify_grips_submit_btn', 'class'=>array('add-dt-btn' )),
					   '#prefix' => '',
					   '#suffix' => '</fieldset></div></div>',		   
  					);
	}
					   
	 return $form;
}

function verified_epaments_data_form_submit($form, &$form_state){
	$form_state['rebuild'] = TRUE;
}