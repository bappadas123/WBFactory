<?php
function add_licence_register_page2($form, &$form_state,$lastid) {	

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	global $base_root, $base_path, $user;
	//$application_id		= encryption_decryption_fun('decrypt',$applicationid);
	//$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
//	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytypeid);
	//$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	$last_id 			= encryption_decryption_fun('decrypt',$lastid);
	
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
	$form['id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $lastid,
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
		'#default_value' 	=> '',
		
	 );
	 $form['licence_register']['schedule'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Schedule:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
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
		'#default_value' 	=> '',
		
	 );
	 $form['licence_register']['power'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Power:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['type'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('HP/KW:'),
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#type' 			=> 'select',
  		'#options' 			=> array(t('SELECT'), t('KW'), t('HP'),),
	 );
	 $form['licence_register']['worker'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('worker:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
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
		'#default_value' 	=> '',
		'#ajax'				=> array('callback'=> 'callback')
	 );
	 $form['licence_register']['licence_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(b). Licence Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['amendment_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(c). Amendment Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['transfer_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(d). Transfer Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['late_pay_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(e). Late Payment Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['loss_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(f). Loss Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'',),
		'#default_value' 	=> '',
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
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['chalan_no'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Serial no. in chalan register:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#description' 		=> '<span style="color:red">Chalan no need to add comma separated.</span>',
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['excess_paid_amount'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Excess amount paid:'),
		'#description' 		=> 'If any excess amount.',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#type' 			=> 'textfield',
		'#default_value' 	=> '',
	 );
	 $form['licence_register']['adjusted_amount'] = array(
        '#prefix' 			=> '<div class="col-md-3 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Excess amount adjusted:'),
        '#type' 			=> 'textfield',
		'#description' 		=> 'If adjusted against fee payable.',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
	 );
	 
	  $form['licence_register']['register_remark'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Register Remark:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '5',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
	 );
	 
	 $form['licence_register']['add'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#attributes' 		=> array('class' => array('btn bg-navy margin')),
        '#type' 			=> 'submit',
        '#value' 			=> 'Add Licence Register'
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
	
  $form['licence_register']['markup6']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
										<h5 class="box-title">View Details</h5>
			    					</div>
									<div class = "box-body">',
	);
	$form['licence_register']['view_register'] = array(
				'#prefix'		=> '<div class="col-md-12" id="view_register_details_id">',
				'#suffix' 		=> '</div>',
				'#type'			=> 'markup',
				'#markup'		=> display_licence_register($last_id),
				
			);
	$form['licence_register']['markup_end6'] 	= array(
		'#suffix' => '</div></div></div>',
	);
	
	return $form; 
}
	

function display_licence_register($last_id){
	
	$get_data = db_query("select * from {fa_licence_register_amount} WHERE register_id='".$last_id."'")->fetchAll();

	$Wcounter		= 0;
	$per_page		= 8;
	$current_page 	= pager_default_initialize(count($get_data), $per_page);
	
	$chunks 		= array_chunk($get_data, $per_page);
	
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header	= array(
			array('data' => 'Year'),
			array('data'=> 'HP/KW'),
			array('data'=> 'Power'),
			array('data'=> 'Amount of fees paid'),
			array('data'=> 'date of deposit'),
			array('data'=> 'Chalan Sl.No.'),
			array('data'=> 'Excess amount'),
			array('data'=> 'amount adjusted'),
			array('data'=> 'Enterd by'),
			array('data'=> 'Checked by'),
			array('data'=> 'Remarks'),
			array('data'=> 'Action'),
	);
	if(!empty($get_data)){
		
		foreach($chunks[$current_page] as $register_details){ 
			//echo $register_details->power_type;die;
			if($register_details->power_type == '1'){
				$type = 'HP';
			}elseif($register_details->power_type == '2'){
				$type = 'KW';
			}else{
				$type = '';
			}
			$name = get_name($register_details->uid);
			$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','del-licence-register-amount/'.encryption_decryption_fun('encrypt', $register_details->id).'/',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
			$rows[] 	= array( 
								array('data' =>$register_details->licence_period ,'class' => array('')),
								array('data' =>$register_details->power.'&nbsp;'.$type,'class' => array('')),
								array('data' =>$register_details->worker ,'class' => array('')),
								array('data' =>'(a)'.$register_details->register_fee.'<br/>(b)'.$register_details->renewal_fee.'<br/>(c)'.$register_details->amendment_fee.'<br/>(e)'.$register_details->transfer_fee.'<br/>(e)'.$register_details->late_pay_fee.'<br/>(f)'.$register_details->loss_fee,'class' => array('')),
								array('data' =>$register_details->deposit_date ,'class' => array('')),	
								array('data' =>$register_details->challan_no ,'class' => array('')),	
								array('data' =>$register_details->excees_fees ,'class' => array('')),	
								array('data' =>$register_details->adjusted_fees ,'class' => array('')),	
								array('data' =>$name,'class' => array('')),	
								array('data' =>$name,'class' => array('')),
								array('data' =>$register_details->register_remarks ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),	
								);
				} 
		
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_register_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
	}
	
function delete_licence_register_data($id){

	drupal_add_library('system', 'drupal.ajax');
	if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_licence_register_amount');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 		//$query->condition('reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
		 	$commands = array();
			$commands[] = ajax_command_replace('#view_register_details_id', "<div class='col-md-12 col-xs-12' id='view_register_details_id'>".display_licence_register(encryption_decryption_fun('decrypt', $id)).'</div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
		}
		
function add_licence_register_page2_submit($form, &$form_state){
	  global $user;
	  $val = $form_state['values'];
	  $uid = $user->uid;
	  
	 // print_r($val);die;
	  
	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_hidden']);
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['service_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_hidden']);
	  $last_id					=  	encryption_decryption_fun('decrypt',$val['id_hidden']); 
	 
	  
	  if($val['op']=='Add Licence Register'){
		 
			$licence_register_amount = array(
				'application_id'	=> NULL,
				'service_id'		=> NULL,
				'factorytype_id'	=> NULL,
				'reference_no' 	 	=> NULL,
				'register_id'		=> $last_id, 
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
			$id = db_insert('fa_licence_register_amount')->fields($licence_register_amount)->execute();	
			if(!empty($id)){
				$active = array('is_active' => 1);
				$query = db_update('fa_licence_register');
				$query->fields($active);
				$query->condition('id', $last_id, '=');
				$query->execute();
				
				 drupal_set_message('Amount register has been saved successfully.');
				}
			}
		
		if($val['op']=='Continue'){
			drupal_goto('regsection/licsection-dashboard');
			
		}
		$form_state['rebuild'] = true;
}

?>