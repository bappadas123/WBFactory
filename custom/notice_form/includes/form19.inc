<?php 
 //drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
 drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
 function form19_form($form, &$form_state, $formid ,$referenceid, $factorytypeid, $serviceid){
	  
	  global	$user;
	  $uid	= $user->uid;
	  $form = array();

	$form_id 	 	= encryption_decryption_fun('decrypt', $formid);
	$reference_id   = encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;
 
	if($form_id != '')
	  { 
		$get_all_data 		= get_dangerous_occurence_details($form_id,$reference_id,$factory_typeid,$service_id);
		$get_occurence_data = get_occurence_data($form_id);
//print_r($get_occurence_data);
		$Factoryid       = $get_all_data[0]->factory_id;
		$FactoryTypeid   = $get_all_data[0]->factory_typeid;
		$FactoryZone	 = $get_all_data[0]->factory_zone;
		$ReferenceNumber = $get_all_data[0]->reference_number;
		$FactoryName     = $get_all_data[0]->factory_name;
		$IndustryNature  = $get_all_data[0]->nature_manufacturing;
		$OccurrenceDate  = trim(implode('-', array_reverse(explode('-', $get_all_data[0]->date_occurrence))));
		$OccurrenceTime  = $get_all_data[0]->time_occurrence;
		$BranchName  	 = $get_all_data[0]->branch_name;
		$FullAccount	 = $get_all_data[0]->full_account;
	  } 
		
		//echo "<pre>"; print_r($get_all_data);

		$form['formid_hidden'] 		= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $formid
		);	
	$form['serviceid_hidden'] 		= array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $serviceid
	);

	$form['dangerous_occurrence'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Notice of dangerous occurrence which does not result in death or bodily injury'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);

	$option = array( "Yes" => "Yes", "No" => "No");
	$form['dangerous_occurrence']['is_registered'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-3 col-xs-6"><label class="select label-block">',
        '#suffix' 			=> '</label></div>',
		'#title' 			=> t('(i) Is it a registered factory ?'),
		'#options'			=> $option,
		'#type' 			=> 'radios',
		'#required' 		=> TRUE,
		'#default_value' 	=> !empty($get_all_data[0]->is_registered) ? $get_all_data[0]->is_registered : '',
		'#ajax' 			=> array(
								'event' 		=> 'change',
								'effect' 		=> 'fade',
								'callback' 		=> 'get_ajax_name_factory',
								'progress' 		=> array(
								'type' 			=> 'throbber',
								'message' 		=> t('loading')
							)
			 )
	);
	
	$value_is_registered = isset($form_state['values']['is_registered']) ? $form_state['values']['is_registered'] : $get_all_data[0]->is_registered;
	
	if($value_is_registered =='Yes' )//|| $get_all_data[0]->is_registered =='Yes'
	{
		$form['dangerous_occurrence']['factory_id'] = array(
			'#prefix' 			=> '<div id="factory_id_id"><div class="col-md-4 col-xs-6"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(ii) Choose Factory Registration & License No.'),
			'#attributes' 		=> array('class' => array( '')),
			//'#options' 			=> get_factory_name($uid),
			'#options' 			=> get_factory_LIC_REG_NO($uid),
			'#type' 			=> 'select',
		   //'#default_value'   	=> $Factoryid ? $Factoryid : 'other',
			'#default_value'   	=> $Factoryid,
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',
									'callback' 		=> 'get_ajax_name_factory',
									'progress' 		=> array(
									'type' 			=> 'throbber',
									'message' 		=> t('loading')
								)
       			       )
              );
		
   		 $value_factory_id = isset($form_state['values']['factory_id']) ? $form_state['values']['factory_id'] : $get_all_data[0]->factory_id;
		 
		 
			//if(!empty($value_factory_id) && ($value_factory_id != 'other')){
				$get_registration_value = get_reg_lic_no($value_factory_id);print_r($get_registration_values);//die;
			//} 
			
			/****************************** REGISTRATION NUMBER ******************************/
			if((!empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['factory_registrstion_no'];
			} 
			elseif((empty($get_registration_value['factory_registrstion_no'])) && (!empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['backlog_registration_no'];
			}
			elseif((empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (!empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['tm_factory_registration_no'];
			}
		
			/****************************** REGISTRATION DATE ******************************/
			if((!empty($get_registration_value['registration_date'])) && (empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['registration_date']))));
			} 
			elseif((empty($get_registration_value['registration_date'])) && (!empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['backlog_registration_date']))));
			}
		
			/****************************** LICENCE NUMBER ******************************/
			if((!empty($get_registration_value['factory_license_no'])) && (empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['factory_license_no'];
			} 
			elseif((empty($get_registration_value['factory_license_no'])) && (!empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['backlog_license_number'];
			}
		
			/****************************** LICENCE DATE ******************************/
			if((!empty($get_registration_value['license_date'])) && (empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['license_date']))));
			} 
			elseif((empty($get_registration_value['license_date'])) && (!empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['backlog_license_date']))));
			}
			
				$Factoryid       = $get_registration_value['factory_id'];
				$FactoryTypeid   = $get_registration_value['factory_typeid'];
				$FactoryZone     = $get_registration_value['factory_zone'];
				$ReferenceNumber = $get_registration_value['reference_number'];
				$FactoryName     = $get_registration_value['factory_name'];
				$IndustryNature  = $get_registration_value['nature_manufacturing'];
				$ClassificationNo = $get_registration_value['classification_no'];
				$OccurrenceDate  = trim(implode('-', array_reverse(explode('-',$get_registration_value['date_occurrence']))));
//				$OccurrenceTime  = $get_registration_value['time_occurrence'];
//				$BranchName  	 = $get_registration_value['branch_name'];
//				$FullAccount	 = $get_registration_value['full_account'];
		 
		 
		if(!empty($value_factory_id))
		{
			$form['dangerous_occurrence']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($FactoryTypeid) ? $FactoryTypeid : $get_all_data[0]->factory_typeid,
			);
			$form['dangerous_occurrence']['factory_zone'] = array(
				'#prefix' 			=> '<div id="factory_zone_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($FactoryZone) ? $FactoryZone : $get_all_data[0]->factory_zone,
			);
			$form['dangerous_occurrence']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($ReferenceNumber) ? $ReferenceNumber : '',
			);
			$form['dangerous_occurrence']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-5 col-xs-12"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(iii). Registered Factory Name'),
				'#type' 			=> 'textfield',
				'#value' 			=> !empty($FactoryName) ? $FactoryName : '',
				'#attributes' 		=> array('readonly' => 'readonly'),
			);
			$form['dangerous_occurrence']['industry_nature'] = array(
				'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-3 col-xs-12"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(iv) Nature of Industry'),
				'#type' 			=> 'textfield',
				'#value' 			=> !empty($IndustryNature) ? $IndustryNature : '',
				'#attributes' 		=> array('readonly' => 'readonly'),
			);
			$form['dangerous_occurrence']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</label></div></div>',//
				'#title' 			=> t('(v) Registration No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($RegistrationNo) ? $RegistrationNo : '',
				'#attributes' 		=> array('readonly' => 'readonly'),
			);
			$form['dangerous_occurrence']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(vi) Registration Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('readonly' => 'readonly'),
				'#value' 			=> !empty($RegistrationDate) ? $RegistrationDate : '',
			);
			$form['dangerous_occurrence']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</label></div></div>',//
				'#title' 			=> t('(vii) Licence No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($LicenceNo) ? $LicenceNo : '',
				'#attributes' 		=> array('class'=>array('NoField'),'readonly' => 'readonly'),
			);
			$form['dangerous_occurrence']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(viii) Licence Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('readonly' => 'readonly'),
				'#value' 			=> !empty($LicenceDate) ? $LicenceDate : '',
			);
			$form['dangerous_occurrence']['classification_no'] = array(
				'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(vi) Classification No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('readonly' => 'readonly'),
				'#value' 			=> !empty($ClassificationNo) ? $ClassificationNo : '',
			);
			$form['dangerous_occurrence']['date_occurrence'] = array(
				'#prefix' 			=> '<div class="col-md-3 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(ix) Date of occurrence1:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Date of Issue of passport.'),
				'#value' 			=> !empty($OccurrenceDate) ? $OccurrenceDate : '',
			);
			$form['dangerous_occurrence']['time_occurrence'] = array(
				'#prefix' 			=> '<div class="col-md-3 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(x) Time of occurrence:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($OccurrenceTime) ? $OccurrenceTime : '',
			);
			$form['dangerous_occurrence']['branch_name'] = array(
				'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(xi) Branch or department where the dangerous occurrence occurred:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($BranchName) ? $BranchName : '',
			);
			$form['dangerous_occurrence']['full_account'] = array(
				'#prefix' 			=> '<div class="col-md-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'textarea',
				'#title' 			=> t('(xii) Full account of the dangerous occurrence:'),
				'#attributes'   	=> array('style'=>'height: 1px;'),
				'#value' 			=> !empty($FullAccount) ? $FullAccount : '',
			);	
	   }
	   else {
		
		$form['dangerous_occurrence']['factory_typeid'] = array(
			'#prefix' 			=> '<div id="factory_typeid_id">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'hidden',
			'#value' 			=> !empty($FactoryTypeid) ? $FactoryTypeid : $get_all_data[0]->factory_typeid,
			//'#value' 			=> '',
		);
		$form['dangerous_occurrence']['factory_zone'] = array(
			'#prefix' 			=> '<div id="factory_zone_id">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'hidden',
			'#value' 			=> !empty($FactoryZone) ? $FactoryZone : $get_all_data[0]->factory_zone,
		);
		$form['dangerous_occurrence']['reference_number'] = array(
			'#prefix' 			=> '<div id="reference_number_id">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'hidden',
			'#value' 			=> !empty($ReferenceNumber) ? $ReferenceNumber : $get_all_data[0]->reference_number,
		);
		$form['dangerous_occurrence']['factory_name'] = array(
			'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-5 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(iii) Registered Factory Name'),
			'#type' 			=> 'textfield',
			'#value' 			=> !empty($FactoryName) ? $FactoryName : $get_all_data[0]->factory_name,
			'#attributes' 		=> array('readonly' => 'readonly'),
		);
		$form['dangerous_occurrence']['industry_nature'] = array(
			'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-3 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(iv) Nature of Industry'),
			'#type' 			=> 'textfield',
			'#value' 			=> !empty($IndustryNature) ? $IndustryNature : $get_all_data[0]->industry_nature,
			'#attributes' 		=> array('readonly' => 'readonly'),
		);
		$form['dangerous_occurrence']['registration_number'] = array(
			'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',//
			'#suffix' 			=> '</label></div></div>',//
			'#title' 			=> t('(v) Registration No.:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($RegistrationNo) ? $RegistrationNo : $get_all_data[0]->registration_number,
			'#attributes' 		=> array('readonly' => 'readonly'),
		);
		
		$form['dangerous_occurrence']['registration_date'] = array(
			'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(vi) Registration Date:'),
			'#type' 			=> 'textfield',//trim(implode('-', array_reverse(explode('-',$get_all_data[0]->registration_date))))
			'#required' 		=> TRUE,
			'#value' 			=> !empty($RegistrationDate) ? $RegistrationDate : $get_all_data[0]->registration_date,
			'#attributes' 		=> array('readonly' => 'readonly'),//'class'=>array('datepicker_retify'),
		);
		$form['dangerous_occurrence']['licence_number'] = array(
			'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',//
			'#suffix' 			=> '</label></div></div>',//
			'#title' 			=> t('(vii) Licence No.:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($LicenceNo) ? $LicenceNo : $get_all_data[0]->licence_number,
			'#attributes' 		=> array('class'=>array('NoField'),'readonly' => 'readonly'),
		);
		
		$form['dangerous_occurrence']['licence_date'] = array(
			'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(viii) Licence Date:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($LicenceDate) ? $LicenceDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->licence_date)))),
			'#attributes' 		=> array('class'=>array('datepicker_retify'),'readonly' => 'readonly'),
		);
		$form['dangerous_occurrence']['classification_no'] = array(
			'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(ix) Classification No.:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('readonly' => 'readonly'),
			'#value' 			=> !empty($ClassificationNo) ? $ClassificationNo : $get_all_data[0]->classification_no,
		);
		
		$form['dangerous_occurrence']['date_occurrence'] = array(
			'#prefix' 			=> '<div class="col-md-3 col-xs-12"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(x) Date of occurrence2:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class'=>array('datepicker_retify'),'title'=>'Enter Date of Issue of passport.'),
			'#value' 			=> !empty($OccurrenceDate) ? $OccurrenceDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->date_occurrence)))),
		);
		$form['dangerous_occurrence']['time_occurrence'] = array(
			'#prefix' 			=> '<div class="col-md-3 col-xs-12"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(viii) Time of occurrence:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($OccurrenceTime) ? $OccurrenceTime : $get_all_data[0]->time_occurrence,			
		);
		$form['dangerous_occurrence']['branch_name'] = array(
			'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xi) Branch or department where the dangerous occurrence occurred:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($BranchName) ? $BranchName : $get_all_data[0]->branch_name,
		);
		$form['dangerous_occurrence']['full_account'] = array(
			'#prefix' 		=> '<div class="col-md-12"><label class="input label-block">',
			'#suffix' 		=> '</label></div>',
			'#type' 		=> 'textarea',
			'#title' 		=> t('(xii) Full account of the dangerous occurrence:'),
			'#attributes'   => array('style'=>'height: 1px;'),
			'#value' 		=> !empty($FullAccount) ? $FullAccount : $get_all_data[0]->full_account,
		);
     }
		
	}
	else {
		
		$form['dangerous_occurrence']['factory_id'] = array(
			'#prefix' 			=> '<div id="factory_id_id">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'hidden',
			'#value' 			=> !empty($get_all_data[0]->factory_id) ? $get_all_data[0]->factory_id : 0,
        );
		$form['dangerous_occurrence']['factory_typeid'] = array(
			'#prefix' 			=> '<div id="factory_typeid_id">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'hidden',
			'#value' 			=> !empty($FactoryTypeid) ? $FactoryTypeid : $get_all_data[0]->factory_typeid,
			//'#value' 			=> '',
		);
		$form['dangerous_occurrence']['factory_zone'] = array(
			'#prefix' 			=> '<div id="factory_zone_id">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'hidden',
			'#value' 			=> !empty($FactoryZone) ? $FactoryZone : $get_all_data[0]->factory_zone,
		);
		$form['dangerous_occurrence']['reference_number'] = array(
			'#prefix' 			=> '<div id="reference_number_id">',
			'#suffix' 			=> '</div>',
			'#type' 			=> 'hidden',
			'#value' 			=> !empty($ReferenceNumber) ? $ReferenceNumber : $get_all_data[0]->reference_number,
		);
		$form['dangerous_occurrence']['factory_name'] = array(
			'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-6 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(ii) Registered Factory Name'),
			'#type' 			=> 'textfield',
			'#value' 			=> !empty($FactoryName) ? $FactoryName : $get_all_data[0]->factory_name,
			'#required' 		=> TRUE,
			//'#attributes' 		=> array('readonly' => 'readonly'),
		);
		$form['dangerous_occurrence']['industry_nature'] = array(
			'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-3 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(iii) Nature of Industry'),
			'#type' 			=> 'textfield',
			'#value' 			=> !empty($IndustryNature) ? $IndustryNature : $get_all_data[0]->industry_nature,
			//'#attributes' 		=> array('readonly' => 'readonly'),
		);
		$form['dangerous_occurrence']['registration_number'] = array(
			'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',//
			'#suffix' 			=> '</label></div></div>',//
			'#title' 			=> t('(iv) Registration No.:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($RegistrationNo) ? $RegistrationNo : $get_all_data[0]->registration_number,
		);
		
		$form['dangerous_occurrence']['registration_date'] = array(
			'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(v) Registration Date:'),
			'#type' 			=> 'textfield',//trim(implode('-', array_reverse(explode('-',$get_all_data[0]->registration_date)))),
			'#required' 		=> TRUE,
			'#value' 			=> !empty($RegistrationDate) ? $RegistrationDate : $get_all_data[0]->registration_date,
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
		);
		$form['dangerous_occurrence']['licence_number'] = array(
			'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',//
			'#suffix' 			=> '</label></div></div>',//
			'#title' 			=> t('(vi) Licence No.:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($LicenceNo) ? $LicenceNo : $get_all_data[0]->licence_number,
			'#attributes' 		=> array('class'=>array('NoField')),
		);
		
		$form['dangerous_occurrence']['licence_date'] = array(
			'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(vii) Licence Date:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($LicenceDate) ? $LicenceDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->licence_date)))),
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
		);
		$form['dangerous_occurrence']['classification_no'] = array(
			'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-3 col-xs-12" ><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(viii) Classification No.:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			//'#attributes' 		=> array('readonly' => 'readonly'),
			'#value' 			=> !empty($ClassificationNo) ? $ClassificationNo : $get_all_data[0]->classification_no,
		);
		
		$form['dangerous_occurrence']['date_occurrence'] = array(
			'#prefix' 			=> '<div class="col-md-3 col-xs-12"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(ix) Date of occurrence:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Date of Issue of passport.'),
			'#value' 			=> !empty($OccurrenceDate) ? $OccurrenceDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->date_occurrence)))),
		);
		$form['dangerous_occurrence']['time_occurrence'] = array(
			'#prefix' 			=> '<div class="col-md-3 col-xs-12"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(x) Time of occurrence:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($OccurrenceTime) ? $OccurrenceTime : $get_all_data[0]->time_occurrence,			
		);
		$form['dangerous_occurrence']['branch_name'] = array(
			'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xi) Branch or department where the dangerous occurrence occurred:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#value' 			=> !empty($BranchName) ? $BranchName : $get_all_data[0]->branch_name,
		);
		$form['dangerous_occurrence']['full_account'] = array(
			'#prefix' 		=> '<div class="col-md-12"><label class="input label-block">',
			'#suffix' 		=> '</label></div>',
			'#type' 		=> 'textarea',
			'#title' 		=> t('(xii) Full account of the dangerous occurrence:'),
			'#attributes'   => array('style'=>'height: 1px;'),
			'#value' 		=> !empty($FullAccount) ? $FullAccount : $get_all_data[0]->full_account,
		);
			
		// Enter Dangerous Occurrence //
			
	$form['dangerous_occurrence']['occurrences'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('(xiii) Name of the person who saw the dangerous occurrence and can give important evidence'),
			'#prefix' 			=> '<div id="occurrence_id" class="col-lg-12 col-md-12 col-sm-12">',
			'#suffix' 			=> '</div>',
		);
	
		if (empty($form_state['occurrence_no'])) {$form_state['occurrence_no'] = 1;}
		
	//if(!empty($get_occurence_data)){$occurrence_count = count($get_occurence_data);} else {$occurrence_count = $form_state['occurrence_no'];}
	
	
		for ($j = 0; $j < $form_state['occurrence_no']; $j++) { //$occurrence_count
			$slno = $j+1;
			
			$form['dangerous_occurrence']['occurrences']['persons_name_'.$j] = array(
				'#prefix' 		=> '<div class="col-md-4"><label class="input label-block">',
				'#suffix' 		=> '</label></div>',
				'#type' 		=> 'textfield',
				'#size' 		=> 150,
				'#title' 		=> t('('.$slno.') Name of the person:'),
				'#attributes' 	=> array('multiple' => 'multiple'),
				'#default_value' 		=> (isset($get_occurence_data[$j]->persons_name)) ? $get_occurence_data[$j]->persons_name : '',
			);
			$form['dangerous_occurrence']['occurrences']['personid_'.$j] = array(
				'#type' 		=> 'hidden',
				'#value' 		=> (isset($get_occurence_data[$j]->id)) ? $get_occurence_data[$j]->id : '',
			);
		}
	
		$form['dangerous_occurrence']['occurrences']['add_occurrences'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></div>',
			'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: left;'),
			'#type' 			=> 'submit',
			'#value' 			=> t("+ Add more Person's name"),
			'#submit' 			=> array('occurrences_add_more_add_one'),
			'#ajax' 			=> array(
				'callback' 		=> 'occurrences_add_more_callback',
				'wrapper' 		=> 'occurrence_id',
				)
			);	
	}
	
	 $form['dangerous_occurrence']['submit'] = array (
		'#prefix' 		=> '<div id="submit_div" class="col-xs-12">',  
		'#suffix' 		=> '</div>',
		'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		'#type' 		=> 'submit',
		'#value'		=> 'Save'
	);
	
	  return $form;
  }
	
 /*function get_reg_lic_no($factory_id){
		$query_reg_lic 		= db_select('fa_cafa', 'cafa');
		$query_reg_lic      ->leftjoin('fa_nature_manufacturing', 'fnm', 'fnm.application_id=cafa.id');
		$query_reg_lic      ->fields('fnm', array('nature_manufacturing'));
		$query_reg_lic		->fields('cafa',array('factory_name','factory_zone','factory_typeid','reference_number','factory_registrstion_no','backlog_registration_no','backlog_registration_date','registration_date','tm_factory_registration_no','backlog_license_number','factory_license_no','backlog_license_date','license_date'));
		$query_reg_lic		->condition('cafa.id',$factory_id,'=');
		$result_reg_lic 	= $query_reg_lic->execute()->fetchAssoc();
		return $result_reg_lic;
	}*/

 /*function get_factory_name($uid){
		$default_select 	= array(""=>"--Select--");
		$result 	 = db_query("SELECT id,factory_name FROM {fa_cafa} WHERE ((factory_registrstion_no !='') OR (backlog_registration_no !='')) AND created_by ='".$uid."'");
		$list 	 = array();
		foreach ($result as $record) {
			$list[$record->id] = t('@factoryname', array(
			'@factoryname' => $record->factory_name,
			));
		}
		$last_select 	= array("other"=>"Other");
		return ($default_select+$list+$last_select);
	}*/

function get_ajax_name_factory($form, $form_state){
	  
	  $commands[] = ajax_command_replace('#factory_id_id', drupal_render($form['dangerous_occurrence']['factory_id']));
	  $commands[] = ajax_command_replace('#factory_typeid_id', drupal_render($form['dangerous_occurrence']['factory_typeid']));
	  $commands[] = ajax_command_replace('#factory_zone_id', drupal_render($form['dangerous_occurrence']['factory_zone']));
	  $commands[] = ajax_command_replace('#reference_number_id', drupal_render($form['dangerous_occurrence']['reference_number']));
	  $commands[] = ajax_command_replace('#full_account_id', drupal_render($form['dangerous_occurrence']['full_account']));
	  $commands[] = ajax_command_replace('#factory_name_id', drupal_render($form['dangerous_occurrence']['factory_name']));
	  $commands[] = ajax_command_replace('#industry_nature_id', drupal_render($form['dangerous_occurrence']['industry_nature']));
	  $commands[] = ajax_command_replace('#registration_number_id', drupal_render($form['dangerous_occurrence']['registration_number']));
	  $commands[] = ajax_command_replace('#classification_no_id', drupal_render($form['dangerous_occurrence']['classification_no']));
	  $commands[] = ajax_command_replace('#registration_date_id', drupal_render($form['dangerous_occurrence']['registration_date']));
	  $commands[] = ajax_command_replace('#licence_number_id', drupal_render($form['dangerous_occurrence']['licence_number']));
	  $commands[] = ajax_command_replace('#licence_date_id', drupal_render($form['dangerous_occurrence']['licence_date']));
	  //$commands[] = ajax_command_replace('#date_occurrence_id', drupal_render($form['dangerous_occurrence']['date_occurrence']));
	  //$commands[] = ajax_command_replace('#time_occurrence_id', drupal_render($form['dangerous_occurrence']['time_occurrence']));
	  //$commands[] = ajax_command_replace('#persons_name_id', drupal_render($form['dangerous_occurrence']['persons_name']));
	  //$commands[] = ajax_command_replace('#branch_name_id', drupal_render($form['dangerous_occurrence']['branch_name']));

	  return array('#type' => 'ajax', '#commands' => $commands);
	  
  } 
   
	function occurrences_add_more_add_one($form, &$form_state) {
		//echo "TEST"; die;
		
		if (!isset($form_state['occurrence_no'])) {
			$form_state['occurrence_no'] = 0;
			$form_state['occurrence_no']++;
		}
	
		$form_state['occurrence_no']++;
		$form_state['rebuild'] = TRUE;
	}
	
	function occurrences_add_more_callback($form, $form_state) {
		return $form['dangerous_occurrence']['occurrences'];
	}

 function form19_form_submit($form, &$form_state){
	
	global $base_root,$base_path,$user,$_SESSION;
	$uid 							= $user->uid;
	//$val   							= $form_state['values'];
	$val   							= $form_state['input'];
	
	$ServiceId = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$service_id = ($ServiceId==0)? 13 :$ServiceId;

	if($val['factory_id']!=0)
	{			
		$factoryid 	   = $val['factory_id'];
		$factorytypeid = $val['factory_typeid'];
		$factoryzone   = $val['factory_zone'];
	} else {
		$factoryid     = 0;
		$factorytypeid = 0;
		$factoryzone   = 0;
	}
	/*if($val['factory_typeid']!='')
	{			
		$factorytypeid = $val['factory_typeid'];
	} else {
		$factorytypeid = 0;
	}*/
	if($val['reference_number']!='')
	{			
		$referencenumber = $val['reference_number'];
	} else {
		$referencenumber = 0;
	}
	
	$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);

	if($formid != 0) 
	{
		$dangerous_occurrence_update = 	array(
			'factory_id'           => $factoryid,
			'factory_name'         => $val['factory_name'],
			'factory_typeid'       => $factorytypeid,
			'reference_number'     => $referencenumber,
			'registration_number'  => $val['registration_number'],
			'registration_date'    => trim(implode('-', array_reverse(explode('-',$val['registration_date'])))),
			'licence_number'       => $val['licence_number'],
			'licence_date'         => trim(implode('-', array_reverse(explode('-',$val['licence_date'])))),
			'date_occurrence'      => trim(implode('-', array_reverse(explode('-',$val['date_occurrence'])))),
			'time_occurrence'      => $val['time_occurrence'],
			'branch_name'          => $val['branch_name'],
			'full_account'         => $val['full_account'],
			'industry_nature'      => $val['industry_nature'],
			'factory_zone'         => $factoryzone,
			'classification_no'    => $val['classification_no'],
			'is_registered'        => $val['is_registered'],
		); 
		//echo '<pre>'.print_r($dangerous_occurrence_update); die;
		
		$queryapp 		 =	db_update('fa_form19_dangerous_occurrence');
		$queryapp		 ->	fields($dangerous_occurrence_update);
		$queryapp		 ->	condition('id',$formid,'=');
		$queryapp		 ->	execute();
		
		$dangerous_occurrence_ID = $formid;
	
		$e = 0;
		while(!empty($dangerous_occurrence_ID) && !empty($val['persons_name_'.$e]))
		{ 
			if(!empty($val['personid_'.$e])) // PERSON NAME UPDATE
			{
				$dangerous_witness = array(
					'persons_name'            => $val['persons_name_'.$e],//
				);
					$querycase 		 =	db_update('fa_form19_dangerous_occurrence_case_witness');
					$querycase		 ->	fields($dangerous_witness);
					$querycase		 ->	condition('id',$val['personid_'.$e],'=');
					$querycase		 ->	condition('dangerous_occurrence_id',$formid,'=');
					$querycase		 ->	execute();
					
			} else { // PERSON NAME ADD DURING EDIT
			
				$dangerous_witness = array(
					'dangerous_occurrence_id' => $dangerous_occurrence_ID,
					'persons_name'            => $val['persons_name_'.$e],
					'created_date' 		   	  => date('Y-m-d H:i:s'),
				);
				db_insert('fa_form19_dangerous_occurrence_case_witness')->fields($dangerous_witness)->execute();
			}
				$e++;
			}

	} else {
	
		$dangerous_details = 	array(
			'factory_id'           => $factoryid,
			'factory_name'         => $val['factory_name'],
			'factory_typeid'       => $factorytypeid,
			'reference_number'     => $referencenumber,
			'registration_number'  => $val['registration_number'],
			'registration_date'    => trim(implode('-', array_reverse(explode('-',$val['registration_date'])))),
			'licence_number'       => $val['licence_number'],
			'licence_date'         => trim(implode('-', array_reverse(explode('-',$val['licence_date'])))),
			'date_occurrence'      => trim(implode('-', array_reverse(explode('-',$val['date_occurrence'])))),
			'time_occurrence'      => $val['time_occurrence'],
			'branch_name'          => $val['branch_name'],
			'full_account'         => $val['full_account'],
			'industry_nature'      => $val['industry_nature'],
			'classification_no'    => $val['classification_no'],
			'is_registered'        => $val['is_registered'],			
			'created_by'		   => $uid,
			'created_date' 		   => date('Y-m-d H:i:s'),
			'factory_zone'         => $factoryzone,
			'service_id' 		   => $service_id,
		); 
		
        //echo "<pre>"; print_r($dangerous_details);die;
		$dangerous_occurrence_ID = db_insert('fa_form19_dangerous_occurrence')->fields($dangerous_details)->execute();
	
		$e = 0;
		while(!empty($dangerous_occurrence_ID) && !empty($val['persons_name_'.$e]))
		{
			$dangerous_witness = array(
				'dangerous_occurrence_id' => $dangerous_occurrence_ID,
				'persons_name'            => $val['persons_name_'.$e],
				'created_date' 		   	  => date('Y-m-d H:i:s'),
			);
		 db_insert('fa_form19_dangerous_occurrence_case_witness')->fields($dangerous_witness)->execute();
			
			$e++;
		}
	}
		drupal_goto('applicant/form19/preview/'.encryption_decryption_fun('encrypt',$dangerous_occurrence_ID).'/'.encryption_decryption_fun('encrypt',$referencenumber).'/'.encryption_decryption_fun('encrypt',$factorytypeid).'/'.encryption_decryption_fun('encrypt',$service_id));

		$form_state['rebuild'] = true;
	}