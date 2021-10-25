<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function inspector_renewal_details($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceid){

	global $base_root,$base_path,$user;
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	
	if (!empty($application_id)){
        $get_fa_cafa           			= get_fa_cafa($application_id);
       	$application_status      		= $get_fa_cafa['application_status'];
		$factory_identification_number	= $get_fa_cafa['factory_reg_identification_number'];
		$factory_referance_number		= $get_fa_cafa['reference_number'];	
		$applicant_users				= $get_fa_cafa['created_by'];	
		$previous_excess_paid			= $get_fa_cafa['previous_excess_paid'];
		$is_calculate					= $get_fa_cafa['is_calculate'];
		$service_fees					= $get_fa_cafa['service_fees'];	
		$period_for_application 		= $get_fa_cafa['period_for_application'];
	}
	
	
	$user_id 	='';
	$user_id 	= $user->uid;
	$query_check_applicant = db_select('fa_cafa_remarks','remarks');
	$query_check_applicant->leftJoin('fa_cafa','ca', 'ca.remark_by_user_id = remarks.remark_by_uid');  
	$query_check_applicant->fields('remarks', array());
	$query_check_applicant->condition('remarks.app_id', $application_id, '=');
	$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
	$query_check_applicant->orderBy('remarks.id','DESC');
	$query_check_applicant->range(0, 1);
	$result 	= $query_check_applicant->execute();
	$content 	= $result->fetchAssoc();
	
	$ending_year 		= fetch_year_asc($application_id,$service_id,$factory_type_id,$reference_no);
	
	$form = array();
	$form['#attributes'] = array('enctype' => "multipart/form-data");
	$form['serviceid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt',$service_id)
	);	
	$form['factorytype_hidden'] = array(
		'#type' 		=> 'hidden',
		'#default_value'=> encryption_decryption_fun('encrypt',$factory_type_id)
	);		  
	$form['factory_identification_number_hidden'] = array(
		'#type' 		=> 'hidden',
		'#default_value'=> empty($factory_identification_number)?'':encryption_decryption_fun('encrypt',$factory_identification_number)
	);	   
	$form['referance_no_hidden'] = array(
		'#type' 		=> 'hidden',
		'#default_value'=> encryption_decryption_fun('encrypt',$reference_no),		 
	);
	$form['application_id_hidden'] = array(
		'#type' 		=> 'hidden',
		'#default_value'=> encryption_decryption_fun('encrypt', $application_id),	 
	);
	$form['applicant_id_hidden'] = array(
		'#type' 		=> 'hidden',
		'#default_value'=> encryption_decryption_fun('encrypt', $applicant_users),	 
	);
	$form['applicantion_verify']['markup_appplication'] = array(
		'#type' 		=> 'markup',
		'#markup' 		=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
	);
	$form['applicantion_verify']['fieldname']	= array(
		'#title'		=> 'Field Name',
		'#type'			=> 'hidden',
		'#attributes'	=> array('id' => 'inspector_verify'),
		'#default_value'=> !empty($content['verify_details']) ? $content['verify_details'] : '',
	);
	$form['applicantion_verify']['document_list_1'] = array(
			'#type' 		=> 'markup',
			'#markup' 		=> display_document($application_id,$service_id,$factory_type_id,$reference_no),
	);
	$payment_details_link=$base_root.$base_path.'view-payment-breakup/nojs/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceid; 	
		$payment_link=ctools_modal_text_button(t('View Payment Details'), $payment_details_link ,t('View Payment Details'),'btn btn-warning margin');
		
	$form['applicantion_verify']['view_payment_breakup']	 = array(
		'#markup'		=> $payment_link,
	);
	if($application_status == 'DC' || $application_status == 'JC' || $application_status == 'I' || $application_status == 'B'|| $application_status == 'ABk'){
		$form['applicantion_verify']['start_list_1']	 = array(
			'#markup' 		=> '<div class="row">
									<div class="box box-info">
										<div class="box-header with-border">
              								<h3 class="box-title">Checklist:</h3>
											<p>Display all checklisted conditions and comments</p>       
			    						</div>
										<div class="table-responsive">          
		  									<table class="table">
												<thead>
													<tr>
														<th>Conditions</th>
														<th>Assistant director(Remarks)</th>
														<th>Deputy Director (Remarks)</th>
														
													</tr>
												</thead>
											<tbody>',
		);

		$checklist = get_checklist_data($application_id,$factory_type_id,$is_chemical=0);
		//print_r($checklist);die;
		$i=1;
		foreach($checklist as $row){
			if($row->observations_id){ 
				$condition_list = get_conditions_details($row->observations_id);
				}
			elseif(!empty($row->ad_extra_observation)){
				$condition_list = $row->ad_extra_observation;
				}
			elseif(!empty($row->dd_extra_observation)){
				$condition_list = $row->dd_extra_observation;
				}else{
					$condition_list = $row->jd_extra_observation;
					}			
		
		$form['applicantion_verify']['data_list_id'.$i] 	= array(
				'#type' 			=> 'hidden',
				'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				'#default_value'	=> $row->observations_id,
		);
						
 		$form['applicantion_verify']['data_list_'.$i] 	= array(
				'#prefix' 			=> '<tr><td>',
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'markup',
				'#markup'			=> $condition_list,
				'#id'				=> 'range',
				'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				'#default_value'	=> '',
		);
		$split_value = explode(',',$row->ad_details);
		$username =!empty($split_value[1])?'<b>Name:-</b>'.$split_value[1]:'';
		$form['applicantion_verify']['data_details_ad_'.$i] 	= array(
				'#prefix' 			=> '<td>',
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'markup',
				'#markup'			=> ''.$row->remark_by_ad.'</br>'.$username,
				'#attributes' 		=> array('class'=>array('form-control')),
				'#default_value'	=> '',
		);
		$options = array(1=> t('Yes'), 0 => t('No'),);
		$dd_split_value = explode(',',$row->dd_details);	
		$dd_username =!empty($dd_split_value[1])?'Name:-'.$dd_split_value[1]:'';
		if($dd_split_value[2]==1) { $v = $dd_split_value[2]; }else{$v =  0;}	
		if(!empty($row->remark_table_id)){	
			$form['applicantion_verify']['check_option_'.$i] = array(
				  '#prefix' 	=> '<td>',		 
				  '#type' 		=> 'radios',
				  '#options' 	=> $options,
				  '#title' 		=> t('Do you agree or not?'),
				  '#default_value' =>  $v,
				  '#attributes' 	=> array('class'=>array(''),'disabled' => 'disabled'),
			);
			}else{
				$form['applicantion_verify']['check_option_'.$i] = array(
				  '#prefix' 	=> '<td>',		 
				  '#type' 		=> 'markup',
				);
			}
			$data_dd = !empty($dd_split_value[1])? '</br>'.$row->remark_by_dd.'</br><b>Name:-</b>'.$dd_split_value[1].'</br>':'';
			$form['applicantion_verify']['data_list_dd_'.$i] 	= array(
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'markup',
				'#markup'			=> $data_dd,
				'#attributes' 		=> array('class'=>array('form-control')),
				'#default_value'	=> '',
			);
		
			$options = array(1=> t('Yes'), 0 => t('No'),);
			$jd_split_value = explode(',',$row->jd_details);
			$jd_username =!empty($jd_split_value[1])?'<b>Name:-</b>'.$jd_split_value[1]:'';	
			if($jd_split_value[2] == 1) { $view = $jd_split_value[2]; }else{$view =  0;}
			if(empty($row->jd_extra_condition)){	
				//$form['applicantion_verify']['check_option_jd_'.$i] = array(
//					  '#prefix' 		=> '<td>',
//					  '#type' 			=> 'radios',
//					  '#options' 		=> $options,
//					  '#title' 			=> t('Do you agree or not?'),
//					  '#default_value' 	=> $view ,
//					  '#attributes' 	=> array('class'=>array(),),
//					  '#attributes' 		=> array('class'=>array(''),'disabled' => 'disabled'),
//				);
			}else{
//				$form['applicantion_verify']['check_option_jd_'.$i] = array(
//					  '#prefix' 		=> '<td>',
//					  '#type' 			=> 'markup',	
//				);
			}
//				$form['applicantion_verify']['data_list_jd_'.$i] 	= array(
//						'#suffix' 	 		=> '</td>',
//						'#type' 			=> 'markup',
//						'#attributes' 		=> array('class'=>array('form-control')),
//						'#markup'			=> ''.$row->remark_by_jd.'</br>'.$jd_username,
//						'#default_value'	=> '',
//					);
			$i++;
		}
		
		$form['applicantion_verify']['end_list_1']	 = array(
			'#markup' 		=> '</tbody></table></div></div></div>',
		);
		
	}
	
	if($application_status == 'U'  || $application_status == 'DCBk' || $application_status=='RS'){
		$status = !empty($application_status ) ? $application_status  : '';
		if($status=='U'){
			$users_action= array(	
					'0'=>'Select',
					'2'=>'Forword to Deputy Director',
					//'3'=>'Request to repayment',
					'4'=>'Send to specific zone inspector',
				);
		}
		
		elseif($status=='DCBk' ||  $application_status=='RS' ){
			$users_action= array(	
				'0'=>'Select',
				'2'=>'Forword to Deputy Director',
				'3'=>'Request to repayment',	
				
			);
		}
		
		
		$action   = isset($form_state['values']['forword_user']) ? $form_state['values']['forword_user'] : $value_app;
	
		$form['application_forword']['markup1']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">Send to Concerned authority:</h3>
			    					</div>
									<div class = "box-body">',
		);
		$form['application_forword']['forword_user'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select label-block">Necessary action to be taken:<span id=\'star\'>*</span>',
			'#suffix' 			=> '</label></div>',
			'#type' 			=> 'select',
			'#options' 			=> $users_action,
			'#default_value' 	=> $value_app,
			'#ajax' 			=> array('event'=>'change' , 'effect'=> 'fade' , 'callback'=>'get_ajax_note' , 'progress'=> array('type' => 'throbber','message' => t('loading')))
		);
		
	
		$form['application_forword']['download_registration'] = array(
			'#prefix' 	=> '<div id="download_registration">',
			'#suffix' 	=> '</div>',
		);
		$form['application_forword']['download_licence'] = array(
			'#prefix' => '<div id="download_licence">',
			'#suffix' => '</div>',
		);
		$form['application_forword']['doc_file_reg'] = array(
			'#prefix' 	=> '<div id="edit-doc-reg-file-ajax-wrapper">',
			'#suffix' 	=> '</div>',
		);
		$form['application_forword']['doc_file_lic'] = array(
        	'#prefix' => '<div id="edit-doc-lic-file-ajax-wrapper">',
        	'#suffix' => '</div>',
		);
		$form['application_forword']['application_zone_change'] = array(
			'#prefix' 	=> '<div id="zone_change_id">',
			'#suffix' 	=> '</div>',
		);
		$form['application_forword']['application_repay'] = array(
			'#prefix' 	=> '<div id="repay_id">',
			'#suffix' 	=> '</div>',
		);
		$form['application_forword']['application_zone_remark'] = array(
			'#prefix'	=> '<div id="application_zone_remark_id">',
			'#suffix'	=> '</div>',
		);
		$form['application_forword']['application_remark'] = array(
			'#prefix'	=> '<div id="remark_id">',
			'#suffix' 	=> '</div>',
		);
		$form['application_forword']['application_note'] = array(
       	 	'#prefix' => '<div id="application_note">',
        	'#suffix' => '</div>',
		);

		
		if($action == 4){
			$factoryzone 	= get_factory_zone();
			$default_zone 	= array(""=>"- Select Zone -");
			foreach($factoryzone as $val){
				$factzonefinal[$val->zone_id] = $val->zone_name;
				$factzonefinal1 = ($default_zone+$factzonefinal);
			}
			$form['application_forword']['application_zone_change'] = array(
				'#prefix'			=> '<div id="zone_change_id" class="col-md-4 col-xs-8"><label class="select label-block">',
				'#suffix'			=> '</label></div>',
				'#title'			=> t('Zone'),
				'#type'				=> 'select',
				'#options'			=> $factzonefinal1,
				'#default_value'	=> $factory_zone,
		 	);
			$form['application_forword']['application_zone_remark'] = array(
				'#prefix' 			=> '<div id="application_zone_remark_id" class="col-md-12"><label class="input label-block">Remark:',
				'#suffix'			=> '</label></div>',
				'#type'				=> 'textarea',
				'#default_value'	=> !empty($content['remarks']) ? '' : '',
			);
			
		 }
		if($action == 1){
			$form['application_forword']['application_repay'] = array(
				'#prefix' 			=> '<div id="repay_id" class="col-md-8"><label class="input label-block">Repayment Remark:',
				'#suffix'			=> '</label></div>',
				'#type'				=> 'textarea',
				'#default_value'	=> !empty($content['remarks']) ? '' : '',
			);
			
		}
		
		$form['application_forword']['submit'] = array(
			'#prefix' 		=> '<div class="col-md-12 col-xs-12">',
			'#suffix' 		=> '</div>',
			'#attributes'	=> array('class' => array('btn btn-success margin'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
			'#type' 		=> 'submit',
			'#value' 		=> 'Submit'
		);
		$form['application_forword']['markup_end1'] 	= array(
		'#suffix' => '</div></div></div>',
	);
	}
	
	return $form;
}
	 
function get_ajax_note($form, &$form_state){
	$commands   = array();
	
	
	$commands[] = ajax_command_replace('#zone_change_id', drupal_render($form['application_forword']['application_zone_change']));
	
	$commands[] = ajax_command_replace('#edit-doc-reg-file-ajax-wrapper', drupal_render($form['application_forword']['doc_file_reg']));
	$commands[] = ajax_command_replace('#download_registration', drupal_render($form['application_forword']['download_registration']));
	$commands[] = ajax_command_replace('#repay_id', drupal_render($form['application_forword']['application_repay']));
	
	$commands[] = ajax_command_replace('#notesheet_id', drupal_render($form['application_forword']['application_note']));
	$commands[] = ajax_command_replace('#remark_id', drupal_render($form['application_forword']['application_remark']));
	$commands[] = ajax_command_replace('#application_zone_remark_id', drupal_render($form['application_forword']['application_zone_remark']));

	$commands[] = ajax_command_replace('#download_licence', drupal_render($form['application_forword']['download_licence']));
	
	$commands[] = ajax_command_replace('#edit-doc-lic-file-ajax-wrapper', drupal_render($form['application_forword']['doc_file_lic']));
	
	$commands[] = ajax_command_replace('#application_note', drupal_render($form['application_forword']['application_note_lic']));
    return array('#type' => 'ajax', '#commands' => $commands);
}

function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no){
		global $base_root,$base_path,$user;		 
		$user_id = $user->uid;
		$get_all_data =  get_fa_cafa($application_id);
		ctools_include('ajax');
		ctools_include('modal');
		ctools_modal_add_js();
		
		$worker_link=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_worker=ctools_modal_text_button(t('View Worker(s)'), $worker_link ,t('View Details'),'');
		

		// $recommanded_worker_link	=	$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		// $recommanded_link_worker	=	ctools_modal_text_button(t('Worker(s)list recommanded by AD'), $recommanded_worker_link ,t('View Details)')) ;	
		// $power_details=$base_root.$base_path.'view-renewal-power-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		// 	$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details'),'');
		
		
			$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no;  	
			$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)'),'');	
		
			$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details'),'') ;	
		
			$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details'),'');		
			
			$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details'),'') ;
				
			// $manufacturing_details=$base_root.$base_path.'view-renewal-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			// $link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details'),'') ;		
		
			$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details'),'');	
		
			$pre_payment_details=$base_root.$base_path.'view-prepaymnet-history/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_pre_payment=ctools_modal_text_button(t('View Previous Payment'), $pre_payment_details ,t('View Details'),'') ;
		
		
			$amaned_link=$base_root.$base_path.'view-amend_power_worker/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_amend=ctools_modal_text_button(t('Amendment Notice'), $amaned_link ,t('Amendment Notice'),'') ;



			$nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
			foreach($nature_details as $nature){
				$nature_work = $nature->nature_manufacturing;
			}	
			
			$power_generating_station 	= get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
			//print_r($power_generating_station);die;
			foreach($power_generating_station as $power){
				if(!empty($power->recommanded_installed_power) || ($power->recommanded_installed_power!=NULL) || ($power->recommanded_installed_power!=0)){
					if(!empty($power->installed_power)){
						$link_power = $power->installed_power.'('.$power->power_unit.').<br/><font color="red">Recommanded install power '.$power->recommanded_installed_power.'('.$power->recommanded_power_unit.')by AD</font>';
					}else{
						$link_power = 'Under Section 2m(ii)';
					}

				}else{
					if(!empty($power->installed_power)){
						$link_power = $power->installed_power.'('.$power->power_unit.')';
					}else{
						$link_power = 'Under Section 2m(ii)';
					}
				}
				
			}
		
		//$tt=$base_root.$base_path.'inspector-renewal/display-note-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs'; 	
		//	$link_t=ctools_modal_text_button(t('Details Notesheet list View'), $tt ,t('Details Notesheet list View'),'btn btn-warning') ;
			 
		//$remarks=$base_root.$base_path.'regsection/remarks-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs'; 	
		//$remarks_ls=ctools_modal_text_button(t('Details Remarks list View'), $remarks ,t('Details Remarks list View')) ;
			
		//$approve_dsc_reg_file_id			= 	$get_all_data['approve_dsc_reg_file_id'];
		//$licence_register_journal			= 	$get_all_data['licence_register_file_id'];
		//$dsc_reg_file = get_uploaded_document_url($approve_dsc_reg_file_id);
		//$licence_register_file = get_uploaded_document_url($licence_register_journal);
		//if(!empty($approve_dsc_reg_file_id)){
	//		$reg_down	= l('Download Registration Certificate', file_create_url($dsc_reg_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	//	}
	//	
	//	if(!empty($licence_register_file)){
	//		$lic_register_file	= l('Download Licence Register',file_create_url($licence_register_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	//	}
		
		$approve_dsc_licence_file_id		= 	$get_all_data['approve_dsc_licence_file_id'];
		$dsc_lic_file = get_uploaded_document_url($approve_dsc_licence_file_id);	
		
		if(!empty($approve_dsc_licence_file_id)){
			$lic_down	= l('Download Licence Certificate',file_create_url($dsc_lic_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
		}
	
	
		if($get_all_data['factory_owershiptype']=="pv"){
			$ownership_type = "Pvt Ltd Company";
		}if($get_all_data['factory_owershiptype']=="ltd"){
			$ownership_type = "Ltd Company";
		}if($get_all_data['factory_owershiptype']=="par_firm"){
			$ownership_type = "Partnership Firm";
		}if($get_all_data['factory_owershiptype']=="pro_firm"){
			$ownership_type = "Proprietorship Firm";
		}if($get_all_data['factory_owershiptype']=="govt"){
			$ownership_type = "Govt";
		}if($get_all_data['factory_owershiptype']=="psu"){
			$ownership_type = "PSU";
		}if($get_all_data['factory_owershiptype']=="others"){
			$ownership_type = "Others";
		}
		$is_backlog = $get_all_data['is_backlog'];
		if($is_backlog == 1){
			$plan_approval_no = $get_all_data['backlog_plan_approval_no'];
			$plan_approval_date =date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
		}else{
			$plan_approval_no = $get_all_data['factory_plan_approval_number'];
			$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
		}
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		$getdata_factory_location	 = array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address_location 	 = $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location).'<br/>JL No: '.$get_all_data['jl_no'].'<br/>Mouza Name: '.$get_all_data['mouza_name'];
		$getdata_headoffice_address  = array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
		$headoffice_address 	= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
		$getdata_owner_address 	=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
		$owner_address		=	$get_all_data['addrline_premises'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
		$intimation_letter 	=  get_uploaded_document_url($get_all_data['wbpcb_intimation_letter']);
		if(!empty($intimation_letter)){ 
			$url 	 = explode('//',$intimation_letter);
			$doc_url = $url[1];
			$view_intimation_letter ='<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>';
			}else{
				$view_intimation_letter = 'Not Applicable for above mention category';
			}
			$previous_details 			=  get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
				foreach($previous_details as $pre_row){
					$is_previous		 	= $pre_row->is_previous;
					if($is_previous == "Yes"){
						$view = "";
					}if($is_previous == "No"){
						$view = "";
					}
				}

			$pdfs_files = get_application_form_pdf($application_id,$reference_no,$factory_type_id,$service_id);
			$fetch_year	= fetch_year($application_id,$service_id,$factory_type_id,$reference_no);
			$pre_view	= get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
			
			$query_check_applicant = db_select('fa_cafa_remarks','remarks');
			$query_check_applicant->fields('remarks', array());
			$query_check_applicant->condition('remarks.app_id', $application_id, '=');
			$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
			$query_check_applicant->orderBy('remarks.id','DESC');
			$query_check_applicant->range(0, 1);
			$result = $query_check_applicant->execute();
			$data = $result->fetchAssoc();
			$remark_field = explode(',', $data['verify_details']);

			foreach ($remark_field as $fieldname){ 
			//echo $fieldname;
				if($fieldname == 'factory_name'){ $factory_name_ck = "checked='checked'";}
				if($fieldname == 'ownership_type'){ $ownership_type_ck = "checked='checked'";}
				if($fieldname == 'factory_pan'){ $factory_pan_ck = "checked='checked'";}
				
				if($fieldname == 'plan_approval_no'){ $plan_approval_ck = "checked='checked'";}
				if($fieldname == 'plan_approval_date'){ $plan_approval_date_ck = "checked='checked'";}
				
				if($fieldname == 'zone_name'){ $zone_name_ck = "checked='checked'";}
				
				if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = "checked='checked'";}
				
				if($fieldname == 'telephone_no'){ $telephone_no_ck = "checked='checked'";}
				if($fieldname == 'mobile_no'){ $mobile_no_ck 	= "checked='checked'";}
				if($fieldname == 'fax_no'){ $fax_no_ck 	= "checked='checked'";}
				if($fieldname == 'email_no'){ $email_no_ck 	= "checked='checked'";}
				
				if($fieldname == 'owner_name'){ $owner_name_ck = "checked='checked'";}
				if($fieldname == 'premises_address'){ $premises_address_ck = "checked='checked'";}
				
				if($fieldname == 'wbpcb_id'){ $wbpcb_id_ck = "checked='checked'";}
				if($fieldname == 'wbpcb_reference_id'){ $wbpcb_reference_id_ck = "checked='checked'";}
				if($fieldname == 'wbpcb_reference_date'){ $wbpcb_reference_date_ck = "checked='checked'";}
				if($fieldname == 'intimation_id'){ $intimation_id_ck = "checked='checked'";}
				
				if($fieldname == 'date_of_amenability_id'){ $date_of_amenability_id_ck = "checked='checked'";}
				if($fieldname == 'period_for_application_id'){ $period_for_application_id_ck = "checked='checked'";}
				if($fieldname == 'previous_name_id'){ $previous_name_id_ck = "checked='checked'";}

				if($fieldname == 'amendment_notice'){ $amendment_notice_ck = "checked='checked'";}

				
				
				if($fieldname == 'worker_details'){ $worker_details_ck = "checked='checked'";}
				if($fieldname == 'power_details'){ $power_details_ck = "checked='checked'";}
				if($fieldname == 'manager_details'){ $manager_details_ck = "checked='checked'";}
				if($fieldname == 'occupier_details'){ $occupier_details_ck = "checked='checked'";}
				if($fieldname == 'director_details'){ $director_details_ck = "checked='checked'";}
				if($fieldname == 'nature_details'){ $nature_details_ck = "checked='checked'";}
				if($fieldname == 'document_details'){ $document_details_ck = "checked='checked'";}
				
				if($fieldname == 'previous_payment_id'){ $previous_payment_ck = "checked='checked'";}
				if($fieldname == 'payment_amount_id'){ $payment_amount_ck = "checked='checked'";}
				if($fieldname == 'payment_date_id'){ $payment_date_ck = "checked='checked'";}
				if($fieldname == 'applications_forms_id'){ $applications_forms_ck = "checked='checked'";}
				
				if($fieldname == 'applications_period_id'){ $applications_period_ck = "checked='checked'";}
				if($fieldname == 'applications_changes_name_id'){ $applications_changes_name_ck = "checked='checked'";}
				
				
			}
				
	$output .= '<div class="row">
				<div class="box box-info">
				<div class="box-header with-border#"><center><h3 class="box-title">
				Application for Renewal of Licence<br/>All inputs are provided by applicant only<br/>
				All inputs are to be verified by officials</h3>
				</center><h5 class="pull-right">'.$lic_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$reg_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$lic_register_file.' &nbsp;&nbsp;&nbsp;&nbsp;'.$link_t.'&nbsp;&nbsp;&nbsp;&nbsp;'.$remarks_ls.'</h5>
				
				</div>
				<div class="box-body">
				<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table table-bordered custom-table-view"><tr>
   				<th width="30%">Parameters</th>
   				<th>Inputs</th>
				<th width="8%" class="center">Is Verified? <input type="checkbox" id="selectall_inspector"/></th>
				</tr>';
	$output .= '<tr><td colspan="3">A. Factory Information</td></tr>
				<tr>
				<td>(i) Name of the factory</td>
				<td>'.$get_all_data['factory_name'].'</td>
				<td class="center"><input type="checkbox" id="factory_name" class="inspector_verify_check" '.$factory_name_ck .' /></td>
				</tr>
				<tr>
				<td>(ii) Ownership Type</td>
				<td>'.$ownership_type.'</td>
				<td class="center"><input type="checkbox" id="ownership_type" class="inspector_verify_check" '.$ownership_type_ck.'/></td>
				</tr>
				<tr>
				<td>(iii) PAN of the Business Establishment / Factory / Company</td>
				<td>'.$get_all_data['factory_pan'].'</td>
				<td class="center"><input type="checkbox" id="factory_pan" class="inspector_verify_check" '.$factory_pan_ck.'/></td>
				</tr>
				<tr>
				<td>(iv) Plan Approval number</td>
				<td>'.$plan_approval_no.'</td>
				<td class="center"><input type="checkbox" id="plan_approval_no" class="inspector_verify_check"'.$plan_approval_ck.' /></td>
				</tr>
				<tr>
				<td>(v) Plan Approval Date</td>
				<td>'.$plan_approval_date.'</td>
				<td class="center"><input type="checkbox" id="plan_approval_date" class="inspector_verify_check" '.$plan_approval_date_ck.'/></td>
				</tr>
				<tr><td colspan="3">B. Location of Factory</td></tr>
				<tr>
				<td>(i) Zone</td>
				<td>'.$factory_zone_date['zone_name'].'</td>
				<td class="center"><input type="checkbox" id="zone_name" class="inspector_verify_check" '.$zone_name_ck.'/></td>
				</tr>
				<tr>
				<td>(ii) Address</td>
				<td colspan="2">'.$factory_address_location.'</td>
				</tr>
				<tr>
				<td>(iii) Telephone No.</td>
				<td>'.$get_all_data['comm_telephone'].'</td>
				<td class="center"><input type="checkbox" id="telephone_no" class="inspector_verify_check" '.$telephone_no_ck.' /></td>
				</tr>
				<tr>
				<td>(iv) Mobile No.</td>
				<td>'.$get_all_data['comm_mobile'].'</td>
				<td class="center"><input type="checkbox" id="mobile_no" class="inspector_verify_check" '.$mobile_no_ck.'/></td>
				</tr>
				<tr>
				<td>(v) Fax No.</td>
				<td>'.$get_all_data['comm_fax'].'</td>
				<td class="center"><input type="checkbox" id="fax_no" class="inspector_verify_check" '.$fax_no_ck.'/></td>
				</tr>
				<tr>
				<td>(vi) Email Id</td>
				<td>'.$get_all_data['comm_email'].'</td>
				<td class="center"><input type="checkbox" id="email_no" class="inspector_verify_check" '.$email_no_ck.'/></td>
				</tr>
				<tr><td colspan="3">C. Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</font> </td></tr>
				<tr>
				<td>(i) Address</td>
				<td>'.$headoffice_address.'</td>
				<td class="center"><input type="checkbox" id="factory_headoffice" class="inspector_verify_check" '.$factory_headoffice_ck.'/></td>
				</tr>
			
				<tr><td colspan="3">D. Details of owner of the premises occupied as a factory</td></tr>
				<tr>
				<td>(i) Details of the owner</td>
				<td>'.$link_owner.'</td>
				<td class="center"><input type="checkbox" id="owner_name" class="inspector_verify_check" '.$owner_name_ck.'/></td>
				</tr>
				<tr><td colspan="3">E. Factory Identification according to WBPCB</td></tr>
				<tr>
				<td>(i) Category</td>
				<td>'.fetch_catogoryname_wbpcb($get_all_data['wbpcb_category_name']).'</td>
				<td class="center"><input type="checkbox" id="wbpcb_id" class="inspector_verify_check" '.$wbpcb_id_ck.'/></td>
				</tr>
				<tr>
				<td>(ii) Reference No.</td>
				<td>'.$get_all_data['wbpcb_reference_no'].'</td>
				<td class="center"><input type="checkbox" id="wbpcb_reference_id" class="inspector_verify_check" '.$wbpcb_reference_id_ck.'/></td>
				</tr>
				<tr>
				<td>(iii) Reference Date</td>
				<td>'.date('dS M Y', strtotime($get_all_data['wbpcb_ref_date'])).'</td>
				<td class="center"><input type="checkbox" id="wbpcb_reference_date" class="inspector_verify_check" '.$wbpcb_reference_date_ck.'/></td>
				</tr>
				<tr>
				<td>(iv) Intimation Letter</td>
				<td>'.$view_intimation_letter.'</td>
				<td class="center"><input type="checkbox" id="intimation_id" class="inspector_verify_check" '.$intimation_id_ck.'/></td>
				</tr>
				<tr><td colspan="3">F. State the period of licence</td></tr>
				<tr>
				<td>(i) Date from which the premises is occupied or been taken into use as factory</td>
				<td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
				<td class="center"><input type="checkbox" id="date_of_amenability_id" class="inspector_verify_check" '.$date_of_amenability_id_ck.'/></td>
				</tr>
				<tr>
				<td>(ii) State the period of license required </td>
				<td>'.$get_all_data['period_for_application'].'year(s)</td>
				<td class="center"><input type="checkbox" id="period_for_application_id" class="inspector_verify_check" '.$period_for_application_id_ck.'/></td>
				</tr>
				<tr>
				<td>(iii) Details of Amendment Notice </td>
				<td>'.$link_amend.'</td>
				<td class="center"><input type="checkbox" id="amendment_notice" class="inspector_verify_check" '.$amendment_notice_ck.'/></td>
				</tr>
				<tr><td colspan="3">G. Worker Details</td></tr>
				<tr>
				<td>(i) Maximum number of workers employed or to be employed in tha factory</td>
				<td>'.$link_worker.'</td>
				<td class="center"><input type="checkbox" id="worker_details" class="inspector_verify_check" '.$worker_details_ck.'" />
				</tr>
				<tr><td colspan="3">H. Power Details</td></tr>
				<tr>
				<td>(i) Installed Power or to be installed power</td>
				<td>'.$link_power.'</td>
				<td class="center"><input type="checkbox" id="power_details" class="inspector_verify_check" '.$power_details_ck.'"/></td>
				</tr>
	
				<tr><td colspan="3">I. Manager Details</td></tr>
				<tr>
				<td>(i) Manager Details</td>
				<td>'.$link_manager.'</td>
				<td class="center"><input type="checkbox" id="manager_details" class="inspector_verify_check" '.$manager_details_ck.'"/></td>
				</tr>
				<tr><td colspan="3">J. Occupier Details</td></tr>
				<tr>
				<td>(i) View occupier details</td>
				<td>'.$link_occuiper.'</td>
				<td class="center"><input type="checkbox" id="occupier_details" class="inspector_verify_check" '.$occupier_details_ck.'"/></td>
				</tr>
				<tr><td colspan="3">K. Director Details</td></tr>
				<tr>
				<td>(i) View director details</td>
				<td>'.$link_director.'</td>
				<td class="center"><input type="checkbox" id="director_details" class="inspector_verify_check"'.$director_details_ck.'/></td>
				</tr>
				<tr><td colspan="3">L. Manufacturing process</td></tr>
				<tr>
				<td>(i) Carried/to be carried on the factory</td>
				<td>'.$nature_work.'</td>
				<td class="center"><input type="checkbox" id="nature_details" class="inspector_verify_check" '.$nature_details_ck.'/></td>
				</tr>
				<tr><td colspan="3">M. Uploaded Documents</td></tr>
				<tr>
				<td>(i) View uploaded documetns</td>
				<td>'.$link_documents.'</td>
				<td class="center"><input type="checkbox" id="document_details" class="inspector_verify_check" '.$document_details_ck.'/></td>
				</tr>
				<tr><td colspan="3">M. Payment History</td></tr>
				<tr>
				<td>(i) Previous Payment</td>
				<td>'.$link_pre_payment.'</td>
				<td class="center"><input type="checkbox" id="previous_payment_id" class="inspector_verify_check" '.$previous_payment_ck.' /></td>
				</tr>
				<tr>
				<td>(ii) Paid fees</td>
				<td>'.$get_all_data['payment_amount'].'</td>
				<td class="center"><input type="checkbox" id="payment_amount_id" class="inspector_verify_check" '.$payment_amount_ck.' /></td>
				</tr>
				<tr>
				<td>(ii) Payment date</td>
				<td>'.date('dS M Y', strtotime($get_all_data['payment_date'])).'</td>
				<td class="center"><input type="checkbox" id="payment_date_id" class="inspector_verify_check" '.$payment_date_ck.' /></td>
				</tr>
				<tr><td colspan="3">N. Application Forms</td></tr>
				<tr>
				<td><b>Application Peroid</b></td>
				<td><b>Type Of Application</b></td>
				<td class="center"><input type="checkbox" id="applications_forms_id" class="inspector_verify_check" '.$applications_forms_ck.'/></td>
				</tr>
				<tr>
					<td></td>
					<td>Common Application Form</td>
					<td class="center"><a  class =" label label-info" href="'.file_create_url(get_uploaded_document_url($get_all_data['uploaded_pdf'])).'" target="ref" onclick="popIt(this.href);return false;">View Application</a></td>
				</tr>';
	// 	if(!empty($fetch_year)){			
	// 		$output.='<tr>
	// 				<td colspan="3">O.State the period of license</td>
	// 			</tr>
	// 			<tr>
	// 				<td><b>License Period</b></td>
	// 				<td><b>License valid for License Period</b></td>
	// 				<td class="center"><input type="checkbox" id="applications_period_id" class="inspector_verify_check" '.$applications_period_ck.'/></td>
	// 			</tr>';
				
	// 		foreach($fetch_year as $year){
	// 		$is_active_year	= $year->is_active_year;
	// 		if($is_active_year == 1){
	// 			$Remark = "Application period";
	// 			$vaild_period = $year->valid_time_period .'year(s)';
	// 		}else{
	// 			$Remark = "Previous 12 months";
	// 			$vaild_period = 0;
				
	// 		}			
	// 		$output.='<tr>
	// 					<td>'.$year->calculate_year.'</td>
	// 					<td colspan="3">'.$vaild_period.' ==> '.$Remark.'</td>
	// 				</tr>';
	// 			}		
				
				
	// 	$output.='</table>';
	// 	}
	// if(!empty($pre_view)){		
	// 	$output.='<table class="table table-bordered custom-table-view">
	// 		<tr>
	// 			<td colspan="6">P.Whethere any changes name and ownership details of factory</td>
	// 		</tr>
	// 		<tr>
	// 			<td><b>SL No.</b></td>
	// 			<td><b>Application Period</b></td>
	// 			<td><b>Change Date</b></td>
	// 			<td><b>Name</b></td>
	// 			<td><b>Ownership</b></td>
	// 			<td><input type="checkbox" id="applications_changes_name_id" class="inspector_verify_check" '.$applications_changes_name_ck.'/></td>
	// 		</tr>';
			
	// 	foreach($pre_view as $view){
	// 	$sl= $sl+1;	
	// 	if($view->ownership_type=="pv"){
	// 		$ownership_type = "Pvt Ltd Company";
	// 	}if($view->ownership_type=="ltd"){
	// 		$ownership_type = "Ltd Company";
	// 	}if($view->ownership_type=="par_firm"){
	// 		$ownership_type = "Partnership Firm";
	// 	}if($view->ownership_type=="pro_firm"){
	// 		$ownership_type = "Proprietorship Firm";
	// 	}if($view->ownership_type=="govt"){
	// 		$ownership_type = "Govt";
	// 	}if($view->ownership_type=="psu"){
	// 		$ownership_type = "PSU";
	// 	}if($view->ownership_type=="others"){
	// 		$ownership_type = "Others";
	// 	}
	// 	$change_date =  date('dS M Y', strtotime($view->change_date));
		
	// 	$output.='<tr>
	// 				<td>'.$sl.'</td>
	// 				<td>'.$view->service_year.'</td>
	// 				<td>'.$change_date.'</td>
	// 				<td>'.$view->pervious_factory_name.'</td>
	// 				<td>'.$ownership_type.'</td>
	// 				<td>&nbsp;</td>
	// 			</tr>';
	// 	}
	// }
	$output.='</table></div></div></div>';
	
return $output;
}


function inspector_renewal_details_submit($form, &$form_state){
	  global $user;
	  $uid = $user->uid;
	  $val   			= 	$form_state['values'];
	  $service_id 		= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id 	= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $application_id 	= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	  $reference_no		=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	  $applicant_id		=  	encryption_decryption_fun('decrypt',$val['applicant_id_hidden']);
	  
	  
	  //if(trim($_FILES['files']['name']['doc_file'])!=""){
//		if($file = file_save_upload('doc_file', FILE_EXISTS_RENAME))
//			$file->status = FILE_STATUS_PERMANENT; //ADDED
//		    file_save($file);
//			$fid = $file->fid;
//		}
		$remark_by_name = get_name($uid);
	  	$rid= get_role_id($uid);
	  	$value_fields = $val['fieldname'];
		$field_check = explode(',', $value_fields);
		foreach ($field_check as $field_checked){ 
			if($field_checked == 'zone_name'){
				$zone_name_value =  1;
				}
			if($field_checked == 'date_of_amenability_id'){
				$date_of_amenability_value =  2;
				}
		}	

		if($val['forword_user']=='2'){
			if($zone_name_value == 1){
				if($date_of_amenability_value == 2){
					$cafa_remarks = array(
						'app_id'   			 => $application_id,
						'remark_by_uid' 	 => $uid,
						'remark_by_roleid' 	 => $rid,
						'remark_to_roleid' 	 => 10,
						'sending_time' 		 => date('Y-m-d h:i:s'),
						'app_reference_no' 	 => $reference_no,
						'remarks' 	         => NULL,
						'remark_type'		 => 'n',
						'remark_by_name'	 => $remark_by_name,
						'verify_details'	 => $val['fieldname'],
						'status' 			 => 'U',
					);
					//print_r($cafa_remarks);die;
					$id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
					
					drupal_goto('ad_observation/part_1/default/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$id));
					
				
					}else{
						drupal_set_message('Amenability must be confirm.','error');
					}
				}
				else{
				drupal_set_message('Plese check application zone.','error');
			}
		}
		if($val['forword_user']=='4'){
			if($zone_name_value==1){
					drupal_set_message('Please! do not check zone.','error');
					drupal_goto('inspector-renewal/view-renewal-details/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
				}
			else{
					$cafa_remarks = array(
					'app_id'	=> $application_id,
					'remark_by_uid' 	 => $uid,
					'remark_by_roleid' 	 => $rid,
					'remark_to_roleid' 	 => 10,
					'sending_time' 		 => date('Y-m-d h:i:s'),
					'app_reference_no' 	 => $reference_no,
					'remarks' 	         => $val['application_zone_remark'],
					'remark_type'		 => 'n',
					'verify_details'	 => $val['fieldname'],
					'status' 			 => 'U',
					);
					db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
				
					$zone_id = $val['application_zone_change'];	
					$data =	 array('factory_zone' => $zone_id,'application_status' => 'U');
					$queryabc 		 =	db_update('fa_cafa');
					$queryabc		 ->	fields($data);
					$queryabc		 ->	condition('id',$application_id,'=');
					$queryabc		 ->	condition('service_id',$service_id,'=');
					$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
					$queryabc		 ->	condition('reference_number',$reference_no,'=');		
					$queryabc		 ->	execute();
					drupal_set_message('Appliction forworded to specific zone.');
					drupal_goto('inspector-renewal-list/');
					}
		}
		if($val['forword_user']=='3'){
				if(!empty($value)){
					
					$cafa_remarks = array(
								'app_id'   	  		 => $application_id,
								'remark_by_uid'  	 => $uid,
								'remark_by_roleid' 	 => $rid,
								'remark_to_roleid' 	 => 10,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
								'verify_details'	 => $val['fieldname'],
									
						);

						$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();

					drupal_goto('repayment_observation/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
				}else{
					drupal_set_message('First need to Confirm factory zone.','error');
				}
				
			}
		
}
function get_conditions_details($id){
	$conditions_details	=  db_query("SELECT observations  FROM {fa_observations_mst} WHERE id = '".$id."'")->fetchObject()->observations;
	return $conditions_details;
}
function display_document($application_id,$service_id,$factory_type_id,$reference_no){
	$query 	=  db_select('fa_caf_upload_doc', 'fcud');
				$query	-> InnerJoin('fa_file_managed_custom', 'file' ,'fcud.fid = file.id');
				$query 	-> fields('fcud', array());
				$query	-> fields('file', array('file_uri'));
				$query	-> condition('fcud.app_id', $application_id);
				$query	-> condition('fcud.application_reference_no', $reference_no);
				$query	-> condition('fcud.upload_documents_service_id', $service_id);
				$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
				$result = $query->execute();
				//echo $query;die;
				$resultData = $result->fetchAll();
	
	$output.='<div class="row">
				<div class="box box-info">
					<div class="box-header with-border"><h3 class="box-title">Q. Uploaded Documents View</h3></div>
						<div class="box-body">
							<div class="col-md-3">
								 <h4 class="label-warning center">Document List</h4>';
							$i=1;
							foreach($resultData as $documents){
								$output.='<li class="btn btn-success" style="white-space: initial; margin: 7px;"><span class="link"  onclick="seeDoc(this);"  data-id="'.file_create_url($documents->file_uri).'"  data-myval='.file_create_url($documents->file_uri).'>'.file_name($documents->id_doc_master).'</span></li>';
							$i++;
							}
			$output.='</div>
						<div class="col-md-9">
							<h4 class="label-warning center">Preview</h4>
							<object type="application/pdf" id="doc" data="'.$GLOBALS['base_url'].'/sites/default/files/preview.pdf" width="100%" height="580" border="1px"></object>
						</div>
					</div></div></div>';
					return $output;
}
?>