<?php 
function licence_register_edit($form, &$form_state,$id){
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$id	= encryption_decryption_fun('decrypt',$id);
	$get_all_data =  get_licence_register($id);
	foreach($get_all_data  as $register){
		$classification_no= $register->classification_no;
		$factory_registrstion_no= $register->registration_no;
		$date_of_amenability= $register->amenability_date;
		$factory_license_no= $register->licence_no;
		
		$factory_name_address= $register->factory_name_address;
		$factory_change_name= $register->change_name;
		$occupier_name= $register->occupier_name;
		$occupier_transfer= $register->occupier_transfer;
	}
	$form['licence_register']['markup1']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">Edit Licence Register</h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['licence_register']['register_no'] = array(
        '#type' 			=> 'hidden',
		'#default_value' 	=> !empty($id)? $id : '',
	 );
	 $form['licence_register']['classification_no'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Classification No:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($classification_no)? $classification_no : '',
	 );
	 $form['licence_register']['registration_no'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Registration No:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($factory_registrstion_no)? $factory_registrstion_no : '',
	 );
	 $form['licence_register']['amenability_date'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Date:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control datepicker'),'title'=>''),
		'#default_value' 	=> !empty($date_of_amenability)? $date_of_amenability : '',
	 );
	 $form['licence_register']['licence_no'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Licence No:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($factory_license_no)? $factory_license_no : '',
		
	 );
	
	$form['licence_register']['name_factory'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Name & address of the factory:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '5',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($factory_name_address)? $factory_name_address : '',
	 );
	 $form['licence_register']['name_occupier'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Name of the occupier:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '5',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($occupier_name)? $occupier_name : '',
	 );
	 $form['licence_register']['change_name_factory'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Change if any:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '2',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($factory_change_name)? $factory_change_name : '',
	 );
	 $form['licence_register']['transferr_name_occupier'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Transferrd to:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '2',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> !empty($occupier_transfer)? $occupier_transfer : '',
	 );
	 $form['licence_register']['op'] = array(
        '#prefix' 			=> '<div class="col-md-12">',
        '#suffix' 			=> '</div>',
        '#attributes' 		=> array('class' => array('btn bg-navy margin')),
        '#type' 			=> 'submit',
        '#value' 			=> 'Save'
    );
	$form['licence_register']['markup_end1'] 	= array(
		'#suffix' => '</div></div></div>',
	);
	
	return $form;	
}

function licence_register_edit_submit($form, &$form_state){
	  global $user;
	  $uid = $user->uid;
	  $val = $form_state['values'];
	  $register_id 			= 	$val['register_no'];
	  
	  $licence_register = array(
		'classification_no'	=> $val['classification_no'], 
  		'licence_no'		=> $val['licence_no'],
		'registration_no'	=> $val['registration_no'],
		'amenability_date'	=> $val['amenability_date'],
		'factory_name_address' => $val['name_factory'],
		'change_name'		=> $val['change_name_factory'],
  		'occupier_name'		=> $val['name_occupier'],
  		'occupier_transfer' => $val['transferr_name_occupier']
		);
		$queryabc = db_update('fa_licence_register');
        $queryabc->fields($licence_register);
        $queryabc->condition('id', $register_id, '=');
        $queryabc->execute();
	drupal_goto('licence-register-edit-details/'.encryption_decryption_fun('encrypt',$register_id));
}