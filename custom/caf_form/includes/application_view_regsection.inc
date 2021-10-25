<?php
//$applicationid

function application_view_regsection($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) {
	
	global $base_root,$base_path,$user;
  	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	$form = array();
	if (!empty($application_id)) {
        $get_fa_cafa           			= get_fa_cafa($application_id);
       	$application_status      		= $get_fa_cafa['application_status'];
		$factory_identification_number	= $get_fa_cafa['factory_reg_identification_number'];
		$factory_referance_number		= $get_fa_cafa['reference_number'];
		$period_for_application 		= $get_fa_cafa['period_for_application'];
		$previous_excess_paid			= $get_fa_cafa['previous_excess_paid'];
		$is_calculate					= $get_fa_cafa['is_calculate'];
		$service_fees					= $get_fa_cafa['service_fees'];	
    }
	$total_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_type_id,$reference_no);
	$total_schedule_fees = 0;
	$total_due_fees 	= 0;
	$total_late_fees 	= 0;
	$total_fees_to_paid = 0;
	foreach($total_fees_breakup as $total){
		$total->schedule_fees;
						$total->late_fees;
						$total->previous_paid_fees;
						$total->balance_amount;
						$total->due_fees;
						
			$total_schedule_fees = $total_schedule_fees+$total->schedule_fees;
			$total_due_fees = $total_due_fees+$total->due_fees;
			$total_late_fees = $total_late_fees+$total->late_fees;
			$exccess_amount = $total->previous_paid_fees;
		}
		
	//print_r($total_fees_breakup);die;

	$form['applicantion_verify']['markup_appplication'] = array(
			'#type' 			=> 'markup',
			'#markup' 			=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
			);
			
	$form['applicantion_verify']['view_payment_breakup']	 = array(
		'#markup' 		=> l(t('View Payment Details'),'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $factory_type_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $reference_no), array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
);
		
	$form['serviceid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$service_id)
			 
	);	
	$form['factorytype_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$factory_type_id)
			 
	);		  
	$form['factory_identification_number_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> empty($factory_identification_number)?'':encryption_decryption_fun('encrypt',$factory_identification_number)
			 
	);	   
	$form['referance_no_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no),
			 
	);
	
	$form['application_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $application_id),
			 
	);
	
	$form['application_notesheet']['markup1']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row"><div class = "col-md-3 col-xs-12">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">Licence Period:<b> '.$period_for_application.' Years </b></h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['application_notesheet']['period_for_application'] = array(
        '#type' 			=> 'hidden',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($period_for_application)? $period_for_application : '',
	 );
	$form['application_notesheet']['register_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(a). Registration Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($service_fees)? $service_fees : '',
	 );
	 $form['application_notesheet']['renewal_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(b). Renewal Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($renewal_fee)? $renewal_fee : '',
	 );
	 $form['application_notesheet']['amendment_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(c). Amendment Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($amendment_fee)? $amendment_fee : '',
	 );
	 $form['application_notesheet']['transfer_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(d). Transfer Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($transfer_fee)? $transfer_fee : '',
	 );
	 $form['application_notesheet']['late_pay_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(e). Late Payment Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($total_late_fees)? $total_late_fees : '',
	 );
	 $form['application_notesheet']['loss_fee'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(f). Loss Fees:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($loss_fee)? $loss_fee : '',
	 );
	 
	$form['application_notesheet']['markup_end1'] 	= array(
			'#suffix' => '</div></div></div>',
	);  
	
	$form['application_notesheet']['markup2']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class = "col-md-9 col-xs-12">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">Payment List</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$output ='<table class="table table-bordered" width="100%"> <tr>
   								<th>Deposit Date</th>
   								<th>Amount</th>
								<th>Challan Register No.</th>
								<th>Details</th>
								</tr>';
	$manual_payment_deatils	=	manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
	$total = 0;
	foreach($manual_payment_deatils as $history){
			$upload_challan_doc 	=  get_uploaded_document_url($history->upload_challan_file);
			if(!empty($upload_challan_doc)){ 
					$url 		= explode('//',$upload_challan_doc);
					$doc_url	= $url[1];
					$view		='<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>';

			}
								
					$output .='<tr>
									<td>'.date("dS M Y",strtotime($history->date_payment)).'</td>
									<td>'.$history->payment_amount.'</td>
									<td>'.$history->brn_grn_challan_no.'</td>
									<td>'.$view.'</td>
								</tr>';
								$total +=  $history->payment_amount;
							    $ids .= $history->id.',';
								}
								
					$output .='<tr style="background-color: black;color: #fff;font-size: 18px;font-weight: 800;">
									<td >Total:</td>
									<td colspan="4">'.$total.'</td>
								</tr>
		</table>';
  $form['application_notesheet']['markup_show'] 	= array(
			'#markup' => $output,
	);
  $form['application_notesheet']['challan_ids'] 	= array(
        '#type' 			=> 'hidden',
		'#default_value'  => $ids,
	);
  $form['application_notesheet']['register_remarks'] = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Register Remarks:'),
        '#type' 			=> 'textarea',
		'#rows'				=> '5',
		'#cols'				=> '150',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
	 );
	$form['application_notesheet']['excees_fees'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Excees Amount(paid if any):'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>'', 'readonly'=>'readonly'),
		'#default_value' 	=> !empty($exccess_amount)? $exccess_amount: '',
	 );
	 $form['application_notesheet']['adjusted_fees'] = array(
        '#prefix' 			=> '<div class="col-md-6 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('Adjusted againest fee payble:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control'),'title'=>''),
		'#default_value' 	=> '',
	 );
	$form['application_notesheet']['markup_end2'] 	= array(
			'#suffix' => '</div></div></div></div>',
	); 
	if($application_status == 'U'){
	/* REMARKS NOTESHEET */
	$form['applicantion_remark']['markup3']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">Send to Concerned authority:</h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['applicantion_remark']['application_note'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-12"><label class="input">Write a notesheet:',
        '#suffix' 			=> '</label></div>',
        '#type' 			=> 'textarea',
		'#cols'				=> '250',
		'#rows'				=> '5',
        '#default_value' 	=> ''
    );
	
	$form['applicantion_remark']['submit'] = array(
        '#prefix' 			=> '<div class="col-md-4">',
        '#suffix' 			=> '</div>',
        '#attributes' 		=> array('class' => array('btn btn-info')),
        '#type' 			=> 'submit',
        '#value' 			=> 'Send Inspector'
    );
	}
	
	$form['applicantion_remark']['markup_end3'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	return $form; 
}



function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no){
	global $base_root,$base_path,$user;		 
	$user_id = $user->uid;
	$get_all_data =  get_fa_cafa($application_id);
	
	
	$approve_dsc_reg_file_id		= 	$get_all_data['approve_dsc_reg_file_id'];
	$approve_dsc_licence_file_id	= 	$get_all_data['approve_dsc_licence_file_id'];
	$dsc_licence_register_file		= 	$get_all_data['approve_dsc_reg_licence_file_id'];
	$period_for_application 		=	$get_all_data['period_for_application'];	
	
	//print_r($get_fa_cafa);die;
	$dsc_reg_file = get_uploaded_document_url($approve_dsc_reg_file_id);
	$dsc_lic_file = get_uploaded_document_url($approve_dsc_licence_file_id);
	$dsc_lic_reg_file = get_uploaded_document_url($dsc_licence_register_file);
	
	if(!empty($approve_dsc_reg_file_id)){
	$reg_down	= l('Download Registration Certificate', file_create_url($dsc_reg_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button'))));}
	if(!empty($approve_dsc_licence_file_id)){
	$lic_down	= l('Download Licence Certificate',file_create_url($dsc_lic_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button'))));}
	if(!empty($dsc_licence_register_file)){
	$lic_register_file	= l('Download Licence Register',file_create_url($dsc_lic_reg_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button'))));}
	
	$is_backlog = $get_all_data['is_backlog'];
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
	if($is_backlog == 1){
		$plan_approval_no = $get_all_data['backlog_plan_approval_no'];
		$plan_approval_date =date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
	}else{
		$plan_approval_no = $get_all_data['factory_plan_approval_number'];
		$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
	}
	
	$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	 = $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
	$getdata_headoffice_address  =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		 = $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	$getdata_owner_address 		 =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address 				 =	$get_all_data['addrline_premises'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
	$intimation_letter 	=  get_uploaded_document_url($get_all_data['wbpcb_intimation_letter']);
			if(!empty($intimation_letter)){ 
					$url 		= explode('//',$intimation_letter);
					$doc_url	= $url[1];
					$view_intimation_letter		='<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>';
			}else{
				$view_intimation_letter = 'Not Applicable for above mention category';
			}
			
	$previous_details 			=  get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
	//echo $application_id. '--'.  $reference_no. '--'.  $factory_type_id. '--'.  $service_id;
	//die;
	//print_r($previous_details);die();
	foreach($previous_details as $pre_row){
		$is_previous		 	= $pre_row->is_previous;
		if($is_previous == "Yes"){
			$view = "";
		}if($is_previous == "No"){
			$view = "";
		}
	}
	
		ctools_include('ajax');
        ctools_include('modal');
	    ctools_modal_add_js();	 
		
		$worker_link=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_worker=ctools_modal_text_button(t('View Worker(s)'), $worker_link ,t('View Details')) ;
		
		$power_details=$base_root.$base_path.'view-power-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details')) ;
		
		$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details')) ;	
		
		$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details')) ;	
		
		$manufacturing_details=$base_root.$base_path.'view-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details')) ;	
		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details')) ;
		
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		$pre_payment_details=$base_root.$base_path.'view-prepaymnet-history/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_pre_payment=ctools_modal_text_button(t('View Previous Payment'), $pre_payment_details ,t('View Details')) ;
		
		$tt=$base_root.$base_path.'regsection/deputy-note-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs'; 	
		$link_t=ctools_modal_text_button(t('Details Notesheet list View'), $tt ,t('Details Notesheet list View')) ;
		
		$pdfs_files = get_application_form_pdf($application_id,$reference_no,$factory_type_id,$service_id);
		
		$query_check_applicant = db_select('fa_cafa_remarks','remarks');
			$query_check_applicant->leftJoin('fa_cafa','ca', 'ca.remark_by_user_id = remarks.remark_by_uid');  
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
			
			
			$fetch_year	=	fetch_year($application_id,$service_id,$factory_type_id,$reference_no);
			$pre_view	=	get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
				
	$output .='<div class="box box-info">
				<div class="box-header with-border#"><center><h3 class="box-title">Application for Registration and Grant of Licence<br/>All inputs are provided by applicant only<br/>All inputs are to be verified by officials</h3></center><h5 class="pull-right">'.$lic_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$reg_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$lic_register_file.' &nbsp;&nbsp;&nbsp;&nbsp;'.$link_t.'&nbsp;&nbsp;&nbsp;&nbsp;'.$remarks_ls.'</h5></div>
				<div class="box-body">
				<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table table-bordered custom-table-view"><tr>
   				<th width="30%">Parameters</th>
   				<th>Inputs</th>
					<th width="8%" class="center">Is Verified? <input type="checkbox" id="select_all" disabled="" /></th>
								</tr>';
	$output .='<tr><td colspan="3">A.Factory Information</td></tr>
				<tr>
					<td>(i).Name of the factory</td>
					<td>'.$get_all_data['factory_name'].'</td>
					<td><input type="checkbox" id="factory_name" class="verify_check" '.$factory_name_ck .'disabled="" /></td>
				</tr>
				<tr>
					<td>(ii).Ownership Type</td>
					<td>'.$ownership_type.'</td>
					<td><input type="checkbox" id="ownership_type" class="verify_check" '.$ownership_type_ck.' disabled="" /></td>
				</tr>
				<tr>
					<td>(iii).PAN of the Business Establishment / Factory / Company </td>
					<td>'.$get_all_data['factory_pan'].'</td>
					<td><input type="checkbox" id="factory_pan" class="verify_check" '.$factory_pan_ck.'disabled=""/></td>
				</tr>
				<tr>
					<td>(iv).Plan Approval number </td>
					<td>'.$plan_approval_no.'</td>
					<td><input type="checkbox" id="plan_approval_no" class="verify_check"  '.$plan_approval_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td>(iv).Plan Approval Date </td>
					<td>'.$plan_approval_date.'</td>
					<td><input type="checkbox" id="plan_approval_date" class="verify_check" '.$plan_approval_date_ck.' disabled=""/></td>
				</tr>
				
				<tr><td colspan="3">B.Location of Factory </td></tr>
				<tr>
						<td>(i).Zone</td>
						<td>'.$factory_zone_date['zone_name'].'<br/>('.$factory_zone_date['zone_details'].')</td>
						<td rowspan="2"><input type="checkbox" id="zone_name" class="verify_check" '.$zone_name_ck.' disabled=""/></td>
						</tr>
				<tr>
					<td>(ii).Address</td>
					<td>'.$factory_address_location.'</td>
					</tr>
				<tr>
				<td colspan="3">C.Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font> </td>
				</tr>
				<tr>
					<td>(i).Address</td>
					<td>'.$headoffice_address.'</td>
					<td><input type="checkbox" id="factory_headoffice" class="verify_check" '.$factory_headoffice_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td>(ii).Telephone No</td>
					<td>'.$get_all_data['comm_telephone'].'</td>
					<td><input type="checkbox" id="telephone_no" class="verify_check" '.$telephone_no_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td>(iii).Mobile No</td>
					<td>'.$get_all_data['comm_mobile'].'</td>
					<td><input type="checkbox" id="mobile_no" class="verify_check" '.$mobile_no_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td>(iv).Fax No</td>
					<td>'.$get_all_data['comm_fax'].'</td>
					<td><input type="checkbox" id="fax_no" class="verify_check" '.$fax_no_ck.' disabled=""/></td>
					</tr>
				<tr>
					<td>(iv).Email Id</td>
					<td>'.$get_all_data['comm_email'].'</td>
					<td><input type="checkbox" id="email_no" class="verify_check" '.$email_no_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td colspan="3">D.Details of owner of the premises occupied as a factory</td>
				</tr>
				<tr>
					<td>(i).Name of the owner</td>
					<td>'.$get_all_data['owner_name'].'</td>
					<td><input type="checkbox" id="owner_name" class="verify_check" '.$owner_name_ck.'disabled=""/></td>
				</tr>
				<tr>
					<td>(ii).Address</td>
					<td>'.$owner_address.'</td>
					<td><input type="checkbox" id="premises_address" class="verify_check" '.$premises_address_ck.'disabled=""/></td>
				</tr>
				<tr>
					<td colspan="3">E.Factory Identification according to WBPCB</td>
				</tr>
				
				<tr>
					<td>(i).Category</td>
					<td>'.fetch_catogoryname_wbpcb($get_all_data['wbpcb_category_name']).'</td>
					<td><input type="checkbox" id="wbpcb_id" class="verify_check" '.$wbpcb_id_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td>(ii).Reference number</td>
					<td>'.$get_all_data['wbpcb_reference_no'].'</td>
					<td><input type="checkbox" id="wbpcb_reference_id" class="verify_check"  '.$wbpcb_reference_id_ck.'disabled=""/></td>
				</tr>
				<tr>
					<td>(iii).Reference Date</td>
					<td>'.date('dS M Y', strtotime($get_all_data['wbpcb_ref_date'])).'</td>
					<td><input type="checkbox" id="wbpcb_reference_id" class="verify_check"'.$wbpcb_reference_date_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td>(iv).Intimation Letter</td>
					<td>'.$view_intimation_letter.'</td>
					<td><input type="checkbox" id="intimation_id" class="verify_check" '.$intimation_id_ck.'disabled=""/></td>
				</tr>
				<tr><td colspan="3">F.State the period of licence</td></tr>
				<tr>
					<td>(i).Date from which the premises is occupied or been taken into use as factory </td>
					<td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
					<td><input type="checkbox" id="date_of_amenability_id" class="verify_check" '.$date_of_amenability_id_ck.' disabled=""/></td>
				<tr>
					<td>(ii).State the period of license required </td>
					<td>'.$get_all_data['period_for_application'].'year(s)</td>
					<td><input type="checkbox" id="period_for_application_id" class="verify_check"  '.$period_for_application_id_ck.'disabled=""/></td>
				</tr>
				<tr>
					<td>(iii).Whethere any changes name and ownership details of factory </td>
					<td>'.$is_previous.$view.'</td>
					<td><input type="checkbox" id="previous_name_id" class="verify_check" '.$previous_name_id_ck.' disabled=""/></td>
				</tr>
				<tr>
					<td colspan="3">G.Worker Details</td></tr>
				<tr>
					<td>(i).Maximum number of workers employed or to be employed in tha factory</td>
					<td>'.$link_worker.'</td>
					<td><input type="checkbox" id="worker_details" class="verify_check" '.$worker_details_ck.' disabled=""/>
				</tr>
					<tr>
						<td colspan="3">H.Power Details</td>
					</tr>
					<tr>
						<td>(i).Installed Power or to be installed power </td>
						<td>'.$link_power.'</td>
						<td><input type="checkbox" id="power_details" class="deputychief_verify_check" '.$power_details_ck.'disabled=""/></td>
					</tr>
					<tr>
						<td colspan="3">I.Manager Details</td>
					</tr>
					<tr>
						<td>(i).Manager Details</td>
						<td>'.$link_manager.'</td>
						<td><input type="checkbox" id="manager_details" class="verify_check" '.$manager_details_ck.'disabled=""/></td>
					</tr>
					<tr>
						<td colspan="3">J.Occupier Details</td>
					</tr>
					<tr>
						<td>(i).View occupier details</td>
						<td>'.$link_occuiper.'</td>
						<td><input type="checkbox" id="occupier_details" class="verify_check" '.$occupier_details_ck.'disabled=""/></td>
					</tr>
					<tr>
						<td colspan="3">K.Director Details</td>
					</tr>
					<tr>
						<td>(i).View director details</td>
						<td>'.$link_director.'</td>
						<td><input type="checkbox" id="director_details" class="verify_check"'.$director_details_ck.' disabled=""/></td>
				   </tr>
				  <tr>
						<td colspan="3">L.Manufacturing process</td>
				</tr>
				<tr>
					<td>(i).Carried/to be carried on the factory</td>
					<td>'.$link_manufacturing.'</td>
					<td><input type="checkbox" id="nature_details" class="verify_check" '.$nature_details_ck.'disabled=""/></td>
				</tr>
				<tr>
					<td colspan="3">M.Uploaded Documents</td>
				</tr>
				<tr>
					<td>(i).View uploaded documetns</td>
					<td>'.$link_documents.'</td>
					<td><input type="checkbox" id="document_details" class="verify_check" '.$document_details_ck.'disabled="" /></td>
				</tr>
				<tr>
					<td colspan="3">M.Payment History</td>
				</tr>
				<tr>
					<td>(i).Previous Payment</td>
					<td>'.$link_pre_payment.'</td>
					<td><input type="checkbox" id="previous_name_id" class="verify_check" '.$previous_payment_ck.'disabled="" /></td>
				</tr>
				<tr>
					<td>(ii).Paid fees</td>
					<td>'.$get_all_data['payment_amount'].'</td>
					<td><input type="checkbox" id="payment_amount_id" class="verify_check" '.$payment_amount_ck.'disabled="" /></td>
				</tr>
				<tr>
					<td>(ii).Payment date</td>
					<td>'.date('dS M Y', strtotime($get_all_data['payment_date'])).'</td>
					<td><input type="checkbox" id="payment_date_id" class="verify_check" '.$payment_date_ck.'disabled="" /></td>
				</tr>
				<tr>
					<td colspan="3">N.Application Forms</td>
				</tr>
				<tr>
					<td><b>Application period</b></td>
					<td><b>Type Of Application</b></td>
					<td><input type="checkbox" id="applications_forms_id" class="verify_check" '.$applications_forms_ck.'disabled=""/></td>
				</tr>';
				
				$i=1;
				foreach($pdfs_files as $pdfs){
				$output.='
				<tr>
						<td>('.$i.').'.$pdfs->application_period_year.'</td>
						<td>'.$pdfs->type_of_application_from.'</td>
						<td class="center">'.l('View', file_create_url(get_uploaded_document_url($pdfs->pdf_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button')))).'</td>
					</tr>';
					$i++;
					}
		$output.='<tr>
					<td colspan="3">O.State the period of license</td>
				</tr>
				<tr>
					<td><b>License Period</b></td>
					<td><b>License valid for License Period</b></td>
					<td><input type="checkbox" id="applications_period_id" class="verify_check" '.$applications_period_ck.'disabled=""/></td>
				</tr>';
				
		foreach($fetch_year as $year){
		$is_active_year	= $year->is_active_year;
		if($is_active_year == 1){
			$Remark = "Application period";
			$vaild_period = $year->valid_time_period .'year(s)';
		}else{
			$Remark = "Previous 12 months";
			$vaild_period = 0;
			
		}			
		$output.='<tr>
					<td>'.$year->calculate_year.'</td>
					<td colspan="3">'.$vaild_period.' ==> '.$Remark.'</td>
				</tr>';
				}			
				
		$output.='</table>
		
		<table class="table table-bordered">
			<tr>
				<td colspan="6">P.Whethere any changes name and ownership details of factory</td>
			</tr>
			<tr>
				<td><b>SL No.</b></td>
				<td><b>Application Period</b></td>
				<td><b>Change Date</b></td>
				<td><b>Name</b></td>
				<td><b>Ownership</b></td>
				<td><input type="checkbox" id="applications_changes_name_id" class="verify_check" '.$applications_changes_name_ck.'disabled=""/></td>
			</tr>';
			
		foreach($pre_view as $view){
		$sl= $sl+1;	
		if($view->ownership_type=="pv"){
			$ownership_type = "Pvt Ltd Company";
		}if($view->ownership_type=="ltd"){
			$ownership_type = "Ltd Company";
		}if($view->ownership_type=="par_firm"){
			$ownership_type = "Partnership Firm";
		}if($view->ownership_type=="pro_firm"){
			$ownership_type = "Proprietorship Firm";
		}if($view->ownership_type=="govt"){
			$ownership_type = "Govt";
		}if($view->ownership_type=="psu"){
			$ownership_type = "PSU";
		}if($view->ownership_type=="others"){
			$ownership_type = "Others";
		}
		$change_date =  date('dS M Y', strtotime($view->change_date));
		
		$output.='<tr>
					<td>'.$sl.'</td>
					<td>'.$view->service_year.'</td>
					<td>'.$change_date.'</td>
					<td>'.$view->pervious_factory_name.'</td>
					<td>'.$ownership_type.'</td>
					<td>&nbsp;</td>
				</tr>';
		}
		
		$output.='</table></div></div></div>';
return $output;
}



function application_view_regsection_submit($form, &$form_state){
	  global $user;
	  $uid = $user->uid;
	  $val   					= 	$form_state['values'];
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	  
	  //---------------- CAFA TABLE UPDATE -------------------
	  
		$approval_status = 	array('application_status' => 'AI');
		$queryabc 		 =	db_update('fa_cafa');
		$queryabc		 ->	fields($approval_status);
		$queryabc		 ->	condition('id',$application_id,'=');
		$queryabc		 ->	condition('service_id',$service_id,'=');
		$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
		$queryabc		 ->	condition('reference_number',$reference_no,'=');
		$queryabc		 ->	execute();

	  //-----------Worker table update---------------------------
		$worker_status 	= 	array('worker_registration_status' => 'AI');
		$queryabc 		 =	db_update('fa_worker_details');
		$queryabc			->	fields($worker_status);
		$queryabc		    ->	condition('application_id',$application_id,'=');
		$queryabc		    ->	condition('service_id',$service_id,'=');
		$queryabc			->	condition('factory_type',$factorytype_id,'=');
		$queryabc			->	condition('application_reference_no',$reference_no,'=');
		$queryabc			->	execute();
	  
	  //----------------Documents Update-------------------
		$doc_status 	= 	array('application_status' => 'AI');
		$queryabc 		=	db_update('fa_caf_upload_doc');
		$queryabc		->	fields($doc_status);
		$queryabc		->	condition('app_id',$application_id,'=');
		$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
		$queryabc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
		$queryabc		->	condition('application_reference_no',$reference_no,'=');
		$queryabc		->	execute();
		
		
		//-----------Manufacturing table update---------------------------
	  $manufacturing_status 	= 	array('manufacturing_application_status' => 'AI');
	  $querymanufacturing 		 		=	db_update('fa_nature_manufacturing');
	  $querymanufacturing			->	fields($manufacturing_status);
	  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
	  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
	  $querymanufacturing			->	condition('factory_type',$factorytype_id,'=');
	  $querymanufacturing			->	condition('application_reference_no',$reference_no,'=');
	  $querymanufacturing			->	execute();
	  
	  //-----------Power table update---------------------------
	  $power_status 	= 	array('power_application_status' => 'AI');
	  $querypower 		=	db_update('fa_power_details');
	  $querypower			->	fields($power_status);
	  $querypower		    ->	condition('application_id',$application_id,'=');
	  $querypower		    ->	condition('service_id',$service_id,'=');
	  $querypower			->	condition('factory_type',$factorytype_id,'=');
	  $querypower			->	condition('application_reference_no',$reference_no,'=');
	  $querypower			->	execute();
	  
	  //-----------Director table update---------------------------
	  $director_status 	= 	array('application_status' => 'AI');
	  $querydirector 		=	db_update('fa_director_details');
	  $querydirector			->	fields($director_status);
	  $querydirector		    ->	condition('application_director_id',$application_id,'=');
	  $querydirector		    ->	condition('director_service_id',$service_id,'=');
	  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
	  $querydirector			->	condition('application_reference_no',$reference_no,'=');
	  $querydirector			->	execute();
	  
	  $occupier_status 	= 	array('application_status' => 'AI');
	  $querydirector 		=	db_update('fa_occupier_details');
	  $querydirector			->	fields($occupier_status);
	  $querydirector		    ->	condition('application_occupier_id',$application_id,'=');
	  $querydirector		    ->	condition('occupier_service_id',$service_id,'=');
	  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
	  $querydirector			->	condition('application_reference_no',$reference_no,'=');
	  $querydirector			->	execute();
	  
	  //-----------Manager table update---------------------------
	  $manager_status 	= 	array('application_status' => 'AI');
	  $querymanager 		=	db_update('fa_manager_details');
	  $querymanager			->	fields($manager_status);
	  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
	  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
	  $querymanager			->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager			->	condition('application_reference_no',$reference_no,'=');
	  $querymanager			->	execute();

	//----------------Remarks Table Insert -------------------
		$rid = get_role_id($uid);
		$cafa_remarks = array(
		'app_id'   			 => $application_id,
		'remark_by_uid' 	 => $uid,
        'remark_by_roleid' 	 => $rid,
		'remark_to_roleid' 	 => 9,
		'sending_time' 		 => date('Y-m-d h:i:s'),
		'app_reference_no' 	 => $reference_no,
		'remarks' 	         => $val['application_note'],
		'verify_details'	 => NULL,
		'status' 			 => 'AI',
		'remark_type' 		 => 'n',
		);
		$id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
		if(!empty($id)){
				$payment_sheet = array(
				'remark_id'				=> $id,
				'app_id'				=> $application_id,
				'app_reference_no'		=> $reference_no,
				'register_remarks'		=> $val['register_remarks'],
				'licence_period'		=> $val['period_for_application'],
				'excees_fees'			=> $val['excees_fees'],
				'adjusted_fees'			=> $val['adjusted_fees'],
				'register_fee'			=> $val['register_fee'],
				'renewal_fee'			=> $val['renewal_fee'],
				'amendment_fee'			=> $val['amendment_fee'],
				'transfer_fee'			=> $val['transfer_fee'],
				'late_pay_fee'			=> $val['late_pay_fee'],
				'loss_fee'				=> $val['loss_fee'],
				'challan_id'			=> $val['challan_ids'],
				'rid'					=> $rid,
				'is_active'				=> 1,
				);
			db_insert('fa_register_journal')->fields($payment_sheet)->execute();
			}
		
		drupal_set_message('Your remarks has been successfully forwarded to Area Inspector.');
		drupal_goto('regsection-list/');
	
		}


?>