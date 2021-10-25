<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function inspection_report_infringement_details($form, &$form_state, $inspection_reportID = '', $factoryID = '', $infringement_detailsID = '') {
		
		global $user;
		$uid = $user->uid;
		
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_reportID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);
		$infringement_details_id = encryption_decryption_fun('decrypt', $infringement_detailsID);
		
		if(empty($inspection_report_id) || $inspection_report_id == '') {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Manager Details first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('admin/inspection-report-factories/manager-details/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL)) ;
		}
		
		$act_id = $section_id = $rule_id = '';
		if($infringement_details_id != NULL) {
			$ir_infringe_data = get_ir_infringement_data_by_id($inspection_report_id, $infringement_details_id);
			$act_id = $ir_infringe_data->act_id;
			$section_id = $ir_infringe_data->section_id;
			$rule_id = $ir_infringe_data->rule_id;
		}
	
		$value_act = isset($form_state['values']['act']) && !empty($form_state['values']['act']) ? $form_state['values']['act'] : $act_id;
		$value_section = isset($form_state['values']['section']) && !empty($form_state['values']['section']) ? $form_state['values']['section'] : $section_id;
		$value_rule = isset($form_state['values']['rule']) && !empty($form_state['values']['rule']) ? $form_state['values']['rule'] : $rule_id;
		
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
			/*'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
			)*/
		);
		
		$form['infringement_details']['markup_appplication'] = array(
			'#prefix' 	=> '<div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
			'#suffix' 	=> '</div></div>',
			'#type' 	=> 'markup',
			'#markup' 	=> get_all_act_list($inspection_report_id, $factory_id),
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
				'#default_value' 	=> $value_section,
				'#ajax' 			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',
										'callback' 		=> 'get_ajax_section_info',
										'progress' 		=> array(
										'type' 			=> 'throbber',
										'message' 		=> t('loading')
									),
				),
			/*	'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				)*/
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
					'#default_value' 	=> $value_rule,
					'#ajax' 			=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',
											'callback' 		=> 'get_ajax_rule_info',
											'progress' 		=> array(
											'type' 			=> 'throbber',
											'message' 		=> t('loading')
										),
					),
				/*	'#select2' => array(
						'width' => '500',
						//'placeholder' => '- Select -',
						'allowClear' => TRUE
					)*/
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
			
			$header = array();
			
			$header = array(
				'sl_no' => array('data' => 'Sl. No.', 'width' => '15%'),
				'infringement_text' => array('data' => 'Infringement', 'width' => '77%'),
			);
			$i = 1;
			if(count($rule_data) > 0) {
				
				if($value_rule != '') {			
			
					foreach($infringement_data as $infringe_details) {
						
						$options[$infringe_details->id] = array(
							'sl_no' => $i,
							'infringement_text' => array('data' => array(
        																	'#type' 			=> 'textarea',
        																	//'#default_value' 	=> $infringe_details->infringement_text,
																			'#value' 			=> $infringe_details->infringement_text,
																			'#name'				=> 'infringement_text['.$infringe_details->id.']',
																			'#rows'				=> 5,
      																),
   												 ),
						);
						
						$form['infringement_details']['infringement_text_info'] = array(
							'#type' => 'tableselect',
							'#header' => $header,
							'#options' => $options,
							'#empty' => t('No infringement available.'),
							'#js_select' => FALSE,
							'#prefix' => '<div id="infringement_text_info_id">',
							'#suffix' => '</div>',
							'#attributes' => array('class' => array("table custom-table-view-dashboard")),
						);
						
						$form['infringement_text'] = array(
							'#type' => 'value'
						);
					
						$i++;
					}
				} else {
					
					$form['infringement_details']['infringement_text_info'] = array(
						'#prefix' => '<div id="infringement_text_info_id">',
						'#suffix' => '</div>',
					);	
				}
			
			} else {
				
				foreach($infringement_data as $infringe_details) {
					
					$options[$infringe_details->id] = array(
						'sl_no' => $i,
						'infringement_text' => array('data' => array(
																		'#type' 			=> 'textarea',
																		//'#default_value' 	=> $infringe_details->infringement_text,
																		'#value' 			=> $infringe_details->infringement_text,
																		'#name'				=> 'infringement_text['.$infringe_details->id.']',
																		'#rows' 			=> 5,
																),
											 ),
					);
					
					$form['infringement_details']['infringement_text_info'] = array(
						'#type' => 'tableselect',
						'#header' => $header,
						'#options' => $options,
						'#empty' => t('No infringement available.'),
						'#js_select' => FALSE,
						'#prefix' => '<div id="infringement_text_info_id">',
						'#suffix' => '</div>',
						'#attributes' => array('class' => array("table custom-table-view-dashboard")),
					);
					
					$form['infringement_text'] = array(
						'#type' => 'value'
					);
				
					$i++;
				}	
			}
		} else {
			
			$form['infringement_details']['infringement_text_info'] = array(
				'#prefix' => '<div id="infringement_text_info_id">',
				'#suffix' => '</div>',
			);
				
		}
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'admin/inspection-report-factories/manager-details/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL), array(
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
		//echo '<pre>'; print_r(array_filter($form_state['values']['infringement_text_info'])); die();
		//echo '<pre>'; print_r($form_state['values']['infringement_text_info']); die();
		//echo $form_state['values']['infringement_text'][1]; die();
		//echo '<pre>'; print_r($form_state['values']); die();
		
		global $base_root,$base_path,$user;
		
		$uid 							= $user->uid;
		
		$inspection_report_id = $form_state['values']['inspection_report_id'];
		
		$factory_id = $form_state['values']['factory_id'];
		
		$infringement_text_info = array_filter($form_state['values']['infringement_text_info']);
		
		$val = $form_state['values'];
		
		$ir_infringement_details = array(
			'inspection_report_id' 	=> $val['inspection_report_id'],
			
			'rule_id' 				=> $val['rule'],
			'section_id' 			=> $val['section'],
			'act_id' 				=> $val['act'],					
			
			'uid' 					=> $uid,
			'created_date'			=> date('Y-m-d H:i:s'),
		);
		//echo '<pre>'; print_r($ir_infringement_details);
		$infringement_details_id = db_insert('fa_ir_infringement_details')->fields($ir_infringement_details)->execute();
		
		foreach($infringement_text_info as $infringe_text_mst_id) {
			$infringe_text_mst_id = trim($infringe_text_mst_id);
			if($infringe_text_mst_id != 0 && !empty($infringe_text_mst_id)) {
				$infringement_text = $val['infringement_text'][$infringe_text_mst_id];
				
				$ir_infringement_text_details = array(
					'infringement_details_id' 	=> $infringement_details_id,
					
					'infringement_id'		=> $infringe_text_mst_id,
					'infringement_text' 	=> $infringement_text,
				);
				//echo '<pre>'; print_r($ir_infringement_details);
				$infringement_text_details_id = db_insert('fa_ir_infringement_text_details')->fields($ir_infringement_text_details)->execute();
			}
		}
		
		$inspection_report_ID = $inspection_report_id;
		
		//die($inspection_report_ID);
		//drupal_goto('admin/inspection-report-factories/workers-details/'.encryption_decryption_fun('encrypt', $inspection_report_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
		
		drupal_goto('admin/inspection-report-list');
	  
		$form_state['rebuild'] = true;
		
		
	}
	
	
	function get_all_act_list($inspection_report_id = '', $factory_id = ''){
		global $user;
		$applicant_id = $user->uid;
		
		$get_all_act_list = get_all_ir_infringement_data($inspection_report_id, $applicant_id);
		//print_r($get_all_act_list);
		$rows[] 				= array();
		
		$header 				= array(
									array('data'=> 'Sl. No.','width' => '8%'),
									array('data'=> 'Act','width' => '20%'),
									array('data'=> 'Section','width' => '15%'),
									array('data'=> 'Rule','width' => '15%'),
									array('data'=> 'View/Edit','width'  => '22%'),
									array('data'=> 'Delete','width' => '15%','align' => 'center'),
								);
		$i = 0;						
		if(!empty($get_all_act_list)) {		
			foreach($get_all_act_list as $act_list_details) {
				$i++;
				
				$infringement_details_id = $act_list_details->id;
				$view_edit_link = l('<i class="fa fa-eye text-blue" aria-hidden="true"></i> View / <i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'admin/inspection-report-factories/infringement-details/'.encryption_decryption_fun('encrypt', $inspection_report_id).'/'.encryption_decryption_fun('encrypt', $factory_id).'/'.encryption_decryption_fun('encrypt', $infringement_details_id), array('html' => TRUE, 'attributes'=>array('title' => 'View/Edit', 'class'=>array(''))));
				
				$onclick="return confirm('Are you sure you want to delete?')";
				
				$del_link = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','#',array('html' => TRUE, 'attributes'=>array('onclick' => $onclick, 'title' => 'Delete')));
				
				if($act_list_details->act_id != NULL) {
					$act_data = get_act_details($act_list_details->act_id);
					$act_name = $act_data->act_name;	
				} else {
					$act_name = 'Not Available';
				}
				
				if($act_list_details->section_id != NULL) {
					$section_data = get_section_details($act_list_details->section_id);
					$section_name = $section_data->section;	
				} else {
					$section_name = 'Not Available';
				}
				
				if($act_list_details->rule_id != NULL) {
					$rule_data = get_rule_details($act_list_details->rule_id);
					$rule_name = $rule_data->rule;	
				} else {
					$rule_name = 'Not Available';
				}
				
				$rows[] = array( 
								array('data' => $i, 'class' => array('')),
								array('data' => $act_name, 'class' => array('')),
								array('data' => $section_name, 'class' => array('')),
								array('data' => $rule_name, 'class' => array('')),
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