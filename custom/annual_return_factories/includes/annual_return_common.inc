<?php

  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
  function annual_return_common($form, &$form_state, $annual_returnID, $factory_typeID, $factoryID) {
	 // drupal_goto('applicant/payment-wages-apply/default/1/2/3');
		
		global $user;
		$uid 						= $user->uid;
		
		
		ctools_include('modal');
		ctools_modal_add_js();
		
		$annual_return_id = encryption_decryption_fun('decrypt', $annual_returnID);
		$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id_decrypt_val = encryption_decryption_fun('decrypt', $factoryID);
		
		//code for incomplete annual return common form where only occupier or manager details inserted
		/*if($annual_return_id == 0) {
			$get_all_blank_status_ar_data	=	get_all_blank_status_ar_data($uid);
			
			foreach($get_all_blank_status_ar_data as $details_data) {
				//echo "<pre>"; print_r($details_data->id);
				
				if($details_data->id != 0) {
					$query = db_delete('fa_annual_return');
					$query->condition('id', $details_data->id, '=');
					$query->condition('uid', $uid, '=');
					$query->execute();
				}	
			}
		}*/
		//end
		
		if($factory_id_decrypt_val != 0) {
			$factory_id = $factory_id_decrypt_val;
											
		} else {
			$factory_id = '';
				
		}
		
		
		//die($annual_return_id.' AND '.$factory_type_id);
		
		$get_factory_info = get_annual_return_factory_information($annual_return_id);
		
		$get_leave_wages_details = get_leave_wages_details($annual_return_id);
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_id);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_id);
		
		$get_medical_officer_details = get_medical_officer($annual_return_ID);
		$get_hospital_details = get_hospital_details($annual_return_ID);
		
		$service_id = $application_id = $RegistrationNo = $RegistrationDate = $LicenceNo = $LicenceDate = $ClassificationNo = $FactoryTypeid = $ReferenceNumber = $FactoryName = $factory_pincode = $factory_state = $factory_district = $factory_subdivision = $factory_areatype = $factory_block = $factory_panchayat = $factory_policestation = $factory_postoffice = $nearest_landmark = $factory_addrline = $industry_nature = '';
		
		$occupier_name = $factory_pincodeoprmntadr_occupier = $factory_state_oprmntadr_occupier = $factory_district_oprmntadr_occupier = $factory_subdivision_oprmntadr_occupier = $factory_areatype_oprmntadr_occupier = $factory_block_oprmntadr_occupier = $factory_panchayat_oprmntadr_occupier = $factory_policestation_oprmntadr_occupier = $factory_postoffice_oprmntadr_occupier = $factory_addrline_oprmntadr_occupier = '';
		
		$manager_name = $factory_pincode_manager = $factory_state_manager = $factory_district_manager = $factory_sub_division_manager = $factory_area_type_manager =
		$factory_block_mun_cor_sez_not_manager = $factory_grm_ward_sector_not_manager = $factory_police_station_manager = $factory_post_office_manager = 
		$factory_adress_line1_manager = '';
		
		$annual_return_year = date('Y') - 1;
		
		$form = array();
		$form['factory_information'] = array(
			'#type' => 'fieldset',
			'#title' => t('1. Factory Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		);
		
		//this section is for add factory data from fact_mast table
		
		$add_new_factory = l('Add Registered Factory', 'add-new-factory', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'font-weight: bold; font-size: 18px;')));
		$factory_list_admin = l('List of Factories 1', 'factory-list-admin/ACTIVE', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'font-weight: bold; font-size: 18px;')));
		
		$form['factory_information']['add_new_factory'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div style="color:#f00">If you didn\'t find Licence No. in the Factory Licence No. dropdown list then click on '.$add_new_factory.' or click on '.$factory_list_admin.'.</div>',
			'#suffix' 			=> '</div></div>',
		);
		
		//end
		
		$form['factory_information']['annual_return_year_heading'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div style="font-size: 20px; font-weight: bold; color: #337ab7;"><strong>Annual Return for the Year '.$annual_return_year.'</strong></div>',
			'#suffix' 			=> '</div></div>',
		);
		
		$form['factory_information']['annual_return_year'] = array(
			'#type' 			=> 'hidden',
			'#prefix' 			=> '',
			'#suffix' 			=> '',
			'#default_value'   	=> $annual_return_year,
		);
			
		$form['factory_information']['payment_wages_flag'] = array(
			'#type' => 'checkbox',
			'#title' => 'Payment of Wages Return.',
			'#value' => 1,
			'#attributes' => array('class' => array(), 'disabled' => 'disabled'),
		);
		
		$form['factory_information']['factories_act_flag'] = array(
			'#type' => 'checkbox',
			'#title' => 'Factories Rules Return.',
			'#value' => 1,
			'#attributes' => array('class' => array(), 'disabled' => 'disabled'),
		);
		
		if($get_medical_officer_details->annual_return_id != NULL || $get_hospital_details->annual_return_id != NULL || $get_details_payment->annual_return_id != NULL || $get_emplm_dism_pay_bonus_women->annual_return_id != NULL) {
			
			$form['factory_information']['maternity_benefit_flag'] = array(
				'#type' => 'checkbox',
				'#title' => 'Check if You want to submit Maternity Benefit Rules Return.',
				'#value' => $get_factory_info->maternity_benefit_flag,
				'#attributes' => array('class' => array(), 'disabled' => 'disabled'),
			);
			
  		} else {
			
			$form['factory_information']['maternity_benefit_flag'] = array(
				'#type' => 'checkbox',
				'#title' => 'Check if You want to submit Maternity Benefit Rules Return.',
			);
				
		}
		
		
		$value_factory_id = isset($form_state['values']['factory_id']) ? $form_state['values']['factory_id'] : $factory_id;	
		  
		$form['factory_information']['factory_id'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-6"><label class="select label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(i) Choose Factory Licence No.'),
			'#attributes' 		=> array('class' => array( '')),
			'#options' 			=> get_factory_licence_no($uid),
			'#type' 			=> 'select',
			'#default_value'   	=> $value_factory_id,
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
		
		
		if($annual_return_id != 0) {
			$form['factory_information']['annual_return_id'] = array(
				'#prefix' 			=> '<div id="annual_return_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> !empty($annual_return_id) ? $annual_return_id : '',
			);
		} else {
			$form['factory_information']['annual_return_id'] = array(
				'#prefix' 			=> '<div id="annual_return_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $annual_return_id,
			);
		}
		
		
		if((!empty($value_factory_id)) && ($value_factory_id != 0)) {
			
			$getdata_factory_address = array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
			$factory_address = get_full_address('fa_cafa','sub-table',$value_factory_id,$getdata_factory_address);
			$full_factory_address = trim($factory_address);
			//echo "<pre>"; print_r($factory_address);
			
			$get_registration_value = get_reg_lic_no($value_factory_id);
			$get_occupier_value = get_reg_factory_occupier($value_factory_id);
			$get_manager_value = get_reg_factory_manager($value_factory_id);
			//echo "SM<pre>"; print_r($get_registration_value); die;
			//echo $get_registration_value['state'];die;
			
			$getdata_occupier_permanent_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
			$address_of_occupier = get_full_address('fa_occupier_details','sub-table',$value_factory_id,$getdata_occupier_permanent_address);
			
			$getdata_manager_address =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
			$address_of_manager = get_full_address('fa_manager_details','sub-table',$value_factory_id,$getdata_manager_address);
			
		
			$service_id     = $get_registration_value['service_id'];
			$application_id = $value_factory_id;
			
			/****************************** REGISTRATION NUMBER ******************************/
			if((!empty($get_registration_value['factory_registrstion_no'])) && (!empty($get_registration_value['backlog_registration_no'])) && (!empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['factory_registrstion_no'];
			}
			else if((!empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['factory_registrstion_no'];
			} 
			else if((empty($get_registration_value['factory_registrstion_no'])) && (!empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['backlog_registration_no'];
			}
			else if((empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (!empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['tm_factory_registration_no'];
			}
			
			/****************************** REGISTRATION DATE ******************************/
			if((!empty($get_registration_value['registration_date'])) && (!empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = $get_registration_value['registration_date'];
			}
			else if((!empty($get_registration_value['registration_date'])) && (empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = $get_registration_value['registration_date'];
			} 
			else if((empty($get_registration_value['registration_date'])) && (!empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = $get_registration_value['backlog_registration_date'];
			}
			
			/****************************** LICENCE NUMBER ******************************/
			if((!empty($get_registration_value['factory_license_no'])) && (!empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['factory_license_no'];
			} 
			else if((!empty($get_registration_value['factory_license_no'])) && (empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['factory_license_no'];
			} 
			else if((empty($get_registration_value['factory_license_no'])) && (!empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['backlog_license_number'];
			}
			
			/****************************** LICENCE DATE ******************************/
			if((!empty($get_registration_value['license_date'])) && (!empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = $get_registration_value['license_date'];
			} 
			else if((!empty($get_registration_value['license_date'])) && (empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = $get_registration_value['license_date'];
			} 
			else if((empty($get_registration_value['license_date'])) && (!empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = $get_registration_value['backlog_license_date'];
			}
			
			/*****************************Classification No****************************/
			if(!empty($get_registration_value['classification_no']))
			{
				$ClassificationNo = $get_registration_value['classification_no'];
			}
			
			
			$FactoryTypeid          = $get_registration_value['factory_typeid'];
			$ReferenceNumber        = $get_registration_value['reference_number'];
			$FactoryName            = $get_registration_value['factory_name'];
			$industry_nature 		= $get_registration_value['nature_manufacturing'];
			
		//for factory
			$factory_pincode        = $get_registration_value['pincode'];
			$factory_state          = $get_registration_value['state'];
			$factory_district 	    = $get_registration_value['district'];
			$factory_subdivision    = $get_registration_value['subdivision'];
			$factory_areatype       = $get_registration_value['areatype'];
			$factory_block          = $get_registration_value['block'];
			$factory_panchayat      = $get_registration_value['panchayat'];
			$factory_policestation  = $get_registration_value['policestation'];
			$factory_postoffice     = $get_registration_value['postoffice'];
			$nearest_landmark       = $get_registration_value['nearest_landmark'];
			$factory_addrline		= $get_registration_value['addrline'];
			
		//for occupier
			if(!empty($get_occupier_value)) {
				$occupier_name 								= $get_occupier_value['name_occupier'];
				$factory_pincodeoprmntadr_occupier          = $get_occupier_value['pincodeoprmntadr'];
				$factory_state_oprmntadr_occupier           = $get_occupier_value['state_oprmntadr'];
				$factory_district_oprmntadr_occupier 	    = $get_occupier_value['district_oprmntadr'];
				$factory_subdivision_oprmntadr_occupier     = $get_occupier_value['subdivision_oprmntadr'];
				$factory_areatype_oprmntadr_occupier        = $get_occupier_value['areatype_oprmntadr'];
				$factory_block_oprmntadr_occupier           = $get_occupier_value['block_oprmntadr'];
				$factory_panchayat_oprmntadr_occupier       = $get_occupier_value['panchayat_oprmntadr'];
				$factory_policestation_oprmntadr_occupier   = $get_occupier_value['policestation_oprmntadr'];
				$factory_postoffice_oprmntadr_occupier      = $get_occupier_value['postoffice_oprmntadr'];
				$factory_addrline_oprmntadr_occupier		= $get_occupier_value['addrline_oprmntadr'];
			}
			
			
		//for manager
			if(!empty($get_manager_value)) {
				$manager_name 								= $get_manager_value['name_manager'];
				$factory_pincode_manager        			= $get_manager_value['pincode_manager'];
				$factory_state_manager          			= $get_manager_value['state_manager'];
				$factory_district_manager 	    			= $get_manager_value['district_manager'];
				$factory_sub_division_manager    			= $get_manager_value['sub_division_manager'];
				$factory_area_type_manager       			= $get_manager_value['area_type_manager'];
				$factory_block_mun_cor_sez_not_manager      = $get_manager_value['block_mun_cor_sez_not_manager'];
				$factory_grm_ward_sector_not_manager      	= $get_manager_value['grm_ward_sector_not_manager'];
				$factory_police_station_manager  			= $get_manager_value['police_station_manager'];
				$factory_post_office_manager     			= $get_manager_value['post_office_manager'];
				$factory_adress_line1_manager				= $get_manager_value['adress_line1_manager'];
			}
			
			//$get_ar_common_value = get_annual_return_common_details($value_factory_id);
//this code is for when factory name changed from dropdown from one factory to another factory
			if($form_state['values']['factory_id'] != NULL) {
				if($annual_return_id != 0) {
					$query = db_update('fa_annual_return');
					$query->fields(array('temp_cafa_id_occupier_data' => NULL, 'temp_cafa_id_manager_data' => NULL));
					$query->condition('id', $annual_return_id, '=');
					$query->condition('uid', $uid, '=');
					$query->execute();
				}
			}
						
			if($annual_return_id != 0) {
				$get_factory_info = get_annual_return_factory_information($annual_return_id);
				
				if(($get_factory_info->temp_cafa_id_occupier_data != NULL) && ($get_factory_info->temp_cafa_id_occupier_data == $value_factory_id)) {
					$get_ar_occupier_value = get_annual_return_occupier_information($annual_return_id);
				}
				
				if(($get_factory_info->temp_cafa_id_manager_data != NULL) && ($get_factory_info->temp_cafa_id_manager_data == $value_factory_id)) {
					$get_ar_manager_value = get_annual_return_manager_information($annual_return_id);	
				}
			
				if(!empty($get_ar_occupier_value)) {
					$ar_occupier_name 					  = $get_ar_occupier_value->name_occupier;
					$ar_pincodeoprmntadr_occupier         = $get_ar_occupier_value->pincodeoprmntadr;
					$ar_state_oprmntadr_occupier          = $get_ar_occupier_value->state_oprmntadr;
					$ar_district_oprmntadr_occupier 	  = $get_ar_occupier_value->district_oprmntadr;
					$ar_subdivision_oprmntadr_occupier    = $get_ar_occupier_value->subdivision_oprmntadr;
					$ar_areatype_oprmntadr_occupier       = $get_ar_occupier_value->areatype_oprmntadr;
					$ar_block_oprmntadr_occupier          = $get_ar_occupier_value->block_oprmntadr;
					$ar_panchayat_oprmntadr_occupier      = $get_ar_occupier_value->panchayat_oprmntadr;
					$ar_policestation_oprmntadr_occupier  = $get_ar_occupier_value->policestation_oprmntadr;
					$ar_postoffice_oprmntadr_occupier     = $get_ar_occupier_value->postoffice_oprmntadr;
					$ar_addrline_oprmntadr_occupier		  = $get_ar_occupier_value->addrline_oprmntadr;
				}
				
				if(!empty($get_ar_manager_value)) {	
					$ar_manager_name 					  = $get_ar_manager_value->name_manager;
					$ar_pincode_manager        			  = $get_ar_manager_value->pincode_manager;
					$ar_state_manager          			  = $get_ar_manager_value->state_manager;
					$ar_district_manager 	    		  = $get_ar_manager_value->district_manager;
					$ar_sub_division_manager    		  = $get_ar_manager_value->sub_division_manager;
					$ar_area_type_manager      	 		  = $get_ar_manager_value->area_type_manager;
					$ar_block_mun_cor_sez_not_manager     = $get_ar_manager_value->block_mun_cor_sez_not_manager;
					$ar_grm_ward_sector_not_manager       = $get_ar_manager_value->grm_ward_sector_not_manager;
					$ar_police_station_manager  		  = $get_ar_manager_value->police_station_manager;
					$ar_post_office_manager     		  = $get_ar_manager_value->post_office_manager;
					$ar_adress_line1_manager			  = $get_ar_manager_value->adress_line1_manager;
				}
			
			}
			
			$occupier_details_update_link = l('<i class="ace-icon fa fa-edit bigger-130 text-blue"></i> Update Occupier\'s Details', 
											'update-occupier-details/nojs/'.encryption_decryption_fun('encrypt', $value_factory_id).'/'.$annual_returnID.'/'.
											encryption_decryption_fun('encrypt', 'annual-return-common'), array('html'=>TRUE, 'attributes' => array('class' => 'ctools-use-modal')));
											
			$manager_details_update_link = l('<i class="ace-icon fa fa-edit bigger-130 text-blue"></i> Update Manager\'s Details', 
											'update-manager-details/nojs/'.encryption_decryption_fun('encrypt', $value_factory_id).'/'.$annual_returnID.'/'.
											encryption_decryption_fun('encrypt', 'annual-return-common'), array('html'=>TRUE, 'attributes' => array('class' => 'ctools-use-modal')));
											
		}
		
		
		if(!empty($value_factory_id) && ($value_factory_id != 0)) {
			$form['factory_information']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id"><label class="select label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(i)a. Enter factory_typeid'),
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($FactoryTypeid) ? $FactoryTypeid : '',
			);
			$form['factory_information']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id"><label class="select label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(i)a. Enter reference_number'),
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($ReferenceNumber) ? $ReferenceNumber : '',
			);
			
	//factory name and address section
	
			$form['factory_information']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(i)a. Enter Registered Factory Name'),
				'#attributes' 		=> array('class' => array( ''),'placeholder' => 'Registered Factory Name','readonly' => 'readonly'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($FactoryName) ? $FactoryName : '',
				//'#element_validate' => array('element_validate_factory_name'),
			);
		
			$form['factory_information']['pincode']       = array(
				'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode','readonly' => 'readonly'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(ii) Pincode'),
				'#value' 	 	        => !empty($factory_pincode) ? $factory_pincode : '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				//'#element_validate' 	=> array('element_validate_numeric_positive'),
			);
			
			$form['factory_information']['state'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($factory_state),
				'#value' 	 	=> !empty($factory_state) ? $factory_state : '',
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$form['factory_information']['district'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($factory_state),
				'#value' 	=> !empty($factory_district) ? $factory_district : '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['subdivision'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division','disabled' => 'disabled'),
				'#options' => common_custom_user_subdivisionlist_list_new($factory_district),
				'#required' => TRUE,
				'#value' 	=> !empty($factory_subdivision) ? $factory_subdivision : '',
				'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$form['factory_information']['areatype'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type','disabled' => 'disabled'),
				'#options' => common_custom_user_areatype_list_new($factory_district, $factory_subdivision),
				'#required' => TRUE,
				'#value' 	=> !empty($factory_areatype) ? $factory_areatype : '',
				'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
				if ($factory_areatype == 'B') {
					$areatype_name = 'Block';
				} elseif ($factory_areatype == 'M') {
					$areatype_name = 'Municipality';
				} elseif ($factory_areatype == 'C') {
					$areatype_name = 'Corporation';
				} elseif ($factory_areatype == 'S') {
					$areatype_name = 'SEZ';
				} elseif ($factory_areatype == 'N') {
					$areatype_name = 'Notified Area';
				}
				
			$form['factory_information']['block'] = array(
				'#title' 		=> '(vii) '. $areatype_name,
				'#type'         => 'select',
				'#disabled' => TRUE,
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block','disabled' => 'disabled'),
				'#options' 		=> common_custom_user_block_list_new($factory_subdivision, $factory_areatype),
				'#required' 	=> TRUE,
				'#value' 	    => !empty($factory_block) ? $factory_block : '',
				'#prefix' 		=> '<div id="ld_empareatype_name_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
				if ($factory_areatype == 'B') {
					$area_name = 'Gram Panchayat';
					$area_code = 'V';
				} elseif ($factory_areatype == 'M') {
					$area_name = 'Ward';
					$area_code = 'W';
				} elseif ($factory_areatype == 'C') {
					$area_name = 'Ward';
					$area_code = 'C';
				} elseif ($factory_areatype == 'S') {
					$area_name = 'Sector';
					$area_code = 'S';
				} elseif ($factory_areatype == 'N') {
					$area_name = 'Notified Area';
					$area_code = 'N';
				}
				
			$form['factory_information']['panchayat'] = array(
				'#title' => '(viii) '.$area_name,
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat','disabled' => 'disabled'),
				'#options' => common_custom_user_villward_list_new($factory_block, $area_code),
				'#value' 	    => !empty($factory_panchayat) ? $factory_panchayat : '',
				'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$form['factory_information']['policestation'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station','disabled' => 'disabled'),
				'#options' => common_custom_user_ps_list_new($factory_district),
				'#required' => TRUE,
				'#value' 	    => !empty($factory_policestation) ? $factory_policestation : '',
				'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['postoffice'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office','disabled' => 'disabled'),
				'#options' => common_custom_post_office_list_new($factory_pincode),
				'#value' 	    => !empty($factory_postoffice) ? $factory_postoffice : '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		
			$factory_zone_name = get_zone_name($factory_block,$factory_panchayat);
		
			$form['factory_information']['factory_zone'] = array(
				'#value'   => $factory_zone_name[0]->zone_id,
				'#type' => 'hidden',
			);
			
			$form['factory_information']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(xi) Factory Zone'),
				'#value' 	    => !empty($factory_zone_name[0]->zone_name) ? $factory_zone_name[0]->zone_name : '',
				'#type' => 'textfield',
				'#required' => TRUE,
				'#attributes'		=> array('class' => array( ''),'readonly' => 'readonly','placeholder' => 'Factory Zone'),
				//'#element_validate' 	=> array('element_validate_hyphenfullstop'),
			);
			
			if(!empty($nearest_landmark)) {
				$form['factory_information']['nearest_landmark'] = array(
					'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('(xii) Nearest Landmark'),
					'#type' => 'textfield',
					'#value' 	    => !empty($nearest_landmark) ? $nearest_landmark : '',
					'#attributes' => array('class' => array('charField'),'readonly' => 'readonly','placeholder' => 'Nearest Landmark'),
					//'#element_validate' 	=> array('element_validate_alphabatic_text'),
					'#required' => TRUE,
				);		
			} else {
				unset($form_state['input']['nearest_landmark']);
				$form['factory_information']['nearest_landmark'] = array(
					'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('(xii) Nearest Landmark'),
					'#type' => 'textfield',
					'#default_value' 	    => !empty($nearest_landmark) ? $nearest_landmark : '',
					'#attributes' => array('class' => array('charField'),'placeholder' => 'Nearest Landmark'),
					//'#element_validate' 	=> array('element_validate_alphabatic_text'),
					'#required' => TRUE,
				);
			}
		
			$form['factory_information']['addrline'] = array(
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xiii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' 	    => !empty($factory_addrline) ? $factory_addrline : '',
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line','readonly' => 'readonly'),
				//'#element_validate' => array('element_validate_streetaddress'), 
			);
			
	//factory address section end
		
			$form['factory_information']['industry_nature'] = array(
				'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xiv) Nature of Industry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('charField'),'readonly' => 'readonly'),
				'#value' 	    	=> !empty($industry_nature) ? $industry_nature : '',
				//'#element_validate' => array('element_validate_hyphen_fullstop_ampersand'),
			);
			$form['factory_information']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xv) Registration No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($RegistrationNo) ? $RegistrationNo : '',
				//'#element_validate' => array('element_validate_factory_reg_no'),
			);
			
			$formated_RegistrationDate = trim(implode('-', array_reverse(explode('-', $RegistrationDate))));
			$form['factory_information']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvi) Registration Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($formated_RegistrationDate) ? $formated_RegistrationDate : '',
				//'#element_validate' => array('element_validate_date'),
			);
			/*$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('numeric_positive'),'readonly' => 'readonly'),
				'#value' 			=> !empty($LicenceNo) ? $LicenceNo : '',
				'#element_validate' => array('element_validate_numeric_positive'),
			);*/
			$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($LicenceNo) ? $LicenceNo : '',
			);
			
			$formated_LicenceDate = trim(implode('-', array_reverse(explode('-', $LicenceDate))));
			$form['factory_information']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xviii) Licence Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($formated_LicenceDate) ? $formated_LicenceDate : '',
				//'#element_validate' => array('element_validate_date'),
			);
			
			if(!empty($ClassificationNo)) {
				$form['factory_information']['classification_no'] = array(
					'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
					'#suffix' 			=> '</label></div></div>',
					'#title' 			=> t('(xix) Classification No.:'),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
					'#attributes' 		=> array('class' => array(''),'placeholder' => 'Classification No.','readonly' => 'readonly'),
					'#value' 			=> !empty($ClassificationNo) ? $ClassificationNo : '',
					//'#element_validate' => array('element_validate_factory_classif_no'),
				);
			} else {
				unset($form_state['input']['classification_no']);
				$form['factory_information']['classification_no'] = array(
					'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
					'#suffix' 			=> '</label></div></div>',
					'#title' 			=> t('(xix) Classification No.:'),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
					'#attributes' 		=> array('class' => array(''),'placeholder' => 'Classification No.'),
					'#autocomplete_path'=> 'nicautocomplete',
					'#id' 				=> 'niccode_autocomplete',
					'#default_value' 	=> !empty($ClassificationNo) ? $ClassificationNo : '',
					//'#element_validate' => array('element_validate_factory_classif_no'),
				);
			}
			
			$form['factory_information']['occupier_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-7 col-xs-12"><h4><b>Occupier\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			$form['factory_information']['occupier_details_update'] = array(
				'#prefix' 				=> '<div id="occupier_details_update_id"><div class="col-md-5 col-xs-12">'.$occupier_details_update_link,
				'#suffix' 				=> '</div></div>',
			);
			
			/*if(!empty($occupier_name)) {
				$form['factory_information']['occupier_name'] = array(
					'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' 				=> '</label></div></div>',
					'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name','readonly' => 'readonly'),
					'#title' 			 	=> t('(xx) Occupier Name'),
					'#value' 	 	        => !empty($occupier_name) ? $occupier_name : '',
					'#required' 			=> TRUE,
					'#type' 				=> 'textfield',
				);
			} else {*/
			$form['factory_information']['occupier_name'] = array(
				'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name','readonly' => 'readonly'),
				'#title' 			 	=> t('(xx) Occupier Name'),
				'#value' 	 	        => !empty($ar_occupier_name) ? $ar_occupier_name : $occupier_name,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);	
			//}
			
	//occupier address section
			
			$pincode_occupier_val = !empty($ar_pincodeoprmntadr_occupier) ? $ar_pincodeoprmntadr_occupier : $factory_pincodeoprmntadr_occupier;
			
			$form['factory_information']['pincodeoprmntadr']       = array(
				'#prefix' 				=> '<div id="pincodeoprmntadr_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode','readonly' => 'readonly'),
				'#autocomplete_path' 	=> 'pinautocomplete',
				'#id' 				 	=> 'pincode_autocomplete_occupier',
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(xxi) Pincode'),
				'#value' 	 			=> $pincode_occupier_val,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
			);
			
			$state_occupier_val = !empty($ar_state_oprmntadr_occupier) ? $ar_state_oprmntadr_occupier : $factory_state_oprmntadr_occupier;
			
			$form['factory_information']['state_oprmntadr'] = array(
				'#title' 		=> '(xxii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_occupier_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($state_occupier_val),
				'#value' 	 	=> $state_occupier_val,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$district_occupier_val = !empty($ar_district_oprmntadr_occupier) ? $ar_district_oprmntadr_occupier : $factory_district_oprmntadr_occupier;
			
			$form['factory_information']['district_oprmntadr'] = array(
				'#title' => '(xxiii) District',
				'#type' => 'select',
				'#id' => 'district_occupier_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($state_occupier_val),
				'#value' 	=> $district_occupier_val,
				'#required' => TRUE,
				'#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$sub_division_occupier_val = !empty($ar_subdivision_oprmntadr_occupier) ? $ar_subdivision_oprmntadr_occupier : $factory_subdivision_oprmntadr_occupier;
			
			$form['factory_information']['subdivision_oprmntadr'] = array(
				'#title' => '(xxiv) Sub-Division',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division','disabled' => 'disabled'),
				'#options' => common_custom_user_subdivisionlist_list_new($district_occupier_val),
				'#required' => TRUE,
				'#value' 	=> $sub_division_occupier_val,
				'#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$area_type_occupier_val = !empty($ar_areatype_oprmntadr_occupier) ? $ar_areatype_oprmntadr_occupier : $factory_areatype_oprmntadr_occupier;
			
			$form['factory_information']['areatype_oprmntadr'] = array(
				'#title' => '(xxv) Area Type',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type','disabled' => 'disabled'),
				'#options' => common_custom_user_areatype_list_new($district_occupier_val, $sub_division_occupier_val),
				'#required' => TRUE,
				'#value' 	=> $area_type_occupier_val,
				'#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			if ($area_type_occupier_val == 'B') {
				$areatype_name_occupier = 'Block';
			} elseif ($area_type_occupier_val == 'M') {
				$areatype_name_occupier = 'Municipality';
			} elseif ($area_type_occupier_val == 'C') {
				$areatype_name_occupier = 'Corporation';
			} elseif ($area_type_occupier_val == 'S') {
				$areatype_name_occupier = 'SEZ';
			} elseif ($area_type_occupier_val == 'N') {
				$areatype_name_occupier = 'Notified Area';
			}
			
			$block_occupier_val = !empty($ar_block_oprmntadr_occupier) ? $ar_block_oprmntadr_occupier : $factory_block_oprmntadr_occupier;
					
			$form['factory_information']['block_oprmntadr'] = array(
				'#title' 		=> '(xxvi) '. $areatype_name_occupier,
				'#type'         => 'select',
				'#disabled' => TRUE,
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block','disabled' => 'disabled'),
				'#options' 		=> common_custom_user_block_list_new($sub_division_occupier_val, $area_type_occupier_val),
				'#required' 	=> TRUE,
				'#value' 	    => $block_occupier_val,
				'#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			if ($area_type_occupier_val == 'B') {
				$area_name_occupier = 'Gram Panchayat';
				$area_code_occupier = 'V';
			} elseif ($area_type_occupier_val == 'M') {
				$area_name_occupier = 'Ward';
				$area_code_occupier = 'W';
			} elseif ($area_type_occupier_val == 'C') {
				$area_name_occupier = 'Ward';
				$area_code_occupier = 'C';
			} elseif ($area_type_occupier_val == 'S') {
				$area_name_occupier = 'Sector';
				$area_code_occupier = 'S';
			} elseif ($area_type_occupier_val == 'N') {
				$area_name_occupier = 'Notified Area';
				$area_code_occupier = 'N';
			}
				
			$form['factory_information']['panchayat_oprmntadr'] = array(
				'#title' => '(xxvii) '.$area_name_occupier,
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat','disabled' => 'disabled'),
				'#options' => common_custom_user_villward_list_new($block_occupier_val, $area_code_occupier),
				'#value' 	    => !empty($ar_panchayat_oprmntadr_occupier) ? $ar_panchayat_oprmntadr_occupier : $factory_panchayat_oprmntadr_occupier,
				'#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$form['factory_information']['policestation_oprmntadr'] = array(
				'#title' => '(xxviii) Police Station',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station','disabled' => 'disabled'),
				'#options' => common_custom_user_ps_list_new($district_occupier_val),
				'#required' => TRUE,
				'#value' 	    => !empty($ar_policestation_oprmntadr_occupier) ? $ar_policestation_oprmntadr_occupier : $factory_policestation_oprmntadr_occupier,
				'#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['postoffice_oprmntadr'] = array(
				'#title' => '(xxix) Post Office',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office','disabled' => 'disabled'),
				'#options' => common_custom_post_office_list_new($pincode_occupier_val),
				'#value' 	    => !empty($ar_postoffice_oprmntadr_occupier) ? $ar_postoffice_oprmntadr_occupier : $factory_postoffice_oprmntadr_occupier,
				'#required' => TRUE,
				'#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['addrline_oprmntadr'] = array(
				'#prefix' => '<div id="addrline_oprmntadr_occupier_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xxx) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' 	    => !empty($ar_addrline_oprmntadr_occupier) ? $ar_addrline_oprmntadr_occupier : $factory_addrline_oprmntadr_occupier,
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line','readonly' => 'readonly'),
				'#element_validate' => array('element_validate_streetaddress'), 
			);
				
	//occupier address section end
			
			$form['factory_information']['manager_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-7 col-xs-12"><h4><b>Manager\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			$form['factory_information']['manager_details_update'] = array(
				'#prefix' 				=> '<div id="manager_details_update_id"><div class="col-md-5 col-xs-12">'.$manager_details_update_link,
				'#suffix' 				=> '</div></div>',
			);
				
			/*if(!empty($manager_name)) {
				$form['factory_information']['manager_name'] = array(
					'#prefix' 				=> '<div id="manager_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' 				=> '</label></div></div>',
					'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name','readonly' => 'readonly'),
					'#title' 			 	=> t('(xxxi) Manager Name'),
					'#value' 	 	        => !empty($manager_name) ? $manager_name : '',
					'#required' 			=> TRUE,
					'#type' 				=> 'textfield',
				);
			} else {*/
			$form['factory_information']['manager_name'] = array(
				'#prefix' 				=> '<div id="manager_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name','readonly' => 'readonly'),
				'#title' 			 	=> t('(xxxi) Manager Name'),
				'#value' 	 	        => !empty($ar_manager_name) ? $ar_manager_name : $manager_name,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);	
			//}
			
	//manager address section
			
			$pincode_manager_val = !empty($ar_pincode_manager) ? $ar_pincode_manager : $factory_pincode_manager;
			
			$form['factory_information']['pincode_manager']       = array(
				'#prefix' 				=> '<div id="pincode_manager_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode','readonly' => 'readonly'),
				'#autocomplete_path' 	=> 'pinautocomplete',
				'#id' 				 	=> 'pincode_autocomplete_manager',
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(xxxii) Pincode'),
				'#value' 	 			=> $pincode_manager_val,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
			);
			
			$state_manager_val = !empty($ar_state_manager) ? $ar_state_manager : $factory_state_manager;
			
			$form['factory_information']['state_manager'] = array(
				'#title' 		=> '(xxxiii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_manager_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($state_manager_val),
				'#value' 	 	=> $state_manager_val,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$district_manager_val = !empty($ar_district_manager) ? $ar_district_manager : $factory_district_manager;
			
			$form['factory_information']['district_manager'] = array(
				'#title' => '(xxxiv) District',
				'#type' => 'select',
				'#id' => 'district_manager_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($state_manager_val),
				'#value' 	=> $district_manager_val,
				'#required' => TRUE,
				'#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$sub_division_manager_val = !empty($ar_sub_division_manager) ? $ar_sub_division_manager : $factory_sub_division_manager;
			
			$form['factory_information']['sub_division_manager'] = array(
				'#title' => '(xxxv) Sub-Division',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division','disabled' => 'disabled'),
				'#options' => common_custom_user_subdivisionlist_list_new($district_manager_val),
				'#required' => TRUE,
				'#value' 	=> $sub_division_manager_val,
				'#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$area_type_manager_val = !empty($ar_area_type_manager) ? $ar_area_type_manager : $factory_area_type_manager;
			
			$form['factory_information']['area_type_manager'] = array(
				'#title' => '(xxxvi) Area Type',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type','disabled' => 'disabled'),
				'#options' => common_custom_user_areatype_list_new($district_manager_val, $sub_division_manager_val),
				'#required' => TRUE,
				'#value' 	=> $area_type_manager_val,
				'#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			if ($area_type_manager_val == 'B') {
				$areatype_name_manager = 'Block';
			} elseif ($area_type_manager_val == 'M') {
				$areatype_name_manager = 'Municipality';
			} elseif ($area_type_manager_val == 'C') {
				$areatype_name_manager = 'Corporation';
			} elseif ($area_type_manager_val == 'S') {
				$areatype_name_manager = 'SEZ';
			} elseif ($area_type_manager_val == 'N') {
				$areatype_name_manager = 'Notified Area';
			}
			
			$block_mun_cor_sez_not_manager_val = !empty($ar_block_mun_cor_sez_not_manager) ? $ar_block_mun_cor_sez_not_manager : $factory_block_mun_cor_sez_not_manager;
					
			$form['factory_information']['block_mun_cor_sez_not_manager'] = array(
				'#title' 		=> '(xxxvii) '. $areatype_name_manager,
				'#type'         => 'select',
				'#disabled' => TRUE,
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block','disabled' => 'disabled'),
				'#options' 		=> common_custom_user_block_list_new($sub_division_manager_val, $area_type_manager_val),
				'#required' 	=> TRUE,
				'#value' 	    => $block_mun_cor_sez_not_manager_val,
				'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			if ($area_type_manager_val == 'B') {
				$area_name_manager = 'Gram Panchayat';
				$area_code_manager = 'V';
			} elseif ($area_type_manager_val == 'M') {
				$area_name_manager = 'Ward';
				$area_code_manager = 'W';
			} elseif ($area_type_manager_val == 'C') {
				$area_name_manager = 'Ward';
				$area_code_manager = 'C';
			} elseif ($area_type_manager_val == 'S') {
				$area_name_manager = 'Sector';
				$area_code_manager = 'S';
			} elseif ($area_type_manager_val == 'N') {
				$area_name_manager = 'Notified Area';
				$area_code_manager = 'N';
			}
				
			$form['factory_information']['grm_ward_sector_not_manager'] = array(
				'#title' => '(xxxviii) '.$area_name_manager,
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat','disabled' => 'disabled'),
				'#options' => common_custom_user_villward_list_new($block_mun_cor_sez_not_manager_val, $area_code_manager),
				'#value' 	    => !empty($ar_grm_ward_sector_not_manager) ? $ar_grm_ward_sector_not_manager : $factory_grm_ward_sector_not_manager,
				'#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
				
			$form['factory_information']['police_station_manager'] = array(
				'#title' => '(xxxix) Police Station',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station','disabled' => 'disabled'),
				'#options' => common_custom_user_ps_list_new($district_manager_val),
				'#required' => TRUE,
				'#value' 	    => !empty($ar_police_station_manager) ? $ar_police_station_manager : $factory_police_station_manager,
				'#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['post_office_manager'] = array(
				'#title' => '(xl) Post Office',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office','disabled' => 'disabled'),
				'#options' => common_custom_post_office_list_new($pincode_manager_val),
				'#value' 	    => !empty($ar_post_office_manager) ? $ar_post_office_manager : $factory_post_office_manager,
				'#required' => TRUE,
				'#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
            
            $form['factory_information']['adress_line1_manager'] = array(
				'#prefix' => '<div id="adress_line1_manager_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div></div>',
				'#title' => '(xli) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' 	    => !empty($ar_adress_line1_manager) ? $ar_adress_line1_manager : $factory_adress_line1_manager,
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line','readonly' => 'readonly'),
				'#element_validate' => array('element_validate_streetaddress'), 
			);
			
	//manager address section end
			
		} 
		
		else {
			unset($form_state['input']);
			
			$form['factory_information']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id">',
				'#suffix' 			=> '</div>',
				'#title' 			=> t('(i)a. Enter factory_typeid'),
				'#type' 			=> 'hidden',
				//'#value' 			=> '',
			);
	
			$form['factory_information']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id">',
				'#suffix' 			=> '</div>',
				'#title' 			=> t('(i)a. Enter reference_number'),
				'#type' 			=> 'hidden',
				//'#value' 			=> '',
			);
			
	//factory name and address section
	
			$form['factory_information']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(i)a. Enter Registered Factory Name'),
				'#attributes' 		=> array('class' => array( ''),'placeholder' => 'Registered Factory Name'),
				'#type' 			=> 'textfield',
				//'#value' 			=> '',
				'#required' 		=> TRUE,
			);
			$form['factory_information']['pincode']       = array(
				'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(ii) Pincode'),
				//'#value' 				=> '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
			
			$form['factory_information']['state'] = array(
				'#title' => '(iii) State',
				'#type' => 'select',
				'#id' => 'state_name',
				'#disabled' => TRUE,
				'#attributes' => array(
					'class' => array(''),
					'placeholder' => 'State',
					'disabled' => 'disabled'
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#options' => array('' => t('Select State')),
				'#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$form['factory_information']['district'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'District','disabled' => 'disabled'),
				'#required' => TRUE,
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 		=> '',
				'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
				
			$form['factory_information']['subdivision'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Sub Division'
				),
				'#required' => TRUE,
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				//'#value' 		=> '',
				'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['areatype'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
	
					'placeholder' => 'Area Type'
				),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['block'] = array(
				'#title' => '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Block'
				),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-6"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
				'#suffix' => '</label></div></div>'
			);
		   
			$form['factory_information']['panchayat'] = array(
				'#title' => '(viii) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'panchayat'
				),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['policestation'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Police Station'
				),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['postoffice'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Post Office'
				),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(xi) Factory Zone'),
				'#type' => 'textfield',
				'#required' => TRUE,
				//'#value' => '',
				'#attributes' => array('class' => array(''),'readonly' => 'readonly','placeholder' => 'Factory Zone'),
			);
			
			$form['factory_information']['nearest_landmark'] = array(
				'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => t('(xii) Nearest Landmark'),
				'#type' => 'textfield',
				//'#value' => '',
				'#required' => TRUE,
				'#attributes' => array('class' => array('charField'),'placeholder' => 'Nearest Landmark'),
				'#required' => TRUE,
			);		
		
			$form['factory_information']['addrline'] = array(
				'#title' => '(xiii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				//'#value' => '',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Address Line',
				),
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>'
			);
			
	//factory address section end
			
			$form['factory_information']['industry_nature'] = array(
				'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xiv) Nature of Industry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Nature of Industry','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xv) Registration No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Registration No.','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			$form['factory_information']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvi) Registration Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				//'#value' 			=> '',
				//'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Registration Date.','disabled' => 'disabled','placeholder' => 'Registration Date'),
				'#attributes' 		=> array('class'=>array(''),'readonly' => 'readonly','placeholder' => 'Registration Date'),
	
			);
			/*$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('numeric_positive'),'readonly' => 'readonly'),
				//'#value' 			=> '',
			);*/
			$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'hidden',
				//'#value' 			=> '',
			);
			$form['factory_information']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xviii) Licence Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				//'#value' 			=> '',
				//'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Licence Date.','disabled' => 'disabled','placeholder' => 'Licence Date'),
				'#attributes' 		=> array('class'=>array(''),'readonly' => 'readonly','placeholder' => 'Licence Date'),
			);
			$form['factory_information']['classification_no'] = array(
				'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xix) Classification No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Classification No.','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['occupier_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-7 col-xs-12"><h4><b>Occupier\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			$form['factory_information']['occupier_details_update'] = array(
				'#prefix' 				=> '<div id="occupier_details_update_id"><div class="col-md-5 col-xs-12">'.$occupier_details_update_link,
				'#suffix' 				=> '</div></div>',
			);
			
			$form['factory_information']['occupier_name'] = array(
				'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name'),
				'#title' 			 	=> t('(xx) Occupier Name'),
				//'#value' 				=> '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
				
		//occupier address section
			
			$form['factory_information']['pincodeoprmntadr']       = array(
				'#prefix' 				=> '<div id="pincodeoprmntadr_occupier_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(xxi) Pincode'),
				//'#value' 	 	        => '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
			
			$form['factory_information']['state_oprmntadr'] = array(
				'#title' 		=> '(xxii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_occupier_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' => array('' => t('Select State')),
				//'#value' 	 	=> '',
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$form['factory_information']['district_oprmntadr'] = array(
				'#title' => '(xxiii) District',
				'#type' => 'select',
				'#id' => 'district_occupier_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 	=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['subdivision_oprmntadr'] = array(
				'#title' => '(xxiv) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$form['factory_information']['areatype_oprmntadr'] = array(
				'#title' => '(xxv) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['block_oprmntadr'] = array(
				'#title' 		=> '(xxvi) Block / Municipality / Corporation / Notified Area / SEZ',
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				'#required' 	=> TRUE,
				//'#value' 	    => '',
				'#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
				
			$form['factory_information']['panchayat_oprmntadr'] = array(
				'#title' => '(xxvii) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				//'#value' 	    => '',
				'#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$form['factory_information']['policestation_oprmntadr'] = array(
				'#title' => '(xxviii) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				'#required' => TRUE,
				//'#value' 	    => '',
				'#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['postoffice_oprmntadr'] = array(
				'#title' => '(xxix) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				//'#value' 	    => '',
				'#required' => TRUE,
				'#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['addrline_oprmntadr'] = array(
				'#prefix' => '<div id="addrline_oprmntadr_occupier_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xxx) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				//'#value' 	    => '',
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
			);			
				
		//occupier address section end
		
			$form['factory_information']['manager_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-7 col-xs-12"><h4><b>Manager\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			$form['factory_information']['manager_details_update'] = array(
				'#prefix' 				=> '<div id="manager_details_update_id"><div class="col-md-5 col-xs-12">'.$manager_details_update_link,
				'#suffix' 				=> '</div></div>',
			);
			
			$form['factory_information']['manager_name'] = array(
				'#prefix' 				=> '<div id="manager_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name'),
				'#title' 			 	=> t('(xxxi) Manager Name'),
				//'#value' 				=> '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
				
		//manager address section
				
			$form['factory_information']['pincode_manager']       = array(
				'#prefix' 				=> '<div id="pincode_manager_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(xxxii) Pincode'),
				//'#value' 	 	        => '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
			
			$form['factory_information']['state_manager'] = array(
				'#title' 		=> '(xxxiii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_manager_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' => array('' => t('Select State')),
				//'#value' 	 	=> '',
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$form['factory_information']['district_manager'] = array(
				'#title' => '(xxxiv) District',
				'#type' => 'select',
				'#id' => 'district_manager_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 	=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['sub_division_manager'] = array(
				'#title' => '(xxxv) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$form['factory_information']['area_type_manager'] = array(
				'#title' => '(xxxvi) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['block_mun_cor_sez_not_manager'] = array(
				'#title' 		=> '(xxxvii) Block / Municipality / Corporation / Notified Area / SEZ',
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				'#required' 	=> TRUE,
				//'#value' 	    => '',
				'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
				
			$form['factory_information']['grm_ward_sector_not_manager'] = array(
				'#title' => '(xxxviii) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				//'#value' 	    => '',
				'#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$form['factory_information']['police_station_manager'] = array(
				'#title' => '(xxxix) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				'#required' => TRUE,
				//'#value' 	    => '',
				'#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['post_office_manager'] = array(
				'#title' => '(xl) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				//'#value' 	    => '',
				'#required' => TRUE,
				'#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['adress_line1_manager'] = array(
				'#prefix' => '<div id="adress_line1_manager_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div></div>',
				'#title' => '(xli) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				//'#value' 	    => '',
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
			);
				
	//manager address section end						
		
		}
		
		if($get_medical_officer_details->annual_return_id != NULL || $get_hospital_details->annual_return_id != NULL || $get_details_payment->annual_return_id != NULL || $get_emplm_dism_pay_bonus_women->annual_return_id != NULL) {
			
			$form['#attributes'] = array('onsubmit' => 'return validate_annual_return_common_form()');
		} else {
			$form['#attributes'] = array('onsubmit' => 'return validate_annual_return_common_form() && maternity_benefit_checking()');	
		}
			 
		$form['factory_information_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/annual-return-list', array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
	
	  return $form;
  }
  
	
	/*function get_factory_name($uid){
		$default_select 	= array(""=>"--Select--");
		$result 	 = db_query("SELECT id,factory_name FROM {fa_cafa} WHERE ((factory_registrstion_no !='') OR (backlog_registration_no !='')) AND created_by ='".$uid."'");
		$list 	 = array();
		foreach ($result as $record) {
			$list[$record->id] = t('@factoryname', array(
			'@factoryname' => $record->factory_name,
			));
		}
		$last_select 	= array(0=>"Other");
		return ($default_select+$list+$last_select);
	}*/

	function get_ajax_name_factory($form, $form_state){
	  
		$commands[] = ajax_command_replace('#factory_typeid_id', drupal_render($form['factory_information']['factory_typeid']));
		$commands[] = ajax_command_replace('#reference_number_id', drupal_render($form['factory_information']['reference_number']));
		$commands[] = ajax_command_replace('#factory_name_id', drupal_render($form['factory_information']['factory_name']));
		
		$commands[] = ajax_command_replace('#pincode_id', drupal_render($form['factory_information']['pincode']));
		$commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['factory_information']['state']));
		$commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['factory_information']['district']));
		$commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['factory_information']['subdivision']));
		$commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['factory_information']['areatype']));
		$commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['factory_information']['block']));
		$commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['factory_information']['panchayat']));
		$commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['factory_information']['policestation']));
		$commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['factory_information']['postoffice']));
		$commands[] = ajax_command_replace('#factory_zone_div', drupal_render($form['factory_information']['factory_zone_name']));
		$commands[] = ajax_command_replace('#nearest_landmark_id', drupal_render($form['factory_information']['nearest_landmark']));
		$commands[] = ajax_command_replace('#addrline_id', drupal_render($form['factory_information']['addrline']));
		
		$commands[] = ajax_command_replace('#industry_nature_id', drupal_render($form['factory_information']['industry_nature'])); 
		$commands[] = ajax_command_replace('#registration_number_id', drupal_render($form['factory_information']['registration_number']));
		$commands[] = ajax_command_replace('#registration_date_id', drupal_render($form['factory_information']['registration_date']));
		$commands[] = ajax_command_replace('#licence_number_id', drupal_render($form['factory_information']['licence_number']));
		$commands[] = ajax_command_replace('#licence_date_id', drupal_render($form['factory_information']['licence_date']));
		$commands[] = ajax_command_replace('#classification_no_id', drupal_render($form['factory_information']['classification_no']));
		
		$commands[] = ajax_command_replace('#occupier_details_update_id', drupal_render($form['factory_information']['occupier_details_update']));
		$commands[] = ajax_command_replace('#occupier_name_id', drupal_render($form['factory_information']['occupier_name']));
		$commands[] = ajax_command_replace('#pincodeoprmntadr_occupier_id', drupal_render($form['factory_information']['pincodeoprmntadr']));
		$commands[] = ajax_command_replace('#state_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['state_oprmntadr']));
		$commands[] = ajax_command_replace('#district_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['district_oprmntadr']));
		$commands[] = ajax_command_replace('#subdivision_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['subdivision_oprmntadr']));
		$commands[] = ajax_command_replace('#areatype_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['areatype_oprmntadr']));
		$commands[] = ajax_command_replace('#block_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['block_oprmntadr']));
		$commands[] = ajax_command_replace('#panchayat_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['panchayat_oprmntadr']));
		$commands[] = ajax_command_replace('#policestation_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['policestation_oprmntadr']));
		$commands[] = ajax_command_replace('#postoffice_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['postoffice_oprmntadr']));
		$commands[] = ajax_command_replace('#addrline_oprmntadr_occupier_id', drupal_render($form['factory_information']['addrline_oprmntadr']));
		
		$commands[] = ajax_command_replace('#manager_details_update_id', drupal_render($form['factory_information']['manager_details_update']));
		$commands[] = ajax_command_replace('#manager_name_id', drupal_render($form['factory_information']['manager_name']));
		$commands[] = ajax_command_replace('#pincode_manager_id', drupal_render($form['factory_information']['pincode_manager']));
		$commands[] = ajax_command_replace('#state_manager_id_replace', drupal_render($form['factory_information']['state_manager']));
		$commands[] = ajax_command_replace('#district_manager_id_replace', drupal_render($form['factory_information']['district_manager']));
		$commands[] = ajax_command_replace('#sub_division_manager_id_replace', drupal_render($form['factory_information']['sub_division_manager']));
		$commands[] = ajax_command_replace('#area_type_manager_id_replace', drupal_render($form['factory_information']['area_type_manager']));
		$commands[] = ajax_command_replace('#block_mun_cor_sez_not_manager_id_replace', drupal_render($form['factory_information']['block_mun_cor_sez_not_manager']));
		$commands[] = ajax_command_replace('#grm_ward_sector_not_manager_id_replace', drupal_render($form['factory_information']['grm_ward_sector_not_manager']));
		$commands[] = ajax_command_replace('#police_station_manager_id_replace', drupal_render($form['factory_information']['police_station_manager']));
		$commands[] = ajax_command_replace('#post_office_manager_id_replace', drupal_render($form['factory_information']['post_office_manager']));
		$commands[] = ajax_command_replace('#adress_line1_manager_id', drupal_render($form['factory_information']['adress_line1_manager']));
	  
	 	return array('#type' => 'ajax', '#commands' => $commands);
	}
  
	function get_ajax_load($form, $form_state)
	{
		$commands   = array();
		$commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['factory_information']['state']));
		$commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['factory_information']['district']));
		$commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['factory_information']['subdivision']));
		$commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['factory_information']['areatype']));
		$commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['factory_information']['block']));
		$commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['factory_information']['panchayat']));
		$commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['factory_information']['policestation']));
		$commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['factory_information']['postoffice']));
		$commands[] = ajax_command_replace('#factory_zone_div', drupal_render($form['factory_information']['factory_zone_name']));
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	}
	
	function get_occupier_ajax_load($form, $form_state) {
		
		$commands   = array();
		$commands[] = ajax_command_replace('#state_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['state_oprmntadr']));
		$commands[] = ajax_command_replace('#district_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['district_oprmntadr']));
		$commands[] = ajax_command_replace('#subdivision_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['subdivision_oprmntadr']));
		$commands[] = ajax_command_replace('#areatype_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['areatype_oprmntadr']));
		$commands[] = ajax_command_replace('#block_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['block_oprmntadr']));
		$commands[] = ajax_command_replace('#panchayat_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['panchayat_oprmntadr']));
		$commands[] = ajax_command_replace('#policestation_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['policestation_oprmntadr']));
		$commands[] = ajax_command_replace('#postoffice_oprmntadr_occupier_id_replace', drupal_render($form['factory_information']['postoffice_oprmntadr']));
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	}
	
	function get_manager_ajax_load($form, $form_state) {
		
		$commands   = array();
		$commands[] = ajax_command_replace('#state_manager_id_replace', drupal_render($form['factory_information']['state_manager']));
		$commands[] = ajax_command_replace('#district_manager_id_replace', drupal_render($form['factory_information']['district_manager']));
		$commands[] = ajax_command_replace('#sub_division_manager_id_replace', drupal_render($form['factory_information']['sub_division_manager']));
		$commands[] = ajax_command_replace('#area_type_manager_id_replace', drupal_render($form['factory_information']['area_type_manager']));
		$commands[] = ajax_command_replace('#block_mun_cor_sez_not_manager_id_replace', drupal_render($form['factory_information']['block_mun_cor_sez_not_manager']));
		$commands[] = ajax_command_replace('#grm_ward_sector_not_manager_id_replace', drupal_render($form['factory_information']['grm_ward_sector_not_manager']));
		$commands[] = ajax_command_replace('#police_station_manager_id_replace', drupal_render($form['factory_information']['police_station_manager']));
		$commands[] = ajax_command_replace('#post_office_manager_id_replace', drupal_render($form['factory_information']['post_office_manager']));
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	}
	
	
	function annual_return_common_validate($form, &$form_state) {
		$query_ar_common 	= db_select('fa_annual_return', 'ar');
		$query_ar_common	->fields('ar',array());
		$result_ar_common 	= $query_ar_common->execute();
		
		$latest_year = date('Y') - 1;
		$annual_return_year = $form_state['values']['annual_return_year'];
		
		if($annual_return_year != '') {
			if($annual_return_year != $latest_year) {
				form_set_error('Annual Return Year', t('You can submit Annual Return for the previous year only!'));
			}
			
			if($result_ar_common->rowCount() > 0) {
				while($data_ar_common = $result_ar_common->fetchObject()) {
					if($data_ar_common->cafa_id == $form_state['values']['factory_id'] && $data_ar_common->annual_return_year == $form_state['values']['annual_return_year']) {
						form_set_error('Factory Name', t('Annual Return for this Factory of the year '.$form_state['values']['annual_return_year'].' already submitted!'));		
					}
				}
			}
		}
		
	}
  
 	function annual_return_common_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		
		$uid 							= $user->uid;
		
		$annual_return_id = $form_state['values']['annual_return_id'];
		
		$factory_id = $form_state['values']['factory_id'];
		
		$service_name = 'Annual Return';
		$service_details = get_service_details($service_name);
		
		$val = $form_state['values'];
		
		if($factory_id != 0) {
			
			if($annual_return_id == 0) {
			
				$annual_return = array(
					'factory_name'         			=> $val['factory_name'],
					'cafa_id'              			=> $factory_id,
					'reference_number'     			=> $val['reference_number'],
					'industry_nature'        		=> $val['industry_nature'],
					'registration_number'  			=> $val['registration_number'],
					'registration_date'    			=> trim(implode('-', array_reverse(explode('-', $val['registration_date'])))),
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> trim(implode('-', array_reverse(explode('-', $val['licence_date'])))),
					'classification_no'    			=> $val['classification_no'],
					'pincode'	  		   			=> $val['pincode'],
					'state'         	   			=> $val['state'],
					'district'             			=> $val['district'],
					'subdivision'     	   			=> $val['subdivision'],
					'areatype'        	   			=> $val['areatype'],
					'block' 			   			=> $val['block'],
					'panchayat'    		   			=> $val['panchayat'],
					'policestation'        			=> $val['policestation'],
					'postoffice'          			=> $val['postoffice'],
					'factory_zone'         			=> $val['factory_zone'],
					'nearest_landmark'	   			=> $val['nearest_landmark'],
					'addrline'    		   			=> $val['addrline'],
					'uid' 				   			=> $uid,
					'created_date'		   			=> date('Y-m-d'),
					'full_application_status'   	=> 'In',
					'name_occupier'   				=> $val['occupier_name'],
					'name_manager'   				=> $val['manager_name'],
					'payment_wages_flag'   			=> $val['payment_wages_flag'],
					'factories_act_flag'   			=> $val['factories_act_flag'],
					'maternity_benefit_flag' 		=> $val['maternity_benefit_flag'],
					'annual_return_year' 			=> $val['annual_return_year'],
					'service_id' 					=> $service_details->id,
					'pincodeoprmntadr'				=> $val['pincodeoprmntadr'],
					'state_oprmntadr'				=> $val['state_oprmntadr'],
					'district_oprmntadr'			=> $val['district_oprmntadr'],
					'subdivision_oprmntadr'			=> $val['subdivision_oprmntadr'],
					'areatype_oprmntadr'			=> $val['areatype_oprmntadr'],
					'block_oprmntadr'				=> $val['block_oprmntadr'],
					'panchayat_oprmntadr'			=> $val['panchayat_oprmntadr'],
					'policestation_oprmntadr'		=> $val['policestation_oprmntadr'],
					'postoffice_oprmntadr'			=> $val['postoffice_oprmntadr'],
					'addrline_oprmntadr'			=> $val['addrline_oprmntadr'],
					'pincode_manager'				=> $val['pincode_manager'],
					'state_manager'					=> $val['state_manager'],
					'district_manager'				=> $val['district_manager'],
					'sub_division_manager'			=> $val['sub_division_manager'],
					'area_type_manager'				=> $val['area_type_manager'],
					'block_mun_cor_sez_not_manager'	=> $val['block_mun_cor_sez_not_manager'],
					'grm_ward_sector_not_manager'	=> $val['grm_ward_sector_not_manager'],
					'police_station_manager'		=> $val['police_station_manager'],
					'post_office_manager'			=> $val['post_office_manager'],
					'adress_line1_manager'			=> $val['adress_line1_manager'],
					'temp_cafa_id_occupier_data' 	=> NULL,
					'temp_cafa_id_manager_data'		=> NULL,
					'factory_typeid'				=> $val['factory_typeid'],
				);
				
				$annual_return_ID = db_insert('fa_annual_return')->fields($annual_return)->execute();			
				
			} else {
				
				$annual_return_ID = $annual_return_id;
				
				$annual_return = array(
					'factory_name'         			=> $val['factory_name'],
					'cafa_id'              			=> $factory_id,
					'reference_number'     			=> $val['reference_number'],
					'industry_nature'        		=> $val['industry_nature'],
					'registration_number'  			=> $val['registration_number'],
					'registration_date'    			=> trim(implode('-', array_reverse(explode('-', $val['registration_date'])))),
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> trim(implode('-', array_reverse(explode('-', $val['licence_date'])))),
					'classification_no'    			=> $val['classification_no'],
					'pincode'	  		   			=> $val['pincode'],
					'state'         	   			=> $val['state'],
					'district'             			=> $val['district'],
					'subdivision'     	   			=> $val['subdivision'],
					'areatype'        	   			=> $val['areatype'],
					'block' 			   			=> $val['block'],
					'panchayat'    		   			=> $val['panchayat'],
					'policestation'        			=> $val['policestation'],
					'postoffice'          			=> $val['postoffice'],
					'factory_zone'         			=> $val['factory_zone'],
					'nearest_landmark'	   			=> $val['nearest_landmark'],
					'addrline'    		   			=> $val['addrline'],
					'uid' 				   			=> $uid,
					'modification_date'	   			=> date('Y-m-d H:i:s'),
					'full_application_status'   	=> 'In',
					'name_occupier'   				=> $val['occupier_name'],
					'name_manager'   				=> $val['manager_name'],
					'payment_wages_flag'   			=> $val['payment_wages_flag'],
					'factories_act_flag'   			=> $val['factories_act_flag'],
					'maternity_benefit_flag' 		=> $val['maternity_benefit_flag'],
					'annual_return_year' 			=> $val['annual_return_year'],
					'service_id' 					=> $service_details->id,
					'pincodeoprmntadr'				=> $val['pincodeoprmntadr'],
					'state_oprmntadr'				=> $val['state_oprmntadr'],
					'district_oprmntadr'			=> $val['district_oprmntadr'],
					'subdivision_oprmntadr'			=> $val['subdivision_oprmntadr'],
					'areatype_oprmntadr'			=> $val['areatype_oprmntadr'],
					'block_oprmntadr'				=> $val['block_oprmntadr'],
					'panchayat_oprmntadr'			=> $val['panchayat_oprmntadr'],
					'policestation_oprmntadr'		=> $val['policestation_oprmntadr'],
					'postoffice_oprmntadr'			=> $val['postoffice_oprmntadr'],
					'addrline_oprmntadr'			=> $val['addrline_oprmntadr'],
					'pincode_manager'				=> $val['pincode_manager'],
					'state_manager'					=> $val['state_manager'],
					'district_manager'				=> $val['district_manager'],
					'sub_division_manager'			=> $val['sub_division_manager'],
					'area_type_manager'				=> $val['area_type_manager'],
					'block_mun_cor_sez_not_manager'	=> $val['block_mun_cor_sez_not_manager'],
					'grm_ward_sector_not_manager'	=> $val['grm_ward_sector_not_manager'],
					'police_station_manager'		=> $val['police_station_manager'],
					'post_office_manager'			=> $val['post_office_manager'],
					'adress_line1_manager'			=> $val['adress_line1_manager'],
					'temp_cafa_id_occupier_data' 	=> NULL,
					'temp_cafa_id_manager_data'		=> NULL,
					'factory_typeid'				=> $val['factory_typeid'],
				);
				
				db_update('fa_annual_return')->fields($annual_return)->condition('id', $annual_return_ID, '=')->execute();	
					
			}
			
		} 
		
		//die($annual_return_ID);
		drupal_goto('applicant/annual-return-common-apply/default/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
	  
		$form_state['rebuild'] = true;

	}
	
	
	

//this code is implemented at line 1059 if Other option is included in the Licence No. or Factory Name Dropdown. Otherwise it will be always comment off.	
	/*else if(($value_factory_id != NULL) && ($value_factory_id == 0)) {
			//unset($form_state['input']);
			$form['factory_information']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id">',
				'#suffix' 			=> '</div>',
				'#title' 			=> t('(i)a. Enter factory_typeid'),
				'#type' 			=> 'hidden',
				'#value'	=> 0,
			);
			
			unset($form_state['input']['reference_number']);
			$form['factory_information']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id">',
				'#suffix' 			=> '</div>',
				'#title' 			=> t('(i)a. Enter reference_number'),
				'#type' 			=> 'hidden',
				'#value'	=> 0,
			);
			
	//factory name and address section
		
			unset($form_state['input']['factory_name']);
			$form['factory_information']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(i)a. Enter Registered Factory Name'),
				'#attributes' 		=> array('class' => array( ''),'placeholder' => 'Registered Factory Name'),
				'#type' 			=> 'textfield',
				'#default_value' 			=> '',
				'#required' 		=> TRUE,
				'#element_validate' => array('element_validate_factory_name'),
			);
			
			$value_pincode     = isset($form_state['values']['pincode']) && !empty($form_state['values']['pincode']) ? $form_state['values']['pincode'] : '';
			unset($form_state['input']['pincode']);
		   	$form['factory_information']['pincode']       = array(
				'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#autocomplete_path' 	=> 'pinautocomplete',
				'#id' 				 	=> 'pincode_autocomplete',
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(ii) Pincode'),
				'#default_value' 	 	=> '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
				'#ajax' 				=> array(
													'effect' 	=> 'fade',
													'callback' 	=> 'get_ajax_load',
													'progress' 	=> array(
													 'type' 	=> 'throbber',
													'message' 	=> t('loading')
					)
				)
			);
			
			if (!empty($value_pincode)) {
				$query = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
							'districtname','statename',  'pincode','district_code', 'state_code', 'po_name'  ))
						->condition('p.pincode', trim($value_pincode), '=');
				
			   $result = $query->execute();
				if ($result->rowcount() > 0) {
					$final       = $result->fetchAssoc();
					$pincode_v   = $value_pincode;
					$state_v     = $final['state_code'];
					$district_v  = $final['district_code'];
					$post_office = $final['po_name'];
				}
			}
			
			$value_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : '';
		
			if(!empty($state_v)) {
				$form['factory_information']['state'] = array(
					'#title' 		=> '(iii) State',
					'#type' 		=> 'select',
					'#id' 			=> 'state_name',
					'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
					'#disabled' 	=> TRUE,
					'#options' 		=> get_all_state($state_v),
					'#value' 		=> !empty($state_v) ? $state_v : '',
					'#required' 	=> TRUE,
					'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' 		=> '</label></div></div>',
					'#ajax' => array(
										'event' => 'change',
										'effect' => 'fade',
										'callback' => 'get_ajax_load',
										'progress' => array(
															 'type' => 'throbber',
															 'message' => t('loading')
													 )
									)
				);
			} else {
				unset($form_state['input']['state']);
				$form['factory_information']['state'] = array(
					'#title' => '(iii) State',
					'#type' => 'select',
					'#id' => 'state_name',
					'#disabled' => TRUE,
					'#attributes' => array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
					'#value' 		=> '',
					'#required' => TRUE,
					'#options' => array(
						'' => t('Select State')
					),
					'#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			}
			
			$value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : '';
			
			if(!empty($state_v)) {
				$form['factory_information']['district'] = array(
					'#title' => '(iv) District',
					'#type' => 'select',
					'#id' => 'district_name',
					'#disabled' => TRUE,
					'#attributes' => array('class' => array(''),'placeholder' => 'District','disabled' => 'disabled'),
					'#options' => get_district_by_id($state_v),
					'#value' => !empty($district_v) ? $district_v : '',
					'#required' => TRUE,
					'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			} else {
				unset($form_state['input']['district']);
				$form['factory_information']['district'] = array(
					'#title' => '(iv) District',
					'#type' => 'select',
					'#id' => 'district_name',
					'#disabled' => TRUE,
					'#attributes' => array('class' => array(''),'placeholder' => 'District','disabled' => 'disabled'),
					'#required' => TRUE,
					'#options' => array(
						'' => t('Select District')
					),
					'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			}
			
			$value_subdivision = isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : '';
			
			if(!empty($district_v) && !empty($state_v)) {
			
				$form['factory_information']['subdivision'] = array(
					'#title' => '(v) Sub-Division',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Sub Division',
					),
					'#options' => common_custom_user_subdivisionlist_list_new($district_v),
					'#required' => TRUE,
					'#default_value' => '',
					'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			
			} else {
				unset($form_state['input']['subdivision']);
				$form['factory_information']['subdivision'] = array(
					'#title' => '(v) Sub-Division',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Sub Division'
					),
					'#required' => TRUE,
					'#options' => array(
						'' => t('Select Sub-Division')
					),
					'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			}
			
			$value_areatype = isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : '';
			
			if (!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
				$form['factory_information']['areatype'] = array(
					'#title' => '(vi) Area Type',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Area Type',
					),
					'#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
					'#required' => TRUE,
					'#default_value' => '',
					'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			} else {
				unset($form_state['input']['areatype']);
				$form['factory_information']['areatype'] = array(
					'#title' => '(vi) Area Type',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
				
						'placeholder' => 'Area Type'
					),
					'#options' => array(
						'0' => t('Select Area Type')
					),
					'#required' => TRUE,
					'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			}
			
			$value_block      = isset($form_state['values']['block']) ? $form_state['values']['block'] : '';
			
			if (!empty($value_district) && !empty($value_state) && $value_subdivision != "" && !empty($value_areatype)) {
			
				if ($value_areatype == 'B') {
					$areatype_name = 'Block';
				} elseif ($value_areatype == 'M') {
					$areatype_name = 'Municipality';
				} elseif ($value_areatype == 'C') {
					$areatype_name = 'Corporation';
				} elseif ($value_areatype == 'S') {
					$areatype_name = 'SEZ';
				} elseif ($value_areatype == 'N') {
					$areatype_name = 'Notified Area';
				}
				
				$form['factory_information']['block'] = array(
					'#title' => '(vii) '. $areatype_name,
					'#type' => 'select',
				
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Block',
					),
					'#options' 		=> common_custom_user_block_list_new($value_subdivision, $value_areatype),
					'#required' 	=> TRUE,
					'#default_value'=> '',
					'#prefix' 		=> '<div id="ld_empareatype_name_replace"><div class="col-md-6"><label class="select label-block">',
					'#suffix' 		=> '</label></div></div>',
					'#ajax' 		=> array(
					'event' 		=> 'change',
					'effect' 		=> 'fade',
					'callback' 		=> 'get_ajax_load',
					'progress' 		=> array(
					'type' 			=> 'throbber',
					'message' 		=> t('loading')
						)
					)
				);
			
			} else {
				unset($form_state['input']['block']);
				$form['factory_information']['block'] = array(
					'#title' => '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Block'
					),
					'#options' => array(
						'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
					),
					'#required' => TRUE,
					'#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-6"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			}
			
			$value_panchayat = isset($form_state['values']['panchayat']) ? $form_state['values']['panchayat'] : '';
			
			if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state)) {
			
				if ($value_areatype == 'B') {
					$area_name = 'Gram Panchayat';
					$area_code = 'V';
				} elseif ($value_areatype == 'M') {
					$area_name = 'Ward';
					$area_code = 'W';
				} elseif ($value_areatype == 'C') {
					$area_name = 'Ward';
					$area_code = 'C';
				} elseif ($value_areatype == 'S') {
					$area_name = 'Sector';
					$area_code = 'S';
				} elseif ($value_areatype == 'N') {
					$area_name = 'Notified Area';
					$area_code = 'N';
				}
				
				$form['factory_information']['panchayat'] = array(
					'#title' => '(viii) '.$area_name,
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'panchayat',
						
					),
					'#options' => common_custom_user_villward_list_new($value_block, $area_code),
					'#default_value' => '',
					'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-6"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#required' => TRUE,
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',	
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			} else {
				unset($form_state['input']['panchayat']);
				$form['factory_information']['panchayat'] = array(
					'#title' => '(viii) Gram Panchayat / Ward / Sector',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'panchayat'
					),
					'#options' => array(
						'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
					),
					'#required' => TRUE,
					'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-6"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			}
		
			if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state) && !empty($value_panchayat)) {
				$form['factory_information']['policestation'] = array(
					'#title' => '(ix) Police Station',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Police Station',
					),
					'#options' => common_custom_user_ps_list_new($value_district),
					'#required' => TRUE,
					'#default_value' => '',
					'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
				);
			} else {
				unset($form_state['input']['policestation']);
				$form['factory_information']['policestation'] = array(
					'#title' => '(ix) Police Station',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Police Station'
					),
					'#options' => array(
						'0' => t('Select Police Station')
					),
					'#required' => TRUE,
					'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
				);
			}
		
			if (!empty($pincode_v)) {
				$form['factory_information']['postoffice'] = array(
					'#title' => '(x) Post Office',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Post Office',
					),
					'#options' => common_custom_post_office_list_new($pincode_v),
					'#default_value' => '',
					'#required' => TRUE,
					'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
				);
			} else {
				unset($form_state['input']['postoffice']);
				$form['factory_information']['postoffice'] = array(
					'#title' => '(x) Post Office',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Post Office'
					),
					'#options' => array(
						'0' => t('Select Post Office')
					),
					'#required' => TRUE,
					'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
				);
			}
		
			if (!empty($value_block) && !empty($value_panchayat)) {
			
				$factory_zone_name = get_zone_name($value_block,$value_panchayat);
				
				$form['factory_information']['factory_zone'] = array(
					'#value'   => $factory_zone_name[0]->zone_id,
					'#type' => 'hidden',
				);
				
				$form['factory_information']['factory_zone_name'] = array(
					'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title'  => t('(xi) Factory Zone'),
					'#value'   => $factory_zone_name[0]->zone_name,
		
					'#type' => 'textfield',
					'#required' => TRUE,
					'#attributes'		=> array('class' => array(''),'readonly' => 'readonly','placeholder' => 'Factory Zone'),
					'#element_validate' 	=> array('element_validate_hyphenfullstop'),
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
		   } else {
				unset($form_state['input']['factory_zone_name']);
				$form['factory_information']['factory_zone_name'] = array(
					'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title'  => t('(xi) Factory Zone'),
					'#type' => 'textfield',
					'#required' => TRUE,
					'#attributes' => array('class' => array(''),'placeholder' => 'Factory Zone'),
					'#element_validate' 	=> array('element_validate_hyphenfullstop'),
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			}
			
			unset($form_state['input']['nearest_landmark']);
			$form['factory_information']['nearest_landmark'] = array(
				'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => t('(xii) Nearest Landmark'),
				'#type' => 'textfield',
				'#default_value' => '',
				'#attributes' => array('class' => array('charField'),'placeholder' => 'Nearest Landmark'),
				'#element_validate' 	=> array('element_validate_alphabatic_text'),
				'#required' => TRUE,
			);
			
			unset($form_state['input']['addrline']);
			$form['factory_information']['addrline'] = array(
				'#title' => '(xiii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#default_value' => '',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Address Line',
				),
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#element_validate' => array('element_validate_streetaddress'), 
			);		
		
	//factory address section end
	
			unset($form_state['input']['industry_nature']);
			$form['factory_information']['industry_nature'] = array(
				'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xiv) Nature of Industry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('charField'),'placeholder' => 'Nature of Industry'),
				'#default_value' 	=> '',
				'#element_validate' => array('element_validate_hyphen_fullstop_ampersand'),
			);
			unset($form_state['input']['registration_number']);
			$form['factory_information']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xv) Registration No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Registration No.'),
				//'#default_value' 	=> $registration_number,
				'#default_value' 	=> !empty($RegistrationNo) ? $RegistrationNo : '',
				'#element_validate' => array('element_validate_factory_reg_no'),
			);
			unset($form_state['input']['registration_date']);
			$formated_RegistrationDate = trim(implode('-', array_reverse(explode('-', $RegistrationDate))));
			$form['factory_information']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvi) Registration Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Registration Date.','readonly' => 'readonly'),
				'#default_value' 	=> !empty($formated_RegistrationDate) ? $formated_RegistrationDate : '',
				'#element_validate' => array('element_validate_date'),
			);
			unset($form_state['input']['licence_number']);
			$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('numeric_positive'),'placeholder' => 'Licence No.'),
				'#default_value' 	=> !empty($LicenceNo) ? $LicenceNo : '',
				'#element_validate' => array('element_validate_numeric_positive'),
			);
			unset($form_state['input']['licence_date']);
			$formated_LicenceDate = trim(implode('-', array_reverse(explode('-', $LicenceDate))));
			$form['factory_information']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xviii) Licence Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Licence Date.','readonly' => 'readonly'),
				'#default_value' 	=> !empty($formated_LicenceDate) ? $formated_LicenceDate : '',
				'#element_validate' => array('element_validate_date'),
			);
			unset($form_state['input']['classification_no']);
			$form['factory_information']['classification_no'] = array(
				'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xix) Classification No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Classification No.'),
				'#default_value' 	=> !empty($ClassificationNo) ? $ClassificationNo : '',
				'#element_validate' => array('element_validate_factory_classif_no'),
			);
			
			$form['factory_information']['occupier_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-7 col-xs-12"><h4><b>Occupier\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			$form['factory_information']['occupier_details_update'] = array(
				'#prefix' 				=> '<div id="occupier_details_update_id"><div class="col-md-5 col-xs-12">'.$occupier_details_update_link,
				'#suffix' 				=> '</div></div>',
			);
			
			unset($form_state['input']['occupier_name']);
			$form['factory_information']['occupier_name'] = array(
				'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name'),
				'#title' 			 	=> t('(xx) Occupier Name'),
				'#default_value' 	 	        => '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);
			
	//occupier address section
	
			unset($form_state['input']['pincodeoprmntadr']);
			$form['factory_information']['pincodeoprmntadr']       = array(
                '#prefix' 				=> '<div id="pincodeoprmntadr_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
                '#suffix' 				=> '</label></div></div>',
                '#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
                '#autocomplete_path' 	=> 'pinautocomplete',
                '#id' 				 	=> 'pincode_autocomplete_occupier',
                '#maxlength' 		 	=> 6,
                '#title' 			 	=> t('(xxi) Pincode'),
                '#default_value' 	 	=> '',
                '#required' 			=> TRUE,
                '#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
                '#ajax' 				=> array(
                                                    'effect' 	=> 'fade',
                                                    'callback' 	=> 'get_occupier_ajax_load',
                                                    'progress' 	=> array(
                                                     'type' 	=> 'throbber',
                                                    'message' 	=> t('loading')
                    )
                )
            );
			
			$value_pincode_occupier    = isset($form_state['values']['pincodeoprmntadr']) && !empty($form_state['values']['pincodeoprmntadr']) ? $form_state['values']['pincodeoprmntadr'] : '';
			
			if(!empty($value_pincode_occupier)) {
				
				$query_pin_occupier = db_select('fa_all_india_pin_code', 'p')
									->fields('p', array('districtname','statename',  'pincode','district_code', 'state_code', 'po_name'))
									->condition('p.pincode', trim($value_pincode_occupier), '=');
				
			   	$result_pin_occupier = $query_pin_occupier->execute();
				if ($result_pin_occupier->rowcount() > 0) {
					$final_pin_occupier       = $result_pin_occupier->fetchAssoc();
					$pincode_v_occupier   = $value_pincode_occupier;
					$state_v_occupier     = $final_pin_occupier['state_code'];
					$district_v_occupier  = $final_pin_occupier['district_code'];
					$post_office_occupier = $final_pin_occupier['po_name'];
				}
			}
			
			if(!empty($state_v_occupier)) {
                $form['factory_information']['state_oprmntadr'] = array(
                    '#title' 		=> '(xxii) State',
                    '#type' 		=> 'select',
                    '#id' 			=> 'state_occupier_name',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' 		=> get_all_state($state_v_occupier),
                    '#value' 	 	=> !empty($state_v_occupier) ? $state_v_occupier : '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
				unset($form_state['input']['state_oprmntadr']);
                $form['factory_information']['state_oprmntadr'] = array(
                    '#title' 		=> '(xxii) State',
                    '#type' 		=> 'select',
                    '#id' 			=> 'state_occupier_name',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' => array(
						'' => t('Select State')
					),
                    '#value' 	 	=> '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_state_occupier = isset($form_state['values']['state_oprmntadr']) && !empty($form_state['values']['state_oprmntadr']) ? $form_state['values']['state_oprmntadr'] : '';	
			
			if(!empty($state_v_occupier)) {
                $form['factory_information']['district_oprmntadr'] = array(
                    '#title' => '(xxiii) District',
                    '#type' => 'select',
                    '#id' => 'district_occupier_name',
                    '#disabled' => TRUE,
                    '#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
                    '#options' => get_district_by_id($state_v_occupier),
                    '#value' 	=> !empty($district_v_occupier) ? $district_v_occupier : '',
                    '#required' => TRUE,
                    '#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
				unset($form_state['input']['district_oprmntadr']);
                $form['factory_information']['district_oprmntadr'] = array(
                    '#title' => '(xxiii) District',
                    '#type' => 'select',
                    '#id' => 'district_occupier_name',
                    '#disabled' => TRUE,
                    '#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
                    '#options' => array(
						'' => t('Select District')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
					 '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_district_occupier = isset($form_state['values']['district_oprmntadr']) && !empty($form_state['values']['district_oprmntadr']) ? $form_state['values']['district_oprmntadr'] : '';
			
			if(!empty($state_v_occupier) && !empty($district_v_occupier)) {
                $form['factory_information']['subdivision_oprmntadr'] = array(
                    '#title' => '(xxiv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => common_custom_user_subdivisionlist_list_new($district_v_occupier),
                    '#required' => TRUE,
                    '#default_value' 	=> '',
                    '#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
				unset($form_state['input']['subdivision_oprmntadr']);
                $form['factory_information']['subdivision_oprmntadr'] = array(
                    '#title' => '(xxiv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => array(
						'' => t('Select Sub-Division')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
					 '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_subdivision_occupier = isset($form_state['values']['subdivision_oprmntadr']) && !empty($form_state['values']['subdivision_oprmntadr']) ? $form_state['values']['subdivision_oprmntadr'] : '';
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier)) {
                $form['factory_information']['areatype_oprmntadr'] = array(
                    '#title' => '(xxv) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => common_custom_user_areatype_list_new($value_district_occupier, $value_subdivision_occupier),
                    '#required' => TRUE,
                    '#default_value' 	=> '',
                    '#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
				
			} else {
				unset($form_state['input']['areatype_oprmntadr']);
                $form['factory_information']['areatype_oprmntadr'] = array(
                    '#title' => '(xxv) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => array(
                        '0' => t('Select Area Type')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
					 '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_areatype_occupier = isset($form_state['values']['areatype_oprmntadr']) && !empty($form_state['values']['areatype_oprmntadr']) ? $form_state['values']['areatype_oprmntadr'] : '';
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier) && !empty($value_areatype_occupier)) {
				if ($value_areatype_occupier == 'B') {
					$areatype_name_occupier = 'Block';
				} elseif ($value_areatype_occupier == 'M') {
					$areatype_name_occupier = 'Municipality';
				} elseif ($value_areatype_occupier == 'C') {
					$areatype_name_occupier = 'Corporation';
				} elseif ($value_areatype_occupier == 'S') {
					$areatype_name_occupier = 'SEZ';
				} elseif ($value_areatype_occupier == 'N') {
					$areatype_name_occupier = 'Notified Area';
				}
				
				$form['factory_information']['block_oprmntadr'] = array(
					'#title' 		=> '(xxvi) '. $areatype_name_occupier,
					'#type'         => 'select',
					'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
					'#options' 		=> common_custom_user_block_list_new($value_subdivision_occupier, $value_areatype_occupier),
					'#required' 	=> TRUE,
					'#default_value' 	    => '',
					'#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
					'#suffix' 		=> '</label></div></div>',
					'#ajax' => array(
										'event' => 'change',
										'effect' => 'fade',
										'callback' => 'get_occupier_ajax_load',
										'progress' => array(
															 'type' => 'throbber',
															 'message' => t('loading')
										)
					)
				);	
				
			} else {
				unset($form_state['input']['block_oprmntadr']);	
                $form['factory_information']['block_oprmntadr'] = array(
                    '#title' 		=> '(xxvi) Block / Municipality / Corporation / Notified Area / SEZ',
                    '#type'         => 'select',
                    '#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
                    '#options' => array(
						'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
					),
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
					 '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_block_occupier = isset($form_state['values']['block_oprmntadr']) && !empty($form_state['values']['block_oprmntadr']) ? $form_state['values']['block_oprmntadr'] : '';
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier) && !empty($value_areatype_occupier) && !empty($value_block_occupier)) {
			
				if ($value_areatype_occupier == 'B') {
					$area_name_occupier = 'Gram Panchayat';
					$area_code_occupier = 'V';
				} elseif ($value_areatype_occupier == 'M') {
					$area_name_occupier = 'Ward';
					$area_code_occupier = 'W';
				} elseif ($value_areatype_occupier == 'C') {
					$area_name_occupier = 'Ward';
					$area_code_occupier = 'C';
				} elseif ($value_areatype_occupier == 'S') {
					$area_name_occupier = 'Sector';
					$area_code_occupier = 'S';
				} elseif ($value_areatype_occupier == 'N') {
					$area_name_occupier = 'Notified Area';
					$area_code_occupier = 'N';
				}
				
                $form['factory_information']['panchayat_oprmntadr'] = array(
                    '#title' => '(xxvii) '.$area_name_occupier,
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => common_custom_user_villward_list_new($value_block_occupier, $area_code_occupier),
                    '#default_value' 	    => '',
                    '#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
				
			} else {
				unset($form_state['input']['panchayat_oprmntadr']);
                $form['factory_information']['panchayat_oprmntadr'] = array(
                    '#title' => '(xxvii) Gram Panchayat / Ward / Sector',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => array(
						'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
					),
                    '#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
					 '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_occupier_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_panchayat_occupier = isset($form_state['values']['panchayat_oprmntadr']) && !empty($form_state['values']['panchayat_oprmntadr']) ? $form_state['values']['panchayat_oprmntadr'] : '';
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier) && !empty($value_areatype_occupier) && !empty($value_block_occupier) && !empty($value_panchayat_occupier)) {
				
                $form['factory_information']['policestation_oprmntadr'] = array(
                    '#title' => '(xxviii) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => common_custom_user_ps_list_new($value_district_occupier),
                    '#required' => TRUE,
                    '#default_value' 	    => '',
                    '#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );	
				
			} else {
				unset($form_state['input']['policestation_oprmntadr']);
                $form['factory_information']['policestation_oprmntadr'] = array(
                    '#title' => '(xxviii) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => array(
						'0' => t('Select Police Station')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			if(!empty($pincode_v_occupier)) {
                $form['factory_information']['postoffice_oprmntadr'] = array(
                    '#title' => '(xxix) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => common_custom_post_office_list_new($pincode_v_occupier),
                    '#default_value' 	    => '',
                    '#required' => TRUE,
                    '#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );	
				
			} else {
				unset($form_state['input']['postoffice_oprmntadr']);
                $form['factory_information']['postoffice_oprmntadr'] = array(
                    '#title' => '(xxix) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => array(
						'0' => t('Select Post Office')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			unset($form_state['input']['addrline_oprmntadr']);
			$form['factory_information']['addrline_oprmntadr'] = array(
				'#prefix' => '<div id="addrline_oprmntadr_occupier_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xxx) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#default_value' 	    => '',
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
				'#element_validate' => array('element_validate_streetaddress'), 
			);
				
	//occupier address section end
			
			$form['factory_information']['manager_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-7 col-xs-12"><h4><b>Manager\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			$form['factory_information']['manager_details_update'] = array(
				'#prefix' 				=> '<div id="manager_details_update_id"><div class="col-md-5 col-xs-12">'.$manager_details_update_link,
				'#suffix' 				=> '</div></div>',
			);
			
			unset($form_state['input']['manager_name']);	
			$form['factory_information']['manager_name'] = array(
				'#prefix' 				=> '<div id="manager_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name'),
				'#title' 			 	=> t('(xxxi) Manager Name'),
				'#default_value' 	 	        => '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);
			
	//manager address section
	
			unset($form_state['input']['pincode_manager']);
			$form['factory_information']['pincode_manager']       = array(
                '#prefix' 				=> '<div id="pincode_manager_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
                '#suffix' 				=> '</label></div></div>',
                '#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
                '#autocomplete_path' 	=> 'pinautocomplete',
                '#id' 				 	=> 'pincode_autocomplete_manager',
                '#maxlength' 		 	=> 6,
                '#title' 			 	=> t('(xxxii) Pincode'),
                '#default_value' 	 	=> '',
                '#required' 			=> TRUE,
                '#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
                '#ajax' 				=> array(
                                                    'effect' 	=> 'fade',
                                                    'callback' 	=> 'get_manager_ajax_load',
                                                    'progress' 	=> array(
                                                     'type' 	=> 'throbber',
                                                    'message' 	=> t('loading')
                    )
                )
            );
				
			$value_pincode_manager    = isset($form_state['values']['pincode_manager']) && !empty($form_state['values']['pincode_manager']) ? $form_state['values']['pincode_manager'] : '';
			
			if(!empty($value_pincode_manager)) {
				
				$query_pin_manager = db_select('fa_all_india_pin_code', 'p')
									->fields('p', array('districtname','statename',  'pincode','district_code', 'state_code', 'po_name'))
									->condition('p.pincode', trim($value_pincode_manager), '=');
				
			   	$result_pin_manager = $query_pin_manager->execute();
				if ($result_pin_manager->rowcount() > 0) {
					$final_pin_manager       = $result_pin_manager->fetchAssoc();
					$pincode_v_manager   = $value_pincode_manager;
					$state_v_manager     = $final_pin_manager['state_code'];
					$district_v_manager  = $final_pin_manager['district_code'];
					$post_office_manager = $final_pin_manager['po_name'];
				}
			}
			
			if(!empty($state_v_manager)) {
                $form['factory_information']['state_manager'] = array(
                    '#title' 		=> '(xxxiii) State',
                    '#type' 		=> 'select',
                    '#id' 			=> 'state_manager_name',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' 		=> get_all_state($state_v_manager),
                    '#value' 	 	=> !empty($state_v_manager) ? $state_v_manager : '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
				unset($form_state['input']['state_manager']);
                $form['factory_information']['state_manager'] = array(
                    '#title' 		=> '(xxxiii) State',
                    '#type' 		=> 'select',
                    '#id' 			=> 'state_manager_name',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' => array(
						'' => t('Select State')
					),
                    '#value' 	 	=> '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_state_manager = isset($form_state['values']['state_manager']) && !empty($form_state['values']['state_manager']) ? $form_state['values']['state_manager'] : '';
			
			if(!empty($state_v_manager)) {
                $form['factory_information']['district_manager'] = array(
                    '#title' => '(xxxiv) District',
                    '#type' => 'select',
                    '#id' => 'district_manager_name',
                    '#disabled' => TRUE,
                    '#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
                    '#options' => get_district_by_id($state_v_manager),
                    '#value' 	=> !empty($district_v_manager) ? $district_v_manager : '',
                    '#required' => TRUE,
                    '#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
				unset($form_state['input']['district_manager']);
                $form['factory_information']['district_manager'] = array(
                    '#title' => '(xxxiv) District',
                    '#type' => 'select',
                    '#id' => 'district_manager_name',
                    '#disabled' => TRUE,
                    '#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
                    '#options' => array(
						'' => t('Select District')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
					'#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_district_manager = isset($form_state['values']['district_manager']) && !empty($form_state['values']['district_manager']) ? $form_state['values']['district_manager'] : '';
			
			if(!empty($state_v_manager) && !empty($district_v_manager)) {
                $form['factory_information']['sub_division_manager'] = array(
                    '#title' => '(xxxv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => common_custom_user_subdivisionlist_list_new($district_v_manager),
                    '#required' => TRUE,
                    '#default_value' 	=> '',
                    '#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
				unset($form_state['input']['sub_division_manager']);
                $form['factory_information']['sub_division_manager'] = array(
                    '#title' => '(xxxv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => array(
						'' => t('Select Sub-Division')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
					'#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_subdivision_manager = isset($form_state['values']['sub_division_manager']) && !empty($form_state['values']['sub_division_manager']) ? $form_state['values']['sub_division_manager'] : '';
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager)) {
                $form['factory_information']['area_type_manager'] = array(
                    '#title' => '(xxxvi) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => common_custom_user_areatype_list_new($value_district_manager, $value_subdivision_manager),
                    '#required' => TRUE,
                    '#default_value' 	=> '',
                    '#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
				
			} else {
				unset($form_state['input']['area_type_manager']);
                $form['factory_information']['area_type_manager'] = array(
                    '#title' => '(xxxvi) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => array(
                        '0' => t('Select Area Type')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
					'#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_areatype_manager = isset($form_state['values']['area_type_manager']) && !empty($form_state['values']['area_type_manager']) ? $form_state['values']['area_type_manager'] : '';
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager) && !empty($value_areatype_manager)) {
				if ($value_areatype_manager == 'B') {
					$areatype_name_manager = 'Block';
				} elseif ($value_areatype_manager == 'M') {
					$areatype_name_manager = 'Municipality';
				} elseif ($value_areatype_manager == 'C') {
					$areatype_name_manager = 'Corporation';
				} elseif ($value_areatype_manager == 'S') {
					$areatype_name_manager = 'SEZ';
				} elseif ($value_areatype_manager == 'N') {
					$areatype_name_manager = 'Notified Area';
				}
				
				$form['factory_information']['block_mun_cor_sez_not_manager'] = array(
					'#title' 		=> '(xxxvii) '. $areatype_name_manager,
					'#type'         => 'select',
					'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
					'#options' 		=> common_custom_user_block_list_new($value_subdivision_manager, $value_areatype_manager),
					'#required' 	=> TRUE,
					'#default_value' 	    => '',
					'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
					'#suffix' 		=> '</label></div></div>',
					'#ajax' => array(
										'event' => 'change',
										'effect' => 'fade',
										'callback' => 'get_manager_ajax_load',
										'progress' => array(
															 'type' => 'throbber',
															 'message' => t('loading')
										)
					)
				);	
				
			} else {
				unset($form_state['input']['block_mun_cor_sez_not_manager']);	
                $form['factory_information']['block_mun_cor_sez_not_manager'] = array(
                    '#title' 		=> '(xxxvii) Block / Municipality / Corporation / Notified Area / SEZ',
                    '#type'         => 'select',
                    '#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
                    '#options' => array(
						'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
					),
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
					'#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_block_manager = isset($form_state['values']['block_mun_cor_sez_not_manager']) && !empty($form_state['values']['block_mun_cor_sez_not_manager']) ? $form_state['values']['block_mun_cor_sez_not_manager'] : '';
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager) && !empty($value_areatype_manager) && !empty($value_block_manager)) {
			
				if ($value_areatype_manager == 'B') {
					$area_name_manager = 'Gram Panchayat';
					$area_code_manager = 'V';
				} elseif ($value_areatype_manager == 'M') {
					$area_name_manager = 'Ward';
					$area_code_manager = 'W';
				} elseif ($value_areatype_manager == 'C') {
					$area_name_manager = 'Ward';
					$area_code_manager = 'C';
				} elseif ($value_areatype_manager == 'S') {
					$area_name_manager = 'Sector';
					$area_code_manager = 'S';
				} elseif ($value_areatype_manager == 'N') {
					$area_name_manager = 'Notified Area';
					$area_code_manager = 'N';
				}
				
                $form['factory_information']['grm_ward_sector_not_manager'] = array(
                    '#title' => '(xxxviii) '.$area_name_manager,
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => common_custom_user_villward_list_new($value_block_manager, $area_code_manager),
                    '#default_value' 	    => '',
                    '#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
				
			} else {
				unset($form_state['input']['grm_ward_sector_not_manager']);
                $form['factory_information']['grm_ward_sector_not_manager'] = array(
                    '#title' => '(xxxviii) Gram Panchayat / Ward / Sector',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => array(
						'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
					),
                    '#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
					'#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_manager_ajax_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );
			}
			
			$value_panchayat_manager = isset($form_state['values']['grm_ward_sector_not_manager']) && !empty($form_state['values']['grm_ward_sector_not_manager']) ? $form_state['values']['grm_ward_sector_not_manager'] : '';
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager) && !empty($value_areatype_manager) && !empty($value_block_manager) && !empty($value_panchayat_manager)) {
				
                $form['factory_information']['police_station_manager'] = array(
                    '#title' => '(xxxix) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => common_custom_user_ps_list_new($value_district_manager),
                    '#required' => TRUE,
                    '#default_value' 	    => '',
                    '#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );	
				
			} else {
				unset($form_state['input']['police_station_manager']);
                $form['factory_information']['police_station_manager'] = array(
                    '#title' => '(xxxix) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => array(
						'0' => t('Select Police Station')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
			}
			
			if(!empty($pincode_v_manager)) {
                $form['factory_information']['post_office_manager'] = array(
                    '#title' => '(xl) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => common_custom_post_office_list_new($pincode_v_manager),
                    '#default_value' 	    => '',
                    '#required' => TRUE,
                    '#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );	
				
			} else {
				unset($form_state['input']['post_office_manager']);
                $form['factory_information']['post_office_manager'] = array(
                    '#title' => '(xl) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => array(
						'0' => t('Select Post Office')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
			}
			
			unset($form_state['input']['adress_line1_manager']);
			$form['factory_information']['adress_line1_manager'] = array(
				'#prefix' => '<div id="adress_line1_manager_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div></div>',
				'#title' => '(xli) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#default_value' 	    => '',
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
				'#element_validate' => array('element_validate_streetaddress'), 
			);
			
	//manager address section end
			
		}*/

		
//this code is implemented at line 1959 if Other option is included in the Licence No. or Factory Name Dropdown. Otherwise it will be always comment off.
	/*else if($factory_id != NULL && $factory_id == 0) {
			
			$annual_return = array(
				'factory_name'         			=> $val['factory_name'],
				'cafa_id'              			=> $factory_id,
				'reference_number'     			=> $val['reference_number'],
				'industry_nature'        		=> $val['industry_nature'],
				'registration_number'  			=> $val['registration_number'],
				'registration_date'    			=> trim(implode('-', array_reverse(explode('-', $val['registration_date'])))),
				'licence_number'       			=> $val['licence_number'],
				'licence_date'         			=> trim(implode('-', array_reverse(explode('-', $val['licence_date'])))),
				'classification_no'    			=> $val['classification_no'],
				'pincode'	  		   			=> $val['pincode'],
				'state'         	   			=> $val['state'],
				'district'             			=> $val['district'],
				'subdivision'     	   			=> $val['subdivision'],
				'areatype'        	   			=> $val['areatype'],
				'block' 			   			=> $val['block'],
				'panchayat'    		   			=> $val['panchayat'],
				'policestation'        			=> $val['policestation'],
				'postoffice'          			=> $val['postoffice'],
				'factory_zone'         			=> $val['factory_zone'],
				'nearest_landmark'	   			=> $val['nearest_landmark'],
				'addrline'    		   			=> $val['addrline'],
				'uid' 				   			=> $uid,
				'created_date'		   			=> date('Y-m-d'),
				'full_application_status'   	=> 'In',
				'name_occupier'   				=> $val['occupier_name'],
				'name_manager'   				=> $val['manager_name'],
				'payment_wages_flag'   			=> $val['payment_wages_flag'],
				'factories_act_flag'   			=> $val['factories_act_flag'],
				'maternity_benefit_flag' 		=> $val['maternity_benefit_flag'],
				'annual_return_year' 			=> $val['annual_return_year'],
				'service_id' 					=> $service_details->id,
				'pincodeoprmntadr'				=> $val['pincodeoprmntadr'],
				'state_oprmntadr'				=> $val['state_oprmntadr'],
				'district_oprmntadr'			=> $val['district_oprmntadr'],
				'subdivision_oprmntadr'			=> $val['subdivision_oprmntadr'],
				'areatype_oprmntadr'			=> $val['areatype_oprmntadr'],
				'block_oprmntadr'				=> $val['block_oprmntadr'],
				'panchayat_oprmntadr'			=> $val['panchayat_oprmntadr'],
				'policestation_oprmntadr'		=> $val['policestation_oprmntadr'],
				'postoffice_oprmntadr'			=> $val['postoffice_oprmntadr'],
				'addrline_oprmntadr'			=> $val['addrline_oprmntadr'],
				'pincode_manager'				=> $val['pincode_manager'],
				'state_manager'					=> $val['state_manager'],
				'district_manager'				=> $val['district_manager'],
				'sub_division_manager'			=> $val['sub_division_manager'],
				'area_type_manager'				=> $val['area_type_manager'],
				'block_mun_cor_sez_not_manager'	=> $val['block_mun_cor_sez_not_manager'],
				'grm_ward_sector_not_manager'	=> $val['grm_ward_sector_not_manager'],
				'police_station_manager'		=> $val['police_station_manager'],
				'post_office_manager'			=> $val['post_office_manager'],
				'adress_line1_manager'			=> $val['adress_line1_manager'],
				'factory_typeid'				=> $val['factory_typeid'],
			);
			
			$annual_return_ID = db_insert('fa_annual_return')->fields($annual_return)->execute();
			
		}*/