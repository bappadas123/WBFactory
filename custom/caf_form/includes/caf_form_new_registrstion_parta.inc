<?php
drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_new_registrstion_parta($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$flagmapp)
{
    global $base_root, $base_path;
    
    $form            = array();
	
	$service_id      = encryption_decryption_fun('decrypt', $serviceid);
	$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	$link_number = encryption_decryption_fun('decrypt', $linknumber);
	$flag_mapp = encryption_decryption_fun('decrypt', $flagmapp);
  
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
	$form['linknumber_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $linknumber
    );
	$form['flagmapp_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $flagmapp
    );
    $factory_name          = '';
    $factory_previous_name = '';
    $factory_location      = '';
    
    $factory_pincode       = '';
    $factory_state         = '';
    $factory_district      = '';
    $factory_subdivision   = '';
    $factory_areatype      = '';
    $factory_block         = '';
    $factory_panchayat     = '';
    $factory_policestation = '';
    $factory_postoffice    = '';
    $factory_addrline      = '';
    
    $office_pincode           = '';
    $office_state_off         = '';
    $office_district_off      = '';
    $office_subdivision_off   = '';
    $office_areatype_off      = '';
    $office_block_off         = '';
    $office_panchayat_off     = '';
    $office_policestation_off = '';
    $office_postoffice_off    = '';
    $office_addrline_off      = '';
    
	$comm_telephone     	  = '';
	$comm_mobile     	      = '';
	$comm_fax     	          = '';
	$comm_email     	      = '';
    
    $factory_pan              = '';
	$ownership_type	  = '';
	$occupier_type 		      = '';
    $occupier_nationality     = '';
    $occupier_aadhaar         = '';
    $occupier_passport        = '';
    $occupier_name            = '';
    $occupier_mobile          = '';
    $occupier_email_id        = '';
	$occupier_age    		  = '';
	$occupier_gurdian_name    = '';
	$occupier_fax_no          = '';
	$occupier_telephone       = '';

    $occupier_pincodeoprmntadr        = '';
    $occupier_state_oprmntadr         = '';
    $occupier_district_oprmntadr      = '';
    $occupier_subdivision_oprmntadr   = '';
    $occupier_areatype_oprmntadr      = '';
    $occupier_block_oprmntadr         = '';
    $occupier_panchayat_oprmntadr     = '';
    $occupier_policestation_oprmntadr = '';
    $occupier_postoffice_oprmntadr    = '';
    $occupier_addrline_oprmntadr      = '';
    
    $occupier_pincodeoprsntadr        = '';
    $occupier_state_oprsntadr         = '';
    $occupier_district_oprsntadr      = '';
    $occupier_subdivision_oprsntadr   = '';
    $occupier_areatype_oprsntadr      = '';
    $occupier_block_oprsntadr         = '';
    $occupier_panchayat_oprsntadr     = '';
    $occupier_policestation_oprsntadr = '';
    $occupier_postoffice_oprsntadr    = '';
    $occupier_addrline_oprsntadr      = '';
    
    $owner_name                   = '';
    $owner_pincodepremises        = '';
    $owner_state_premises         = '';
    $owner_district_premises      = '';
    $owner_subdivision_premises   = '';
    $owner_areatype_premises      = '';
    $owner_block_premises         = '';
    $owner_panchayat_premises     = '';
    $owner_policestation_premises = '';
    $owner_postoffice_premises    = '';
    $owner_addrline_premises      = '';

    //New field Added
    $trade_license_no = '';
    $date_of_amenability = '';
    $period_for_application  = '';
    $plan_approve_identification_number  = '';
    $factory_plan_approval_number  = '';
    $factory_reg_number  = '';
    $factory_reg_identification_number  = '';
    $reference_number  = '';
    $application_status  = '';
    $is_backlog  = '';

    
    if (!empty($application_id)) {
        $get_fa_cafa           = get_fa_cafa($application_id);
        //print_r($get_fa_cafa);die();
        $factory_name          = $get_fa_cafa['factory_name'];
        $factory_previous_name = $get_fa_cafa['factory_previous_name'];
        $factory_location      = $get_fa_cafa['factory_location'];
        $factory_pincode       = $get_fa_cafa['pincode'];
        $factory_state         = $get_fa_cafa['state'];
        $factory_district      = $get_fa_cafa['district'];
        $factory_subdivision   = $get_fa_cafa['subdivision'];
        $factory_areatype      = $get_fa_cafa['areatype'];
        $factory_block         = $get_fa_cafa['block'];
        $factory_panchayat     = $get_fa_cafa['panchayat'];
        $factory_policestation = $get_fa_cafa['policestation'];
        $factory_postoffice    = $get_fa_cafa['postoffice'];
        $factory_addrline      = $get_fa_cafa['addrline'];
        
        $office_pincode           = $get_fa_cafa['pincodeoff'];
        $office_state_off         = $get_fa_cafa['state_off'];
        $office_district_off      = $get_fa_cafa['district_off'];
        $office_subdivision_off   = $get_fa_cafa['subdivision_off'];
        $office_areatype_off      = $get_fa_cafa['areatype_off'];
        $office_block_off         = $get_fa_cafa['block_off'];
        $office_panchayat_off     = $get_fa_cafa['panchayat_off'];
        $office_policestation_off = $get_fa_cafa['policestation_off'];
        $office_postoffice_off    = $get_fa_cafa['postoffice_off'];
        $office_addrline_off      = $get_fa_cafa['addrline_off'];
       
        $comm_telephone     	  = $get_fa_cafa['comm_telephone'];
		$comm_mobile     	      = $get_fa_cafa['comm_mobile'];
		$comm_fax     	          = $get_fa_cafa['comm_fax'];
		$comm_email     	      = $get_fa_cafa['comm_email'];

		$factory_pan              = $get_fa_cafa['factory_pan'];
        $ownership_type	  = $get_fa_cafa['ownership_type'];
	    $occupier_type 		      = $get_fa_cafa['occupier_type'];
        $occupier_nationality     = $get_fa_cafa['occupier_nationality'];
        $occupier_aadhaar         = $get_fa_cafa['occupier_aadhaar'];
        $occupier_passport        = $get_fa_cafa['occupier_passport'];
        $occupier_name            = $get_fa_cafa['occupier_name'];
        $occupier_mobile          = $get_fa_cafa['occupier_mobile'];
        $occupier_email_id        = $get_fa_cafa['occupier_email_id'];
        $occupier_age             = $get_fa_cafa['occupier_age'];
        $occupier_gurdian_name    = $get_fa_cafa['occupier_gurdian_name'];
        $occupier_fax_no          = $get_fa_cafa['occupier_fax_no'];
		$occupier_telephone       = $get_fa_cafa['occupier_telephone'];
        
        $occupier_pincodeoprmntadr        = $get_fa_cafa['pincodeoprmntadr'];
        $occupier_state_oprmntadr         = $get_fa_cafa['state_oprmntadr'];
        $occupier_district_oprmntadr      = $get_fa_cafa['district_oprmntadr'];
        $occupier_subdivision_oprmntadr   = $get_fa_cafa['subdivision_oprmntadr'];
        $occupier_areatype_oprmntadr      = $get_fa_cafa['areatype_oprmntadr'];
        $occupier_block_oprmntadr         = $get_fa_cafa['block_oprmntadr'];
        $occupier_panchayat_oprmntadr     = $get_fa_cafa['panchayat_oprmntadr'];
        $occupier_policestation_oprmntadr = $get_fa_cafa['policestation_oprmntadr'];
        $occupier_postoffice_oprmntadr    = $get_fa_cafa['postoffice_oprmntadr'];
        $occupier_addrline_oprmntadr      = $get_fa_cafa['addrline_oprmntadr'];
        
        $occupier_pincodeoprsntadr        = $get_fa_cafa['pincodeoprsntadr'];
        $occupier_state_oprsntadr         = $get_fa_cafa['state_oprsntadr'];
        $occupier_district_oprsntadr      = $get_fa_cafa['district_oprsntadr'];
        $occupier_subdivision_oprsntadr   = $get_fa_cafa['subdivision_oprsntadr'];
        $occupier_areatype_oprsntadr      = $get_fa_cafa['areatype_oprsntadr'];
        $occupier_block_oprsntadr         = $get_fa_cafa['block_oprsntadr'];
        $occupier_panchayat_oprsntadr     = $get_fa_cafa['panchayat_oprsntadr'];
        $occupier_policestation_oprsntadr = $get_fa_cafa['policestation_oprsntadr'];
        $occupier_postoffice_oprsntadr    = $get_fa_cafa['postoffice_oprsntadr'];
        $occupier_addrline_oprsntadr      = $get_fa_cafa['addrline_oprsntadr'];
        
        $owner_name                   = $get_fa_cafa['owner_name'];
        $owner_pincodepremises        = $get_fa_cafa['pincodepremises'];
        $owner_state_premises         = $get_fa_cafa['state_premises'];
        $owner_district_premises      = $get_fa_cafa['district_premises'];
        $owner_subdivision_premises   = $get_fa_cafa['subdivision_premises'];
        $owner_areatype_premises      = $get_fa_cafa['areatype_premises'];
        $owner_block_premises         = $get_fa_cafa['block_premises'];
        $owner_panchayat_premises     = $get_fa_cafa['panchayat_premises'];
        $owner_policestation_premises = $get_fa_cafa['policestation_premises'];
        $owner_postoffice_premises    = $get_fa_cafa['postoffice_premises'];
        $owner_addrline_premises      = $get_fa_cafa['addrline_premises'];
        
        $reg_adress_same_factory       = $get_fa_cafa['reg_adress_same_factory'];
        //$communication_adress_same_factory    = $get_fa_cafa['communication_adress_same_factory'];
        $occupier_present_address_same = $get_fa_cafa['occupier_present_address_same'];

        //New Field Added

        $trade_license_no                       = $get_fa_cafa['trade_license_no'];
       
        $reference_number                       = $get_fa_cafa['reference_number'];
        $application_status                     = $get_fa_cafa['application_status'];
        $is_backlog                             = $get_fa_cafa['is_backlog'];
		$is_backlog                             = $get_fa_cafa['is_backlog'];
		$date_of_amenability                    = $get_fa_cafa['date_of_amenability'];
		$period_for_application                 = $get_fa_cafa['period_for_application'];
        
    }
    $form['application_status_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt', $application_status)
        
    );
	/********** Factory Information - Start **********/
    
    $form['header']            = array(
        '#markup' => t('<div class="content"><div class="sky-form"><h3><b>General Information 544445</b></h3>')
    );
    $form['factory_part_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Factory Information'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
    $form['factory_part_info']['factory_name'] = array(
        '#prefix' => '<div class="row"><div class="col-md-6 col-xs-12"><label class="input">',
        '#suffix' => '</label></div>',
        '#title' => t('Name of the factory'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#default_value' => $factory_name
        //'#description' => '<font color="#FF0000">Note:-As per Concents to establishment</font>'
    );
    $form['factory_part_info']['tread_license_no'] = array(
            '#prefix' => '<div class="col-md-6 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Trade License Number of factory'),
            '#type' => 'textfield',
            '#default_value' => $trade_license_no
        );
    
$form['factory_part_info']['factor_amenablity_date'] = array(
			 '#prefix' 		=> 	'<div class="row"><div class="col-md-6 col-xs-12"><label class="input">Date from which the primises is occupied or been taken into use as factory',
			 '#suffix' 		=> 	'</label></div>',
			  '#type' 		=> 	'textfield',
			  '#required' => TRUE,
			 '#attributes' 	=> 	array('class' => array('datepicker amenablity_date'),'placeholder' => '','readonly' => 'readonly'),
			 
			 '#default_value' => $date_of_amenability
	);
	$form['factory_part_info']['how_many_year'] 	= array(
			  '#prefix' 		=> '<div class="col-md-6 col-xs-12"><label class="input">State the period of license required',
			  '#suffix' 		=> '</label></div></div>',
			  '#type' 			=> 'textfield',
			  '#required' => TRUE, 
			  '#description'	=> t('<font color="#FF0000">(N.B.:-Maximun 15 years)</font>'),
			   '#attributes' 	=> 	array('class' => array('many_year'),'placeholder' => ''),
			   '#default_value' => $period_for_application
	  );
    
    
    
    /********** Factory Information - End **********/
	
	/********** Location of the factory - Start **********/
	
	$form['factory_part_a'] = array(
        '#type' => 'fieldset',
        '#title' => t('Location of the factory'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
    $form['factory_part_a']['firstRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    $form['factory_part_a']['pincode']       = array(
        '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input">',
        '#suffix' => '</label></div>',
        '#attributes' => array(
            'class' => array(
                ''
            ),
            'placeholder' => 'Pincode'
        ),
        '#autocomplete_path' => 'pinautocomplete',
        '#id' => 'pincode_autocomplete',
        '#maxlength' => 6,
        '#title' => t('Pincode'),
        '#default_value' => $factory_pincode,
        '#required' => TRUE,
        '#type' => 'textfield',
        '#ajax' => array(
            //'event'         => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_load',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        )
    );
    $value_pincode                           = isset($form_state['values']['pincode']) ? $form_state['values']['pincode'] : $factory_pincode;
    if (!empty($value_pincode)) {
        
        $query = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
            'districtname',
            'statename',
            'pincode',
            'district_code',
            'state_code',
            'po_name'
        ))->condition('p.pincode', trim($value_pincode), '=');
        
        $result = $query->execute();
        if ($result->rowcount() > 0) {
            $final       = $result->fetchAssoc();
            $pincode_v   = $value_pincode;
            $state_v     = $final['state_code'];
            $district_v  = $final['district_code'];
            $post_office = $final['po_name'];
        }
    }
    
    if (!empty($state_v)) {
        $form['factory_part_a']['state'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'state_name',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'State'
            ),
            '#disabled' => TRUE,
            '#options' => get_all_state($state_v),
            '#value' => !empty($state_v) ? $state_v : $factory_state,
            '#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
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
        $form['factory_part_a']['state'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'state_name',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'State',
                'readonly' => 'readonly'
            ),
            '#options' => array(
                '' => t('Select State')
            ),
            '#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
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
    
    $value_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : $factory_state;
    
    if (!empty($state_v)) {
        $form['factory_part_a']['district'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'district_name',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'District'
            ),
            '#options' => get_district_by_id($state_v),
            '#value' => !empty($district_v) ? $district_v : $factory_district,
            '#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
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
        $form['factory_part_a']['district'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'district_name',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'District'
            ),
            '#options' => array(
                '' => t('Select District')
            ),
            '#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
            '#suffix' => '</label></div></div>'
        );
    }
    
    $form['factory_part_a']['firstRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
    $value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : $factory_district;
    
    $form['factory_part_a']['secondRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    
    if (!empty($district_v) && !empty($state_v)) {
        
        $form['factory_part_a']['subdivision'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Sub Division'
            ),
            '#options' => common_custom_user_subdivisionlist_list_new($district_v),
            '#default_value' => $factory_subdivision,
            '#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
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
        
        $form['factory_part_a']['subdivision'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Sub Division'
            ),
            '#options' => array(
                '' => t('Select Sub-Division')
            ),
            '#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    $value_subdivision = isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : $factory_subdivision;
    
    if (!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
        $form['factory_part_a']['areatype'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Area Type'
            ),
            '#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
            '#default_value' => $factory_areatype,
            '#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
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
        $form['factory_part_a']['areatype'] = array(
            '#title' => '',
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
            '#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    
    $value_areatype = isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : $factory_areatype;
    
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
        
        $form['factory_part_a']['block'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'subdivision'
            ),
            '#options' => common_custom_user_block_list_new($value_subdivision, $value_areatype),
            '#default_value' => $factory_block,
            '#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select">' . $areatype_name . ' <span id=\'star\'>*</span>',
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
        $form['factory_part_a']['block'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'subdivision'
            ),
            '#options' => array(
                '0' => t('Select Block/Municipality/Corporation/SEZ/Notified Area')
            ),
            '#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select">Block/Municipality/Corporation/Notified Area/SEZ <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    
    $form['factory_part_a']['secondRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
    $form['factory_part_a']['thirdRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    $value_block                             = isset($form_state['values']['block']) ? $form_state['values']['block'] : $factory_block;
    
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
        
        
        $form['factory_part_a']['panchayat'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'panchayat'
            ),
            '#options' => common_custom_user_villward_list_new($value_block, $area_code),
            '#default_value' => $factory_panchayat,
            '#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select">' . $area_name . ' <span id=\'star\'>*</span>',
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
        $form['factory_part_a']['panchayat'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'panchayat'
            ),
            '#options' => array(
                '0' => t('Select Gram Panchayat/Ward/Sector/Notified Area')
            ),
            '#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select">Gram Panchayat/Ward/Sector <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    $value_panchayat = isset($form_state['values']['panchayat']) ? $form_state['values']['panchayat'] : $factory_panchayat;
    
    if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state) && !empty($value_panchayat)) {
        $form['factory_part_a']['policestation'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Police Station'
            ),
            '#options' => common_custom_user_ps_list_new($value_district),
            '#default_value' => $factory_policestation,
            '#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    } else {
        $form['factory_part_a']['policestation'] = array(
            '#title' => '',
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
            '#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    
    if (!empty($pincode_v)) {
        $form['factory_part_a']['postoffice'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Post Office'
            ),
            '#options' => common_custom_post_office_list_new($pincode_v),
            '#default_value' => $factory_postoffice,
            '#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    } else {
        $form['factory_part_a']['postoffice'] = array(
            '#title' => '',
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
            '#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    $form['factory_part_a']['addrline'] = array(
        '#title' => '',
        '#rows' => 3,
        '#type' => 'textarea',
        '#default_value' => $factory_addrline,
        '#attributes' => array(
            'class' => array(
                ''
            ),
            'placeholder' => 'Address Line'
        ),
        '#prefix' => '<div class="col-md-12"><label class="textarea">Address <span id=\'star\'>*</span>',
        '#suffix' => '</label></div>'
    );
    
    $form['factory_part_a']['thirdRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
        
    );
    
    /********** Location of the factory - End **********/
	
	/********** Address of the Registered office / Head office - Start **********/
	
    $form['factory_part_off']              = array(
        '#type' => 'fieldset',
        '#title' => t('Address of the Registered office / Head office'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    $form['factory_part_off']['addr_same'] = array(
        '#type' => 'checkbox',
        '#id' => 'same_factory_addr',
        '#default_value' => $reg_adress_same_factory,
        '#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_factory_address',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        ),
        '#title' => t('Same as Location of the factory'),
        '#prefix' => '<div class="col-md-12">',
        '#suffix' => '</div>'
    );
    
    $form['factory_part_off']['firstRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    
	$checkbox = isset($form_state['values']['addr_same']) ? $form_state['values']['addr_same'] : $reg_adress_same_factory;
    if ($checkbox == 1) {
        $form['factory_part_off']['pincodeoff']        = array(
            '#prefix' => '<div id="off_edit_emp_pincodeoff_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['state_off']         = array(
            '#prefix' => '<div id="off_edit_emp_state_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['district_off']      = array(
            '#prefix' => '<div id="off_edit_emp_district_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['subdivision_off']   = array(
            '#prefix' => '<div id="off_empsubdv_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['areatype_off']      = array(
            '#prefix' => '<div id="off_emp_areatype_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['block_off']         = array(
            '#prefix' => '<div id="off_empareatype_name_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['panchayat_off']     = array(
            '#prefix' => '<div id="off_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['policestation_off'] = array(
            '#prefix' => '<div id="off_empps_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['postoffice_off']    = array(
            '#prefix' => '<div id="off_post_office_div">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['addrline_off']      = array(
            '#prefix' => '<div id="off_addressline_div">',
            '#suffix' => '</div>'
        );
    }
    
    
    if ($checkbox == 0) {
        $form['factory_part_off']['pincodeoff'] = array(
            '#prefix' => '<div id="off_edit_emp_pincodeoff_replace"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode'
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' => 'pincode_autocomplete_off',
            '#maxlength' => 6,
            '#default_value' => $office_pincode,
            '#title' => t('Pincode'),
            '#required' => TRUE,
            '#type' => 'textfield',
            '#ajax' => array(
                //'event'         => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_off',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
        $value_pincode_off                      = isset($form_state['values']['pincodeoff']) ? $form_state['values']['pincodeoff'] : $office_pincode;
        if (!empty($value_pincode_off)) {
            
            $query_off = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_off), '=');
            
            $result_off = $query_off->execute();
            if ($result_off->rowcount() > 0) {
                $final_off       = $result_off->fetchAssoc();
                $pincode_v_off   = $value_pincode_off;
                $state_v_off     = $final_off['state_code'];
                $district_v_off  = $final_off['district_code'];
                $post_office_off = $final_off['po_name'];
            }
        }
        
        if (!empty($state_v_off)) {
            $form['factory_part_off']['state_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'state_name_off',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State'
                ),
                '#disabled' => TRUE,
                '#options' => get_all_state($state_v_off),
                '#default_value' => !empty($state_v_off) ? $state_v_off : $office_state_off,
                '#prefix' => '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['state_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'state_name_off',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State',
                    'readonly' => 'readonly'
                ),
                '#options' => array(
                    '' => t('Select State')
                ),
                '#prefix' => '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        }
        
        $value_state_off = isset($form_state['values']['state_off']) ? $form_state['values']['state_off'] : $office_state_off;
        
        if (!empty($state_v_off)) {
            $form['factory_part_off']['district_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'district_name_off',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District'
                ),
                '#options' => get_district_by_id($state_v_off),
                '#value' => !empty($district_v_off) ? $district_v_off : $office_district_off,
                '#prefix' => '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['district_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'district_name_off',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District'
                ),
                '#options' => array(
                    '' => t('Select District')
                ),
                '#prefix' => '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $form['factory_part_off']['firstRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $value_district_off = isset($form_state['values']['district_off']) ? $form_state['values']['district_off'] : $office_district_off;
        
        $form['factory_part_off']['secondRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
        
        if (!empty($district_v_off) && !empty($state_v_off)) {
            
            $form['factory_part_off']['subdivision_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division'
                ),
                '#options' => common_custom_user_subdivisionlist_list_new($district_v_off),
                '#default_value' => $office_subdivision_off,
                '#prefix' => '<div id="off_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            
            $form['factory_part_off']['subdivision_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division'
                ),
                '#options' => array(
                    '' => t('Select Sub-Division')
                ),
                '#prefix' => '<div id="off_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
        
        $value_subdivision_off = isset($form_state['values']['subdivision_off']) ? $form_state['values']['subdivision_off'] : $office_subdivision_off;
        
        if (!empty($value_district_off) && !empty($value_state_off) && !empty($value_subdivision_off)) {
            
            $form['factory_part_off']['areatype_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type'
                ),
                '#options' => common_custom_user_areatype_list_new($value_district_off, $value_subdivision_off),
                '#default_value' => $office_areatype_off,
                '#prefix' => '<div id="off_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['areatype_off'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="off_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $value_areatype_off = isset($form_state['values']['areatype_off']) ? $form_state['values']['areatype_off'] : $office_areatype_off;
        
        if (!empty($value_district_off) && !empty($value_state_off) && $value_subdivision_off != "" && !empty($value_areatype_off)) {
            
            if ($value_areatype_off == 'B') {
                $areatype_name_off = 'Block';
            } elseif ($value_areatype_off == 'M') {
                $areatype_name_off = 'Municipality';
            } elseif ($value_areatype_off == 'C') {
                $areatype_name_off = 'Corporation';
            } elseif ($value_areatype_off == 'S') {
                $areatype_name_off = 'SEZ';
            } elseif ($value_areatype_off == 'N') {
                $areatype_name_off = 'Notified Area';
            }
            
            $form['factory_part_off']['block_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision'
                ),
                '#options' => common_custom_user_block_list_new($value_subdivision_off, $value_areatype_off),
                '#default_value' => $office_block_off,
                '#prefix' => '<div id="off_empareatype_name_replace"><div class="col-md-4"><label class="select">' . $areatype_name_off . ' <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
            
        } else {
            $form['factory_part_off']['block_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision'
                ),
                '#options' => array(
                    '0' => t('Select Block/Municipality/Corporation/SEZ/Notified Area')
                    
                ),
                '#prefix' => '<div id="off_empareatype_name_replace"><div class="col-md-4"><label class="select">Block/Municipality/Corporation/Notified Area/SEZ <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $form['factory_part_off']['secondRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $form['factory_part_off']['thirdRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
        $value_block_off                           = isset($form_state['values']['block_off']) ? $form_state['values']['block_off'] : $office_block_off;
        
        if (!empty($value_district_off) && !empty($value_subdivision_off) && !empty($value_areatype_off) && !empty($value_block_off) && !empty($value_state_off)) {
            
            if ($value_areatype_off == 'B') {
                $area_name_off = 'Gram Panchayat';
                $area_code_off = 'V';
            } elseif ($value_areatype_off == 'M') {
                $area_name_off = 'Ward';
                
                $area_code_off = 'W';
            } elseif ($value_areatype_off == 'C') {
                $area_name_off = 'Ward';
                $area_code_off = 'C';
            } elseif ($value_areatype_off == 'S') {
                $area_name_off = 'Sector';
                $area_code_off = 'S';
            } elseif ($value_areatype_off == 'N') {
                $area_name_off = 'Notified Area';
                $area_code_off = 'N';
            }
            
            $form['factory_part_off']['panchayat_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => common_custom_user_villward_list_new($value_block_off, $area_code_off),
                '#default_value' => $office_panchayat_off,
                '#prefix' => '<div id="off_emp_vill_ward_replace"><div class="col-md-4"><label class="select">' . $area_name_off . ' <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['panchayat_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => array(
                    '0' => t('Select Gram Panchayat/Ward/Sector/Notified Area')
                ),
                '#prefix' => '<div id="off_emp_vill_ward_replace"><div class="col-md-4"><label class="select">Gram Panchayat/Ward/Sector <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_panchayat_off = isset($form_state['values']['panchayat_off']) ? $form_state['values']['panchayat_off'] : $office_panchayat_off;
        
        if (!empty($value_district_off) && !empty($value_subdivision_off) && !empty($value_areatype_off) && !empty($value_block_off) && !empty($value_state_off) && !empty($value_panchayat_off)) {
            
            $form['factory_part_off']['policestation_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station'
                ),
                '#options' => common_custom_user_ps_list_new($value_district_off),
                '#default_value' => $office_policestation_off,
                '#prefix' => '<div id="off_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_off']['policestation_off'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="off_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
        if (!empty($pincode_v_off)) {
            $form['factory_part_off']['postoffice_off'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office'
                ),
                '#options' => common_custom_post_office_list_new($pincode_v_off),
                '#default_value' => $office_postoffice_off,
                '#prefix' => '<div id="off_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_off']['postoffice_off'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="off_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
            
        }
        
        $form['factory_part_off']['addrline_off'] = array(
            '#title' => '',
            '#rows' => 3,
            '#type' => 'textarea',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line'
            ),
            '#default_value' => $office_addrline_off,
            '#prefix' => '<div id="off_addressline_div"><div class="col-md-12"><label class="textarea">Address <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>',
            '#description' => t('<font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font>')
        );
        
        $form['factory_part_off']['thirdRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
    }
	
    /********** Address of the Registered office / Head office - End **********/
    
	/********** Other Communication Details of factory - Start **********/
	
    $form['factory_other_comm_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Other Communication Details of Factory'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    $form['factory_other_comm_info']['comm_telephone'] = array(
        '#prefix' => '<div class="row"><div class="col-md-3"><label class="input">',
        '#suffix' => '</label></div>',
        '#title' => t('Telephone No.'),
        '#type' => 'textfield',
        '#default_value' => $comm_telephone
    );
	$form['factory_other_comm_info']['comm_mobile'] = array(
		'#prefix' => '<div class="col-md-3"><label class="input">',
		'#suffix' => '</label></div>',
		'#title' => t('Mobile No.'),
		'#type' => 'textfield',
		'#default_value' => $comm_mobile
    );
    $form['factory_other_comm_info']['comm_fax'] = array(
        '#prefix' => '<div class="col-md-3"><label class="input">',
        '#suffix' => '</label></div>',
        '#title' => t('Fax No.'),
        '#type' => 'textfield',
        '#default_value' => $comm_fax
    );
    
	$form['factory_other_comm_info']['comm_email'] = array(
		'#prefix' => '<div class="col-md-3"><label class="input">',
		'#suffix' => '</label></div></div>',
		'#title' => t('Email Id'),
		'#type' => 'textfield',
		'#default_value' => $comm_email
    );
    /********** Other Communication Details of factory - End **********/

    /********** PAN of Business Establishment / Factory / Company - Start **********/
	
	$form['factory_part_p']                = array(
        '#type' => 'fieldset',
        '#title' => t('PAN of Business Establishment / Factory / Company'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    $form['factory_part_p']['factory_pan'] = array(
        '#prefix' => '<div class="row"><div class="col-md-12 col-xs-12"><label class="input">',
        '#suffix' => '</label></div></div>',
        '#title' => t('PAN of the Business Establishment / Factory / Company under the Income Tax Act ,1961'),
        '#type' => 'textfield',
        '#default_value' => $factory_pan,
        '#required' => TRUE
    );
    
    /********** PAN of Business Establishment / Factory / Company - End **********/
	
	/********** Details of Occupier - Start **********/
    
    $form['factory_part_c']                         = array(
        '#type' => 'fieldset',
        '#title' => t('Details of Occupier & Permanent Address'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    $ownershiptype  = array(
        "0" => "Select",
		"dir_firm" => "Directorship Firm",
        "par_firm" => "Partnership Firm",
		"pro_firm" => "Proprietorship Firm",
        "govt" => "Govt.",
		"psu" => "PSU",
		"others" => "Others",
    );
	
    $form['factory_part_c']['ownership_type'] = array(
        '#prefix' => '<div class="row"><div class="col-md-4 col-xs-12"><label class="select">',
        '#suffix' => '</label></div>',
        '#title' => t('Type of Ownership'),
        '#options' => $ownershiptype,
        '#type' => 'select',
        '#default_value'        => !empty($ownership_type) ? $ownership_type :'',
        '#required' => TRUE,
		'#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_occupier_type',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        )
    );
	
    $form['factory_part_c']['occupier_type'] = array(
        '#prefix' => '<div id="occupier_type_id"><div class="col-md-8 col-xs-12"><label class="input">',
        '#suffix' => '</label></div></div>',
    );
		
	/*$form['factory_part_c']['din_director'] = array(
		'#prefix' => '<div id="din_director_id"><div class="col-md-4 col-xs-12"><label class="input">',
		'#suffix' => '</label></div></div>',
	); */

	$value_ownership_type   = isset($form_state['values']['ownership_type']) ? $form_state['values']['ownership_type'] : $ownership_type;
	
	if($value_ownership_type == 'dir_firm')
	{
		$form['factory_part_c']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#title' => t('Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Director',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		); 
		/*$form['factory_part_c']['din_director'] = array(
			'#prefix' => '<div id="din_director_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#title' => t('Occupier DIN'),
			'#type' => 'textfield',
		); */
	} elseif($value_ownership_type == 'par_firm')
	{
		$form['factory_part_c']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#title' => t('Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Partner',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		);
		/*$form['factory_part_c']['din_director_blank'] = array(
			'#prefix' => '<div id="din_director_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#type' => 'hidden',
		); */

	} elseif($value_ownership_type == 'pro_firm')
	{
		$form['factory_part_c']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#title' => t('Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Proprietor',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		);
        /*$form['factory_part_c']['din_director_blank'] = array(
			'#prefix' => '<div id="din_director_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#type' => 'hidden',
		);*/ 
	} elseif($value_ownership_type == 'govt' || $value_ownership_type == 'psu' || $value_ownership_type == 'others')
	{
		$form['factory_part_c']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#title' => t('Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Nominated',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		);
        /*$form['factory_part_c']['din_director_blank'] = array(
			'#prefix' => '<div id="din_director_id"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' => '</label></div></div>',
			'#type' => 'hidden',
		);*/ 
	}
	
	$nationality_list     = array(
        "0" => "Select",
		"Indian" => "Indian",
        "Other" => "Other"
    );
    $form['factory_part_c']['occupier_nationality'] = array(
        '#prefix' => '<div class="col-md-4 col-xs-12"><label class="select">',
        '#suffix' => '</label></div>',
        '#title' => t('Nationality'),
        
        '#options' => $nationality_list,
        '#type' => 'select',
        '#default_value'        => !empty($occupier_nationality) ? $occupier_nationality :'',
        '#required' => TRUE,
        '#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_nationality',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        )
    );
    $form['factory_part_c']['occupier_aadhaar']     = array(
        '#prefix' => '<div id="ld_show_aadhaar">',
        '#suffix' => '</div>'
    );
	$form['factory_part_c']['occupier_passport']     = array(
        '#prefix' => '<div id="ld_show_passport">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['occupier_name']        = array(
        '#prefix' => '<div id="occupier_name_id">',
        '#suffix' => '</div>'
    );
		$form['factory_part_c']['occupier_age']        = array(
        '#prefix' => '<div id="occupier_age_id">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['occupier_gurdian_name']        = array(
        '#prefix' => '<div id="occupier_gurdian_name_id">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['occupier_telephone']        = array(
        '#prefix' => '<div id="occupier_telephone_id">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['occupier_fax_no']        = array(
        '#prefix' => '<div id="occupier_fax_no_id">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['occupier_mobile']      = array(
        '#prefix' => '<div id="occupier_mobile_id">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['occupier_email_id']    = array(
        '#prefix' => '<div id="occupier_emailid">',
        '#suffix' => '</div>'
    );
    
    $form['factory_part_c']['pincodeoprmntadr']        = array(
        '#prefix' => '<div id="pincodeoprmntadr_id">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['state_oprmntadr']       = array(
        '#prefix' => '<div id="oprmntadr_edit_emp_state_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['district_oprmntadr']    = array(
        '#prefix' => '<div id="oprmntadr_edit_emp_district_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['subdivision_oprmntadr'] = array(
        '#prefix' => '<div id="oprmntadr_empsubdv_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['areatype_oprmntadr']    = array(
        '#prefix' => '<div id="oprmntadr_emp_areatype_replace">',
        '#suffix' => '</div>'
    );
    
    $form['factory_part_c']['block_oprmntadr'] = array(
        '#prefix' => '<div id="oprmntadr_empareatype_name_replace">',
        '#suffix' => '</div>'
    );
    
    $form['factory_part_c']['panchayat_oprmntadr']     = array(
        '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['policestation_oprmntadr'] = array(
        '#prefix' => '<div id="oprmntadr_empps_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['postoffice_oprmntadr']    = array(
        '#prefix' => '<div id="oprmntadr_post_office_div">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['addrline_oprmntadr']      = array(
        '#prefix' => '<div id="addrline_oprmntadr_div">',
        '#suffix' => '</div>'
    );
    $value_nationality   = isset($form_state['values']['occupier_nationality']) ? $form_state['values']['occupier_nationality'] : $occupier_nationality;
    if ($value_nationality == "Indian") {
        $form['factory_part_c']['occupier_aadhaar']   = array(
            '#prefix' => '<div id="ld_show_aadhaar"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Aadhaar Number'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_aadhaar) ? $occupier_aadhaar :'',
            '#required' => TRUE
        );
        $form['factory_part_c']['occupier_name']      = array(
            '#prefix' => '<div id="occupier_name_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Name'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_name) ? $occupier_name :'',
            '#required' => TRUE
        );
		$form['factory_part_c']['occupier_age']    = array(
            '#prefix' => '<div id="occupier_age_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Age'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_age) ? $occupier_age :'',
        );
        $form['factory_part_c']['occupier_gurdian_name']  = array(
            '#prefix' => '<div id="occupier_gurdian_name_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Father\'s/Husband\'s name'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_gurdian_name) ? $occupier_gurdian_name :'',
        );
        $form['factory_part_c']['occupier_telephone']  = array(
            '#prefix' => '<div id="occupier_telephone_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Telephone Number'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_telephone) ? $occupier_telephone :'',
        );
        $form['factory_part_c']['occupier_mobile']    = array(
            '#prefix' => '<div id="occupier_mobile_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Registered Mobile Number'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_mobile) ? $occupier_mobile :'',
            '#required' => TRUE
        );
        $form['factory_part_c']['occupier_email_id']  = array(
            '#prefix' => '<div id="occupier_emailid"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Email Id'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_email_id) ? $occupier_email_id :'',
            '#required' => TRUE
        );
		$form['factory_part_c']['occupier_fax_no']    = array(
            '#prefix' => '<div id="occupier_fax_no_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Fax No.'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_fax_no) ? $occupier_fax_no :'',
        );
        $form['factory_part_c']['addrline_oprmntadr'] = array(
            '#prefix' => '<div id = "addrline_oprmntadr_div"><div class="col-md-12 col-xs-12"><label class="textarea">Address <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>',
            '#title' => '',
            '#rows' => 3,
            '#type' => 'textarea',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line'
            ),
            '#default_value' => $occupier_addrline_oprmntadr
            
            
        );
        $form['factory_part_c']['pincodeoprmntadr']     = array(
            '#prefix' => '<div id="pincodeoprmntadr_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode'
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' => 'pincode_autocomplete_oprmntadr',
            '#maxlength' => 6,
            '#title' => t('Pincode'),
			'#default_value'  => !empty($occupier_pincodeoprmntadr) ? $occupier_pincodeoprmntadr    :'',
            '#required' => TRUE,
            '#type' => 'textfield',
            '#ajax' => array(
                //'event'         => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_oprmntadr',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
        
        $value_pincode_oprmntadr = isset($form_state['values']['pincodeoprmntadr']) ? $form_state['values']['pincodeoprmntadr'] : $occupier_pincodeoprmntadr;
        if (!empty($value_pincode_oprmntadr)) {
            
            $query_oprmntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_oprmntadr), '=');
            
            $result_oprmntadr = $query_oprmntadr->execute();
            if ($result_oprmntadr->rowcount() > 0) {
                $final_oprmntadr       = $result_oprmntadr->fetchAssoc();
                $pincode_v_oprmntadr   = $value_pincode_oprmntadr;
                $state_v_oprmntadr     = $final_oprmntadr['state_code'];
                $district_v_oprmntadr  = $final_oprmntadr['district_code'];
                $post_office_oprmntadr = $final_oprmntadr['po_name'];
            }
            
        }
        if (!empty($state_v_oprmntadr)) {
            $form['factory_part_c']['state_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'state_name_oprmntadr',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State'
                ),
                '#disabled' => TRUE,
                '#options' => get_all_state($state_v_oprmntadr),
                '#value' => !empty($state_v_oprmntadr) ? $state_v_oprmntadr : $occupier_state_oprmntadr,
                '#prefix' => '<div id="oprmntadr_edit_emp_state_replace"><div class="col-md-4 col-xs-12"><label class="select">State',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_c']['state_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'state_name_oprmntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State',
                    'readonly' => 'readonly'
                ),
                '#options' => array(
                    '' => t('Select State')
                ),
                '#prefix' => '<div id="oprmntadr_edit_emp_state_replace"><div class="col-md-4 col-xs-12"><label class="select">State',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        }
        $value_state_oprmntadr = isset($form_state['values']['state']) ? $form_state['values']['state_oprmntadr'] : $occupier_state_oprmntadr;
        if (!empty($state_v_oprmntadr)) {
            $form['factory_part_c']['district_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'district_name_oprmntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District'
                ),
                '#options' => get_district_by_id($state_v_oprmntadr),
                '#value' => !empty($district_v_oprmntadr) ? $district_v_oprmntadr : $occupier_district_oprmntadr,
                '#prefix' => '<div id="oprmntadr_edit_emp_district_replace"><div class="col-md-4 col-xs-12"><label class="select">District',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
            
        } else {
            $form['factory_part_c']['district_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'district_name_oprmntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District'
                ),
                '#options' => array(
                    '' => t('Select District')
                ),
                '#prefix' => '<div id="oprmntadr_edit_emp_district_replace"><div class="col-md-4 col-xs-12"><label class="select">District',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_district_oprmntadr = isset($form_state['values']['district_oprmntadr']) ? $form_state['values']['district_oprmntadr'] : $occupier_district_oprmntadr;
        
        if (!empty($district_v_oprmntadr) && !empty($state_v_oprmntadr)) {
            
            $form['factory_part_c']['subdivision_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division'
                ),
                '#options' => common_custom_user_subdivisionlist_list_new($district_v_oprmntadr),
                '#default_value' => $occupier_subdivision_oprmntadr,
                '#prefix' => '<div id="oprmntadr_empsubdv_replace"><div class="col-md-4 col-xs-12"><label class="select">Sub-Division <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            
            $form['factory_part_c']['subdivision_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division'
                ),
                '#options' => array(
                    '' => t('Select Sub-Division')
                ),
                '#prefix' => '<div id="oprmntadr_empsubdv_replace"><div class="col-md-4 col-xs-12"><label class="select">Sub-Division <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_subdivision_oprmntadr = isset($form_state['values']['subdivision_oprmntadr']) ? $form_state['values']['subdivision_oprmntadr'] : $occupier_subdivision_oprmntadr;
        if (!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr)) {
            $form['factory_part_c']['areatype_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type'
                ),
                '#options' => common_custom_user_areatype_list_new($value_district_oprmntadr, $value_subdivision_oprmntadr),
                '#default_value' => $occupier_areatype_oprmntadr,
                '#prefix' => '<div id="oprmntadr_emp_areatype_replace"><div class="col-md-4 col-xs-12"><label class="select">Area Type <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_c']['areatype_oprmntadr'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="oprmntadr_emp_areatype_replace"><div class="col-md-4 col-xs-12"><label class="select">Area Type <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
            
        }
        $value_areatype_oprmntadr = isset($form_state['values']['areatype_oprmntadr']) ? $form_state['values']['areatype_oprmntadr'] : $occupier_areatype_oprmntadr;
        
        if (!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && $value_subdivision_oprmntadr != "" && !empty($value_areatype_oprmntadr)) {
            
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
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision'
                ),
                '#options' => common_custom_user_block_list_new($value_subdivision_oprmntadr, $value_areatype_oprmntadr),
                '#default_value' => $occupier_block_oprmntadr,
                '#prefix' => '<div id="oprmntadr_empareatype_name_replace"><div class="col-md-4 col-xs-12"><label class="select">' . $areatype_name_oprmntadr . ' <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
            
        } else {
            
            $form['factory_part_c']['block_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Block/Municipality/Corporation/Notified Area/SEZ'
                ),
                '#options' => array(
                    '0' => t('select Block/Municipality/Corporation/Notified Area/SEZe')
                ),
                '#prefix' => '<div id="oprmntadr_empareatype_name_replace"><div class="col-md-4 col-xs-12"><label class="select">Block/Municipality/Corporation/Notified Area/SEZ <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
            
            
        }
        $value_block_oprmntadr = isset($form_state['values']['block_oprmntadr']) ? $form_state['values']['block_oprmntadr'] : $occupier_block_oprmntadr;
        
        if (!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr) && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr)) {
            
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
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => get_full_villward($value_block_oprmntadr, $area_code_oprmntadr),
                '#default_value' => $occupier_panchayat_oprmntadr,
                '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select"> ' . $area_name_oprmntadr . ' <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_c']['panchayat_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => array(
                    '0' => t('Select Gram Panchayat/Ward/Sector/Notified Area')
                ),
                '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select">Gram Panchayat/Ward/Sector <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_panchayat_oprmntadr1 = isset($form_state['values']['panchayat_oprmntadr']) ? $form_state['values']['panchayat_oprmntadr'] : '';
        
        
        
        if (!empty($value_district_oprmntadr)) {
            
            $form['factory_part_c']['policestation_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office'
                ),
                '#options' => common_custom_user_ps_list_new($value_district_oprmntadr),
                '#default_value' => $occupier_policestation_oprmntadr,
                '#prefix' => '<div id="oprmntadr_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
            
            
            
        } else {
            $form['factory_part_c']['policestation_oprmntadr'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="oprmntadr_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        if (!empty($value_pincode_oprmntadr)) {
            $form['factory_part_c']['postoffice_oprmntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office'
                ),
                '#options' => common_custom_post_office_list_new($value_pincode_oprmntadr),
                '#default_value' => $occupier_postoffice_oprmntadr,
                '#prefix' => '<div id="oprmntadr_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_c']['postoffice_oprmntadr'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="oprmntadr_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
            
        }
    }
    if ($value_nationality == "Other") {
        /*$form['factory_part_c']['occupier_aadhaar']  = array(
            '#prefix' => '<div id="ld_show_aadhaar">',
            '#suffix' => '</div>'
        );*/
		
        $form['factory_part_c']['occupier_passport'] = array(
            '#prefix' => '<div id="ld_show_passport"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Passport Number'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_passport) ? $occupier_passport :'',
            '#required' => TRUE
        );
        $form['factory_part_c']['occupier_name']           = array(
            '#prefix' => '<div id="occupier_name_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Name'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_name) ? $occupier_name :'',
            '#required' => TRUE
        );
		$form['factory_part_c']['occupier_age']    = array(
            '#prefix' => '<div id="occupier_age_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Age'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_age) ? $occupier_age :'',
        );
        $form['factory_part_c']['occupier_gurdian_name']  = array(
            '#prefix' => '<div id="occupier_gurdian_name_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Father\'s/Husband\'s name'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_gurdian_name) ? $occupier_gurdian_name :'',
        );
        $form['factory_part_c']['occupier_telephone']  = array(
            '#prefix' => '<div id="occupier_telephone_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Telephone Number'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_telephone) ? $occupier_telephone :'',
        );
        $form['factory_part_c']['occupier_mobile']         = array(
            '#prefix' => '<div id="occupier_mobile_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Mobile Number'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_mobile) ? $occupier_mobile :'',
            '#required' => TRUE
        );
        $form['factory_part_c']['occupier_email_id']       = array(
            '#prefix' => '<div id="occupier_emailid"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Email id'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_email_id) ? $occupier_email_id :'',
            '#required' => TRUE
        );
		$form['factory_part_c']['occupier_fax_no']    = array(
            '#prefix' => '<div id="occupier_fax_no_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('Fax No.'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_fax_no) ? $occupier_fax_no :'',
        );
		
        $form['factory_part_c']['addrline_oprmntadr']      = array(
            '#prefix' => '<div id = "addrline_oprmntadr_div"><div class="col-md-12 col-xs-12"><label class="textarea">Address <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>',
            '#title' => '',
            '#rows' => 3,
            '#type' => 'textarea',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line'
            ),
            '#default_value' => $occupier_addrline_oprmntadr
            
            
        );
        $form['factory_part_c']['pincodeoprmntadr']          = array(
            '#prefix' => '<div id="pincodeoprmntadr_id">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['state_oprmntadr']         = array(
            '#prefix' => '<div id="oprmntadr_edit_emp_state_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['district_oprmntadr']      = array(
            '#prefix' => '<div id="oprmntadr_edit_emp_district_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['subdivision_oprmntadr']   = array(
            '#prefix' => '<div id="oprmntadr_empsubdv_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['areatype_oprmntadr']      = array(
            '#prefix' => '<div id="oprmntadr_emp_areatype_replace"',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['block_oprmntadr']         = array(
            '#prefix' => '<div id="oprmntadr_empareatype_name_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['panchayat_oprmntadr']     = array(
            '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['panchayat_oprmntadr']     = array(
            '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['policestation_oprmntadr'] = array(
            '#prefix' => '<div id="oprmntadr_empps_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['postoffice_oprmntadr']    = array(
            '#prefix' => '<div id="oprmntadr_post_office_div">',
            '#suffix' => '</div>'
        );
        
    }
    $form['factory_part_c']['thirdRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
	/********** Details of Occupier - End **********/
	 
    /********** Occupier Present Address - Start **********/
	
   
    $form['factory_part_oprsntadr'] = array(
        '#type' => 'fieldset',
        '#title' => t('Occupier Present Address'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	$form['factory_part_oprsntadr']['markup_div'] = array(
        '#prefix' =>'<div class="row">' ,
		'#suffix' => '',
       
    );
	 $form['factory_part_oprsntadr']['same_as_address_occupier'] = array(
        '#type' => 'checkbox',
        '#default_value' => !empty($occupier_present_address_same)?$occupier_present_address_same:0,
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
	 
	 if($checkbox_premanent_occupier == 1) {
        $form['factory_part_oprsntadr']['pincodeoprsntadr']      = array(
            '#prefix' => '<div id ="pincodeoprsntadr_id">',
            '#suffix' => '</div>'
        );
		
        $form['factory_part_oprsntadr']['state_oprsntadr']       = array(
            
            '#prefix' => '<div id="oprsntadr_edit_emp_state_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['district_oprsntadr']    = array(
            
            '#prefix' => '<div id="oprsntadr_edit_emp_district_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
            
            '#prefix' => '<div id="oprsntadr_empsubdv_replace">',
            '#suffix' => '</div>'
            
        );
        $form['factory_part_oprsntadr']['areatype_oprsntadr']    = array(
            
            '#prefix' => '<div id="oprsntadr_emp_areatype_replace">',
            '#suffix' => '</div>'
        );
        
        $form['factory_part_oprsntadr']['block_oprsntadr']         = array(
            
            '#prefix' => '<div id="oprsntadr_empareatype_name_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['panchayat_oprsntadr']     = array(
            
            '#prefix' => '<div id="oprsntadr_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
            
            '#prefix' => '<div id="oprsntadr_empps_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['postoffice_oprsntadr']    = array(
            
            '#prefix' => '<div id="oprsntadr_post_office_div">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['addrline_oprsntadr']      = array(
            
            '#prefix' => '<div id = "addrline_oprsntadr_id">',
            '#suffix' => '</div>'
        );
    }
	 if($checkbox_premanent_occupier == 0) {
		 
		  $form['factory_part_oprsntadr']['pincodeoprsntadr'] = array(
            '#prefix' => '<div id="pincodeoprsntadr_id"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#default_value'  => !empty($occupier_pincodeoprsntadr) ? $occupier_pincodeoprsntadr :'',
			'#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode'
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' => 'pincode_autocomplete_oprsntadr',
            '#maxlength' => 6,
            '#title' => t('Pincode'),
            '#required' => TRUE,
            '#type' => 'textfield',
            '#ajax' => array(
                //'event'         => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_oprsntadr',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
		$value_pincode_oprsntadr   = isset($form_state['values']['pincodeoprsntadr']) ? $form_state['values']['pincodeoprsntadr'] : $occupier_pincodeoprsntadr;
        if (!empty($value_pincode_oprsntadr)) {
            
            $query_oprsntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_oprsntadr), '=');
            
            $result_oprsntadr = $query_oprsntadr->execute();
            if ($result_oprsntadr->rowcount() > 0) {
                $final_oprsntadr       = $result_oprsntadr->fetchAssoc();
                $pincode_v_oprsntadr   = $value_pincode_oprsntadr;
                $state_v_oprsntadr     = $final_oprsntadr['state_code'];
                $district_v_oprsntadr  = $final_oprsntadr['district_code'];
                $post_office_oprsntadr = $final_oprsntadr['po_name'];
            }
        }
		
		if (!empty($state_v_oprsntadr)) {
            $form['factory_part_oprsntadr']['state_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'state_name_oprsntadr',
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State'
                ),
                '#disabled' => TRUE,
                '#options' => get_all_state($state_v_oprsntadr),
                '#value' => !empty($state_v_oprsntadr) ? $state_v_oprsntadr : $occupier_state_oprsntadr,
                '#prefix' => '<div id="oprsntadr_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['state_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'state_name_oprsntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State',
                    'readonly' => 'readonly'
                ),
                '#options' => array(
                    '' => t('Select State')
                ),
                '#prefix' => '<div id="oprsntadr_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        }
        
        $value_state_oprsntadr = isset($form_state['values']['state_oprsntadr']) ? $form_state['values']['state_oprsntadr'] : $occupier_state_oprsntadr;
		
		if (!empty($state_v_oprsntadr)) {
            $form['factory_part_oprsntadr']['district_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'district_name_oprsntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District'
                ),
                '#options' => get_district_by_id($state_v_oprsntadr),
                '#value' => !empty($district_v_oprsntadr) ? $district_v_oprsntadr : $occupier_district_oprsntadr,
                '#prefix' => '<div id="oprsntadr_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['district_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#id' => 'district_name_oprsntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District'
                ),
                '#options' => array(
                    '' => t('Select District')
                ),
                '#prefix' => '<div id="oprsntadr_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
                '#suffix' => '</label></div></div>'
            );
        }
		
		$form['factory_part_oprsntadr']['firstRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $value_district_oprsntadr = isset($form_state['values']['district_oprsntadr']) ? $form_state['values']['district_oprsntadr'] : $occupier_district_oprsntadr;
		
		$form['factory_part_oprsntadr']['secondRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
		
		if (!empty($district_v_oprsntadr) && !empty($state_v_oprsntadr)) {
            
            $form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#default_value'  => $occupier_subdivision_oprsntadr,
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division'
                ),
                '#options' => common_custom_user_subdivisionlist_list_new($district_v_oprsntadr),
                '#prefix' => '<div id="oprsntadr_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            
            $form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division'
                ),
                '#options' => array(
                    '' => t('Select Sub-Division')
                ),
                '#prefix' => '<div id="oprsntadr_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
		$value_subdivision_oprsntadr = isset($form_state['values']['subdivision_oprsntadr']) ? $form_state['values']['subdivision_oprsntadr'] : $occupier_subdivision_oprsntadr;
		if (!empty($value_district_oprsntadr) && !empty($value_state_oprsntadr) && !empty($value_subdivision_oprsntadr)) {
            $form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#default_value'  => $occupier_areatype_oprsntadr,
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type'
                ),
                '#options' => common_custom_user_areatype_list_new($value_district_oprsntadr, $value_subdivision_oprsntadr),
                '#prefix' => '<div id="oprsntadr_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="oprsntadr_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $value_areatype_oprsntadr = isset($form_state['values']['areatype_oprsntadr']) ? $form_state['values']['areatype_oprsntadr'] : $occupier_areatype_oprsntadr;
		
		if (!empty($value_district_oprsntadr) && !empty($value_state_oprsntadr) && $value_subdivision_oprsntadr != "" && !empty($value_areatype_oprsntadr)) {
            
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
                '#title' => '',
                '#type' => 'select',
                
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision'
                ),
                '#options' => common_custom_user_block_list_new($value_subdivision_oprsntadr, $value_areatype_oprsntadr),
                '#default_value'  => $occupier_block_oprsntadr,
				'#prefix' => '<div id="oprsntadr_empareatype_name_replace"><div class="col-md-4"><label class="select">' . $areatype_name_oprsntadr . ' <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
        } else {
            $form['factory_part_oprsntadr']['block_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision'
                ),
                '#options' => array(
                    '0' => t('Select Block/Municipality/Corporation/SEZ/Notified Area')
                ),
                '#prefix' => '<div id="oprsntadr_empareatype_name_replace"><div class="col-md-4"><label class="select">Block/Municipality/Corporation/Notified Area/SEZ <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $form['factory_part_oprsntadr']['secondRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $form['factory_part_oprsntadr']['thirdRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
        $value_block_oprsntadr    = isset($form_state['values']['block_oprsntadr']) ? $form_state['values']['block_oprsntadr'] : $occupier_block_oprsntadr;
        
        if (!empty($value_district_oprsntadr) && !empty($value_subdivision_oprsntadr) && !empty($value_areatype_oprsntadr) && !empty($value_block_oprsntadr) && !empty($value_state_oprsntadr)) {
            
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
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => common_custom_user_villward_list_new($value_block_oprsntadr, $area_code_oprsntadr),
                '#default_value'  => $occupier_panchayat_oprsntadr,
				'#prefix' => '<div id="oprsntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select">' . $area_name_oprsntadr . ' <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['panchayat_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => array(
                    '0' => t('Select Gram Panchayat/Ward/Sector/Notified Area')
                ),
                '#prefix' => '<div id="oprsntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select">Gram Panchayat/Ward/Sector <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_panchayat_oprsntadr = isset($form_state['values']['panchayat_oprsntadr']) ? $form_state['values']['panchayat_oprsntadr'] : $occupier_panchayat_oprsntadr;
        
        if (!empty($value_district_oprsntadr) && !empty($value_subdivision_oprsntadr) && !empty($value_areatype_oprsntadr) && !empty($value_block_oprsntadr) && !empty($value_state_oprsntadr) && !empty($value_panchayat_oprsntadr)) {
            $form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station'
                ),
                '#options' => common_custom_user_ps_list_new($value_district_oprsntadr),
                '#default_value'  => $occupier_policestation_oprsntadr,
				'#prefix' => '<div id="oprsntadr_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="oprsntadr_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
        }
        
        if (!empty($pincode_v_oprsntadr)) {
            $form['factory_part_oprsntadr']['postoffice_oprsntadr'] = array(
                '#title' => '',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office'
                ),
                '#options' => common_custom_post_office_list_new($pincode_v_oprsntadr),
                '#default_value'  => $occupier_postoffice_oprsntadr,
				'#prefix' => '<div id="oprsntadr_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
			
        } else {
            $form['factory_part_oprsntadr']['postoffice_oprsntadr'] = array(
                '#title' => '',
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
                '#prefix' => '<div id="oprsntadr_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
                '#suffix' => '</label></div></div>'
            );
            
        }
        
        $form['factory_part_oprsntadr']['addrline_oprsntadr'] = array(
            '#title' => '',
            '#rows' => 3,
            '#type' => 'textarea',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line'
            ),
            '#default_value' => $occupier_addrline_oprsntadr,
			'#prefix' => '<div id = "addrline_oprsntadr_id"><div class="col-md-12"><label class="textarea">Address <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
	 }
   
    $form['factory_part_oprsntadr']['thirdRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
   
	/********** Occupier Present Address - End **********/    
    
    /********** Details of owner of the premises occupied as a factory - Start **********/
    
    $form['factory_part_premises'] = array(
        '#type' => 'fieldset',
        '#title' => t('Details of owner of the premises occupied as a factory'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
    
    $form['factory_part_premises']['firstRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    $form['factory_part_premises']['owner_name']    = array(
        '#prefix' => '<div class="col-md-12 col-xs-12"><label class="input">',
        '#suffix' => '</label></div>',
        '#title' => t('Name of the owner'),
        '#type' => 'textfield',
        '#default_value' => $owner_name,
        '#required' => TRUE
    );
    
    $form['factory_part_premises']['pincodepremises'] = array(
        '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input">',
        '#suffix' => '</label></div>',
        '#attributes' => array(
            'class' => array(
                ''
            ),
            'placeholder' => 'Pincode',
            'autocomplete' => 'off'
        ),
        '#autocomplete_path' => 'pinautocomplete',
        '#id' => 'pincode_autocomplete_premises',
        '#maxlength' => 6,
        '#title' => t('Pincode'),
        '#default_value' => $owner_pincodepremises,
        '#required' => TRUE,
        '#type' => 'textfield',
        '#ajax' => array(
            //'event'         => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_load_premises',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        )
    );
    
    
    $value_pincode_premises = isset($form_state['values']['pincodepremises']) ? $form_state['values']['pincodepremises'] : $owner_pincodepremises;
    if (!empty($value_pincode_premises)) {
        
        $query_premises = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
            'districtname',
            'statename',
            'pincode',
            'district_code',
            'state_code',
            'po_name'
        ))->condition('p.pincode', trim($value_pincode_premises), '=');
        
        $result_premises = $query_premises->execute();
        if ($result_premises->rowcount() > 0) {
            $final_premises       = $result_premises->fetchAssoc();
            $pincode_v_premises   = $value_pincode_premises;
            $state_v_premises     = $final_premises['state_code'];
            $district_v_premises  = $final_premises['district_code'];
            $post_office_premises = $final_premises['po_name'];
        }
    }
    
    if (!empty($state_v_premises)) {
        $form['factory_part_premises']['state_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'state_name_premises',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'State'
            ),
            '#disabled' => TRUE,
            '#options' => get_all_state($state_v_premises),
            '#value' => !empty($state_v_premises) ? $state_v_premises : $owner_state_premises,
            '#prefix' => '<div id="premises_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
            '#suffix' => '</label></div></div>',
            '#ajax' => array(
                'event' => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_premises',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
    } else {
        $form['factory_part_premises']['state_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'state_name_premises',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'State',
                'readonly' => 'readonly'
            ),
            '#options' => array(
                '' => t('Select State')
            ),
            '#prefix' => '<div id="premises_edit_emp_state_replace"><div class="col-md-4"><label class="select">State',
            '#suffix' => '</label></div></div>',
            '#ajax' => array(
                'event' => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_premises',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')

                )
            )
        );
    }
    
    $value_state_premises = isset($form_state['values']['state']) ? $form_state['values']['state_premises'] : $owner_state_premises;
    
    if (!empty($state_v_premises)) {
        $form['factory_part_premises']['district_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'district_name_premises',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'District'
            ),
            '#options' => get_district_by_id($state_v_premises),
            '#value' => !empty($district_v_premises) ? $district_v_premises : $owner_district_premises,
            '#prefix' => '<div id="premises_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
            '#suffix' => '</label></div></div>',
            '#ajax' => array(
                'event' => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_premises',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
    } else {
        $form['factory_part_premises']['district_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#id' => 'district_name_premises',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'District'
            ),
            '#options' => array(
                '' => t('Select District')
            ),
            '#prefix' => '<div id="premises_edit_emp_district_replace"><div class="col-md-4"><label class="select">District',
            '#suffix' => '</label></div></div>'
        );
    }
    
    $form['factory_part_premises']['firstRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
    $value_district_premises = isset($form_state['values']['district_premises']) ? $form_state['values']['district_premises'] : $owner_district_premises;
    
    $form['factory_part_premises']['secondRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    
    if (!empty($district_v_premises) && !empty($state_v_premises)) {
        
        $form['factory_part_premises']['subdivision_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Sub Division'
            ),
            '#options' => common_custom_user_subdivisionlist_list_new($district_v_premises),
            '#default_value' => $owner_subdivision_premises,
            '#prefix' => '<div id="premises_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>',
            '#ajax' => array(
                'event' => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_premises',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
    } else {
        
        $form['factory_part_premises']['subdivision_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Sub Division'
            ),
            '#options' => array(
                '' => t('Select Sub-Division')
            ),
            '#prefix' => '<div id="premises_empsubdv_replace"><div class="col-md-4"><label class="select">Sub-Division <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    $value_subdivision_premises = isset($form_state['values']['subdivision_premises']) ? $form_state['values']['subdivision_premises'] : $owner_subdivision_premises;
    
    if (!empty($value_district_premises) && !empty($value_state_premises) && !empty($value_subdivision_premises)) {
        $form['factory_part_premises']['areatype_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Area Type'
            ),
            '#options' => common_custom_user_areatype_list_new($value_district_premises, $value_subdivision_premises),
            '#default_value' => $owner_areatype_premises,
            '#prefix' => '<div id="premises_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>',
            '#ajax' => array(
                'event' => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_premises',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
    } else {
        $form['factory_part_premises']['areatype_premises'] = array(
            '#title' => '',
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
            '#prefix' => '<div id="premises_emp_areatype_replace"><div class="col-md-4"><label class="select">Area Type <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
        $form['factory_part_premises']['block_premises']    = array(
            
            '#prefix' => '<div id="premises_empareatype_name_replace">',
            '#suffix' => '</div>'
        );
    }
    
    $value_areatype_premises = isset($form_state['values']['areatype_premises']) ? $form_state['values']['areatype_premises'] : $owner_areatype_premises;
    
    if (!empty($value_district_premises) && !empty($value_state_premises) && $value_subdivision_premises != "" && !empty($value_areatype_premises)) {
        
        if ($value_areatype_premises == 'B') {
            $areatype_name_premises = 'Block';
        } elseif ($value_areatype_premises == 'M') {
            $areatype_name_premises = 'Municipality';
        } elseif ($value_areatype_premises == 'C') {
            $areatype_name_premises = 'Corporation';
        } elseif ($value_areatype_premises == 'S') {
            $areatype_name_premises = 'SEZ';
        } elseif ($value_areatype_premises == 'N') {
            $areatype_name_premises = 'Notified Area';
        }
        
        $form['factory_part_premises']['block_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'subdivision'
            ),
            '#options' => common_custom_user_block_list_new($value_subdivision_premises, $value_areatype_premises),
            '#default_value' => $owner_block_premises,
            '#prefix' => '<div id="premises_empareatype_name_replace"><div class="col-md-4"><label class="select">' . $areatype_name_premises . ' <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>',
            '#ajax' => array(
                'event' => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_premises',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
        
        
    } else {
        $form['factory_part_premises']['block_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'subdivision'
            ),
            '#options' => array(
                '0' => t('Select Block/Municipality/Corporation/SEZ/Notified Area')
            ),
            '#prefix' => '<div id="premises_empareatype_name_replace"><div class="col-md-4"><label class="select">Block/Municipality/Corporation/Notified Area/SEZ <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    
    $form['factory_part_premises']['secondRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
    $form['factory_part_premises']['thirdRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    $value_block_premises                           = isset($form_state['values']['block_premises']) ? $form_state['values']['block_premises'] : $owner_block_premises;
    
    if (!empty($value_district_premises) && !empty($value_subdivision_premises) && !empty($value_areatype_premises) && !empty($value_block_premises) && !empty($value_state_premises)) {
        
        if ($value_areatype_premises == 'B') {
            $area_name_premises = 'Gram Panchayat';
            $area_code_premises = 'V';
        } elseif ($value_areatype_premises == 'M') {
            $area_name_premises = 'Ward';
            $area_code_premises = 'W';
        } elseif ($value_areatype_premises == 'C') {
            $area_name_premises = 'Ward';
            $area_code_premises = 'C';
        } elseif ($value_areatype_premises == 'S') {
            $area_name_premises = 'Sector';
            $area_code_premises = 'S';
        } elseif ($value_areatype_premises == 'N') {
            $area_name_premises = 'Notified Area';
            $area_code_premises = 'N';
        }
        
        
        $form['factory_part_premises']['panchayat_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'panchayat'
            ),
            '#options' => common_custom_user_villward_list_new($value_block_premises, $area_code_premises),
            '#default_value' => $owner_panchayat_premises,
            '#prefix' => '<div id="premises_emp_vill_ward_replace"><div class="col-md-4"><label class="select">' . $area_name_premises . ' <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>',
            '#ajax' => array(
                'event' => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_premises',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
    } else {
        $form['factory_part_premises']['panchayat_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'panchayat'
            ),
            '#options' => array(
                '0' => t('Select Gram Panchayat/Ward/Sector/Notified Area')
            ),
            '#prefix' => '<div id="premises_emp_vill_ward_replace"><div class="col-md-4"><label class="select">Gram Panchayat/Ward/Sector <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    $value_panchayat_premises = isset($form_state['values']['panchayat_premises']) ? $form_state['values']['panchayat_premises'] : $owner_panchayat_premises;
    
    
    
    if (!empty($value_district_premises) && !empty($value_subdivision_premises) && !empty($value_areatype_premises) && !empty($value_block_premises) && !empty($value_state_premises) && !empty($value_panchayat_premises)) {
        
        $form['factory_part_premises']['policestation_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Post Office'
            ),
            '#options' => common_custom_user_ps_list_new($value_district_premises),
            '#default_value' => $owner_policestation_premises,
            //'#prefix' => '<div id="premises_empps_replace"><div class="col-md-4"><label class="select">Police Station2' . $owner_policestation_premises . ' <span id=\'star\'>*</span>',
            '#prefix' => '<div id="premises_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
        
        
        
    } else {
        $form['factory_part_premises']['policestation_premises'] = array(
            '#title' => '',
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
            '#prefix' => '<div id="premises_empps_replace"><div class="col-md-4"><label class="select">Police Station <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    }
    
    if (!empty($pincode_v_premises)) {
        $form['factory_part_premises']['postoffice_premises'] = array(
            '#title' => '',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Post Office'
            ),
            '#options' => common_custom_post_office_list_new($pincode_v_premises),
            '#default_value' => $owner_postoffice_premises,
            '#prefix' => '<div id="premises_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
    } else {
        $form['factory_part_premises']['postoffice_premises'] = array(
            '#title' => '',
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
            '#prefix' => '<div id="premises_post_office_div"><div class="col-md-4"><label class="select">Post Office <span id=\'star\'>*</span>',
            '#suffix' => '</label></div></div>'
        );
        
    }
    
    $form['factory_part_premises']['addrline_premises'] = array(
        '#title' => '',
        '#rows' => 3,
        '#type' => 'textarea',
        '#attributes' => array(
            'class' => array(
                ''
            ),
            'placeholder' => 'Address Line'
        ),
        '#default_value' => $owner_addrline_premises,
        '#prefix' => '<div id="addrline_premises_div"><div class="col-md-12"><label class="textarea">Address <span id=\'star\'>*</span>',
        '#suffix' => '</label></div></div>'
    );
    
		$form['factory_part_premises']['thirdRowEnd'] = array(
			'#prefix' => '',
			'#suffix' => '</div>'
		);
	
    
	
    /********** Details of owner of the premises occupied as a factory - End **********/
	
	/********** In case of Registered Factory - Start **********/
    
    
	
	/********** In case of Registered Factory - End **********/
	
    
    
    $form['back_link'] = array(
        
        '#markup' => l(t('Back'), 'applicant/applicant-dasboard/', array(
            'html' => TRUE,
            'attributes' => array(
                'class' => array(
                    'button '
                )
            )
        ))
    );
    if($application_status == 'I' || $application_status == 'B' || empty($application_status) || $application_status == 'In'){
    $form['submit'] = array(
        '#prefix' => '<div class="col-md-4">',
        '#suffix' => '</div></div>',
        '#attributes' => array(
            'class' => array(
                'btn btn-info'
            )
        ),
        '#type' => 'submit',
        '#value' => 'Save & Continue'
    );
	}else{
		$form['markup'] = array(
       
        '#suffix' => '</div>',
        
        '#type' => 'markup',
       
    );
	}
    return $form;
}

function caf_form_registrstion_parta_validate($form, &$form_state)
{
    global $base_root, $base_path;
    drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
}

function get_ajax_load($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['factory_part_a']['state']));
    $commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['factory_part_a']['district']));
    $commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['factory_part_a']['subdivision']));
    $commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['factory_part_a']['areatype']));
    $commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['factory_part_a']['block']));
    $commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['factory_part_a']['panchayat']));
    $commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['factory_part_a']['policestation']));
    $commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['factory_part_a']['postoffice']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_factory_address($form, &$form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#off_edit_emp_pincodeoff_replace', drupal_render($form['factory_part_off']['pincodeoff']));
    $commands[] = ajax_command_replace('#off_edit_emp_state_replace', drupal_render($form['factory_part_off']['state_off']));
    $commands[] = ajax_command_replace('#off_edit_emp_district_replace', drupal_render($form['factory_part_off']['district_off']));
    $commands[] = ajax_command_replace('#off_empsubdv_replace', drupal_render($form['factory_part_off']['subdivision_off']));
    $commands[] = ajax_command_replace('#off_emp_areatype_replace', drupal_render($form['factory_part_off']['areatype_off']));
    $commands[] = ajax_command_replace('#off_empareatype_name_replace', drupal_render($form['factory_part_off']['block_off']));
    $commands[] = ajax_command_replace('#off_emp_vill_ward_replace', drupal_render($form['factory_part_off']['panchayat_off']));
    $commands[] = ajax_command_replace('#off_empps_replace', drupal_render($form['factory_part_off']['policestation_off']));
    $commands[] = ajax_command_replace('#off_post_office_div', drupal_render($form['factory_part_off']['postoffice_off']));
    $commands[] = ajax_command_replace('#off_addressline_div', drupal_render($form['factory_part_off']['addrline_off']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_load_off($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#off_edit_emp_state_replace', drupal_render($form['factory_part_off']['state_off']));
    $commands[] = ajax_command_replace('#off_edit_emp_district_replace', drupal_render($form['factory_part_off']['district_off']));
    $commands[] = ajax_command_replace('#off_empsubdv_replace', drupal_render($form['factory_part_off']['subdivision_off']));
    $commands[] = ajax_command_replace('#off_emp_areatype_replace', drupal_render($form['factory_part_off']['areatype_off']));
    $commands[] = ajax_command_replace('#off_empareatype_name_replace', drupal_render($form['factory_part_off']['block_off']));
    $commands[] = ajax_command_replace('#off_emp_vill_ward_replace', drupal_render($form['factory_part_off']['panchayat_off']));
    $commands[] = ajax_command_replace('#off_empps_replace', drupal_render($form['factory_part_off']['policestation_off']));
    $commands[] = ajax_command_replace('#off_post_office_div', drupal_render($form['factory_part_off']['postoffice_off']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_occupier_type($form, &$form_state)
{
    $commands   = array();
	$factprofiletype = $form_state['values']['ownership_type'];
    
	if($factprofiletype == 'dir_firm' || $factprofiletype == 'govt' || $factprofiletype == 'psu' || $factprofiletype == 'others')
	{
		$commands[] = ajax_command_replace('#occupier_type_id', drupal_render($form['factory_part_c']['occupier_type']));
		$commands[] = ajax_command_replace('#din_director_id', drupal_render($form['factory_part_c']['din_director']));
	} else {
		$commands[] = ajax_command_replace('#occupier_type_id', drupal_render($form['factory_part_c']['occupier_type']));
		$commands[] = ajax_command_replace('#din_director_id', drupal_render($form['factory_part_c']['din_director_blank']));
	}
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_nationality($form, &$form_state)
{
    $commands   = array();
    //  $commands[] = ajax_command_replace('#occupier_nationality_id', drupal_render( $form['factory_part_c']['occupier_nationality']));
    $commands[] = ajax_command_replace('#ld_show_aadhaar', drupal_render($form['factory_part_c']['occupier_aadhaar']));
	$commands[] = ajax_command_replace('#ld_show_passport', drupal_render($form['factory_part_c']['occupier_passport']));
    $commands[] = ajax_command_replace('#occupier_name_id', drupal_render($form['factory_part_c']['occupier_name']));
    $commands[] = ajax_command_replace('#occupier_age_id', drupal_render($form['factory_part_c']['occupier_age']));
    $commands[] = ajax_command_replace('#occupier_gurdian_name_id', drupal_render($form['factory_part_c']['occupier_gurdian_name']));
    $commands[] = ajax_command_replace('#occupier_telephone_id', drupal_render($form['factory_part_c']['occupier_telephone']));
	$commands[] = ajax_command_replace('#occupier_mobile_id', drupal_render($form['factory_part_c']['occupier_mobile']));
   	$commands[] = ajax_command_replace('#occupier_fax_no_id', drupal_render($form['factory_part_c']['occupier_fax_no']));
	$commands[] = ajax_command_replace('#occupier_emailid', drupal_render($form['factory_part_c']['occupier_email_id']));
    $commands[] = ajax_command_replace('#addrline_oprmntadr_div', drupal_render($form['factory_part_c']['addrline_oprmntadr']));
    $commands[] = ajax_command_replace('#pincodeoprmntadr_id', drupal_render($form['factory_part_c']['pincodeoprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_state_replace', drupal_render($form['factory_part_c']['state_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_district_replace', drupal_render($form['factory_part_c']['district_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empsubdv_replace', drupal_render($form['factory_part_c']['subdivision_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_areatype_replace', drupal_render($form['factory_part_c']['areatype_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empareatype_name_replace', drupal_render($form['factory_part_c']['block_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_vill_ward_replace', drupal_render($form['factory_part_c']['panchayat_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empps_replace', drupal_render($form['factory_part_c']['policestation_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_post_office_div', drupal_render($form['factory_part_c']['postoffice_oprmntadr']));
    
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_load_oprmntadr($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_state_replace', drupal_render($form['factory_part_c']['state_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_district_replace', drupal_render($form['factory_part_c']['district_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empsubdv_replace', drupal_render($form['factory_part_c']['subdivision_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_areatype_replace', drupal_render($form['factory_part_c']['areatype_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empareatype_name_replace', drupal_render($form['factory_part_c']['block_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_vill_ward_replace', drupal_render($form['factory_part_c']['panchayat_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empps_replace', drupal_render($form['factory_part_c']['policestation_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_post_office_div', drupal_render($form['factory_part_c']['postoffice_oprmntadr']));
    
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_same_address_permanent_occupier($form, &$form_state){
	
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
	$commands[] = ajax_command_replace('#addrline_oprsntadr_id', drupal_render($form['factory_part_oprsntadr']['addrline_oprsntadr']));
	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_load_oprsntadr($form, $form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_state_replace', drupal_render($form['factory_part_oprsntadr']['state_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_district_replace', drupal_render($form['factory_part_oprsntadr']['district_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empsubdv_replace', drupal_render($form['factory_part_oprsntadr']['subdivision_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_areatype_replace', drupal_render($form['factory_part_oprsntadr']['areatype_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empareatype_name_replace', drupal_render($form['factory_part_oprsntadr']['block_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_vill_ward_replace', drupal_render($form['factory_part_oprsntadr']['panchayat_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empps_replace', drupal_render($form['factory_part_oprsntadr']['policestation_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_post_office_div', drupal_render($form['factory_part_oprsntadr']['postoffice_oprsntadr']));
	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_load_premises($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#premises_edit_emp_state_replace', drupal_render($form['factory_part_premises']['state_premises']));
    $commands[] = ajax_command_replace('#premises_edit_emp_district_replace', drupal_render($form['factory_part_premises']['district_premises']));
    $commands[] = ajax_command_replace('#premises_empsubdv_replace', drupal_render($form['factory_part_premises']['subdivision_premises']));
    $commands[] = ajax_command_replace('#premises_emp_areatype_replace', drupal_render($form['factory_part_premises']['areatype_premises']));
    $commands[] = ajax_command_replace('#premises_empareatype_name_replace', drupal_render($form['factory_part_premises']['block_premises']));
    $commands[] = ajax_command_replace('#premises_emp_vill_ward_replace', drupal_render($form['factory_part_premises']['panchayat_premises']));
    $commands[] = ajax_command_replace('#premises_empps_replace', drupal_render($form['factory_part_premises']['policestation_premises']));
    $commands[] = ajax_command_replace('#premises_post_office_div', drupal_render($form['factory_part_premises']['postoffice_premises']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function caf_form_registrstion_parta_submit($form, &$form_state)
{
    global $user;
    $userid = $user->uid;
    $val    = $form_state['values'];
	$date_of_amenability		= $val['factor_amenablity_date'];
	$period_for_application				= $val['how_many_year'];
	$application_status = empty( $val['application_status_hidden'])?'':encryption_decryption_fun('decrypt', $val['application_status_hidden']);
  $application_id = empty($val['applicationid_hidden'])?'':encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$flagmapp= encryption_decryption_fun('decrypt', $val['flagmapp_hidden']); 
	if($flagmapp == 'backlogplanapproval_no'){
		$backlog_plan_approval_no =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		$is_backlog = 1;
	}if($flagmapp == 'backlog_registrationno'){
		$backlog_registration_no =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		$is_backlog = 1;
	}if($flagmapp == 'planapproval_no'){
		$factory_plan_approval_number =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		
	}if($flagmapp == 'registration_number'){
		$factory_reg_number =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		
	}
   if($application_status == 'I' || $application_status == NULL || empty($application_status)){
	   $reference_no = created_referenceno();
   }else{
			$get_fa_cafa = get_fa_cafa($application_id);
			$reference_no = $get_fa_cafa['reference_number'];
			
           	
	}
	
    $addr_same                = $form_state['values']['addr_same'];
    //$same_address_communication = $val['same_address_communication'];
    $same_as_address_occupier = $val['same_as_address_occupier'];
    
    if (!empty($val['addr_same']) && ($val['addr_same'] == 1)) {
        $pincodeoff        = $val['pincode'];
        $state_off         = $val['state'];
        $district_off      = $val['district'];
        $subdivision_off   = $val['subdivision'];
        $areatype_off      = $val['areatype'];
        $block_off         = $val['block'];
        $panchayat_off     = $val['panchayat'];
        $policestation_off = $val['policestation'];
        $postoffice_off    = $val['postoffice'];
        $addrline_off      = $val['addrline'];
    } else {
        $pincodeoff        = $val['pincodeoff'];
        $state_off         = $val['state_off'];
        $district_off      = $val['district_off'];
        $subdivision_off   = $val['subdivision_off'];
        $areatype_off      = $val['areatype_off'];
        $block_off         = $val['block_off'];
        $panchayat_off     = $val['panchayat_off'];
        $policestation_off = $val['policestation_off'];
        $postoffice_off    = $val['postoffice_off'];
        $addrline_off      = $val['addrline_off'];
    }
    
    /* communication office - if same as factory address OR if same as register office */
    /*if (!empty($val['same_address_communication']) && ($val['same_address_communication'] == 1)) {
    $pincodecom        = $val['pincode'];
    $state_com         = $val['state'];
    $district_com      = $val['district'];
    $subdivision_com   = $val['subdivision'];
    $areatype_com      = $val['areatype'];
    $block_com         = $val['block'];
    $panchayat_com     = $val['panchayat'];
    $policestation_com = $val['policestation'];
    $postoffice_com    = $val['postoffice'];
    $addrline_com      = $val['addrline'];
    } elseif (!empty($val['same_address_communication']) && ($val['same_address_communication'] == 2)) {
    $pincodecom        = $val['pincodeoff'];
    $state_com         = $val['state_off'];
    $district_com      = $val['district_off'];
    $subdivision_com   = $val['subdivision_off'];
    $areatype_com      = $val['areatype_off'];
    $block_com         = $val['block_off'];
    $panchayat_com     = $val['panchayat_off'];
    $policestation_com = $val['policestation_off'];
    $postoffice_com    = $val['postoffice_off'];
    $addrline_com      = $val['addrline_off'];
    } else {
    $pincodecom        = $val['pincodecom'];
    $state_com         = $val['state_com'];
    $district_com      = $val['district_com'];
    $subdivision_com   = $val['subdivision_com'];
    $areatype_com      = $val['areatype_com'];
    $block_com         = $val['block_com'];
    $panchayat_com     = $val['panchayat_com'];
    $policestation_com = $val['policestation_com'];
    $postoffice_com    = $val['postoffice_com'];
    $addrline_com      = $val['addrline_com'];
    }*/
    
    /* occupier present address - if same as occupier permanent address */
    if (!empty($val['same_as_address_occupier']) && ($val['same_as_address_occupier'] == 1)) {
        $pincodeoprsntadr        = $val['pincodeoprmntadr'];
        $state_oprsntadr         = $val['state_oprmntadr'];
        $district_oprsntadr      = $val['district_oprmntadr'];
        $subdivision_oprsntadr   = $val['subdivision_oprmntadr'];
        $areatype_oprsntadr      = $val['areatype_oprmntadr'];
        $block_oprsntadr         = $val['block_oprmntadr'];
        $panchayat_oprsntadr     = $val['panchayat_oprmntadr'];
        $policestation_oprsntadr = $val['policestation_oprmntadr'];
        $postoffice_oprsntadr    = $val['postoffice_oprmntadr'];
        $addrline_oprsntadr      = $val['addrline_oprmntadr'];
    } else {
        $pincodeoprsntadr        = $val['pincodeoprsntadr'];
        $state_oprsntadr         = $val['state_oprsntadr'];
        $district_oprsntadr      = $val['district_oprsntadr'];
        $subdivision_oprsntadr   = $val['subdivision_oprsntadr'];
        $areatype_oprsntadr      = $val['areatype_oprsntadr'];
        $block_oprsntadr         = $val['block_oprsntadr'];
        $panchayat_oprsntadr     = $val['panchayat_oprsntadr'];
        $policestation_oprsntadr = $val['policestation_oprsntadr'];
        $postoffice_oprsntadr    = $val['postoffice_oprsntadr'];
        $addrline_oprsntadr      = $val['addrline_oprsntadr'];
    }
    
    $cafa_Info = array(
        'factory_name' 			=> $val['factory_name'],
        'factory_previous_name' => $val['factory_previous_name'],
        'factory_location' 		=> $val['factory_location'],
        'factory_zone' 			=> $val['factory_zone'],
        
        //* factory address *//
        'pincode' 				=> $val['pincode'],
        'state' 				=> $val['state'],
        'district' 				=> $val['district'],
        'subdivision' 			=> $val['subdivision'],
        'areatype' 				=> $val['areatype'],
        'block' 				=> $val['block'],
        'panchayat' 			=> $val['panchayat'],
        'policestation' 		=> $val['policestation'],
        'postoffice' 			=> $val['postoffice'],
        'addrline' 				=> $val['addrline'],
        
        /* register office - if same as factory address */
        'pincodeoff' 			=> $pincodeoff,
        'state_off' 			=> $state_off,
        'district_off' 			=> $district_off,
        'subdivision_off' 		=> $subdivision_off,
        'areatype_off' 			=> $areatype_off,
        'block_off' 			=> $block_off,
        'panchayat_off' 		=> $panchayat_off,
        'policestation_off' 	=> $policestation_off,
        'postoffice_off' 		=> $postoffice_off,
        'addrline_off' 			=> $addrline_off,

		'comm_telephone'   	    => $val['comm_telephone'],
		'comm_mobile'     	    => $val['comm_mobile'],
		'comm_fax'     	        => $val['comm_fax'],
		'comm_email'     	    => $val['comm_email'],
        /* communication office - if same as factory address OR if same as register office */

        'factory_pan' 			    => $val['factory_pan'],
		'ownership_type'			=> $val['ownership_type'],
	    'occupier_type '		    => $val['occupier_type'],
        'occupier_nationality' 	    => $val['occupier_nationality'],
        'occupier_aadhaar' 		    => $val['occupier_aadhaar'],
		'occupier_passport' 	    => $val['occupier_passport'],
        'occupier_name' 		    => $val['occupier_name'],
        'occupier_mobile' 		    => $val['occupier_mobile'],
        'occupier_email_id' 	    => $val['occupier_email_id'],
		'occupier_age'   		    => $val['occupier_age'],
		'occupier_gurdian_name'  	=> $val['occupier_gurdian_name'],
		'occupier_fax_no'        	=> $val['occupier_fax_no'],
		'occupier_telephone'     	=> $val['occupier_telephone'],
        
        //* occupier present address *//
        'pincodeoprmntadr' 			=> $val['pincodeoprmntadr'],
        'state_oprmntadr' 			=> $val['state_oprmntadr'],
        'district_oprmntadr' 		=> $val['district_oprmntadr'],
        'subdivision_oprmntadr' 	=> $val['subdivision_oprmntadr'],
        'areatype_oprmntadr' 		=> $val['areatype_oprmntadr'],
        'block_oprmntadr' 			=> $val['block_oprmntadr'],
        'panchayat_oprmntadr' 		=> $val['panchayat_oprmntadr'],
        'policestation_oprmntadr' 	=> $val['policestation_oprmntadr'],
        'postoffice_oprmntadr' 		=> $val['postoffice_oprmntadr'],
        'addrline_oprmntadr' 		=> $val['addrline_oprmntadr'],
        
        /* occupier present address - if same as occupier permanent address */
        'pincodeoprsntadr' 			=> $pincodeoprsntadr,
        'state_oprsntadr' 			=> $state_oprsntadr,
        'district_oprsntadr' 		=> $district_oprsntadr,
        'subdivision_oprsntadr'		=> $subdivision_oprsntadr,
        'areatype_oprsntadr' 		=> $areatype_oprsntadr,
        'block_oprsntadr' 			=> $block_oprsntadr,
        'panchayat_oprsntadr' 		=> $panchayat_oprsntadr,
        'policestation_oprsntadr' 	=> $policestation_oprsntadr,
        'postoffice_oprsntadr' 		=> $postoffice_oprsntadr,
        'addrline_oprsntadr' 		=> $addrline_oprsntadr,
        
        /* owner premises address */
        'owner_name' 				=> $val['owner_name'],
        'pincodepremises' 			=> $val['pincodepremises'],
        'state_premises' 			=> $val['state_premises'],
        'district_premises' 		=> $val['district_premises'],
        'subdivision_premises' 		=> $val['subdivision_premises'],
        'areatype_premises' 		=> $val['areatype_premises'],
        'block_premises' 			=> $val['block_premises'],
        'panchayat_premises' 		=> $val['panchayat_premises'],
        'policestation_premises' 	=> $val['policestation_premises'],
        'postoffice_premises' 		=> $val['postoffice_premises'],
        'addrline_premises'		 	=> $val['addrline_premises'],
      
        'service_id' 				=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
        'factory_typeid' 			=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
        'created_by' 				=> $userid,
        'reg_adress_same_factory' 	=> $addr_same,
        //'communication_adress_same_factory' => $same_address_communication,
        'occupier_present_address_same' => $same_as_address_occupier,
        //New field
	    'trade_license_no' 				=> $val['tread_license_no'],
        'reference_number'  			=> $reference_no,
        'is_backlog'  					=> $is_backlog,
		'application_status'  			=> 'In',
       
	   	'backlog_plan_approval_no'  	=> $backlog_plan_approval_no,
		'backlog_registration_no'  		=> $backlog_registration_no,
		'factory_reg_number' 	    	=> $factory_reg_number,
		'factory_plan_approval_number' 	=> $factory_plan_approval_number,
		'date_of_amenability'			=> $date_of_amenability,
		'period_for_application'		=> $period_for_application
		
	    );

    
    if (empty($application_id)) {
        $id = db_insert('fa_cafa')->fields($cafa_Info)->execute();
		
		create_validate_year1($date_of_amenability,$period_for_application,$val['serviceid_hidden'],$val['factorytypeid_hidden'],$reference_no,$id);
        if ($id) {
			$director_propieter_details = array(
					'type_director'   				=> $val['occupier_type'],
					'name_director' 				=> $val['owner_name'],
					'pincode_director' 				=> $val['pincodeoprmntadr'],
					'state_director' 				=> $val['state_oprmntadr'],
					'district_director' 			=> $val['district_oprmntadr'],
					'sub_division_director' 		=> $val['subdivision_oprmntadr'],
					'area_type_director' 			=> $val['areatype_oprmntadr'],
					'block_mun_cor_sez_not_director'=> $val['block_oprmntadr'],
					'grm_ward_sector_not_director' 	=> $val['panchayat_oprmntadr'],
					'police_station_director' 		=> $val['policestation_oprmntadr'],
					'post_office_director' 			=> $val['postoffice_oprmntadr'],
					'adress_line1_director'		 	=> $val['addrline_oprmntadr'],
					'din_director'		 			=> $val['din_director'],
					
					'created_by'						=> $uid,
					'application_director_id'			=> $id,
					'factory_type_id'					=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
					'add_year_director'					=> date('Y'),
					'director_service_id'				=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
					'application_reference_no'  		=> $reference_no,
					'worker_plan_approval_status'		=> 'In',
					'is_occupier'						=> 1,
					'age_director'   		    		=> $val['occupier_age'],
					'father_husband_name_director'  	=> $val['occupier_gurdian_name']
				);		
		    db_insert('fa_director_details')->fields($director_propieter_details)->execute();
            drupal_set_message('Factory Information has been saved successfully.');
            drupal_goto('applicant/caf-reg/details-worker-hp-yearly-registrtatoin/' . $val['serviceid_hidden'] . '/' . $val['factorytypeid_hidden'].'/'.encryption_decryption_fun('encrypt', $id).'/'.$val['linknumber_hidden'].'/'.$val['flagmapp_hidden']);
        }
    } else {
        //print_r($cafa_Info);die();
        $queryabc = db_update('fa_cafa');
        $queryabc->fields($cafa_Info);
        $queryabc->condition('id', $application_id, '=');
        $queryabc->execute();
		
		$director_propieter_details = array(
					'type_director'   				=> $val['occupier_type'],
					'name_director' 				=> $val['owner_name'],
					'pincode_director' 				=> $val['pincodeoprmntadr'],
					'state_director' 				=> $val['state_oprmntadr'],
					'district_director' 			=> $val['district_oprmntadr'],
					'sub_division_director' 		=> $val['subdivision_oprmntadr'],
					'area_type_director' 			=> $val['areatype_oprmntadr'],
					'block_mun_cor_sez_not_director'=> $val['block_oprmntadr'],
					'grm_ward_sector_not_director' 	=> $val['panchayat_oprmntadr'],
					'police_station_director' 		=> $val['policestation_oprmntadr'],
					'post_office_director' 			=> $val['postoffice_oprmntadr'],
					'adress_line1_director'		 	=> $val['addrline_oprmntadr'],
					'din_director'		 			=> $val['din_director'],
					
					'created_by'						=> $uid,
					'application_director_id'			=> $id,
					'factory_type_id'					=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
					'add_year_director'					=> date('Y'),
					'director_service_id'				=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
					'application_reference_no'  		=> $reference_no,
					'worker_plan_approval_status'		=> 'In',
					'is_occupier'						=> 1,
					'age_director'   		    		=> $val['occupier_age'],
					'father_husband_name_director'  	=> $val['occupier_gurdian_name']
					
				);			
		
		$queryabc = db_update('fa_director_details');
        $queryabc->fields($director_propieter_details);
        $queryabc->condition('application_director_id', $application_id, '=');
		$queryabc->condition('application_reference_no', $reference_no, '=');
		$queryabc->condition('type_director', 'Own','=');
        $queryabc->execute();
		create_validate_year1($date_of_amenability,$period_for_application,$val['serviceid_hidden'],$val['factorytypeid_hidden'],$reference_no,$application_id);
        
        drupal_goto('applicant/caf-reg/details-worker-hp-yearly-registrtatoin/' . $val['serviceid_hidden'] . '/' . $val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['linknumber_hidden'].'/'.$val['flagmapp_hidden']);
    }
    
    $form_state['rebuild'] = true;
}
?> 