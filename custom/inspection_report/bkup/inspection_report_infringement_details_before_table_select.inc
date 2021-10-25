<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function inspection_report_infringement_details($form, &$form_state, $inspection_reportID = '', $factoryID = '') {
	
		global $user;
		$uid = $user->uid;
		
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_reportID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);
		
	
		$value_act = isset($form_state['values']['act']) && !empty($form_state['values']['act']) ? $form_state['values']['act'] : '';
		$value_section = isset($form_state['values']['section']) && !empty($form_state['values']['section']) ? $form_state['values']['section'] : '';
		$value_rule = isset($form_state['values']['rule']) && !empty($form_state['values']['rule']) ? $form_state['values']['rule'] : '';
		
		$form = array();
		
		$form['inspection_report_id'] = array(
				'#prefix' 			=> '<div id="inspection_report_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> !empty($inspection_report_id) ? $inspection_report_id : '',
		);
		
		$form['factory_id'] = array(
				'#prefix' 			=> '<div id="factory_type_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
		);
		
		$form['infringement_details'] = array(
			'#type' => 'fieldset',
			'#title' => t('G. Infringements Details'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		);		
		
		//$act_list = array('' => '-- Select Act --', 'P' => 'Payment of Wages Act', 'F' => 'Factories Act', 'M' => 'Maternity Bennefit Act');
		//$act_list = array('' => '-- Select Act --', '1' => 'Payment of Wages Act', '2' => 'Factories Act', '3' => 'Maternity Bennefit Act');
		
		$form['infringement_details']['act'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('Select any Act from dropdown for infringements details'),
			'#attributes' 		=> array('class' => array( '')),
			'#options' 			=> get_act_name_list(),
			'#type' 			=> 'select',
			'#default_value'   	=> $value_act,
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',
										'callback' 		=> 'get_ajax_act_info',
										'progress' 		=> array(
										'type' 			=> 'throbber',
										'message' 		=> t('loading')
									),
			),
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
			)
		);
		
		$form['infringement_details']['markup_appplication'] = array(
			'#prefix' 	=> '<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
			'#suffix' 	=> '</div></div></div>',
			'#type' 	=> 'markup',
			'#markup' 	=> get_all_act_list(),
		);
		
		if($value_act != '') {
			
			$form['infringement_details']['section'] = array(
				'#prefix' 			=> '<div id="section_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('Section'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array('')),
				'#options' 			=> get_section_name_list($value_act),
				'#required' 		=> TRUE,
				'#default_value' 	=> '',
				'#ajax' 			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',
										'callback' 		=> 'get_ajax_section_info',
										'progress' 		=> array(
										'type' 			=> 'throbber',
										'message' 		=> t('loading')
									),
				),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				)
			);
			
		} else {
		
			$form['infringement_details']['section'] = array(
				'#prefix' 			=> '<div id="section_id"><div class="col-md-4 col-xs-12" >',
				'#suffix' 			=> '</div></div>',
			);
			
		}
		
		if($value_act != '' && $value_section != '') {
			
			$rule_data = get_rule_name_data($value_act, $value_section);
			if(count($rule_data) > 0) {
			
				$form['infringement_details']['rule'] = array(
					'#prefix' 			=> '<div id="rule_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
					'#suffix' 			=> '</label></div></div></div>',
					'#title' 			=> t('Rule'),
					'#type' 			=> 'select',
					'#attributes' 		=> array('class' => array('')),
					'#options' 			=> get_rule_name_list($value_act, $value_section),
					'#required' 		=> TRUE,
					'#default_value' 	=> '',
					'#ajax' 			=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',
											'callback' 		=> 'get_ajax_rule_info',
											'progress' 		=> array(
											'type' 			=> 'throbber',
											'message' 		=> t('loading')
										),
					),
					'#select2' => array(
						'width' => '500',
						//'placeholder' => '- Select -',
						'allowClear' => TRUE
					)
				);
			
			} else {
		
				$form['infringement_details']['rule'] = array(
					'#prefix' 			=> '<div id="rule_id"><div class="col-md-4 col-xs-12" >',
					'#suffix' 			=> '</div></div></div>',
				);
			
			}
			
		} else {
		
			$form['infringement_details']['rule'] = array(
				'#prefix' 			=> '<div id="rule_id"><div class="col-md-4 col-xs-12" >',
				'#suffix' 			=> '</div></div></div>',
			);	
			
		}
		
		if($value_act != '' && $value_section != '') {
			
			$rule_data = get_rule_name_data($value_act, $value_section);
			$infringement_data = get_infringement_data($value_act, $value_section, $value_rule);
			
			if(count($rule_data) > 0) {
				
				if($value_rule != '') {
					$form['infringement_details']['infringement_table_start'] 	= array(
						'#type'		=> 'markup',
						'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<div id="infringement_table_start_id">
							<table class="custom-table-view-dashboard renewal-table" width="100%">
								<tr>
									<th width="7%">Sl. No.</th>  
									<th width="18%">Select</th>
									<th width="75%">Infringement</th>
								</tr>',
						'#suffix' 	=> '</div>',
					);
					
					$i = 1;
					
					foreach($infringement_data as $infrin_details) {
						
					$form['infringement_details']['infringement_slno'] 	= array(
						'#type'		=> 'markup',
						'#prefix' 	=> '<div id="infringement_slno_id"><tr><td><div class="col-xs-1">'.$i,
						'#suffix' 	=> '</div></td></div></td>',
					);
					
					$form['infringement_details']['infringement_checkbox'] = array(
						'#prefix' 			=> '<div id="infringement_checkbox_id"><td><div class="col-xs-2">',
						'#suffix' 			=> '</div></td></div></td>',
						'#type' 			=> 'checkbox',
						'#title' 			=> t('Select Checkbox'),
						'#default_value' 	=> '',
						'#attributes' 		=> array('class' => array()),
						'#title_display' 	=> 'invisible',
					);
					
					$form['infringement_details']['infringement_text'] = array(
						'#prefix' 			=> '<div id="infringement_text_id"><td><div class="col-xs-9">',
						'#suffix' 			=> '</div></td></tr></div></td></tr>',
						'#type' 			=> 'textarea',
						'#rows' 			=> 6,
						'#title' 			=> t('Infringement'),
						'#default_value' 	=> $infrin_details->infringement_text,
						'#attributes' 		=> array('class' => array()),
						'#title_display' 	=> 'invisible',
					);
						$i++;
					}
						
					$form['infringement_details']['infringement_table_end'] 	= array(
						'#prefix' 	=> '<div id="infringement_table_end_id">',
						'#suffix' 	=> '
							</table>
							</div></div>
							</div>',
						'#type'	  	=> 'markup',
						'#markup'	=> '',	
					);
				
				} else {
					
					$form['infringement_details']['infringement_table_start'] 	= array(
						'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="infringement_table_start_id">',
						'#suffix' 	=> '</div>',
					);
					
					$form['infringement_details']['infringement_slno'] 	= array(
						'#prefix' 	=> '<div id="infringement_slno_id"><div class="col-xs-1">'.$i,
						'#suffix' 	=> '</div></div>',
					);
					
					$form['infringement_details']['infringement_checkbox'] = array(
						'#prefix' 			=> '<div id="infringement_checkbox_id"><div class="col-xs-2">',
						'#suffix' 			=> '</div></div>',
					);
					
					$form['infringement_details']['infringement_text'] = array(
						'#prefix' 			=> '<div id="infringement_text_id"><div class="col-xs-9">',
						'#suffix' 			=> '</div></div>',
					);
					
					$form['infringement_details']['infringement_table_end'] 	= array(
						'#prefix' => '<div id="infringement_table_end_id">',
						'#suffix' => '</div></div></div>',
					);	
				}
			
			} else {
				
				$form['infringement_details']['infringement_table_start'] 	= array(
					'#type'		=> 'markup',
					'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
						<div id="infringement_table_start_id">
						<table class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>
								<th width="7%">Sl. No.</th>  
								<th width="18%">Select</th>
								<th width="75%">Infringement</th>
							</tr>',
					'#suffix' 	=> '</div>',
				);
				
				$i = 1;	
				$form['infringement_details']['infringement_slno'] 	= array(
					'#type'		=> 'markup',
					'#prefix' 	=> '<div id="infringement_slno_id"><tr><td><div class="col-xs-1">'.$i,
					'#suffix' 	=> '</div></td></div></td>',
				);
				
				$form['infringement_details']['infringement_checkbox'] = array(
					'#prefix' 			=> '<div id="infringement_checkbox_id"><td><div class="col-xs-2">',
					'#suffix' 			=> '</div></td></div></td>',
					'#type' 			=> 'checkbox',
					'#title' 			=> t('Select Checkbox'),
					'#default_value' 	=> '',
					'#attributes' 		=> array('class' => array()),
					'#title_display' 	=> 'invisible',
				);
				
				$form['infringement_details']['infringement_text'] = array(
					'#prefix' 			=> '<div id="infringement_text_id"><td><div class="col-xs-9">',
					'#suffix' 			=> '</div></td></tr></div></td></tr>',
					'#type' 			=> 'textarea',
					'#rows' 			=> 3,
					'#title' 			=> t('Infringement'),
					'#default_value' 	=> '',
					'#attributes' 		=> array('class' => array()),
					'#title_display' 	=> 'invisible',
				);
					
				$form['infringement_details']['infringement_table_end'] 	= array(
					'#prefix' 	=> '<div id="infringement_table_end_id">',
					'#suffix' 	=> '
						</table>
						</div></div>
						</div>',
					'#type'	  	=> 'markup',
					'#markup'	=> '',	
				);	
					
			}
		} else {
			
			$form['infringement_details']['infringement_table_start'] 	= array(
				'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="infringement_table_start_id">',
				'#suffix' 	=> '</div>',
			);
			
			$form['infringement_details']['infringement_slno'] 	= array(
				'#prefix' 	=> '<div id="infringement_slno_id"><div class="col-xs-1">'.$i,
				'#suffix' 	=> '</div></div>',
			);
			
			$form['infringement_details']['infringement_checkbox'] = array(
				'#prefix' 			=> '<div id="infringement_checkbox_id"><div class="col-xs-2">',
				'#suffix' 			=> '</div></div>',
			);
			
			$form['infringement_details']['infringement_text'] = array(
				'#prefix' 			=> '<div id="infringement_text_id"><div class="col-xs-9">',
				'#suffix' 			=> '</div></div>',
			);
			
			$form['infringement_details']['infringement_table_end'] 	= array(
				'#prefix' => '<div id="infringement_table_end_id">',
				'#suffix' => '</div></div></div>',
			);
				
		}
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'admin/inspection-report-factories/manager-details/'.$inspection_reportID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['infringement_details_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		return $form;
		
	}
	
	
	function inspection_report_infringement_details_validate($form, &$form_state) {
		
			
		
	}
	
	
	function inspection_report_infringement_details_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		
		$uid 							= $user->uid;
		
		$inspection_report_id = $form_state['values']['inspection_report_id'];
		
		$factory_id = $form_state['values']['factory_id'];
		
		$service_name = 'Inspection Report';
		$service_details = get_service_details($service_name);
		
		$val = $form_state['values'];
		
		if($factory_id != 0) {
			
			if($inspection_report_id == 0) {
			
				$inspection_report = array(
					'cafa_id'              			=> $factory_id,
					'factory_name'         			=> $val['factory_name'],
					'service_id' 					=> $service_details->id,
					'reference_number'     			=> $val['reference_number'],
					'factory_typeid'				=> $val['factory_typeid'],
					'registration_number'  			=> $val['registration_number'],
					'registration_date'    			=> trim(implode('-', array_reverse(explode('-', $val['registration_date'])))),
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> trim(implode('-', array_reverse(explode('-', $val['licence_date'])))),
					'classification_no'    			=> $val['classification_no'],
					'factory_classification_type'  	=> $val['factory_classification_type'],
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
					'building_plan_no'	   			=> $val['building_plan_no'],
					'building_plan_date'    		=> trim(implode('-', array_reverse(explode('-', $val['building_plan_date'])))),
					'inspected_by'    				=> $val['inspected_by'],
					'person_during_inspection'      => $val['person_during_inspection'],
					'nature_manufacturing'        	=> $val['nature_manufacturing'],
					'factory_sector_ownership_type' => $val['factory_sector_ownership_type'],
					'type_power_station'        	=> $val['is_generating'],
					'power_unit'        			=> $val['power_type'],
					'installed_power' 				=> $val['installed_power'],
					'uid' 				   			=> $uid,
					'full_application_status'   	=> 'In',
					'created_date'		   			=> date('Y-m-d'),
					
				);
				
				$inspection_report_ID = db_insert('fa_inspection_report')->fields($inspection_report)->execute();			
				
			} else {
				
				$inspection_report_ID = $inspection_report_id;
				
				$inspection_report = array(
					'cafa_id'              			=> $factory_id,
					'factory_name'         			=> $val['factory_name'],
					'service_id' 					=> $service_details->id,
					'reference_number'     			=> $val['reference_number'],
					'factory_typeid'				=> $val['factory_typeid'],
					'registration_number'  			=> $val['registration_number'],
					'registration_date'    			=> trim(implode('-', array_reverse(explode('-', $val['registration_date'])))),
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> trim(implode('-', array_reverse(explode('-', $val['licence_date'])))),
					'classification_no'    			=> $val['classification_no'],
					'factory_classification_type'  	=> $val['factory_classification_type'],
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
					'building_plan_no'	   			=> $val['building_plan_no'],
					'building_plan_date'    		=> trim(implode('-', array_reverse(explode('-', $val['building_plan_date'])))),
					'inspected_by'    				=> $val['inspected_by'],
					'person_during_inspection'      => $val['person_during_inspection'],
					'nature_manufacturing'        	=> $val['nature_manufacturing'],
					'factory_sector_ownership_type' => $val['factory_sector_ownership_type'],
					'type_power_station'        	=> $val['is_generating'],
					'power_unit'        			=> $val['power_type'],
					'installed_power' 				=> $val['installed_power'],
					'uid' 				   			=> $uid,
					'full_application_status'   	=> 'In',
					'modification_date'	   			=> date('Y-m-d H:i:s'),
					
				);
				
				db_update('fa_inspection_report')->fields($inspection_report)->condition('id', $inspection_report_ID, '=')->execute();	
					
			}
			
		} 
		
		//die($inspection_report_ID);
		drupal_goto('admin/inspection-report-factories/workers-details/'.encryption_decryption_fun('encrypt', $inspection_report_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
	  
		$form_state['rebuild'] = true;
		
		
	}
	
	
	function get_all_act_list(){
		global $user;
		$applicant_id = $user->uid;
		
		$get_all_act_list = get_all_inspection_report_data($applicant_id);
		//print_r($get_all_act_list);
		$rows[] 				= array();
		
		$header 				= array(
									array('data'=> 'Sl. No.','width' => '8%'),
									array('data'=> 'Act','width' => '55%'),
									array('data'=> 'View/Edit','width'  => '22%'),
									array('data'=> 'Delete','width' => '15%','align' => 'center'),
								);
		$i = 0;						
		if(!empty($get_all_act_list)) {		
			foreach($get_all_act_list as $act_list_details) {
				$i++;
				$view_edit_link = l('<i class="fa fa-eye text-blue" aria-hidden="true"></i> View / <i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', '#', array('html' => TRUE, 'attributes'=>array('title' => 'View', 'class'=>array(''))));
				
				$onclick="return confirm('Are you sure you want to delete?')";
				
				$del_link = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','#',array('html' => TRUE, 'attributes'=>array('onclick' => $onclick, 'title' => 'Delete')));
				
				$rows[] = array( 
								array('data' => $i, 'class' => array('')),
								array('data' => 'Demo Act', 'class' => array('')),
								array('data' => $view_edit_link, 'class' => array('')),
								array('data' => $del_link, 'class' => array('')),
							);
			}
							
		} else {
				
			$rows[] = array(
							array('data' => 'No data found!', 'colspan' => 6, 'align' => 'center'),
						);	
		}
		
		$output = theme_table(
		array(
			  'header' 			=> $header,
			  'rows' 			=> $rows,
			  'attributes' 		=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
			  //'attributes' 	=> array('class' => array('table table-bordered custom-table-view')),
			  'caption' 		=> '',
			  'colgroups' 		=> array(),
			  'empty' 			=> t("No data found!") 
			)
		).theme('pager');	
		
		return $output;
		
	}