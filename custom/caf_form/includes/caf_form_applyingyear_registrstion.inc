<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_applyingyear_registrstion($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp)
{
    global $base_root, $base_path;
   //print_r($_SESSION['is_power_value']);die();
    $form           	= array();
	$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
	 $factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid); 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$link_number 		= encryption_decryption_fun('decrypt', $linknumber);
	$flag_mapp 			= encryption_decryption_fun('decrypt', $flagmapp);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }
  
    $form['serviceid_hidden']     = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid
    );
    $form['factorytypeid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $factory_typeid
    );
	 $form['applicationid_hidden'] = array(
		 '#type' 			=> 'hidden',
		 '#default_value' 	=> $applicationid
    );
	$form['linknumber_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $linknumber
    );
	$form['flagmapp_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $flagmapp
    );
	
  
  	$get_fa_cafa 				= get_fa_cafa($application_id);
	
	
 	$reference_number 			= $get_fa_cafa['reference_number'];
 	$date_of_amenability       	= $get_fa_cafa['date_of_amenability'];
	$period_for_application     = $get_fa_cafa['period_for_application'];
	$application_status         = $get_fa_cafa['application_status'];
	$owership_type				= $get_fa_cafa['factory_owershiptype'];
	$factory_name				= $get_fa_cafa['factory_name'];
	$created_date				= $get_fa_cafa['created_date'];
 /********** Factory checking data **********/
	if (!empty($application_id) && $get_fa_cafa['application_status']=='B') {
	$checked =get_checking($application_id,$service_id,$factory_type_id,$reference_number);
	
	$verify_details      = ($checked['verify_details'])? $checked['verify_details'] : ''; 
	
	$remark_field = explode(',', $checked['verify_details']);
			foreach ($remark_field as $fieldname){
				if($fieldname == 'date_of_amenability_id'){ $date_of_amenability_ck = "disabled";}				
				if($fieldname == 'period_for_application_id'){ $period_for_application_ck = "disabled";}
				if($fieldname == 'ownership_type'){ $ownership_type_ck = "disabled";}
			}
	 }
 
 $form['reference_no_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number)
    );
    
 
    $form['application_status_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $application_status)
        
    );
	
	$form['factory_name_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $factory_name)
        
    );
	$form['owership_type_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $owership_type)
        
    );
	$form['created_date_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $created_date)
        
    );
	
        
  $form['factory_part_info']['header'] 	= array(
		'#type'				=> 'markup',
		'#prefix'			=> '<h3>F. State the period of license</h3><div class="row">'
			);	
	 $year_data 			= fetch_year_asc($application_id,$service_id,$factory_type_id,$reference_number);
	//print_r($year_data);die();
 if(empty($application_status) || $application_status == 'In'){
	 $form['factory_part_info']['factor_amenablity_date'] = array(
		'#prefix' 			=> 	'<div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">',
		'#suffix' 			=> 	'</div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t('(i). Date from which the premises is occupied or been taken into use as factory'),
		'#required' 		=>  TRUE,
		'#default_value' 	=>  $date_of_amenability,
		'#attributes' 		=> 	array('class' => array('form-control datepicker'),'placeholder' => '','readonly' => 'readonly'),
			
		);
	$form['factory_part_info']['how_many_year'] 	= array(
		'#prefix' 			=> '<div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">',
		'#suffix' 			=> '</div>',
		'#type' 			=> 'textfield',
		'#maxlength' 		=> 2,
		'#required' 		=> TRUE,
		'#element_validate'	=> array('isnumaric_valiadtion'),  
		'#title'			=>	t('(ii). State the period of license required for date from application date'),
		'#description'		=> t('<font color="#FF0000">(N.B.:- Maximun 15 years)</font>'),
		'#attributes' 		=> 	array('class' => array('form-control'),'placeholder' => ''),
		'#default_value' 	=> $period_for_application
	  );
	}else{
		$form['factory_part_info']['factor_amenablity_date'] = array(
		'#prefix' 			=> 	'<div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">',
		'#suffix' 			=> 	'</div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t('(i). Date from which the primises is occupied or been taken into use as factory'),
		'#required' 		=>  TRUE,
		'#default_value' 	=>  $date_of_amenability,
		'#attributes' 		=> 	array('class' => array('form-control datepicker'),'placeholder' => '','readonly' => 'readonly'),
		'#description'		=>  t('N.B.:- You can not change the date'),
		);
	$form['factory_part_info']['how_many_year'] 	= array(
		'#prefix' 			=> '<div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">',
		'#suffix' 			=> '</div>',
		'#type' 			=> 'textfield',
		'#maxlength' 		=> 2,
		'#required' 		=> TRUE,
		'#element_validate'	=> array('isnumaric_valiadtion'), 
		'#title'			=>	t('(ii). State the period of license required'),
		'#description'		=> t('<font color="#FF0000">(N.B.:- Maximun 15 years)</font>'),
		'#attributes' 		=> 	array('class' => array('form-control'),'placeholder' => '','readonly' => 'readonly'),
		'#default_value' 	=> $period_for_application
	  );
	}
 
  
	/*$form['factory_part_info']['back_link']	 = array(
			  '#prefix' 		=> '<div class="col-xs-6">',	
			  '#suffix' 		=> '</div>',
			  '#type' 			=> 'markup',
			  '#markup' 		=> l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
		);*/
		
		$form['factory_part_info']['markup_1'] = array(
					//'#prefix' 		=> '<div class="row">',
					
				);
	 if($application_status == 'B' || $application_status == 'In' || empty($$application_status)){
		 $is_year = fetch_year($application_id,$service_id,$factory_type_id,$reference_number);
		
		 foreach($is_year as $exists_year){
			 $is_exists_year = $exists_year->calculate_year;
			 
		 }
		 if(empty($date_of_amenability_ck) || empty($period_for_application_ck)){
		 if(empty($is_exists_year)){
			 $form['factory_part_info']['submit'] = array(
				'#prefix' 		=> '<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-dark pull-right')),
				'#type' 		=> 'submit',
				'#value' 		=> 'Calculate'
				);
		 }else{
			 $form['factory_part_info']['reset_year'] = array(
				'#prefix' 		=> '<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-dark pull-right')),
				'#type' 		=> 'submit',
				'#value' 		=> 'Reset Year'
				);
		 }
	}
		 	 
		$form['factory_part_info']['markup_2'] = array(
				'#suffix' 		=> '</div>',
					
				);	
	 }
	 
	 $form['factory_part_info']['year_break_up'] 	= array(
				'#prefix' 		=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
				'#suffix' 		=> '</div></div>',
				'#type'			=> 'markup',
				'#markup'		=> view_break_licese_period($application_id,$service_id,$factory_type_id,$reference_number)
				
  
			);
	$previous_details =  get_previous_details_view($application_id,$reference_number,$factory_type_id,$service_id);
	//print_r($previous_details);die();
	foreach($previous_details as $pre_row){
		$is_previous		 	= $pre_row->conversation_ownership_type;
		$change_date 			= $pre_row->change_date;
		$ownership_type 		= $pre_row->ownership_type;
		$pervious_factory_name	= $pre_row->pervious_factory_name;
		$service_year			= $pre_row->service_year;
		$same_as_pre_details	= $pre_row->same_as_pre_details;
	}
	 $ownershiptype  = array(
		"pv" 			=> "Pvt Ltd Company",
		"ltd" 			=> "Ltd Company",
		"par_firm" 		=> "Partnership Firm",
		"pro_firm" 		=> "Proprietorship Firm",
		
 
    );
	//echo $is_previous;die();

	if(!empty($ownership_type_ck)){
		$radios_options = array(''=>"Select",'pv'=>"Public to Private",'ltd'=>"Private to Public",'par_firm' =>"Partnership to Proprietorship Firm",'pro_firm' => "Proprietorship to Partnership Firm",'pv_par'=>"Partnership to Private",'par_ltd'=>"Partnership to Public", 'pv_pro'=>"Proprietorship to Private",'ltd_pro'=>"Proprietorship to Public",'pro_pri'=>"Private to Proprietorship",'pro_ltd'=>"Public to Proprietorship",'pri_par'=>"Private to Partnership",'ltd_par'=>"Public to Partnership","amal" => "Amalgamation");
	}else{
		$radios_options = array(''=>"Select",'pv'=>"Public to Private (Vise versa)",'par_firm' =>"Partnership to Proprietorship Firm (Vise versa)",'pv_par'=>"Partnership to Private (Vise versa)",'par_ltd'=>"Partnership to Public (Vise versa)", 'pv_pro'=>"Proprietorship to Private (Vise versa)",'ltd_pro'=>"Proprietorship to Public (Vise versa)","amal" => "Amalgamation","name"=>"Name change (ex:- XYZ ltd to YZX ltd)");
	}
 
	 $form['factory_part_info']['is_previous']= array(
		'#prefix' 			=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
		'#suffix' 			=> '<div></div>',
		'#type' 			=> 'select',
		'#title'			=>	t('(iii).Change in name of factory from'),
		'#attributes' 		=> 	array('class' => array('form-control')),
		'#options'   		=> $radios_options,	
		'#default_value' 	=> $is_previous,
		'#ajax'				=> array(
								'event' 		=> 'change',
								'effect' 		=> 'fade',			
								'callback'		=> 'previous_name_ajax',
								'progress'		=>	array(
								'type'			=>'throbber',
								'message'		=> t('loading'),
						),
		)
					
			   
	 );
	 $is_previous_value = isset($form_state['values']['is_previous'])? $form_state['values']['is_previous'] : $is_previous;
	 $form['factory_part_info']['year_deatils'] = array(
		'#prefix' 			=> '<div class="row"><div id="year_deatils_div">',
		'#suffix' 			=> '</div>',
		   
	 );
	 $form['factory_part_info']['change_date'] = array(
		'#prefix' 			=> '<div id="change_date_div">',
		'#suffix' 			=> '</div>',
		   
	);
	/*$form['factory_part_info']['ownership_type'] = array(
		'#prefix' 			=> '<div id="ownership_type_div">',
		'#suffix' 			=> '</div>',
		   
	);*/
	$form['factory_part_info']['previous_name'] = array(
		'#prefix' 			=> '<div id="previous_name_div">',
		'#suffix' 			=> '</div>',
		   
     );
	$form['factory_part_info']['previous_ownership'] = array(
		'#prefix' 			=> '<div id="previous_ownership_div">',
		'#suffix' 			=> '</div>',
		   
    );
	$form['factory_part_info']['conversation_name'] = array(
		'#prefix' 			=> '<div id="conversation_name_div">',
		'#suffix' 			=> '</div>',
		   
		 );
		  $form['factory_part_info']['conversation_ownership'] = array(
		'#prefix' 			=> '<div id="conversation_ownership_div">',
		'#suffix' 			=> '</div>',
		   
		 );
		  $form['factory_part_info']['addr_same'] = array(
		'#prefix' 			=> '<div id="addr_same_div">',
		'#suffix' 			=> '</div>',
		   
		 );
		 
		 $form['factory_part_info']['add_details'] = array(
		'#prefix' 			=> '<div id="add_details_div">',
		'#suffix' 			=> '</div>',
		   
		 );
		 $form['factory_part_info']['view_previous_details'] 	= array(
		'#prefix' 			=> '<div id ="view_previous_details_id" class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
		'#suffix' 			=> '</div>',
		'#type'				=> 'markup',
		'#markup'			=> view_previous_details($application_id,$reference_number,$factory_type_id,$service_id)
				
  
			);
			
		$is_year = fetch_year($application_id,$service_id,$factory_type_id,$reference_number);
		
		 foreach($is_year as $exists_year){
			 $is_exists_year = $exists_year->calculate_year;
			 
		 }
		// echo $is_exists_year;die();
		 if(!empty($is_exists_year)){
			  $form['factory_part_info']['save_details'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
		'#suffix' 			=> '</div></div>',
		'#attributes' 		=> array('class' => array('btn btn-dark pull-right')),
		'#type' 			=> 'submit',
		'#value' 			=> 'Save & Continue'
								);
		 }
		 
		 /*$form['factory_part_info']['save_details'] = array(
			'#prefix' 			=> '<div id="save_details_div">',
			'#suffix' 			=> '</div>',
		   
		 );*/
	 if($is_previous_value == 'pv' ||$is_previous_value == 'par_firm' || $is_previous_value == 'pv_par' || $is_previous_value == 'par_ltd' || $is_previous_value == 'pv_pro' || $is_previous_value == 'ltd_pro' ||$is_previous_value == 'amal'  ||  $is_previous_value == 'name'){
		 if($is_previous_value == 'pv'){
			 $ownershiptype  = array(
				"pv" 			=> "Pvt Ltd Company",
				"ltd" 			=> "Ltd Company",
		  );
		 }if($is_previous_value == 'par_firm'){
			 $ownershiptype  = array(
				"par_firm" 		=> "Partnership Firm",
				"pro_firm" 		=> "Proprietorship Firm",
		  );
		 }if($is_previous_value == 'pv_par'){
			 $ownershiptype  = array(
				"par_firm" 		=> "Partnership Firm",
				"pv" 			=> "Pvt Ltd Company",
		  );
		 }if($is_previous_value == 'par_ltd'){
			 $ownershiptype  = array(
				"par_firm" 		=> "Partnership Firm",
				"ltd" 			=> "Ltd Company",
		  );
		 }if($is_previous_value == 'pv_pro'){
			 $ownershiptype  = array(
				"pro_firm" 		=> "Proprietorship Firm",
				"pv" 			=> "Pvt Ltd Company",
		  );
		 }if($is_previous_value == 'ltd_pro'){
			 $ownershiptype  = array(
				"pro_firm" 		=> "Proprietorship Firm",
				"ltd" 			=> "Ltd Company",
		  );
		 }
		  $year_data 			= fetch_year_asc($application_id,$service_id,$factory_type_id,$reference_number);
  		  $current_year 		= date("Y");
		  $current_date 		= date("Y-m-d");
		  $i 					= 1;
		  $calculate_year_array	= array();
		 foreach($year_data as $row){
			 //echo $row->calculate_end_year;echo '<br/>';
			$calculate_starting		= ($row->calculate_starting_year);
			//$r						= validateDate($calculate_starting, 'Y-m-d');
			//$datex 					= new DateTime($current_date);
			//$datey 					= new DateTime($row->calculate_starting_year);
			//$datez 					= new DateTime($row->calculate_end_year);
			//if($datez<$datex){
			 $calculate_year_array[$row->id] = t('@year', array('@year' => $row->calculate_year));
			 //}
			/*if($r==1){
			 	if($datez>$datex){
			 	
		 	 	}if($datez<$datex){
					 $calculate_year_array[$row->calculate_year] = t('@year', array('@year' => $row->calculate_year));
			 }
			}else{
			   if($calculate_starting<$current_year){
					 $calculate_year_array[$row->calculate_year] = t('@year', array('@year' => $row->calculate_year));
			  }
		}*/
		
	}
		 
	$form['factory_part_info']['year_deatils'] 	= array(
			'#prefix' 	 		=> '<div id="year_deatils_div" class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div>',
			'#type' 			=> 'select',
			'#title'			=>	t('(a). Application Period'),
			'#attributes' 		=> 	array('class' => array('form-control range')),
			'#required'			=> TRUE,
			//'#multiple'		=> TRUE,
			'#id'				=> 'dates',
			'#default_value' 	=> $service_year,
			'#options' 	 		=> $calculate_year_array//($application_id,$service_id,$factory_type_id,$reference_number), 
			);
	$form['factory_part_info']['change_date'] 	= array(
			'#prefix' 	 		=> '<div id="change_date_div" class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div>',
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE, 
			'#default_value' 	=> $change_date,
			'#title'			=>	t('(b). Change Date'),
			'#attributes' 		=> 	array('class' => array('form-control datepicker_cls'),'placeholder' => '','readonly' => 'readonly'),
			 
	  	);
	/*$form['factory_part_info']['ownership_type'] 	= array(
			'#prefix' 	 		=> '<div id="ownership_type_div" class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div>',
			'#type' 	 		=> 'select',
			'#title'			=>	t('(c). Ownership Type'),
			'#attributes' 		=> 	array('class' => array('form-control')),
			'#required'			=> TRUE,
			'#default_value' 	=> $ownership_type,
			'#options' 	 		=> $ownershiptype, 
			);*/
		$form['factory_part_info']['previous_name'] 	= array(
			'#prefix' 	 		=> '<div id="previous_name_div"><div class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div></div>',
			'#type' 	 		=> 'textfield',
			'#title'			=>	t('(d). Previous Name'),
			'#attributes' 		=> 	array('class' => array('form-control')),
			'#required'			=> TRUE,
			'#default_value' 	=> $pervious_factory_name,
  				 
			);
		$form['factory_part_info']['previous_ownership'] 	= array(
			'#prefix' 	 		=> '<div id="previous_ownership_div"><div class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div></div>',
			'#type' 	 		=> 'select',
			'#title'			=>	t('(d).Ownership type of previous name'),
			'#attributes' 		=> 	array('class' => array('form-control')),
			'#required'			=> TRUE,
			'#options' 	 		=> $ownershiptype, 
  				 
			);
	$form['factory_part_info']['conversation_name'] 	= array(
			'#prefix' 	 		=> '<div id="conversation_name_div"><div class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div></div>',
			'#type' 	 		=> 'textfield',
			'#title'			=>	t('(d). New Name'),
			'#attributes' 		=> 	array('class' => array('form-control')),
			'#required'			=> TRUE,
			'#default_value' 	=> $pervious_factory_name,
  				 
			);
			
			$form['factory_part_info']['conversation_ownership'] 	= array(
			'#prefix' 	 		=> '<div id="conversation_ownership_div"><div class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div></div>',
			'#type' 	 		=> 'select',
			'#title'			=>	t('(d).Ownership type after conversion'),
			'#attributes' 		=> 	array('class' => array('form-control')),
			'#required'			=> TRUE,
			'#options' 	 		=> $ownershiptype, 
  				 
			);
			
		/*$form['factory_part_info']['addr_same'] = array(
			'#prefix' 	 		=> '<div id="addr_same_div"><div class="col-lg-3 col-md-3 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div></div>',
			'#type' 			=> 'checkbox',
			'#default_value' 	=> $same_as_pre_details,
			
			'#title' 			=> t('(e). Same as for all application period'),
        		
    );*/
	$form['factory_part_info']['add_details'] 	= array(
			'#type' 			=> 'submit',
			'#submit'			=> array(),
			'#ajax' 			=> array(
			'callback' 			=> 'add_pre_details',
									),
			'#value' 			=> t('Add details'),
			'#attributes' 		=> array('class' => array('btn btn-dark pull-right')),
			'#prefix' 	 		=> '<div id="add_details_div"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
			'#suffix' 	 		=> '</div></div>',
	);
	
	 }
	
	 
	 if($is_previous_value == 'No'){
		  $form['factory_part_info']['year_deatils'] = array(
			'#prefix' 			=> '<div id="year_deatils_div">',
			'#suffix' 			=> '</div>',
		   
		 );
		 $form['factory_part_info']['change_date'] = array(
			'#prefix' 			=> '<div id="change_date_div">',
			'#suffix' 			=> '</div>',
		   
		 );
		/* $form['factory_part_info']['ownership_type'] = array(
			'#prefix' 			=> '<div id="ownership_type_div">',
			'#suffix' 			=> '</div>',
		   
		 );*/
		 $form['factory_part_info']['previous_name'] = array(
			'#prefix' 			=> '<div id="previous_name_div">',
			'#suffix' 			=> '</div>',
		   
		 );
		  $form['factory_part_info']['addr_same'] = array(
			'#prefix' 			=> '<div id="addr_same_div">',
			'#suffix' 			=> '</div></div>',

		   
		 );
		 $form['factory_part_info']['add_details'] = array(
			'#prefix' 			=> '<div id="add_details_div">',
			'#suffix' 			=> '</div>',
		   
		 );
		
	 }
	 
    $form['factory_part_info']['markup_end'] = array (
			//'#prefix' 		=> '',  
			'#prefix' 			=> '</div></div></div>',
			'#type' 			=> 'markup',
	   		
		); 
  return $form;  
}

function add_pre_details($form, &$form_state){
	
	global $user;
	
	$val   								= 	$form_state['values'];
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);	
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$factory_name_hidden				= 	encryption_decryption_fun('decrypt',$val['factory_name_hidden']);
	$owership_type_hidden				= 	encryption_decryption_fun('decrypt',$val['owership_type_hidden']);
	$created_date_hidden				= 	encryption_decryption_fun('decrypt',$val['created_date_hidden']);
	$is_previous						= 	$val['is_previous'];
	$service_year						= 	$val['year_deatils'];
	$change_date						= 	$val['change_date'];
	$conversation_ownership				= 	$val['conversation_ownership'];
	$previous_ownership					= 	$val['previous_ownership'];
	$pervious_factory_name				= 	$val['previous_name'];
	$conversation_name_name				= 	$val['conversation_name'];
	$same_as_pre_details				= 	$val['addr_same'];
	$current_date 						=   date('Y-m-d');
	$transfer_fees 						= 	1000;
	 if($is_previous == 'pv'){
		 $description_conversation			=	"Public to Private (Vise versa)";
	 }if($is_previous == 'par_firm'){
		 $description_conversation			=	"Partnership to Proprietorship Firm (Vise versa)";
	 }if($is_previous == 'pv_par'){
		 $description_conversation			=	"Partnership to Private (Vise versa)";
	 }if($is_previous == 'par_ltd'){
		 $description_conversation			=	"Partnership to Public (Vise versa)";
	 }if($is_previous == 'pv_pro'){
		 $description_conversation			=	"Proprietorship to Private (Vise versa)";
	 }if($is_previous == 'ltd_pro'){
		 $description_conversation			=	"Proprietorship to Public (Vise versa)";
	 }if($is_previous == 'amal'){
		 $description_conversation			=	"Amalgamation";
	 }if($is_previous == 'name'){
		 $description_conversation			=	"Name change (ex:- XYZ ltd to YZX ltd)";
		 $transfer_fees = 0;
	 }
	
	$year_id							= 	fetch_year_details_withid($service_year);
	
	$previos_name =array(
						'pervious_factory_name' 		      => $pervious_factory_name,
						'change_date'						  => $change_date ,
						'conversation_ownership_type'		  => $conversation_ownership,
						'service_id' 		             	  => $service_id,
						'application_id'              		  => $application_id,
						'name_application_status' 	  		  => 'In',
						'factory_type'				     	  => $factory_type,
						'created_by'				          => $user->uid,
						'service_year'				          => $year_id['calculate_year'],
						'application_reference_no'			  => $reference_no,
						'name_active_inactive'				  => $year_id['is_active_year'],
						'is_change'							  => 1,
						'transfer_fees'						  =>  $transfer_fees,
						'valid_time_period'					  =>  $year_id['valid_time_period'], 
						'is_previous'						  =>  'No',
						'valid_year'						  =>  $year_id['calculate_end_year'],	
						'starting_year'						  =>  $year_id['calculate_starting_year'],
						'calculate_year_id'					  =>  $service_year,
						'created_date'						  =>  date('Y-m-d'),
						'conversation_name'					  => $conversation_name_name,
						'previous_ownership'				  =>  $previous_ownership,
						'type_of_conversation'				  =>  $is_previous,
						'description_conversation'			 => $description_conversation,
						
				
			);
			
			$id = db_insert('fa_factory_previous_name')->fields($previos_name)->execute();
	
	if($id){
		$commands[] = ajax_command_replace('#view_previous_details_id', '<div id="view_previous_details_id"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">'.view_previous_details($application_id,$reference_no,$factory_type,$service_id).'</div></div>');
		
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	
	
	
}

function previous_name_ajax($form, $form_state){ 
	
	$commands = array();
	$commands[] = ajax_command_replace('#year_deatils_div', drupal_render($form['factory_part_info']['year_deatils']));
	$commands[] = ajax_command_replace('#previous_ownership_div', drupal_render($form['factory_part_info']['previous_ownership']));
	$commands[] = ajax_command_replace('#conversation_ownership_div', drupal_render($form['factory_part_info']['conversation_ownership']));
	$commands[] = ajax_command_replace('#change_date_div', drupal_render($form['factory_part_info']['change_date']));
	//$commands[] = ajax_command_replace('#ownership_type_div', drupal_render($form['factory_part_info']['ownership_type']));
	$commands[] = ajax_command_replace('#previous_name_div', drupal_render($form['factory_part_info']['previous_name']));
	$commands[] = ajax_command_replace('#add_details_div', drupal_render($form['factory_part_info']['add_details']));
	$commands[] = ajax_command_replace('#addr_same_div', drupal_render($form['factory_part_info']['addr_same']));
	$commands[] = ajax_command_replace('#conversation_name_div', drupal_render($form['factory_part_info']['conversation_name']));
	return array('#type' => 'ajax', '#commands' => $commands);
} 
function view_break_licese_period($application_id,$service_id,$factory_type_id,$reference_number){
	$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'Sl. No.','width'=> '4%'),
		array('data'=> 'License Period','width'=> '42%'),
		array('data'=> 'License valid for'),
		array('data'=> 'Remark','width'=> '10%'),
		
	);
	$fetch_year	=	fetch_year($application_id,$service_id,$factory_type_id,$reference_number);
	
	foreach($fetch_year as $year){
		$sl				= $sl+1;	
		$is_active_year	= $year->is_active_year;
		if($is_active_year == 1){
			$Remark = "Application period";
			$vaild_period = $year->showing_year .'year(s)';
		}else{
			$Remark = "Previous 12 months";
			$vaild_period = 0;
			
		}
		
		$rows [] = array(  
			array('data' => $sl), 	
			array('data' => t($year->calculate_year)), 
			array('data' => t($vaild_period)), 
			array('data' => t($Remark)), 
			
			//array('data' => $delLink),	
		);
		
	}
	$output = theme_table(
	array(
		  'header' 		=> $header,
		  'rows' 		=> $rows,
		  'attributes' 	=> array('id'=>'table_div_replace', 'class' => array('table', 'no-margin', 'custom-table-view-dashboard')),
		  'sticky' 		=> true,
		  'caption' 	=> '',
		  'colgroups' 	=> array(),
		  'empty' 		=> t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	  
	return $output;	
}  
function caf_form_applyingyear_registrstion_submit($form, &$form_state){

    global $user;
   	 $userid 					= $user->uid;
     $val    					= $form_state['values']; 
	 $date_of_amenability		= $val['factor_amenablity_date'];
	 $period_for_application	= $val['how_many_year'];
	
	 $reference_number          = encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	 $service_id				= encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
     $factory_typeid 		    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']); 
	 $application_status 		= empty( $val['application_status_hidden'])?'':encryption_decryption_fun('decrypt', $val['application_status_hidden']);
  	 $application_id 			= empty($val['applicationid_hidden'])?'':encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	 $is_previous				= $val['is_previous'];
	 $factory_name_hidden		= encryption_decryption_fun('decrypt',$val['factory_name_hidden']);
	 $owership_type_hidden		= encryption_decryption_fun('decrypt',$val['owership_type_hidden']);
	 $created_date_hidden		= encryption_decryption_fun('decrypt',$val['created_date_hidden']);
	if($val['op']=='Reset Year'){
		
		 // print_r($val);die();
		$cal_year = fetch_year($application_id,$service_id,$factory_typeid,$reference_number);
		
		
		foreach($cal_year as $row_year){
			$cal_year_id = $row_year->id;
			common_del_function($cal_year_id,'fa_factory_previous_name',$application_id);
			common_del_function($cal_year_id,'fa_worker_details',$application_id);
			common_del_function($cal_year_id,'fa_calculate_year',$application_id);
			common_del_function($cal_year_id,'fa_director_details',$application_id);
			common_del_function($cal_year_id,'fa_occupier_details',$application_id);
			common_del_function($cal_year_id,'fa_manager_details',$application_id);
			common_del_function($cal_year_id,'fa_nature_manufacturing',$application_id);
		}
		//$val['op']=""; 
	 }
	
	else if($val['op']=='Save & Continue'){
		
		$cafa_Info = array('is_year_calculation_tab'=>1);
		$queryabc = db_update('fa_cafa');
        $queryabc->fields($cafa_Info);
        $queryabc->condition('id', $application_id, '=');
        $queryabc->execute();
		
		     
     drupal_goto('applicant/caf-reg/details-worker-registration/' . $val['serviceid_hidden'] . '/' . $val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['linknumber_hidden'].'/'.$val['created_date_hidden'].'/'.$val['flagmapp_hidden']);
		
	 }
	else{ 
	 
	if($period_for_application!= 0 && ($period_for_application<=15)){
		$cafa_Info = array(
       						'date_of_amenability'		=>date("Y-m-d", strtotime($date_of_amenability)),
							'period_for_application'	=> $period_for_application
	    			);
  
		$queryabc 	= 	db_update('fa_cafa');
		$queryabc	->	fields($cafa_Info);
		$queryabc	->	condition('id', $application_id, '=');
		$queryabc	->	execute();
		$is_year	= 	is_year($application_id,$service_id,$factory_typeid,$reference_number);
	
	if($is_year>0){
		
		del_year($application_id,$service_id,$factory_typeid,$reference_number);
		create_validate_year1($date_of_amenability,$period_for_application,$val['serviceid_hidden'],$val['factorytypeid_hidden'],$reference_number,$application_id);
			
			
		
	}else{
		create_validate_year1($date_of_amenability,$period_for_application,$val['serviceid_hidden'],$val['factorytypeid_hidden'],$reference_number,$application_id);
	}
   	
	}else{
		drupal_set_message('The period of license period should be less them or equal to 15 years','error');
	}
	  
		}
      
  
    
    
 
}

function view_previous_details($application_id,$reference_number,$factory_type_id,$service_id){
	$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'Sl. No.','width'=> '4%'),
		array('data'=> 'Application Period','width'=> '34%'),
		array('data'=> 'Change Date','width'=> '10%'),
		array('data'=> 'Previous Name','width'=> '34%'),
		array('data'=> 'Conversion Name','width'=> '34%'),
		array('data'=> 'Transfer Fees','width'=> '20%'),
		
	);
	$pre_view	=	get_previous_details_view($application_id,$reference_number,$factory_type_id,$service_id);
	//print_r($pre_view);die();
	
	foreach($pre_view as $view){
		$sl= $sl+1;	
		if($view->conversation_ownership_type=="pv"){
			$conversation_ownership_type = "Pvt Ltd Company";
		}if($view->conversation_ownership_type=="ltd"){
			$conversation_ownership_type = "Ltd Company";
		}if($view->conversation_ownership_type=="par_firm"){
			$conversation_ownership_type = "Partnership Firm";
		}if($view->conversation_ownership_type=="pro_firm"){
			$conversation_ownership_type = "Proprietorship Firm";
			
		}if($view->previous_ownership=="pv"){
			$previous_ownership_type = "Pvt Ltd Company";
		}if($view->previous_ownership=="ltd"){
			$previous_ownership_type = "Ltd Company";
		}if($view->previous_ownership=="par_firm"){
			$previous_ownership_type = "Partnership Firm";
		}if($view->previous_ownership=="pro_firm"){
			$previous_ownership_type = "Proprietorship Firm";
		}
		$change_date =  date('dS M Y', strtotime($view->change_date));
		
		$rows [] = array(  
			array('data' => $sl), 	
			array('data' => t($view->service_year)),
			array('data' =>	$change_date) ,
			array('data' => t($view->pervious_factory_name)),
			array('data' => t($view->conversation_name)),
			array('data' => t($view->transfer_fees)), 
			
			//array('data' => $delLink),	
		);
		
	}
	$output = theme_table(
	array(
		  'header' 		=> $header,
		  'rows' 		=> $rows,
		  'attributes' 	=> array('id'=>'table_div_replace', 'class' => array('table', 'no-margin', 'custom-table-view-dashboard')),
		  'sticky' 		=> true,
		  'caption' 	=> '',
		  'colgroups' 	=> array(),
		  'empty' 		=> t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	  
	return $output;	
}
?> 