<?php
function edit_licence_register_page2($form, &$form_state,$id) {	
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	global $base_root, $base_path, $user;
	
	$edit_id 		= encryption_decryption_fun('decrypt',$id);
	$amount_details = db_select('fa_licence_register_amount', 'dt')->condition('id',$edit_id, '=');
	$amount_details ->fields('dt',array());
	$details 		= $amount_details->execute()->fetchAssoc(); 
 
	$form = array();
	$form['id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$edit_id),
			 );
			 
	$form['licence_register']['markup2']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
							<div class = "col-md-3 col-xs-12">
								<div class="box box-info">
									<div class="box-header with-border">
										<h5 class="box-title">Licence issued for</h5>
			    					</div>
									<div class = "box-body">',
	);
	$form['licence_register']['category'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Category:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($details['category'])?$details['category']:'',
		
	 );
	 $form['licence_register']['schedule'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Schedule:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($details['schedule'])?$details['schedule']:'',
	 );
	 

	$form['licence_register']['markup_end2'] 	= array(
		'#suffix' => '</div></div></div>',
	);
	
	$form['licence_register']['markup3']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class = "col-md-9 col-xs-12">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title"></h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$form['licence_register']['year'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Year:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($details['licence_period'])?$details['licence_period']:'',
		
	 );
	 $form['licence_register']['power'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Power:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($details['power'])?$details['power']:'',
	 );
	 $form['licence_register']['type'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('HP/KW:'),
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#type' 			=> 'select',
  		'#options' 			=> array(t('SELECT'), t('KW'), t('HP'),),
		'#default_value' 	=> !empty($details['power_type'])?$details['power_type']:'',
	 );
	 $form['licence_register']['worker'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('worker:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($details['worker'])?$details['worker']:'',
	 );
	
	$form['licence_register']['markup_end3'] 	= array(
		'#suffix' => '</div></div></div></div>',
	);
	
	
	$form['licence_register']['markup4']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
							<div class = "col-md-3 col-xs-12">
								<div class="box box-info">
									<div class="box-header with-border">
										<h5 class="box-title">Amount of fees paid for</h5>
			    					</div>
									<div class = "box-body">',
	);
	$form['licence_register']['register_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(a). Registration Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> !empty($details['register_fee'])?$details['register_fee']:'',
		//'#ajax'				=> array('callback'=> 'callback')
	 );
	 $form['licence_register']['licence_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(b). Licence Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> !empty($details['renewal_fee'])?$details['renewal_fee']:'',
	 );
	 $form['licence_register']['amendment_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(c). Amendment Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> !empty($details['amendment_fee'])?$details['amendment_fee']:'',
	 );
	 $form['licence_register']['transfer_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(d). Transfer Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> !empty($details['transfer_fee'])?$details['transfer_fee']:'',
	 );
	 $form['licence_register']['late_pay_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(e). Late Payment Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> !empty($details['late_pay_fee'])?$details['late_pay_fee']:'',
	 );
	 $form['licence_register']['loss_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(f). Loss Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> !empty($details['loss_fee'])?$details['loss_fee']:'',
	 );
	$form['licence_register']['markup_end4'] 	= array(
		'#suffix' => '</div></div></div>',
	);
	
	$form['licence_register']['markup5']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class = "col-md-9 col-xs-12">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title"></h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$form['licence_register']['deposit_date'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Date of Deposit:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control multidate'),'title'=>''),
		'#default_value' 	=> !empty($details['deposit_date'])?$details['deposit_date']:'',
	 );
	 $form['licence_register']['chalan_no'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Serial no. in chalan register:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#description' 		=> '<span style="color:red">Chalan no need to add comma separated.</span>',
		'#default_value' 	=> !empty($details['challan_no'])?$details['challan_no']:'',
	 );
	 $form['licence_register']['excess_paid_amount'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Excess amount paid:'),
		'#description' 		=> 'If any excess amount.',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#type' 			=> 'textfield',
		'#default_value' 	=> !empty($details['excees_fees'])?$details['excees_fees']:'',
	 );
	 $form['licence_register']['adjusted_amount'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Excess amount adjusted:'),
        '#type' 			=> 'textfield',
		'#description' 		=> 'If adjusted against fee payable.',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($details['adjusted_fees'])?$details['adjusted_fees']:'',
	 );
	 
	  $form['licence_register']['register_remark'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Register Remark:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '5',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($details['register_remarks'])?$details['register_remarks']:'',
	 );
	 
	 $form['licence_register']['add'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#attributes' 		=> array('class' => array('btn bg-navy margin')),
        '#type' 			=> 'submit',
        '#value' 			=> 'Edit Licence Register'
    );
	
	$form['licence_register']['save_continue'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#attributes' 		=> array('class' => array('btn bg-navy margin')),
        '#type' 			=> 'submit',
        '#value' 			=> 'Continue'
    );
	$form['licence_register']['markup_end5'] 	= array(
		'#suffix' => '</div></div></div></div>',
	);
	
	return $form; 
}
	


function edit_licence_register_page2_submit($form, &$form_state){
	  global $user;
	  $val = $form_state['values'];
	  $uid = $user->uid;
	  
	  $edit_id	= encryption_decryption_fun('decrypt',$val['id_hidden']); 
	
	  if($val['op']=='Edit Licence Register'){
		 
			$licence_register_amount = array(
			 
				'category'			=> $val['category'],
				'schedule'			=> $val['schedule'],
				'licence_period'	=> $val['year'],
				'power' 			=> $val['power'],
				'power_type'		=> $val['type'],
				'worker'			=> $val['worker'],
				'register_fee' 		=> $val['register_fee'],
				'renewal_fee' 		=> $val['licence_fee'],
				'amendment_fee' 	=> $val['amendment_fee'],
				'transfer_fee' 		=> $val['transfer_fee'],
				'late_pay_fee' 		=> $val['late_pay_fee'],
				'loss_fee' 			=> $val['loss_fee'],
				'deposit_date' 		=> $val['deposit_date'],
				'challan_no'		=> $val['chalan_no'],
				'excees_fees' 		=> $val['excess_paid_amount'],
				'adjusted_fees' 	=> $val['adjusted_amount'],
				'register_remarks' 	=> $val['register_remark'],
				'uid'				=> $uid,
				);
			if(!empty($edit_id)){
				$query = db_update('fa_licence_register_amount');
				$query->fields($licence_register_amount);
				$query->condition('id', $edit_id, '=');
				$query->execute();
				
				 drupal_set_message('Amount register has been updated successfully.');
				}
			}
		
		if($val['op']=='Continue'){
			drupal_goto('all-licence-register');
			
		}
		$form_state['rebuild'] = true;
}

?>