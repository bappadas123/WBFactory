<?php
function add_licence_register($form, &$form_state) {
	
	//$application_id		= encryption_decryption_fun('decrypt',$applicationid);
//	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
//	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytypeid);
//	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	
	//$get_id = get_licence_register_data($application_id, $service_id,$factory_type_id,$reference_no);
	//$get_fa_cafa 		= get_fa_cafa($application_id);
	
	//$factory_name			= $get_fa_cafa['factory_name'];
	//$factory_license_no			= $get_fa_cafa['factory_license_no'];
	
	$classification_no			= $get_fa_cafa['classification_no'];
	$factory_registrstion_no	= $get_fa_cafa['factory_registrstion_no'];
	$date_of_amenability		= $get_fa_cafa['date_of_amenability'];
	$factory_license_no			= $get_fa_cafa['factory_license_no'];
	
	//if(!empty($get_id)){
//		drupal_goto('applicant/add-licence-register-page2/'.$serviceid.'/'.$factorytypeid.'/'.$applicationid.'/'.$referenceid.'/'.encryption_decryption_fun('encrypt',$get_id));
//	}
	
	$form = array();
	
	$form['application_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid,
			 );
	$form['service_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $serviceid,
			 );	
	$form['factorytype_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factorytypeid,
			 );		  	   
	$form['referance_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $referenceid,
			 );
	
	
	$form['licence_register']['markup1']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">Licence Register</h3>
			    					</div>
									<div class = "box-body">',
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
		'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>''),
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
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['name_occupier'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Name of the occupier:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '5',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['change_name_factory'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Change if any:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '2',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['transferr_name_occupier'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Transferrd to:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '2',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
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
function add_licence_register_submit($form, &$form_state){
	  global $user;
	  $uid = $user->uid;
	  $val = $form_state['values'];
	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_hidden']);
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['service_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_hidden']);
	  
	  $licence_register = array(
		'application_id'	=> NULL,
		'service_id'		=> NULL,
		'factorytype_id'	=> NULL,
		'reference_no' 	 	=> NULL,
		'classification_no'	=> $val['classification_no'], 
  		'licence_no'		=> $val['licence_no'],
		'registration_no'	=> $val['registration_no'],
		'amenability_date'	=> $val['amenability_date'],
		'factory_name_address' => $val['name_factory'],
		'change_name'		=> $val['change_name_factory'],
  		'occupier_name'		=> $val['name_occupier'],
  		'occupier_transfer' => $val['transferr_name_occupier'],
		'is_active'			=> 0,
		);
		$id = db_insert('fa_licence_register')->fields($licence_register)->execute();
	  drupal_goto('add-licence-register-page2/'.encryption_decryption_fun('encrypt',$id));
}

//function get_licence_register_data($application_id, $service_id,$factory_type_id,$reference_no){
//	//echo $application_id.'<br/>';echo  $service_id.'<br/>'; echo $factory_type_id.'<br/>';echo $reference_no.'hh<br/>';
//	$register_id = db_query("select id from fa_licence_register WHERE application_id='".$application_id."' AND service_id='".$service_id."' AND factorytype_id='".$factory_type_id."' AND reference_no='".$reference_no."'AND is_active='1'")->fetchObject()->id;
//	return $register_id;
//	}

?>