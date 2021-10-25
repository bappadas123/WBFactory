<?php
function check_amendment_year_form($form, &$form_state, $applicationid, $serviceid, $factorytypeid, $referenceno) {
	
	drupal_add_js(drupal_get_path('module', 'amendment') . '/js/myfunction.js');
	
	$application_id 		= 	encryption_decryption_fun('decrypt', $applicationid);
	$service_id 			= 	encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 		= 	encryption_decryption_fun('decrypt', $factorytypeid);
	$reference_no			=  	encryption_decryption_fun('decrypt', $referenceno);
		
	//die($application_id.'<br>'.$service_id.'<br>'.$factorytype_id.'<br>'.$reference_no);
	$form = array();
   	$form['#attributes'] = array('enctype' => "multipart/form-data");
		
	$form['serviceid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid
	);	
	$form['factorytype_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=>  $factorytypeid
	);		  	   
	$form['referance_no_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $referenceno
	);
	$form['application_id_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $applicationid
	);
	
	$form['applicantion_verify']['markup_appplication'] = array(
		'#prefix' => '<div class="row"><div class="box box-info"><div class="box-header with-border"><center><h3 class="box-title"><b>Check the year of amendment notice</b></center></div><div class = "box-body">',
		'#suffix' => '</div></div></div>',
		'#type' => 'markup',
		'#markup' => get_amendment_year_data($application_id,$service_id,$factorytype_id,$reference_no),
	   );
	   
//print_r($get_amendment_year_data);die;

	$form['applicantion_verify']['fieldname']	= array(
		'#title'			=> 'Field Name',
		'#type'				=> 'hidden',
		'#attributes'		=> array('id' => 'amendment_year_check'),
		'#default_value' 	=> !empty($content['application_period']) ? $content['application_period'] : '',
   	);
	
	$form['amendment_submit'] = array(
		'#prefix' => '<div class="col-md-1  col-xs-1">',
		'#suffix' => '</div>',
		'#attributes' => array('class' => array('btn btn-success '), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}', 'id' => 'checkBtn'),
		'#type' => 'submit',
		'#value' => 'Proceed'
	);
	return $form;	
}

function check_amendment_year_form_validate($form, &$form_state) {
	if($form_state['values']['fieldname'] == '') {
		form_set_error('fieldname', t('You have to select atleast one Application Period.'));	
	}	
}

function check_amendment_year_form_submit($form, &$form_state) {
	
	global $user;
	$uid	= $user->uid;
	$val   	= $form_state['values'];
	
	
	$factorytype_id		= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	$reference_no		=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	$application_id 	= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	$service_id 		= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);

	$cafa_field = array(
		'application_period' => trim($val['fieldname'],",")
	);


	$amendment_checking = get_amendment_checking($application_id,$service_id,$factorytype_id,$reference_no);

	$remark_field = explode(',',$amendment_checking['fieldname']);
	//print_r($remark_field);
	foreach ($remark_field as $fieldname){
		if($fieldname == 'factory_name'){$factory_name = "1";}
	}


	$names = explode(',',$val['fieldname']);
	foreach($names  as $nm){
		$start_date= get_starting_date($nm);
		if(!empty($start_date)){
			break;
		}
	}

	
	if(!empty($factory_name)){

		if(!empty($start_date)){

			$check_point_id =  fun_check_check_point($application_id,$reference_no,$factorytype_id,$service_id);

			if(empty($check_point_id)|| ($check_point_id == NULL) ||($check_point_id==0)){
				drupal_set_message('please! check atleast one application year.' ,'Error');
			}else{
				$previous_year	=	db_update('fa_caf_check_point');
				$previous_year	->	fields($cafa_field);
				$previous_year	->	condition('app_id',$application_id,'=');
				$previous_year	->	condition('reference_no',$reference_no,'=');
				$previous_year	->	condition('factory_type',$factorytype_id,'=');
				$previous_year	->	condition('service_id',$service_id,'=');
				$previous_year	->	execute();
			}
			
			if($service_id == 3){
				drupal_goto('applicant/change-renewal/transfer-declaration/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['application_id_hidden'].'/'.$val['referance_no_hidden']);
			}elseif($service_id == 8){
				//drupal_goto('applicant/change-renewal/transfer-declaration/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['application_id_hidden'].'/'.$val['referance_no_hidden']);
				drupal_goto('applicant/amendment/amendment-information/'.$val['application_id_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['referance_no_hidden']);	
			}

			//drupal_set_message('Change with transfer.');

		}else{

			drupal_set_message('You need to change Name of factory, so you can not decleare future date.','error');
		}
		

	}else{

		$check_point_id =  fun_check_check_point($application_id,$reference_no,$factorytype_id,$service_id);
			if(empty($check_point_id)|| ($check_point_id == NULL) ||($check_point_id==0)){
				drupal_set_message('Data not found' ,'Error');
			}else{
				$previous_year	=	db_update('fa_caf_check_point');
				$previous_year	->	fields($cafa_field);
				$previous_year	->	condition('app_id',$application_id,'=');
				$previous_year	->	condition('reference_no',$reference_no,'=');
				$previous_year	->	condition('factory_type',$factorytype_id,'=');
				$previous_year	->	condition('service_id',$service_id,'=');
				$previous_year	->	execute();
			}
			if($service_id == 3){
				drupal_goto('applicant/change-renewal/transfer-declaration/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['application_id_hidden'].'/'.$val['referance_no_hidden']);	
			}elseif($service_id == 8){
				//drupal_goto('applicant/change-renewal/transfer-declaration/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['application_id_hidden'].'/'.$val['referance_no_hidden']);	
				drupal_goto('applicant/amendment/amendment-information/'.$val['application_id_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['referance_no_hidden']);	
			}
			
			//drupal_set_message('Change without transfer.');

	}

	
}
	
function get_amendment_year_data($application_id,$service_id,$factorytype_id,$reference_no) {



	$years = get_amend_year($application_id);
	//$fetch_checkpoint = fetch_checkpoint($application_id,$reference_no,$factorytype_id,$service_id);
   //$application_period = explode(',', $fetch_checkpoint['application_period']);
	//print_r($years);
	//print_r($fetch_checkpoint);
	//die;
	$output = '<table width="100%" class="table table-bordered custom-table-view">
				<tr>
					<th width="10%">SL No.</th>
					<th width="50%">Application Period</th>
					<th width="40%" class="center"> Check <input type="checkbox" id="amend_select_all"/></th>
				</tr>';

	$sl=1;			
	foreach($years as $year) {
		
		$output .= '<tr>
						<td width="10%">'.$sl.'</td>
   						<td width="50%">'.$year->calculate_year.'</td>
   						<td width="40%" class="center"><input type="checkbox" id="'.$year->id.'" class="amendment_year_check"/></td>
   					</tr>';
					$sl++;
				}
		$output.='</table>';
		return $output;
	}

	function get_starting_date($ids){

		$current_date = date('yy-m-d');
		
		$sql_start_date	=  db_query("SELECT calculate_starting_year  FROM {fa_calculate_year} WHERE id = '".$ids."'AND calculate_starting_year <= '".$current_date."'  ORDER BY id ASC  LIMIT 1")->fetchObject()->calculate_starting_year;
	
		return $sql_start_date;
	}