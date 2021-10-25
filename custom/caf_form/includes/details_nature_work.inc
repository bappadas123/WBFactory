<?php
//$applicationid
function details_nature_work($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp) {	
	global $base_root, $base_path, $user;
 	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
				drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
				drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
		 }else{
		 	$get_fa_cafa = get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
	}
	 
	 
	if(empty($is_year_calculation_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the worker information'),'warning');
			
			drupal_goto('applicant/caf-reg/details-applyingyear-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }  
	$service_id 	= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id = encryption_decryption_fun('decrypt',$factory_typeid);
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
			 '#default_value' 	=> $factory_typeid
			 
		);
	$form['reference_no_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number)
			 
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	
	
	$form['nature_worker']['nature_worker_header'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
              				<h3 class="box-title">L.Nature of Manufacturing process</h3>
                            </div><div class = "box-body">
							<table class="table table-bordered"> <tr>
   							<th>Application Period</th>
   							<th>Manufacturing process</th>
    						</tr>'
			
  
			);	
	
	
	$year_data = fetch_year($application_id,$service_id,$factory_type_id,$reference_no);
	$i 		   = 1;
    foreach($year_data as $row){
		$form['nature_worker']['nature_year1'.$i] = array(
						
						'#type' 	 => 'markup',
						'#markup' 	 =>  '<tr><td>',
		  
					);
		$manufacturing_detials_year = nature_manufacturing_year($row->calculate_year,$application_id,$reference_no,$factory_type_id,$service_id);
		if(!empty($manufacturing_detials_year)){
			$form['nature_worker']['nature_year_'.$i] 	= array(
				  '#prefix' 	=> '<div class="col-xs-12">',
				  '#suffix' 	=> '</div></td><td>',
				  '#title'		=>	t('Period').$i,
				  '#type' 		=> 'textfield',
				  '#default_value'=> $row->calculate_year,
				  '#attributes' => array('class'=>array('form-control'),'readonly' => 'readonly'),
			);
		
			foreach($manufacturing_detials_year as $row_nature){
			
			
					$form['nature_worker']['nature_manufacturing_'.$i] 	= array(
							 '#prefix' 			=> '<div class="col-xs-12">',
							 '#suffix' 	 		=> '</div></td></tr>',
							 '#suffix' 	 		=> '</label>',
							 '#title'			=>	t('Carried/to be carried on the factory'),
							 '#type' 	 		=> 'textfield',
							 '#default_value'	=> $row_nature->nature_manufacturing,
							 '#attributes' 		=> array('class'=>array('form-control')),
					 	); 
			}
			$form['markup_note'] 	= array(
					 '#prefix' 			=> '<div class="col-xs-12">',
					 '#suffix' 	 		=> '</div>',
					 '#type' 			=> 'markup',
					 '#markup'			=> '<font color="#FF0000"><b>Please note:-Manufacturing process of subsequrent years has been populated based on first input. However appliant may change the values in next year(s) manually if requried.</b></font>',
		    );	
			$form['submit'] = array (
					'#type' 			=> 'submit',
					'#attributes' 		=> array('class' => array('btn btn-info pull-right')),
					'#value' 			=> 'Save & Continue'
			);
		}
		
	if(empty($manufacturing_detials_year)){
		if($row->is_active_year != 1){
			$form['nature_worker']['nature_year'] 	= array(
				  '#prefix' 	=> '<div class="col-xs-12">',
				  '#suffix' 	=> '</div></td><td>',
				  '#title'		=>	t('Period').$i,
				  '#type' 		=> 'textfield',
				  '#default_value'=> $row->calculate_year,
				  '#attributes' => array('class'=>array('form-control'),'readonly' => 'readonly'),
			);
		   $form['nature_worker']['nature_manufacturing'] 	= array(
					 '#prefix' 			=> '<div class="col-xs-12">',
					 '#suffix' 	 		=> '</div></td></tr>',
					 '#suffix' 	 		=> '</label>',
					 '#title'			=>	t('Carried on the factory'),
					 '#type' 	 		=> 'textfield',
					 
					 '#attributes' 		=> array('class'=>array('form-control')),
					 ); 
		}
		$form['previous_data'] = array (
	  		
	  		
	  		'#type' 		=> 'submit',
	   		'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
	  		'#value' 		=> 'Save'
		); 
	break;	
	}
	
	$i=$i+1;

}
	


$form['nature_worker']['nature_worker_table_end'] 	= array(
  			'#markup' 	=> '</table>',
  			'#suffix' 	=> '</div></div>',
 );	
$form['nature_worker']['back_link']	 = array(
		'#markup' 		=> l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
);


return $form; 
        
   }

function details_nature_work_validate($form, &$form_state) {

   if (isset($form_state['values']['nature_manufacturing']) && !$form_state['values']['nature_manufacturing']) {
    form_set_error('nature_manufacturing', 'Please enter a manufacturing process');    
  }
}
function details_nature_work_submit($form, &$form_state){
	global $user;
	$uid 			    			= 	$user->uid;
	$val   							= 	$form_state['values'];
	$service_id						= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 				=	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no		= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	del_nature_work($application_id,$service_id,$factory_type_id,$application_reference_no);
	$year_data = fetch_year($application_id,$service_id,$factory_type_id,$application_reference_no);
	if($val['op'] == "Save"){
	  foreach($year_data as $row){
			$nature_work =array(
					'nature_manufacturing' 		          => $val['nature_manufacturing'],
					'service_id' 		             	  => $service_id,
					'application_id'              		  => $application_id,
					'service_year' 		     			  => $row->calculate_year,
					'manufacturing_application_status' 	  => 'In',
					'factory_type'				     	  => $factory_type_id,
					'created_by'				          => $service_id,
					'factory_type'				          => $factory_type_id,
					'created_by'				          => $uid,
					'application_reference_no'			  => $application_reference_no,
					'manufacturing_active_inactive'		  => $row->is_active_year,
					'valid_year'					 	  => $row->calculate_end_year,
					'valid_time_period'				      => $row->valid_time_period,
					'starting_year'	     			      => $row->calculate_starting_year,
					'calculate_year_id'				      => $row->id,
			
				);
		
		
			$id = db_insert('fa_nature_manufacturing')->fields($nature_work)->execute();
			
		}
	}
	else{
		$i = 1;

foreach($year_data as $row){
	$nature_work =array(
			'nature_manufacturing' 		          => $val['nature_manufacturing_'.$i],
			'service_id' 		             	  => $service_id,
			'application_id'              		  => $application_id,
			'service_year' 		     			  => $val['nature_year_'.$i],
			'manufacturing_application_status' 	  => 'In',
			'factory_type'				     	  => $factory_type_id,
			'created_by'				          => $service_id,
			'service_year'				          => $val['nature_year_'.$i],
			'factory_type'				          => $factory_type_id,
			'created_by'				          => $uid,
			'application_reference_no'			  => $application_reference_no,
			'manufacturing_active_inactive'		  => $row->is_active_year,
			'valid_year'					 	  => $row->calculate_end_year,
			'valid_time_period'				      => $row->valid_time_period,
			'starting_year'	     			      => $row->calculate_starting_year,
			'calculate_year_id'				      => $row->id,
		);
		
		
			$id = db_insert('fa_nature_manufacturing')->fields($nature_work)->execute();
	$i= $i+1;
}
		
	}



	
}
//-------------Fetch director------------------------
