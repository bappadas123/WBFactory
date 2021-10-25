<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
drupal_add_js('https://www.jqueryscript.net/demo/jQuery-Plugin-For-Auto-Tab-Form-Fields-autotab/js/jquery.autotab.js', 'external');
	
function caf_form_occupier_extn($form, &$form_state, $serviceid, $factory_typeid, $applicationid,$referenceno)
{
    global $base_root, $base_path, $user;
    
    $service_id      			= encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id 			= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id  			= encryption_decryption_fun('decrypt', $applicationid);
    $reference_no 		        = encryption_decryption_fun('decrypt', $referenceno);

	if(empty($application_id) || $application_id==0 || $application_id == ''){
		  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Owner Information tab.</h5>'),'alert alert-danger alert-dismissible');
		  drupal_goto('applicant/caf_extn/caf-form-owner-extension/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno) ;
	}

	$get_user_data     			= get_details_applicant($user->uid);//echo "<pre>"; print_r($get_user_data);
	$get_fa_cafa 		        = get_fa_cafa($application_id);
    //$reference_no 		        = $get_fa_cafa['reference_number'];
	$plan_approve_status        = $get_fa_cafa['plan_approve_status'];

  $ownership_type = $type_occupier = $country_oprmntadr =  $aadhaar_oprmntadr = $passport_oprmntadr =  $name_occupier =  $occupier_name_middle = $occupier_name_last = $occupier_mobile = $occupier_email_id = $occupier_age =  $father_husband_name_occupier =  $occupier_fax_no =  $occupier_telephone = $occupier_pincodeoprmntadr = $occupier_state_oprmntadr = $occupier_district_oprmntadr = $occupier_subdivision_oprmntadr = $occupier_areatype_oprmntadr = $occupier_block_oprmntadr = $occupier_panchayat_oprmntadr = $occupier_policestation_oprmntadr = $occupier_postoffice_oprmntadr = $occupier_addrline_oprmntadr = $occupier_pincodeoprsntadr = $occupier_state_oprsntadr = $occupier_district_oprsntadr = $occupier_subdivision_oprsntadr = $occupier_areatype_oprsntadr = $occupier_block_oprsntadr = $occupier_panchayat_oprsntadr = $occupier_policestation_oprsntadr = $occupier_postoffice_oprsntadr = $occupier_addrline_oprsntadr =  $occupier_present_address_same = $passport_date_of_issue_oprmntadr = $passport_date_of_expiry_oprmntadr = $street_name_oprmntadr = $house_no_oprmntadr = $police_station_oprmntadr = $country_oprsntadr = $aadhaar_oprsntadr = $passport_oprsntadr = $passport_date_of_issue_oprsntadr = $passport_date_of_expiry_oprsntadr = $occupier_street_name_oprsntadr = $occupier_house_no_oprsntadr = $occupier_police_station_oprsntadr = ''; 
	
    $form            			= array();
	$form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $factory_typeid
    );
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );
    $form['reference_no_hidden']       = array(
        '#type'          => 'hidden',
        '#default_value' => $referenceno
    );
	$form['plan_approve_status_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $plan_approve_status)
    );

	    $get_fa_occupier            = get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_no);
		
		
		if (!empty($get_fa_occupier[0]->type_occupier)) { 

        //Details of Occupier//
        $ownership_type						    = $get_fa_occupier[0]->ownership_type;
    	$type_occupier 						    = $get_fa_occupier[0]->type_occupier;
        $occupier_name        				    = $get_fa_occupier[0]->name_occupier;
		$occupier_name_middle				    = $get_fa_occupier[0]->occupier_name_middle;
		$occupier_name_last					    = $get_fa_occupier[0]->occupier_name_last;
        $occupier_mobile      				    = $get_fa_occupier[0]->occupier_mobile;
        $occupier_email_id    				    = $get_fa_occupier[0]->occupier_email_id;
        $occupier_age           			    = $get_fa_occupier[0]->age_occupier;
        $father_husband_name_occupier  	 	    = $get_fa_occupier[0]->father_husband_name_occupier;
        $occupier_fax_no        			    = $get_fa_occupier[0]->occupier_fax_no;
		$occupier_telephone     			    = $get_fa_occupier[0]->occupier_telephone;
        
        // Occupier Permanent Address//
		$country_oprmntadr 			  	  		= $get_fa_occupier[0]->country_oprmntadr;
        $passport_oprmntadr    			  		= $get_fa_occupier[0]->passport_oprmntadr;
		$occupier_pincodeoprmntadr        		= $get_fa_occupier[0]->pincodeoprmntadr;
        $occupier_state_oprmntadr         		= $get_fa_occupier[0]->state_oprmntadr;
        $occupier_district_oprmntadr      		= $get_fa_occupier[0]->district_oprmntadr;
        $occupier_subdivision_oprmntadr   		= $get_fa_occupier[0]->subdivision_oprmntadr;
        $occupier_areatype_oprmntadr      		= $get_fa_occupier[0]->areatype_oprmntadr;
        $occupier_block_oprmntadr         		= $get_fa_occupier[0]->block_oprmntadr;
        $occupier_panchayat_oprmntadr     		= $get_fa_occupier[0]->panchayat_oprmntadr;
        $occupier_policestation_oprmntadr 		= $get_fa_occupier[0]->policestation_oprmntadr;
        $occupier_postoffice_oprmntadr    		= $get_fa_occupier[0]->postoffice_oprmntadr;
        $aadhaar_oprmntadr     			  		= explode('-',$get_fa_occupier[0]->aadhaar_oprmntadr);
		$user_aadhar_1_oprmntadr 		  		= $aadhaar_oprmntadr[0];
		$user_aadhar_2_oprmntadr 		  		= $aadhaar_oprmntadr[1];
		$user_aadhar_3_oprmntadr 		  		= $aadhaar_oprmntadr[2];
		$occupier_addrline_oprmntadr      		= $get_fa_occupier[0]->addrline_oprmntadr;
		$passport_date_of_issue_oprmntadr 		= $get_fa_occupier[0]->passport_date_of_issue_oprmntadr;
		$passport_date_of_expiry_oprmntadr		= $get_fa_occupier[0]->passport_date_of_expiry_oprmntadr;
		$street_name_oprmntadr		      		= $get_fa_occupier[0]->street_name_oprmntadr;
		$house_no_oprmntadr		          		= $get_fa_occupier[0]->house_no_oprmntadr;
		$police_station_oprmntadr	      		= $get_fa_occupier[0]->police_station_oprmntadr;        
        
		//Occupier Present Address//
		
		$occupier_present_address_same          = $get_fa_occupier[0]->occupier_present_address_same;
		$country_oprsntadr   					= $get_fa_occupier[0]->country_oprsntadr;
        $passport_oprsntadr        				= $get_fa_occupier[0]->passport_oprsntadr;
		$occupier_pincodeoprsntadr          	= $get_fa_occupier[0]->pincodeoprsntadr;
        $occupier_state_oprsntadr           	= $get_fa_occupier[0]->state_oprsntadr;
        $occupier_district_oprsntadr        	= $get_fa_occupier[0]->district_oprsntadr;
        $occupier_subdivision_oprsntadr     	= $get_fa_occupier[0]->subdivision_oprsntadr;
        $occupier_areatype_oprsntadr        	= $get_fa_occupier[0]->areatype_oprsntadr;
        $occupier_block_oprsntadr           	= $get_fa_occupier[0]->block_oprsntadr;
        $occupier_panchayat_oprsntadr       	= $get_fa_occupier[0]->panchayat_oprsntadr;
        $occupier_policestation_oprsntadr   	= $get_fa_occupier[0]->policestation_oprsntadr;
        $occupier_postoffice_oprsntadr      	= $get_fa_occupier[0]->postoffice_oprsntadr;
        $aadhaar_oprsntadr       				= explode('-',$get_fa_occupier[0]->aadhaar_oprsntadr);
		$user_aadhar_1_oprsntadr 		   	 	= $aadhaar_oprsntadr[0];
		$user_aadhar_2_oprsntadr 		    	= $aadhaar_oprsntadr[1];
		$user_aadhar_3_oprsntadr		    	= $aadhaar_oprsntadr[2];
		$occupier_addrline_oprsntadr        	= $get_fa_occupier[0]->addrline_oprsntadr;
		$passport_date_of_issue_oprsntadr 		= $get_fa_occupier[0]->passport_date_of_issue_oprsntadr;
		$passport_date_of_expiry_oprsntadr		= $get_fa_occupier[0]->passport_date_of_expiry_oprsntadr;
		$street_name_oprsntadr					= $get_fa_occupier[0]->street_name_oprsntadr;
		$house_no_oprsntadr						= $get_fa_occupier[0]->house_no_oprsntadr;
		$police_station_oprsntadr				= $get_fa_occupier[0]->police_station_oprsntadr; 
		
    } else { 
		
		// DATA FROM USER DETAILS TABLE 
		if($get_user_data['user_type'] == 'occupier')
		{ 
			$occupier_name						= $get_user_data['firstname'];
			$occupier_name_middle               = $get_user_data['middlename'];
			$occupier_name_last                 = $get_user_data['lastname'];
			$ownership_type         	        = $get_user_data['ownership_type'];
			$type_occupier                      = $get_user_data['type_occupier'];
			$father_husband_name_occupier       = $get_user_data['gurdian_name'];
			$occupier_email_id            		= $get_user_data['email'];
			$occupier_mobile              		= $get_user_data['mobile'];
			$from = new DateTime($get_user_data['dob']);
			$to   = new DateTime('today');
			$occupier_age						= $from->diff($to)->y;

			$occupier_user_aadhar       		= explode('-',$get_user_data['user_aadhar']);
			$user_aadhar_1_oprmntadr 			= $user_aadhar_1_oprsntadr = $occupier_user_aadhar[0];
			$user_aadhar_2_oprmntadr 			= $user_aadhar_2_oprsntadr	= $occupier_user_aadhar[1];
			$user_aadhar_3_oprmntadr 			= $user_aadhar_3_oprsntadr = $occupier_user_aadhar[2];

			$country_oprmntadr            	    = $country_oprsntadr 	            = $get_user_data['country'];
			$occupier_pincodeoprmntadr       	= $occupier_pincodeoprsntadr     	= $get_user_data['pincode'];
			$occupier_state_oprmntadr        	= $occupier_state_oprsntadr    		= $get_user_data['state'];
			$occupier_district_oprmntadr     	= $occupier_district_oprsntadr    	= $get_user_data['district'];
			$occupier_subdivision_oprmntadr  	= $occupier_subdivision_oprsntadr  	= $get_user_data['subdivision'];
			$occupier_areatype_oprmntadr     	= $occupier_areatype_oprsntadr     	= $get_user_data['areatype'];
			$occupier_block_oprmntadr        	= $occupier_block_oprsntadr        	= $get_user_data['block'];
			$occupier_panchayat_oprmntadr    	= $occupier_panchayat_oprsntadr    	= $get_user_data['panchayat'];
			$occupier_policestation_oprmntadr 	= $occupier_policestation_oprsntadr = $get_user_data['policestation'];
			$occupier_postoffice_oprmntadr   	= $occupier_postoffice_oprsntadr   	= $get_user_data['postoffice'];
			
			$passport_oprmntadr     	   		= $passport_oprsntadr 		         = $get_user_data['user_passport'];
			$passport_date_of_issue_oprmntadr   = $passport_date_of_issue_oprsntadr  = $get_user_data['passport_date_of_issue'];
			$passport_date_of_expiry_oprmntadr  = $passport_date_of_expiry_oprsntadr = $get_user_data['passport_date_of_expiry'];
			$street_name_oprmntadr           	= $street_name_oprsntadr          	 = $get_user_data['street_name'];
			$house_no_oprmntadr	             	= $house_no_oprsntadr             	 = $get_user_data['house_no'];
			$police_station_oprmntadr  		 	= $police_station_oprsntadr       	 = $get_user_data['police_station'];
			$occupier_addrline_oprmntadr     	= $occupier_addrline_oprsntadr       = $get_user_data['addrline'];
		
		} elseif(($get_user_data['user_type'] == 'owner') && ($get_user_data['is_occupier'] == 'Y')) { 
			
			$occupier_name						= $get_user_data['occupier_first_name'];
			$occupier_name_middle               = $get_user_data['occupier_middle_name'];
			$occupier_name_last                 = $get_user_data['occupier_last_name'];
		    $ownership_type         	        = $get_user_data['ownership_type'];
			$type_occupier                      = $get_user_data['type_occupier'];
			$occupier_type_reg					= $get_user_data['occupier_type'];
			$father_husband_name_occupier       = $get_user_data['gurdian_name'];
			$occupier_email_id            		= $get_user_data['email'];
			$occupier_mobile              		= $get_user_data['mobile'];
			$from 								= new DateTime($get_user_data['dob']);
			$to   								= new DateTime('today');
			$occupier_age					    = $from->diff($to)->y;

			$occupier_user_aadhar     			= explode('-',$get_user_data['user_aadhar']);
			$user_aadhar_1_oprmntadr  			= $user_aadhar_1_oprsntadr  = $occupier_user_aadhar[0];
			$user_aadhar_2_oprmntadr  			= $user_aadhar_2_oprsntadr  = $occupier_user_aadhar[1];
			$user_aadhar_3_oprmntadr  			= $user_aadhar_3_oprsntadr  = $occupier_user_aadhar[2];

			$country_oprmntadr            	    = $country_oprsntadr 	            =  $get_user_data['country'];
			$occupier_pincodeoprmntadr       	= $occupier_pincodeoprsntadr     	=  $get_user_data['pincode'];
			$occupier_state_oprmntadr        	= $occupier_state_oprsntadr    		=  $get_user_data['state'];
			$occupier_district_oprmntadr     	= $occupier_district_oprsntadr    	=  $get_user_data['district'];
			$occupier_subdivision_oprmntadr  	= $occupier_subdivision_oprsntadr  	=  $get_user_data['subdivision'];
			$occupier_areatype_oprmntadr     	= $occupier_areatype_oprsntadr     	=  $get_user_data['areatype'];
			$occupier_block_oprmntadr        	= $occupier_block_oprsntadr        	=  $get_user_data['block'];
			$occupier_panchayat_oprmntadr    	= $occupier_panchayat_oprsntadr    	=  $get_user_data['panchayat'];
			$occupier_policestation_oprmntadr 	= $occupier_policestation_oprsntadr =  $get_user_data['policestation'];
			$occupier_postoffice_oprmntadr   	= $occupier_postoffice_oprsntadr   	=  $get_user_data['postoffice'];
			
			$passport_oprmntadr     	   		= $passport_oprsntadr 				 = $get_user_data['user_passport'];
			$passport_date_of_issue_oprmntadr   = $passport_date_of_issue_oprsntadr  = $get_user_data['passport_date_of_issue'];
			$passport_date_of_expiry_oprmntadr  = $passport_date_of_expiry_oprsntadr = $get_user_data['passport_date_of_expiry'];
			$street_name_oprmntadr           	= $street_name_oprsntadr          	 = $get_user_data['street_name'];
			$house_no_oprmntadr	             	= $house_no_oprsntadr             	 = $get_user_data['house_no'];
			$police_station_oprmntadr  		 	= $police_station_oprsntadr       	 = $get_user_data['police_station'];
			$occupier_addrline_oprmntadr     	= $occupier_addrline_oprsntadr       = $get_user_data['addrline'];

		} elseif(($get_user_data['user_type'] == 'owner') && ($get_user_data['is_occupier'] == 'N')) { 
			
			$occupier_name						= $get_user_data['occupier_first_name'];
			$occupier_name_middle               = $get_user_data['occupier_middle_name'];
			$occupier_name_last                 = $get_user_data['occupier_last_name'];
			$occupier_email_id            		= $get_user_data['occupier_email'];
			$occupier_mobile              		= $get_user_data['occupier_mobile'];

		} elseif($get_user_data['user_type'] == 'consultant') { 
			
			$occupier_name					    = $get_user_data['occupier_first_name'];
			$occupier_name_middle           	= $get_user_data['occupier_middle_name'];
			$occupier_name_last             	= $get_user_data['occupier_last_name'];
			$occupier_email_id            		= $get_user_data['occupier_email'];
			$occupier_mobile              		= $get_user_data['occupier_mobile'];
		}
	}

    /********** Factory checking data **********/
	
	if($plan_approve_status == 'ABk') {
	
	$reference_number = $get_fa_cafa['reference_number'];
	$checked = get_verified_field($application_id, $reference_number, $plan_approve_status);
	
	$verify_details      = ($checked['verify_details'])? $checked['verify_details'] : ''; 
	
	$remark_field = explode(',', $checked['verify_details']);
			foreach ($remark_field as $fieldname){

				if($fieldname == 'name_occupier'){ $occupier_name_ck = "disabled";}
				if($fieldname == 'age_occupier'){ $occupier_age_ck = "disabled";}
				if($fieldname == 'father_husband_name_occupier'){ $father_husband_name_occupier_ck = "disabled";}
				if($fieldname == 'occupier_telephone'){ $occupier_telephone_ck = "disabled";}
				if($fieldname == 'occupier_fax_no'){ $occupier_fax_no_ck = "disabled";}
				if($fieldname == 'occupier_mobile'){ $occupier_mobile_ck = "disabled";}
				if($fieldname == 'occupier_email_id'){ $occupier_email_id_ck = "disabled";}
				if($fieldname == 'occupier_type'){ $type_occupier_ck = "disabled";}
				if($fieldname == 'country_oprmntadr'){ $country_oprmntadr_ck = "disabled";}
				if($fieldname == 'occupier_present_address'){ $country_oprsntadr_ck = "disabled"; $occupier_present_address_check_ck = "readonly";}
				//if($fieldname == 'occupier_present_address'){ $occupier_present_address_ck = "disabled"; }
			}


		if(in_array("name_occupier", $remark_field)) { $occupier_name_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_name_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("age_occupier", $remark_field)) { $occupier_age_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_age_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("father_husband_name_occupier", $remark_field)) { $father_husband_name_occupier_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $father_husband_name_occupier_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_telephone", $remark_field)) { $occupier_telephone_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_telephone_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_fax_no", $remark_field)) { $occupier_fax_no_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_fax_no_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_mobile", $remark_field)) { $occupier_mobile_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_mobile_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_email_id", $remark_field)) { $occupier_email_id_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_email_id_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_type", $remark_field)) { $type_occupier_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $type_occupier_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("country_oprmntadr", $remark_field)) { $country_oprmntadr_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $country_oprmntadr_check_data = '<i class="fa fa-close text-red verified"></i>'; }
		
		if(in_array("occupier_present_address", $remark_field)) { $country_oprsntadr_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $country_oprsntadr_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		/*if(in_array("occupier_present_address", $remark_field)) { $occupier_present_address_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_present_address_check_data = '<i class="fa fa-close text-red verified"></i>'; }*/

	 }	
	 
	/********** Factory Information - Start **********/
    
	$form['header']            = array(
        '#markup' => t('<div class="content"><h3>General Information</h3>')
    );
	
	/********** Details of Occupier - Start **********/
	
	$form['factory_part_d']    = array(
        '#type' => 'fieldset',
        '#title' => t('h. Details of Occupier'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
	$ownershiptype  = array(
		"0" => "Select",
		"pv" 			=> "Private Ltd Company",
		"ltd" 			=> "Public Ltd Company",
		"par_firm" 		=> "Partnership Firm",
		"pro_firm" 		=> "Proprietorship Firm",
		"llp" 			=> "Limited Liability Partnership",
		"cooperative" 	=> "Co-operative",
		"registered" 	=> "Registered Society under Society Register",
		"govt" 			=> "Government(State/Central)",
		"psu" 			=> "Public Sector Undertaking",
		"localbody" 	=> "Local Body",
		"others" 		=> "Others",
    );
	
	if(!empty($ownership_type)){
	 if($ownership_type == 'pv' || $ownership_type == 'ltd'){
		 $ownership_type_occupier 	= 'Director';
	 }elseif($ownership_type == 'par_firm'  || $ownership_type=='llp'){
		 $ownership_type_occupier 	= 'Partner';
	 }elseif($ownership_type == 'pro_firm'){
		 $ownership_type_occupier 	= 'Proprietor';
	 }elseif($ownership_type=='cooperative'|| $ownership_type=='registered'){
		 $ownership_type_occupier	= 'Nominated Occupier';
	 }elseif($ownership_type == 'govt' || $ownership_type == 'psu' || $ownership_type == 'others' || $ownership_type=='localbody' ){
		 $ownership_type_occupier	= 'Nominated ';
	 }
	}
	
    $form['factory_part_d']['ownership_type'] = array(
        '#prefix' => '<div class="row"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        '#suffix' => '</label></div>',
        '#title' => t($type_occupier_check_data.'(i) Type of Ownership'),
		'#attributes' => array('class' => array( ''),$type_occupier_ck => $type_occupier_ck ),
        '#options' => $ownershiptype,
        '#type' => 'select',
        '#default_value'        => !empty($ownership_type) ? $ownership_type : $get_fa_cafa['factory_owershiptype'],
        '#required' => TRUE,
		'#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_type_occupier',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        )
    );
	
	$form['factory_part_d']['type_occupier'] = array(
		'#prefix' => '<div id="type_occupier_id">',
		'#suffix' => '</div>',
	);

	$value_ownership_type   = isset($form_state['values']['ownership_type']) ? $form_state['values']['ownership_type'] : $ownership_type;

	if($value_ownership_type == 'par_firm' || $value_ownership_type == 'llp')
	{
		$form['factory_part_d']['type_occupier'] = array(
			'#prefix' => '<div id="type_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($type_occupier_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Partner',
			'#attributes' 		=> array(
			   'readonly' => 'readonly',$type_occupier_ck => $type_occupier_ck 
			),
		);

	} elseif($value_ownership_type == 'pro_firm')
	{
		$form['factory_part_d']['type_occupier'] = array(
			'#prefix' => '<div id="type_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($type_occupier_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Proprietor',
			'#attributes' 		=> array(
			   'readonly' => 'readonly',$type_occupier_ck => $type_occupier_ck 
			),
		);

	} elseif($value_ownership_type == 'govt' || $value_ownership_type == 'psu' || $value_ownership_type == 'others' || $value_ownership_type == 'localbody')
	{
		$form['factory_part_d']['type_occupier'] = array(
			'#prefix' => '<div id="type_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($type_occupier_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Nominated',
			'#attributes' 		=> array(
			   'readonly' => 'readonly',$type_occupier_ck => $type_occupier_ck 
			),
		);

	} elseif($value_ownership_type == 'ltd' || $value_ownership_type == 'pv')
	{
		$form['factory_part_d']['type_occupier'] = array(
			'#prefix' => '<div id="type_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($type_occupier_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Director',
			'#attributes' 		=> array(
			   'readonly' => 'readonly',$type_occupier_ck => $type_occupier_ck 
			),
		);
	} elseif($value_ownership_type == 'cooperative' || $value_ownership_type == 'registered')
	{
		$form['factory_part_d']['type_occupier'] = array(
			'#prefix' => '<div id="type_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($type_occupier_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Nominated Occupier',
			'#attributes' 		=> array(
			   'readonly' => 'readonly',$type_occupier_ck => $type_occupier_ck 
			),
		);

	}
		
	    $form['factory_part_d']['occupier_name']           = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_name_check_data.'(ii)a. First Name'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_name) ? $occupier_name :'',
			'#attributes' => array('class' => array('charField'),$occupier_name_ck => $occupier_name_ck, 'readonly' => 'readonly', 'style'=>'background-color: #EBEBEB;' ),
            '#required' => TRUE,
        );
		$form['factory_part_d']['occupier_name_middle']           = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_name_check_data.'(ii)b. Middle Name'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_name_middle) ? $occupier_name_middle :'',
			'#attributes' => array('class' => array('charField'),$occupier_name_ck => $occupier_name_ck, 'readonly' => 'readonly', 'style'=>'background-color: #EBEBEB;' ),
            //'#required' => TRUE,
        );
		$form['factory_part_d']['occupier_name_last']           = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_name_check_data.'(ii)c. Last Name'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_name_last) ? $occupier_name_last :'',
			'#attributes' => array('class' => array('charField'),$occupier_name_ck => $occupier_name_ck, 'readonly' => 'readonly', 'style'=>'background-color: #EBEBEB;' ),
            '#required' => TRUE,
        );
		$form['factory_part_d']['occupier_age']    = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_age_check_data.'(iii) Age'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_age) ? $occupier_age :'',
			'#attributes' => array('class' => array('NoField'),$occupier_age_ck => $occupier_age_ck ),
			'#maxlength' => 2,
			'#required' => TRUE,
        );
        $form['factory_part_d']['father_husband_name_occupier']  = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($father_husband_name_occupier_check_data.'(iv) Father\'s / Husband\'s name'),
            '#type' => 'textfield',
            '#default_value' => !empty($father_husband_name_occupier) ? $father_husband_name_occupier :'',
			'#attributes' => array('class' => array('charField'),$father_husband_name_occupier_ck => $father_husband_name_occupier_ck ),
			'#required' => TRUE,
        );
        $form['factory_part_d']['occupier_telephone']  = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_telephone_check_data.'(v) Telephone Number'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_telephone) ? $occupier_telephone :'',
			'#attributes' => array('class' => array('NoField'),$occupier_telephone_ck => $occupier_telephone_ck ),
			'#maxlength' => 11,
			'#required' => TRUE,
        );
        $form['factory_part_d']['occupier_mobile']         = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_mobile_check_data.'(vi) Mobile Number'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_mobile) ? $occupier_mobile :'',
			'#attributes' => array('class' => array('NoField'),$occupier_mobile_ck => $occupier_mobile_ck, 'readonly' => 'readonly', 'style'=>'background-color: #EBEBEB;' ),
            '#required' => TRUE,
			'#maxlength' => 10,
        );
        $form['factory_part_d']['occupier_email_id']       = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_email_id_check_data.'(vii) Email id'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_email_id) ? $occupier_email_id :'',
			'#attributes' => array('class' => array('emailField'),$occupier_email_id_ck => $occupier_email_id_ck, 'readonly' => 'readonly', 'style'=>'background-color: #EBEBEB;' ),
            '#required' => TRUE,
        );
		$form['factory_part_d']['occupier_fax_no']    = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_fax_no_check_data.'(viii) Fax No.'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_fax_no) ? $occupier_fax_no :'',
			'#attributes' => array('class' => array('NoField'),$occupier_fax_no_ck => $occupier_fax_no_ck )
        );	
		$form['factory_part_d']['firstRowEnd'] = array(
			'#prefix' => '',
			'#suffix' => '</div>'
		);	
	
	/********** Details of Occupier - End **********/
	
	/********** Occupier Permanent Address - Start **********/
	
	$form['factory_part_c'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('I i). Occupier Permanent Address'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);		
	
		$form['factory_part_c']['country_oprmntadr'] 	= array(
			  '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="select label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#maxlength' 			=> 6, 
			  '#options' 			=> get_country_with_ph(),
			  '#default_value'      => !empty($country_oprmntadr) ? $country_oprmntadr :'',
			  '#title' 				=> t($country_oprmntadr_check_data.'(i) Nationality'),
			  '#attributes' 		=> array('class' => array( ''),$country_oprmntadr_ck => $country_oprmntadr_ck ),
			  '#required' 			=> TRUE,
			  '#type' 				=> 'select',
			  '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'get_ajax_load_oprmntadr',
											'progress'		=>	array(
												'type'		=>'throbber',
												'message'	=>t('loading'),
											),
									)
			);
//echo $country_oprmntadr;
//echo $form_state['values']['country_oprmntadr'];

	if((isset($form_state['values']['country_oprmntadr']) && trim($form_state['values']['country_oprmntadr']) != '99') || (!isset($form_state['values']['country_oprmntadr']) && !empty($country_oprmntadr) && ($country_oprmntadr != '99')))
	{ 
			$form['factory_part_c']['pincodeoprmntadr'] = array(
				'#prefix' 	=> '<div id="pincodeoprmntadr_id">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['state_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_edit_emp_state_replace">',
				'#suffix' 	=> '</div>'
			);
		    $form['factory_part_c']['district_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_edit_emp_district_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['subdivision_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_empsubdv_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['areatype_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_emp_areatype_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['block_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_empareatype_name_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['panchayat_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_emp_vill_ward_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['policestation_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_empps_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['postoffice_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_post_office_div">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_c']['user_aadhar_1'] = array(
			   '#prefix' => '<div id="oprmntadr_user_aadhar_1_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_c']['user_aadhar_2'] = array(
			   '#prefix' => '<div id="oprmntadr_user_aadhar_2_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_c']['user_aadhar_3'] = array(
			   '#prefix' => '<div id="oprmntadr_user_aadhar_3_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_c']['passport_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_passport_oprmntadr_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Passport No.'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($passport_oprmntadr) ? $passport_oprmntadr :'',
				'#required' 		=> TRUE,
			);
			$form['factory_part_c']['passport_date_of_issue_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doi_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Issue'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value'    => !empty($passport_date_of_issue_oprmntadr) ? $passport_date_of_issue_oprmntadr :'',
				'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Issue of passport.'),
			);
			$form['factory_part_c']['passport_date_of_expiry_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doe_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Expiry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value'    => !empty($passport_date_of_expiry_oprmntadr) ? $passport_date_of_expiry_oprmntadr :'',
				'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Expiry of passport.'),
			);
			
			$form['factory_part_c']['street_name_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_streetname_div" class="col-md-4 col-xs-12" ><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your Street Name / Road Name'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($street_name_oprmntadr) ? $street_name_oprmntadr :'',
				'#required' 		=> TRUE,
			);
			$form['factory_part_c']['house_no_oprmntadr'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="oprmntadr_houseno_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your House No.'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($house_no_oprmntadr) ? $house_no_oprmntadr :'',
				'#required' 		=> TRUE,
			);
			$form['factory_part_c']['police_station_oprmntadr'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="oprmntadr_policestation_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Local Police Station'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($police_station_oprmntadr) ? $police_station_oprmntadr :'',
				'#required' 		=> TRUE,
			);
			
	} else{ 
		
		$form['factory_part_c']['pincodeoprmntadr'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12" id="pincodeoprmntadr_id" ><label class="input">',
		  '#suffix' 			=> '</label></div>',
		  '#autocomplete_path' 	=> 'pinautocomplete',
		  '#id'					=> 'pincode_autocomplete_oprmntadr',
		  '#maxlength' 			=> 6, 
		  '#title'				=>	t($country_oprmntadr_check_data.'(iii) Pincode'),
		  '#required' 			=> TRUE,
		  '#type' 				=> 'textfield',
		  '#default_value'  => !empty($occupier_pincodeoprmntadr) ? $occupier_pincodeoprmntadr    :'',
		  '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode',
			    $country_oprmntadr_ck => $country_oprmntadr_ck
            ),
		  '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprmntadr',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
		);
		$value_pincode_oprmntadr				= isset($form_state['values']['pincodeoprmntadr'])? $form_state['values']['pincodeoprmntadr'] : $occupier_pincodeoprmntadr;
		
		if(!empty($value_pincode_oprmntadr)){
			
		   $query_oprmntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_oprmntadr), '=');
		
			$result_oprmntadr = $query_oprmntadr->execute();
	
			if($result_oprmntadr->rowcount()>0){
				$final_oprmntadr = $result_oprmntadr->fetchAssoc();
				$pincode_v_oprmntadr 		 = $value_pincode_oprmntadr;
				$state_v_oprmntadr		 = $final_oprmntadr['state_code'];
				$district_v_oprmntadr		 = $final_oprmntadr['district_code'];
				$post_office_oprmntadr 	 = $final_oprmntadr['po_name'];
			}
		} 
		
		if(!empty($state_v_oprmntadr)){
			$form['factory_part_c']['state_oprmntadr'] = array(
			   '#title'			=>	$country_oprmntadr_check_data.'(iv) State',
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State',$country_oprmntadr_ck => $country_oprmntadr_ck),
			   '#disabled' 		=> TRUE, 
			   '#required' 		=> TRUE,
			   '#options' 		=> get_all_state($state_v_oprmntadr),
			   '#value' 		=> !empty($state_v_oprmntadr) ? $state_v_oprmntadr : $occupier_state_oprmntadr,
			   '#prefix' 		=> '<div class="col-md-4" id="oprmntadr_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',			
									'callback'		=> 'get_ajax_load_oprmntadr',
									'progress'		=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
									),
					)
			);
		}else{
			$form['factory_part_c']['state_oprmntadr'] = array(
			   '#title'			=> t('(iv) State'),
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#disabled' 		=> TRUE,
			   '#required' 		=> TRUE,
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),

			   '#options' 		=> array(''=>t('Select State')),
			   '#prefix' 		=> '<div class="col-md-4" id="oprmntadr_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprmntadr',
										'progress'		=>	array(

											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}

		$value_state_oprmntadr = isset($form_state['values']['state_oprmntadr'])? $form_state['values']['state_oprmntadr'] : $occupier_state_oprmntadr;
		
		if(!empty($state_v_oprmntadr)){	
			$form['factory_part_c']['district_oprmntadr'] = array(
			   '#title'=> $country_oprmntadr_check_data.'(v) District',
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District',$country_oprmntadr_ck => $country_oprmntadr_ck),
			   '#options' => get_district_by_id($state_v_oprmntadr),
			   '#value' => !empty($district_v_oprmntadr) ? $district_v_oprmntadr : $occupier_district_oprmntadr,
			   '#prefix' => '<div class="col-md-4 clear-left" id="oprmntadr_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			   '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprmntadr',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}else{
			$form['factory_part_c']['district_oprmntadr'] = array(
			   '#title'=>	t('(v) District'),
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District'),
			   '#options' => array(''=>t('Select District')),
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			);
		}
		
		$value_district_oprmntadr	=	isset($form_state['values']['district_oprmntadr']) ? $form_state['values']['district_oprmntadr'] : $occupier_district_oprmntadr;
		
		if(!empty($district_v_oprmntadr) && !empty($state_v_oprmntadr) && $state_v_oprmntadr == 1){
			
			$form['factory_part_c']['subdivision_oprmntadr'] = array(
			   '#title'=>	$country_oprmntadr_check_data.'(vi) Sub-Division',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Sub Division', $country_oprmntadr_ck => $country_oprmntadr_ck ),
			   '#required' 	=> TRUE,
			   '#options' => common_custom_user_subdivisionlist_list_new($district_v_oprmntadr),
			   '#default_value' => $occupier_subdivision_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_empsubdv_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'		=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprmntadr',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{ 
			
			$form['factory_part_c']['subdivision_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_empsubdv_replace">',
			   '#suffix' => '</div>',
			);
		}		
		$value_subdivision_oprmntadr	= isset($form_state['values']['subdivision_oprmntadr']) ? $form_state['values']['subdivision_oprmntadr'] : $occupier_subdivision_oprmntadr;
		
		if(!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr) && $state_v_oprmntadr == 1){
			$form['factory_part_c']['areatype_oprmntadr'] = array(
			   '#title'=> $country_oprmntadr_check_data.'(vii) Area Type',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Area Type', $country_oprmntadr_ck => $country_oprmntadr_ck),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_areatype_list_new($value_district_oprmntadr, $value_subdivision_oprmntadr),
			   '#default_value' => $occupier_areatype_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_emp_areatype_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprmntadr',
							'progress'		=>	array(
								'type'		=> 'throbber',
								'message'	=> t('loading'),
							),
					)
			);
		}else{
			
			$form['factory_part_c']['areatype_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_emp_areatype_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_areatype_oprmntadr	=	isset($form_state['values']['areatype_oprmntadr']) ? $form_state['values']['areatype_oprmntadr'] : $occupier_areatype_oprmntadr;
	
		if(!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr) && $state_v_oprmntadr == 1){
			
			if ($value_areatype_oprmntadr == 'B') {
                $areatype_name_oprmntadr = 'Block';
            } elseif ($value_areatype_oprmntadr == 'M') {
                $areatype_name_oprmntadr = 'Municipality';
            } elseif ($value_areatype_oprmntadr == 'C') {
                $areatype_name_oprmntadr = 'Corporation';
            } elseif ($value_areatype_oprmntadr == 'S') {
                $areatype_name_oprmntadr = 'SEZ';
            } elseif ($value_areatype_oprmntadr == 'N') {
                $areatype_name_oprmntadr = 'Notified Area';
            }
			
			$form['factory_part_c']['block_oprmntadr'] = array(
			   '#title'=> $country_oprmntadr_check_data.'(viii) '.$areatype_name_oprmntadr,
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'subdivision', $country_oprmntadr_ck => $country_oprmntadr_ck),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_block_list_new($value_subdivision_oprmntadr,$value_areatype_oprmntadr),
			   '#default_value' => $occupier_block_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_empareatype_name_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprmntadr',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{
			$form['factory_part_c']['block_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_empareatype_name_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_block_oprmntadr	= 	isset($form_state['values']['block_oprmntadr']) ? $form_state['values']['block_oprmntadr'] : $occupier_block_oprmntadr;
					
		if(!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr)  && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr) && $state_v_oprmntadr == 1){
			
            if ($value_areatype_oprmntadr == 'B') {
                $area_name_oprmntadr = 'Gram Panchayat';
                $area_code_oprmntadr = 'V';
            } elseif ($value_areatype_oprmntadr == 'M') {
                $area_name_oprmntadr = 'Ward';
                $area_code_oprmntadr = 'W';
            } elseif ($value_areatype_oprmntadr == 'C') {
                $area_name_oprmntadr = 'Ward';
                $area_code_oprmntadr = 'C';
            } elseif ($value_areatype_oprmntadr == 'S') {
                $area_name_oprmntadr = 'Sector';
                $area_code_oprmntadr = 'S';
            } elseif ($value_areatype_oprmntadr == 'N') {
                $area_name_oprmntadr = 'Notified Area';
                $area_code_oprmntadr = 'N';
            }
		$form['factory_part_c']['panchayat_oprmntadr'] = array(
		   '#title'=> $country_oprmntadr_check_data.'(ix) '.$area_name_oprmntadr,
		   '#type' => 'select',
		   '#attributes' => array('class'=>array(''), 'placeholder'=>'panchayat', $country_oprmntadr_ck => $country_oprmntadr_ck),
		   '#default_value' => $occupier_panchayat_oprmntadr,
		   '#required' 		=> TRUE,
		   '#options' => get_full_villward($value_block_oprmntadr, $area_code_oprmntadr),
		   '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
		   '#suffix' => '</label></div></div>',
		   '#ajax'=> array(
				'event' 		=> 'change',
				'effect' 		=> 'fade',			
				'callback'		=> 'get_ajax_load_oprmntadr',
				'progress'		=>	array(
					'type'		=>'throbber',
					'message'	=>t('loading'),
				),
				)
			);
		}else{
			
			$form['factory_part_c']['panchayat_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_panchayat_oprmntadr 	= 	isset($form_state['values']['panchayat_oprmntadr']) ? $form_state['values']['panchayat_oprmntadr'] : $occupier_panchayat_oprmntadr;

		if(!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr)  && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_panchayat_oprmntadr) && $state_v_oprmntadr == 1){
			
			$form['factory_part_c']['policestation_oprmntadr'] = array(
			   '#title'=> $country_oprmntadr_check_data.'(x) Police Station',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Police Station', $country_oprmntadr_ck => $country_oprmntadr_ck),
			   '#required' 		=> TRUE,
			   '#default_value' => $occupier_policestation_oprmntadr,
			   '#options' => common_custom_user_ps_list_new($value_district_oprmntadr),
			   '#prefix' => '<div id="oprmntadr_empps_replace"><div class="col-md-4"><label class="select label-block">',
			   '#suffix' => '</label></div></div>',
			);
		}else{
			$form['factory_part_c']['policestation_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_empps_replace">',
			   '#suffix' => '</div>',
			);
		}

			$form['factory_part_c']['postoffice_oprmntadr'] = array(
			   '#title'=> $country_oprmntadr_check_data.'(xi) Post Office',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Post Office',$country_oprmntadr_ck => $country_oprmntadr_ck),
			   '#options' => common_custom_post_office_list_new($pincode_v_oprmntadr),
			   '#default_value' => $occupier_postoffice_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_post_office_div"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			);
			
			$form['factory_part_c']['user_aadhar_1'] = array(
			   '#title'			=>	$country_oprmntadr_check_data.t('Aadhar No.'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprmntadr_user_aadhar_1_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value'  	=> $user_aadhar_1_oprmntadr,
			   '#attributes' => array('class' => array('NoField'),'maxlength' => 4,'size' => '','id'=>'number1',$country_oprmntadr_ck => $country_oprmntadr_ck),
			);
			$form['factory_part_c']['user_aadhar_2'] = array(
			   '#title'			=> t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprmntadr_user_aadhar_2_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value'  	=> $user_aadhar_2_oprmntadr,
			   '#attributes' => array('class' => array('NoField'),'maxlength' => 4,'size' => '','id'=>'number2',$country_oprmntadr_ck => $country_oprmntadr_ck),
			);
			$form['factory_part_c']['user_aadhar_3'] = array(
			   '#title'			=>	t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprmntadr_user_aadhar_3_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value'  	=> $user_aadhar_3_oprmntadr,
			   '#attributes' => array('class' => array('NoField'),'maxlength' => 4,'size' => '','id'=>'number3',$country_oprmntadr_ck => $country_oprmntadr_ck),
			);
			
			$form['factory_part_c']['passport_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_passport_oprmntadr_div">',
				'#suffix' 			=> '</div>',
			);
			$form['factory_part_c']['passport_date_of_issue_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doi_div">',
				'#suffix' 			=> '</div>',
			);
			$form['factory_part_c']['passport_date_of_expiry_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doe_div">',
				'#suffix' 			=> '</div>',
			);
			
			if(!empty($state_v_oprmntadr) && $state_v_oprmntadr == 1)
			{
				$form['factory_part_c']['street_name_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_streetname_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprmntadr_check_data.t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'    => $street_name_oprmntadr,
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['factory_part_c']['house_no_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprmntadr_check_data.t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'    => $house_no_oprmntadr,
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['factory_part_c']['police_station_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_policestation_div">',
					'#suffix' 			=> '</div>',
				);

			} else {
				$form['factory_part_c']['street_name_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_streetname_div" class="col-md-4 col-xs-12" ><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprmntadr_check_data.t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'    => $street_name_oprmntadr,
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['factory_part_c']['house_no_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprmntadr_check_data.t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'    => $house_no_oprmntadr,
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['factory_part_c']['police_station_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_policestation_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprmntadr_check_data.t('Enter Local Police Station'),
					'#type' 			=> 'textfield',
					'#default_value'    => $police_station_oprmntadr,
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
			}
			
	 }
	 
	$form['factory_part_c']['addrline_oprmntadr'] = array(
		   '#title'=>'',
		   '#rows'=> 3,
		   '#type' => 'textarea',
		   '#attributes' => array('class'=>array(''), 'placeholder'=> 'Address Line',$country_oprmntadr_ck => $country_oprmntadr_ck),
		   '#default_value'    => $occupier_addrline_oprmntadr,
		   '#prefix'=> '<div class="col-md-12"><label class="textarea label-block">'.$country_oprmntadr_check_data.' Address',
		   '#required' 		=> TRUE,
	   	   '#suffix' =>'</label></div>',
	);	
	
	/********** Occupier Permanent Address - End **********/

    /********** Occupier Present Address - Start **********/
   
	$form['factory_part_oprsntadr'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('I ii). Occupier Present Address'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);		
	
		$form['factory_part_oprsntadr']['markup_div'] = array(
			'#prefix' =>'<div class="row">' ,
			'#suffix' => '',
		);
	
		$form['factory_part_oprsntadr']['same_as_address_occupier'] = array(
			'#type' => 'checkbox',
			'#default_value' => !empty($occupier_present_address_same)?$occupier_present_address_same:0,
			'#attributes' => array('class' => array( ''),$occupier_present_address_check_ck => $occupier_present_address_check_ck ),
			'#ajax' => array(
				'event' => 'change',
				'effect' => 'fade',
				'callback' => 'get_ajax_same_address_permanent_occupier',
				'progress' => array(
					'type' => 'throbber',
					'message' => t('loading')
				)
			),
			'#title' => t('Same as occupier permanent address'),
			'#prefix' => '<div class="col-md-12 col-xs-12">',
			'#suffix' => '</div>'
		);
	 $checkbox_premanent_occupier = isset($form_state['values']['same_as_address_occupier']) ? $form_state['values']['same_as_address_occupier'] :$occupier_present_address_same;
	
	 if($checkbox_premanent_occupier == 0) {
	$form['factory_part_oprsntadr']['country_oprsntadr'] 	= array(
			  '#prefix' 			=> '<div id="country_oprsntadr_div"><div class="col-md-4 col-xs-12"><label class="select label-block">',
			  '#suffix' 			=> '</label></div></div>',
			  '#maxlength' 			=> 6, 
			  '#options' 			=> get_country_with_ph(),
			  '#default_value'      => !empty($country_oprsntadr) ? $country_oprsntadr :'',
			  '#title' 				=> t($country_oprsntadr_check_data.'(i) Nationality'),
			  '#attributes' 		=> array('class' => array( ''),$country_oprsntadr_ck => $country_oprsntadr_ck ),
			  '#required' 			=> TRUE,
			  '#type' 				=> 'select',
			  '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'get_ajax_load_oprsntadr',
											'progress'		=>	array(
												'type'		=>'throbber',
												'message'	=>t('loading'),
											),
									)
			);

	if((isset($form_state['values']['country_oprsntadr']) && trim($form_state['values']['country_oprsntadr']) != '99') || (!isset($form_state['values']['country_oprsntadr']) && !empty($country_oprsntadr) && ($country_oprsntadr != '99')))
	{ 

			$form['factory_part_oprsntadr']['pincodeoprsntadr'] = array(
				'#prefix' 	=> '<div id="pincodeoprsntadr_id">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['state_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_edit_emp_state_replace">',
				'#suffix' 	=> '</div>'
			);
		    $form['factory_part_oprsntadr']['district_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_edit_emp_district_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_empsubdv_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_emp_areatype_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['block_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_empareatype_name_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['panchayat_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_emp_vill_ward_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_empps_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['postoffice_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_post_office_div">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['user_aadhar_4'] = array(
			   '#prefix' => '<div id="oprsntadr_user_aadhar_4_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_oprsntadr']['user_aadhar_5'] = array(
			   '#prefix' => '<div id="oprsntadr_user_aadhar_5_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_oprsntadr']['user_aadhar_6'] = array(
			   '#prefix' => '<div id="oprsntadr_user_aadhar_6_div">',
			   '#suffix' => '</div>',
			);
			
			$form['factory_part_oprsntadr']['passport_oprsntadr'] 	= array(
				'#prefix' 			=> '<div id="oprsntadr_passport_oprmntadr_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Passport No.'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($passport_oprsntadr) ? $passport_oprsntadr :'',
				'#required' 		=> TRUE,
			);
			$form['factory_part_oprsntadr']['passport_date_of_issue_oprsntadr'] 	= array(
				'#prefix' 			=> '<div id="oprsntadr_doi_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Issue'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value'    => !empty($passport_date_of_issue_oprsntadr) ? $passport_date_of_issue_oprsntadr :'',
				'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Issue of passport.'),
			);
			$form['factory_part_oprsntadr']['passport_date_of_expiry_oprsntadr'] 	= array(
				'#prefix' 			=> '<div id="oprsntadr_doe_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Expiry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value'    => !empty($passport_date_of_expiry_oprsntadr) ? $passport_date_of_expiry_oprsntadr :'',
				'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Expiry of passport.'),
			);
			
			$form['factory_part_oprsntadr']['street_name_oprsntadr'] 	= array(
				'#prefix' 			=> '<div id="oprsntadr_streetname_div" class="col-md-4 col-xs-12" ><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your Street Name / Road Name'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($street_name_oprsntadr) ? $street_name_oprsntadr :'',
				'#required' 		=> TRUE,
			);
			$form['factory_part_oprsntadr']['house_no_oprsntadr'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="oprsntadr_houseno_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your House No.'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($house_no_oprsntadr) ? $house_no_oprsntadr :'',
				'#required' 		=> TRUE,
			);
			$form['factory_part_oprsntadr']['police_station_oprsntadr'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="oprsntadr_policestation_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Local Police Station'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($police_station_oprsntadr) ? $police_station_oprsntadr :'',
				'#required' 		=> TRUE,
			);

	} else{ 
		
		$form['factory_part_oprsntadr']['pincodeoprsntadr'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12" id="pincodeoprsntadr_id" ><label class="input">',
		  '#suffix' 			=> '</label></div>',
		  '#autocomplete_path' 	=> 'pinautocomplete',
		  '#id'					=> 'pincode_autocomplete_oprsntadr',
		  '#maxlength' 			=> 6, 
		  '#title'				=>	t($country_oprsntadr_check_data.'(iii) Pincode'),
		  '#required' 			=> TRUE,
		  '#type' 				=> 'textfield',
		  '#default_value'  => !empty($occupier_pincodeoprsntadr) ? $occupier_pincodeoprsntadr    :'',
		  '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode',
			    $country_oprsntadr_ck => $country_oprsntadr_ck
            ),
		  '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprsntadr',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
		);
		$value_pincode_oprsntadr				= isset($form_state['values']['pincodeoprsntadr'])? $form_state['values']['pincodeoprsntadr'] : $occupier_pincodeoprsntadr;
		
		if(!empty($value_pincode_oprsntadr)){
			
		   $query_oprsntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_oprsntadr), '=');
		
			$result_oprsntadr = $query_oprsntadr->execute();
	
			if($result_oprsntadr->rowcount()>0){
				$final_oprsntadr = $result_oprsntadr->fetchAssoc();
				$pincode_v_oprsntadr 		 = $value_pincode_oprsntadr;
				$state_v_oprsntadr		 = $final_oprsntadr['state_code'];
				$district_v_oprsntadr		 = $final_oprsntadr['district_code'];
				$post_office_oprsntadr 	 = $final_oprsntadr['po_name'];
			}
		} 
		
		if(!empty($state_v_oprsntadr)){
			$form['factory_part_oprsntadr']['state_oprsntadr'] = array(
			   '#title'			=>	$country_oprsntadr_check_data.'(iv) State',
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State',$country_oprsntadr_ck => $country_oprsntadr_ck),
			   '#disabled' 		=> TRUE, 
			   '#required' 		=> TRUE,
			   '#options' 		=> get_all_state($state_v_oprsntadr),
			   '#value' 		=> !empty($state_v_oprsntadr) ? $state_v_oprsntadr : $occupier_state_oprsntadr,
			   '#prefix' 		=> '<div class="col-md-4" id="oprsntadr_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',			
									'callback'		=> 'get_ajax_load_oprsntadr',
									'progress'		=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
									),
					)
			);
		}else{
			$form['factory_part_oprsntadr']['state_oprsntadr'] = array(
			   '#title'			=> t('(iv) State'),
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#disabled' 		=> TRUE,
			   '#required' 		=> TRUE,
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),

			   '#options' 		=> array(''=>t('Select State')),
			   '#prefix' 		=> '<div class="col-md-4" id="oprsntadr_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprsntadr',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}

		$value_state_oprsntadr = isset($form_state['values']['state_oprsntadr'])? $form_state['values']['state_oprsntadr'] : $occupier_state_oprsntadr;
		
		if(!empty($state_v_oprsntadr)){	
			$form['factory_part_oprsntadr']['district_oprsntadr'] = array(
			   '#title'=> $country_oprsntadr_check_data.'(v) District',
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District',$country_oprsntadr_ck => $country_oprsntadr_ck),
			   '#options' => get_district_by_id($state_v_oprsntadr),
			   '#value' => !empty($district_v_oprsntadr) ? $district_v_oprsntadr : $occupier_district_oprsntadr,
			   '#prefix' => '<div class="col-md-4 clear-left" id="oprsntadr_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			   '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprsntadr',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}else{
			$form['factory_part_oprsntadr']['district_oprsntadr'] = array(
			   '#title'=>	t('(v) District'),
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District'),
			   '#options' => array(''=>t('Select District')),
			   '#prefix' => '<div class="col-md-4" id="oprsntadr_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			);
		}
		
		$value_district_oprsntadr	=	isset($form_state['values']['district_oprsntadr']) ? $form_state['values']['district_oprsntadr'] : $occupier_district_oprsntadr;
		
		if(!empty($district_v_oprsntadr) && !empty($state_v_oprsntadr) && $state_v_oprsntadr == 1){
			
			$form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
			   '#title'=>	$country_oprsntadr_check_data.'(vi) Sub-Division',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Sub Division', $country_oprsntadr_ck => $country_oprsntadr_ck ),
			   '#required' 	=> TRUE,
			   '#options' => common_custom_user_subdivisionlist_list_new($district_v_oprsntadr),
			   '#default_value' => $occupier_subdivision_oprsntadr,
			   '#prefix' => '<div class="col-md-4" id="oprsntadr_empsubdv_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'		=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprsntadr',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{ 
			
			$form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
			   '#prefix' => '<div id="oprsntadr_empsubdv_replace">',
			   '#suffix' => '</div>',
			);
		}		
		$value_subdivision_oprsntadr	= isset($form_state['values']['subdivision_oprsntadr']) ? $form_state['values']['subdivision_oprsntadr'] : $occupier_subdivision_oprsntadr;
		
		if(!empty($value_district_oprsntadr) && !empty($value_state_oprsntadr) && !empty($value_subdivision_oprsntadr) && $state_v_oprsntadr == 1){
			$form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
			   '#title'=> $country_oprsntadr_check_data.'(vii) Area Type',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Area Type', $country_oprsntadr_ck => $country_oprsntadr_ck),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_areatype_list_new($value_district_oprsntadr, $value_subdivision_oprsntadr),
			   '#default_value' => $occupier_areatype_oprsntadr,
			   '#prefix' => '<div class="col-md-4" id="oprsntadr_emp_areatype_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprsntadr',
							'progress'		=>	array(
								'type'		=> 'throbber',
								'message'	=> t('loading'),
							),
					)
			);
		}else{
			
			$form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
			   '#prefix' => '<div id="oprsntadr_emp_areatype_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_areatype_oprsntadr	=	isset($form_state['values']['areatype_oprsntadr']) ? $form_state['values']['areatype_oprsntadr'] : $occupier_areatype_oprsntadr;
	
		if(!empty($value_district_oprsntadr) && !empty($value_state_oprsntadr) && !empty($value_subdivision_oprsntadr) && !empty($value_areatype_oprsntadr) && $state_v_oprsntadr == 1){
			
			if ($value_areatype_oprsntadr == 'B') {
                $areatype_name_oprsntadr = 'Block';
            } elseif ($value_areatype_oprsntadr == 'M') {
                $areatype_name_oprsntadr = 'Municipality';
            } elseif ($value_areatype_oprsntadr == 'C') {
                $areatype_name_oprsntadr = 'Corporation';
            } elseif ($value_areatype_oprsntadr == 'S') {
                $areatype_name_oprsntadr = 'SEZ';
            } elseif ($value_areatype_oprsntadr == 'N') {
                $areatype_name_oprsntadr = 'Notified Area';
            }
			
			$form['factory_part_oprsntadr']['block_oprsntadr'] = array(
			   '#title'=> $country_oprsntadr_check_data.'(viii) '.$areatype_name_oprsntadr,
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'subdivision', $country_oprsntadr_ck => $country_oprsntadr_ck),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_block_list_new($value_subdivision_oprsntadr,$value_areatype_oprsntadr),
			   '#default_value' => $occupier_block_oprsntadr,
			   '#prefix' => '<div class="col-md-4" id="oprsntadr_empareatype_name_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprsntadr',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{
			$form['factory_part_oprsntadr']['block_oprsntadr'] = array(
			   '#prefix' => '<div id="oprsntadr_empareatype_name_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_block_oprsntadr	= 	isset($form_state['values']['block_oprsntadr']) ? $form_state['values']['block_oprsntadr'] : $occupier_block_oprsntadr;
					
		if(!empty($value_district_oprsntadr) && !empty($value_subdivision_oprsntadr) && !empty($value_areatype_oprsntadr)  && !empty($value_block_oprsntadr) && !empty($value_state_oprsntadr) && $state_v_oprsntadr == 1){
			
            if ($value_areatype_oprsntadr == 'B') {
                $area_name_oprsntadr = 'Gram Panchayat';
                $area_code_oprsntadr = 'V';
            } elseif ($value_areatype_oprsntadr == 'M') {
                $area_name_oprsntadr = 'Ward';
                $area_code_oprsntadr = 'W';
            } elseif ($value_areatype_oprsntadr == 'C') {
                $area_name_oprsntadr = 'Ward';
                $area_code_oprsntadr = 'C';
            } elseif ($value_areatype_oprsntadr == 'S') {
                $area_name_oprsntadr = 'Sector';
                $area_code_oprsntadr = 'S';
            } elseif ($value_areatype_oprsntadr == 'N') {
                $area_name_oprsntadr = 'Notified Area';
                $area_code_oprsntadr = 'N';
            }
		$form['factory_part_oprsntadr']['panchayat_oprsntadr'] = array(
		   '#title'=> $country_oprsntadr_check_data.'(ix) '.$area_name_oprsntadr,
		   '#type' => 'select',
		   '#attributes' => array('class'=>array(''), 'placeholder'=>'panchayat', $country_oprsntadr_ck => $country_oprsntadr_ck),
		   '#default_value' => $occupier_panchayat_oprsntadr,
		   '#required' 		=> TRUE,
		   '#options' => get_full_villward($value_block_oprsntadr, $area_code_oprsntadr),
		   '#prefix' => '<div id="oprsntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
		   '#suffix' => '</label></div></div>',
		   '#ajax'=> array(
				'event' 		=> 'change',
				'effect' 		=> 'fade',			
				'callback'		=> 'get_ajax_load_oprsntadr',
				'progress'		=>	array(
					'type'		=>'throbber',
					'message'	=>t('loading'),
				),
				)
			);
		}else{
			
			$form['factory_part_oprsntadr']['panchayat_oprsntadr'] = array(
			   '#prefix' => '<div id="oprsntadr_emp_vill_ward_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_panchayat_oprsntadr 	= 	isset($form_state['values']['panchayat_oprsntadr']) ? $form_state['values']['panchayat_oprsntadr'] : $occupier_panchayat_oprsntadr;
		
		if(!empty($value_district_oprsntadr) && !empty($value_subdivision_oprsntadr) && !empty($value_areatype_oprsntadr)  && !empty($value_block_oprsntadr) && !empty($value_state_oprsntadr) && !empty($value_panchayat_oprsntadr) && $state_v_oprsntadr == 1){
			
			$form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
			   '#title'=> $country_oprsntadr_check_data.'(x) Police Station',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Police Station', $country_oprsntadr_ck => $country_oprsntadr_ck),
			   '#required' 		=> TRUE,
			   '#default_value' => $occupier_policestation_oprsntadr,
			   '#options' => common_custom_user_ps_list_new($value_district_oprsntadr),
			   '#prefix' => '<div id="oprsntadr_empps_replace"><div class="col-md-4"><label class="select label-block">',
			   '#suffix' => '</label></div></div>',
			);
		}else{
			$form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
			   '#prefix' => '<div id="oprsntadr_empps_replace">',
			   '#suffix' => '</div>',
			);
		}

			$form['factory_part_oprsntadr']['postoffice_oprsntadr'] = array(
			   '#title'=> $country_oprsntadr_check_data.'(xi) Post Office',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Post Office',$country_oprsntadr_ck => $country_oprsntadr_ck),
			   '#options' => common_custom_post_office_list_new($pincode_v_oprsntadr),
			   '#prefix' => '<div class="col-md-4" id="oprsntadr_post_office_div"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#default_value' => $occupier_postoffice_oprsntadr,
			   '#required' 		=> TRUE,
			);
			
			$form['factory_part_oprsntadr']['user_aadhar_4'] = array(
			   '#title'			=>	$country_oprsntadr_check_data.t('Aadhar No.'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprsntadr_user_aadhar_4_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value' => $user_aadhar_1_oprsntadr,
			   '#attributes' => array('maxlength' => 4,'size' => '','id'=>'number4',$country_oprsntadr_ck => $country_oprsntadr_ck),
			);
			$form['factory_part_oprsntadr']['user_aadhar_5'] = array(
			   '#title'			=>	t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprsntadr_user_aadhar_5_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value' => $user_aadhar_2_oprsntadr,
			   '#attributes' => array('maxlength' => 4,'size' => '','id'=>'number5',$country_oprsntadr_ck => $country_oprsntadr_ck),
			);
			$form['factory_part_oprsntadr']['user_aadhar_6'] = array(
			   '#title'			=>	t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprsntadr_user_aadhar_6_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value' => $user_aadhar_3_oprsntadr,
			   '#attributes' => array('maxlength' => 4,'size' => '','id'=>'number6',$country_oprsntadr_ck => $country_oprsntadr_ck),
			);
			
			$form['factory_part_oprsntadr']['passport_oprsntadr'] 	= array(
				'#prefix' 			=> '<div id="oprsntadr_passport_oprmntadr_div">',
				'#suffix' 			=> '</div>',
			);
			$form['factory_part_oprsntadr']['passport_date_of_issue_oprsntadr'] 	= array(
				'#prefix' 			=> '<div id="oprsntadr_doi_div">',
				'#suffix' 			=> '</div>',
			);
			$form['factory_part_oprsntadr']['passport_date_of_expiry_oprsntadr'] 	= array(
				'#prefix' 			=> '<div id="oprsntadr_doe_div">',
				'#suffix' 			=> '</div>',
			);
			
			if(!empty($state_v_oprsntadr) && $state_v_oprsntadr == 1)
			{
				$form['factory_part_oprsntadr']['street_name_oprsntadr'] 	= array(
					'#prefix' 			=> '<div id="oprsntadr_streetname_div" class="col-md-4 col-xs-12" ><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprsntadr_check_data.t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'    => !empty($street_name_oprsntadr) ? $street_name_oprsntadr :'',
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprsntadr_ck => $country_oprsntadr_ck),
				);
				$form['factory_part_oprsntadr']['house_no_oprsntadr'] 	= array(
					'#prefix' 			=> '<div id="oprsntadr_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprsntadr_check_data.t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'    => !empty($house_no_oprsntadr) ? $house_no_oprsntadr :'',
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprsntadr_ck => $country_oprsntadr_ck),
				);
				$form['factory_part_oprsntadr']['police_station_oprsntadr'] 	= array(
					'#prefix' 			=> '<div id="oprsntadr_policestation_div">',
					'#suffix' 			=> '</div>',
				);

			} else {
				$form['factory_part_oprsntadr']['street_name_oprsntadr'] 	= array(
					'#prefix' 			=> '<div id="oprsntadr_streetname_div" class="col-md-4 col-xs-12" ><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprsntadr_check_data.t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'    => !empty($street_name_oprsntadr) ? $street_name_oprsntadr :'',
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprsntadr_ck => $country_oprsntadr_ck),
				);
				$form['factory_part_oprsntadr']['house_no_oprsntadr'] 	= array(
					'#prefix' 			=> '<div id="oprsntadr_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'    => !empty($house_no_oprsntadr) ? $house_no_oprsntadr :'',
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprsntadr_ck => $country_oprsntadr_ck),
				);
				$form['factory_part_oprsntadr']['police_station_oprsntadr'] 	= array(
					'#prefix' 			=> '<div id="oprsntadr_policestation_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	$country_oprsntadr_check_data.t('Enter Local Police Station'),
					'#type' 			=> 'textfield',
					'#default_value'    => !empty($police_station_oprsntadr) ? $police_station_oprsntadr :'',
					'#required' 		=> TRUE,
					'#attributes' 		=> array($country_oprsntadr_ck => $country_oprsntadr_ck),
				);
			}
	 	}

		$form['factory_part_oprsntadr']['addrline_oprsntadr'] = array(
		   '#title'=>'',
		   '#rows'=> 3,
		   '#type' => 'textarea',
		   '#attributes' => array('class'=>array(''), 'placeholder'=>'Address Line',$country_oprsntadr_ck => $country_oprsntadr_ck),
		   '#prefix'=> '<div id="addrline_oprsntadr_id"><div class="col-md-12"><label class="textarea label-block">'.$country_oprsntadr_check_data.' Address',
	   	   '#default_value'    => $occupier_addrline_oprsntadr,
		   '#suffix' =>'</label></div></div>',
		   '#required' 		=> TRUE,
		);
	}
	
	 if($checkbox_premanent_occupier == 1) {
			$form['factory_part_oprsntadr']['country_oprsntadr'] = array(
				'#prefix' 	=> '<div id="country_oprsntadr_div">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['pincodeoprsntadr'] = array(
				'#prefix' 	=> '<div id="pincodeoprsntadr_id">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['state_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_edit_emp_state_replace">',
				'#suffix' 	=> '</div>'
			);
		    $form['factory_part_oprsntadr']['district_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_edit_emp_district_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_empsubdv_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_emp_areatype_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['block_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_empareatype_name_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['panchayat_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_emp_vill_ward_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_empps_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['postoffice_oprsntadr'] = array(
				'#prefix' 	=> '<div id="oprsntadr_post_office_div">',
				'#suffix' 	=> '</div>'
			);
			$form['factory_part_oprsntadr']['user_aadhar_4'] = array(
			   '#prefix' => '<div id="oprsntadr_user_aadhar_4_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_oprsntadr']['user_aadhar_5'] = array(
			   '#prefix' => '<div id="oprsntadr_user_aadhar_5_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_oprsntadr']['user_aadhar_6'] = array(
			   '#prefix' => '<div id="oprsntadr_user_aadhar_6_div">',
			   '#suffix' => '</div>',
			);
			$form['factory_part_oprsntadr']['street_name_oprsntadr'] 	= array(
				'#prefix' => '<div id="oprsntadr_streetname_div">',
				'#suffix' => '</div>',
			);
			$form['factory_part_oprsntadr']['house_no_oprsntadr'] 	= array(
				'#prefix' => '<div id="oprsntadr_houseno_div">',
				'#suffix' => '</div>',
			);
			$form['factory_part_oprsntadr']['police_station_oprsntadr'] 	= array(
				'#prefix' => '<div id="oprsntadr_policestation_div">',
				'#suffix' => '</div>',

			);
			$form['factory_part_oprsntadr']['addrline_oprsntadr']      = array(
				'#prefix' => '<div id = "addrline_oprsntadr_id">',
				'#suffix' => '</div>'
			);
		}
	
	 $form['factory_part_oprsntadr']['thirdRowEnd'] = array(
		'#prefix' => '',
		'#suffix' => '</div>'
	  );
		
	/********** Occupier Present Address - End **********/    	
	
	if($plan_approve_status != 'F')
	{
		$form['back_link'] = array(
			
			'#markup' => l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'), 'applicant/caf_extn/caf-form-owner-extension/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno, array(
				'html' => TRUE,
				'attributes' => array(
					'class' => array(
						'btn btn-dark pull-left '
					)
				)
			))
		);
    
		$form['submit'] = array(
        '#prefix' => '',
        '#suffix' => '</div>',
        '#attributes' => array(
            'class' => array(
                'btn btn-success pull-right'
            )
        ),
        '#type' => 'submit',
        '#value' => 'Save'
    	);

		$form['pdf_link'] = array(
				'#markup' => l(t('Print Draft Copy'), 'download-pdf-occupier-as-draft/'.$applicationid.'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.$serviceid.'/'.$factory_typeid, array(
					'html' => TRUE,
					'attributes' => array(
						'class' => array('btn btn-warning pull-left '), 'style'=> 'margin-left: 10px'
					)
				))
			);
	}
    return $form;
}

function get_ajax_type_occupier($form, &$form_state)
{
    $commands   = array();
	$factprofiletype = $form_state['values']['ownership_type'];
    $commands[] = ajax_command_replace('#type_occupier_id', drupal_render($form['factory_part_d']['type_occupier']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_load_oprmntadr($form, $form_state)
{
	$commands = array();
	$commands[] = ajax_command_replace('#pincodeoprmntadr_id', drupal_render($form['factory_part_c']['pincodeoprmntadr']));
	
	$commands[] = ajax_command_replace('#oprmntadr_edit_emp_state_replace', drupal_render($form['factory_part_c']['state_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_edit_emp_district_replace', drupal_render($form['factory_part_c']['district_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_empsubdv_replace', drupal_render($form['factory_part_c']['subdivision_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_emp_areatype_replace', drupal_render($form['factory_part_c']['areatype_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_empareatype_name_replace', drupal_render($form['factory_part_c']['block_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_emp_vill_ward_replace', drupal_render($form['factory_part_c']['panchayat_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_empps_replace', drupal_render($form['factory_part_c']['policestation_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_post_office_div', drupal_render($form['factory_part_c']['postoffice_oprmntadr']));
	
	$commands[] = ajax_command_replace('#oprmntadr_user_aadhar_1_div', drupal_render($form['factory_part_c']['user_aadhar_1']));
	$commands[] = ajax_command_replace('#oprmntadr_user_aadhar_2_div', drupal_render($form['factory_part_c']['user_aadhar_2']));
	$commands[] = ajax_command_replace('#oprmntadr_user_aadhar_3_div', drupal_render($form['factory_part_c']['user_aadhar_3']));
	
	$commands[] = ajax_command_replace('#oprmntadr_streetname_div', drupal_render($form['factory_part_c']['street_name_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_houseno_div', drupal_render($form['factory_part_c']['house_no_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_policestation_div', drupal_render($form['factory_part_c']['police_station_oprmntadr']));
	
	$commands[] = ajax_command_replace('#oprmntadr_passport_oprmntadr_div', drupal_render($form['factory_part_c']['passport_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_doi_div', drupal_render($form['factory_part_c']['passport_date_of_issue_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_doe_div', drupal_render($form['factory_part_c']['passport_date_of_expiry_oprmntadr']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_load_oprsntadr($form, $form_state)
{
	$commands = array();
	$commands[] = ajax_command_replace('#pincodeoprsntadr_id', drupal_render($form['factory_part_oprsntadr']['pincodeoprsntadr']));
	
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_state_replace', drupal_render($form['factory_part_oprsntadr']['state_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_district_replace', drupal_render($form['factory_part_oprsntadr']['district_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empsubdv_replace', drupal_render($form['factory_part_oprsntadr']['subdivision_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_areatype_replace', drupal_render($form['factory_part_oprsntadr']['areatype_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empareatype_name_replace', drupal_render($form['factory_part_oprsntadr']['block_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_vill_ward_replace', drupal_render($form['factory_part_oprsntadr']['panchayat_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empps_replace', drupal_render($form['factory_part_oprsntadr']['policestation_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_post_office_div', drupal_render($form['factory_part_oprsntadr']['postoffice_oprsntadr']));
	
	$commands[] = ajax_command_replace('#oprsntadr_user_aadhar_4_div', drupal_render($form['factory_part_oprsntadr']['user_aadhar_4']));
	$commands[] = ajax_command_replace('#oprsntadr_user_aadhar_5_div', drupal_render($form['factory_part_oprsntadr']['user_aadhar_5']));
	$commands[] = ajax_command_replace('#oprsntadr_user_aadhar_6_div', drupal_render($form['factory_part_oprsntadr']['user_aadhar_6']));
	
	$commands[] = ajax_command_replace('#oprsntadr_streetname_div', drupal_render($form['factory_part_oprsntadr']['street_name_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_houseno_div', drupal_render($form['factory_part_oprsntadr']['house_no_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_policestation_div', drupal_render($form['factory_part_oprsntadr']['police_station_oprsntadr']));
	
	$commands[] = ajax_command_replace('#oprsntadr_passport_oprmntadr_div', drupal_render($form['factory_part_oprsntadr']['passport_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_doi_div', drupal_render($form['factory_part_oprsntadr']['passport_date_of_issue_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_doe_div', drupal_render($form['factory_part_oprsntadr']['passport_date_of_expiry_oprsntadr']));

	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_same_address_permanent_occupier($form, &$form_state)
{
	$commands = array();
	$commands[] = ajax_command_replace('#country_oprsntadr_div', drupal_render($form['factory_part_oprsntadr']['country_oprsntadr']));
	
	$commands[] = ajax_command_replace('#pincodeoprsntadr_id', drupal_render($form['factory_part_oprsntadr']['pincodeoprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_state_replace', drupal_render($form['factory_part_oprsntadr']['state_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_district_replace', drupal_render($form['factory_part_oprsntadr']['district_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empsubdv_replace', drupal_render($form['factory_part_oprsntadr']['subdivision_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_areatype_replace', drupal_render($form['factory_part_oprsntadr']['areatype_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empareatype_name_replace', drupal_render($form['factory_part_oprsntadr']['block_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_vill_ward_replace', drupal_render($form['factory_part_oprsntadr']['panchayat_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empps_replace', drupal_render($form['factory_part_oprsntadr']['policestation_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_post_office_div', drupal_render($form['factory_part_oprsntadr']['postoffice_oprsntadr']));
	$commands[] = ajax_command_replace('#addrline_oprsntadr_id', drupal_render($form['factory_part_oprsntadr']['addrline_oprsntadr']));
	
	$commands[] = ajax_command_replace('#oprsntadr_user_aadhar_4_div', drupal_render($form['factory_part_oprsntadr']['user_aadhar_4']));
	$commands[] = ajax_command_replace('#oprsntadr_user_aadhar_5_div', drupal_render($form['factory_part_oprsntadr']['user_aadhar_5']));
	$commands[] = ajax_command_replace('#oprsntadr_user_aadhar_6_div', drupal_render($form['factory_part_oprsntadr']['user_aadhar_6']));
	$commands[] = ajax_command_replace('#oprsntadr_streetname_div', drupal_render($form['factory_part_oprsntadr']['street_name_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_houseno_div', drupal_render($form['factory_part_oprsntadr']['house_no_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_policestation_div', drupal_render($form['factory_part_oprsntadr']['police_station_oprsntadr']));
 				
return array('#type' => 'ajax', '#commands' => $commands);
}

//function caf_form_occupier_validate($form, &$form_state)
//{
//  $comm_telephone = $form_state['values']['comm_telephone'];
//  $comm_mobile = $form_state['values']['comm_mobile'];
//  
//  if ($form_state['values']['comm_telephone']=="" && $form_state['values']['comm_mobile']=="") {
//    form_set_error('comm_telephone', t('You must enter either Telephone No. or Mobile!!'));
//  }
//}

function caf_form_occupier_extn_submit($form, &$form_state)
{
    global $user;
    $userid 				= $user->uid;
    $val    				= $form_state['values'];

    $service_id 			= encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$application_id 		= encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$factory_type_id				= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$reference_no		= encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
  	$plan_approve_status 	= encryption_decryption_fun('decrypt', $val['plan_approve_status_hidden']);
 
    // occupier present address - if same as occupier permanent address //
    	$same_as_address_occupier = $val['same_as_address_occupier'];

    if (!empty($val['same_as_address_occupier']) && ($val['same_as_address_occupier'] == 1)) {
        
		$country_oprsntadr              = $val['country_oprmntadr'];
		$passport_oprsntadr 	        = $val['passport_oprmntadr'];
		$pincodeoprsntadr        		= $val['pincodeoprmntadr'];
        $state_oprsntadr         		= $val['state_oprmntadr'];
        $district_oprsntadr     		= $val['district_oprmntadr'];
        $subdivision_oprsntadr   		= $val['subdivision_oprmntadr'];
        $areatype_oprsntadr      		= $val['areatype_oprmntadr'];
        $block_oprsntadr         		= $val['block_oprmntadr'];
        $panchayat_oprsntadr     		= $val['panchayat_oprmntadr'];
        $policestation_oprsntadr 		= $val['policestation_oprmntadr'];
        $postoffice_oprsntadr    		= $val['postoffice_oprmntadr'];
		$aadhaar_oprsntadr 	            = $val['user_aadhar_1'].'-'.$val['user_aadhar_2'].'-'.$val['user_aadhar_3'];
		$addrline_oprsntadr      		= $val['addrline_oprmntadr'];
		$passport_date_of_issue_oprsntadr 		= $val['passport_date_of_issue_oprmntadr'];
		$passport_date_of_expiry_oprsntadr 		= $val['passport_date_of_expiry_oprmntadr'];
		$street_name_oprsntadr 	  		= $val['street_name_oprmntadr'];
		$house_no_oprsntadr 	  		= $val['house_no_oprmntadr'];
		$police_station_oprsntadr 		= $val['police_station_oprmntadr'];
		
    } else {
		$country_oprsntadr       		= $val['country_oprsntadr'];
		$passport_oprsntadr 			= $val['passport_oprsntadr'];
		$pincodeoprsntadr        		= $val['pincodeoprsntadr'];
        $state_oprsntadr         		= $val['state_oprsntadr'];
        $district_oprsntadr      		= $val['district_oprsntadr'];
        $subdivision_oprsntadr   		= $val['subdivision_oprsntadr'];
        $areatype_oprsntadr      		= $val['areatype_oprsntadr'];
        $block_oprsntadr         		= $val['block_oprsntadr'];
        $panchayat_oprsntadr     		= $val['panchayat_oprsntadr'];
        $policestation_oprsntadr 		= $val['policestation_oprsntadr'];
        $postoffice_oprsntadr    		= $val['postoffice_oprsntadr'];
		$aadhaar_oprsntadr 				= $val['user_aadhar_4'].'-'.$val['user_aadhar_5'].'-'.$val['user_aadhar_6'];
		$addrline_oprsntadr     		= $val['addrline_oprsntadr'];
		$passport_date_of_issue_oprsntadr 		= $val['passport_date_of_issue_oprsntadr'];
		$passport_date_of_expiry_oprsntadr 		= $val['passport_date_of_expiry_oprsntadr'];
		$street_name_oprsntadr 	  		= $val['street_name_oprsntadr'];
		$house_no_oprsntadr 	  		= $val['house_no_oprsntadr'];
		$police_station_oprsntadr 		= $val['police_station_oprsntadr'];
    }
         //die;
		$occupier_details = array(
				'ownership_type'				=> $val['ownership_type'],
				'type_occupier' 				=> $val['type_occupier'],
				'name_occupier' 				=> $val['occupier_name'],
				'occupier_name_middle'			=> $val['occupier_name_middle'],
				'occupier_name_last'			=> $val['occupier_name_last'],
				'age_occupier'					=> $val['occupier_age'],
				'father_husband_name_occupier'	=> $val['father_husband_name_occupier'],
				'occupier_telephone'			=> $val['occupier_telephone'],
				'occupier_mobile'				=> $val['occupier_mobile'],
				'occupier_email_id'				=> $val['occupier_email_id'],
				'occupier_fax_no'				=> $val['occupier_fax_no'],
				
				'country_oprmntadr'				=> $val['country_oprmntadr'],
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
				'aadhaar_oprmntadr'				=> $val['user_aadhar_1'].'-'.$val['user_aadhar_2'].'-'.$val['user_aadhar_3'],
				'passport_oprmntadr' 			=> $val['passport_oprmntadr'],
				'passport_date_of_issue_oprmntadr' 	=> $val['passport_date_of_issue_oprmntadr'],
				'passport_date_of_expiry_oprmntadr' => $val['passport_date_of_expiry_oprmntadr'],
				'street_name_oprmntadr' 	    => $val['street_name_oprmntadr'],
				'house_no_oprmntadr' 		    => $val['house_no_oprmntadr'],
				'police_station_oprmntadr' 	    => $val['police_station_oprmntadr'],
				
				'country_oprsntadr'				=> $country_oprsntadr,
				'pincodeoprsntadr'			    => $pincodeoprsntadr,
				'state_oprsntadr'			    => $state_oprsntadr,
				'district_oprsntadr'	     	=> $district_oprsntadr,
				'subdivision_oprsntadr'			=> $subdivision_oprsntadr,
				'areatype_oprsntadr'			=> $areatype_oprsntadr,
				'block_oprsntadr'			    => $block_oprsntadr,
				'panchayat_oprsntadr'			=> $panchayat_oprsntadr,
				'policestation_oprsntadr'		=> $policestation_oprsntadr,
				'postoffice_oprsntadr'			=> $postoffice_oprsntadr,
				'addrline_oprsntadr'			=> $addrline_oprsntadr,
				'aadhaar_oprsntadr' 			=> $aadhaar_oprsntadr,
				'passport_oprsntadr' 			=> $passport_oprsntadr,
				'passport_date_of_issue_oprsntadr' 	=> $passport_date_of_issue_oprsntadr,
				'passport_date_of_expiry_oprsntadr' => $passport_date_of_expiry_oprsntadr,
				'street_name_oprsntadr' 			=> $street_name_oprsntadr,
				'house_no_oprsntadr' 				=> $house_no_oprsntadr,
				'police_station_oprsntadr' 			=> $police_station_oprsntadr,
				
				'add_year_occupier'				=> date('Y'),
				'occupier_service_id'			=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
				'application_occupier_id'		=> $application_id,
				'factory_type_id'				=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
				'application_reference_no'		=> $reference_no,
				'worker_plan_approval_status'	=> $plan_approve_status,
				'created_by'					=> $uid,
				'active_inactive_occupier'		=> 1,	
				'occupier_present_address_same' => $same_as_address_occupier,
		);		
		//echo "<pre>"; print_r($occupier_details); die;

		$queryabc = db_update('fa_occupier_details');
        $queryabc->fields($occupier_details);
        $queryabc->condition('application_occupier_id', $application_id, '=');
		$queryabc->condition('application_reference_no', $reference_no, '=');
        $queryabc->execute();

		drupal_set_message('Occupier Information has been saved successfully.');
		drupal_goto('applicant/caf_extn/details-worker-hp-extension/' . $val['serviceid_hidden'] . '/' . $val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']);
    //}
    $form_state['rebuild'] = true;
}

?> 