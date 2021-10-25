<?php
function previous_log_data($ajax){
	if ($ajax){
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state = array(
			'ajax' 		=> TRUE,
			'title' 	=> t('Previous Data Details'),
    );
	$output = ctools_modal_form_wrapper('previous_data_details',$form_state);
	if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
	print ajax_render($output);
    drupal_exit();
     
   }else {
     return drupal_get_form('previous_data_details');
   }
}
function previous_data_details($form, &$form_state) {
	global $base_root,$base_path,$user;
	
	$link 			 	= $_GET['q'];
	$link_arr 		 	= explode('/', $link);	
	$applicationid 		= $link_arr[2];
	$serviceid 			= $link_arr[3];
	$factory_typeid 	= $link_arr[4];
	$reference_no 		= $link_arr[5];
	
	$form = array();
	$form['log_details']['log_data'] 	= array(
		'#type' 	=> 'markup',
		'#markup'	=> view_log_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	return $form;
}
function view_log_details($serviceid,$factory_typeid,$applicationid,$referenceno){
	global $base_root,$base_path,$user;
	$output = "";
	
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_number 	= encryption_decryption_fun('decrypt',$referenceno);
	
	
	$get_log_data =  get_cafa_log_data($application_id);
	
	$log_application_id 	= $get_log_data['previous_id'];
	$log_service_id 		= $get_log_data['service_id'];
	$log_factory_typeid 	= $get_log_data['factory_typeid'];
	$log_reference_number 	= $get_log_data['reference_number'];

	if($get_log_data['factory_owershiptype']=="pv"){
   			$ownership_type = "Pvt Ltd Company";
   	}if($get_log_data['factory_owershiptype']=="ltd"){
   			$ownership_type = "Ltd Company";
   	}if($get_log_data['factory_owershiptype']=="par_firm"){
   			$ownership_type = "Partnership Firm";
   	}if($get_log_data['factory_owershiptype']=="pro_firm"){
   			$ownership_type = "Proprietorship Firm";
   	}if($get_log_data['factory_owershiptype']=="govt"){
   			$ownership_type = "Govt";
   	}if($get_log_data['factory_owershiptype']=="psu"){
   			$ownership_type = "PSU";
   	}if($get_log_data['factory_owershiptype']=="llp"){
   			$ownership_type = "Limited Liability Partnership";
   	}if($get_log_data['factory_owershiptype']=="cooperative"){
   			$ownership_type = "Co-operative";
   	}if($get_log_data['factory_owershiptype']=="registered"){
   			$ownership_type = "Registered Society under Society Register";
   	}if($get_log_data['factory_owershiptype']=="localbody"){
   			$ownership_type = "Local Body";
   	}if($get_log_data['factory_owershiptype']=="others"){
   			$ownership_type = "Others";
   	}
	$is_backlog = $get_log_data['is_backlog'];
	if($is_backlog == 1){
		$plan_approval_no = $get_log_data['backlog_plan_approval_no'];
		$plan_approval_date =date('dS M Y', strtotime($get_log_data['backlog_plan_approval_date']));
	}else{
		$plan_approval_no = $get_log_data['factory_plan_approval_number'];
		$plan_approval_date = date('dS M Y', strtotime($get_log_data['modification_date']));
	}
	
	
	$getdata_factory_location	=  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	= $get_log_data['addrline'].',<br/>'.get_full_address('fa_cafa_log','sub-table',$get_log_data['id'],$getdata_factory_location);
	
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		= $get_log_data['addrline_off'].',<br/>'.get_full_address('fa_cafa_log','sub-table',$get_log_data['id'],$getdata_headoffice_address);
	
	$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$communication_address 		= $get_log_data['addrline_comm'].',<br/>'.get_full_address('fa_cafa_log','sub-table',$get_log_data['id'],$getdata_communication_address);
	
	$owner_address_details 	= !empty($get_log_data['addrline_premises'])?$get_log_data['addrline_premises'].',':'';
	$owner_address_details	.= !empty($get_log_data['country_premises'])?country_name($get_log_data['country_premises']):'<br/>';
	
	$getdata_owner_address 		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa_log','sub-table',$get_log_data['id'],$getdata_owner_address);
	
	$passport_details = !empty($get_log_data['passport_premises'])?'Passport No-'.$get_log_data['passport_premises'].',<br/>Passport Issue Date-'.$get_log_data['passport_date_of_issue_premises'].',<br/>Passport Expiry date-'.$get_log_data['passport_date_of_expiry_premises']:'';
	
	$previous_details			=  get_previous_details_view($log_application_id,$log_reference_number,$log_factory_typeid,$log_service_id);
	foreach($previous_details as $pre_row){
		$is_previous		 	= $pre_row->is_previous;
		if($is_previous == "Yes"){
			$view = "";
		}
	}
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();	 
	
	$worker_link=$base_root.$base_path.'view-worker-log-data/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_number; 	
	$link_t=ctools_modal_text_button(t('View Worker(s)'), $worker_link ,t('View Details')) ;
	
	
	$occupier_details=$base_root.$base_path.'view-occupier-log-data/nojs/'.$log_service_id.'/'.$log_factory_typeid.'/'.$log_application_id.'/'.$log_reference_number; 	
	$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details')) ;	
	
	$director_details=$base_root.$base_path.'view-director-log-data/nojs/'.$log_service_id.'/'.$log_factory_typeid.'/'.$log_application_id.'/'.$log_reference_number; 	
	$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details')) ;	
	
	$manager_details=$base_root.$base_path.'view-manager-log-data/nojs/'.$log_service_id.'/'.$log_factory_typeid.'/'.$log_application_id.'/'.$log_reference_number; 	
	$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details')) ;
	
	$documents_details=$base_root.$base_path.'view-documents-log-data/nojs/'.$log_service_id.'/'.$log_factory_typeid.'/'.$log_application_id.'/'.$log_reference_number; 	
	$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details')) ;
	
	
		
	$factory_zone_date = get_factory_zone_name($get_log_data['factory_zone']);
		
	if(!empty($get_log_data['enargy_no'])){ $enargy_no = $get_log_data['enargy_no']; }else{$enargy_no =  'Nil';}
	if(!empty($get_log_data['cin_no'])){ $cin_no = $get_log_data['cin_no']; }else{$cin_no =  'Nil';}
	if(!empty($get_log_data['trade_license_no'])){ $trade_no = $get_log_data['trade_license_no']; }else{$trade_no =  'Nil';}	
	
	$power_generating_station 	= get_power_generating_station($log_application_id,$log_reference_number,$log_factory_typeid,$log_service_id);
	//print_r($power_generating_station);die;
	foreach($power_generating_station as $power){
			$power_details = $power->installed_power_hp.'(HP)';
		}
	$nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_number);
	foreach($nature_details as $nature){
		$nature_work = $nature->nature_manufacturing;
	}
	if($get_log_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = $get_log_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_log_data['wbpcb_ref_date']));}
	if($get_log_data['wbpcb_category_name']==2){$consent ='Green'; $wbpcb_reference_no = $get_log_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_log_data['wbpcb_ref_date']));}
	if($get_log_data['wbpcb_category_name']==3){$consent ='Orange'; $wbpcb_reference_no = $get_log_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_log_data['wbpcb_ref_date']));}
			
	if($get_log_data['wbpcb_category_name']== 4){
		$consent ='White'; 
		$wbpcb_reference_no = 'n/a'; 
		$wbpcb_ref_date = 'n/a';
		$file = $get_log_data['wbpcb_intimation_letter'];
		$file_url = '<a href='.file_create_url(get_uploaded_document_url($file)).' onclick = "popIt(this.href);return false;">View</a>';
	}
	if($get_log_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}
	
	$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance no = '.$wbpcb_ref_date.'<br>'.$file_url;
		
	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border"><span style="float:right;float: right;background-color: #4caf5024; border: 1px #00c0ef solid;color: white;padding: 3px 4px; text-align: center;text-decoration: none;display: inline-block;font-size: 16px;">'.$link_previous.'</span>
              	<h3 class="box-title">Application Preview</h3>
              
            	</div><div class = "box-body">
				<table class="table table-bordered"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
	$output .='<tr><td colspan="2">A.Factory Information</td></tr>
				<tr><td>(i). Name of the factory</td><td>'.$get_log_data['factory_name'].'</td></tr>
				<tr><td>(ii). Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iii). PAN of the Business Establishment / Factory / Company </td><td>'.$get_log_data['factory_pan'].'</td></tr>
				<tr><td>(iv). Plan Approval number </td><td>'.$plan_approval_no.'</td></tr>
				<tr><td>(iv). Plan Approval Date </td><td>'.$plan_approval_date.'</td></tr>
				<tr><td>(v). GSTIN No. </td><td>'.$get_log_data['gstin_no'].'</td></tr>
				<tr><td>(vi). Udyog Aadhaar No.</td><td>'.$get_log_data['udyog_aadhaar'].'</td></tr>
				<tr><td>(vii). Enargy Meter No. </td><td>'.$enargy_no.'</td></tr>
				<tr><td>(viii). CIN No. </td><td>'.$cin_no.'</td></tr>
				<tr><td>(ix). Trade License No. </td><td>'.$trade_no.'</td></tr>
				<tr><td colspan="2">B.Location of Factory </td></tr>
				<tr><td>(i).Zone</td><td>'.$factory_zone_date['zone_name'].'</td></tr>
				<tr><td>(ii).Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td colspan="2">C.Address of the Registered office / Head office</td></tr>
				<tr><td>(i).Address</td><td>'.$headoffice_address.'</td></tr>
				<tr><td>(ii).Telephone No</td><td>'.$get_log_data['comm_telephone'].'</td></tr>
				<tr><td>(iii).Mobile No</td><td>'.$get_log_data['comm_mobile'].'</td></tr>
				<tr><td>(iv).Fax No</td><td>'.$get_log_data['comm_fax'].'</td></tr>
				<tr><td>(iv).Email Id</td><td>'.$get_log_data['comm_email'].'</td></tr>
				<tr><td colspan="2">D. Address to which communications relating to the factory may be sent</td></tr>
				<tr><td>(i).Address</td><td>'.$communication_address.'</td></tr>
				<tr><td colspan="2">E.Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i).Name of the owner</td><td>'.$get_log_data['owner_name'].'&nbsp;'.$get_log_data['owner_mname'].'&nbsp;'.$get_log_data['owner_lname'].'</td></tr>
				<tr><td>(ii).Address</td><td>'.$owner_address.'<br>'.$passport_details.'</td></tr>
				<tr><td>F.Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				<tr><td colspan="2">G.State the period of license</td></tr>
				<tr><td>(i).Date from which the premises is occupied or been taken into use as factory </td><td>'.date('dS M Y', strtotime($get_log_data['date_of_amenability'])).'</td>
				<tr><td>(ii).State the period of license required </td><td>'.$get_log_data['period_for_application'].'year(s)</td></tr>
				<tr><td>(iii).Whethere any changes name and ownership details of factory </td><td>'.$is_previous.$view.'</td></tr>
				<tr><td colspan="2">H.Worker Details</td></tr>
				<tr><td>(i).Maximum number of workers employed or to be employed in tha factory</td><td>'.$link_t.'</td></tr>
				<tr><td colspan="2">I.Power Details</td></tr>
				<tr><td>(i).Installed Power or to be installed power </td><td>'.$power_details.'</td></tr>
				<tr><td colspan="2">J.Manager Details</td></tr>
				<tr><td>(i).Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2">K.Occupier Details</td></tr>
				<tr><td>(i).View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2">L.Director Details</td></tr>
				<tr><td>(i).View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2">M.Manufacturing process</td></tr>
				<tr><td>(i).Carried/to be carried on the factory</td><td>'.$nature_work.'</td></tr>
				<td colspan="2">N.Uploaded Documents</td></tr>
				<tr><td>(i).View uploaded documetns</td><td>'.$link_documents.'</td></tr>';
	$output .= '</table></div></div></div>';
	return $output;
	
	
}

/*----------Worker Preview log------------------------------------*/
function worker_data_log($ajax){
	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state = array(
			'ajax' 		=> TRUE,
			'title' 	=> t('Worker Previous Details'),
    	);
		$output = ctools_modal_form_wrapper('worker_preview_log',$form_state);
		if (!empty($form_state['ajax_commands'])) {
      		$output = $form_state['ajax_commands'];
    	}
		print ajax_render($output);
    	drupal_exit();
		} else {
			return drupal_get_form('worker_preview_log');
   	}
}
function worker_preview_log($form, &$form_state) {
	global $base_root,$base_path,$user;	
	$link 			 = $_GET['q'];
	
	$link_arr		= explode('/', $link);	
	$serviceid 		= $link_arr[2];
	$factory_typeid = $link_arr[3];
	$applicationid 	= $link_arr[4];
	$reference_no 	= $link_arr[5];
	
	$form = array();
	$form['worker_preview']['worker_log'] 	= array(
		  '#type' 				=> 'markup',
		  '#markup'				=> view_worker_log_data($serviceid,$factory_typeid,$applicationid,$reference_no),
	);
	return $form;
}
function view_worker_log_data($serviceid,$factory_typeid,$applicationid,$reference_no){
	$applicant_id 			= $user->uid;
	$worker_details 		= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';					
	/* WORKER DETAILS */
	$worker_details = get_worker_previous_log($serviceid,$factory_typeid,$applicationid,$reference_no);
	//print_r($worker_details);die;
	$output = '<table class="renewal-table" >
					<tr>
						<th  colspan="6">Permanent</th>
						<th  colspan="6">Contactual</th>
					</tr>
					<tr>
						<th rowspan="2">Men</th>
						<th rowspan="2">Women</th>  
						<th colspan="2">Adolescents</th>
						<th colspan="2">Children </th>
			
						<th rowspan="2">Men</th>
						<th rowspan="2">Women</th>  
						<th colspan="2">Adolescents</th>
						<th colspan="2">Children</th>
						
					</tr>
					<tr>
						<th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
					</tr>';

	foreach($worker_details as $worker){
		$permanent_worker_men 			= $worker->permanent_worker_men;
		$permanent_worker_women 		= $worker->permanent_worker_women;
		$permanent_adolescents_male 	= $worker->permanent_adolescents_male;
		$permanent_adolescents_female 	= $worker->permanent_adolescents_female;
		$permanent_children_male 		= $worker->permanent_children_male;
		$permanent_children_female 		= $worker->permanent_children_female;
		$contactual_worker_men 			= $worker->contactual_worker_men;
		$contactual_worker_women 		= $worker->contactual_worker_women;
		$contactual_adolescents_male 	= $worker->contactual_adolescents_male;
		$contactual_adolescents_female 	= $worker->contactual_adolescents_female;
		$contactual_children_male 		= $worker->contactual_children_male;
		$contactual_children_female 	= $worker->contactual_children_female;
		$worker_total 					= $worker->worker_total;
		$previous_worker_total 			= $worker->previous_worker;
		$worker_id 						= $worker->id;
		
	}
	
	$output .='<tr>
			<td>'.$permanent_worker_men.'</td>
			<td>'.$permanent_worker_women.'</td>
			<td>'.$permanent_adolescents_male.'</td>
			<td>'.$permanent_adolescents_female.'</td>
			<td>'.$permanent_children_male.'</td>
			<td>'.$permanent_children_female.'</td>
			<td>'.$contactual_worker_men.'</td>
			<td>'.$contactual_worker_women.'</td>
			<td>'.$contactual_adolescents_male.'</td>
			<td>'.$contactual_adolescents_female.'</td>
			<td>'.$contactual_children_male.'</td>
			<td>'.$contactual_children_female.'</td>
		
		</tr>
		<tfoot>
		<tr>
			<td colspan="12"><font color="#00498b">Total Worker(s)  :-</font>'.$worker_total.'&nbsp;&nbsp;Previous Worker:- <strong>'.$previous_worker_total.'</strong></td>
		</tr>
		</tfoot>
		</table>';
	return $output;
}

/*---------Occupier Preview log---------------------*/
function occupier_data_log($ajax){
	if ($ajax){
		ctools_include('ajax');
		ctools_include('modal');
		ctools_modal_add_js();
		$form_state = array(
			'ajax' 		=> TRUE,
			'title' 	=> t(''),
		);
		$output = ctools_modal_form_wrapper('occupier_preview_log',$form_state);
		
		if (!empty($form_state['ajax_commands'])){
			$output = $form_state['ajax_commands'];
		}
		print ajax_render($output);
		drupal_exit();
	} else {
		return drupal_get_form('occupier_preview_log');
	}
}
function occupier_preview_log($form, &$form_state) {
	global $base_root,$base_path,$user;
	
	$link 			= $_GET['q'];
	$link_arr 		= explode('/', $link);	
	$serviceid 		= $link_arr[2];
	$factory_typeid = $link_arr[3];
	$applicationid 	= $link_arr[4];
	$reference_no 	= $link_arr[5];
	$form = array();
	$form['preview_occupier']['occupier_log'] = array(
		'#type' 	=> 'markup',
		'#markup'	=> view_occupier_details($applicationid,$serviceid,$factory_typeid,$reference_no),
	);
	return $form;
}
function view_occupier_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	//echo $applicationid.'--'.$serviceid.'--'.$factory_typeid.'--'.$reference_no;die;
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$get_all_data = get_all_occupier_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	
	$Wcounter		= 0;
	$per_page		= 5;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
							array('data' => 'Sl. No'),
							array('data'=> 'Details of Occupier'),
							array('data'=> 'Present Address'),
							array('data'=> 'Premanant Address'),
							//array('data'=> 'Service Name'),
							//array('data'=> 'Action'),
						);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if($details->application_status == 'In'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			else if($details->worker_plan_approval_status == 'In'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-occupier-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->reference_number).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		$fieldArr_occupier			 =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
    $address_of_occupier	 =	$details->addrline_oprmntadr.'<br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldArr_occupier);
	$details_occupier = $details->name_occupier.'('.$details->type_occupier.')'.'<br/>Father/Husband:-'.$details->father_husband_name_occupier.'<br/>Age:-'.$details->age_occupier;
	
		$fieldArr_occupier_presnt			 =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
    $address_of_occupier_presnt	 =	$details->addrline_oprsntadr.'<br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldArr_occupier_presnt);
			$rows[] 	= array(
				array('data' =>$Wcounter,'class' => array('')),
				array('data' =>$details_occupier,'class' => array('')),
				array('data' =>$address_of_occupier_presnt ,'class' => array('')),
				array('data' =>$address_of_occupier ,'class' => array('')),
			);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_occupier_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;	
}

/*---------Manager Preview log---------------------*/
function manager_data_log($ajax){
	if ($ajax){
		ctools_include('ajax');
		ctools_include('modal');
		ctools_modal_add_js();
		$form_state = array(
			'ajax' 		=> TRUE,
			'title' 	=> t(''),
		);
		$output = ctools_modal_form_wrapper('manager_preview_log',$form_state);
		
		if (!empty($form_state['ajax_commands'])){
			$output = $form_state['ajax_commands'];
		}
		print ajax_render($output);
		drupal_exit();
	} else {
		return drupal_get_form('manager_preview_log');
	}
}
function manager_preview_log($form, &$form_state) {
	global $base_root,$base_path,$user;
	
	$link 			= $_GET['q'];
	$link_arr 		= explode('/', $link);	
	$serviceid 		= $link_arr[2];
	$factory_typeid = $link_arr[3];
	$applicationid 	= $link_arr[4];
	$reference_no 	= $link_arr[5];
	$form = array();
	$form['preview_manager']['manager_log'] = array(
		'#type' 	=> 'markup',
		'#markup'	=> view_manager_details($applicationid,$serviceid,$factory_typeid,$reference_no),
	);
	return $form;
}
function view_manager_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	//echo $applicationid.'--'.$serviceid.'--'.$factory_typeid.'--'.$reference_no;die;
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$get_all_data = get_all_manager_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	$chunks 		= array_chunk($get_all_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Employee Type'),
						array('data'=> 'Employee Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						array('data'=> 'Action'),		
					);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $manager_details){ 
			$Wcounter++;
			
			if($manager_details->relationship_manager == '1'){
				$relationship = 'D/O';
			}if($manager_details->relationship_manager == '2'){
				$relationship = 'S/O';
			}if($manager_details->relationship_manager == '3'){
				$relationship = 'W/O';
			}
			if($manager_details ->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-manager-registration/'.encryption_decryption_fun('encrypt', $manager_details->id).'/'.encryption_decryption_fun('encrypt', $manager_details->application_manager_id).'/'.encryption_decryption_fun('encrypt', $manager_details->manager_service_id).'/'.encryption_decryption_fun('encrypt', $manager_details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $manager_details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		
		$fieldArr_manager			 =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
   $address_of_manager	 =	$manager_details->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager_details->id,$fieldArr_manager);
     $manager_details_view =$manager_details->name_manager.'<br/>' .$relationship.'-'.$manager_details->father_husband_name_manager.'<br/>Age:-'.$manager_details->age_manager;
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>'Manager' ,'class' => array('')),
								array('data' =>$manager_details_view,'class' => array('')),
								array('data' =>$address_of_manager ,'class' => array('')),	
								array('data' =>$manager_details->manager_present_address.'<br>'.'Telephone: '.$manager_details->manager_telephone.'<br>'.'Mobile: '.$manager_details->manager_phone.'<br>'.'FAX: '.$manager_details->manager_fax.'<br>'.'Email: '.$manager_details->manager_email ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								);
				} 
		
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_manager_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '(1). All Manager List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;		
}

/*---------Director Preview log---------------------*/
function director_data_log($ajax){
	if ($ajax){
		ctools_include('ajax');
		ctools_include('modal');
		ctools_modal_add_js();
		$form_state = array(
			'ajax' 		=> TRUE,
			'title' 	=> t(''),
		);
		$output = ctools_modal_form_wrapper('director_preview_log',$form_state);
		
		if (!empty($form_state['ajax_commands'])){
			$output = $form_state['ajax_commands'];
		}
		print ajax_render($output);
		drupal_exit();
	} else {
		return drupal_get_form('director_preview_log');
	}
}
function director_preview_log($form, &$form_state) {
	global $base_root,$base_path,$user;
	
	$link 			= $_GET['q'];
	$link_arr 		= explode('/', $link);	
	$serviceid 		= $link_arr[2];
	$factory_typeid = $link_arr[3];
	$applicationid 	= $link_arr[4];
	$reference_no 	= $link_arr[5];
	$form = array();
	$form['preview_director']['director_log'] = array(
		'#type' 	=> 'markup',
		'#markup'	=> view_director_details($applicationid,$serviceid,$factory_typeid,$reference_no),
	);
	return $form;
}
function view_director_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	//echo $applicationid.'--'.$serviceid.'--'.$factory_typeid.'--'.$reference_no;die;
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$get_all_data = get_director_details_service($applicationid,$serviceid,$factory_typeid,$reference_no);
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Employee Type'),
						array('data'=> 'Employee Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						array('data'=> 'Action'),		
					);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
			if($type=='ltd' || $type=='pv'){$director_type = 'Director';}
			if($type == 'par_firm'){$director_type 	= 'Partner';}
			if($type == 'pro_firm'){$director_type 	= 'Proprietor';}
			if($type == 'govt' || $type == 'psu' || $type == 'others'){$director_type 	= 'Nominated Occupier';}
			if(!empty($details->age_director)){
				$age = 'Age- '.$details->age_director;
				}
			$is_occupier =$details->is_occupier;
			
			$relation =$details->relationship_director;
			 if($relation == 1){
				$relationship = 'D/O';
			}
			 if($relation == 2){
				$relationship = 'S/O';
			}
			 if($relation == 3){
				$relationship = 'W/O';
			}
			if($is_occupier == 1){
				$occupier = '<br/>(Occupier)';
			}else{$occupier = '';}
			if($details->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			else if($details->worker_plan_approval_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-dir-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_director_id).'/'.encryption_decryption_fun('encrypt', $details->director_service_id).'/'.encryption_decryption_fun('encrypt', $details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		$fieldArr_director			 =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    $address_of_director	 =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$director_type ,'class' => array('')),
								array('data' =>$details->name_director.'<br>'.$din.'<br>'.$relationship.'-'.$details->father_husband_name_director.'<br>'.$age,'class' => array('')),
								array('data' =>$address_of_director ,'class' => array('')),
								array('data' =>$details->addrline_oprsntadr.'<br>'.'Telephone: '.$details->director_telephone.'<br>'.'Mobile: '.$details->director_mobile.'<br>'.'FAX: '.$details->director_fax_no.'<br>'.'Email: '.$details->director_email_id ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								//array('data' =>'View' ,'class' => array('')),
								);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_director_details_id1', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '(2). All Director List',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	return $output;	
}

/*-----------Document preview log------------------------*/
function document_data_log($ajax){
	if ($ajax){
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state 	= array(
			'ajax'	=> TRUE,
			'title'	=> t('')
		);
		$output = ctools_modal_form_wrapper('document_preview_log',$form_state);
		if (!empty($form_state['ajax_commands'])) {
			$output = $form_state['ajax_commands'];
    	}
		print ajax_render($output);
		drupal_exit();
	} else {
		return drupal_get_form('document_preview_log');
	}
} 
function document_preview_log($form, &$form_state) {	

$link 			 = $_GET['q'];

$link_arr 		 	= explode('/', $link);
	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['preview_log']['document_log'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_document_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	 
	  return $form;	

}
function view_document_details($serviceid,$factory_typeid,$applicationid,$reference_no){

	$query 	=  db_select('fa_caf_upload_doc', 'fcud');
	$query	-> InnerJoin('fa_file_managed_custom', 'file' ,'fcud.fid = file.id');
	$query 	-> fields('fcud', array());
	$query	-> fields('file', array('file_uri'));
	$query	-> condition('fcud.app_id', $applicationid);
	$query	-> condition('fcud.application_reference_no', $reference_no);
	$query	-> condition('fcud.upload_documents_service_id', $serviceid);
	$query	-> condition('fcud.upload_doc_factory_type_id', $factory_typeid);
	$result = $query->execute();
	//echo $applicationid.'----->'.$reference_no.'----->'.$serviceid.'----->'.$factory_typeid.'------>'.$query;die;
	$resultData = $result->fetchAll();
	
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Related Documents'),
		array('data'=> 'Previous Uploaded Documents'),
		
		//array('data'=> 'Act')
	);
	$i=1;
	foreach($resultData as $documents){
		
		
		$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>',file_create_url($documents->file_uri),array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$rows[] = array( 
						array('data' =>$i,'class' => array('')),
						//array('data' =>file_name($documents->id_doc_master) ,'class' => array('')),
						array('data' =>$documents->doc_name ,'class' => array('')),
						array('data' =>$displayLink,'class' => array('')),
								//array('data' =>get_service_name($nature->service_id) ,'class' => array('')),
				);
					
			$i++;
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);
	return $output;	
}

/*---------------------------------------------*/
/*----------previous name change data------------------------------------*/
function previous_factory_name($ajax){
	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state = array(
			'ajax' 		=> TRUE,
			'title' 	=> t('factory Previous Details'),
		);
		
		$output = ctools_modal_form_wrapper('factory_preview_name',$form_state);
		if (!empty($form_state['ajax_commands'])) {
      		$output = $form_state['ajax_commands'];
    	}
		print ajax_render($output);
    	drupal_exit();
		} else {
			return drupal_get_form('factory_preview_name');
   	}
}
function factory_preview_name($form, &$form_state) {
	global $base_root,$base_path,$user;	
	$link 			 = $_GET['q'];
	
	$link_arr		= explode('/', $link);	
	$serviceid 		= $link_arr[2];
	$factory_typeid = $link_arr[3];
	$applicationid 	= $link_arr[4];
	$reference_no 	= $link_arr[5];
	
	$form = array();
	$form['worker_preview']['preview_name_log'] 	= array(
		  '#type' 				=> 'markup',
		  '#markup'				=> view_previous_name_data($serviceid,$factory_typeid,$applicationid,$reference_no),
	);
	return $form;
}
function view_previous_name_data($serviceid,$factory_typeid,$applicationid,$reference_no){
	$output = '';
	$sl = 0;
//echo $serviceid.'--'.$factory_typeid.'--'.$applicationid.'--'.$reference_no;die;
	$pre_view	=	get_previous_details_view($applicationid,$reference_no,$factory_typeid,$serviceid);
	//print_r($pre_view);die($pre_view[0]->id);
	//$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/transfer-delete-year/'.encryption_decryption_fun('encrypt', $pre_view[0]->id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $reference_number).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id),array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
	
	if(!empty($pre_view)){
	//print_r($pre_view);die();
		$header = array(
		array('data'=> 'Sl. No.','width'=> '8%'),
		//array('data'=> 'Application Period','width'=> '20%'),
		array('data'=> 'Change Date','width'=> '20%'),
		array('data'=> 'Previous Name','width'=> '34%'),
		array('data'=> 'Conversion Name','width'=> '34%'),
		array('data'=> 'Transfer Fees','width'=> '20%'),
		//array('data'=> 'Action','width'=> '10%'),
		
	);
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
			//array('data' => t($view->service_year)),
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
}



?>