<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function add_factory($form, &$form_state) {
	global $base_root,$base_path,$user;
	
	 $user_role = array_keys($user->roles);
      $urole  = $user_role[1];
	 $form['header']            = array(
        '#markup' => t('<div class="content"><h3>Add Factory details</h3></div>')
    );
	 $form['renewal_information']['registration_no'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(i).Registration Number'),
        '#type' 			=> 'textfield',
       
        '#default_value' 	=> $factory_name,
		'#attributes' 		=> array('class' => array( 'form-control')),
      
    );
	
	$form['renewal_information']['registration_date'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(ii).Registration Date'),
        '#type'				=> 'textfield',
        '#default_value' 	=> $factory_pan,
       
		'#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
		
    );
	 $form['renewal_information']['markup'] = array(
        '#prefix' 			=> '<div class="row">',
        '#suffix' 			=> '</div>',
       
      
    );
	
   $form['renewal_information']['license_no'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(iii).License Number'),
        '#type' 			=> 'textfield',
       
        '#default_value' 	=> $factory_name,
		'#attributes' 		=> array('class' => array( 'form-control')),
      
    );
	
	$form['renewal_information']['valid_upto'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(iv).Valid upto Date'),
        '#type'				=> 'textfield',
        '#default_value' 	=> $factory_pan,
       
		'#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
		
    );
	if($urole == 4){
		 $descriprtion 			= '<font color="black"><b>N.B.:-If factory does not exists on your dashboard, add your factory details by the given valid (registration number and date of registration) or (license number and validity date of the license) or both </b></font> ';
	}else{
		  $descriprtion 			= '<font color="black"><b>N.B.:-If factory does not exists in your factory list , please this factory details, by the given valid (registration number and date of registration) or (license number and validity date of the license) or both </b></font> ';
	}
	$form['renewal_information']['description'] = array(
              
        '#type'				=> 'markup',
        '#markup' 			=> $descriprtion
       
		
		
    );
	
	
	$form['renewal_information']['submit'] = array (
		'#prefix' 		=> '<div class="row"><div class="col-md-12">',
		'#suffix'		=> '</div></div</div><br>',
		'#type' 		=> 'submit',
		'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		'#value' 		=> 'Submit',
	
	);
	
	return $form;
	}

function add_factory_submit($form, &$form_state){
	global $user;
    $userid 			= $user->uid;
    $val    			= $form_state['values'];
	$license_no 		= $val['license_no'];
	$valid_upto 		= !empty($val['valid_upto'])?date('Y-m-d',strtotime($val['valid_upto'])):'';
	$reg_no 			= $val['registration_no'];
	$reg_date 			= !empty($val['registration_date'])?date('Y-m-d',strtotime($val['registration_date'])):'';
	$service_id			= 16;
	$uid 				= NULL;
	$zone_id			= NULL;
	$factoy_status		= '';
	$user_role = array_keys($user->roles);
    $urole  = $user_role[1];
	
	if(empty($license_no)&& empty($valid_upto) && empty($reg_no) && empty($reg_date)){
		 drupal_set_message('Please provided any two valid information','error');
	}
	if(!empty($license_no)&& empty($valid_upto)){
		 drupal_set_message('Please provided License validupto date','error');
	}
	if(!empty($reg_no)&& empty($reg_date)){
		 drupal_set_message('Please provided Registration date','error');
	}
	if(empty($license_no)&& !empty($valid_upto)){
		 drupal_set_message('Please provided License Number','error');
	}
	if(empty($reg_no)&& !empty($reg_date)){
		 drupal_set_message('Please provided Registration Number','error');
	}
	//echo $license_no.'--'.$valid_upto ;die;
	if(!empty($reg_no)&& !empty($reg_date)){
		$license_no = $reg_no;
		$valid_upto = $reg_date;
		$caf_data 	= fun_fetch_cafa($license_no,$valid_upto,$service_id,$uid,$zone_id);
		
	}if(!empty($license_no)&& !empty($valid_upto)){
		 $caf_data 	= fun_fetch_cafa($license_no,$valid_upto,$service_id,$uid,$zone_id);
	}
	

	if(empty($caf_data)){
		$tm_fact_data = fun_fetch_fact_tm($license_no,$valid_upto,$factoy_status);
		
		if(!empty($tm_fact_data)){
			$status = $tm_fact_data['status'];
			if($status == 'CROSSED OFF'){
				 drupal_set_message('Your factory does not exist.Contact to office ','error');
			}if($status == 'UNDER PROCESS'){
				 drupal_set_message('Your factory is in UNDER PROCESS status under any sevices.Either you can find it on your dashboard or it is not yours','error');
			}if($status == 'APPLICATION UNDER PROCESS'){
				 drupal_set_message('Your factory is in APPLICATION UNDER PROCESS status under any sevices.Either you can find it on your dashboard or it is not yours','error');
			}if($status == 'DISAPPROVED'){
				 drupal_set_message('Your factory is in DISAPPROVED status under any sevices.Either you can find it on your dashboard or it is not yours','error');
			}
			if($status == 'ACTIVE' || $status == 'PLAN APPROVED'){
				drupal_goto('applicant/add-factory-part1/'.encryption_decryption_fun('encrypt',$license_no).'/'.encryption_decryption_fun('encrypt',$valid_upto).'/'.encryption_decryption_fun('encrypt',$service_id));	
			}
			
		
		}else{
			 drupal_set_message('This is an invalid Licesne Number or registration number.Contact to office','error');
		}
	}else{
		 if($urole == 4){
				 if((empty($caf_data['created_by']) || $caf_data['created_by']==0) && $caf_data['factor_add_inspector']==1){
			 		drupal_goto('applicant/backlog-factory-add/default/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$caf_data['factory_typeid']).'/'.encryption_decryption_fun('encrypt',$caf_data['id']).'/'.encryption_decryption_fun('encrypt',$caf_data['reference_number']));	
			
				}else{
			 if($urole == 4){
				 drupal_set_message('This factory is already exists. Either you can find it on your dashboard or it is not yours. ','warring');
			}else{
		 		 drupal_set_message('This factory is already exists.  you can find it in List of Active factories.  ','warring');
		}
 
			
			
		}
		}
		else{
			 if($urole == 4){
				 drupal_set_message('This factory is already exists. Either you can find it on your dashboard or it is not yours ','warring');
			}else{
		 		 drupal_set_message('This factory is already exists.  you can find it in List of Active factories  ','warring');
		}
 
			
			
		}
		
	}
		
	
}

?>