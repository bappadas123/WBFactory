<?php

function active_factory_list($form, &$form_state,$factory_status) {

	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
    $form = array();
	//echo $user->uid;die();
	$license_no = NULL;
	$valid_upto = NULL;
	//echo $factory_status;
	//$tm_fact_data = fun_fetch_fact_tm($license_no,$valid_upto,$factory_status);
	//print_r($tm_fact_data);die;
	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Factories did not travel for any services from our portal or pre-existing portals</h3></div>
						<div class="box-tools pull-right">
						<button type="button" class="btn btn-box-tool" data-widget="collapse" title="Minimise"><i class="fa fa-minus"></i> </button>
						<button type="button" class="btn btn-box-tool" data-widget="remove" title="Close"><i class="fa fa-times"></i></button>
						</div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_type_application($license_no,$valid_upto,$factory_status),
  	);		  
	return $form; 
  }
		 
function get_all_type_application($license_no,$valid_upto,$factory_status){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
	$rows[] 				= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';
	$status 				= '';
	$link					= '';
	$pdf_link 				= '';
	$edit_link				= '';
	$preview_link			= '';
	$upload_link			= '';

	$get_all_data 			=  fun_fetch_fact_tm($license_no,$valid_upto,$factory_status);
	
   $Wcounter				= 0;
	$per_page				= 100;
	$current_page 			= pager_default_initialize(count($get_all_data), $per_page);
	
	
	$chunks 				= array_chunk($get_all_data, $per_page, TRUE);
	
	if($current_page>0){
		$Wcounter 			= $current_page*$per_page;
	}
	$header 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Details','width' => '25%'),
								array('data'=> 'Comunication Details','width' => '25%'),
								array('data'=> 'Status','width' => '22%'),
								array('data'=> 'Action','width' => '22%'),
								
							);						
		
		
		
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if($details->classification_type == 1){
				$scetion = 'Section-2m(i)';
			}if($details->classification_type == 2){
				$scetion = 'Section-2m(ii)';
			}if($details->classification_type == 3){
				$scetion = 'Section-85';
			}
			$factory_zone		   		= 	!empty($details->new_zone_id)?$details->new_zone_id:$details->unit_zone_id;
			$zone_name_dt 				=  	get_factory_zone_name($factory_zone);
			$zone_name					=	!empty($zone_name_dt['zone_name'])?$zone_name_dt['zone_name']:'<font color="red">Not Available</font>';
			$date_of_amenability      	= 	!empty($details->amenability_date)?date('d-m-Y',strtotime($details->amenability_date)):'<font color="red">Not Available</font>';
			$backlog_registration_no	= 	!empty($details->registration_no)?$details->registration_no:'<font color="red">Not Available</font>';
			$backlog_registration_date	= 	!empty($details->registration_date)?date('d-m-Y',strtotime($details->registration_date)):'<font color="red">Not Available</font>';
			$backlog_license_number	  	= 	!empty($details->license_no)?$details->license_no:'<font color="red">Not Available</font>';
			$license_date	  		  	= 	!empty($details->last_license_date)?date('d-m-Y',strtotime($details->last_license_date)):(!empty($details->license_date)?date('d-m-Y',strtotime($details->license_date)):'<font color="red">Not Available</font>');
			$factory_addrline      		= 	!empty($details->unit_address)?$details->unit_address:'<font color="red">Not Available</font>';
			$license_valid_upto		    = 	!empty($details->license_valid_upto_date)?date('d-m-Y',strtotime($details->license_valid_upto_date)):'<font color="red">Not Available</font>';
			
			$comm_telephone     	  =!empty($details->unit_comm_phone_no)?$details->unit_comm_phone_no:'<font color="red">Not Available</font>';
			$comm_mobile     	      = !empty($details->unit_comm_mobile_no)?$details->unit_comm_mobile_no:'<font color="red">Not Available</font>';
			$comm_fax     	          = !empty($details->unit_comm_fax_no)?$details->unit_comm_fax_no:'<font color="red">Not Available</font>';
			$comm_email     	      = !empty($details->unit_comm_email)?$details->unit_comm_email:'<font color="red">Not Available</font>';
			$comm_alt_mobile 		  = !empty($details->unit_comm_mobile_no)?$details->unit_comm_mobile_no:'<font color="red">Not Available</font>';
			$office_addrline_comm 	  = !empty($details->loc_office_address)?$details->loc_office_address:'<font color="red">Not Available</font>';
			
			
			if($details->service_id == 16){
				$factory_zone		   		= 	!empty($details->factory_zone)?$details->factory_zone:$details->factory_zone;
				$zone_name_dt 				=  	get_factory_zone_name($factory_zone);
				$zone_name					=	!empty($zone_name_dt['zone_name'])?$zone_name_dt['zone_name']:'<font color="red">Not Available</font>';
				$factory_addrline      		= 	!empty($details->addrline)?$details->addrline:'<font color="red">Not Available</font>';
			$date_of_amenability      	= 	!empty($details->date_of_amenability)?date('d-m-Y',strtotime($details->date_of_amenability)):'<font color="red">Not Available</font>';
			$backlog_registration_no	= 	!empty($details->backlog_registration_no)?$details->backlog_registration_no:'<font color="red">Not Available</font>';
			$backlog_registration_date	= 	!empty($details->backlog_license_date)?date('d-m-Y',strtotime($details->backlog_license_date)):'<font color="red">Not Available</font>';
		
			$backlog_license_number	  	= 	!empty($details->backlog_license_number)?$details->backlog_license_number:'<font color="red">Not Available</font>';
			$license_date	  		  	= 	!empty($details->backlog_license_date)?date('d-m-Y',strtotime($details->backlog_license_date)):'<font color="red">Not Available</font>';	
			$license_valid_upto	= 	!empty($details->license_valid_upto)?date('d-m-Y',strtotime($details->license_valid_upto)):'<font color="red">Not Available</font>';
			
			$comm_telephone     	  =!empty($details->comm_telephone)?$details->comm_telephone:'<font color="red">Not Available</font>';
			$comm_mobile     	      = !empty($details->comm_mobile)?$details->comm_mobile:'<font color="red">Not Available</font>';
			$comm_fax     	          = !empty($details->comm_fax)?$details->comm_fax:'<font color="red">Not Available</font>';
			$comm_email     	      = !empty($details->comm_email)?$details->comm_email:'<font color="red">Not Available</font>';
			$comm_alt_mobile 		  = !empty($details->comm_mobile)?$details->comm_mobile:'<font color="red">Not Available</font>';
			$office_addrline_comm 	  = !empty($details->addrline_comm)?$details->addrline_comm:'<font color="red">Not Available</font>';
			
				
				$details_factor = $details->factory_name.' ['.$scetion.']<br><b>Address:-</b>'.$factory_addrline.'<br><b>Zone - </b>'.$zone_name.'<br/><b>Date of Amenability:-</b>'.$date_of_amenability.'<br/><b>Reg. No.:-</b>'.$backlog_registration_no.' dated on '.$backlog_registration_date.'<br/><b>License. No.:-</b>'.$backlog_license_number.' dated on '.$license_date.'<br/><br/><b><font color = "red">License Expire Date:'.$license_valid_upto.'</font></b>';
				
			if($details->application_status == 'In'){
				$status = 'Factory Information <br/>is partially submitted';
				$edit_link = l('Add/Edit for Inspection','applicant/backlog-factory-add/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit'))) ;
			}if($details->application_status == 'A'){
				$status = 'Factory Information <br/>is successfully submitted';
				$edit_link = 'This factory ia added to our inspcetion list' ;
			}
			
			
			$communication_deatils = '<b>Address:-</b>'.$office_addrline_comm.'<br><b>Telephone - </b>'.$comm_telephone.'<br/><b>Mobile:-</b>'.$comm_mobile.'<br/><b>Fax.:-</b>'.$comm_fax.' <br/><b>Email.:-</b>'.$comm_email;
			
				
			}else{
				
				$service_id		= 	16;
				 $license_no	  	= 	!empty($details->license_no)?$details->license_no:$details->registration_no;
				 $valid_upto	 	= 	!empty($details->license_valid_upto_date)?$details->license_valid_upto_date:$details->registration_date;
				
				$details_factor = $details->unit_name.' ['.$scetion.']<br><b>Address:-</b>'.$factory_addrline.'<br><b>Zone - </b>'.$zone_name.'<br/><b>Date of Amenability:-</b>'.$date_of_amenability.'<br/><b>Reg. No.:-</b>'.$backlog_registration_no.' dated on '.$backlog_registration_date.'<br/><b>License. No.:-</b>'.$backlog_license_number.' dated on '.$license_date.'<br/><br/><b><font color = "red">License Expire Date:'.$license_valid_upto.'</font></b>';
				
			$status = '<b>'.$details->status.'</b>';
			$communication_deatils = '<b>Address:-</b>'.$office_addrline_comm.'<br><b>Telephone - </b>'.$comm_telephone.'<br/><b>Mobile:-</b>'.$comm_mobile.'<br/><b>Fax.:-</b>'.$comm_fax.' <br/><b>Email.:-</b>'.$comm_email;
			$edit_link = l('Add/Edit for Inspection','applicant/add-factory-part1/'.encryption_decryption_fun('encrypt',$license_no).'/'.encryption_decryption_fun('encrypt',$valid_upto).'/'.encryption_decryption_fun('encrypt',$service_id),array('html' => TRUE,'attributes'=>array('title' => 'Edit'))) ;
			}
			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details_factor,'class' => array('')),
							array('data' =>$communication_deatils,'class' => array('')),
							array('data' =>$status,'class' => array('')),
							array('data' =>$edit_link,'class' => array(''))
						
						);
	 
	}
	$output = theme_table(
	array(
		  'header' 			=> $header,
		  'rows' 			=> $rows,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');	
		 return $output;
	
}
}



?>