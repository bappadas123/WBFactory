<?php
//$applicationid
function details_previous_name_factory($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp) {	
	global $base_root, $base_path, $user;
 	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }else{
		 	$get_fa_cafa = get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$date_of_amenability		= $get_fa_cafa['date_of_amenability'];
			
  
	 }
	 
	  
	
	$service_id 	= encryption_decryption_fun('decrypt',$serviceid);
	$factory_typeid = encryption_decryption_fun('decrypt',$factory_type_id);
	//////////////////////////////occupier Type////////////////////////
	$get_fa_cafa 		= get_fa_cafa($application_id);
    $reference_no 		= $get_fa_cafa['reference_number'];
	
	//////////////////////////////end occupier Type////////////////////////
	
	
	
    $form = array();
	$form['serviceid_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> $serviceid,
		);
	$form['factorytypeid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_type_id
			 
		);
	$form['reference_no_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number)
			 
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	
	//drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	 $ownershiptype  = array(
        "0" 			=> "Select",
		"pv" 			=> "Pvt Ltd Company",
        "ltd" 			=> "Ltd Company",
		"dir_firm" 		=> "Directorship Firm",
        "par_firm" 		=> "Partnership Firm",
		"pro_firm" 		=> "Proprietorship Firm",
        "govt" 			=> "Govt.",
		"psu" 			=> "PSU",
		"others" 		=> "Others",
 
    );
	$form['yearly_name']['factory_name_table'] 	= array(
  			
  				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
              <h3 class="box-title">Previous Factory Name details</h3>
              
            </div><div class = "box-body">
			<table class="table table-bordered"> <tr>
   								<th>Apply year</th>
   								<th>Change Date</th>
    							<th>Ownership Type</th>
	 							<th>Name</th>
	 							
 								</tr>'
			
  
			);	

	$year_data 			= fetch_year_asc($application_id,$service_id,$factory_typeid,$reference_number);
  $current_year 		= date("Y");
	$i = 1;
	foreach($year_data as $row){
		$year_array		= (explode(" ",$row->calculate_year));
		$r				= validateDate($year_array[0], 'Y-m-d');
		if($r==1){
				 $actuall_year= date('Y', strtotime($year_array[0]));
		}else{
			   $actuall_year = $year_array[0];
		}
		$r	= validateDate($year_array[0], 'Y-m-d');
		if($r==1){
				 $actuall_year= date('Y', strtotime($year_array[0]));
		}else{
			   $actuall_year = $year_array[0];
		}
			
		if($actuall_year<=$current_year){
				$form['yearly_name']['name_year1_'.$i] = array(
						'#type' 	 => 'markup',
						'#markup' 	 =>  '<tr><td>',
		  
				);
				
			$is_previous_name = is_previous_name($application_id,$reference_number,$factory_typeid,$service_id,$row->calculate_year);
			
			
			$form['yearly_name']['name_year_'.$i] 	= array(
				  '#prefix' 			=> '<div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td><td>',
				  '#type' 				=> 'textfield',
				  '#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				  '#default_value'		=> $row->calculate_year,
				 
			
				);
			if($is_previous_name>0){
				$previous_details =  get_previous_details_yearwise($application_id,$reference_number,$factory_typeid,$service_id,$row->calculate_year);
				foreach($previous_details as $row_details){
					$form['yearly_name']['name_date_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td>',
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_details->change_date,
					  '#attributes' 		=> array('class'=>array('form-control datepicker')),
					 
				
					);
				
				$form['yearly_name']['name_type_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#type' 				=> 'select',
		     		   '#default_value'		=> $row_details->ownership_type,
					   '#options'			=> $ownershiptype,
					   '#attributes' 		=> array('class'=>array('form-control')),
					  
					 
							
					);	
				$form['yearly_name']['name_previous_name_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td></tr>',
					  '#type' 				=> 'textfield',
					    '#default_value'	=> $row_details->pervious_factory_name,
					  '#attributes' 		=> array('class'=>array('form-control')),
					
					  
					);
				}
				
			}else{
				$form['yearly_name']['name_date_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td>',
					  '#type' 				=> 'textfield',
					  '#attributes' 		=> array('class'=>array('form-control datepicker')),
					 
				
					);
				
				$form['yearly_name']['name_type_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#type' 				=> 'select',
					   '#default_value'		=> $row_worker->worker_women,
					   '#options'			=> $ownershiptype,
					   '#attributes' 		=> array('class'=>array('form-control')),
					  
					 
							
					);	
				$form['yearly_name']['name_previous_name_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td></tr>',
					  '#type' 				=> 'textfield',
					  '#attributes' 		=> array('class'=>array('form-control')),
					
					  
					);
			}
			
			
				
		}
		
		
		
	
	  $i=$i+1;
		
   }
 


	$form['yearly_name']['factory_name_table_end'] 	= array(
					'#suffix' => '</table></div></div></div>',
					
			);	
	
	$form['back_link']	 = array(
					
				'#markup' 		=> l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
		);
					
	$form['submit'] = array (
	  		
	  		
	  		'#type' 		=> 'submit',
	   		'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
	  		'#value' 		=> 'Save & Continue'
		); 

            return $form; 
        
    }

function details_previous_name_factory_submit($form, &$form_state){
	global $user;
	$uid 			    			= 	$user->uid;
	$val   							= 	$form_state['values'];
	$service_id						= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 				=	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no		= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
    $current_year 					=   date("Y");
	$get_fa_cafa           			=  get_fa_cafa($application_id);
	$factory_name					=  $get_fa_cafa['factory_name'];
	$factory_owershiptype			=  $get_fa_cafa['factory_owershiptype'];
	$created_date					=  $get_fa_cafa['created_date'];
	
   del_previous_name($application_id,$service_id,$factory_type_id,$application_reference_no);
   $year_data = fetch_year_asc($application_id,$service_id,$factory_type_id,$application_reference_no);
   $i = 1;
   $k = 0;
 
foreach($year_data as $row){
	$year_array		= (explode(" ",$row->calculate_year));
		$r			= validateDate($year_array[0], 'Y-m-d');
		if($r==1){
				 $actuall_year= date('Y', strtotime($year_array[0]));
		}else{
			   $actuall_year = $year_array[0];
		}
		$r	= validateDate($year_array[0], 'Y-m-d');
		if($r==1){
				 $actuall_year= date('Y', strtotime($year_array[0]));
		}else{
			   $actuall_year = $year_array[0];
		}
		
		if($actuall_year<$current_year){
			if($k>0){
				if($val['name_type_'.$i] == "pv" || $val['name_type_'.$i] == "ltd" || $val['name_type_'.$i] == "par_firm" ){
					if($val['name_type_'.$k] == "pv" || $val['name_type_'.$k] == "ltd" || $val['name_type_'.$k] == "par_firm" ){//echo $val['name_type_'.$i].$i.'i'.'<br/>'.$val['name_type_'.$k].$k.'k<br>';
						if($val['name_type_'.$i] != $val['name_type_'.$k]){
						 $is_change =1;
						 $transfer_fees = 1000;
						}else{//echo $val['name_type_'.$i].'<br/>'.$val['name_type_'.$k].'<br>';
							$is_change 		=0;
							$transfer_fees = 0;
						}
				 }
				}
			}
				$previos_name =array(
				'pervious_factory_name' 		      => $val['name_previous_name_'.$i],
				'change_date'						  => date("Y-m-d", strtotime($val['name_date_'.$i])),
				'ownership_type'					  => $val['name_type_'.$i],
				'service_id' 		             	  => $service_id,
				'application_id'              		  => $application_id,
				'name_application_status' 	  		  => 'In',
				'factory_type'				     	  => $factory_type_id,
				'created_by'				          => $service_id,
				'service_year'				          => $val['name_year_'.$i],
				'factory_type'				          => $factory_type_id,
				'created_by'				          => $uid,
				'application_reference_no'			  => $application_reference_no,
				'name_active_inactive'				  => $row->is_active_year,
				'is_change'							  => $is_change,
				'transfer_fees'						  => $transfer_fees
				
			);
		
		
		$id = db_insert('fa_factory_previous_name')->fields($previos_name)->execute();
	
}
$i= $i+1;
$k = $k+1;
$is_change =0;
$transfer_fees = 0;
	}
	//die();

$max_previous_name = max_previous_name($application_id,$application_reference_no,$factory_type_id,$service_id);
if($max_previous_name == "pv" || $max_previous_name == "ltd" || $max_previous_name == "par_firm" ){
	if($factory_owershiptype == "pv" || $factory_owershiptype == "ltd" || $factory_owershiptype == "par_firm" ){
		if($max_previous_name !=$factory_owershiptype){
			$is_change =1;
			$transfer_fees = 1000;
		}else{
			$is_change =0;
			$transfer_fees = 0;
}	
		}
}
/*if($max_previous_name !=$factory_owershiptype){
	$is_change =1;
}else{
	$is_change =0;
}*/	

foreach($year_data as $row){
	$year_array		= (explode(" ",$row->calculate_year));
		$r			= validateDate($year_array[0], 'Y-m-d');
		if($r==1){
				 $actuall_year= date('Y', strtotime($year_array[0]));
		}else{
			   $actuall_year = $year_array[0];
		}
		$r	= validateDate($year_array[0], 'Y-m-d');
		if($r==1){
				 $actuall_year= date('Y', strtotime($year_array[0]));
		}else{
			   $actuall_year = $year_array[0];
		}
		
		if($actuall_year>$current_year){
	
$previos_name =array(
				'pervious_factory_name' 		      => $factory_name,
				'change_date'						  => $created_date,
				'ownership_type'					  => $factory_owershiptype,
				'service_id' 		             	  => $service_id,
				'application_id'              		  => $application_id,
				'name_application_status' 	  		  => 'In',
				'factory_type'				     	  => $factory_type_id,
				'created_by'				          => $service_id,
				'service_year'				          => $row->calculate_year,
				'factory_type'				          => $factory_type_id,
				'created_by'				          => $uid,
				'application_reference_no'			  => $application_reference_no,
				'name_active_inactive'				  => $row->is_active_year,
				'is_change'							  => $is_change,
				'transfer_fees'						  => $transfer_fees
				
			);
		
		
			$id = db_insert('fa_factory_previous_name')->fields($previos_name)->execute();
			$is_change =0;
			$transfer_fees = 0;
//-------------Fetch director------------------------
}

	}
	//die();
}	
