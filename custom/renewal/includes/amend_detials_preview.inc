<?php
 drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

function amand_detials_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t('Amendment Notice'),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('amend_detials_preview',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('amend_detials_preview');
   }
   }

   
function amend_detials_preview($form, &$form_state) {	
$link 			 = $_GET['q'];

$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	 
	  return $form;	

}
function view_details($serviceid,$factory_typeid,$applicationid,$reference_no){
	$applicant_id 			= $user->uid;
	$worker_details 		= array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';					
	/* WORKER DETAILS */
	
	if($factory_typeid==1 || $factory_typeid == 3){
		$get_all_data = fetch_old_data($applicationid,$serviceid,$factory_typeid,$reference_no);
//print_r($get_all_data);die();
	
	$output = '<table class="renewal-table" >
							
						 <tr>
						 <th >Licence Period</th>
						<th >Previous Total Worker</th>  
						<th >Amendment Worker</th>
						<th >Previous power</th>  
						<th >Amendment Power</th>
						
						 </tr>
						 '
						 ;
		
	
	foreach($get_all_data as $amand){
		
		$Licence_Period= $amand->service_year;
		$Previous_Total_Worke = $amand->previous_worker;
		$Amendment_Worker=$amand->worker_total;
		$Previous_power = $amand->previous_power.' ('.$amand->previous_power_unit.')';
	     $Amendment_power =$amand->installed_power.' ('.$amand->power_unit.')';	
		
		$output .='<tr>
	<td>'.$Licence_Period.'</td>
	<td>'.$Previous_Total_Worke.'</td>
	<td>'.$Amendment_Worker.'</td>
	<td>'.$Previous_power.'</td>
	<td>'.$Amendment_power.'</td>
	
	
	</tr>';
		
	}
	}
	if($factory_typeid==2){
		
		$amand_notice = fun_worker_detials_amendnotice($applicationid,$serviceid,$factory_typeid,$reference_no);
		//print_r($amand_notice);die();
		$output = '<table class="renewal-table" >
							
						 <tr>
						 <th >Licence Period</th>
						<th >Previous Total Worker</th>  
						<th >Amendment Worker</th>
					
						
						 </tr>
						 '
						 ;
		
	
	foreach($amand_notice as $notice){
		
		$Licence_Period= $notice->service_year;
		$Previous_Total_Worke = $notice->previous_worker;
		$Amendment_Worker=$notice->worker_total;
		
		
		$output .='<tr>
	<td>'.$Licence_Period.'</td>
	<td>'.$Previous_Total_Worke.'</td>
	<td>'.$Amendment_Worker.'</td>

	
	
	</tr>';
	}
	
	}
	
	'</table>';
		return $output;

}

?>