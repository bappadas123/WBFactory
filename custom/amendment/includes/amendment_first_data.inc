<?php
function amendment_first_data($form, &$form_state, $applicationid, $serviceid, $factorytypeid, $license_no,$date) {
	
	drupal_add_js(drupal_get_path('module', 'amendment') . '/js/myfunction.js');
	
	$application_id 		= 	encryption_decryption_fun('decrypt', $applicationid);
	$service_id 			= 	encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 		= 	encryption_decryption_fun('decrypt', $factorytypeid);
	$license_number			= 	encryption_decryption_fun('decrypt', $license_no);
	$license_date			= 	encryption_decryption_fun('decrypt', $date);

	$reference_no			=  	encryption_decryption_fun('decrypt', $referenceno);
		
	//die($application_id.'<br>'.$service_id.'<br>'.$factorytype_id.'<br>'.$license_number.'<br>'.$license_date);
	$form = array();
   	$form['#attributes'] = array('enctype' => "multipart/form-data");
		
	$form['serviceid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid
	);	
	$form['factorytype_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=>  $factorytypeid
	);		  	   
	$form['referance_no_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $referenceno
	);
	$form['application_id_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $applicationid
	);
	
$form['reg_year'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('F. State the period of license'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	 $form['reg_year']['factor_amenablity_date'] = array(
		'#prefix' 			=> 	'<div class="row"><div class="col-lg-6 col-md-6 col-sm-6 col-xs-6">',
		'#suffix' 			=> 	'</div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t('(i). Date from which the premises is occupied or been taken into use as factory'),
		'#required' 		=>  TRUE,
		'#default_value' 	=>  $date_of_amenability,
		'#attributes' 		=> 	array('class' => array('form-control datepicker'),'placeholder' => '','readonly' => 'readonly'),
			
		);
		$form['reg_year']['how_many_year'] = array(
		'#prefix' 			=> 	'<div  class="col-lg-6 col-md-6 col-sm-6 col-xs-6">',
		'#suffix' 			=> 	'</div></div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t('(ii). State the period of license required for date from application date'),
		'#required' 		=>  TRUE,
		'#element_validate'	=>  array('isnumaric_valiadtion'), 
		'#default_value' 	=>  $period_for_application,
		'#attributes' 		=> 	array('class' => array('form-control'),'placeholder' => ''),
			
		);
		
	
  
    $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => ' Save'
    );


	return $form;	
}


function amendment_first_data_submit($form, &$form_state) {
	global $user;
	$val   						    =  $form_state['values'];
	//print_r($val);die;
	$uid 			    			=  $user->uid;
	
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	//$application_id 				=  created_appeno();
	$application_reference_no		=  created_referenceno();
	
	$is_generating					=  $val['is_generating'];
	$how_many_year					=  $val['how_many_year'];
	$factor_amenablity_date			=  $val['factor_amenablity_date'];

	
	$cafa_Info = array(
       						'date_of_amenability'		=>  date("Y-m-d", strtotime($factor_amenablity_date)),
							'period_for_application'	=>  $how_many_year,
							'is_worker_tab'				=>  1,
							'is_year_calculation_tab'	=>	1,
							'service_id' 				=> $service_id,
							'reference_number' 			=> $application_reference_no,
							'factory_typeid'			=> $factory_type_id
							
	    			);
		 $application_id= db_insert('fa_cafa')->fields($cafa_Info)->execute();

		//echo $factor_amenablity_date.'--'.$how_many_year.'--'.$service_id.'--'.$factory_type_id.'--'.$application_reference_no.'--'.$ $id;die;
		
		//del_year($ $application_id,$service_id,$factory_type_id,$application_reference_no);
		year_calculation_for_license_period($factor_amenablity_date,$how_many_year,$service_id,$factory_type_id,$application_reference_no,$application_id);

		//previous_calculation_for_license_period($vaild_license_date,$license_for_period,$service_id,$factorytype_id,$reference_no,$application_id);
		//drupal_set_message('Basic Information has been saved successfully.');
		//previous_calculation_for_license_period($factor_renewal_date,$previous_license_year,$service_id,$factory_type_id,$application_reference_no,$application_id);   

			  if($service_id==8){

		  $cafa_field = array(
			'app_id'			=> $application_id,
			'factory_type' 		=> $factory_type_id,
			'reference_no' 	 	=> $application_reference_no,
			'service_id'		=> $service_id,
			'fieldname'			=> 'ownership_type,factory_pan,gstin_no,udyog_aadhaar,factory_name',
			'application_status'=> NULL,
			'created_by'		=> $uid
			);
		
			$query_check_point 	=  db_select('fa_caf_check_point', 'check_point');
			$query_check_point	-> fields('check_point',array());
			$query_check_point	-> condition('check_point.factory_type', $factory_type_id);
			$query_check_point	-> condition('check_point.reference_no', $application_reference_no);
			$query_check_point	-> condition('check_point.app_id', $application_id);
			$query_check_point	-> condition('check_point.service_id', $service_id);
			$query_check_point	-> condition('check_point.created_by', $uid);
			
			$result_check_point =	$query_check_point->execute();
			$data_check_point	=	$result_check_point->fetchObject();
			if($result_check_point->rowCount() > 0) {
				$value = array('fieldname' => $val['fieldname']);
						
				$query_update 	=	db_update('fa_caf_check_point');
				$query_update	->	fields($value);
				$query_update	-> 	condition('factory_type', $factory_type_id);
				$query_update	-> 	condition('reference_no', $application_reference_no);
				$query_update	-> 	condition('app_id', $application_id);
				$query_update	-> 	condition('service_id', $service_id);
				$query_update	-> 	condition('created_by', $uid);
				$query_update	->	execute();
			} else {
				db_insert('fa_caf_check_point')->fields($cafa_field)->execute();
			}
			
			drupal_goto('applicant/check-amendment-year/'.encryption_decryption_fun('encrypt',$application_id).'/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.encryption_decryption_fun('encrypt',$application_reference_no)); 
		  
		  }
	
	
}

function created_appeno(){
	$max_id = '';
	$maxmum_id  = db_query("select max(id) as id from fa_cafa")->fetchObject()->id;
	 
	if($maxmum_id == NULL || empty($maxmum_id)){
		$max_id = 1;
	}else{
		$max_id = $maxmum_id+1;
		//echo $max_id; die('c');
	}
	return $max_id;
}